/**
 * @file itudev.h
 * @author Maur�cio Spinardi (mauricio.spinardi@setis.com.br)
 * @platform cygwin64
 * @brief Defini��o de espa�o de nomes, classe e/ou interface.
 * @date 2020-07-20
 * 
 */

#ifndef _ITUDEV_H_INCLUDED_

#include "itudev/itudev.h" /* Defini��es p�blicas */

/**********/
/* Macros */
/**********/

#define LIB_PRIVATE __attribute__((visibility("hidden")))

#define LIB_PROTECTED __attribute__((visibility("protected")))

#define LIB_PUBLIC __attribute__((visibility("default")))

#endif /* #ifndef _ITUDEV_H_INCLUDED_ */
