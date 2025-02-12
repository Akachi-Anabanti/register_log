#include <stdio.h>
#include <stdlib.h>
#include <libfprint-2/fprint.h>
#include "../include/fingerprint.h"


static FpContext *ctx = NULL;
static FpDevice *dev = NULL;

int initialize_fingerprint_sensor() {
    GError *error = NULL;
    GCancellable *cancellable = NULL;

    ctx = fp_context_new();

    if (!ctx) {
        fprintf(stderr, "Failed to create fingerprint context \n");
        return 0;
    }

    GPtrArray *devices = fp_context_get_devices(ctx);
    if (!devices || devices->len == 0){
        fprintf(stderr, "No fingerprint devices found \n");
        g_ptr_array_unref(devices);
        return 0;
    }

    dev =  g_ptr_array_index(devices, 0);
    g_object_ref(dev);
    g_ptr_array_unref(devices);

    if (!fp_device_open_sync(dev, cancellable, &error))
    {
        fprintf(stderr, "Failed open device: %s\n", error->message);
        g_error_free(error);
        return 0;
    }

    return 1;
}


int enroll_fingerprint(int staff_id)
{
    GError *error = NULL;
    FpPrint *print = NULL;

    if (!dev) {
        fprintf(stderr, "Fingerprint device not initialized \n");
        return 0;
    }

    printf("Place your finger on sensor... \n");

    if (!fp_device_enroll_sync(dev, fp_print_new(dev), NULL,NULL, &print, &error))
    {
        fprintf(stderr, "Enrollment failed: %s\n", error->message);
        g_error_free(error);
        return 0;
    }


    char filename[20];
    snprintf(filename, sizeof(filename), "fp_%d.dat", staff_id);

    gsize length;
    guchar *data = NULL;

    if (!fp_print_serialize(print, &data, &length, NULL)){
        fprintf(stderr, "Failed to serialize print\n");
        g_object_unref(print);
        return 0;
    }
    FILE *file = fopen(filename, "wb");
    if (!file){
        fprintf(stderr, "Failed to open file for writing \n");
        g_object_unref(print);
        g_free(data);
        return 0;
    }

    fwrite(data, 1, length, file);
    fclose(file);

    g_object_unref(print);
    g_free(data);

    printf("Fingerprint enrolled successfully \n");
    return 1;
}

int verify_fingerprint(int staff_id)
{
    GError *error = NULL;
    FpPrint *stored_print = NULL;

    if (!dev){
        fprintf(stderr, "Fingerprint device not initialized\n");
        return 0;
    }

    /*Load the stored print from file */
    char filename[20];
    snprintf(filename, sizeof(filename), "fp_%d.dat", staff_id);
    FILE *file = fopen(filename, "rb");
    if (!file){
        fprintf(stderr, "Failed to open fingerprint file \n");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    guchar *data = g_malloc(file_size);
    fread(data, 1, file_size, file);
    fclose(file);

    stored_print = fp_print_deserialize(data, file_size, NULL);
    g_free(data);


    if (!stored_print)
    {
        fprintf(stderr, "Failed to deserialize stored print\n");
        return 0;
    }

    printf("Place your finger on the sensor for verification...\n");

    FpMatchCb result;
    gboolean match;
    FpPrint *print = NULL;
    if(!fp_device_verify_sync(dev, stored_print, NULL, result, NULL, &match, &print, &error))
    {
        fprintf(stderr, "Verification failed: %s\n", error->message);
        g_error_free(error);
        g_object_unref(stored_print);
        return 0;
    }

    g_object_unref(stored_print);
    if (print){
        g_object_unref(print);
    }

    if (match){
        printf("Fingerprint verified successfully\n");
        return 1;
    } else {
        printf("Fingerprint did not match\n");
        return 0;
    }
}

void cleanup_fingerprint_sensor(){
    if (dev){
        fp_device_close_sync(dev, NULL, NULL);
        g_object_unref(dev);
    }
    if (ctx) {
        g_object_unref(ctx);
    }
}