	.file	"avrmain.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.__vector_7,"ax",@progbits
.global	__vector_7
	.type	__vector_7, @function
__vector_7:
.LFB7:
	.file 1 "avrmain.c"
	.loc 1 53 0
	.cfi_startproc
	push r1
.LCFI0:
	.cfi_def_cfa_offset 3
	.cfi_offset 1, -2
	push r0
.LCFI1:
	.cfi_def_cfa_offset 4
	.cfi_offset 0, -3
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
.LCFI2:
	.cfi_def_cfa_offset 5
	.cfi_offset 18, -4
	push r19
.LCFI3:
	.cfi_def_cfa_offset 6
	.cfi_offset 19, -5
	push r20
.LCFI4:
	.cfi_def_cfa_offset 7
	.cfi_offset 20, -6
	push r21
.LCFI5:
	.cfi_def_cfa_offset 8
	.cfi_offset 21, -7
	push r22
.LCFI6:
	.cfi_def_cfa_offset 9
	.cfi_offset 22, -8
	push r24
.LCFI7:
	.cfi_def_cfa_offset 10
	.cfi_offset 24, -9
	push r25
.LCFI8:
	.cfi_def_cfa_offset 11
	.cfi_offset 25, -10
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 10 */
.L__stack_usage = 10
	.loc 1 58 0
	in r20,0x9
	sts portd_temp,r20
	.loc 1 61 0
	lds r20,major_trip_count
	lds r21,major_trip_count+1
	lds r22,portd_temp
	bst r22,3
	clr r18
	bld r18,0
	ldi r19,0
	lsl r20
	rol r21
	or r18,r20
	or r19,r21
	sts major_trip_count+1,r19
	sts major_trip_count,r18
	.loc 1 62 0
	lds r18,return_trip_count
	lds r19,return_trip_count+1
	lds r20,portd_temp
	bst r20,4
	clr r24
	bld r24,0
	ldi r25,0
	lsl r18
	rol r19
	or r24,r18
	or r25,r19
	sts return_trip_count+1,r25
	sts return_trip_count,r24
	.loc 1 65 0
	lds r24,major_trip_count
	lds r25,major_trip_count+1
	andi r25,15
	or r24,r25
	brne .L2
	.loc 1 67 0
	lds r24,portd_state
	andi r24,lo8(-9)
	rjmp .L8
.L2:
	.loc 1 70 0
	lds r24,major_trip_count
	lds r25,major_trip_count+1
	andi r25,15
	cpi r24,-1
	sbci r25,15
	brne .L3
	.loc 1 71 0
	lds r24,portd_state
	ori r24,lo8(8)
.L8:
	sts portd_state,r24
.L3:
	.loc 1 75 0
	lds r24,return_trip_count
	lds r25,return_trip_count+1
	andi r25,15
	or r24,r25
	brne .L4
	.loc 1 76 0
	lds r24,portd_state
	andi r24,lo8(-17)
	rjmp .L9
.L4:
	.loc 1 79 0
	lds r24,return_trip_count
	lds r25,return_trip_count+1
	andi r25,15
	cpi r24,-1
	sbci r25,15
	brne .L5
	.loc 1 80 0
	lds r24,portd_state
	ori r24,lo8(16)
.L9:
	sts portd_state,r24
.L5:
	.loc 1 86 0
	lds r24,cpu_state
	cpi r24,lo8(1)
	brne .L6
	.loc 1 87 0
	ldi r24,lo8(1)
	ldi r25,0
	sts tick+1,r25
	sts tick,r24
	.loc 1 88 0
	sts cpu_state,__zero_reg__
	rjmp .L1
.L6:
	.loc 1 91 0
	lds r24,tick
	lds r25,tick+1
	adiw r24,1
	sts tick+1,r25
	sts tick,r24
.L1:
/* epilogue start */
	.loc 1 93 0
	pop r25
	pop r24
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.cfi_endproc
.LFE7:
	.size	__vector_7, .-__vector_7
	.section	.text.__vector_14,"ax",@progbits
.global	__vector_14
	.type	__vector_14, @function
__vector_14:
.LFB8:
	.loc 1 96 0
	.cfi_startproc
	push r1
.LCFI9:
	.cfi_def_cfa_offset 3
	.cfi_offset 1, -2
	push r0
.LCFI10:
	.cfi_def_cfa_offset 4
	.cfi_offset 0, -3
	in r0,__SREG__
	push r0
	clr __zero_reg__
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 3 */
.L__stack_usage = 3
/* epilogue start */
	.loc 1 97 0
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.cfi_endproc
.LFE8:
	.size	__vector_14, .-__vector_14
	.section	.text.__vector_5,"ax",@progbits
.global	__vector_5
	.type	__vector_5, @function
__vector_5:
.LFB9:
	.loc 1 102 0
	.cfi_startproc
	push r1
.LCFI11:
	.cfi_def_cfa_offset 3
	.cfi_offset 1, -2
	push r0
.LCFI12:
	.cfi_def_cfa_offset 4
	.cfi_offset 0, -3
	in r0,__SREG__
	push r0
	clr __zero_reg__
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 3 */
.L__stack_usage = 3
/* epilogue start */
	.loc 1 103 0
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.cfi_endproc
.LFE9:
	.size	__vector_5, .-__vector_5
	.section	.text.startup.main,"ax",@progbits
.global	main
	.type	main, @function
main:
.LFB10:
	.loc 1 106 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 109 0
	in r24,0x7
	ori r24,lo8(63)
	out 0x7,r24
	.loc 1 110 0
	sbi 0x6,6
	.loc 1 112 0
	in r24,0xa
	out 0xa,r24
	.loc 1 113 0
	in r24,0x9
	ldi r25,lo8(-1)
	out 0x9,r25
	.loc 1 120 0
	lds r24,177
	ori r24,lo8(6)
	sts 177,r24
	.loc 1 123 0
	lds r24,176
	ori r24,lo8(2)
	sts 176,r24
	.loc 1 124 0
	lds r24,112
	ori r24,lo8(2)
	sts 112,r24
	.loc 1 125 0
	ldi r24,lo8(8)
	sts 179,r24
	.loc 1 134 0
	sts 109,__zero_reg__
	.loc 1 135 0
	lds r24,109
	ori r24,lo8(8)
	sts 109,r24
	.loc 1 136 0
	lds r24,109
	ori r24,lo8(16)
	sts 109,r24
	.loc 1 146 0
	in r24,0x4
	out 0x4,r25
	.loc 1 147 0
	in r24,0x5
	ori r24,lo8(5)
	out 0x5,r24
	.loc 1 149 0
	ldi r24,lo8(5)
	out 0x8,r24
	.loc 1 156 0
/* #APP */
 ;  156 "avrmain.c" 1
	sei
 ;  0 "" 2
	.loc 1 176 0
/* #NOAPP */
	ldi r18,lo8(15)
	.loc 1 177 0
	ldi r19,lo8(1)
.L14:
	.loc 1 163 0
	lds r24,portd_state
	lsr r24
	lsr r24
	lsr r24
	out 0x5,r24
	.loc 1 173 0
	lds r24,cpu_state
	cpse r24,__zero_reg__
	rjmp .L13
	.loc 1 173 0 is_stmt 0 discriminator 1
	lds r24,tick
	lds r25,tick+1
	cpi r24,100
	cpc r25,__zero_reg__
	brlo .L13
	.loc 1 176 0 is_stmt 1
	in r24,0x8
	eor r24,r18
	out 0x8,r24
	.loc 1 177 0
	sts cpu_state,r19
.L13:
	.loc 1 181 0
/* #APP */
 ;  181 "avrmain.c" 1
	sleep
	
 ;  0 "" 2
	.loc 1 183 0
/* #NOAPP */
	rjmp .L14
	.cfi_endproc
.LFE10:
	.size	main, .-main
	.comm	fish,1,1
	.comm	cpu_state,1,1
	.comm	return_trip_count,2,1
	.comm	major_trip_count,2,1
	.comm	portd_temp,1,1
.global	program_state
	.section	.bss.program_state,"aw",@nobits
	.type	program_state, @object
	.size	program_state, 2
program_state:
	.zero	2
	.comm	portd_state,1,1
	.comm	portb_state,1,1
	.comm	portc_state,1,1
	.comm	tick,2,1
	.text
.Letext0:
	.file 2 "c:\\program files (x86)\\atmel\\avr tools\\avr toolchain\\bin\\../lib/gcc/avr/4.7.2/../../../../avr/include/stdint.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x183
	.word	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF20
	.byte	0x1
	.long	.LASF21
	.long	.LASF22
	.long	.Ldebug_ranges0+0
	.long	0
	.long	0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF0
	.uleb128 0x3
	.long	.LASF23
	.byte	0x2
	.byte	0x7a
	.long	0x3b
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF3
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF4
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF6
	.uleb128 0x5
	.byte	0x1
	.long	.LASF7
	.byte	0x1
	.byte	0x35
	.byte	0x1
	.long	.LFB7
	.long	.LFE7
	.long	.LLST0
	.byte	0x1
	.uleb128 0x5
	.byte	0x1
	.long	.LASF8
	.byte	0x1
	.byte	0x60
	.byte	0x1
	.long	.LFB8
	.long	.LFE8
	.long	.LLST1
	.byte	0x1
	.uleb128 0x5
	.byte	0x1
	.long	.LASF9
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.long	.LFB9
	.long	.LFE9
	.long	.LLST2
	.byte	0x1
	.uleb128 0x6
	.byte	0x1
	.long	.LASF24
	.byte	0x1
	.byte	0x6a
	.byte	0x1
	.long	0x42
	.long	.LFB10
	.long	.LFE10
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0x7
	.long	.LASF10
	.byte	0x1
	.byte	0x1d
	.long	0xda
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	tick
	.uleb128 0x8
	.long	0x49
	.uleb128 0x7
	.long	.LASF11
	.byte	0x1
	.byte	0x1e
	.long	0xf1
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	portc_state
	.uleb128 0x8
	.long	0x3b
	.uleb128 0x7
	.long	.LASF12
	.byte	0x1
	.byte	0x1f
	.long	0xf1
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	portb_state
	.uleb128 0x7
	.long	.LASF13
	.byte	0x1
	.byte	0x20
	.long	0xf1
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	portd_state
	.uleb128 0x7
	.long	.LASF14
	.byte	0x1
	.byte	0x21
	.long	0xda
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	program_state
	.uleb128 0x7
	.long	.LASF15
	.byte	0x1
	.byte	0x22
	.long	0xf1
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	portd_temp
	.uleb128 0x7
	.long	.LASF16
	.byte	0x1
	.byte	0x23
	.long	0xda
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	major_trip_count
	.uleb128 0x7
	.long	.LASF17
	.byte	0x1
	.byte	0x24
	.long	0xda
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	return_trip_count
	.uleb128 0x7
	.long	.LASF18
	.byte	0x1
	.byte	0x26
	.long	0xf1
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	cpu_state
	.uleb128 0x7
	.long	.LASF19
	.byte	0x1
	.byte	0x27
	.long	0xf1
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	fish
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LFB7
	.long	.LCFI0
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI0
	.long	.LCFI1
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI1
	.long	.LCFI2
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI2
	.long	.LCFI3
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI3
	.long	.LCFI4
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	.LCFI4
	.long	.LCFI5
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 7
	.long	.LCFI5
	.long	.LCFI6
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI6
	.long	.LCFI7
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 9
	.long	.LCFI7
	.long	.LCFI8
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 10
	.long	.LCFI8
	.long	.LFE7
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 11
	.long	0
	.long	0
.LLST1:
	.long	.LFB8
	.long	.LCFI9
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI9
	.long	.LCFI10
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI10
	.long	.LFE8
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	0
	.long	0
.LLST2:
	.long	.LFB9
	.long	.LCFI11
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI11
	.long	.LCFI12
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI12
	.long	.LFE9
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x34
	.word	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.word	0
	.word	0
	.long	.LFB7
	.long	.LFE7-.LFB7
	.long	.LFB8
	.long	.LFE8-.LFB8
	.long	.LFB9
	.long	.LFE9-.LFB9
	.long	.LFB10
	.long	.LFE10-.LFB10
	.long	0
	.long	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LFB7
	.long	.LFE7
	.long	.LFB8
	.long	.LFE8
	.long	.LFB9
	.long	.LFE9
	.long	.LFB10
	.long	.LFE10
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF19:
	.string	"fish"
.LASF8:
	.string	"__vector_14"
.LASF1:
	.string	"unsigned char"
.LASF14:
	.string	"program_state"
.LASF4:
	.string	"long unsigned int"
.LASF10:
	.string	"tick"
.LASF24:
	.string	"main"
.LASF15:
	.string	"portd_temp"
.LASF22:
	.string	"D:\\DEVZONE\\AVR-Programming\\useless_box\\useless_box"
.LASF2:
	.string	"unsigned int"
.LASF12:
	.string	"portb_state"
.LASF6:
	.string	"long long unsigned int"
.LASF23:
	.string	"uint8_t"
.LASF16:
	.string	"major_trip_count"
.LASF21:
	.string	"avrmain.c"
.LASF11:
	.string	"portc_state"
.LASF5:
	.string	"long long int"
.LASF17:
	.string	"return_trip_count"
.LASF20:
	.string	"GNU C 4.7.2"
.LASF13:
	.string	"portd_state"
.LASF9:
	.string	"__vector_5"
.LASF7:
	.string	"__vector_7"
.LASF3:
	.string	"long int"
.LASF0:
	.string	"signed char"
.LASF18:
	.string	"cpu_state"
	.ident	"GCC: (AVR_8_bit_GNU_Toolchain_3.4.2_939) 4.7.2"
.global __do_clear_bss
