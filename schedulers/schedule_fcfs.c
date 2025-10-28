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

int reverse_traverse(struct node *head){
  if(!head){
    return 0;
  }
  int slice = head->task->burst;

  int count = reverse_traverse(head->next);

  int wait = count;
  int response = count;

  run(head->task, slice);
  delete(&head, head->task);

  count+= slice;
  int turn_around = count;

  printf("Waiting Time: %d\n", wait);
  printf("Turnaround Time: %d\n", turn_around);
  printf("Response Time: %d\n", response);

  return count;
}
void schedule(){
  reverse_traverse(head);
}
