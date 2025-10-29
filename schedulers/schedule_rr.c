#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../general/task.h"
#include "../general/list.h"
#include "../general/cpu.h"

static node *head = NULL;
static int size = 0;

int add(char *name, int priority, int burst){
  static int tid = 0;
  int check = 0;

  Task *task_ptr = malloc(sizeof(Task));
  if(task_ptr == NULL){
    printf("Failure allocating task\n");
    return -1;
  }

  task_ptr->name = strdup(name);
  task_ptr->tid = tid;
  task_ptr->priority = priority;
  task_ptr->burst = burst;

  if((check = insert(&head, task_ptr)) < 0){
    printf("error adding task\n");
    return -1;
  }
  
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
  int index, t_burst;
  int count = 0;
  const int slice = 2;

  node *temp;

  while(head){
    temp = head;
    
    index = 0;

    while(temp){
      printf("index: %d\n", index);
      // may be indexing problem with incorrect indexes being accessed once nodes get deleted
      // some int value from responses or run_times may be getting set to pointer which is causing such high and random values
      t_burst = temp->task->burst;
      if(run_times[index] == 0){
        responses[index] = count;
        run_times[index] = t_burst;
      }
      if(t_burst - slice < 1){
        count += t_burst;
        run(temp->task,t_burst);
        delete(&head, temp->task);

        printf("Waiting Time: %d\n", count - run_times[index]);
        printf("Turnaround Time: %d\n", count);
        printf("Response Time: %d\n", responses[index]);

      }else{
        temp->task->burst -= slice;
        count += slice;
        run(temp->task,slice);
      }
      temp = temp->next;
      index++;
    }
    printf("\n%d\n", count);
  } 
}
