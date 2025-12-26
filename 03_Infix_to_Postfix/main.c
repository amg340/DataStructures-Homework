#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 500

typedef struct {
    char data[MAX];
    int top;
} Stack;

void init(Stack *s) { s->top = -1; }
int empty(Stack *s) { return s->top == -1; }
char peek(Stack *s) { return s->data[s->top]; }
void push(Stack *s, char x) { s->data[++s->top] = x; }
char pop(Stack *s) { return s->data[s->top--]; }

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int is_right_associative(char op) {
    return op == '^';
}

int is_operator(char c) {
    return c=='+' || c=='-' || c=='*' || c=='/' || c=='^';
}

// Input assumed like: 3+4*(2-1) or with spaces, both work
void infix_to_postfix(const char *infix, char *postfix) {
    Stack ops;
    init(&ops);

    int j = 0;
    for (int i = 0; infix[i]; i++) {
        char c = infix[i];
        if (isspace((unsigned char)c)) continue;

        if (isdigit((unsigned char)c)) {
            // number (may be multi-digit)
            while (isdigit((unsigned char)infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        } else if (c == '(') {
            push(&ops, c);
        } else if (c == ')') {
            while (!empty(&ops) && peek(&ops) != '(') {
                postfix[j++] = pop(&ops);
                postfix[j++] = ' ';
            }
            if (!empty(&ops) && peek(&ops) == '(') pop(&ops);
        } else if (is_operator(c)) {
            while (!empty(&ops) && is_operator(peek(&ops))) {
                char topOp = peek(&ops);
                int p1 = precedence(c), p2 = precedence(topOp);

                if ((is_right_associative(c) && p1 < p2) ||
                    (!is_right_associative(c) && p1 <= p2)) {
                    postfix[j++] = pop(&ops);
                    postfix[j++] = ' ';
                } else break;
            }
            push(&ops, c);
        } else {
            // simple support for variables like a,b,c
            if (isalpha((unsigned char)c)) {
                postfix[j++] = c;
                postfix[j++] = ' ';
            } else {
                // unknown char
            }
        }
    }

    while (!empty(&ops)) {
        char x = pop(&ops);
        if (x != '(') {
            postfix[j++] = x;
            postfix[j++] = ' ';
        }
    }
    postfix[j] = '\0';
}

int main() {
    char infix[MAX];
    char postfix[MAX];

    printf("Enter infix expression: ");
    fgets(infix, sizeof(infix), stdin);

    infix_to_postfix(infix, postfix);

    printf("Postfix: %s\n", postfix);
    return 0;
}
