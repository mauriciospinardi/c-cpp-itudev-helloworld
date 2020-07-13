/**
 * @file main.cpp
 * @author Maurício Spinardi (mauricio.spinardi@setis.com.br)
 * @platform cygwin64
 * @brief Ponto de entrada.
 * @date 2020-07-13
 * 
 */

#include <iostream>

#include <gtk/gtkx.h>

/**
 * @brief 
 * 
 * @param application 
 * @param user_data 
 */
static void
activate(GtkApplication *application, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *label;

    (void) user_data;

    window = gtk_application_window_new(application);

    label = gtk_label_new("Hello GNOME!");

    gtk_container_add(GTK_CONTAINER(window), label);

    gtk_window_set_title(GTK_WINDOW(window), "Welcome to GNOME");

    gtk_window_set_default_size(GTK_WINDOW(window), 320, 480);

    gtk_widget_show_all(window);
}

/**
 * @brief 
 * 
 * @param event_box 
 * @param event 
 * @param data 
 * @return gboolean 
 */
// static gboolean
// button_press_callback(GtkWidget *event_box, GdkEventButton *event, gpointer data)
// {
//     (void) event_box;
//     (void) data;

//     g_print("Event box clicked at coordinates %f,%f\n", event->x, event->y);

//     return TRUE;
// }

/**
 * @brief 
 * 
 * @return GtkWidget* 
 */
// static GtkWidget*
// create_image(void)
// {
//     GtkWidget *event_box;
//     GtkWidget *image;

//     image = gtk_image_new_from_file("myfile.png");

//     event_box = gtk_event_box_new();

//     gtk_container_add (GTK_CONTAINER(event_box), image);

//     g_signal_connect(G_OBJECT(event_box), "button_press_event", G_CALLBACK(button_press_callback), image);

//     return image;
// }

/**************************/
/* Funções externalizadas */
/**************************/

/**
 * @brief Ponto de entrada.
 * 
 * @param [in] argc contador de argumentos
 * @param [in] argv vetor de argumentos
 * 
 * @return EXIT_xxx
 * 
 */
int main(int argc, char *argv[])
{
    GtkApplication *application;
    int status;

    application = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);

    g_signal_connect(application, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(application), argc, argv);

    g_object_unref(application);

    return status;
}
