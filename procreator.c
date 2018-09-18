#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main(int argc, char *argv[]){
  int qty_process = 0;
  int process[64];
  int id;

  if(argc == 1){
    printf(1, "Wrong format\n");
    printf(1, "qty_process tickets tickets tickets");
    exit();
  }

  qty_process = atoi(argv[1]);

  for(int i = 0; i < qty_process; i++){
    process[i] = atoi(argv[i+2]);
  }

  for(int i = 0; i < qty_process; i++){
    printf(1, "Process %d tickets: %d\n", i, process[i]);
    id = fork(process[i]);
    if(id == 0){
      for(;;);
      exit();
    }
    if(id == -1) break;
  }

  for(int i = 0; i < qty_process; i++){
    wait();
  }

  exit();
}
