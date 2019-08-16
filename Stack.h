#include "Node.h"

#ifndef STACK_H_
#define STACK_H_

template <class T>
class Stack {
public:
    Node<T> *top;

    Stack();

    bool push(T item);

    bool pop(T *item);

    int size();

    bool isEmpty();
};

#endif /* STACK_H_ */

template <class T>
Stack<T>::Stack() {
    this->top = 0;
}

template <class T>
bool Stack<T>::push(T item) {
    Node<T> *pto = Node<T>::montaNo(item);

    if (!pto) {
        return false;
    }
    pto->next = top;
    top = pto;
    return true;
}

template <class T>
bool Stack<T>::pop(T *item) {
    Node<T> *pto = new Node<T>;

    if (!top) {
        return false;
    }
    pto = top;
    top = pto->next;
    *item = Node<T>::desmontaNo(pto);
    return true;
}

template <class T>
int Stack<T>::size() {
    int size = 0;
    Node<T> *pto = top;

    while (pto) {
        pto = pto->next;
        size++;
    }
    return size;
}

template <class T>
bool Stack<T>::isEmpty() {
    return (!top);
}









