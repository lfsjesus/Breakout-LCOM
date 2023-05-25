// C program for array implementation of queue
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <src/controller/serialPort/queue.h>

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
int isFull( Queue* queue){
	return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(Queue* queue){
	return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(Queue* queue, int item) {
	if (isFull(queue))
		return;
	queue->back = (queue->back + 1)
				% queue->capacity;
	queue->array[queue->back] = item;
	queue->size = queue->size + 1;
	printf("%d enqueued to queue\n", item);
}

// Function to remove an item from queue.
// It changes front and size
int dequeue(Queue* queue) {
	if (isEmpty(queue))
		return INT_MIN;
	int item = queue->array[queue->front];
	queue->front = (queue->front + 1)
				% queue->capacity;
	queue->size = queue->size - 1;
	return item;
}


int front(Queue* queue){
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->front];
}

int back(Queue* queue) {
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->back];
}

