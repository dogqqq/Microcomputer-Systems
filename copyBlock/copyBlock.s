! array operation example
.equ num, 20
.section .rodata
.align 2
.fmt_str1:
	.string "%d "

.fmt_str2:
	.string "\n"

.fmt_str3:
	.string "src: "

.fmt_str4:
	.string "dst: "

	.text
	.global memcpy
	.global main

main:
memcpy:
	la		$r0, .fmt_str3		!'src:'
	jal		printf

	la		$r6, src
	li		$r7, num			!r7 = 20
m_src_word_print:
	la		$r0, .fmt_str1
	lwi.bi	$r1, [$r6], (#1 << #2)
	jal		printf
	addi	$r7, $r7, #-1		!r7--
	bnez	$r7, m_src_word_print

	la		$r0, .fmt_str2
	jal		printf

	la		$r1, src
	la		$r0, dst
	li		$r2, num

m_word_copy:
	lmw.bim	$r5, [$r1], $r8, 0
	smw.bim	$r5, [$r0], $r8, 0
	addi	$r2, $r2, #-4		!arr position
	bnez	$r2, m_word_copy

	la		$r0, .fmt_str4
	jal		printf

	la		$r6, dst
	li		$r7, num

m_dst_word_print:
	la		$r0, .fmt_str1
	lwi.bi	$r1, [$r6], (#1 << #2)
	jal		printf
	addi	$r7, $r7, #-1
	bnez	$r7, m_dst_word_print

	la		$r0, .fmt_str2
	jal		printf

	ret

	.data
	.align 2

src:	.word	1,	2,	3,	4,	5,	6,	7,	8,	9,	10
		.word	11,	12,	13,	14,	15,	16,	17,	18,	19,	20

dst:
		.skip	num*4
		.end
