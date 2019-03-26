/*
  Implementação do "Sleeping Barber Problem"
  por Éverton de Assis Vieira
  UFFS - Ciência da Computaçao 2018.2
  Disciplina: Sistema Operacionais de Tempo Real
*/

#include "FreeRTOS_AVR.h"
#include "basic_io_avr.h"

#define CHAIRS 2
#define CUSTOMERS 4

const TickType_t halfSec = 1000 / portTICK_PERIOD_MS;
portSHORT customersWatting;

SemaphoreHandle_t semCustomers, semBarber, semMutex;

void barberTask(void* barberArgs);
//void customerTask(void* customerArgs);
void customerProcedure(void* args);

void setup() {
  Serial.begin(9600);

  if (xTaskCreate(barberTask, "Barber", 100, NULL, 1, NULL) == pdFAIL) {
    vPrintString("Problem with barberTask create.\n");
    for (;;) {}
  }

  for (portSHORT i = 0;  i < CUSTOMERS; i++) {
    if (xTaskCreate(customerProcedure, "Customer", 100, NULL, 1, NULL) == pdFAIL) {
      vPrintString("Problem with customerProcedure create.\n");
    }
  }

  //  if (xTaskCreate(customerTask, "Custom", 400, NULL, 1, NULL) == pdFAIL) {
  //    vPrintString("Problem with customerTask create\n");
  //    for (;;) {}
  //  }

  semCustomers = xSemaphoreCreateCounting(CHAIRS, 0);
  semBarber = xSemaphoreCreateBinary();
  semMutex = xSemaphoreCreateMutex();
  customersWatting = 0;

  if (semCustomers == NULL || semBarber == NULL || semMutex == NULL) {
    vPrintString("Problem with semaphores create\n");
    for (;;) {}
  }

  randomSeed(analogRead(0));

  vTaskStartScheduler();
  for (;;) {}
}

void barberTask(void* barberArgs) {
  for (;;) {
    xSemaphoreTake(semCustomers, portMAX_DELAY / portTICK_PERIOD_MS);
    xSemaphoreTake(semMutex, portMAX_DELAY / portTICK_PERIOD_MS);
    vPrintString("The barber has customers waiting.\n");
    customersWatting -= 1;
    xSemaphoreGive(semBarber);
    xSemaphoreGive(semMutex);
    vPrintString("The barber is cutting the customer's hair.\n");
    vTaskDelay(halfSec);
  }
}

void customerProcedure(void* args) {
  for (;;) {
    vTaskDelay(random(200, 1700) / portTICK_PERIOD_MS);
    xSemaphoreTake(semMutex, portMAX_DELAY / portTICK_PERIOD_MS);
    if (xSemaphoreGive(semCustomers) == pdTRUE) {
      if (customersWatting > 0) {
        vPrintString("The barber is cutting hair, customer will wait.\n");
      } else {
        vPrintString("The barbershop is empty, i'm going to wake the barber.\n");
      }
      customersWatting += 1;
      xSemaphoreGive(semMutex);
      xSemaphoreTake(semBarber, portMAX_DELAY / portTICK_PERIOD_MS);
      vPrintString("The barber has cutted my hair.\n");
    } else {
      vPrintString("The barbershop is full, the customer is leaving.\n");
      xSemaphoreGive(semMutex);
    }
  }
}

//void customerTask(void* customerArgs) {
//  vPrintString("Customer.\n");
//
//  vTaskDelay(halfSec);
//
//  for (;;) {
//
//
//    vTaskDelay(1000 / portTICK_PERIOD_MS);
////    vTaskDelay(random(100, 700) / portTICK_PERIOD_MS);
//
//    vPrintString("Aqui estou\n");
//    if( xTaskCreate(customerProcedure, "Curoc", 100, NULL, 1, NULL) == pdFAIL ) {
//      vPrintString("Falho para Criar\n");
//    }
//
////    vPrintString("Task Criada.\n");
//  }
//}



void vApplicationIdleHook( void ) {
  vPrintString("Rodando\n");
}

void loop() {}
