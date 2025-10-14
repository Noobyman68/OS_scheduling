/**
 * Various list operations
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"


// add a new task to the list of tasks
int insert(node **last, Task *newTask) {
    node *newNode = malloc(sizeof(node));

    if(newNode == NULL){
      printf("Failure allocating memory\n");
      return -1;
    }

    newNode->task = newTask;
    newNode->next = NULL;

    if(*last == NULL){
      *last = newNode;
      return 1;
    }
    
    (*last)->next = newNode;
    (*last) = newNode;

    return 0;
}

// delete the selected task from the list
void delete(node **head, Task *task) {
    // After all cases temp will point to the deleted node
    node *temp;
    node *prev;

    temp = *head;
    // special case - beginning of list
    if (strcmp(task->name,temp->task->name) == 0) {
        *head = (*head)->next;

        // pointers to freed memory should be set to null to prevent hanging pointers
        *head = NULL;
        head = NULL;
    }else{
        // interior or last element in the list
        prev = *head;
        temp = temp->next;

        while (strcmp(task->name,temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
    }
    // nodes are malloced and need to be freed to avoid memory leaks
    free(temp);
}

// traverse the list
void traverse(node *head) {
    node *temp = head;

    while (temp != NULL) {
        printf("[%s] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}
