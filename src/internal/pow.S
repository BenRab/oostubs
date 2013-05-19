/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                         P O W                                                 *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* Tell (not existing) includes, that this is an assembly file */
#define ASM 1

#ifdef DOXYGEN_SHOULD_IGNORE_THIS
  /** 
   * \~german
   * \brief Diese Funktion berechnet mit Hilfe der <a href="http://wiki.osdev.org/FPU">x86 FPU</a>
   *        die Potenz zweier Zahlen.
   * 
   * 
   * \~english
   * 
   * 
   */
  void _pow(float a, float b, float* c){
    //Assembler-code siehe unten
    //see the assembler code underneath this dummy function for doxygen
  }
  
#else
.text

.global _pow

_pow: 
	push %ebp
	mov %esp, %ebp
	push %ebx
	pushf
	cli
	
	/* Zustand sichern */
	sub $48, %esp
	fstenv (%esp)
	fstpt 28(%esp)
	fstpt 38(%esp)
	sub $8, %esp		/*tmpVal*/
	
	/* y*log2(x) */
	flds 12(%ebp)
	flds 8(%ebp)
	fyl2x
	
	/* runden auf "nahe an null" umstellen */
	fstcw 6(%esp)
	fstcw 4(%esp)
	orw $0x0C00, 4(%esp)
	fldcw 4(%esp)
	/* Wert in den bereich [-1,1] bringen*/
	fist (%esp)
	fild (%esp)
	fsubrp		/* ACHTUNG: im Intel-Handbuch ist das fsubp! (siehe link am Ende) */
	/* runden zurueckstellen */
	fldcw 6(%esp)
	
	/* (2^{x} - 1) + 1 */
	f2xm1
	fld1
	faddp
	
	/* Ergebnis korrekt skalieren */
	fild (%esp)
	fxch
	fscale
	
	movl 16(%ebp), %ebx
	fstps (%ebx)
	
	/* Zustand wieder herstellen */
	add $8, %esp
	fldt 38(%esp)
	fldt 28(%esp)
	fldenv (%esp)
	add $48, %esp
		
	popf
	pop %ebx
	pop %ebp
	
	ret

.data
myTmpVal:
	.float 123.45
#endif

/*
Wichtige Hinweise:
GAS nutzt standardmaessig die AT&T-Syntax und an einigen Stellen auch deren mnemo-codes.
Dies ist z.B. u8nter 9.13.5 der binutil docs beschrieben
(http://sourceware.org/binutils/docs-2.22/as/i386_002dMnemonics.html).
Zitat:
<<
as supports assembly using Intel mnemonic. .intel_mnemonic selects Intel mnemonic with Intel 
syntax, and .att_mnemonic switches back to the usual AT&T mnemonic with AT&T syntax for 
compatibility with the output of gcc. Several x87 instructions, `fadd', `fdiv', `fdivp', `fdivr', 
`fdivrp', `fmul', `fsub', `fsubp', `fsubr' and `fsubrp', are implemented in AT&T System V/386 
assembler with different mnemonics from those in Intel IA32 specification. gcc generates those 
instructions with AT&T mnemonic. 
>>
*/
