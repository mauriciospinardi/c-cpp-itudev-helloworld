/**
 * @file main.c
 * @author Maurício Spinardi (mauricio.spinardi@setis.com.br)
 * @platform cygwin64
 * @brief Ponto de entrada.
 * @date 2020-07-13
 * 
 */

#include "itudev/itudev.h"

#include <stdio.h>
#include <stdlib.h>

/**************/
/* Constantes */
/**************/

static const char hello_world[] = "misc/200713153459.png";

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
int main(int argc, char *argv[]) /* Para pensar: será main(...) um bom ponto
                                  * de entrada multiplataforma? */
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

    ret = itudev_image_flush((char *) hello_world);

    ITUDEV_TRACE("itudev_image_flush() [%d]", ret);

    if (ret)
    {
        exit(EXIT_FAILURE);
    }

    ret = itudev_end();

    ITUDEV_TRACE("itudev_end() [%d]", ret);

    return (ret) ? EXIT_FAILURE : EXIT_SUCCESS;
}
