#include<bits/stdc++.h>
using namespace std;
// node class
class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int data) : data(data), next(nullptr), prev(nullptr) {}
};

//DLL class
class DoublyLinkedList {
public:
    Node* head;
    Node* tail;
    int size;

    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    bool isEmpty() const { return size == 0; }

    void insertFront(int data);
    void insertBack(int data);
    void insertAfter(int data, int prevData);
    void deleteFront();
    void deleteBack();
    void deleteNode(int data);
    Node* search(int data) const;
    void display() const;
    ~DoublyLinkedList();
};

void DoublyLinkedList::insertFront(int data) {
    Node* node = new Node(data);
    if (isEmpty()) {
        head = tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
    size++;
}

void DoublyLinkedList::insertBack(int data) {
    Node* node = new Node(data);
    if (isEmpty()) {
        head = tail = node;
    } else {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
    size++;
}

void DoublyLinkedList::insertAfter(int data, int prevData) {
    Node* prevNode = search(prevData);
    if (prevNode) {
        Node* node = new Node(data);
        node->next = prevNode->next;
        node->prev = prevNode;
        if (prevNode->next) {
            prevNode->next->prev = node;
        }
        prevNode->next = node;
        if (prevNode == tail) {
            tail = node;
        }
        size++;
    }
}

void DoublyLinkedList::deleteFront() {
    if (!isEmpty()) {
        Node* node = head;
        if (size == 1) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete node;
        size--;
    }
}

void DoublyLinkedList::deleteBack() {
    if (!isEmpty()) {
        Node* node = tail;
        if (size == 1) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete node;
        size--;
    }
}

void DoublyLinkedList::deleteNode(int data) {
    Node* node = search(data);
    if (node) {
        if (node == head) {
            deleteFront();
        } else if (node == tail) {
            deleteBack();
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
            size--;
        }
    }
}

Node* DoublyLinkedList::search(int data) const {
    Node* node = head;
    while (node && node->data != data) {
        node = node->next;
    }
    return node;
}

void DoublyLinkedList::display() const {
    Node* it = head;
    while (it) {
        std::cout << it->data << " ";
        it = it->next;
    }
    std::cout << std::endl;
}

DoublyLinkedList::~DoublyLinkedList() {
    while (!isEmpty()) {
        deleteFront();
    }
}


//Queue class
class Queue {
public:
    DoublyLinkedList* list;

    Queue() { list = new DoublyLinkedList(); }
    void enqueue(int data) { list->insertBack(data); }
    int dequeue();
    int front() const;
    bool empty() const { return list->isEmpty(); }
    ~Queue() { delete list; }
};

int Queue::dequeue() {
    if (empty()) {
        return -1;
    } else {
        int data = list->head->data;
        list->deleteFront();
        return data;
    }
}

int Queue::front() const {
    if (empty()) {
        return -1;
    } else {
        return list->head->data;
    }
}

// playlist class
class Playlist {
public:
    DoublyLinkedList* list;
    int numSongs;
    Node* lastSong;

    Playlist() : list(new DoublyLinkedList()), numSongs(0), lastSong(nullptr) {}
    void addSong(int songId, int where);
    void deleteSong(int songId);
    Node* searchSong(int songId) const;
    void searchAndPlay(int songId);
    void playNext(Queue* q);
    void playPrevious();
    void playFromQueue(Queue* q);
    void insertToQueue(Queue* q, int songId);
    void reverse();
    void kSwap(int k);
    void shuffle(int k);
    Node* debug();
    void display() const;
    ~Playlist() { delete list; }
};

void Playlist::addSong(int songId, int where) {
    if (where == -1) {
        list->insertFront(songId);
    } else if (where == -2) {
        list->insertBack(songId);
    } else {
        list->insertAfter(songId, where);
    }
    numSongs++;
}

void Playlist::deleteSong(int songId) {
    list->deleteNode(songId);
    numSongs--;
}

Node* Playlist::searchSong(int songId) const {
    return list->search(songId);
}

void Playlist::searchAndPlay(int songId) {
    Node* song = searchSong(songId);
    if (song) {
        std::cout << "Playing: " << song->data << std::endl;
        lastSong = song;
    }
}

void Playlist::playNext(Queue* q) {
    if (list->isEmpty()) {
        return;
    } else if (q->empty()) {
        if (lastSong && lastSong->next) {
            searchAndPlay(lastSong->next->data);
        } else {
            searchAndPlay(list->head->data);
        }
    } else {
        playFromQueue(q);
    }
}

void Playlist::playPrevious() {
    if (list->isEmpty()) {
        return;
    } else {
        if (lastSong && lastSong->prev) {
            searchAndPlay(lastSong->prev->data);
        } else {
            searchAndPlay(list->tail->data);
        }
    }
}

void Playlist::playFromQueue(Queue* q) {
    if (!q->empty()) {
        int songId = q->dequeue();
        std::cout << "Playing from queue: " << songId << std::endl;
    }
}

void Playlist::insertToQueue(Queue* q, int songId) {
    q->enqueue(songId);
}

void Playlist::reverse() {
    Node* temp = list->tail;
    list->tail = list->head;
    list->head = temp;
    Node* temp2 = temp->prev;
    for (int i = 0; i < numSongs; i++) {
        if (temp == list->head) {
            temp->prev = nullptr;
        } else {
            temp->prev = temp->next;
        }
        temp->next = temp2;
        temp = temp2;
        if (temp2) {
            temp2 = temp2->prev;
        }
    }
}

void Playlist::kSwap(int k) {
    if (k == 0) {
        return;
    } else if (k == 1) {
        list->tail->next = list->head;
        list->head = list->head->next;
        list->head->prev = nullptr;
        list->tail->next->prev = list->tail;
        list->tail = list->tail->next;
        list->tail->next = nullptr;
    } else {
        Node* temp = list->head;
        Node* temp2 = list->head;
        Node *prevTemp = nullptr, *nextTemp = nullptr;
        for (int i = 0; i < k; i++) {
            temp2 = temp2->next;
        }
        for (int i = 0; i < numSongs - k; i++) {
            nextTemp = temp->next;
            prevTemp = temp2->prev;
            if (temp == list->head) {
                list->head = temp2;
                temp2->prev = nullptr;
            } else {
                temp2->prev = temp->prev;
                temp2->prev->next = temp2;
            }
            if (temp2 == list->tail) {
                list->tail = temp;
                temp->next = nullptr;
            } else {
                temp->next = temp2->next;
                temp->next->prev = temp;
            }
            temp->prev = prevTemp;
            prevTemp->next = temp;
            temp2->next = nextTemp;
            nextTemp->prev = temp2;
            if (i != numSongs - k - 1) 
            {
                temp = temp->next;
                temp2 = temp2->next;
            }
        }
    }
}

void Playlist::shuffle(int k) {
for (int i = 0; i < k; i++) {
kSwap(1);
}
}

Node* Playlist::debug() {
return lastSong;
}

void Playlist::display() const {
list->display();
}


int main() 
{
    Playlist playlist;
    Queue queue;
    int n;
    std::cout << "Enter the number of songs: ";
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int songId;
        std::cout << "Enter song ID: ";
        std::cin >> songId;
        playlist.addSong(songId, -2);
    }
    int choice;
    do {
        std::cout << "1. Add song\n2. Delete song\n3. Search and play\n4. Play next\n5. Play previous\n6. Play from queue\n7. Insert to queue\n8. Reverse playlist\n9. K-swap\n10. Shuffle\n11. Display\n12. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        switch (choice) {
        case 1: {
            int songId, where;
            std::cout << "Enter song ID and position (-1 for front, -2 for back, or enter previous song ID): ";
            std::cin >> songId >> where;
            playlist.addSong(songId, where);
            break;
        }
        case 2: {
            int songId;
            std::cout << "Enter song ID to delete: ";
            std::cin >> songId;
            playlist.deleteSong(songId);
            break;
        }
        case 3: {
            int songId;
            std::cout << "Enter song ID to search and play: ";
            std::cin >> songId;
            playlist.searchAndPlay(songId);
            break;
        }
        case 4: {
            playlist.playNext(&queue);
            break;
        }
        case 5: {
            playlist.playPrevious();
            break;
        }
        case 6: {
            playlist.playFromQueue(&queue);
            break;
        }
        case 7: {
            int songId;
            std::cout << "Enter song ID to insert into queue: ";
            std::cin >> songId;
            playlist.insertToQueue(&queue, songId);
            break;
        }
        case 8: {
            playlist.reverse();
            break;
        }
        case 9: {
            int k;
            std::cout << "Enter k value for K-swap: ";
            std::cin >> k;
            playlist.kSwap(k);
            break;
        }
        case 10: {
            int k;
            std::cout << "Enter k value for shuffle: ";
            std::cin >> k;
            playlist.shuffle(k);
            break;
        }
        case 11: {
            playlist.display();
            break;
        }
        case 12: {
            std::cout << "Exiting program.\n";
            break;
        }
        default: {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (choice != 12);

    return 0;
}
