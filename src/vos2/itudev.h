/**
 * @file itudev.h
 * @author Maurício Spinardi (mauricio.spinardi@setis.com.br)
 * @platform Verifone Engage
 * @brief Definição de espaço de nomes, classe e/ou interface.
 * @date 2020-07-20
 * 
 */

#ifndef _ITUDEV_H_INCLUDED_

extern "C" /* Ref. "name mangling" */
{
#include "itudev/itudev.h" /* Definições públicas */
}

/**********/
/* Macros */
/**********/

#define LIB_PRIVATE __attribute__((visibility("hidden")))

#define LIB_PROTECTED __attribute__((visibility("protected")))

#define LIB_PUBLIC __attribute__((visibility("default")))

#endif /* #ifndef _ITUDEV_H_INCLUDED_ */
