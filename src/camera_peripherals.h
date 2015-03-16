#ifndef CAMERA_PERIPHERALS_H_
#define CAMERA_PERIPHERALS_H_

// SIOC_PORT B
// SIOC_PIN  0

// HREF_PORT B
// HREF_PIN  0

void initCameraClk(void);
void configure_GPIO_for_SIOC(void);
void initTim4ForCameraClk(uint16_t period, uint16_t prescaler);
void initPWMForCameraClk(uint16_t period);

#endif /* CAMERA_PERIPHERALS_H_ */
