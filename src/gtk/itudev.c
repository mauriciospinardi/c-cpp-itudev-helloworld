/**
 * @file itudev.c
 * @author Maurício Spinardi (mauricio.spinardi@setis.com.br)
 * @platform cygwin64
 * @brief Biblioteca ItuDevelopers para Cygwin64 via GTK.
 * @date 2020-07-20
 * 
 */

#include "itudev.h" /* Definições privadas */

#include <semaphore.h>
#include <stdarg.h>
#include <stdlib.h>

#include <gtk/gtkx.h>

/*********************/
/* Vairáveis globais */
/*********************/

static GtkApplication *application;

static GtkWidget *window;

static int status = -1; /* -1 se não inicializada */

/*************************/
/* Protótipos de funções */
/*************************/

extern int
main(int argc, char *argv[]);

static void
activate(GtkApplication *application, gpointer user_data);

static gboolean
button_press_callback(GtkWidget *event_box, GdkEventButton *event, gpointer data);

static GtkWidget *
create_image(char *file);

/**************************/
/* Funções externalizadas */
/**************************/

/**
 * @brief @ref itudev.h
 * 
 * @return int -1 para erros; 0 para sucesso
 */
extern int LIB_PUBLIC
itudev_end(void)
{
    if (application && !status)
    {
        g_object_unref(application);

        application = NULL;
    }

    ITUDEV_TRACE("application [%lu]", (long unsigned int) application);

    return 0;
}

/**
 * @brief @ref itudev.h
 * 
 * @return int -1 para erros; 0 para sucesso
 */
extern int LIB_PUBLIC
itudev_image_flush(char *file)
{
    GtkWidget *event_box;

    if (!file)
    {
        return -1;
    }

    event_box = create_image(file);

    ITUDEV_TRACE("create_image() [%lu]", (long unsigned int) event_box);

    gtk_container_add(GTK_CONTAINER(window), event_box);

    gtk_window_set_title(GTK_WINDOW(window), "Itu Developers");

    gtk_window_set_default_size(GTK_WINDOW(window), 320, 480);

    gtk_widget_show_all(window);

    return (!event_box) ? -1 : 0;
}

/**
 * @brief @ref itudev.h
 *
 * @return int -1 para erros; 0 para sucesso
 */
extern int LIB_PUBLIC
itudev_start(void)
{
    if (status > 0)
    {
        return 0;
    }

    application = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);

    ITUDEV_TRACE("gtk_application_new() [%lu]", (long unsigned int) application);

    status = (!application) ? -1 : 1;

    if (status < 0)
    {
        return -1;
    }

    g_signal_connect(application, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(application), 0, NULL);

    ITUDEV_TRACE("g_application_run() [%d]", status);

    if (status)
    {
        return -1;
    }

    status = itudev_end();

    ITUDEV_TRACE("itudev_end() [%d] (platform exiting point...)", status);

    exit(EXIT_SUCCESS);
}

/**
 * @brief @ref itudev.h
 * 
 * @param format [in] autodescritivo
 * @param ... [in] número variável de argumentos
 */
extern void LIB_PUBLIC
itudev_log(const char *date, const char *time, const char *file, const int line, const char *function, const char *format, ...)
{
    char log[256];
    int ret;
    va_list args;

    static sem_t *semaphore = NULL;

    if (!format)
    {
        return;
    }

    if (!semaphore) /* Para pensar: thread safe? */
    {
        semaphore = (sem_t *) malloc(sizeof(sem_t));

        if (!semaphore)
        {
            return;
        }

        sem_init(semaphore, 0, 1);
    }

    sem_wait(semaphore);

    va_start(args, format);

    g_print("\r\n%11.11s %8.8s %.25s #%.4d %s::", date, time, file, line, function);

    ret = vsnprintf(log, sizeof(log), format, args);

    if (ret)
    {
        g_print("%s", log);
    }

    va_end(args);

    sem_post(semaphore);
}

/******************/
/* Funções locais */
/******************/

/**
 * @brief Cria nova janela e retoma o ponto de entrada da aplicação.
 * 
 * @param application [in] Identificador da aplicação
 * @param user_data [in] Dados privados
 */
static void
activate(GtkApplication *application, gpointer user_data)
{
    (void) user_data;

    window = gtk_application_window_new(application);

    ITUDEV_TRACE("gtk_application_window_new() [%lu]", (long unsigned int) window);

    main(0, NULL);
}

/**
 * @brief Função de retorno para monitoramento de eventos.
 * 
 * @param event_box [in] GtkWidget
 * @param event [in] Evento
 * @param data [in] Dados privados
 * @return gboolean TRUE se o evento foi tratado; FALSE, caso contrário.
 */
static gboolean
button_press_callback(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
    (void) event_box;
    (void) data;

    ITUDEV_TRACE("event->x [%f]", event->x);
    ITUDEV_TRACE("event->y [%f]", event->y);

    return TRUE;
}

/**
 * @brief Carrega e envia um arquivo de imagem para o motor de renderização.
 *
 * @return GtkWidget* 
 */
static GtkWidget *
create_image(char *file)
{
    GtkWidget *event_box;
    GtkWidget *image;

    image = gtk_image_new_from_file(file);

    ITUDEV_TRACE("gtk_image_new_from_file() [%lu]", (long unsigned int) image);

    event_box = gtk_event_box_new();

    ITUDEV_TRACE("gtk_event_box_new() [%lu]", (long unsigned int) event_box);

    gtk_container_add(GTK_CONTAINER(event_box), image);

    g_signal_connect(G_OBJECT(event_box), "button_press_event", G_CALLBACK(button_press_callback), image);

    return event_box;
}
