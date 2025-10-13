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
  Task *new_task; 
  new_task->name = name;
  new_task->tid = tid;
  new_task->priority = priority;
  new_task->burst = burst;

  



  if(tid){
    if((check = insert(&last, new_task)) < 0){
      printf("error adding task\n");
      return -1;
    }
  }else{
    head->task = new_task;
    head->next = NULL;
    last = head;
  }
  tid++;
  return 0;
}

void schedule(){
  traverse(head);
}



