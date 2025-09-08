#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// ================= STACK STRUCTURE =================
typedef struct {
    int arr[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

void push(Stack* s, int val) {
    if (isFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->arr[++s->top] = val;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return s->arr[s->top--];
}

int peek(Stack* s) {
    if (isEmpty(s)) return -1;
    return s->arr[s->top];
}

// ================= QUEUE USING TWO STACKS - METHOD 1 (Push costly) =================
typedef struct {
    Stack s1, s2;
} QueuePushCostly;

void initQueuePushCostly(QueuePushCostly* q) {
    initStack(&q->s1);
    initStack(&q->s2);
}

void enqueuePushCostly(QueuePushCostly* q, int val) {
    // Move all elements from s1 to s2
    while (!isEmpty(&q->s1)) push(&q->s2, pop(&q->s1));
    // Push new element to s1
    push(&q->s1, val);
    // Move back elements from s2 to s1
    while (!isEmpty(&q->s2)) push(&q->s1, pop(&q->s2));
    printf("%d enqueued to Queue (Push Costly)\n", val);
}

int dequeuePushCostly(QueuePushCostly* q) {
    if (isEmpty(&q->s1)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    return pop(&q->s1);
}

// ================= QUEUE USING TWO STACKS - METHOD 2 (Pop costly) =================
typedef struct {
    Stack s1, s2;
} QueuePopCostly;

void initQueuePopCostly(QueuePopCostly* q) {
    initStack(&q->s1);
    initStack(&q->s2);
}

void enqueuePopCostly(QueuePopCostly* q, int val) {
    push(&q->s1, val);
    printf("%d enqueued to Queue (Pop Costly)\n", val);
}

int dequeuePopCostly(QueuePopCostly* q) {
    if (isEmpty(&q->s2)) {
        while (!isEmpty(&q->s1)) push(&q->s2, pop(&q->s1));
    }
    if (isEmpty(&q->s2)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    return pop(&q->s2);
}

// ==================== DISPLAY FUNCTION ====================
void displayStack(Stack* s) {
    if (isEmpty(s)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue: ");
    for (int i = 0; i <= s->top; i++)
        printf("%d ", s->arr[i]);
    printf("\n");
}

// ==================== MENU DRIVEN PROGRAM ====================
int main() {
    QueuePushCostly qPush;
    QueuePopCostly qPop;
    int choice, method, val;

    initQueuePushCostly(&qPush);
    initQueuePopCostly(&qPop);

    while (1) {
        printf("\n--- Queue Using Two Stacks ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) break;

        if (choice >= 1 && choice <= 3) {
            printf("Choose method: 1. Push Costly  2. Pop Costly : ");
            scanf("%d", &method);
        }

        switch (choice) {
            case 1: // Enqueue
                printf("Enter value to enqueue: ");
                scanf("%d", &val);
                if (method == 1) enqueuePushCostly(&qPush, val);
                else if (method == 2) enqueuePopCostly(&qPop, val);
                else printf("Invalid method!\n");
                break;

            case 2: // Dequeue
                if (method == 1) {
                    val = dequeuePushCostly(&qPush);
                    if (val != -1) printf("Dequeued: %d\n", val);
                } else if (method == 2) {
                    val = dequeuePopCostly(&qPop);
                    if (val != -1) printf("Dequeued: %d\n", val);
                } else {
                    printf("Invalid method!\n");
                }
                break;

            case 3: // Display
                if (method == 1) displayStack(&qPush.s1);
                else if (method == 2) {
                    if (!isEmpty(&qPop.s2)) displayStack(&qPop.s2);
                    else displayStack(&qPop.s1);
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
