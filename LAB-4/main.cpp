#include <iostream>
#include <string>
#include <limits>

using namespace std;

// --- DATA STRUCTURES ---

struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3]; // [0]: 100s, [1]: 50s, [2]: 20s
    MoneyBundle* next;
};

class MoneyStack {
private:
    MoneyBundle* top;
    int stackSize;

public:
    MoneyStack() : top(nullptr), stackSize(0) {}

    bool isEmpty() { return top == nullptr; }
    int getSize() { return stackSize; }

    void push(string serial, string currency, int hundred, int fifty, int twenty) {
        MoneyBundle* newNode = new MoneyBundle();
        newNode->serialNumber = serial;
        newNode->currencyType = currency;
        newNode->billCounts[0] = hundred;
        newNode->billCounts[1] = fifty;
        newNode->billCounts[2] = twenty;
        newNode->next = top;
        top = newNode;
        stackSize++;
        cout << "[System] Bundle added to vault -> Serial: " << serial << " Currency: " << currency << endl;
    }

    MoneyBundle* peek() {
        return top;
    }

    void popAndRelease() {
        if (isEmpty()) return;
        MoneyBundle* temp = top;
        top = top->next;
        delete temp;
        stackSize--;
    }

    void display() {
        cout << "\n--- VAULT (MONEY STACK) ---" << endl;
        if (isEmpty()) {
            cout << "  Vault is empty." << endl;
            return;
        }
        MoneyBundle* temp = top;
        int i = 1;
        while (temp != nullptr) {
            cout << "  " << i << ". Serial: " << temp->serialNumber
                 << " | Type: " << temp->currencyType
                 << " | 100s: " << temp->billCounts[0]
                 << " | 50s: " << temp->billCounts[1]
                 << " | 20s: " << temp->billCounts[2] << endl;
            temp = temp->next;
            i++;
        }
    }

    ~MoneyStack() {
        while (!isEmpty()) {
            popAndRelease();
        }
    }
};

struct Customer {
    string customerName;
    string transactionType;
    int request[3];
};

#define MAX 5

class CustomerQueue {
private:
    Customer arr[MAX];
    int front;
    int rear;
    int count;

public:
    CustomerQueue() : front(0), rear(0), count(0) {}

    bool isEmpty() { return count == 0; }
    bool isFull() { return count == MAX; }
    int getCount() { return count; }

    void enqueue(string name, string type, int r100, int r50, int r20) {
        if (isFull()) {
            cout << "[Error] Queue is full! " << name << " could not be added." << endl;
            return;
        }
        arr[rear].customerName = name;
        arr[rear].transactionType = type;
        arr[rear].request[0] = r100;
        arr[rear].request[1] = r50;
        arr[rear].request[2] = r20;
        rear = (rear + 1) % MAX;
        count++;
        cout << "[System] Customer added -> " << name << " | " << type << endl;
    }

    Customer dequeue() {
        Customer emptyCust = {"", "", {0,0,0}};
        if (isEmpty()) return emptyCust;
        Customer servedCustomer = arr[front];
        front = (front + 1) % MAX;
        count--;
        return servedCustomer;
    }

    void display() {
        cout << "\n--- CUSTOMER QUEUE ---" << endl;
        if (isEmpty()) {
            cout << "  Queue is empty." << endl;
            return;
        }
        int idx = front;
        for (int i = 0; i < count; i++) {
            cout << "  " << i + 1 << ". " << arr[idx].customerName
                 << " | " << arr[idx].transactionType
                 << " (Request: 100x" << arr[idx].request[0]
                 << ", 50x" << arr[idx].request[1]
                 << ", 20x" << arr[idx].request[2] << ")" << endl;
            idx = (idx + 1) % MAX;
        }
    }
};

class BankBranch {
private:
    MoneyStack vault;
    CustomerQueue line;

public:
    void addMoneyBundle(string serial, string currency, int hundred, int fifty, int twenty) {
        vault.push(serial, currency, hundred, fifty, twenty);
    }

    void addCustomer(string name, string type, int r100, int r50, int r20) {
        line.enqueue(name, type, r100, r50, r20);
    }

    void processTransaction() {
        if (line.isEmpty() || vault.isEmpty()) {
            cout << "[Notice] Cannot process: Customer or cash missing." << endl;
            return;
        }

        MoneyBundle* bundle = vault.peek();
        Customer customer = line.dequeue();

        bool sufficient = true;
        for(int i = 0; i < 3; i++) {
            if(bundle->billCounts[i] < customer.request[i]) sufficient = false;
        }

        if (sufficient) {
            for(int i = 0; i < 3; i++) bundle->billCounts[i] -= customer.request[i];
            cout << "Transaction completed for: " << customer.customerName << endl;

            if(bundle->billCounts[0] == 0 && bundle->billCounts[1] == 0 && bundle->billCounts[2] == 0) {
                cout << "Bundle is empty and removed from vault." << endl;
                vault.popAndRelease();
            }
        } else {
            cout << "FAILED: Not enough banknotes in current bundle! Customer left the queue." << endl;
        }
    }

    void showStatus() {
        cout << "\n========== BANK STATUS ==========";
        vault.display();
        line.display();
        cout << "=================================\n";
    }
};

int getValidatedInt(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Invalid input! Please enter a positive number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    BankBranch branch;
    int menuChoice = -1;

    while (menuChoice != 0) {
        cout << "\n--- BANK MANAGEMENT SYSTEM ---";
        cout << "\n1. Add Money Bundle (Push)";
        cout << "\n2. Add New Customer (Enqueue)";
        cout << "\n3. Process Transaction (Pop & Dequeue)";
        cout << "\n4. Display Status";
        cout << "\n0. Exit";
        cout << "\nYour Choice: ";

        menuChoice = getValidatedInt("");

        if (menuChoice == 1) {
            string s, c;
            cout << "Serial Number: "; getline(cin, s);
            cout << "Currency (e.g. TL/USD): "; getline(cin, c);
            int h = getValidatedInt("Count of 100s: ");
            int f = getValidatedInt("Count of 50s: ");
            int t = getValidatedInt("Count of 20s: ");
            branch.addMoneyBundle(s, c, h, f, t);
        }
        else if (menuChoice == 2) {
            string n, t;
            cout << "Customer Name: "; getline(cin, n);
            cout << "Transaction Type (Withdraw/Deposit): "; getline(cin, t);
            int r1 = getValidatedInt("Request 100s: ");
            int r2 = getValidatedInt("Request 50s: ");
            int r3 = getValidatedInt("Request 20s: ");
            branch.addCustomer(n, t, r1, r2, r3);
        }
        else if (menuChoice == 3) {
            branch.processTransaction();
        }
        else if (menuChoice == 4) {
            branch.showStatus();
        }
    }

    cout << "Exiting system..." << endl;
    return 0;
}
