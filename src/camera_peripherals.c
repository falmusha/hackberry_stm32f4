#include "stm32f4xx_it.h"
#include "camera_peripherals.h"

  
void initCameraClk() {

  /* timer_tick_frequency = TIM4_default_frequency / (prescaler + 1) */
	/* PWM_frequency = timer_tick_frequency / (period + 1) */
	/* period = timer_tick_frequency / PWM_frequency - 1 */

  uint16_t period = 50;
  uint16_t prescaler = 0;

  initGPIOForCameraClk();
  initTim4ForCameraClk(period, prescaler);
  initPWMForCameraClk(period);

}


void initGPIOForCameraClk(void) {
  
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
  

void initTim4ForCameraClk(uint16_t period, uint16_t prescaler) {
  
  // Enable APB1 Peripheral Clock for Timer 4
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  TIM_TimeBaseInitTypeDef timerInitStructure;
  timerInitStructure.TIM_Prescaler = prescaler;
  timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  timerInitStructure.TIM_Period = period;
  timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  timerInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM4, &timerInitStructure);
  TIM_Cmd(TIM4, ENABLE);

}
  
void initPWMForCameraClk(uint16_t period) {

  uint16_t pulse;

  /* pulse = ((period + 1) * DutyCycle) / 100 - 1 */

  pulse = ((period + 1) * 50) / 100 - 1;

  TIM_OCInitTypeDef outputChannelInit;
  outputChannelInit.TIM_OCMode = TIM_OCMode_PWM2;
  outputChannelInit.TIM_Pulse = pulse;
  outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
  outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_Low;

  TIM_OC1Init(TIM4, &outputChannelInit);
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  TIM_CtrlPWMOutputs(TIM4,ENABLE);

}

