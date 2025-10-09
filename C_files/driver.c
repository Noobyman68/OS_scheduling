/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"

#define SIZE    100

int main(int argc, char *argv[])
{
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    if((in = fopen(argv[1],"r")) == NULL){
      printf("Error opening file");
      return -1;
    }
    
    while (fgets(task,SIZE,in) != NULL) {

        // Dont need to work with a copy of task because it gets new values each time
        // Can use a temp pointer to current char in task rather than mallocing and freeing temp string
        temp = task;
        name = strsep(&temp,",");
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));

        // add the task to the scheduler's list of tasks
        add(name,priority,burst);

    }

    fclose(in);

    // invoke the scheduler
    schedule();

    return 0;
}
