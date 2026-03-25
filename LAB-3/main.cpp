#include <iostream>
#include <string>
using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3]; // saat, dakika, saniye

    Page* next;
    Page* prev;
};

Page* head = NULL;
Page* tail = NULL;
Page* current = NULL;

// yeni sayfa ekleme
void visit(string url, string title, int h, int m, int s) {
    Page* newPage = new Page;

    newPage->url = url;
    newPage->title = title;
    newPage->accessTime[0] = h;
    newPage->accessTime[1] = m;
    newPage->accessTime[2] = s;

    newPage->next = NULL;
    newPage->prev = NULL;

    if (head == NULL) {
        head = tail = newPage;
    } else {
        tail->next = newPage;
        newPage->prev = tail;
        tail = newPage;
    }

    current = newPage;
}

// geri git
void goBack() {
    if (current != NULL && current->prev != NULL) {
        current = current->prev;
    } else {
        cout << "Geri gidilemez!\n";
    }
}

// ileri git
void goForward() {
    if (current != NULL && current->next != NULL) {
        current = current->next;
    } else {
        cout << "Ileri gidilemez!\n";
    }
}

// mevcut sayfayý sil
void deleteCurrent() {
    if (current == NULL) return;

    Page* temp = current;

    if (current == head) {
        head = current->next;
        if (head != NULL)
            head->prev = NULL;
        current = head;
    }
    else if (current == tail) {
        tail = current->prev;
        if (tail != NULL)
            tail->next = NULL;
        current = tail;
    }
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        current = current->next;
    }

    delete temp;
}

// geçmiþi yazdýr
void display() {
    Page* temp = head;

    while (temp != NULL) {
        cout << temp->title << " (" << temp->url << ") - ";

        for (int i = 0; i < 3; i++) {
            cout << temp->accessTime[i];
            if (i < 2) cout << ":";
        }

        if (temp == current)
            cout << "  <-- su an buradasin";

        cout << endl;
        temp = temp->next;
    }
}

// belleði temizle
void clearAll() {
    Page* temp = head;

    while (temp != NULL) {
        Page* next = temp->next;
        delete temp;
        temp = next;
    }

    head = tail = current = NULL;
}

int main() {
    int secim;

    while (true) {
        cout << "\n1- Yeni sayfa\n";
        cout << "2- Geri\n";
        cout << "3- Ileri\n";
        cout << "4- Sil\n";
        cout << "5- Gecmisi goster\n";
        cout << "6- Cikis\n";
        cout << "Secim: ";
        cin >> secim;

        if (secim == 1) {
            string url, title;
            int h, m, s;

            cout << "URL: ";
            cin >> url;
            cout << "Baslik: ";
            cin >> title;
            cout << "Saat dakika saniye: ";
            cin >> h >> m >> s;

            visit(url, title, h, m, s);
        }
        else if (secim == 2) goBack();
        else if (secim == 3) goForward();
        else if (secim == 4) deleteCurrent();
        else if (secim == 5) display();
        else if (secim == 6) {
            clearAll();
            cout << "Program bitti\n";
            break;
        }
        else {
            cout << "Hatali secim\n";
        }
    }
}
