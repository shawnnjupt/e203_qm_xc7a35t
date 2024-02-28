/*
 * saes_test.h
 *
 *  Created on: 2023年12月21日
 *      Author: 96579
 */

#ifndef APPLICATION_AES_H_
#define APPLICATION_AES_H_


#include "hbird_sdk_soc.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


//extern uint8_t pt[16];
//extern uint8_t key1[16];
extern uint8_t key2[16];
extern uint8_t key3[16];
extern uint8_t key4[16];
extern uint8_t key5[16];
extern uint8_t key6[16];
extern uint8_t key7[16];
extern uint8_t key8[16];
extern uint8_t key9[16];
extern uint8_t key10[16];
extern uint8_t key11[16];


extern uint32_t cir_rd_1;
extern uint32_t cir_rd_2;
extern uint32_t cir_rd_3;
extern uint32_t cir_rd_4;

extern uint32_t cir_rd_5;
extern uint32_t cir_rd_6;
extern uint32_t cir_rd_7;
extern uint32_t cir_rd_8;


extern uint32_t cir1_rs2_1;
extern uint32_t cir1_rs2_2;
extern uint32_t cir1_rs2_3;
extern uint32_t cir1_rs2_4;


static uint32_t custom3_aes_keyset1 (uint32_t first_keygen,uint32_t second_keygen)
{
	uint32_t keyset;


        asm volatile (
           ".insn r 0x7b, 6, 8, %0, %1, %2"
                 :"=r"(keyset)
                 :"r"(first_keygen),
				  "r"(second_keygen)
         );


    return keyset;
}



static uint32_t custom3_aes_keyset2 (uint32_t third_keygen,uint32_t fourth_keygen)
{
	uint32_t keyset;


        asm volatile (
           ".insn r 0x7b, 6, 9, %0, %1, %2"
                 :"=r"(keyset)
                 :"r"(third_keygen),
				  "r"(fourth_keygen)
         );


    return keyset;
}







static uint32_t custom3_aes_encoding_1 (uint32_t encoding_rs1,uint32_t encoding_rs2)
{
	uint32_t encoding_rd;


        asm volatile (
           ".insn r 0x7b, 6, 0, %0, %1, %2"
                 :"=r"(encoding_rd)
                 :"r"(encoding_rs1),
				  "r"(encoding_rs2)
         );    	


    return encoding_rd;
}


static uint32_t custom3_aes_encoding_2 (uint32_t encoding_rs1,uint32_t encoding_rs2)
{
	uint32_t encoding_rd;


        asm volatile (
           ".insn r 0x7b, 6, 1, %0, %1, %2"
                 :"=r"(encoding_rd)
                 :"r"(encoding_rs1),
				  "r"(encoding_rs2)
         );


    return encoding_rd;
}


static uint32_t custom3_aes_encoding_3 (uint32_t encoding_rs1,uint32_t encoding_rs2)
{
	uint32_t encoding_rd;


        asm volatile (
           ".insn r 0x7b, 6, 2, %0, %1, %2"
                 :"=r"(encoding_rd)
                 :"r"(encoding_rs1),
				  "r"(encoding_rs2)
         );


    return encoding_rd;
}



static uint32_t custom3_aes_encoding_4 (uint32_t encoding_rs1,uint32_t encoding_rs2)
{
	uint32_t encoding_rd;


        asm volatile (
           ".insn r 0x7b, 6, 3, %0, %1, %2"
                 :"=r"(encoding_rd)
                 :"r"(encoding_rs1),
				  "r"(encoding_rs2)
         );


    return encoding_rd;
}




//正常加密 对于明文加密
static uint32_t custom3_aes_encoding_choose(uint32_t encoding_rs1,uint32_t encoding_rs2,int word_sequence)
{


    if(word_sequence==0)
    {
    return custom3_aes_encoding_1(encoding_rs1,encoding_rs2);

    }else if (word_sequence==1)
    {
        return custom3_aes_encoding_2(encoding_rs1,encoding_rs2);

    }else if (word_sequence==2)
    {
        return custom3_aes_encoding_3(encoding_rs1,encoding_rs2);

    }else if (word_sequence==3)
    {

        return custom3_aes_encoding_4(encoding_rs1,encoding_rs2);
    }

    return 0;

}



static uint32_t custom3_aes_spe_encoding_1 (uint32_t spe_encoding_rs1,uint32_t spe_encoding_rs2)
{
	uint32_t spe_encoding_rd;


        asm volatile (
           ".insn r 0x7b, 6, 4, %0, %1, %2"
                 :"=r"(spe_encoding_rd)
                 :"r"(spe_encoding_rs1),
				  "r"(spe_encoding_rs2)
         );


    return spe_encoding_rd;
}



static uint32_t custom3_aes_spe_encoding_2 (uint32_t spe_encoding_rs1,uint32_t spe_encoding_rs2)
{
	uint32_t spe_encoding_rd;


        asm volatile (
           ".insn r 0x7b, 6, 5, %0, %1, %2"
                 :"=r"(spe_encoding_rd)
                 :"r"(spe_encoding_rs1),
				  "r"(spe_encoding_rs2)
         );


    return spe_encoding_rd;
}

static uint32_t custom3_aes_spe_encoding_3 (uint32_t spe_encoding_rs1,uint32_t spe_encoding_rs2)
{
	uint32_t spe_encoding_rd;


        asm volatile (
           ".insn r 0x7b, 6, 6, %0, %1, %2"
                 :"=r"(spe_encoding_rd)
                 :"r"(spe_encoding_rs1),
				  "r"(spe_encoding_rs2)
         );


    return spe_encoding_rd;
}

static uint32_t custom3_aes_spe_encoding_4 (uint32_t spe_encoding_rs1,uint32_t spe_encoding_rs2)
{
	uint32_t spe_encoding_rd;


        asm volatile (
           ".insn r 0x7b, 6, 7, %0, %1, %2"
                 :"=r"(spe_encoding_rd)
                 :"r"(spe_encoding_rs1),
				  "r"(spe_encoding_rs2)
         );


    return spe_encoding_rd;
}


//特殊加密 对于密钥加密或者是最后一次明文加密
static uint32_t custom3_aes_spe_encoding_choose (uint32_t spe_encoding_rs1,uint32_t spe_encoding_rs2,int word_sequence)
{
    if(word_sequence==0)
    {
    return custom3_aes_spe_encoding_1(spe_encoding_rs1,spe_encoding_rs2);

    }else if (word_sequence==1)
    {
        return custom3_aes_spe_encoding_2(spe_encoding_rs1,spe_encoding_rs2);

    }else if (word_sequence==2)
    {
        return custom3_aes_spe_encoding_3(spe_encoding_rs1,spe_encoding_rs2);

    }else if (word_sequence==3)
    {

        return custom3_aes_spe_encoding_4(spe_encoding_rs1,spe_encoding_rs2);
    }

    return 0;
}


uint32_t pt_extract(uint8_t pt_test[],int word_sequence);
void before_cir_xor(uint8_t pt_xor[],uint8_t key[]);
void  aes_cir_odd(uint8_t key[],uint32_t cir_rs2_1,uint32_t cir_rs2_2,uint32_t cir_rs2_3,uint32_t cir_rs2_4);
void  aes_cir_even(uint8_t key[],uint32_t cir_rs2_1,uint32_t cir_rs2_2,uint32_t cir_rs2_3,uint32_t cir_rs2_4);
void  aes_cir_end(uint8_t key[],uint32_t cir_rs2_1,uint32_t cir_rs2_2,uint32_t cir_rs2_3,uint32_t cir_rs2_4);
void nice_case(uint8_t key[],uint8_t pt[]);
void key_insert(uint32_t key_1, uint32_t key_2,uint32_t key_3,uint32_t key_4,uint8_t key[]);

void aes_key_cir(uint8_t key[]);



#endif /* APPLICATION_AES_H_ */
