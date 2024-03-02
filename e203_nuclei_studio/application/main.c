// See LICENSE for license details.
#include <aes.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "hbird_sdk_soc.h"
#include "board_mcu200t.h"
#include "tinyaes_h.h"

#include "aes32_wrap.h"



static void phex(uint8_t *str)
{

#if defined(AES256)
    uint8_t len = 32;
#elif defined(AES192)
    uint8_t len = 24;
#elif defined(AES128)
    uint8_t len = 16;
#endif

    unsigned char i;
    for (i = 0; i < len; ++i)
        printf("%.2x", str[i]);
    printf("\n");
}

static void normal_case(void)
{
    uint8_t i;
    uint8_t key[16] = {(uint8_t)0x2b, (uint8_t)0x7e, (uint8_t)0x15, (uint8_t)0x16, (uint8_t)0x28, (uint8_t)0xae, (uint8_t)0xd2, (uint8_t)0xa6, (uint8_t)0xab, (uint8_t)0xf7, (uint8_t)0x15, (uint8_t)0x88, (uint8_t)0x09, (uint8_t)0xcf, (uint8_t)0x4f, (uint8_t)0x3c};
    uint8_t plain_text[16] = {(uint8_t)0x32, (uint8_t)0x43, (uint8_t)0xf6, (uint8_t)0xa8, (uint8_t)0x88, (uint8_t)0x5a, (uint8_t)0x30, (uint8_t)0x8d, (uint8_t)0x31, (uint8_t)0x31, (uint8_t)0x98, (uint8_t)0xa2, (uint8_t)0xe0, (uint8_t)0x37, (uint8_t)0x07, (uint8_t)0x34};
    printf("ciphertext:\n");
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);
    AES_ECB_encrypt(&ctx, plain_text);
    phex(plain_text);

}






void led_config()
{

    gpio_enable_output(GPIOA,SOC_LED_6_GPIO_MASK);
    gpio_write(GPIOA,SOC_LED_6_GPIO_MASK,0);

    gpio_enable_output(GPIOB,SOC_SW_0_GPIO_MASK);
    gpio_write(GPIOB,SOC_SW_0_GPIO_MASK,0);

    gpio_enable_output(GPIOB,SOC_SW_1_GPIO_MASK);
    gpio_write(GPIOB,SOC_SW_1_GPIO_MASK,0);

    gpio_enable_output(GPIOB,SOC_SW_2_GPIO_MASK);
    gpio_write(GPIOB,SOC_SW_2_GPIO_MASK,0);

}


void led_toggle()
{

    gpio_toggle(GPIOA,SOC_LED_6_GPIO_MASK);
    gpio_toggle(GPIOB,SOC_SW_0_GPIO_MASK);
    gpio_toggle(GPIOB,SOC_SW_1_GPIO_MASK);
    gpio_toggle(GPIOB,SOC_SW_2_GPIO_MASK);
}






int main(void)
{

      //明文
	 uint8_t pt[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
	 //密钥
	 uint8_t key1[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

	 uint32_t rk[44];

	 int i=0;

	 unsigned int begin_instret, end_instret, instret_normal, instret_nice;
	 unsigned int begin_cycle,   end_cycle,   cycle_normal,   cycle_nice;

     printf(" Hello World From RISC-V Processor!\r\n");

#if defined(AES256)
    printf("\nTesting AES256\n\n");
#elif defined(AES192)
    printf("\nTesting AES192\n\n");
#elif defined(AES128)
    printf("Testing AES128\n");
#else
    printf("You need to specify a symbol between AES128, AES192 or AES256. Exiting");
    return 0;
#endif



    while(1){

    	 printf("**********************************************\n");
    	 printf("** begin to exu normal case\n");


    	 aes128_enc_key(rk,key1);

//    	 begin_instret =  __get_rv_instret();
//    	 begin_cycle   =  __get_rv_cycle();
//
//        normal_case();
//
//        instret_normal = end_instret - begin_instret;
//        cycle_normal = end_cycle - begin_cycle;
//
//
//        printf("**********************************************\n");
//        printf("** begin to exu nice_case\n");
//        begin_instret =  __get_rv_instret();
//        begin_cycle   =  __get_rv_cycle();
//
//
//        custom3_aes_keyset1(pt_extract(key1,0),pt_extract(key1,1));
//  		custom3_aes_keyset2(pt_extract(key1,2),pt_extract(key1,3));
//        nice_case(key1,pt);
//
//        end_instret = __get_rv_instret();
//        end_cycle   = __get_rv_cycle();
//
//        instret_nice = end_instret - begin_instret;
//        cycle_nice   = end_cycle - begin_cycle;
//
//        printf("**********************************************\n");
//        printf("** performance list \n");
//
//        printf("\t normal: \n");
//        printf("\t      instret: %u, cycle: %u \n", instret_normal, cycle_normal);
//        printf("\t nice  : \n");
//        printf("\t      instret: %u, cycle: %u \n", instret_nice  , cycle_nice  );
//
//        printf("**********************************************\n\n");



for (i=0;i<11;i++)
{

	printf("context(%d)=%8x %8x %8x %8x\n",i,rk[4*i],rk[4*i+1],rk[4*i+2],rk[4*i+3]);
}


        delay_1ms(1);


    }
    return 0;
}

