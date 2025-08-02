#include <stdlib.h>
#include <limits.h>
#include <stdio.h>


typedef struct Node {
	int data;
	struct Node* next;
}Node;


typedef struct Stack {
	Node* top;
}Stack;


Stack* create_stack(){
	
	Stack* s = (Stack*)malloc(sizeof(Stack));
	if(s == NULL){
		return NULL; //mem alloc failed
	}

	s->top = NULL;
	return s;

}

void push(Stack* s, int value){
	Node* new_node = (Node*)malloc(sizeof(Node));
	if(new_node == NULL){
		return;
	}
	
	new_node->data = value;
	new_node->next = s->top;
	s->top = new_node;

}

int pop(Stack* s){
	
	//find the node with value int? and free the mem?
	if(s->top == NULL){
		return INT_MIN; //stack underflow ...
	}

	Node* temp = s->top; //Save pointer to the top node
	int value = temp->data; //Grab the value to return
	s->top = temp->next; //Move the top pointer down to the next node
	free(temp); //Free the memory of the old top node

	return value;

}

int peek(Stack* s){

	if(s->top == NULL){
		return INT_MIN;
	}
	
	return s->top->data;
}

int is_empty(Stack* s){

	return s->top == NULL;

}

void free_stack(Stack* s){
	Node* current = s->top;
	while(current != NULL){
		Node* next = current->next;
		free(current);
		current = next;
	}	

	free(s);
}




int main(){

	Stack *curr_stack = create_stack();
	
	push(curr_stack, 10);
	push(curr_stack, 20);
	push(curr_stack, 30);

	printf("Peek 1: %d\n",  peek(curr_stack));
	printf("Pop 1: %d\n", pop(curr_stack));
	printf("Peek 2: %d\n", peek(curr_stack));
	
	printf("Is Empty? %d\n", is_empty(curr_stack));
	
	printf("Pop 2: %d\n", pop(curr_stack));
	printf("Pop 3: %d\n", pop(curr_stack));

	printf("Is Empty? %d\n", is_empty(curr_stack));

	free_stack(curr_stack);

	return 0;



}

