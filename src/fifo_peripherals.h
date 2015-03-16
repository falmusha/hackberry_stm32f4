#ifndef FIFO_PERIPHERALS_H_
#define FIFO_PERIPHERALS_H_

// FIFO_RCK_PORT A
// FIFO_RCK_PIN  6

// FIFO_RRST_PORT G
// FIFO_RRST_PIN  15

// FIFO_WRST_PORT B
// FIFO_WRST_PIN  10

// FIFO_DATA_PORT D
// FIFO_DATA_PIN  0:7

#define FIFO_RRST_H() GPIOG->ODR|=(0x1<<15);
#define FIFO_RRST_L() GPIOG->ODR&=~(0x1<<15);

#define FIFO_WRST_H() GPIOB->ODR|=(0x1<<10);
#define FIFO_WRST_L() GPIOB->ODR&=~(0x1<<10);

void initFifoClk(void);
void initGPIOForFifoClk(void);
void initTim3ForFifoClk(uint16_t period, uint16_t prescaler);
void initPWMForFifoClk(uint16_t period);

#endif /* FIFO_PERIPHERALS_H_ */
