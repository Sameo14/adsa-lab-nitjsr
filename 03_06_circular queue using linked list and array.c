#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

// ==================== ARRAY BASED CIRCULAR QUEUE ====================
typedef struct {
    int arr[SIZE];
    int front, rear;
} CircularQueueArray;

void initArrayQueue(CircularQueueArray* q) {
    q->front = q->rear = -1;
}

int isFullArray(CircularQueueArray* q) {
    return (q->front == (q->rear + 1) % SIZE);
}

int isEmptyArray(CircularQueueArray* q) {
    return (q->front == -1);
}

void enqueueArray(CircularQueueArray* q, int value) {
    if (isFullArray(q)) {
        printf("Array Queue Overflow!\n");
        return;
    }
    if (isEmptyArray(q))
        q->front = 0;
    q->rear = (q->rear + 1) % SIZE;
    q->arr[q->rear] = value;
    printf("%d enqueued to Array Queue.\n", value);
}

int dequeueArray(CircularQueueArray* q) {
    if (isEmptyArray(q)) {
        printf("Array Queue Underflow!\n");
        return -1;
    }
    int value = q->arr[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front = (q->front + 1) % SIZE;
    return value;
}

void displayArrayQueue(CircularQueueArray* q) {
    if (isEmptyArray(q)) {
        printf("Array Queue is empty.\n");
        return;
    }
    printf("Array Queue: ");
    int i = q->front;
    while (1) {
        printf("%d ", q->arr[i]);
        if (i == q->rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

// ==================== LINKED LIST BASED CIRCULAR QUEUE ====================
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* rear;
} CircularQueueLinkedList;

void initLinkedListQueue(CircularQueueLinkedList* q) {
    q->rear = NULL;
}

int isEmptyLinkedList(CircularQueueLinkedList* q) {
    return (q->rear == NULL);
}

void enqueueLinkedList(CircularQueueLinkedList* q, int value) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = value;
    if (isEmptyLinkedList(q)) {
        temp->next = temp;
        q->rear = temp;
    } else {
        temp->next = q->rear->next;
        q->rear->next = temp;
        q->rear = temp;
    }
    printf("%d enqueued to Linked List Queue.\n", value);
}

int dequeueLinkedList(CircularQueueLinkedList* q) {
    if (isEmptyLinkedList(q)) {
        printf("Linked List Queue Underflow!\n");
        return -1;
    }
    Node* front = q->rear->next;
    int value = front->data;
    if (q->rear == front) {
        free(front);
        q->rear = NULL;
    } else {
        q->rear->next = front->next;
        free(front);
    }
    return value;
}

void displayLinkedListQueue(CircularQueueLinkedList* q) {
    if (isEmptyLinkedList(q)) {
        printf("Linked List Queue is empty.\n");
        return;
    }
    printf("Linked List Queue: ");
    Node* temp = q->rear->next;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != q->rear->next);
    printf("\n");
}

// ==================== MAIN MENU DRIVEN PROGRAM ====================
int main() {
    CircularQueueArray qArr;
    CircularQueueLinkedList qLL;
    int choice, type, value;

    initArrayQueue(&qArr);
    initLinkedListQueue(&qLL);

    while (1) {
        printf("\n--- Circular Queue Menu ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) break;

        if (choice >= 1 && choice <= 3) {
            printf("Choose implementation: 1. Array  2. Linked List : ");
            scanf("%d", &type);
        }

        switch (choice) {
            case 1: // Enqueue
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                if (type == 1)
                    enqueueArray(&qArr, value);
                else if (type == 2)
                    enqueueLinkedList(&qLL, value);
                else
                    printf("Invalid type.\n");
                break;

            case 2: // Dequeue
                if (type == 1) {
                    value = dequeueArray(&qArr);
                    if (value != -1) printf("Dequeued: %d\n", value);
                } else if (type == 2) {
                    value = dequeueLinkedList(&qLL);
                    if (value != -1) printf("Dequeued: %d\n", value);
                } else {
                    printf("Invalid type.\n");
                }
                break;

            case 3: // Display
                if (type == 1)
                    displayArrayQueue(&qArr);
                else if (type == 2)
                    displayLinkedListQueue(&qLL);
                else
                    printf("Invalid type.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    }

    printf("Exiting program.\n");
    return 0;
}
