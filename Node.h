#ifndef NODE_H_
#define NODE_H_

template <class T>
class Node {
public:
	T item;
	Node<T> *next;
	
	Node();
	static Node<T> *montaNo(T novoItem);
	static T desmontaNo(Node<T> *pto);
};

#endif /* NODE_H_ */

template <class T>
Node<T>::Node() {}

template <class T>
Node<T> *Node<T>::montaNo(T novoItem) {
    Node *pto;
    pto = new Node;

	if (!pto) {
		return pto;
	}
	pto->item = novoItem;
	pto->next = 0;
	return pto;
}

template <class T>
T Node<T>::desmontaNo(Node<T> *pto) {
	T meuItem = pto->item;
    delete pto;
    return meuItem;
}



