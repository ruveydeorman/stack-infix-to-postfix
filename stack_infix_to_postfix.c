#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30

typedef struct {
	char items[SIZE];
	int top;
}Stack;

void init_stack(Stack* stack) {
	stack->top = -1;
}
int is_empty(Stack* stack) {
	if (stack->top == -1)
		return 1;
	else return 0;
}
void push(Stack* stack, char item) {
	stack->top++;
	stack->items[stack->top] = item;
}
char pop(Stack* stack) {
	char item;
	item = stack->items[stack->top] ;
	stack->top--;
	return item;
}
int operator_control(char operator) {
	if(operator == '*' || operator == '/') return 2;
	if (operator == '+' || operator == '-') return 1;
	return 0;
}
int is_digit(char ch) {
	if (ch >= '0' && ch <= '9') {
		return 1;
	}
	else return 0;
}
int infix_to_postfix(const char* infix,  char* postfix){
	Stack stack;
	init_stack(&stack);
	int j = 0;
	int i;
	for (i = 0; infix[i] != '\0'; i++) {
		if (isdigit(infix[i])) {
			postfix[j++] = infix[i];
		}
		else if (infix[i] == '(') {
			push(&stack, infix[i]);
		}
		else if (infix[i] == ')') {
			while (!is_empty(&stack) && stack.items[stack.top ]!= '(') {
				postfix[j++] = pop(&stack);
			}
			pop(&stack);
		}
		else {
			while (!is_empty(&stack) && operator_control(stack.items[stack.top]) >= operator_control(infix[i])) {
				postfix[j++] = pop(&stack);
			}
			push(&stack, infix[i]);
		}
	}
	while (!is_empty(&stack)) {
		postfix[j++] = pop(&stack);
	}
	postfix[j] = '\0';
	return j;

}
int main() {
	char infix[SIZE] = "(6+3+7)/(4*3)";
	char postfix[SIZE];

	infix_to_postfix(infix, postfix);
	printf("Postfix : %s\n", postfix);

	return 0;
}
