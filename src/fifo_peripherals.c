#include "stm32f4xx_it.h"
#include "fifo_peripherals.h"

void initFifoClk() {

  /* timer_tick_frequency = TIM4_default_frequency / (prescaler + 1) */
	/* PWM_frequency = timer_tick_frequency / (period + 1) */
	/* period = timer_tick_frequency / PWM_frequency - 1 */

  /* 5.3 Mhz */
  uint16_t period = 3-1;
  uint16_t prescaler = 0;

  initTim3ForFifoClk(period, prescaler);
  initGPIOForFifoClk();
  initPWMForFifoClk(period);

}

void initGPIOForFifoClk(void) {
  
  // Configure GPIO port C pin 12 to output 
  // pin to send clk signal to camera

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;

  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
}

void initTim3ForFifoClk(uint16_t period, uint16_t prescaler) {
  
  //Enable APB2 Peripheral Clock
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  TIM_TimeBaseInitTypeDef timerInitStructure;
  timerInitStructure.TIM_Prescaler = prescaler;
  timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  timerInitStructure.TIM_Period = period;
  timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

  TIM_TimeBaseInit(TIM3, &timerInitStructure);

  TIM_ARRPreloadConfig(TIM3, ENABLE);

  // Enable Timer 3
  TIM_Cmd(TIM3, ENABLE);

}

void initPWMForFifoClk(uint16_t period) {

  uint16_t pulse;

  /* pulse = ((period + 1) * DutyCycle) / 100 - 1 */

  /*pulse = ((period + 1) * 50) / 100 - 1;*/
  pulse = period/2;

  /*if (pulse >= period) {*/
    /*pulse = 1;*/
  /*}*/

  TIM_OCInitTypeDef outputChannelInit;
  outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
  outputChannelInit.TIM_Pulse = pulse;
  outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
  outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM3, &outputChannelInit);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  TIM_CtrlPWMOutputs(TIM3, ENABLE);

}

void configure_FIFO_RRSET() {

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

  
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

}

