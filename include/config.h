/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                        C O N F I G                                            *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* Deactivate include guard for assembler files */
#ifndef __config_header__
#define __config_header__

/* MACROS */

/**\brief 
 * \~german  Größe für den Stack, die der Bootcode anlegen und nutzen soll
 * \~english Size of the stack created by the assembly bootup code 
 **/
#define BOOT_STACK_SIZE 4096

/** \brief 
 * \~german  Attribut, welches standardmäßig bei CGA-Text verwendet werden soll
 * \~english Default attribute for text 
 **/
#define DEFAULT_SCREEN_ATTRIB 7

/** \brief 
 * \~german  Größe des Zeichenpuffers
 * \~english Size of string buffer 
 **/
#define BUFFERSIZE 128

#endif
