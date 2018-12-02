#ifndef ROUTER_H
#define ROUTER_H

#include "defs.h"
#include <time.h>

typedef struct _router {
  char ip[20];
  int port;
} Router;

typedef struct _package {
  int id, type, src, dest;
  char message[MSG_SIZE];
  int distanceVector[MAX_ROUTERS_QT];
} Package;

// typedef struct _packageNode {
//   package package;
//   struct _packageNode *prev, *next;
// } packageNode;

// typedef struct _packageQueue {
//   packageNode *first, *last;
//   int size;
// } packageQueue;

typedef struct _PQueue {
  Package queue[PKG_QUEUE_SIZE];
  int begin, end, count;
} PQueue;

typedef struct _Timer {
  time_t timer;
  int neighborId;
} Timer;

typedef struct _TimersQueue {
  Timer queue[TIMER_QUEUE_SIZE];
  int begin, end, count;
} TimerQueue;

void packageQueueInitializer(PQueue *queue);
int routerInitialize(int routerId, int neighborsList[],
                     int distanceOfNeighbor[], int availableNeighbors[],
                     int distanceVectorsTable[][MAX_ROUTERS_QT],
                     const char *linksFile, Router neighborConfig[],
                     const char *routersConfigFile, int routingTable[]);
int packagePush(PQueue *queue, Package package);
int packagePop(PQueue *queue, Package *buf);
void timerQueueInitializer(TimerQueue *queue);
int timerPush(TimerQueue *queue, Timer timer);
int timerPop(TimerQueue *queue, Timer *buf);

// void packageQueueInitializer(packageQueue *queue);
// void packagePush(packageQueue *queue, package package);
// int packagePop(packageQueue *queue, package *buf) {

#endif