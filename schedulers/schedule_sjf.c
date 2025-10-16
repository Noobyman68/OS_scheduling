#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

static node *head = NULL;

int add(char *name, int priority, int burst){
  static int tid = 0;

  Task *task_ptr = malloc(sizeof(Task));
  if(task_ptr == NULL){
    printf("Failure allocated task\n");
    return -1;
  }

  task_ptr->name = strdup(name);
  task_ptr->tid = tid;
  task_ptr->priority = priority;
  task_ptr->burst = burst;

  insert(&head, task_ptr);
  
  tid++;

  printf("Adding Node #%d\n", tid);
  traverse(head);
  printf("\n");

  return 0;
}


void schedule(){
  int count = 0;
  int slice;
  int wait, response, turn_around;
  node *temp;
  Task *lowest;

  while(head){
    lowest = head->task;
    temp = head->next;

    while(temp){
      if(temp->task->burst < lowest->burst){
        lowest = temp->task;
      }
      temp = temp->next;
    }
    slice = lowest->burst;

    wait = count;
    response = count;

    run(lowest,lowest->burst);
    delete(&head, lowest);

    count += slice;
    turn_around = count;

    printf("Waiting Time: %d\n", wait);
    printf("Turnaround Time: %d\n", turn_around);
    printf("Response Time: %d\n", response);
  } 
}
