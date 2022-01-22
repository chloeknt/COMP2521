
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

int main(void) {
	Queue q = QueueNew();
	
	for (int i = 1; i <= 100000; i++) {
		QueueEnqueue(q, i);
	}

    for (int i = 0; i < 99999; i++) {
        QueueDequeue(q);
    }
    
	QueueFree(q);
}

/* This benchmark utilises the fact that CircularArrayQueue's efficiency
is most observable within its O(1) QueueDequeue function, whereas in ArrayQueue's
dequeue function the time complexity is dependant on n, O(n) regardless of 
the best/worst/average case. */
