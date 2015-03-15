#include "stm32f4xx.h"
#include "camera_peripherals.h"
#include "fifo_peripherals.h"

int main(void) {

  
  initCameraClk();
  initFifoClk();

  while(1); // Don't wait to exit

	return 0;
}

