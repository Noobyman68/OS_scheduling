#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

static struct node *head = NULL;
static int size = 0;

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

  printf("Adding Node #%d\n", tid);
  traverse(head);
  printf("\n");

  size++;
  return 0;
}


void schedule(){
  int run_times[size];
  int responses[size];
  memset(run_times, 0, sizeof(int) * size);
  memset(responses, 0, sizeof(int) * size);

  int index, t_burst;
  int count = 0;
  const int slice = 2;

  struct node *temp, *last;

  while(head){
    temp = head;
    last = head;
    

    while(temp){
      index = temp->task->tid;
      t_burst = temp->task->burst;

      if(run_times[index] == 0){
        responses[index] = count;
        run_times[index] = t_burst;
      }
      if(t_burst - slice < 1){
        count += t_burst;
        run(temp->task,t_burst);
        delete(&head, temp->task);

        temp = last;

        printf("\nWaiting Time: %d\n", count - run_times[index]);
        printf("Turnaround Time: %d\n", count);
        printf("Response Time: %d\n", responses[index]);

      }else{
        temp->task->burst -= slice;
        count += slice;
        last = temp;
        run(temp->task,slice);
      }
      temp = temp->next;
      index++;
    }
  } 
}

