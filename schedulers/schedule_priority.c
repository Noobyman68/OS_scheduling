#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../general/task.h"
#include "../general/list.h"
#include "../general/cpu.h"

static node *head = NULL;

//return the index of list position or -1 for error
int add(char *name, int priority, int burst){
  static int tid = 0;
  int check = 0;
  node *last = head;
  node *cur = NULL;

  Task *task_ptr = malloc(sizeof(Task));
  if(task_ptr == NULL){
    printf("Failure allocated task\n");
    return -1;
  }

  task_ptr->name = strdup(name);
  task_ptr->tid = tid;
  task_ptr->priority = priority;
  task_ptr->burst = burst;

  if(head){
    cur = head;
    while(cur && priority < cur->task->priority){
      last = cur;
      cur = cur->next;
    }
  }

  if(last == head){
    node *newNode = malloc(sizeof(node));
    newNode->task = task_ptr;
    newNode->next = head;
    head = newNode;
    return 0;
  }

  if((check = insert(&last, task_ptr)) < 0){
    printf("error adding task\n");
    return -1;
  }else if(check==1){
    head = last;
  }else{
    last->next = cur;
  }
  printf("[%s] [%d] [%d]\n",last->task->name, last->task->priority, last->task->burst);

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
}
