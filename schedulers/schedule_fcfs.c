#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../general/task.h"
#include "../general/list.h"
#include "../general/cpu.h"

static node *head = NULL, *last = NULL;

//return the index of list position or -1 for error
int add(char *name, int priority, int burst){
  static int tid = 0;
  int check = 0;

  Task *task_ptr = malloc(sizeof(Task));
  if(task_ptr == NULL){
    printf("Failure allocated task\n");
    return -1;
  }

  task_ptr->name = strdup(name);
  task_ptr->tid = tid;
  task_ptr->priority = priority;
  task_ptr->burst = burst;

    if((check = insert(&last, task_ptr)) < 0){
      printf("error adding task\n");
      return -1;
    }
    if(check == 1){
      head = last;
    }

  tid++;
  return 0;
}

void schedule(){
  node *temp = head;
  while(temp != NULL){
    int slice = temp->task->burst;
    run(temp->task, slice);
    temp = temp->next;
    delete(&head, head->task);
    head = temp;
  }
  if(!temp){
    printf("list cleared\n");
  }
  if(!head){
    printf("list cleared\n");
  }
}



