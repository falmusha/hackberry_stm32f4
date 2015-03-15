#ifndef CAMERA_PERIPHERALS_H_
#define CAMERA_PERIPHERALS_H_

void initCameraClk(void);
void initGPIOForCameraClk(void);
void initTim4ForCameraClk(uint16_t period, uint16_t prescaler);
void initPWMForCameraClk(uint16_t period);

#endif /* CAMERA_PERIPHERALS_H_ */
