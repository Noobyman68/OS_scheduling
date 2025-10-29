#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

static struct node *head = NULL;

int add(char *name, int priority, int burst){
  static int tid = 0;

  Task *task_ptr = malloc(sizeof(Task));
  if(task_ptr == NULL){
    printf("Failure allocating task\n");
    return -1;
  }

  task_ptr->name = strdup(name);
  task_ptr->tid = tid;
  task_ptr->priority = priority;
  task_ptr->burst = burst;

  insert(&head, task_ptr);

  tid++;

  printf("Adding struct node #%d\n", tid);
  traverse(head);
  printf("\n");

  return 0;
}

void schedule(){
  int count = 0;
  int slice;
  int wait, response, turn_around;
  struct node *temp;
  Task *highest;

  while(head){
    highest = head->task;
    temp = head->next;

    while(temp){
      if(temp->task->priority > highest->priority){
        highest = temp->task;
      }
      temp = temp->next;
    }
    slice = highest->burst;

    wait = count;
    response = count;

    run(highest,slice);
    delete(&head, highest);

    count += slice;
    turn_around = count;

    printf("Waiting Time: %d\n", wait);
    printf("Turnaround Time: %d\n", turn_around);
    printf("Response Time: %d\n", response);
  } 
}
