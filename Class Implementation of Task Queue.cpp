#include <stdlib.h>
#include <iostream>
#ifndef MARMOSET_TESTING
using namespace std;


enum TaskType{LAUNDRY, DISHES, MAKE_BED, VACUUM, MOP_FLOOR, MOW_LAWN};

struct Task 
{
	TaskType type;
	int taskID;
	char* description;
};

struct TaskQueue
{
	Task* task;
	TaskQueue* nextInQueue;
};

#endif

bool enqueue(TaskQueue*& queue, const Task& task);
const Task* dequeue(TaskQueue*& queue);

bool enqueue(TaskQueue*& queue, const Task& task)
{	
	if (task.taskID < 0 || task.description == NULL || task.description[0] == 0 )
		return false;
	
	if (queue == NULL){
		
		queue = new TaskQueue;
		
		queue->task = NULL;
		
		queue->nextInQueue = NULL;
	}
	
	TaskQueue* pointer = queue;
		
	while (pointer->nextInQueue != NULL){
		
		if (pointer->task->taskID == task.taskID && pointer->task->type == task.type)
			return false;
		
		pointer = pointer->nextInQueue;
	}
	
	if (pointer->task != NULL){
		
		if (pointer->task->taskID == task.taskID && pointer->task->type == task.type)
		return false;
	
		pointer->nextInQueue = new TaskQueue;
	
		pointer = pointer->nextInQueue;
	
		pointer->nextInQueue = NULL;
	}
	
	pointer->task = new Task;
	
	pointer->task->type = task.type;
	
	pointer->task->taskID = task.taskID;
	
	pointer->task->description = task.description;

	return true;
}

const Task* dequeue(TaskQueue*& queue)
{
	if (queue == NULL || queue->task == NULL)
		return NULL;
	
	TaskQueue* node = queue;
	
	queue = queue->nextInQueue;
	
	Task* task = new Task;
	
	task->type = node->task->type;
	
	task->taskID = node->task->taskID;
	
	task->description = node->task->description;
	
	delete node;
	
	return task;
}

int main(){
	
	char sampleDescription[] = "sample description";

	Task task1 =
	{
		.type = DISHES,
		.taskID = 1,
		.description = sampleDescription
	};
	
	TaskQueue* p_queue = new TaskQueue;
	p_queue->task = NULL;
	p_queue->nextInQueue = NULL;

	bool enqueueSuccess = enqueue(p_queue, task1);
	if(enqueueSuccess){
		cout << "task1 enqueued successfully" << endl << endl;
	
		cout << "p_queue task type: " << p_queue->task->type << endl;
	}
	
	else
		cout << "enqueue() failed" << endl << endl; 

	const Task* p_firstTaskInQueue = dequeue(p_queue);
	
	if (p_firstTaskInQueue)
	{
		cout << "Dequeue successful..." << endl;
		cout << "Type: " << p_firstTaskInQueue->type << endl;
		cout << "Task ID: " << p_firstTaskInQueue->taskID << endl;
		cout << "Description: " << p_firstTaskInQueue->description << endl;
	}
	else
		cout << "dequeue() failed" << endl;

	delete p_queue;
	
	return 0;
}

