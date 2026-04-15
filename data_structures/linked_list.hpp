#pragma once

#include <cassert>

/* these are just basic versions, you can clearly add tons of function, note that
   singly linked list has more functions just not to add them everywhere  */
namespace algo {

template <class T> struct LinkedList {
    struct Node {
        T val;
        Node *next;
    };

    Node *head;

    LinkedList() { head = nullptr; }

    // the copy constructor is a must to avoid safety problems with contextual assignment an declaration
    LinkedList(const LinkedList &l) {
        head = nullptr;
        *this = l;
    }

    ~LinkedList() { clear(); }

    void push_front(T k) {
        Node *p = new Node;
        p->next = head;
        p->val = k;
        head = p;
    }

    void pop_front() {
        assert(head != nullptr);
        Node *p = head;
        head = p->next;
        delete p;
    }

    void push_back(T k) {
        if (head == nullptr) {
            push_front(k);
            return;
        }

        Node *p = head;
        while (p->next != nullptr) {
            p = p->next;
        }
        Node *q = new Node;
        q->next = nullptr;
        q->val = k;
        p->next = q;
    }

    void pop_back() {
        assert(head != nullptr);
        if (head->next == nullptr) {
            pop_front();
            return;
        }

        Node *p = head;
        while (p->next->next != nullptr) {
            p = p->next;
        }
        delete p->next;
        p->next = nullptr;
    }

    void reverse() {
        if (head == nullptr || head->next == nullptr) return;
        Node *p = head->next;
        Node *q;
        head->next = nullptr;
        while (p != nullptr) {
            q = p->next;
            p->next = head;
            head = p;
            p = q;
        }
    }

    Node *find(T k) {
        Node *p = head;
        while (p != nullptr && p->val != k) p = p->next;
        return p;
    }

    void clear() {
        while (head != nullptr) pop_front();
    }

    LinkedList &operator=(const LinkedList &l) { // to avoid safety problems with contextual assignment
        clear();
        Node *pl = l.head;
        while (pl != nullptr) {
            push_front(pl->val);
            pl = pl->next;
        }
        reverse();
        return *this;
    }
};


template <class T> struct DoublyLinkedList {
    struct Node {
        T val;
        Node *next;
        Node *prev;
    };

    Node *head;
    Node *tail;

    DoublyLinkedList() { head = tail = nullptr; }

    // the copy constructor is a must to avoid safety problems with contextual assignment and declaration
    DoublyLinkedList(const DoublyLinkedList &l) {
        head = tail = nullptr;
        *this = l;
    }

    ~DoublyLinkedList() { clear(); }

    void push_front(T k) {
        Node *p = new Node;
        if (tail == nullptr) tail = p;
        else head->prev = p;
        p->val = k;
        p->prev = nullptr;
        p->next = head;
        head = p;
    }

    void push_back(T k) {
        Node *p = new Node;
        if (head == nullptr) head = p;
        else tail->next = p;
        p->val = k;
        p->next = nullptr;
        p->prev = tail;
        tail = p;
    }

    void pop_front() {
        assert(head != nullptr);
        if (head->next == nullptr) {
            delete head;
            head = tail = nullptr;
        } else {
            Node *p = head->next;
            delete head;
            p->prev = nullptr;
            head = p;
        }
    }

    void pop_back() {
        assert(tail != nullptr);
        if (tail->prev == nullptr) {
            delete tail;
            head = tail = nullptr;
        } else {
            Node *p = tail->prev;
            delete tail;
            p->next = nullptr;
            tail = p;
        }
    }

    void clear() {
        while (head != nullptr) pop_front();
    }

    DoublyLinkedList &operator=(const DoublyLinkedList &l) { // to avoid safety problems with contextual assignment
        clear();
        Node *pl = l.head;
        while (pl != nullptr) {
            push_back(pl->val);
            pl = pl->next;
        }
        return *this;
    }
};

} // namespace algo