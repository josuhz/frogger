.section .text
.global contieneLilypad

contieneLilypad:
	@en r0 esta filarana, r1 columnarana
	@en r2 filalilypad, r3 columnallilypad, r4 ancho en el stack
	LDR r4, [sp]
	CMP r0, r2
	beq siguiente1
	MOV r0, #0
	bx lr
	
siguiente1:
	CMP r1, r3
	bge siguiente2
	MOV r0, #0
	bx lr

siguiente2:
	ADD r3, r3, r4
	CMP r1, r3
	blo final
	MOV r0, #0
	bx lr
final:
	MOV r0, #1
	bx lr
