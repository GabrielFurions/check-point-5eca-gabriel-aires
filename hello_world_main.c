#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#define PDF_DISPLAY_DELAY_MS 5000

// Estrutura para simular dados de um PDF
typedef struct {
    char nome[30];
    int idade;
    char cargo[30];
} PDFData;

SemaphoreHandle_t xSemaphore = NULL;

// Função para exibir dados em formato de tabela
void exibir_tabela(PDFData *dados, int num_registros)
{
    printf("\n");
    printf("+------------------------------+-------+------------------------------+\n");
    printf("| %-28s | %-5s | %-28s |\n", "Nome", "Idade", "Cargo");
    printf("+------------------------------+-------+------------------------------+\n");
    
    for (int i = 0; i < num_registros; i++)
    {
        printf("| %-28s | %-5d | %-28s |\n", 
               dados[i].nome, 
               dados[i].idade, 
               dados[i].cargo);
    }
    
    printf("+------------------------------+-------+------------------------------+\n");
    printf("\n");
}

// Função para simular leitura de PDF
void ler_pdf_simulado(PDFData *dados, int *num_registros)
{
    // Simulando dados extraídos de um PDF
    strncpy(dados[0].nome, "GABRIEL Pessoa Aires", sizeof(dados[0].nome) - 1);
    dados[0].nome[sizeof(dados[0].nome) - 1] = '\0';
    dados[0].idade = 22;
    strncpy(dados[0].cargo, "Engenheiro de Software", sizeof(dados[0].cargo) - 1);
    dados[0].cargo[sizeof(dados[0].cargo) - 1] = '\0';
    
    strncpy(dados[1].nome, "Maria Silva", sizeof(dados[1].nome) - 1);
    dados[1].nome[sizeof(dados[1].nome) - 1] = '\0';
    dados[1].idade = 28;
    strncpy(dados[1].cargo, "Analista de Sistemas", sizeof(dados[1].cargo) - 1);
    dados[1].cargo[sizeof(dados[1].cargo) - 1] = '\0';
    
    strncpy(dados[2].nome, "João Santos", sizeof(dados[2].nome) - 1);
    dados[2].nome[sizeof(dados[2].nome) - 1] = '\0';
    dados[2].idade = 35;
    strncpy(dados[2].cargo, "Gerente de Projetos", sizeof(dados[2].cargo) - 1);
    dados[2].cargo[sizeof(dados[2].cargo) - 1] = '\0';
    
    strncpy(dados[3].nome, "Ana Costa", sizeof(dados[3].nome) - 1);
    dados[3].nome[sizeof(dados[3].nome) - 1] = '\0';
    dados[3].idade = 26;
    strncpy(dados[3].cargo, "Desenvolvedora", sizeof(dados[3].cargo) - 1);
    dados[3].cargo[sizeof(dados[3].cargo) - 1] = '\0';
    
    *num_registros = 4;
}

void Task1(void *pvParameters)
{
    PDFData dados[10];
    int num_registros = 0;
    
    while (1)
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            printf("[Tarefa 1] Lendo dados do PDF simulado...\n");
            ler_pdf_simulado(dados, &num_registros);
            printf("[Tarefa 1] Exibindo dados em formato de tabela:\n");
            exibir_tabela(dados, num_registros);
            vTaskDelay(pdMS_TO_TICKS(PDF_DISPLAY_DELAY_MS));
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
