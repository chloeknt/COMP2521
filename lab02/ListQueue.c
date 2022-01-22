// Implementation of the Queue ADT using a linked list

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

typedef struct node *Node;
struct node {
	Item item;
	Node next;
};

struct queue {
	Node head;
	Node tail;
	int  size;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}

	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	Node curr = q->head;
	while (curr != NULL) {
		Node temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
    //Allocate memory
	Node new_node = malloc(sizeof(Node));
	//If the queue is empty 
	if (q->head == NULL) {
	    //Point the head and tail pointers to the new node
	    q->head = new_node;
	    //Queue is not empty 
	} else {
	    //Tail points to the new node
	    q->tail->next = new_node;
	}
	new_node->item = it;
	q->tail = new_node;
	q->size++;
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) { 
    //Temp variable for the item
    int value = q->head->item;
    //One element only
    if (q->head->next == NULL) {
        free(q->head);
        q->head = NULL;
        q->tail = NULL;
        //More than one element 
    } else {
        //Set a temporary value for the item 
	    Node new_head = q->head->next;
    	//Free the node 
        free(q->head);
	    //Head pointer points at the second node
	    q->head = new_head;
	}
	q->size--;
	return value;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);

	return q->head->item;
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
	return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}

/**
 * Prints the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp) {
	for (Node curr = q->head; curr != NULL; curr = curr->next) {
		fprintf(fp, "%d ", curr->item);
	}
	fprintf(fp, "\n");
}

/**
 * Prints out information for debugging
 */
void QueueDebugPrint(Queue q) {
    Node curr = q->head;
    while (curr != NULL) {
        printf("%d ", curr->item);
        curr = curr->next;
    }
}

