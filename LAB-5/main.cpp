#include <iostream>
using namespace std;

#define MAX 100


struct Stack {
    int arr[MAX];
    int top;
};

void initStack(Stack* s) { s->top = -1; }
bool isStackEmpty(Stack* s) { return s->top == -1; }
void push(Stack* s, int val) {
    if (s->top < MAX - 1) {
        s->arr[++(s->top)] = val;
    }
}
int pop(Stack* s) {
    if (!isStackEmpty(s)) {
        return s->arr[(s->top)--];
    }
    return -1; // Error or Empty
}
void printStack(Stack* s) {
    if (isStackEmpty(s)) {
        cout << "Stack is empty." << endl;
        return;
    }
    cout << "[Top] ";
    for (int i = s->top; i >= 0; i--) {
        cout << s->arr[i] << " ";
    }
    cout << "[Bottom]" << endl;
}

// --- QUEUE IMPLEMENTATION (DO NOT MODIFY) ---
struct Queue {
    int arr[MAX];
    int front;
    int rear;
};

void initQueue(Queue* q) { q->front = -1; q->rear = -1; }
bool isQueueEmpty(Queue* q) { return q->front == -1 || q->front > q->rear; }
void enqueue(Queue* q, int val) {
    if (q->rear < MAX - 1) {
        if (q->front == -1) q->front = 0;
        q->arr[++(q->rear)] = val;
    }
}
int dequeue(Queue* q) {
    if (!isQueueEmpty(q)) {
        return q->arr[(q->front)++];
    }
    return -1; // Error or Empty
}


void transferStack(Stack* source, Stack* destination) {
    // 1. Create and initialize the temporary Queue
    Queue tempQueue;
    initQueue(&tempQueue);


    while (!isStackEmpty(source)) {
        enqueue(&tempQueue, pop(source));
    }

    // Adým 2: Queue'daki elemanlarý tekrar Source stack'e geri it.
    // Bu iþlem elemanlarýn Source içindeki sýrasýný orijinalin TAM TERSÝ yapar.
    while (!isQueueEmpty(&tempQueue)) {
        push(source, dequeue(&tempQueue));
    }

    // Adým 3: Ters dönmüþ Source stack'teki elemanlarý Destination stack'e pop/push yap.
    // Bir kez daha ters döndüðü için orijinal "Top-to-Bottom" sýrasý korunmuþ olur.
    while (!isStackEmpty(source)) {
        push(destination, pop(source));
    }
}
// ==========================================

int main() {
    Stack stackA, stackB;
    initStack(&stackA);
    initStack(&stackB);

    cout << "Please enter 5 integers for Stack A:" << endl;
    for(int i = 0; i < 5; i++) {
        int val;
        cout << "Enter element " << i + 1 << ": ";
        cin >> val;
        push(&stackA, val);
    }

    cout << "\nOriginal Stack A: ";
    printStack(&stackA);

    // Transfer iþlemini baþlat
    cout << "\nTransferring elements from Stack A to Stack B maintaining order..." << endl;
    transferStack(&stackA, &stackB);

    cout << "After transfer, Stack A: ";
    printStack(&stackA);

    cout << "After transfer, Stack B: ";
    printStack(&stackB);

    return 0;
}
