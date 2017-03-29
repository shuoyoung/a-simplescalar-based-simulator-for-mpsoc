        .globl MTA_write
	.ent MTA_write
MTA_write:
	li $2,5
        syscall
        nop
        jr $31
        nop
	.end MTA_write

    .globl MTA_write_EM_directly
    .ent MTA_write_EM_directly
MTA_write_EM_directly:
    li $2,9
    syscall
    nop
    jr $31
    nop
    .end MTA_write_EM_directly

	.globl MTA_read_EM_directly
    .ent MTA_read_EM_directly
MTA_read_EM_directly:
    li $2,10
    syscall
    nop
    jr $31
    nop
    .end MTA_read_EM_directly

	.globl  MTA_read
	.ent    MTA_read
MTA_read:
	li $2, 6
	syscall 
	nop
	jr $31
	nop
	.end MTA_read

	.globl  MTA_getthreadID
	.ent    MTA_getthreadID
MTA_getthreadID:
	li $2, 500
	syscall 
	nop
	jr $31
	nop
	.end MTA_getthreadID

	.globl  MTA_getsim_cycle
	.ent    MTA_getsim_cycle
MTA_getsim_cycle:
	li $2, 7
	syscall 
	nop
	jr $31
	nop
	.end MTA_getsim_cycle

	.globl  MTA_flush_EM
	.ent    MTA_flush_EM
MTA_flush_EM:
	li $2, 8
	syscall 
	nop
	jr $31
	nop
	.end MTA_flush_EM

	.globl  MTA_acquiesce	
	.ent    MTA_acquiesce
MTA_acquiesce:
	li $2, 534
	syscall 
	nop
	jr $31
	nop
	.end MTA_acquiesce

    .globl  MTA_Bar_Stats
    .ent    MTA_Bar_Stats
MTA_Bar_Stats:
    li $2, 531
    syscall 
    nop
    jr $31
    nop
    .end MTA_Bar_Stats

    .globl  MTA_Bar_Instr
    .ent    MTA_Bar_Instr
MTA_Bar_Instr:
    li $2, 533
    syscall 
    nop
    jr $31
    nop
    .end MTA_Bar_Instr
