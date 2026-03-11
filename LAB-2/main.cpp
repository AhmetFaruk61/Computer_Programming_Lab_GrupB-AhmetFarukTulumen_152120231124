#include <iostream>
#include <string>
using namespace std;

struct Node
{
    string title;
    Node* next;
};

Node* head = NULL;

void addSong(string song)
{
    Node* newNode = new Node;
    newNode->title = song;
    newNode->next = head;
    head = newNode;
}

void listSongs()
{
    Node* temp = head;
    int i = 1;

    while(temp != NULL)
    {
        cout << i << ". " << temp->title << endl;
        temp = temp->next;
        i++;
    }

    if(head == NULL)
        cout << "Playlist empty\n";
}

void searchSong(string song)
{
    Node* temp = head;

    while(temp != NULL)
    {
        if(temp->title == song)
        {
            cout << "Song found\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Song not found\n";
}

int main()
{
    int choice;
    string song;

    while(true)
    {
        cout << "\n1.Add Song\n2.Search Song\n3.List Songs\n4.Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if(choice == 1)
        {
            cout << "Enter song title: ";
            getline(cin,song);
            addSong(song);
        }
        else if(choice == 2)
        {
            cout << "enter song title: ";
            getline(cin,song);
            searchSong(song);
        }
        else if(choice == 3)
        {
            listSongs();
        }
        else if(choice == 4)
        {
            break;
        }
    }

    return 0;
}
