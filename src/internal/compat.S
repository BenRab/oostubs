/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                        C O M P A T                                            *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* Define the target section to be code */
.text

/* Define the exported symbols */
.global __pure_virtual, __cxa_pure_virtual, __builtin_delete, _ZdlPv, __cxa_atexit, _alloca, __w32_sharedptr_initialize, __dso_handle, __stack_chk_fail

/* Implement the symbols as empty functions*/

__pure_virtual:
__cxa_pure_virtual:
__builtin_delete:
_ZdlPv:
__cxa_atexit:
_alloca:
__w32_sharedptr_initialize:
__stack_chk_fail:
	ret

__dso_handle:
    .long 0
