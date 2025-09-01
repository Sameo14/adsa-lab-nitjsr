#include <stdio.h>
#include <ctype.h>  // for isdigit()
#include <string.h>

#define MAX 100

// Stack implementation
char stack[MAX];
int top = -1;

void push(char c) {
    if (top < MAX - 1)
        stack[++top] = c;
}

char pop() {
    if (top >= 0)
        return stack[top--];
    return '\0';
}

char peek() {
    if (top >= 0) return stack[top];
    return '\0';
}

// precedence function
int precedence(char c) {
    switch (c) {
        case '/':
        case '*': return 2;
        case '+':
        case '-': return 1;
        default: return -1;
    }
}

// Infix to Postfix
void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        // if operand → output
        if (isdigit(ch)) {
            postfix[k++] = ch;
        }
        // if '(' → push
        else if (ch == '(') {
            push(ch);
        }
        // if ')' → pop until '('
        else if (ch == ')') {
            while (top != -1 && peek() != '(') {
                postfix[k++] = pop();
            }
            if (top != -1 && peek() == '(')
                pop(); // remove '('
        }
        // if operator
        else {
            while (top != -1 && precedence(ch) <= precedence(peek())) {
                if (peek() == '(') break;
                postfix[k++] = pop();
            }
            push(ch);
        }
    }

    // pop remaining operators
    while (top != -1) {
        postfix[k++] = pop();
    }

    postfix[k] = '\0'; // null terminate
}

int main() {
    char infix[MAX] = "3+(4*5)-6/(1+2)";
    char postfix[MAX];

    infixToPostfix(infix, postfix);

    printf("Infix:   %s\n", infix);
    printf("Postfix: %s\n", postfix);

    return 0;
}

