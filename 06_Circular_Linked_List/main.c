#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* newNode(int x) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->data = x;
    n->next = NULL;
    return n;
}

void traverse(Node *tail) {
    if (!tail) { printf("List is empty.\n"); return; }
    Node *cur = tail->next; // head
    printf("Circular: ");
    do {
        printf("%d ", cur->data);
        cur = cur->next;
    } while (cur != tail->next);
    printf("\n");
}

Node* search(Node *tail, int key) {
    if (!tail) return NULL;
    Node *cur = tail->next;
    do {
        if (cur->data == key) return cur;
        cur = cur->next;
    } while (cur != tail->next);
    return NULL;
}

void insertEnd(Node **tail, int x) {
    Node *n = newNode(x);
    if (!*tail) {
        n->next = n;
        *tail = n;
        return;
    }
    n->next = (*tail)->next; // new points to head
    (*tail)->next = n;
    *tail = n;
}

void insertAfter(Node *pos, int x) {
    if (!pos) return;
    Node *n = newNode(x);
    n->next = pos->next;
    pos->next = n;
}

void deleteKey(Node **tail, int key) {
    if (!*tail) return;

    Node *prev = *tail;
    Node *cur = (*tail)->next; // head

    do {
        if (cur->data == key) {
            if (cur == prev) {
                // single node
                free(cur);
                *tail = NULL;
                return;
            }
            prev->next = cur->next;
            if (cur == *tail) *tail = prev;
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    } while (cur != (*tail)->next);
}

void freeList(Node **tail) {
    if (!*tail) return;
    Node *head = (*tail)->next;
    Node *cur = head;
    do {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    } while (cur != head);
    *tail = NULL;
}

int main() {
    Node *tail = NULL;

    insertEnd(&tail, 10);
    insertEnd(&tail, 20);
    insertEnd(&tail, 30);
    traverse(tail);

    Node *p = search(tail, 20);
    insertAfter(p, 25);
    traverse(tail);

    deleteKey(&tail, 10);
    traverse(tail);

    freeList(&tail);
    return 0;
}
