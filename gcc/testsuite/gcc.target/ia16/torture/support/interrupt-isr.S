/* Assembly language interrupt service routine for __attribute__
   ((interrupt)) test cases.  */

	.arch	i8086, jumps
	.code16

	.text

	.global	isr
isr:
	iret
