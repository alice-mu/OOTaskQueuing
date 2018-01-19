#include <stdlib.h>
#include <iostream>
using namespace std;

enum TaskType{LAUNDRY, DISHES, MAKE_BED, VACUUM, MOP_FLOOR, MOW_LAWN};

struct Task 
{
	TaskType type;
	int taskID;
	char* description;
};

struct Item
{
	Task* task;
	Item* nextInQueue;
};

class TaskQueue{
public:
	TaskQueue(){
		item = new Item;
		item->task = NULL;
		item->nextInQueue = NULL;
	}
	
	~TaskQueue(){
	}
	
	bool enqueue(const Task& task){
		
		if (task.taskID < 0 || task.description == NULL || task.description[0] == 0)
		return false;
	
		Item* pointer = this->item;
	
		while (pointer->nextInQueue != NULL){
			
			if (task.taskID == pointer->task->taskID && task.type == pointer->task->type)
				return false;
				
			pointer = pointer->nextInQueue;
			
		}
			
		if (pointer->task != NULL){
		
			if (task.taskID == pointer->task->taskID && task.type == pointer->task->type)
				return false;
			
			pointer->nextInQueue = new Item;
	
			pointer = pointer->nextInQueue;
			
			pointer->task = NULL;
			
			pointer->nextInQueue = NULL;
		}
	
		pointer->task = new Task;
	
		pointer->task->type = task.type;
	
		pointer->task->taskID = task.taskID;
	
		pointer->task->description = task.description;
		
		return true;
	}
		
	const Task* dequeue(){
	
		if (item->task == NULL)
			return NULL;
	
		Task* dequeued = new Task;
	
		dequeued->type = item->task->type;
	
		dequeued->taskID = item->task->taskID;
	
		dequeued->description = item->task->description;
		
		Item* pointer = this->item;
		
		if (item->nextInQueue != NULL)
			item = item->nextInQueue;
		
		else{
			item -> task = NULL;
			item -> nextInQueue = NULL;
		}
		
		return dequeued;	
	}

private:
	Item* item;
};


#ifndef MARMOSET_TESTING

int main(){
	
	char sampleDescription[] = "sample description";

	Task task1 =
	{
		.type = LAUNDRY,
		.taskID = 1,
		.description = sampleDescription
	};

		Task task2 =
	{
		.type = MAKE_BED,
		.taskID = 2,
		.description = sampleDescription
	};
	
		Task task3 =
	{
		.type = MOW_LAWN,
		.taskID = 3,
		.description = sampleDescription
	};
	
		Task task4 =
	{
		.type = VACUUM,
		.taskID = 4,
		.description = sampleDescription
	};
	
	TaskQueue* taskQueue = new TaskQueue();
	bool enqueueSuccess01 = taskQueue->enqueue(task1);
	bool enqueueSuccess02 = taskQueue->enqueue(task2);
	bool enqueueSuccess03 = taskQueue->enqueue(task3);
	bool enqueueSuccess04 = taskQueue->enqueue(task4);

	
	if(enqueueSuccess01 && enqueueSuccess02 && enqueueSuccess03 && enqueueSuccess04)
		cout << "tasks enqueued successfully!" << endl << endl;
	else
		cout << "enqueue() failed" << endl << endl; 

	const Task* task01 = taskQueue->dequeue();
	const Task* task02 = taskQueue->dequeue();
	const Task* task03 = taskQueue->dequeue();
	const Task* task04 = taskQueue->dequeue();
	
	if (task01 && task02 && task03 && task04)
		cout << "dequeue successful!" << endl;
	else
		cout << "dequeue() failed" << endl;

	delete taskQueue;
	
	return 0;
}
#endif

