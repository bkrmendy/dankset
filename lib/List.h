#ifndef HASHSET_LIST_H
#define HASHSET_LIST_H

#include <memory>

template <typename Key>
class List {

    struct Node {
        Key data;
        Node* next;

        Node(Key data) : data{data}, next{nullptr} {}

        void remove(const Key& key) {
            if (this->next == nullptr) {
                return;
            }
            if (this->next->data == key) {
                Node* temp = this->next->next;
                delete this->next;
                this->next = temp;
                return;
            }
            this->next->remove(key);
        }
    };

    Node* front;

public:
    List() = default;

    void push_front(Key key) {
        Node* temp = new Node{key};
        temp->next = this->front;
        this->front = temp;
    }

    size_t size() const {
        size_t size = 0;
        Node* current = this->front;
        while (current != nullptr) {
            size += 1;
            current = this->front->next;
        }
        return size;
    }

    bool contains(const Key& key) const {
        Node* current = this->front;
        while (current != nullptr) {
            if (current->data == key) {
                return true;
            }
            current = this->front->next;
        }
        return false;
    }

    void remove(const Key& key) {
        if (this->front == nullptr) {
            return;
        }
        if (this->front->data == key) {
            Node* temp = this->front->next;
            delete this->front;
            this->front = temp;
            return;
        }
        this->front->remove(key);
    }

    void dump(std::ostream& o) {
        Node* current = this->front;
        while (current != nullptr) {
            o << current->data << " ";
            current = current->next;
        }
    }

    void clear() {
        while (this->front != nullptr) {
            Node* next = this->front->next;
            delete this->front;
            this->front = next;
        }
    }

    ~List() {
        this->clear();
    }
};

#endif //HASHSET_LIST_H
