#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "sccb.h"
#include "delay.h"

void initCameraClk() {

  uint16_t period = 50;
  uint16_t prescaler = 0;

  SCCB_GPIO_Config();
  initGPIOForCameraClk();
  initTim4ForCameraClk(period, prescaler);
  initPWMForCameraClk(period);

}

void SCCB_GPIO_Config(void) {

  /* configure sio_c / sio_d to port A */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin =  SCCB_SIC_BIT|SCCB_SID_BIT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void SCCB_SIC_GPIO_Config(void) {
  
  // Configure GPIO port D pin 12 to output 
  // pin to send clk signal to camera

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;

  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Connect TIM4 pins to  GPIO Port D Pin 12 */
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
}
  
/*void SCCB_SID_GPIO_OUTPUT(void)*/
/*{*/
   /*[> Enable GPIOC  clock <]*/
  /*[>RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);<]*/
  /*RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);*/

  /*GPIO_InitTypeDef GPIO_InitStructure;*/
  /*GPIO_InitStructure.GPIO_Pin =  SCCB_SID_BIT;*/
  /*GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;*/
  /*GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;*/
  /*GPIO_Init(GPIOC, &GPIO_InitStructure);*/
/*}*/

/*void SCCB_SID_GPIO_INPUT(void) {*/

  /*[> Enable GPIOC  clock <]*/
  /*[>RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);<]*/

  /*RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);*/

  /*GPIO_InitTypeDef GPIO_InitStructure;*/
  /*GPIO_InitStructure.GPIO_Pin =  SCCB_SID_BIT;*/
  /*GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;*/
  /*//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;*/
  /*GPIO_Init(GPIOC, &GPIO_InitStructure);*/
/*}*/

/*void startSCCB(void) {*/

    /*SCCB_SID_H();     //Êý¾ÝÏß¸ßµçÆ½*/
    /*delay_us(500);*/

    /*SCCB_SIC_H();	   //ÔÚÊ±ÖÓÏß¸ßµÄÊ±ºòÊý¾ÝÏßÓÉ¸ßÖÁµÍ*/
    /*delay_us(500);*/
 
    /*SCCB_SID_L();*/
    /*delay_us(500);*/

    /*SCCB_SIC_L();	 //Êý¾ÝÏß»Ö¸´µÍµçÆ½£¬µ¥²Ù×÷º¯Êý±ØÒª*/
    /*delay_us(500);*/
/*}*/
/*/**/
/*-----------------------------------------------*/
   /*¹¦ÄÜ: stopÃüÁî,SCCBµÄÍ£Ö¹ÐÅºÅ*/
   /*²ÎÊý: ÎÞ*/
 /*·µ»ØÖµ: ÎÞ*/
/*-----------------------------------------------*/
/**/*/
/*void stopSCCB(void)*/
/*{*/
    /*SCCB_SID_L();*/
    /*delay_us(500);*/
 
    /*SCCB_SIC_H();	*/
    /*delay_us(500);*/
  

    /*SCCB_SID_H();	*/
    /*delay_us(500);*/
   
/*}*/

/*/**/
/*-----------------------------------------------*/
   /*¹¦ÄÜ: noAck,ÓÃÓÚÁ¬Ðø¶ÁÈ¡ÖÐµÄ×îºóÒ»¸ö½áÊøÖÜÆÚ*/
   /*²ÎÊý: ÎÞ*/
 /*·µ»ØÖµ: ÎÞ*/
/*-----------------------------------------------*/
/**/*/
/*void noAck(void)*/
/*{*/
	
	/*SCCB_SID_H();	*/
	/*delay_us(500);*/
	
	/*SCCB_SIC_H();	*/
	/*delay_us(500);*/
	
	/*SCCB_SIC_L();	*/
	/*delay_us(500);*/
	
	/*SCCB_SID_L();	*/
	/*delay_us(500);*/

/*}*/

/*/**/
/*-----------------------------------------------*/
   /*¹¦ÄÜ: Ð´ÈëÒ»¸ö×Ö½ÚµÄÊý¾Ýµ½SCCB*/
   /*²ÎÊý: Ð´ÈëÊý¾Ý*/
 /*·µ»ØÖµ: ·¢ËÍ³É¹¦·µ»Ø1£¬·¢ËÍÊ§°Ü·µ»Ø0*/
/*-----------------------------------------------*/
/**/*/
/*unsigned char SCCBwriteByte(unsigned char m_data)*/
/*{*/
	/*unsigned char j,tem;*/

	/*for(j=0;j<8;j++) //Ñ­»·8´Î·¢ËÍÊý¾Ý*/
	/*{*/
		/*if((m_data<<j)&0x80)*/
		/*{*/
			/*SCCB_SID_H();	*/
		/*}*/
		/*else*/
		/*{*/
			/*SCCB_SID_L();	*/
		/*}*/
		/*delay_us(500);*/
		/*SCCB_SIC_H();	*/
		/*delay_us(500);*/
		/*SCCB_SIC_L();	*/
		/*delay_us(500);*/

	/*}*/
	/*delay_us(100);*/
	/*SCCB_SID_IN;[>ÉèÖÃSDAÎªÊäÈë<]*/
	/*delay_us(500);*/
	/*SCCB_SIC_H();	*/
	/*delay_us(100);*/
	/*if(SCCB_SID_STATE){tem=0;}   //SDA=1·¢ËÍÊ§°Ü£¬·µ»Ø0}*/
	/*else {tem=1;}   //SDA=0·¢ËÍ³É¹¦£¬·µ»Ø1*/
	/*SCCB_SIC_L();	*/
	/*delay_us(500);	*/
        /*SCCB_SID_OUT;[>ÉèÖÃSDAÎªÊä³ö<]*/

	/*return (tem);  */
/*}*/

/*/**/
/*-----------------------------------------------*/
   /*¹¦ÄÜ: Ò»¸ö×Ö½ÚÊý¾Ý¶ÁÈ¡²¢ÇÒ·µ»Ø*/
   /*²ÎÊý: ÎÞ*/
 /*·µ»ØÖµ: ¶ÁÈ¡µ½µÄÊý¾Ý*/
/*-----------------------------------------------*/
/**/*/
/*unsigned char SCCBreadByte(void)*/
/*{*/
	/*unsigned char read,j;*/
	/*read=0x00;*/
	
	/*SCCB_SID_IN;[>ÉèÖÃSDAÎªÊäÈë<]*/
	/*delay_us(500);*/
	/*for(j=8;j>0;j--) //Ñ­»·8´Î½ÓÊÕÊý¾Ý*/
	/*{		     */
		/*delay_us(500);*/
		/*SCCB_SIC_H();*/
		/*delay_us(500);*/
		/*read=read<<1;*/
		/*if(SCCB_SID_STATE) */
		/*{*/
			/*read=read+1;*/
		/*}*/
		/*SCCB_SIC_L();*/
		/*delay_us(500);*/
	/*}	*/
	/*return(read);*/
/*}*/

