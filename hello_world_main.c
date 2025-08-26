#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

SemaphoreHandle_t xSemaphore = NULL;

void Task1(void *pvParameters)
{
    while (1)
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            printf("[Tarefa 1] Executou - GABRIEL Pessoa\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            xSemaphoreGive(xSemaphore);
            vTaskDelay(pdMS_TO_TICKS(10)); // Pequeno delay para alternância
        }
    }
}

void Task2(void *pvParameters)
{
    while (1)
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            printf("[Tarefa 2] Executou - GABRIEL Pessoa\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            xSemaphoreGive(xSemaphore);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}

void Task3(void *pvParameters)
{
    while (1)
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            printf("[Tarefa 3] Executou - GABRIEL Pessoa\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            xSemaphoreGive(xSemaphore);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}

void app_main(void)
{
    xSemaphore = xSemaphoreCreateBinary();

    if (xSemaphore == NULL)
    {
        printf("Falha ao criar semáforo\n");
        return;
    }

    xSemaphoreGive(xSemaphore);

    xTaskCreate(Task1, "Task1", 2048, NULL, 2, NULL);
    xTaskCreate(Task2, "Task2", 2048, NULL, 2, NULL);
    xTaskCreate(Task3, "Task3", 2048, NULL, 2, NULL);
}
