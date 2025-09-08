#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// ================= QUEUE STRUCTURE =================
typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

int isEmptyQueue(Queue* q) {
    return q->front == -1;
}

int isFullQueue(Queue* q) {
    return q->rear == MAX - 1;
}

void enqueue(Queue* q, int val) {
    if (isFullQueue(q)) {
        printf("Queue Overflow!\n");
        return;
    }
    if (isEmptyQueue(q)) q->front = 0;
    q->arr[++q->rear] = val;
}

int dequeue(Queue* q) {
    if (isEmptyQueue(q)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    int val = q->arr[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return val;
}

// ================= STACK USING TWO QUEUES - METHOD 1 (Push costly) =================
typedef struct {
    Queue q1, q2;
} StackPushCostly;

void initStackPushCostly(StackPushCostly* s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

void pushPushCostly(StackPushCostly* s, int val) {
    // Enqueue to q2
    enqueue(&s->q2, val);
    // Move all elements from q1 to q2
    while (!isEmptyQueue(&s->q1)) enqueue(&s->q2, dequeue(&s->q1));
    // Swap q1 and q2
    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
    printf("%d pushed to Stack (Push Costly)\n", val);
}

int popPushCostly(StackPushCostly* s) {
    if (isEmptyQueue(&s->q1)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return dequeue(&s->q1);
}

// ================= STACK USING TWO QUEUES - METHOD 2 (Pop costly) =================
typedef struct {
    Queue q1, q2;
} StackPopCostly;

void initStackPopCostly(StackPopCostly* s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

void pushPopCostly(StackPopCostly* s, int val) {
    enqueue(&s->q1, val);
    printf("%d pushed to Stack (Pop Costly)\n", val);
}

int popPopCostly(StackPopCostly* s) {
    if (isEmptyQueue(&s->q1)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    // Move all elements except last to q2
    while (s->q1.front != s->q1.rear) enqueue(&s->q2, dequeue(&s->q1));
    int val = dequeue(&s->q1);
    // Swap q1 and q2
    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
    return val;
}

// ==================== MENU DRIVEN PROGRAM ====================
int main() {
    StackPushCostly sPush;
    StackPopCostly sPop;
    int choice, method, val;

    initStackPushCostly(&sPush);
    initStackPopCostly(&sPop);

    while (1) {
        printf("\n--- Stack Using Two Queues ---\n");
        printf("1. Push\n2. Pop\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 3) break;

        if (choice >= 1 && choice <= 2) {
            printf("Choose method: 1. Push Costly  2. Pop Costly : ");
            scanf("%d", &method);
        }

        switch (choice) {
            case 1: // Push
                printf("Enter value to push: ");
                scanf("%d", &val);
                if (method == 1) pushPushCostly(&sPush, val);
                else if (method == 2) pushPopCostly(&sPop, val);
                else printf("Invalid method!\n");
                break;

            case 2: // Pop
                if (method == 1) {
                    val = popPushCostly(&sPush);
                    if (val != -1) printf("Popped: %d\n", val);
                } else if (method == 2) {
                    val = popPopCostly(&sPop);
                    if (val != -1) printf("Popped: %d\n", val);
                } else {
                    printf("Invalid method!\n");
                }
                break;

            default:
                printf("Invalid choice!\n");
        }
    }

    printf("Exiting program.\n");
    return 0;
}
