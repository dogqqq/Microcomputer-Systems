! print all prime number < 100
! Creation Date: 2020/09/25
! Author: dogQ

.equ num, 100
.section .rodata
.align 2
.fmt_dicimal:
	.string "%d "

.fmt_new_line:
	.string "\n"

.text
.align 2
.global main

main:
.Init:
	movi	$r6, 2			!factor
	movi	$r7, 2			!check number
	j 		.Print_num

.Check_bound:
	subri	$r4, $r7, num
	blez	$r4, .Out			!check number >= 100

.Check_prime:
	sub 	$r4, $r6, $r7
	beqz	$r4, .Print_num
	bgez	$r4, .Add_check_num		!factor >= check number
	divr	$r3, $r4, $r7, $r6
	beqz 	$r4, .Add_check_num
	addi	$r6, $r6, #1			!factor += 1
	j 		.Check_prime

.Print_num:
	movi	$r6, 2					!factor = 2
	la		$r0, .fmt_dicimal
	addi	$r1, $r7, 0
	push	$lp
	bal		printf
	pop		$lp

.Add_check_num:
	addi	$r7, $r7, #1
	j 		.Check_bound

.Out:
	ret
