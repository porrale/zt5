#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 state is off */

}

/* Led testigo */
static void vLedTestigo(void *pvParameters) {
	bool LedState = false;

	while (1) {
		Board_LED_Set(0, LedState);
		LedState = (bool) !LedState;

		/* About a 3Hz on/off toggle rate */
		//vTaskDelay(configTICK_RATE_HZ / 6);

		/* Apaga y prende cada 3 segundos */
		vTaskDelay(3000 / portTICK_RATE_MS);
	}
}

/* UART (or output) thread */
static void vUARTTask(void *pvParameters) {
	int tickCnt = 0;

	while (1) {
		DEBUGOUT("Tick: %d\r\n", tickCnt);
		tickCnt++;

		/* About a 1s delay here */
		vTaskDelay(configTICK_RATE_HZ);
	}
}

/*****************************************************************************
 * Funciones públicas
 ****************************************************************************/

/**
 * @brief	Rutina de main
 * @return	Nada, la función nunca saldrá
 */
int main(void)
{
	prvSetupHardware();

	/* Tarea del Led testigo */
	xTaskCreate(vLedTestigo, (signed char *) "vTaskLedTestigo",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* UART output thread, simply counts seconds */
	xTaskCreate(vUARTTask, (signed char *) "vTaskUart",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* Empieza el scheduler */
	vTaskStartScheduler();

	/* El código nunca debe llegar acá */
	return 1;
}

/**
 * @}
 */
