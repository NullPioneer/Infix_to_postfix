#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100

// Stack operations
void pushChar(char stack[], int *top, char value) {
    stack[++(*top)] = value;
}

char popChar(char stack[], int *top) {
    return stack[(*top)--];
}

char peekChar(char stack[], int top) {
    return stack[top];
}

void pushInt(int stack[], int *top, int value) {
    stack[++(*top)] = value;
}

int popInt(int stack[], int *top) {
    return stack[(*top)--];
}

int peekInt(int stack[], int top) {
    return stack[top];
}

// Operator precedence
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Convert infix to postfix
void infixToPostfix(const char* infix, char* postfix) {
    char stack[MAX];
    int top = -1;
    int j = 0;

    for (int i = 0; infix[i]; i++) {
        char c = infix[i];

        if (isdigit(c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            pushChar(stack, &top, c);
        } else if (c == ')') {
            while (top != -1 && peekChar(stack, top) != '(') {
                postfix[j++] = popChar(stack, &top);
            }
            popChar(stack, &top); // Remove '('
        } else {
            while (top != -1 && precedence(peekChar(stack, top)) >= precedence(c)) {
                postfix[j++] = popChar(stack, &top);
            }
            pushChar(stack, &top, c);
        }
    }

    while (top != -1) {
        postfix[j++] = popChar(stack, &top);
    }
    postfix[j] = '\0';
}

// Evaluate postfix expression
int evaluatePostfix(const char* postfix) {
    int stack[MAX];
    int top = -1;

    for (int i = 0; postfix[i]; i++) {
        char c = postfix[i];

        if (isdigit(c)) {
            pushInt(stack, &top, c - '0');
        } else {
            int val2 = popInt(stack, &top);
            int val1 = popInt(stack, &top);

            switch (c) {
                case '+':
                    pushInt(stack, &top, val1 + val2);
                    break;
                case '-':
                    pushInt(stack, &top, val1 - val2);
                    break;
                case '*':
                    pushInt(stack, &top, val1 * val2);
                    break;
                case '/':
                    pushInt(stack, &top, val1 / val2);
                    break;
                case '^':
                    pushInt(stack, &top, (int)pow(val1, val2));
                    break;
            }
        }
    }

    return popInt(stack, &top);
}

int main() {
    char infix[MAX] = "3+(2*5)^2";
    char postfix[MAX];
    
    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}
