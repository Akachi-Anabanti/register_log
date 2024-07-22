#include <gtk/gtk.h>
#include "../include/gui/main_window.h"
#include "../include/staff.h"
#include "../include/visitor.h"


static void on_staff_check_in_clicked(GtkWidget *widget, gpointer data)
{
	/*TODO: Implement staff check-in logic*/
	g_print("Staff check-in clicked\n");
}

static void on_staff_check_out_clicked(GtkWidget *widget, gpointer data)
{
	/*TODO: Implement staff check-out logic*/
	g_print("Staff checkout clicked\n");
}

static void on_visitor_log_clicked(GtkWidget *widget, gpointer data)
{
	/*TODO: Implement visitor logging logic*/
	g_print("Visitor log clicked \n");
}


GtkWidget *create_main_window(void)
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *button;


	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_Set_title(GTK_WINDOW(window), "Register Log");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	button = gtk_button_new_label("Staff Check-In");
	g_signal_connect(button, "clicked", G_CALLBACK(on_staff_check_in_clicked), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

	button = gtk_button_new_label("Staff Check-Out");
	g_signal_connect(button, "clicked", G_CALLBACK(on_staff_check_out_clicked), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);


	button = gtk_button_new_with_label("Visitor Log");
	g_signal_connect(button, "clicked", G_CALLBACK(on_visitor_log_clicked), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);
	return window;
}

