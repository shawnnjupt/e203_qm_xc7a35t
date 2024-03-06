//	saes32_enc.S
//	2020-02-16	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Copyright (c) 2020, PQShield Ltd. All rights reserved.

//	AES Encryption and Key Schedule using "lwaes" instructions.

//	macro definitions for the custom instruction
#include	"aes32_c0.h"

		.option nopic
		.text
		.align	2




//	Key schedule for AES-128 Encryption.
//		void aes128_enc_key(uint32_t rk[44], const uint8_t key[16])
//		where:	a0 = rk, a1 = key

		//.align	2
		.globl	aes128_enc_key
		.type	aes128_enc_key,	 @function

aes128_enc_key:

		lui		a2,		%hi(.rcon)			//	rcon pointer
		addi	a2,		a2,		%lo(.rcon)

		addi	a3,		a0,		16 * 10		//	end pointer

		lw		t0,		0(a1)				//	input key
		lw		t1,		4(a1)
		lw		t2,		8(a1)
		lw		t3,		12(a1)

		sw		t0,		0(a0)				//	first round key
		sw		t1,		4(a0)
		sw		t2,		8(a0)
		sw		t3,		12(a0)

		xori	t0,		t0,		1			//	first round constant
		j		.nl0

.ekl0:
		addi	a2,		a2,		1
		lbu		a1,		0(a2)				//	round constant
		xor		t0,		a1,		t0

.nl0:
		slli	a4,		t3,		24			//	rotate a4
		srli	a1,		t3,		8
		or		a1,		a1,		a4

		aes32_spe_encoding		T0, T0, A1, 0
		aes32_spe_encoding		T0, T0, A1, 1
		aes32_spe_encoding		T0, T0, A1, 2
		aes32_spe_encoding		T0, T0, A1, 3

		xor		t1,		t1,		t0
		xor		t2,		t2,		t1
		xor		t3,		t3,		t2

		addi	a0,		a0,		16
		sw		t0,		0(a0)				//	store round key
		sw		t1,		4(a0)
		sw		t2,		8(a0)
		sw		t3,		12(a0)

		bne		a0,		a3,		.ekl0

		jr		ra
		.size	aes128_enc_key,	 .-aes128_enc_key


//	Encrypt rounds. Implements AES-128/192/256 optimized1 depending on nr = {10,12,14}
//		void aes_enc_optimized1(uint8_t ct[16], const uint8_t pt[16],
//							 uint8_t key[16], int nr)
//		where:	a0 = ct, a1 = pt, a2 = key, a3 = nr
        .align	2
		.globl	aes_enc_optimized1
		.type	aes_enc_optimized1,	 @function

aes_enc_optimized1:

		lw		t4,		0(a1)				//	load pt
		lw		t5,		4(a1)
		lw		t6,		8(a1)
		lw		a7,		12(a1)

		lw		t0,		0(a2)				//	load key1
		lw		t1,		4(a2)
		lw		t2,		8(a2)
		lw		t3,		12(a2)

        aes_keygen  T0,  T1,  0

        aes_keygen  T2,  T3,  1

		xor		t0,		t4,		t0			//	pt ^ rk
		xor		t1,		t5,		t1
		xor		t2,		t6,		t2
		xor		t3,		a7,		t3

		add   	a4,		x0,		x0
		//slli	a3,		a3,		4			//	final pointer
		//add		a3,		a3,		a2

		j		.ent1						//	enter loop in the middle

.loop1:
		//	odd round
		aes32_encoding	T0, 0, T4, 0
		aes32_encoding	T0, T0, T5, 1
		aes32_encoding	T0, T0, T6, 2
		aes32_encoding	T0, T0, A7, 3

		aes32_encoding	T1, 0, T5, 0
		aes32_encoding	T1, T1, T6, 1
		aes32_encoding	T1, T1, A7, 2
		aes32_encoding	T1, T1, T4, 3

		aes32_encoding	T2, 0, T6, 0
		aes32_encoding	T2, T2, A7, 1
		aes32_encoding	T2, T2, T4, 2
		aes32_encoding	T2, T2, T5, 3

		aes32_encoding	T3, 0, A7, 0
		aes32_encoding	T3, T3, T4, 1
		aes32_encoding	T3, T3, T5, 2
		aes32_encoding	T3, T3, T6, 3

.ent1:
	//	lw		t4,		16(a2)				//	load round key
	//	lw		t5,		20(a2)
	//	lw		t6,		24(a2)
	//	lw		a7,		28(a2)
        addi  a4,  a4,  1
	  //	even round
		aes32_encoding	T4, 0, T0, 0  //
		aes32_encoding	T4, T4, T1, 1
		aes32_encoding	T4, T4, T2, 2
		aes32_encoding	T4, T4, T3, 3

		aes32_encoding	T5, 0, T1, 0
		aes32_encoding	T5, T5, T2, 1
		aes32_encoding	T5, T5, T3, 2
		aes32_encoding	T5, T5, T0, 3

		aes32_encoding	T6, 0, T2, 0
		aes32_encoding	T6, T6, T3, 1
		aes32_encoding	T6, T6, T0, 2
		aes32_encoding	T6, T6, T1, 3

		aes32_encoding	A7, 0, T3, 0
		aes32_encoding	A7, A7, T0, 1
		aes32_encoding	A7, A7, T1, 2
		aes32_encoding	A7, A7, T2, 3


	//	lw		t0,		0(a2)				//	load round key
	//	lw		t1,		4(a2)
	//	lw		t2,		8(a2)
	//	lw		t3,		12(a2)
		bne		a4,		a3,		.loop1

		//	final (output) round
		aes32_spe_encoding		T0, 0, T4, 0
		aes32_spe_encoding		T0, T0, T5, 1
		aes32_spe_encoding		T0, T0, T6, 2
		aes32_spe_encoding		T0, T0, A7, 3

		aes32_spe_encoding		T1, 0, T5, 0
		aes32_spe_encoding		T1, T1, T6, 1
		aes32_spe_encoding		T1, T1, A7, 2
		aes32_spe_encoding		T1, T1, T4, 3

		aes32_spe_encoding		T2, 0, T6, 0
		aes32_spe_encoding		T2, T2, A7, 1
		aes32_spe_encoding		T2, T2, T4, 2
		aes32_spe_encoding		T2, T2, T5, 3

		aes32_spe_encoding		T3, 0, A7, 0
		aes32_spe_encoding		T3, T3, T4, 1
		aes32_spe_encoding		T3, T3, T5, 2
		aes32_spe_encoding		T3, T3, T6, 3

		sw		t0,		0(a0)				//	store ct
		sw		t1,		4(a0)
		sw		t2,		8(a0)
		sw		t3,		12(a0)

		jr		ra
		.size	aes_enc_optimized1,	 .-aes_enc_optimized1





//	Encrypt rounds. Implements AES-128/192/256 optimized1 depending on nr = {10,12,14}
//		void aes_enc_optimized2(uint8_t ct[16], const uint8_t pt[16],
//							 uint8_t key[16])
//		where:	a0 = ct, a1 = pt, a2 = key
        .align	2
		.globl	aes_enc_optimized2
		.type	aes_enc_optimized2,	 @function

aes_enc_optimized2:

		lw		t4,		0(a1)				//	load pt
		lw		t5,		4(a1)
		lw		t6,		8(a1)
		lw		a7,		12(a1)

		lw		t0,		0(a2)				//	load key1
		lw		t1,		4(a2)
		lw		t2,		8(a2)
		lw		t3,		12(a2)

        aes_keygen  T0,  T1,  0

        aes_keygen  T2,  T3,  1

		xor		t0,		t4,		t0			//	pt ^ rk
		xor		t1,		t5,		t1
		xor		t2,		t6,		t2
		xor		t3,		a7,		t3

		aes_cirgen   T0,  T1,  0
		aes_cirgen   T2,  T3,  1

        aes_get_result  T0,0
        aes_get_result  T1,1
        aes_get_result  T2,2
        aes_get_result  T3,3

        sw		t0,		0(a0)				//	store ct
		sw		t1,		4(a0)
		sw		t2,		8(a0)
		sw		t3,		12(a0)


		jr		ra
		.size	aes_enc_optimized2,	 .-aes_enc_optimized2





//	Encrypt rounds. Implements AES-128/192/256 depending on nr = {10,12,14}
//		void aes_enc_rounds(uint8_t ct[16], const uint8_t pt[16],
//							const uint32_t rk[], int nr)
//		where:	a0 = ct, a1 = pt, a2 = rk, a3 = nr
        .align	2
		.globl	aes_enc_rounds
		.type	aes_enc_rounds,	 @function

aes_enc_rounds:

		lw		t4,		0(a1)				//	load pt
		lw		t5,		4(a1)
		lw		t6,		8(a1)
		lw		a7,		12(a1)

		lw		t0,		0(a2)				//	load rk
		lw		t1,		4(a2)
		lw		t2,		8(a2)
		lw		t3,		12(a2)

		xor		t0,		t4,		t0			//	pt ^ rk
		xor		t1,		t5,		t1
		xor		t2,		t6,		t2
		xor		t3,		a7,		t3

		slli	a3,		a3,		4			//	final pointer
		add		a3,		a3,		a2

		j		.ent						//	enter loop in the middle

.loop:
		//	odd round
		aes32_encoding	T0, T0, T4, 0
		aes32_encoding	T0, T0, T5, 1
		aes32_encoding	T0, T0, T6, 2
		aes32_encoding	T0, T0, A7, 3

		aes32_encoding	T1, T1, T5, 0
		aes32_encoding	T1, T1, T6, 1
		aes32_encoding	T1, T1, A7, 2
		aes32_encoding	T1, T1, T4, 3

		aes32_encoding	T2, T2, T6, 0
		aes32_encoding	T2, T2, A7, 1
		aes32_encoding	T2, T2, T4, 2
		aes32_encoding	T2, T2, T5, 3

		aes32_encoding	T3, T3, A7, 0
		aes32_encoding	T3, T3, T4, 1
		aes32_encoding	T3, T3, T5, 2
		aes32_encoding	T3, T3, T6, 3

.ent:
		lw		t4,		16(a2)				//	load round key
		lw		t5,		20(a2)
		lw		t6,		24(a2)
		lw		a7,		28(a2)
       // nop
        //nop
		//	even round
		aes32_encoding	T4, T4, T0, 0  // t0λ��ʼxorֵ T4Ϊ��Կ  ���浽T4
		aes32_encoding	T4, T4, T1, 1
		aes32_encoding	T4, T4, T2, 2
		aes32_encoding	T4, T4, T3, 3

		aes32_encoding	T5, T5, T1, 0
		aes32_encoding	T5, T5, T2, 1
		aes32_encoding	T5, T5, T3, 2
		aes32_encoding	T5, T5, T0, 3

		aes32_encoding	T6, T6, T2, 0
		aes32_encoding	T6, T6, T3, 1
		aes32_encoding	T6, T6, T0, 2
		aes32_encoding	T6, T6, T1, 3

		aes32_encoding	A7, A7, T3, 0
		aes32_encoding	A7, A7, T0, 1
		aes32_encoding	A7, A7, T1, 2
		aes32_encoding	A7, A7, T2, 3

		addi	a2,		a2,		32
		lw		t0,		0(a2)				//	load round key
		lw		t1,		4(a2)
		lw		t2,		8(a2)
		lw		t3,		12(a2)
		bne		a3,		a2,		.loop

		//	final (output) round
		aes32_spe_encoding		T0, T0, T4, 0
		aes32_spe_encoding		T0, T0, T5, 1
		aes32_spe_encoding		T0, T0, T6, 2
		aes32_spe_encoding		T0, T0, A7, 3

		aes32_spe_encoding		T1, T1, T5, 0
		aes32_spe_encoding		T1, T1, T6, 1
		aes32_spe_encoding		T1, T1, A7, 2
		aes32_spe_encoding		T1, T1, T4, 3

		aes32_spe_encoding		T2, T2, T6, 0
		aes32_spe_encoding		T2, T2, A7, 1
		aes32_spe_encoding		T2, T2, T4, 2
		aes32_spe_encoding		T2, T2, T5, 3

		aes32_spe_encoding		T3, T3, A7, 0
		aes32_spe_encoding		T3, T3, T4, 1
		aes32_spe_encoding		T3, T3, T5, 2
		aes32_spe_encoding		T3, T3, T6, 3

		sw		t0,		0(a0)				//	store ct
		sw		t1,		4(a0)
		sw		t2,		8(a0)
		sw		t3,		12(a0)

		jr		ra
		.size	aes_enc_rounds,	 .-aes_enc_rounds



//	round constants

		.type	.rcon,	@object
.rcon:
		.byte	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
		.size	.rcon,	10

