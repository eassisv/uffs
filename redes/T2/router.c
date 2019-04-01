#include "router.h"
#include <stdio.h>
#include <string.h>

int routerInitialize(int routerId, int neighborsList[],
                     int distanceOfNeighbor[], int availableNeighbors[],
                     int distanceVectorsTable[][MAX_ROUTERS_QT],
                     const char *linksFile, Router neighborConfig[],
                     const char *routersConfigFile, int routingTable[]) {

  FILE *f = fopen(linksFile, "r");
  if (f == NULL) {
    return -1;
  }

  /*  Inicializa todos os vetores distância com -1 e a distancia para todos
     possíveis com -1 também, indicando não conhecer uma rota até o destino  */

  for (int i = 0; i < MAX_ROUTERS_QT; i++) {
    distanceOfNeighbor[i] = INF;
    for (int j = 0; j < MAX_ROUTERS_QT; j++) {
      distanceVectorsTable[i][j] = INF;
    }
  }

  distanceVectorsTable[routerId][routerId] = 0;
  distanceOfNeighbor[routerId] = 0;
  routingTable[routerId] = routerId;

  int numberOfNeighbors = 0;
  int src, dest, weight;
  while (fscanf(f, "%d %d %d", &src, &dest, &weight) != EOF) {
    dest -= 1;
    src -= 1;
    if (dest == routerId) {
      int swap = dest;
      dest = src;
      src = swap;
    }
    if (src == routerId) {
      /*  Decrementa o indice, pois no vetor o indice inicia em 0  */
      neighborsList[numberOfNeighbors] = dest;
      numberOfNeighbors += 1;
      distanceVectorsTable[routerId][dest] = weight;
      distanceOfNeighbor[dest] = weight;
      routingTable[dest] = dest;
    }
  }

  fclose(f);

  f = fopen(routersConfigFile, "r");
  if (f == NULL) {
    return -1;
  }

  int id, port;
  char ip[20];

  for (; fscanf(f, "%d %d %s", &id, &port, ip) != EOF;) {
    id -= 1;
    if (distanceOfNeighbor[id] != INF || id == routerId) {
      neighborConfig[id].port = port;
      strcpy(neighborConfig[id].ip, ip);
    }
  }
  fclose(f);

  return numberOfNeighbors;
}

void packageQueueInitializer(PQueue *queue) {
  (*queue).begin = (*queue).end = (*queue).count = 0;
}

int packagePush(PQueue *queue, Package package) {
  if ((*queue).count < PKG_QUEUE_SIZE) {
    (*queue).queue[(*queue).end] = package;
    (*queue).end = ((*queue).end + 1) % PKG_QUEUE_SIZE;
    (*queue).count += 1;
    return 1;
  }
  return 0;
}

int packagePop(PQueue *queue, Package *buf) {
  if ((*queue).count == 0) {
    return 0;
  }
  *buf = (*queue).queue[(*queue).begin];
  (*queue).begin = ((*queue).begin + 1) % PKG_QUEUE_SIZE;
  (*queue).count -= 1;
  return 1;
}

void timerQueueInitializer(TimerQueue *queue) {
  (*queue).begin = (*queue).end = (*queue).count = 0;
}

int timerPush(TimerQueue *queue, Timer timer) {
  if ((*queue).count < PKG_QUEUE_SIZE) {
    (*queue).queue[(*queue).end] = timer;
    (*queue).end = ((*queue).end + 1) % PKG_QUEUE_SIZE;
    (*queue).count += 1;
    return 1;
  }
  return 0;
}

int timerPop(TimerQueue *queue, Timer *buf) {
  if ((*queue).count == 0) {
    return 0;
  }
  *buf = (*queue).queue[(*queue).begin];
  (*queue).begin = ((*queue).begin + 1) % PKG_QUEUE_SIZE;
  (*queue).count -= 1;
  return 1;
}