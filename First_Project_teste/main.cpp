/* Scheduler includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

/* Library includes. */
#include <stm32f4xx.h>

//#include <iostream>
//#include <string>

//using namespace std;

void prvSetupLed(void);

void vLEDTask( void *pvParameters )
{
	
	prvSetupLed();
	for( ;; )
	{
//		string a("ola"), b("aa"), c;
//		c = a + b;
//		cout << "ola" << endl;
		/* Toogle the LED bit */
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		vTaskDelay(500 / portTICK_RATE_MS);	
//		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
//		vTaskDelay(500 / portTICK_RATE_MS);	
		GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
		vTaskDelay(500 / portTICK_RATE_MS);	
//		GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
//		vTaskDelay(500 / portTICK_RATE_MS);	
	}
}


int main()
{
	portBASE_TYPE task1_pass;
	
	/* Create Task */
	task1_pass = xTaskCreate( vLEDTask, "Task_Led", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	
	if( task1_pass == pdPASS )
	{
			/* Start the Scheduler */ 
			vTaskStartScheduler(); 
	}
	else
	{
			/* ERROR! Creating the Tasks */
			return -2;
	}
	
	return 0;
}


void prvSetupLed(void)
{
	// GPIO structure declaration
	GPIO_InitTypeDef GPIO_InitStruct;
	// Enabling GPIO peripheral clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	// GPIO peripheral properties specification
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; // LED3 GPIO pin
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; // output
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // clock speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // push/pull 
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; // pullup/pulldown resistors inactive
	// Setting GPIO peripheral corresponding bits
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}
