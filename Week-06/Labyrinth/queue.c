#include <stdio.h>
#include <stdlib.h>

struct QueueNode {
    int data;
    struct QueueNode* next;
};

struct QueueNode* newQueueItem(int data){
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enQueue(struct QueueNode** head, int data){
    if(*head == NULL){
        *head = newQueueItem(data);
        return;
    }
    while ((*head)->next != NULL) {
        *head = (*head)->next;
    }

    (*head)->next = newQueueItem(data);
}

int deQueue(struct QueueNode** head){
    int retval = -1;
    struct QueueNode * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->data;
    free(*head);
    *head = next_node;

    return retval;
    }

int main(){
    struct QueueNode* head = NULL;
    enQueue(&head, 1);
    enQueue(&head, 2);
    int t = deQueue(&head);
    printf("%d\n", t);
    return 0;
}