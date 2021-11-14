#ifndef HASHSET_LIST_H
#define HASHSET_LIST_H

#include <memory>

template <typename Key>
class List {

    struct Node {
        Key data;
        std::unique_ptr<Node> next;

        Node(Key data) : data{data}, next{nullptr} {}

        size_t size() const {
            if (this->next == nullptr) {
                return 1;
            }
            return this->next->size() + 1;
        }

        bool contains(const Key& key) const {
            if (this->data == key) {
                return true;
            }
            if (this->next == nullptr) {
                return false;
            }
            return this->next->contains(key);
        }

        void remove(const Key& key) {
            if (this->next == nullptr) {
                return;
            }
            if (this->next->data == key) {
                this->next = std::move(this->next->next);
                return;
            }
            this->next->remove(key);
        }
    };

    std::unique_ptr<Node> front;

public:
    List() = default;

    void push_front(Key key) {
        auto temp{std::make_unique<Node>(key)};
        temp->next = std::move(this->front);
        this->front = std::move(temp);
    }

    size_t size() const {
        if (this->front == nullptr) {
            return 0;
        }
        return this->front->size();
    }

    bool contains(const Key& key) const {
        if (this->front == nullptr) {
            return false;
        }
        return this->front->contains(key);
    }

    void remove(const Key& key) {
        if (this->front == nullptr) {
            return;
        }
        if (this->front->data) {
            this->front = nullptr;
            return;
        }
        this->front->remove(key);
    }
};

#endif //HASHSET_LIST_H
