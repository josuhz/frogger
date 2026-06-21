.section .text
.global contiene

contiene:
	@en r0 filarana, r1 columnarana
	@en r2 fila, r3 columna
	PUSH {lr}
	LDR r12, [SP, #4]
	CMP r0, r2 @r12 ancho que estaba en el stack
	beq siguiente1
	MOV r0, #0
	POP {pc}
	
siguiente1:
	CMP r1, r3
	bge siguiente2
	MOV r0, #0
	POP {pc}

siguiente2:
	ADD r3, r3, r12
	CMP r1, r3
	blt final
	MOV r0, #0
	POP {pc}
final:
	MOV r0, #1
	POP {pc}
