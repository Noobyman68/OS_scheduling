#include <stdio.h>
#include <stdlib.h>

#include "../general/task.h"
#include "../general/list.h"
#include "../general/cpu.h"

int tid = 0;
node *head;
node *last;

//return the index of list position or -1 for error
int add(char *name, int priority, int burst){
  int check = 0;
  printf("Creating task\n");
  Task new_task = {name, tid, priority, burst};
  Task *task_ptr = &new_task; 
  printf("task created\n");

  if(tid){
    printf("insert starting\n");
    if((check = insert(&last, task_ptr)) < 0){
      printf("error adding task\n");
      return -1;
    }
    printf("insert ending\n");
  }else{
    printf("adding head\n");
    head->task = task_ptr;
    head->next = NULL;
    last = head;
    printf("Head added\n");
  }
  tid++;
  return 0;
}

void schedule(){
  printf("traversing\n");
  traverse(head);
}



