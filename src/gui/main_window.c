#include <gtk/gtk.h>
#include "../include/gui/main_window.h"
#include "../include/staff.h"
#include "../include/visitor.h"


static void show_message_dailog(GtkWindow *parent, const char *message)
{
	GtkWidget *dialog = gtk_message_dialog_new(parent,
											   GTK_DIALOG_DESTROY_WITH_PARENT,
											   GTK_MESSAGE_INFO,
											   GTK_BUTTONS_OK,
											   "%s", message);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}


static void on_staff_check_in_clicked(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog, *content_area, *id_entry;
	GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;

	dialog = gtk_dialog_new_with_buttons("Staff Check-In",
										 GTK_WINDOW(data),
										 flags,
										 "Check-In",
										 GTK_RESPONSE_ACCEPT,
										 "Cancel",
										 GTK_RESPONSE_CANCEL,
										 NULL);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	GtkWidget *label = gtk_label_new("Enter staff ID:");
	gtk_container_Ad(GTK_CONTAINER(content_area), label);


	id_entry = gtk_entry_new();
	gtk_contianer_add(GTK_CONTAINER(content_area), id_entry);

	gtk_widget_show_all(dialog);


	gint result = gtk_dialog_run(GTK_DIALOG(dialog));
	if (result == GTK_RESPONSE_ACCEPT){
		const char *id_str = gtk_entry_get_text(GTK_ENTRY(id_entry));
		int id = atoi(id_str);
		Staff *staff = get_staff_by_id(id);
		if (staff){
			if (staff_check_in(staff)){
				show_message_dailog(GTK_WINDOW(data), "Staff checked in successfully");
			} else {
				show_message_dailog(GTK_WINDOW(data), "Failed to check in staff");
			}
		} else {
			show_message_dailog(GTK_WINDOW(data), "Staff not found");
		}
	}

	gtk_widget_destroy(dialog);
}

static void on_staff_check_out_clicked(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog, *content_area, *id_entry;
	GtkDialogFlags flags = GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT;

	dialog = gtk_dialog_new_with_buttons("Staff Check-Out",
										 GTK_WINDOW(data),
										 flags,
										 "Check-Out",
										 GTK_RESPONSE_ACCEPT,
										 "Cancel",
										 GTK_RESPONSE_CANCEL,
										 NULL);

	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

	GtkWidget *label = gtk_label_new("Enter staff ID:");
	gtk_container_add(GTK_CONTAINER(content_area), label);

	id_entry = gtl_entry_new();
	gtk_container_add(GTK_CONTAINER(content_area), id_entry);

	gtk_widget_show_all(dialog);

	gint result = gtk_dialog_run(GTK_DIALOG(dialog));
	if (result == GTK_RESPONSE_ACCEPT){
		const char *id_str = gtk_entry_get_trxt(GET_ENTRY(id_entry));
		int id = atoi(id_str);
		Staff *staff = get_staff_by_id(id);

		if (staff) {
			if (staff_check_out(staff)){
				show_message_dailog(GTK_WINDOW(data), "Staff checked out successfully");
			} else {
				show_message_dailog(GTK_WINDOW(data), "Failed to check out staff");
			}

			free_staff(staff);
		} else {
			show_message_dailog(GTK_WINDOW(data), "Staff not found");
		}
	}
	gtk_widget_destroy(dialog);
}


static void on_visitor_log_clicked(GtkWidget *widget, gpointer data)
{
	/*TODO: Implement visitor logging logic*/
	g_print("Visitor log clicked \n");
}


static void on_enroll_staff_clicked(GtkWidget *widget, gpointer data){
	GtkWidget *dialog, *content_area, *name_entry;
	GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;

	dialog = gtk_dialog_new_with_buttons("Enroll New Staff",
										  GTK_WINDOW(data),
										  flags,
										  "Enroll",
										  GTK_RESPONSE_ACCEPT,
										  "Cancel",
										  GTK_RESPONSE_CANCEL,
										  NULL);
	content_area = gtk_dialog_get_content_area(GTK_DAILOG(dialog));
	GtkWidget *label = gtk_label_new("Enter staff name:");
	gtk_container_add(GTK_CONTAINER(content_area), label);


	name_entry = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(content_area), name_entry);


	gtk_widget_show_all(dialog);

	gint result = gtk_dialog_run(GTK_DIALOG(dialog));
	if (result == GTK_RESPONSE_ACCEPT){
		const char *name = gtk_entry_get_text(GTK_ENTRY(name_entry));

		if (enroll_new_staff(name))
		{
			g_print("Staff enrolled successfully: %s\n", name);
		} else {
			g_print("Failed to enroll staff\n");
		}
	}
	gtk_widget_destroy(dialog);
}


static void on_visitor_log_clicked(GtkWidget *widgt, gpointer data){
	GtkWidget *dialog, *content_area, *name_entry;
	GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;

	dialog = gtk_dialog_new_with_buttons("Visitor Check-In",
	GTK_WINDOW(data),
	flags,
	"Check-In",
	GTK_RESPONSE_ACCEPT,
	"Cancel",
	GTK_RESPONSE_CANCEL, NULL);

	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

	gtk_container_add(GTK_CONTAINER(content_area), label);

	name_entry = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(content_area), name_entry);

	gtk_widget_show_all(dialog);


	gint result = gtk_dialog_run(GTK_DIALOG(dialog));
	if (result == GTK_RESPONSE_ACCEPT){
		const char *name = gtk_entry_get_text(GTK_ENTRY(name_entry));
		if (visitor_check_in(name)){
			show_message_dailog(GTK_WINDOW(data), "Visitor checked in successfully");
		} else {
			show_message_dailog(GTK_WINDOW(data), "Failed to check in Visitor");
		}
	}

	gtk_widget_destroy(dialog);
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

	button = gtk_button_new_with_label("Enroll New Staff");
	g_signal_connect(button, "clicked", G_CALLBACK(on_enroll_staff_clicked), window);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 2, 1);

	return window;

}
