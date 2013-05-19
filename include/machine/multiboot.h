/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                     M U L T I B O O T                                         *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __multiboot_header__
#define __multiboot_header__

/* MACROS */

/** \brief 
 * \~german spezielle ("magische") Zahl, um den Multiboot-Kopf zu identifizieren
 * \~english Magic number to identify multiboot header
 **/
#define MULTIBOOT_HEADER_MAGIC          0x1BADB002

#ifdef __ELF__
  /** \brief 
   * \~german Flag für ELF-Dateien zur Angabe bei Multiboot 
   * \~english Flag definition for ELF executables
   **/
  # define MULTIBOOT_HEADER_FLAGS         0x00000003
  
#else
  /** \brief 
   * \~german Flag für alles andere als ELF-Dateien (PE-Datei, a.out, ...) zur Angabe bei Multiboot 
   * \~english Flag definition for a.out executables. 
   **/
  # define MULTIBOOT_HEADER_FLAGS         0x00010003
  
#endif //__ELF__

/** \brief 
 * \~german spezielle ("magische") Zahl, 
 *          die durch einen Multiboot-Boot-Loader dem Kernel übergeben wird
 * \~english Magic number passed by a Multiboot-compliant boot loader. 
 **/
#define MULTIBOOT_BOOTLOADER_MAGIC      0x2BADB002

/* Do not include in assembly files */
#ifndef ASM
  /* INCLUDES */
  #include <stdint.h>
  
  /* TYPES */
  struct Multiboot_Info;
  
#endif // ASM

#endif // __multiboot_header__
