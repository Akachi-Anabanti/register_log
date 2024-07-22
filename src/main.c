#include <gtk/gtk.h>
#include "gui/main_window.h"
#include "../include/database.h"
#include "../include/fingerprint.h"
#include <gtk/gtktypes.h>



int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    if (!initialize_database()){
        g_printerr("Failed to initialize database\n");
        return 1;
    }

    if (!initialize_fingerprint_sensor()){
        g_printer("Failed to initialize fingerprint sensor\n");
        return 1;
    }

    GtkWidget *window = create_main_window();
    gtk_widget_show(window);

    gtk_main();

    close_database();
    cleanup_fingerprint_sensor();

    return 0;
}