/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                        B O O T                                                *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* Tell includes, that this is an assembly file */
#define ASM 1
#include <machine/multiboot.h>
#include <config.h>


.text					          /* The fallowing is code */

	
.globl  entry, gotoAnalyse	/* Define the entry point for the bootloader to be exported */


.macro	wrapperGen			/* Assembler macro to create interrupt wrapper  */
	.ifeq \@				      /* \@ is an automatically incremented variable, */
		INT_WRAPPER_START:	/* it is incremented, everytime the macro		*/
	.endif					      /* is expanded. 								*/

	int_wrapper_\@:
	push %eax
	mov	$\@, %eax
	jmp	callGuardian
	
	.ifeq \@
		INT_WRAPPER_END:
	.endif
.endm

.align  4					      /* The Multiboot header must be aligned to 32bit */
     
multiboot_header:
    .long   MULTIBOOT_HEADER_MAGIC
    .long   MULTIBOOT_HEADER_FLAGS
    .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
#ifndef __ELF__
    .long   multiboot_header
    .long   _start
    .long   _edata
    .long   _end
    .long   entry
#endif
     
entry:						      /* Entry point of the system */
	 cli

gdtSetup:					      /* Initialize the GDT */
	 lgdt GDTR				    /* Load the static GDT */

	 mov 	$0x10, %cx		  /* Setting the segment selectors*/
	 mov	%cx, %ss		    /* stack is data*/
	 mov	%cx, %ds		
	 mov	%cx, %es
	 mov	%cx, %gs
	 mov	%cx, %fs
   ljmpl $0x08, $stackSetup   /* set cs register to 0x08 */

stackSetup:					    /*Creating a stack*/
	 mov	$(stack + BOOT_STACK_SIZE), %esp
	
multibootSetup:				  /* Passing multiboot arguments to kernel */
	 pushl	%ebx			
	 pushl	%eax

idtSetup:
	mov	$initialIDT, %eax	/* Load the base address of the IDT template */
	mov	$256, %dx			    /* There are 256 possible interrupts */
	movl	$(int_wrapper_0-INT_WRAPPER_END+INT_WRAPPER_START), %ebx	/* Load base address of the wrapper function */

.loop:
	add  $(INT_WRAPPER_END-INT_WRAPPER_START), %ebx					/* Load the address of the current wrapper function */
	movl %ebx, %ecx
	mov	 %cx, (%eax)			/* Copy the lower bytes of the address to the IDT */
	shr	 $16, %ecx
	mov	 %cx,	6(%eax)			/* Copy the upper bytes of the address to the IDT */
	add	 $8,	%eax
	dec	 %dx
	jnz	 .loop

	lidt IDTR							/* Load the IDT */

disableNMI:					    /* Disable non-maskable interrupts */
	mov	$0x80, %al			  /* NMI verbieten */
	out	%al, $0x70

initFPU:										/* setup FPU for 486 and newer */
  pushl %eax
	mov  %CR0, %eax
	and  $(-1-0x04), %eax			/* clear CR0.EM Bit */
	or   $0x20, %eax					/*   set CR0.NE Bit */
	mov  %eax, %CR0
  popl %eax
	finit											/* initialize floating point */
  fldcw fpucw_37E						/* enable invalid opcode exception */
	ffree %ST(0)
	ffree %ST(1)
	ffree %ST(2)
	ffree %ST(3)
	ffree %ST(4)
	ffree %ST(5)
	ffree %ST(6)
	ffree %ST(7)

setupObj:					      /* Call the constructors of global objects */
	call constructObjects
	/*ljmpl $0x04, $callKernel*/ /* only test code: generate GP */
	/*int $2*/				    /* only test code: generate pseudo Interrupt 2, just normal interrupt, no exception generation */

callKernel:					    /* Call the C/C++ main function of the operating system */
	call kernel

destroyObj:					    /* Call the destructors of global objects */
	call destructObjects

leaveKernel:				    /* The operating system ended, halt the CPU */
	cli
.halt:	hlt
		jmp .halt



intWrappers:				    /* Create the interrupt wrappers */
	.rept 256
		wrapperGen
	.endr

callGuardian:				    /* Unified interrupt handling routine */
	cld						        /* expected by gcc */
	
	push %ecx				      /* save volatile registers */
	push %edx
	
	and  $0xFF, %eax 		  /* the interrupt wrapper only provides 8bit */
	cmp  $0x20, %eax
	jb callEHandle
	
	push %eax						  /* push the argument of the C/C++ interrupt handler */
	call guardian			    /* call the interrupt handler */
	pop %eax				      /* cleanup */
	
endGuardian:
	pop %edx				      /* retrieve saved registers */
	pop %ecx
	pop %eax							/* was pushed in wrapper */
	
	iret									/* leave interrupt */

callEHandle:
	/* identify reserved exceptions */
	cmp $0x01, %ax			
	je callExcRHandle
	cmp $0x0F, %ax
	je callExcRHandle
	cmp $0x09, %ax
	je callExcRHandle
	cmp $0x13, %ax
	ja callExcRHandle
	
	/* identify exceptions with no error code */
	cmp $0x07, %ax
	jb callExcNHandle
	cmp $0x10, %ax
	je callExcNHandle
	cmp $0x11, %ax
	ja callExcNHandle
	
	/* otherwise it should be a exception with error code */
	jmp callExcEHandle
	

callExcNHandle:					/* handle exception interrupt with no error code */
	push %ebp
	mov %esp,%ebp
	
	push 20(%ebp)
	push 24(%ebp)
	push 16(%ebp)
	push %eax
	
	cmp $0x00, %ax
	je extraCEH
	
	call handleException
	
endCEH:									/* clean up */
	add 16,%esp
	pop %ebp
	jmp endGuardian				/* and go to clean up of guardian */

extraCEH:
	pushl endCEH
	push %esp
	push %eax
	call analyseException
	pop %eax
	pop %esp
	add $4, %esp
	jmp endCEH

callExcEHandle:					/* handle exception interrupt with error code */
	push %ebp
	mov %esp,%ebp
	
	push 16(%ebp)
	push 24(%ebp)
	push 28(%ebp)
	push 20(%ebp)
	push %eax
	
	call handleExceptionE
	
	add 20,%esp
	pop %ebp
	jmp endGuardian

callExcRHandle:					/* handle reserved exception interrupt */
	push %ax							/* push the argument of the C/C++ interrupt handler */
	call handleExceptionReserved
	pop %ax								/* cleanup */
	
	jmp endGuardian

gotoAnalyse:
  push %ebp
  mov %esp, %ebp
  add $8, %ebp
  push %ebp
	call analyseProcedureStack
	pop %ebp
	pop %ebp
	ret


.bss						        /* the fallowing is uninitialized reserved memory */

	.comm   stack, BOOT_STACK_SIZE 	/* memory for stack */


.data										/* pre-initialized memory */

fpucw_37E:
	.short 0x37E					/* initial value for FPU */

GDTR:										/* The gdt pseudo-register */
	.short	3*8-1 				/* 3 segments, null, code, data */
	.int	initialGDT			/* start of GDT */

IDTR:										/* The idt pseudo-register */
	.short 256*8-1				/* 256 handlers */
	.int   initialIDT			/* start if IDT */

	.align 4

initialGDT:							/* The fixed GDT for the operating system */

nullSegment:						/* Null segment as expected by x86 architecture */
	.short	0
	.short	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0

codeSegment:						/* Code segment, flat memory model, read and execute */
	.short	0xFFFF
	.short	0
	.byte	0
	.byte	0x9A
	.byte	0xCF
	.byte	0

dataSegment:						/* Data segment, flat memory model, read and write */
	.short	0xFFFF
	.short	0
	.byte	0
	.byte	0x92
	.byte	0xCF
	.byte	0


initialIDT:							/* The fixed IDT for the initial protected mode setup */

traps:									/* 32 Trap handler for CPU generated traps(, faults, interr. and aborts) */
	.rept	32
		.short	0
		.short  0x8
		.byte	0
		.byte	0xEF
		.short	0
	.endr

externalInts:						/* 224 interrupt handler for possibly external interrupts */
	.rept	224
		.short	0
		.short  0x8
		.byte	0
		.byte	0xEE
		.short	0
	.endr
