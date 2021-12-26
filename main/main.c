/* TTP229 Example

	 This example code is in the Public Domain (or CC0 licensed, at your option.)

	 Unless required by applicable law or agreed to in writing, this
	 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
	 CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "ttp229.h"

static const char *TAG = "MAIN";

void app_main(void)
{
	ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d", CONFIG_SCL_GPIO);
	ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d", CONFIG_SDA_GPIO);
	TTP229_t dev;
	TTP229_Init(&dev, CONFIG_SCL_GPIO, CONFIG_SDA_GPIO);

	while(1) {
		uint8_t key = TTP229_GetKey16(&dev); // Non Blocking
		if (key != 0) printf("ttp229.GetKey16=%d\n", key);
		vTaskDelay(1);
	}
}
