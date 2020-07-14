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

/**********/
/* Macros */
/**********/

#ifdef _DEBUG_
#define ITUDEV_TRACE(...) g_print("\r\n%19.19s #%4.4d %s::", __FILE__, __LINE__, __FUNCTION__); g_print(__VA_ARGS__)
#else
#define ITUDEV_TRACE(...) /* NULL */
#endif /* #ifdef _DEBUG_ */

/*********************/
/* Vairáveis globais */
/*********************/

static GtkApplication *application;

static GtkWidget *window;

static int status = -1; /* Não inicializada! */

/*************************/
/* Protótipos de funções */
/*************************/

static int
itudev_end(void);

static int
itudev_helloworld(void);

static int
itudev_start(void);

static void
activate(GtkApplication *application, gpointer user_data);

static gboolean
button_press_callback(GtkWidget *event_box, GdkEventButton *event, gpointer data);

static GtkWidget *
create_image(void);

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
int main(int argc, char *argv[])    /* Para pensar:
                                     * 
                                     * - Será main(...) o melhor ponto de
                                     * entrada para a aplicação?
                                     *
                                     */
{
    int ret;

    (void) argc;
    (void) argv;

    ret = itudev_start();

    ITUDEV_TRACE("itudev_start() [%d]", ret);

    if (ret)
    {
        exit(EXIT_FAILURE);
    }

    ret = itudev_helloworld();  /* Para pensar:
                                 *
                                 * - itudev_file_load(...);
                                 * - itudev_file_size(...);
                                 * - itudev_image_draw(...);
                                 * - itudev_image_flush(...);
                                 * 
                                 * - itudev_...
                                 * 
                                 */

    ITUDEV_TRACE("itudev_helloworld() [%d]", ret);

    if (ret)
    {
        exit(EXIT_FAILURE);
    }

    ret = itudev_end();

    ITUDEV_TRACE("itudev_end() [%d]", ret);

    return (ret) ? EXIT_FAILURE : EXIT_SUCCESS;
}

/******************/
/* Funções locais */
/******************/

/**
 * @brief Libera recursos consumidos na execução de itudev_start().
 * 
 * @return int -1 para erros; 0 para sucesso
 */
static int
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
 * @brief Exibe "Hello, World!" na janela principal da aplicação.
 * 
 * @return int -1 para erros; 0 para sucesso
 */
static int
itudev_helloworld(void)
{
    GtkWidget *event_box;

    event_box = create_image();

    ITUDEV_TRACE("create_image() [%lu]", (long unsigned int) event_box);

    gtk_container_add(GTK_CONTAINER(window), event_box);

    gtk_window_set_title(GTK_WINDOW(window), "Itu Developers");

    gtk_window_set_default_size(GTK_WINDOW(window), 320, 480);

    gtk_widget_show_all(window);

    return (!event_box) ? -1 : 0;
}

/**
 * @brief Inicializa o motor de renderização da plataforma.
 *
 * @return int -1 para erros; 0 para sucesso
 */
static int
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
create_image(void)
{
    GtkWidget *event_box;
    GtkWidget *image;

    image = gtk_image_new_from_file("misc/200713153459.png");

    ITUDEV_TRACE("gtk_image_new_from_file() [%lu]", (long unsigned int) image);

    event_box = gtk_event_box_new();

    ITUDEV_TRACE("gtk_event_box_new() [%lu]", (long unsigned int) event_box);

    gtk_container_add(GTK_CONTAINER(event_box), image);

    g_signal_connect(G_OBJECT(event_box), "button_press_event", G_CALLBACK(button_press_callback), image);

    return event_box;
}
