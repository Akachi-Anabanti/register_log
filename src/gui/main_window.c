#include <gtk/gtk.h>
#include "../include/gui/main_window.h"
#include "../include/staff.h"
#include "../include/visitor.h"
#include "../include/database.h"


static void show_message_dialog(GtkWindow *parent, const char *message)
{
	GtkWidget *dialog = gtk_message_dialog_new(parent,
											   GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
											   GTK_MESSAGE_INFO,
											   GTK_BUTTONS_OK,
											   "%s", message);
	gtk_window_set_transient_for(GTK_WINDOW(dialog), parent);
	gtk_window_present(GTK_WINDOW(dialog));
	g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_window_destroy), dialog);
}


// Button responses
static void on_staff_check_in_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
	if (response_id == GTK_RESPONSE_ACCEPT){
		GtkEntry *id_entry = GTK_ENTRY(user_data);
		const char *id_str = gtk_entry_buffer_get_text(gtk_entry_get_buffer(id_entry));
		int id = atoi(id_str);
		Staff *staff = get_staff_by_id(id);
		if (staff) {
			if (staff_check_in(staff)){
			 show_message_dialog(GTK_WINDOW(dialog), "Staff checked in successfully");
			} else {
			 show_message_dialog(GTK_WINDOW(dialog), "Failed to check in staff");
			}
		} else {
		 show_message_dialog(GTK_WINDOW(dialog), "Staff not found");
		}
	}
	gtk_window_destroy(GTK_WINDOW(dialog));
}


static void on_staff_check_out_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
	if (response_id == GTK_RESPONSE_ACCEPT){
		GtkEntry *id_entry = GTK_ENTRY(user_data);
		const char *id_str = gtk_entry_buffer_get_text(gtk_entry_get_buffer(id_entry));
		int id = atoi(id_str);
		Staff *staff = get_staff_by_id(id);
		if (staff) {
			if (staff_check_out(staff)){
			 show_message_dialog(GTK_WINDOW(dialog), "Staff checked out successfully");
			} else {
			 show_message_dialog(GTK_WINDOW(dialog), "Failed to check out staff");
			}
		} else {
		 show_message_dialog(GTK_WINDOW(dialog), "Staff not found");
		}
	}
	gtk_window_destroy(GTK_WINDOW(dialog));
}


static void on_enroll_staff_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
    if (response_id == GTK_RESPONSE_ACCEPT) {
        GtkEntry *name_entry = GTK_ENTRY(user_data);
        const char *name = gtk_entry_buffer_get_text(gtk_entry_get_buffer(name_entry));
        if (enroll_new_staff(name)) {
            g_print("Staff enrolled successfully: %s\n", name);
        } else {
            g_print("Failed to enroll staff\n");
        }
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
}


static void on_visitor_check_in_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
	if (response_id == GTK_RESPONSE_ACCEPT){
		GtkEntry *name_entry = GTK_ENTRY(user_data);
		const char *name = gtk_entry_buffer_get_text(gtk_entry_get_buffer(name_entry));
		if (visitor_check_in(name)){
		 show_message_dialog(GTK_WINDOW(dialog), "Visitor checked in successfully");
		} else {
		 show_message_dialog(GTK_WINDOW(dialog), "Failed to check in Visitor");
		}

	}
	gtk_window_destroy(GTK_WINDOW(dialog));
}


//  button actions
static void on_staff_check_in_clicked(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog, *content_area, *id_entry;
	GtkWidget *box;

	dialog = gtk_dialog_new_with_buttons("Staff Check-In",
										 GTK_WINDOW(data),
										 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
										 "Check-In",
										 GTK_RESPONSE_ACCEPT,
										 "Cancel",
										 GTK_RESPONSE_CANCEL,
										 NULL);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_append(GTK_BOX(content_area), box);

	GtkWidget *label = gtk_label_new("Enter staff ID:");
	gtk_box_append(GTK_BOX(box), label);

	id_entry = gtk_entry_new();
	gtk_box_append(GTK_BOX(box), id_entry);

	gtk_widget_show(dialog);

	g_signal_connect(dialog, "response", G_CALLBACK(on_staff_check_in_response), id_entry);
}

static void on_staff_check_out_clicked(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog, *content_area, *id_entry;
	GtkWidget *box;

	dialog = gtk_dialog_new_with_buttons("Staff Check-Out",
										 GTK_WINDOW(data),
										 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
										 "Check-Out",
										 GTK_RESPONSE_ACCEPT,
										 "Cancel",
										 GTK_RESPONSE_CANCEL,
										 NULL);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_append(GTK_BOX(content_area), box);

	GtkWidget *label = gtk_label_new("Enter staff ID:");
	gtk_box_append(GTK_BOX(box), label);

	id_entry = gtk_entry_new();
	gtk_box_append(GTK_BOX(box), id_entry);

	gtk_widget_show(dialog);

	g_signal_connect(dialog, "response", G_CALLBACK(on_staff_check_in_response), id_entry);
}

static void on_enroll_staff_clicked(GtkWidget *widget, gpointer data){
	GtkWidget *dialog, *content_area, *name_entry, *box;


	dialog = gtk_dialog_new_with_buttons("Enroll New Staff",
										  GTK_WINDOW(data),
										  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
										  "Enroll",
										  GTK_RESPONSE_ACCEPT,
										  "Cancel",
										  GTK_RESPONSE_CANCEL,
										  NULL);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_append(GTK_BOX(content_area), box);

	GtkWidget *label = gtk_label_new("Enter staff name:");

	gtk_box_append(GTK_BOX(box), label);


	name_entry = gtk_entry_new();
	gtk_box_append(GTK_BOX(box), name_entry);


	gtk_widget_show(dialog);

	g_signal_connect(dialog, "response", G_CALLBACK(on_enroll_staff_response), name_entry);
}

static void on_visitor_log_clicked(GtkWidget *widgt, gpointer data){
	GtkWidget *dialog, *content_area, *name_entry, *box;

	dialog = gtk_dialog_new_with_buttons("Visitor Check-In",
										GTK_WINDOW(data),
										GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
										"Check-In",
										GTK_RESPONSE_ACCEPT,
										"Cancel",
										GTK_RESPONSE_CANCEL, NULL);

	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_append(GTK_BOX(content_area), box);

	GtkWidget *label = gtk_label_new("Enter Visitor name:");

	gtk_box_append(GTK_BOX(box), label);


	name_entry = gtk_entry_new();
	gtk_box_append(GTK_BOX(box), name_entry);


	gtk_widget_show(dialog);

	g_signal_connect(dialog, "response", G_CALLBACK(on_visitor_check_in_response), name_entry);
}

//  Main Window

GtkWidget *create_main_window(void)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;

    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Register Log");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_close), NULL);

    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);

    button = gtk_button_new_with_label("Staff Check-In");
    g_signal_connect(button, "clicked", G_CALLBACK(on_staff_check_in_clicked), window);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

    button = gtk_button_new_with_label("Staff Check-Out");
    g_signal_connect(button, "clicked", G_CALLBACK(on_staff_check_out_clicked), window);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

    button = gtk_button_new_with_label("Visitor Log");
    g_signal_connect(button, "clicked", G_CALLBACK(on_visitor_log_clicked), window);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);

    button = gtk_button_new_with_label("Enroll New Staff");
    g_signal_connect(button, "clicked", G_CALLBACK(on_enroll_staff_clicked), window);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 2, 1);

    return window;
}