#ifndef FIFO_PERIPHERALS_H_
#define FIFO_PERIPHERALS_H_

void initFifoClk(void);
void initGPIOForFifoClk(void);
void initTim3ForFifoClk(uint16_t period, uint16_t prescaler);
void initPWMForFifoClk(uint16_t period);

#endif /* FIFO_PERIPHERALS_H_ */
