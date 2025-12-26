#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

Node* newNode(int x) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->data = x;
    n->prev = n->next = NULL;
    return n;
}

void insertFront(Node **head, int x) {
    Node *n = newNode(x);
    n->next = *head;
    if (*head) (*head)->prev = n;
    *head = n;
}

void insertBack(Node **head, int x) {
    Node *n = newNode(x);
    if (!*head) { *head = n; return; }
    Node *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = n;
    n->prev = cur;
}

Node* search(Node *head, int key) {
    while (head) {
        if (head->data == key) return head;
        head = head->next;
    }
    return NULL;
}

void insertAfter(Node *pos, int x) {
    if (!pos) return;
    Node *n = newNode(x);
    n->next = pos->next;
    n->prev = pos;
    if (pos->next) pos->next->prev = n;
    pos->next = n;
}

void deleteKey(Node **head, int key) {
    Node *cur = *head;
    while (cur && cur->data != key) cur = cur->next;
    if (!cur) return;

    if (cur->prev) cur->prev->next = cur->next;
    else *head = cur->next;

    if (cur->next) cur->next->prev = cur->prev;

    free(cur);
}

void traverseForward(Node *head) {
    printf("Forward: ");
    while (head) {
        printf("%d ", head->data);
        if (!head->next) break;
        head = head->next;
    }
    printf("\n");
}

void traverseBackward(Node *tail) {
    printf("Backward: ");
    while (tail) {
        printf("%d ", tail->data);
        tail = tail->prev;
    }
    printf("\n");
}

Node* getTail(Node *head) {
    if (!head) return NULL;
    while (head->next) head = head->next;
    return head;
}

void freeList(Node *head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    Node *head = NULL;

    insertBack(&head, 10);
    insertBack(&head, 20);
    insertFront(&head, 5);
    traverseForward(head);

    Node *p = search(head, 10);
    insertAfter(p, 15);
    traverseForward(head);

    deleteKey(&head, 20);
    traverseForward(head);

    Node *tail = getTail(head);
    traverseBackward(tail);

    freeList(head);
    return 0;
}
