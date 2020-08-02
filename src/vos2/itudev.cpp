/**
 * @file itudev.cpp
 * @author Maurício Spinardi (mauricio.spinardi@setis.com.br)
 * @platform Verifone Engage
 * @brief Biblioteca ItuDevelopers para Verifone Engage.
 * @date 2020-08-02
 * 
 */

#include "itudev.h" /* Definições privadas */

#include <html/gui.h>
#include <html/gui_error.h>
#include <html/jsobject.h>
#include <html/jsproc.h>
#include <html/scriptproc.h>
#include <log/liblog2.h>
#include <log/syslogcmd.h>
#include <semaphore.h>
#include <sysinfo/sysinfo.h>
#include <sysinfo/vfisyspm.h>
#include <unistd.h>

#include <stdarg.h>
#include <stdlib.h>
#include <string>

/*********************/
/* Vairáveis globais */
/*********************/

static LibLogHandle log;

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
    LOGAPI_DEINIT(log);

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
    std::string path;
    vfigui::UIDrawing draw;

    draw.clear(0xFFFFFF);

    path = "/home/usr1/www/" + std::string(file);

    ITUDEV_TRACE("path [%s]", path.c_str());

    draw.image(path.c_str(), 0, 0);

    if (vfigui::uiDraw(vfigui::UI_REGION_DEFAULT, draw))
    {
        return -1;
    }

    ITUDEV_TRACE("vfigui::uiDraw() [OK]");

    usleep(10000000); /* Congela a tela por 10 seg. para garantir o efeito
                       * desejado para "Olá, Mundo!" */

    /* Para pensar: o congelamento acima deveria ser responsabilidade da
     * aplicação ou da plataforma? */

    return 0;
}

/**
 * @brief @ref itudev.h
 *
 * @return int -1 para erros; 0 para sucesso
 */
extern int LIB_PUBLIC
itudev_start(void)
{
    int height, width;
    std::vector<vfigui::UIRegion> region;

    while (true)
    {
        switch (vfisyspm::sys_Init())
        {
        case vfisyspm::SYS_PM_ERR_OK:
        case vfisyspm::SYS_PM_ERR_ALREADY_INIT:
            break;

        default:
            usleep(1000000);
            continue;
        }

        break; /* ADK-SYS [OK] */
    }

    log = LOGAPI_INIT("ITUDEV");

    ITUDEV_TRACE("vfisyspm::sys_Init() [OK]");

    vfisysinfo::sysGetPropertyInt(vfisysinfo::SYS_PROP_DISP_HEIGHT, &height);

    vfisysinfo::sysGetPropertyInt(vfisysinfo::SYS_PROP_DISP_WIDTH, &width);

    region.push_back({ 0, 0, 0, width, height, 0 });

    if (vfigui::uiLayout(region))
    {
        return -1;
    }

    ITUDEV_TRACE("vfigui::uiLayout() [OK]");

    if (vfigui::uiCanvas(vfigui::UI_REGION_DEFAULT, (vfigui::uiEventCallback) NULL, NULL) < 0)
    {
        return -1;
    }

    ITUDEV_TRACE("vfigui::uiCanvas() [OK]");

    return 0;
}

/**
 * @brief @ref itudev.h
 * 
 * @param[in] format autodescritivo
 * @param[in] ... número variável de argumentos
 */
extern void LIB_PUBLIC
itudev_log(const char *date, const char *time, const char *file, const int line, const char *function, const char *format, ...)
{
    char data[256];
    int ret;
    std::string trace;
    va_list args;

    static sem_t *semaphore = NULL;

    (void) date;
    (void) time;

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

    sprintf(data, "\r\n%.25s #%.4d %s::", file, line, function);

    trace = data;

    ret = vsnprintf(data, sizeof(data), format, args);

    if (ret)
    {
        trace += data;

        LOGF_TRACE(log, "%s", trace.c_str());
    }

    va_end(args);

    sem_post(semaphore);
}
