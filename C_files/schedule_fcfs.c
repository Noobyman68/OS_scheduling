#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

int tid = 0;
node *head;
node *last;

//return the index of list position or -1 for error
int add(char *name, int priority, int burst){
  int check = 0;
  Task new_task = {name, tid, priority, burst};

  if(tid){
    if((check = insert(&last, &new_task)) < 0){
      printf("error adding task\n");
      return -1
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
  traverse(head)
}



