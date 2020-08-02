/**
 * @file itudev.h
 * @author Maurício Spinardi (mauricio.spinardi@setis.com.br)
 * @platform N/A
 * @brief Definição de espaço de nomes, classe e/ou interface.
 * @date 2020-07-20
 * 
 */

#ifndef _ITUDEV_H_INCLUDED_
#define _ITUDEV_H_INCLUDED_

/**********/
/* Macros */
/**********/

#ifdef _DEBUG_
#define ITUDEV_TRACE(...) itudev_log(__DATE__, __TIME__, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#else
#define ITUDEV_TRACE(...) /* NULL */
#endif /* #ifdef _DEBUG_ */

/**************************/
/* Funções externalizadas */
/**************************/

/**
 * @description Libera recursos consumidos pela biblioteca.
 *
 * @return int -1 para erros; 0 para sucesso
 */
extern int
itudev_end(void);

/**
 * @description Exibe uma imagem na janela principal da aplicação.
 * 
 * @return int -1 para erros; 0 para sucesso
 */
extern int
itudev_image_flush(char *file);

/**
 * @description Inicializa a biblioteca.
 *
 * @return int -1 para erros; 0 para sucesso
 */
extern int
itudev_start(void);

/**
 * @description Canal de depuração da aplicação.
 * 
 * @param[in] format autodescritivo
 * @param[in] ... número variável de argumentos
 */
extern void
itudev_log(const char *date, const char *time, const char *file, const int line, const char *function, const char *format, ...);

#endif /* #ifndef _ITUDEV_H_INCLUDED_ */
