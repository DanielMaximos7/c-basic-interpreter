#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


typedef struct Node {
	void* data;
	struct Node* next;
}Node;


typedef struct Stack {
	Node* top;
	size_t data_size; //size of each element's data
}Stack;


Stack* create_stack(size_t data_size){
	
	Stack* s = (Stack*)malloc(sizeof(data_size));
	if(s == NULL){
		return NULL; //mem alloc failed
	}

	s->top = NULL;
	s->data_size = data_size;
	return s;

}

void push(Stack* s, void* value_ptr){
	Node* new_node = (Node*)malloc(sizeof(Node));
	if(!new_node) return;
	
	new_node->data = malloc(s->data_size);
	if(!new_node->data){
		free(new_node);
		return;
	}
	
	memcpy(new_node->data, value_ptr, s->data_size);
	
	new_node->next = s->top;

	s->top = new_node;	
}

void* pop(Stack* s){
	

	if(s->top == NULL){
		return NULL; //stack underflow ...
	}

	Node* temp = s->top; //Save pointer to the top node
	void* data_copy = malloc(s->data_size);
	if(!data_copy){
		return NULL;
	}

	memcpy(data_copy, temp->data, s->data_size);

	s->top = temp->next; 

	free(temp->data);
	free(temp);

	return data_copy;

}

void* peek(Stack* s){

	if(s->top == NULL){
		return NULL;
	}
	
	void* data_copy = malloc(s->data_size);
	
	if(!data_copy){
		return NULL;
	}

	memcpy(data_copy, s->top->data, s->data_size);

	return data_copy;
}

int is_empty(Stack* s){

	return s->top == NULL;

}

void free_stack(Stack* s){
	Node* current = s->top;
	while(current != NULL){
		Node* next = current->next;
		free(current->data);
		free(current);
		current = next;
	}	

	free(s);
}











	






	


















