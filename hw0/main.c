#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    int count;
    struct Node* next;
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

Node* insertNode(Node* head, char data) {
    if (head == NULL) {
        return createNode(data);
    }

    Node* current = head;
    while (current != NULL) {
        if (current->data == data) {
            current->count++;
            return head;
        }
        
        if (current->next == NULL) {
            break;
        }
        current = current->next;
    }

    current->next = createNode(data);
    return head;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("Char: %c, Count: %d\n", current->data, current->count);
        current = current->next;
    }
}

int main() {
    Node* head = NULL;
    char ch;

    printf("Enter characters (Ctrl+D to end):\n");
    while ((ch = getchar()) != EOF) {
        if (ch != '\n') {
            head = insertNode(head, ch);
        }
    }

    printList(head);

    return 0;
}