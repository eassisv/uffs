#include <arpa/inet.h>
#include <limits.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <unistd.h>
#include "router.h"

void* sender(void* senderArgs);
void* receiver(void* receiverArgs);
void* unpacker(void* unpackerArgs);
void* distanceVectorUpdater(void* updaterArgs);
void* periodicVectorSender(void* pVecSenderArgs);
void* neighborsTimersCheker(void* neighborsTimerCheckerArgs);

int sock;
int routerId;
int routingTable[MAX_ROUTERS_QT];
int neighborsList[MAX_ROUTERS_QT], numberOfNeighbors;
int availableNeighbors[MAX_ROUTERS_QT];
int distanceOfNeighbor[MAX_ROUTERS_QT];
time_t neighborsTimers[MAX_ROUTERS_QT];
int distanceVectorsTable[MAX_ROUTERS_QT][MAX_ROUTERS_QT];
Router neighborConfig[MAX_ROUTERS_QT];
PQueue outQueue, inQueue, vecQueue;
TimerQueue neighborTimersQueue;
pthread_t senderHandle, receiverHandle, unpackerHandle, updaterHandle,
    pVecSenderHandle, verifierHandle;
pthread_mutex_t mutexOutQueue, mutexInQueue, mutexVecQueue;
pthread_mutex_t mutexNeighborsQueue, mutexPrint;
sem_t semOutQueue, semInQueue, semVecQueue;
sem_t semNeighborsQueue;

int main(int argc, char const* argv[]) {
  if (argc != 2) {
    printf("Execute %s <id do roteador>\n", *argv);
    return 0;
  }

  routerId = atoi(argv[1]) - 1;

  memset(neighborConfig, 0, sizeof(neighborConfig));

  numberOfNeighbors =
      routerInitialize(routerId, neighborsList, distanceOfNeighbor,
                       availableNeighbors, distanceVectorsTable, "links.config",
                       neighborConfig, "routers.config", routingTable);

  for (int i = 0; i < numberOfNeighbors; i++) {
    availableNeighbors[neighborsList[i]] = 1;
  }

  // for (int i = 0; i < numberOfNeighbors; i++) {
  //   printf("Vizinho %d\n", neighborsList[i] + 1);
  // }

  // printf("%d\n", numberOfNeighbors);
  // for (int i = 0; i < numberOfNeighbors; i++) {
  //   int id = neighborsList[i];
  //   printf("Visinho: %d\nCusto: %d\nIP: %s\nPorta: %d\n", id + 1,
  //          distanceOfNeighbor[id], neighborConfig[id].ip,
  //          neighborConfig[id].port);
  // }

  if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    puts("Erro ao executa socket na main");
    return 0;
  }

  packageQueueInitializer(&outQueue);
  packageQueueInitializer(&inQueue);
  packageQueueInitializer(&vecQueue);
  timerQueueInitializer(&neighborTimersQueue);

  if (sem_init(&semOutQueue, 0, 0) == -1) {
    puts("Erro ao iniciar semOutQueue");
    return 0;
  }
  if (sem_init(&semInQueue, 0, 0) == -1) {
    puts("Erro ao iniciar semInQueue");
    return 0;
  }
  if (sem_init(&semVecQueue, 0, 0) == -1) {
    puts("Erro ao iniciar semInQueue");
    return 0;
  }
  if (sem_init(&semNeighborsQueue, 0, 0) == -1) {
    puts("Erro ao iniciar semInQueue");
    return 0;
  }

  if (pthread_mutex_init(&mutexOutQueue, NULL) != 0) {
    puts("Erro ao iniciar mutexOutQueue");
    return 0;
  }
  if (pthread_mutex_init(&mutexInQueue, NULL) != 0) {
    puts("Erro ao iniciar mutexInQueue");
    return 0;
  }
  if (pthread_mutex_init(&mutexVecQueue, NULL) != 0) {
    puts("Erro ao iniciar mutexVecQueue");
    return 0;
  }
  if (pthread_mutex_init(&mutexNeighborsQueue, NULL) != 0) {
    puts("Erro ao iniciar mutexNeighborsQueue");
    return 0;
  }

  if (pthread_mutex_init(&mutexPrint, NULL) != 0) {
    puts("Erro ao iniciar mutexPrint");
    return 0;
  }

  if (pthread_create(&senderHandle, NULL, sender, NULL) != 0) {
    puts("Erro ao criar thread sender");
    return 0;
  }
  if (pthread_create(&receiverHandle, NULL, receiver, NULL) != 0) {
    puts("Erro ao criat thread receiver");
    return 0;
  }
  if (pthread_create(&unpackerHandle, NULL, unpacker, NULL) != 0) {
    puts("Erro ao criar thread receiver");
    return 0;
  }
  if (pthread_create(&updaterHandle, NULL, distanceVectorUpdater, NULL) != 0) {
    puts("Erro ao criar thread sender");
    return 0;
  }

  if (pthread_create(&pVecSenderHandle, NULL, periodicVectorSender, NULL) !=
      0) {
    puts("Erro ao criar thread sender");
    return 0;
  }

  if (pthread_create(&verifierHandle, NULL, neighborsTimersCheker, NULL) != 0) {
    puts("Erro ao criar thread sender");
    return 0;
  }

  char message[MSG_SIZE];
  int dest;
  Package pack;
  pack.src = routerId;
  pack.type = MSG;

  for (int i = 0; i < MAX_ROUTERS_QT; i++) {
    pack.distanceVector[i] = distanceOfNeighbor[i];
  }

  for (;;) {
    // printf("Mensagem: ");

    memset(message, 0, sizeof(message));
    fgets(message, MSG_SIZE, stdin);
    message[strlen(message) - 1] = '\0';  // Retira o \n do fim da mensagem
    // printf("Destino: ");

    if (strcmp(message, "tabela") == 0) {
      pthread_mutex_lock(&mutexPrint);
      printf("Tabela de Roteamento\n");
      for (int i = 0; i < MAX_ROUTERS_QT; i++) {
        if (distanceVectorsTable[routerId][i] != INF) {
          printf("[%d] = %d\n", i + 1, routingTable[i] + 1);
        }
      }
      puts("\nVetor distância");
      for (int i = 0; i < MAX_ROUTERS_QT; i++) {
        if (distanceVectorsTable[routerId][i] != INF) {
          printf("D(%d) = %d\n", i + 1, distanceVectorsTable[routerId][i]);
        }
      }
      printf("\n\n");
      pthread_mutex_unlock(&mutexPrint);
      continue;
    }

    scanf("%d", &dest);
    getchar();

    if (distanceVectorsTable[routerId][dest - 1] == INF ||
        dest >= MAX_ROUTERS_QT) {
      puts("Destino inalcançável");
      continue;
    }

    pack.dest = dest - 1;
    strcpy(pack.message, message);

    pthread_mutex_lock(&mutexOutQueue);
    packagePush(&outQueue, pack);
    pthread_mutex_unlock(&mutexOutQueue);

    sem_post(&semOutQueue);
  }

  return 0;
}

void* sender(void* senderArgs) {
  Package pack;
  int nextHop;
  struct sockaddr_in sockDest;

  sockDest.sin_family = AF_INET;

  for (;;) {
    sem_wait(&semOutQueue);

    pthread_mutex_lock(&mutexOutQueue);
    packagePop(&outQueue, &pack);
    pthread_mutex_unlock(&mutexOutQueue);

    // Verificar se o roteador destino ainda está disponível
    nextHop = pack.type == CONTROL ? pack.dest : routingTable[pack.dest];

    if (distanceVectorsTable[routerId][pack.dest] == INF) {
      pthread_mutex_lock(&mutexPrint);
      printf("Caminho para %d não conhecido\n\n", pack.dest + 1);
      pthread_mutex_unlock(&mutexPrint);
      continue;
    }

    sockDest.sin_port = htons((uint16_t)neighborConfig[nextHop].port);
    if (inet_aton(neighborConfig[nextHop].ip, &sockDest.sin_addr) == 0) {
      puts("Erro ao executar inet_aton na thread sender");
      exit(0);
    }

    // printf("Enviando pacote do tipo %d de %d para %d\n", pack.type,
    //        pack.src + 1, pack.dest + 1);

    if (sendto(sock, &pack, sizeof(Package), 0, (struct sockaddr*)&sockDest,
               sizeof(sockDest)) == -1) {
      puts("Erro ao executar sendto na thread sender");
      exit(0);
    }

    pthread_mutex_lock(&mutexPrint);
    if (pack.type != CONTROL)
      printf("Enviando pacote para %d\n\n", pack.dest + 1);
    pthread_mutex_unlock(&mutexPrint);
  }
}

void* receiver(void* receiverArgs) {
  struct sockaddr_in sockMe;
  Package pack;

  sockMe.sin_family = AF_INET;
  sockMe.sin_port = htons((uint16_t)neighborConfig[routerId].port);
  if (inet_aton(neighborConfig[routerId].ip, &sockMe.sin_addr) == 0) {
    puts("Erro ao executar inet_aton na thread receiver");
    exit(0);
  }

  if (bind(sock, (struct sockaddr*)&sockMe, sizeof(sockMe)) == -1) {
    puts("Erro ao executar bind na thread receiver");
    exit(0);
  }

  for (;;) {
    if (recv(sock, &pack, sizeof(pack), 0) == -1) {
      puts("Erro ao executar recv na thread receiver");
      exit(0);
    }
    pthread_mutex_lock(&mutexPrint);
    if (pack.type != CONTROL)
      printf("Recebi pacote do roteador %d\n\n", pack.src + 1);
    pthread_mutex_unlock(&mutexPrint);

    pthread_mutex_lock(&mutexInQueue);
    packagePush(&inQueue, pack);
    pthread_mutex_unlock(&mutexInQueue);

    sem_post(&semInQueue);
  }
}

void* unpacker(void* unpackagerArgs) {
  Package pack;
  for (;;) {
    sem_wait(&semInQueue);

    pthread_mutex_lock(&mutexInQueue);
    packagePop(&inQueue, &pack);
    pthread_mutex_unlock(&mutexInQueue);

    // printf("Mensagem tipo %d recebida de roteador %d\n", pack.type,
    //        pack.src + 1);

    if (pack.dest == routerId) {
      if (pack.type == MSG) {
        pack.dest = pack.src;
        pack.src = routerId;
        pack.type = ACK;

        pthread_mutex_lock(&mutexPrint);
        printf("Mensagem: %s\n\n", pack.message);
        pthread_mutex_unlock(&mutexPrint);

        pthread_mutex_lock(&mutexOutQueue);
        packagePush(&outQueue, pack);
        pthread_mutex_unlock(&mutexOutQueue);

        sem_post(&semOutQueue);

      } else if (pack.type == CONTROL) {
        availableNeighbors[pack.src] = 1;
        neighborsTimers[pack.src] = time(NULL);

        pthread_mutex_lock(&mutexVecQueue);
        packagePush(&vecQueue, pack);
        pthread_mutex_unlock(&mutexVecQueue);

        sem_post(&semVecQueue);

      } else if (pack.type == ACK) {
        pthread_mutex_lock(&mutexPrint);
        printf("Resposta recebida de roteador %d\n\n", pack.src + 1);
        pthread_mutex_unlock(&mutexPrint);
      }
    } else {
      pthread_mutex_lock(&mutexOutQueue);
      packagePush(&outQueue, pack);
      pthread_mutex_unlock(&mutexOutQueue);

      pthread_mutex_lock(&mutexPrint);
      printf("Roteador %d repassando pacote de %d para %d via roteador %d\n\n",
             routerId + 1, pack.src + 1, pack.dest + 1,
             routingTable[pack.dest] + 1);
      pthread_mutex_unlock(&mutexPrint);

      sem_post(&semOutQueue);
    }
  }
}

void* distanceVectorUpdater(void* updaterArgs) {
  Package pack;
  int *distanceVector, change, routingChange, oldValue;
  time_t changeTime;
  struct tm* gtm;
  char timeToChar[50];

  for (;;) {
    sem_wait(&semVecQueue);

    pthread_mutex_lock(&mutexVecQueue);
    packagePop(&vecQueue, &pack);
    pthread_mutex_unlock(&mutexVecQueue);

    change = routingChange = 0;
    distanceVector = pack.distanceVector;
    for (int i = 0; i < MAX_ROUTERS_QT; i++) {
      if (i == routerId)
        continue;
      /*  Atualiza o vetor distância de src na tabela de vetores distância  */
      distanceVectorsTable[pack.src][i] = distanceVector[i];
      /*  Se a distância até o roteador i melhora apartir do vetor distância do
       * pack.src, atualizo meu vetor distancia e minha tabela de roteamento  */

      // printf("distanceVector[%d] + distanceOfNeighbor[%d] = %d", i, )

      if (distanceVector[i] + distanceOfNeighbor[pack.src] <
          distanceVectorsTable[routerId][i]) {
        // printf("Melhorando distância para %d atrávez de %d\n", i + 1,
        //  pack.src + 1);
        distanceVectorsTable[routerId][i] =
            distanceVector[i] + distanceOfNeighbor[pack.src];
        routingTable[i] = pack.src;
        change = routingChange = 1;
      } else if (distanceVector[i] + distanceOfNeighbor[pack.src] >
                 distanceVectorsTable[routerId][i]) {
        if (routingTable[i] == pack.src) {
          oldValue = distanceVectorsTable[routerId][i];
          if (distanceVector[i] + distanceOfNeighbor[pack.src] >= INF) {
            distanceVectorsTable[routerId][i] = INF;
          } else {
            distanceVectorsTable[routerId][i] =
                distanceVector[i] + distanceOfNeighbor[pack.src];
          }

          for (int j = 0; j < numberOfNeighbors; j++) {
            if (distanceVectorsTable[neighborsList[j]][i] +
                    distanceOfNeighbor[neighborsList[j]] <
                distanceVectorsTable[routerId][i]) {
              distanceVectorsTable[routerId][i] =
                  distanceVectorsTable[neighborsList[j]][i] +
                  distanceOfNeighbor[neighborsList[j]];
              routingTable[i] = neighborsList[j];
              change = routingChange = 1;
            }
          }
          routingChange = change =
              change == 1 || distanceVectorsTable[routerId][i] != oldValue ? 1
                                                                           : 0;
        }
      }
    }

    if (change == 1) {
      // printf("Change = 1\n");
      pack.src = routerId;
      pack.type = CONTROL;
      for (int i = 0; i < MAX_ROUTERS_QT; i++) {
        pack.distanceVector[i] = distanceVectorsTable[routerId][i];
      }

      for (int i = 0; i < numberOfNeighbors; i++) {
        if (availableNeighbors[neighborsList[i]] == 0)
          continue;
        pack.dest = neighborsList[i];
        pthread_mutex_lock(&mutexOutQueue);
        packagePush(&outQueue, pack);
        pthread_mutex_unlock(&mutexOutQueue);

        sem_post(&semOutQueue);
      }
    } else {
      // puts("Change = 0");
    }
    if (routingChange == 1) {
      changeTime = time(NULL);
      gtm = localtime(&changeTime);
      strftime(timeToChar, 50, "Alteração: %T", gtm);

      pthread_mutex_lock(&mutexPrint);
      puts(timeToChar);
      for (int i = 0; i < MAX_ROUTERS_QT; i++) {
        if (distanceVectorsTable[routerId][i] != INF) {
          printf("[%d] = %d\n", i + 1, routingTable[i] + 1);
        }
      }
      for (int i = 0; i < MAX_ROUTERS_QT; i++) {
        if (distanceVectorsTable[routerId][i] != INF) {
          printf("D(%d) = %d\n", i + 1, distanceVectorsTable[routerId][i]);
        }
      }
      pthread_mutex_unlock(&mutexPrint);
    }
  }
}

void* periodicVectorSender(void* pVecSenderArgs) {
  Package pack;
  pack.type = CONTROL;
  pack.src = routerId;

  for (;;) {
    for (int i = 0; i < MAX_ROUTERS_QT; i++) {
      pack.distanceVector[i] = distanceVectorsTable[routerId][i];
    }

    for (int i = 0; i < numberOfNeighbors; i++) {
      if (availableNeighbors[neighborsList[i]] == 0)
        continue;

      pack.dest = neighborsList[i];

      pthread_mutex_lock(&mutexOutQueue);
      packagePush(&outQueue, pack);
      pthread_mutex_unlock(&mutexOutQueue);

      sem_post(&semOutQueue);
    }

    sleep(VECTOR_SEND_PERIOD);
  }
}

void* neighborsTimersCheker(void* neighborsTimerCheckerArgs) {
  Package diePack;

  diePack.type = CONTROL;

  for (int i = 0; i < numberOfNeighbors; i++) {
    neighborsTimers[neighborsList[i]] = time(NULL);
  }

  for (;;) {
    sleep(3 * VECTOR_SEND_PERIOD);
    for (int i = 0; i < numberOfNeighbors; i++) {
      if (availableNeighbors[neighborsList[i]] == 0)
        continue;
      if (difftime(time(NULL), neighborsTimers[neighborsList[i]]) >=
          (double)(3 * VECTOR_SEND_PERIOD)) {
        // printf("Timer %d Expirou\n", neighborsList[i] + 1);
        availableNeighbors[neighborsList[i]] = 0;

        for (int j = 0; j < MAX_ROUTERS_QT; j++) {
          diePack.distanceVector[j] = INF;
        }

        diePack.src = neighborsList[i];
        diePack.dest = routerId;

        pthread_mutex_lock(&mutexVecQueue);
        packagePush(&vecQueue, diePack);
        pthread_mutex_unlock(&mutexVecQueue);

        sem_post(&semVecQueue);
      }
    }
  }
}
