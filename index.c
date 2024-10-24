#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to check precedence of operators
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

// Function to perform the infix to postfix conversion
void infixToPostfix(char* infix, char* postfix) {
    char stack[100];
    int top = -1, k = 0;
    
    for (int i = 0; infix[i]; i++) {
        // If the scanned character is an operand, add it to the result
        if (isalnum(infix[i])) {
            postfix[k++] = infix[i];
        } 
        // If the scanned character is '(', push it to the stack
        else if (infix[i] == '(') {
            stack[++top] = infix[i];
        } 
        // If the scanned character is ')', pop and output from the stack until '(' is encountered
        else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = stack[top--];
            }
            if (top != -1 && stack[top] != '(') {
                return; // Invalid expression
            } else {
                top--;
            }
        } 
        // An operator is encountered
        else {
            while (top != -1 && precedence(infix[i]) <= precedence(stack[top])) {
                postfix[k++] = stack[top--];
            }
            stack[++top] = infix[i];
        }
    }
    
    // Pop all the operators from the stack
    while (top != -1) {
        postfix[k++] = stack[top--];
    }
    
    postfix[k] = '\0'; // Null terminate the result
}

// Function to reverse a string
void reverse(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

// Function to swap parentheses
void swapParentheses(char* expr) {
    for (int i = 0; expr[i]; i++) {
        if (expr[i] == '(') {
            expr[i] = ')';
        } else if (expr[i] == ')') {
            expr[i] = '(';
        }
    }
}

// Function to convert infix to prefix by first reversing the infix expression
void infixToPrefix(char* infix, char* prefix) {
    reverse(infix);            // Reverse the infix expression
    swapParentheses(infix);    // Swap parentheses after reversing
    infixToPostfix(infix, prefix); // Get postfix of the reversed expression
    reverse(prefix);           // Reverse the result to get the prefix
}

int main() {
    char infix[100], result[100];
    int choice;
    
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    
    printf("Choose conversion type:\n");
    printf("1. Postfix\n");
    printf("2. Prefix\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        infixToPostfix(infix, result);
        printf("Postfix expression: %s\n", result);
    } else if (choice == 2) {
        infixToPrefix(infix, result);
        printf("Prefix expression: %s\n", result);
    } else {
        printf("Invalid choice!\n");
    }
    
    return 0;
}
