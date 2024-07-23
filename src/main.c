#include <gtk/gtk.h>
#include "gui/main_window.h"
#include "../include/database.h"
#include "../include/fingerprint.h"

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = create_main_window();
    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_widget_show(window);
}



int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    if (!initialize_database()){
        g_printerr("Failed to initialize database\n");
        return 1;
    }

    if (!initialize_fingerprint_sensor()){
        g_printerr("Failed to initialize fingerprint sensor\n");
        // close_database();
        // return 1;
    }

    app = gtk_application_new("org.techut.registerlog", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);


    close_database();
    cleanup_fingerprint_sensor();

    return status;
}