#include "FreeRTOS_AVR.h"
#include "basic_io_avr.h"

#define N 5
#define LEFT(x) (x + N - 1) % N
#define RIGHT(x) (x + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

const char *str[3] = {"Thinking", "Hungry", "Eating"};
const TickType_t oneSec = 1000 / portTICK_PERIOD_MS;
uint8_t state[N] = {0, 0, 0, 0, 0}, index[N] = {0, 1, 2, 3, 4}, Mtx = 1;
QueueHandle_t fs[N], mutex, fork;

void philosopher(void *pvParameters);
void takeForks(void *pvParameters);
void tellState(uint8_t i);

void setup() {
  Serial.begin(9600);
  uint8_t i;
  mutex = xQueueCreate(1, sizeof(uint8_t));
  fork = xQueueCreate(1, sizeof(uint8_t));
  if(!mutex || !fork) {
    for(;;);
  }
  for(i = 0; i < N; i++){
    fs[i] = xQueueCreate(1, sizeof(uint8_t));
    if(!fs[i]){
      for(;;);
    }
  }
  for(i = 0; i < N; i++){
    if(pdPASS != xTaskCreate(philosopher, "Philo", 150, index + i, 1, NULL)){
      for(;;);
    }
  }
  if(pdPASS != xTaskCreate(takeForks, "Forks", 100, NULL, 2, NULL)) {
    for(;;);
  }
  vPrintString("Ok\n");
  vTaskStartScheduler();
  for (;;);
}

void philosopher(void *pvParameters) {
  const uint8_t id = *(uint8_t *)pvParameters;

  tellState(id);                                      // Thinking
  vTaskDelay(oneSec);
  
  for(;;){
    xQueueSend(mutex, &Mtx, portMAX_DELAY);             // Get mutex
    
    state[id] = HUNGRY;
    tellState(id);
    vTaskDelay(oneSec);    
    
    xQueueSend(fork, &id, portMAX_DELAY);               // Take forks
    
    xQueueReceive(mutex, &Mtx, portMAX_DELAY);          
    xQueueReceive(fs[id], &Mtx, portMAX_DELAY);

    tellState(id);
    vTaskDelay(oneSec);

    xQueueSend(mutex, &Mtx, portMAX_DELAY);
  
    state[id] = THINKING;
    tellState(id);                                      // Thinking
    vTaskDelay(oneSec);
    
    xQueueSend(fork, &index[LEFT(id)], portMAX_DELAY);  // Test left
    xQueueSend(fork, &index[RIGHT(id)], portMAX_DELAY); // Test right


    xQueueReceive(mutex, &Mtx, portMAX_DELAY);
  }
}

void takeForks(void *pvParameters) {
  uint8_t id;
  for(;;) {
    xQueueReceive(fork, &id, portMAX_DELAY);
    if(state[id] == HUNGRY && state[LEFT(id)] != EATING && state[RIGHT(id)] != EATING){
      state[id] = EATING;
      xQueueSend(fs[id], &Mtx, portMAX_DELAY);
    }
  }
}

void tellState(uint8_t i) {
  vPrintStringAndNumber(str[state[i]], i);
}

void loop() {}
