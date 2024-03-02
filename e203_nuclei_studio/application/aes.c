/*
 * saes_test.c
 *
 *  Created on: 2023年12月21日
 *      Author: 96579
 */


#include <aes.h>



  uint8_t key2[16]={0};
  uint8_t key3[16]={0};
  uint8_t key4[16]={0};
  uint8_t key5[16]={0};
  uint8_t key6[16]={0};
  uint8_t key7[16]={0};
  uint8_t key8[16]={0};
  uint8_t key9[16]={0};
  uint8_t key10[16]={0};
  uint8_t key11[16]={0};


	uint32_t cir_rd_1;
	uint32_t cir_rd_2;
	uint32_t cir_rd_3;
	uint32_t cir_rd_4;

	uint8_t cir_rd_temp1;
	uint8_t cir_rd_temp2;
	uint8_t cir_rd_temp3;
	uint8_t cir_rd_temp4;




	uint32_t cir_rd_5;
	uint32_t cir_rd_6;
	uint32_t cir_rd_7;
	uint32_t cir_rd_8;


	uint32_t cir1_rs2_1;
	uint32_t cir1_rs2_2;
	uint32_t cir1_rs2_3;
	uint32_t cir1_rs2_4;


//从uint8 中抽取uint32
uint32_t pt_extract(uint8_t pt_test[],int word_sequence){
	volatile uint32_t result=0;
	    result=(pt_test[4*word_sequence+3]<<24)+(pt_test[4*word_sequence+2]<<16)+(pt_test[4*word_sequence+1]<<8)+pt_test[4*word_sequence];

	    return result;
}

//将 uint32 数据插入 uint8数组中
void key_insert(uint32_t key_1, uint32_t key_2,uint32_t key_3,uint32_t key_4,uint8_t key[])
{
	int i;
	for(i=0;i<16;i++)
	{
		if(i<4)
		{
		key[i]=key_1>>(8*i);
		}else if (i<8)
		{
		key[i]=key_2>>(8*(i-4));
		}else if(i<12){

			key[i]=key_3>>(8*(i-8));
		}else{

			key[i]=key_4>>(8*(i-12));
		}
	}




}

//循环生成 10个密钥
void aes_key_cir(uint8_t key[]){

	uint32_t key_1=pt_extract(key,0);
	uint32_t key_2=pt_extract(key,1);
	uint32_t key_3=pt_extract(key,2);
	uint32_t key_4=pt_extract(key,3);
	uint32_t temp1=0;
	uint32_t temp2=0;
	uint32_t temp_key_4=0;


	uint8_t rcon[10]={1,2,4,8,16,32,64,128,27,54};
	int i;
	for(i=0;i<10;i++)
	{
	key_1=key_1^(uint32_t)rcon[i];
    temp1=key_4<<24;
    temp2=key_4>>8;

    temp_key_4=temp1+temp2;
    key_1=custom3_aes_spe_encoding_choose(key_1,temp_key_4,0);
    key_1=custom3_aes_spe_encoding_choose(key_1,temp_key_4,1);
    key_1=custom3_aes_spe_encoding_choose(key_1,temp_key_4,2);
    key_1=custom3_aes_spe_encoding_choose(key_1,temp_key_4,3);

    key_2=key_1^key_2;
    key_3=key_3^key_2;
    key_4=key_4^key_3;



#ifdef _DEBUG_INFO_
    printf("key1=%08x\n",key_1);
    printf("key2=%08x\n",key_2);
    printf("key3=%08x\n",key_3);
    printf("key4=%08x\n",key_4);
#endif

    	switch(i)
    	{
		case 0:key_insert(key_1,key_2,key_3,key_4,key2);
		case 1:key_insert(key_1,key_2,key_3,key_4,key3);
		case 2:key_insert(key_1,key_2,key_3,key_4,key4);
		case 3:key_insert(key_1,key_2,key_3,key_4,key5);
		case 4:key_insert(key_1,key_2,key_3,key_4,key6);
		case 5:key_insert(key_1,key_2,key_3,key_4,key7);
		case 6:key_insert(key_1,key_2,key_3,key_4,key8);
		case 7:key_insert(key_1,key_2,key_3,key_4,key9);
		case 8:key_insert(key_1,key_2,key_3,key_4,key10);
		case 9:key_insert(key_1,key_2,key_3,key_4,key11);
    	}

	}

}

void before_cir_xor(uint8_t pt_xor[],uint8_t key[]){

	cir1_rs2_1=pt_extract(pt_xor,0)^pt_extract(key,0);// 明文与初始密钥xor之后得到的四个字数据
	cir1_rs2_2=pt_extract(pt_xor,1)^pt_extract(key,1);
	cir1_rs2_3=pt_extract(pt_xor,2)^pt_extract(key,2);
	cir1_rs2_4=pt_extract(pt_xor,3)^pt_extract(key,3);


//	printf("cir1_rs2_1=%08x\n",cir1_rs2_1);
//	printf("cir1_rs2_2=%08x\n",cir1_rs2_2);
//	printf("cir1_rs2_3=%08x\n",cir1_rs2_3);
//	printf("cir1_rs2_4=%08x\n",cir1_rs2_4);

}


void  aes_cir_odd(uint8_t key[],uint32_t cir_rs2_1,uint32_t cir_rs2_2,uint32_t cir_rs2_3,uint32_t cir_rs2_4)//奇次循环处理 32x4=128  以字为单位，每次处理一个byte 8位 分别用四个uint32_t变量存储四个字
{


    cir_rd_1=custom3_aes_encoding_choose(0,cir_rs2_1,0);
	cir_rd_1=custom3_aes_encoding_choose(cir_rd_1,cir_rs2_2,1);
	cir_rd_1=custom3_aes_encoding_choose(cir_rd_1,cir_rs2_3,2);
	cir_rd_1=custom3_aes_encoding_choose(cir_rd_1,cir_rs2_4,3);

	cir_rd_2=custom3_aes_encoding_choose(0,cir_rs2_2,0);
	cir_rd_2=custom3_aes_encoding_choose(cir_rd_2,cir_rs2_3,1);
	cir_rd_2=custom3_aes_encoding_choose(cir_rd_2,cir_rs2_4,2);
	cir_rd_2=custom3_aes_encoding_choose(cir_rd_2,cir_rs2_1,3);



	cir_rd_3=custom3_aes_encoding_choose(0,cir_rs2_3,0);
	cir_rd_3=custom3_aes_encoding_choose(cir_rd_3,cir_rs2_4,1);
	cir_rd_3=custom3_aes_encoding_choose(cir_rd_3,cir_rs2_1,2);
	cir_rd_3=custom3_aes_encoding_choose(cir_rd_3,cir_rs2_2,3);


	cir_rd_4=custom3_aes_encoding_choose(0,cir_rs2_4,0);
	cir_rd_4=custom3_aes_encoding_choose(cir_rd_4,cir_rs2_1,1);
	cir_rd_4=custom3_aes_encoding_choose(cir_rd_4,cir_rs2_2,2);
	cir_rd_4=custom3_aes_encoding_choose(cir_rd_4,cir_rs2_3,3);


#ifdef _DEBUG_INFO_
	printf("cir_rd_1=%08x\n",cir_rd_1);
	printf("cir_rd_2=%08x\n",cir_rd_2);
	printf("cir_rd_3=%08x\n",cir_rd_3);
	printf("cir_rd_4=%08x\n",cir_rd_4);
#endif

}


void  aes_cir_even(uint8_t key[],uint32_t cir_rs2_1,uint32_t cir_rs2_2,uint32_t cir_rs2_3,uint32_t cir_rs2_4)//偶次 32x4=128  以字为单位，每次处理一个byte 8位 分别用四个uint32_t变量存储四个字
{

	cir_rd_5=custom3_aes_encoding_choose(0,cir_rs2_1,0);
	cir_rd_5=custom3_aes_encoding_choose(cir_rd_5,cir_rs2_2,1);
	cir_rd_5=custom3_aes_encoding_choose(cir_rd_5,cir_rs2_3,2);
	cir_rd_5=custom3_aes_encoding_choose(cir_rd_5,cir_rs2_4,3);


	cir_rd_6=custom3_aes_encoding_choose(0,cir_rs2_2,0);
	cir_rd_6=custom3_aes_encoding_choose(cir_rd_6,cir_rs2_3,1);
	cir_rd_6=custom3_aes_encoding_choose(cir_rd_6,cir_rs2_4,2);
	cir_rd_6=custom3_aes_encoding_choose(cir_rd_6,cir_rs2_1,3);



	cir_rd_7=custom3_aes_encoding_choose(0,cir_rs2_3,0);
	cir_rd_7=custom3_aes_encoding_choose(cir_rd_7,cir_rs2_4,1);
	cir_rd_7=custom3_aes_encoding_choose(cir_rd_7,cir_rs2_1,2);
	cir_rd_7=custom3_aes_encoding_choose(cir_rd_7,cir_rs2_2,3);


	cir_rd_8=custom3_aes_encoding_choose(0,cir_rs2_4,0);
	cir_rd_8=custom3_aes_encoding_choose(cir_rd_8,cir_rs2_1,1);
	cir_rd_8=custom3_aes_encoding_choose(cir_rd_8,cir_rs2_2,2);
	cir_rd_8=custom3_aes_encoding_choose(cir_rd_8,cir_rs2_3,3);

#ifdef _DEBUG_INFO_
	printf("cir_rd_5=%08x\n",cir_rd_5);
	printf("cir_rd_6=%08x\n",cir_rd_6);
	printf("cir_rd_7=%08x\n",cir_rd_7);
	printf("cir_rd_8=%08x\n",cir_rd_8);
#endif
}



void  aes_cir_end(uint8_t key[],uint32_t cir_rs2_1,uint32_t cir_rs2_2,uint32_t cir_rs2_3,uint32_t cir_rs2_4)//奇次 32x4=128  以字为单位，每次处理一个byte 8位 分别用四个uint32_t变量存储四个字
{

    	cir_rd_5=custom3_aes_spe_encoding_choose(0,cir_rs2_1,0);
		cir_rd_5=custom3_aes_spe_encoding_choose(cir_rd_5,cir_rs2_2,1);
		cir_rd_5=custom3_aes_spe_encoding_choose(cir_rd_5,cir_rs2_3,2);
		cir_rd_5=custom3_aes_spe_encoding_choose(cir_rd_5,cir_rs2_4,3);


		cir_rd_6=custom3_aes_spe_encoding_choose(0,cir_rs2_2,0);
		cir_rd_6=custom3_aes_spe_encoding_choose(cir_rd_6,cir_rs2_3,1);
		cir_rd_6=custom3_aes_spe_encoding_choose(cir_rd_6,cir_rs2_4,2);
		cir_rd_6=custom3_aes_spe_encoding_choose(cir_rd_6,cir_rs2_1,3);



		cir_rd_7=custom3_aes_spe_encoding_choose(0,cir_rs2_3,0);
		cir_rd_7=custom3_aes_spe_encoding_choose(cir_rd_7,cir_rs2_4,1);
		cir_rd_7=custom3_aes_spe_encoding_choose(cir_rd_7,cir_rs2_1,2);
		cir_rd_7=custom3_aes_spe_encoding_choose(cir_rd_7,cir_rs2_2,3);


		cir_rd_8=custom3_aes_spe_encoding_choose(0,cir_rs2_4,0);
		cir_rd_8=custom3_aes_spe_encoding_choose(cir_rd_8,cir_rs2_1,1);
		cir_rd_8=custom3_aes_spe_encoding_choose(cir_rd_8,cir_rs2_2,2);
		cir_rd_8=custom3_aes_spe_encoding_choose(cir_rd_8,cir_rs2_3,3);

#ifdef _DEBUG_INFO_
	printf("cir_rd_5=%08x\n",cir_rd_5);
	printf("cir_rd_6=%08x\n",cir_rd_6);
	printf("cir_rd_7=%08x\n",cir_rd_7);
	printf("cir_rd_8=%08x\n",cir_rd_8);
#endif
}



//格式为 aes-ecb 128  11个密钥
void nice_case(uint8_t key[],uint8_t pt[])
{

	//aes_key_cir(key);//生成密钥
	before_cir_xor(pt,key);//初始工作 进行xor
	aes_cir_odd(key2,cir1_rs2_1,cir1_rs2_2,cir1_rs2_3,cir1_rs2_4);//奇次操作
	aes_cir_even(key3,cir_rd_1,cir_rd_2,cir_rd_3,cir_rd_4);//偶次操作
	aes_cir_odd(key4,cir_rd_5,cir_rd_6,cir_rd_7,cir_rd_8);
	aes_cir_even(key5,cir_rd_1,cir_rd_2,cir_rd_3,cir_rd_4);
	aes_cir_odd(key6,cir_rd_5,cir_rd_6,cir_rd_7,cir_rd_8);
	aes_cir_even(key7,cir_rd_1,cir_rd_2,cir_rd_3,cir_rd_4);
	aes_cir_odd(key8,cir_rd_5,cir_rd_6,cir_rd_7,cir_rd_8);
	aes_cir_even(key9,cir_rd_1,cir_rd_2,cir_rd_3,cir_rd_4);
	aes_cir_odd(key10,cir_rd_5,cir_rd_6,cir_rd_7,cir_rd_8);
	aes_cir_end(key11,cir_rd_1,cir_rd_2,cir_rd_3,cir_rd_4);

	//打印结果
//#ifdef _DEBUG_INFO_
	printf("rd_1=%08x\n",cir_rd_5);
	printf("rd_2=%08x\n",cir_rd_6);
	printf("rd_3=%08x\n",cir_rd_7);
	printf("rd_4=%08x\n",cir_rd_8);
//#endif
}




