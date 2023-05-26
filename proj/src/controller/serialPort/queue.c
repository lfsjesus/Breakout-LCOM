// C program for array implementation of queue
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
Queue* createQueue(unsigned capacity) {
	Queue* queue = (Queue*)malloc(
		sizeof(Queue));
	queue->capacity = capacity;
	queue->front = queue->size = 0;

	// This is important, see the enqueue
	queue->back = capacity - 1;
	queue->array = (int*)malloc(
		queue->capacity * sizeof(int));
	return queue;
}

// Queue is full when size becomes
// equal to the capacity
bool isFull( Queue* queue){
	return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
bool isEmpty(Queue* queue){
	return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
bool push(Queue* queue, uint8_t element) {
	if (isFull(queue))
		return false;
	queue->back = (queue->back + 1)
				% queue->capacity;
	queue->array[queue->back] = element;
	queue->size = queue->size + 1;
	printf("%d enqueued\n", element);
	return true;
}

// Function to remove an item from queue.
// It changes front and size
uint8_t pop(Queue* queue) {
	if (isEmpty(queue))
		return 0;
	int element = queue->array[queue->front];
	queue->front = (queue->front + 1)
				% queue->capacity;
	queue->size = queue->size - 1;
	return element;
}


uint8_t front(Queue* queue){
	if (isEmpty(queue))
		return 0;
	return queue->array[queue->front];
}

uint8_t back(Queue* queue) {
	if (isEmpty(queue))
		return 0;
	return queue->array[queue->back];
}

