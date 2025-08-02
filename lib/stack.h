#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct Stack Stack;

/**
 * Creates a new generic stack.
 * @param data_size The size of each element in bytes
 * @return Pointer to a new Stack, or NULL on failure
 */
Stack* create_stack(size_t data_size);

/**
 * Pushes a value onto the stack.
 * @param s The stack.
 * @param value_ptr Pointer to the value to push (copied internally)
 */
void push (Stack* s, void* value_ptr);

/**
 * Pops the top element off the stack.
 * @param s The stack.
 * @return Pointer to a newly allocated copy of the value (caller must free)
 */
void* pop(Stack* s);

/**
 * Returns a copy of the top element without removing it.
 * @param s The stack.
 * @return Pointer to a newly allocated copy of the top value (caller must free)
 */
void* peek(Stack* s);

/**
 * Checks whether the stack is empty.
 * @param s The stack.
 * @return 1 if empty, 0 otherwise
 */
int is_empty(Stack* s);

/**
 * Frees all memory used by the stack and its contents.
 * @param s The stack.
 */
void free_stack(Stack* s);

#endif // STACK_H
