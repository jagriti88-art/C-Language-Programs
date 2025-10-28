#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

struct Node {
    char data;
    struct Node *next;
};

struct Node *top = NULL;

void push(char value) {
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->data = value;
    newnode->next = top;
    top = newnode;
}

int pop() {
    if (top == NULL) return -1;
    struct Node *temp = top;
    int val = temp->data;
    top = top->next;
    free(temp);
    return val;
}

int peek() {
    if (top == NULL) return -1;
    return top->data;
}

int precedence(char c) {
    if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

void intopost(char *in, char *post) {
    int j = 0;
    int len = strlen(in);
    for (int i = 0; i < len; i++) {
        char c = in[i];

        if (isdigit(c)) {
            while (isdigit(in[i])) {
                post[j++] = in[i++];
            }
            post[j++] = ' ';
            i--;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != NULL && peek() != '(') {
                post[j++] = pop();
                post[j++] = ' ';
            }
            pop();
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (top != NULL && precedence(peek()) >= precedence(c)) {
                post[j++] = pop();
                post[j++] = ' ';
            }
            push(c);
        }
    }

    while (top != NULL) {
        post[j++] = pop();
        post[j++] = ' ';
    }
    post[j] = '\0';
}

int calculation(char *post) {
    int stack[100];
    int topIndex = -1;
    int len = strlen(post);

    for (int i = 0; i < len; i++) {
        if (isdigit(post[i])) {
            int num = 0;
            while (isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                i++;
            }
            stack[++topIndex] = num;
        } else if (post[i] == '+' || post[i] == '-' || post[i] == '*' || post[i] == '/') {
            int value2 = stack[topIndex--];
            int value1 = stack[topIndex--];
            int result = 0;

            switch (post[i]) {
                case '+': result = value1 + value2; break;
                case '-': result = value1 - value2; break;
                case '*': result = value1 * value2; break;
                case '/': result = value1 / value2; break;
            }
            stack[++topIndex] = result;
        }
    }

    return stack[topIndex];
}

int main() {
    char infix[100], postfix[100];
    printf("Enter infix expression: ");
    scanf("%[^\n]", infix);
    intopost(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    int result = calculation(postfix);
    printf("Result = %d\n", result);
    return 0;
}
