#ifndef BST_H
#define BST_H

#include <iostream>

template <class T>
struct node {
	T data;
	node<T>* left;	//left child
	node<T>* right; //left child
};

template <class T>
class BST {
	node<T>* root;

	public:
		BST(){root = NULL;}	    // constructor for empty tree
		void initialize();			// deletes all nodes in the BST
		void insert(T&);	    	// add element to tree (maintain ordering)
		void printPreOrder();		// print elements in pre-order
		void printInOrder();		// print elements in-order
		void printPostOrder();	// print elements in post-order
		T search(T&);	    	// return true if element is found in BST
		void deleteNode(T&);		// removes the element if it exists in BST
		int height();		    		// returns the height of the BST
		T findMax();		    		// returns the 'maximum' element in the BST
		T findMin(); 		    		// returns the 'minimum' element in the BST
	private:
		void deleteNode(node<T>*&, T&);	// removes the element if it exists in BST
		void insert(node<T>*&, T&);     // recursive helper function to insert element in BST
		void printPreOrder(node<T>*);		// recursive helper function to print elements in pre-order
		void printInOrder(node<T>*);		// recursive helper function to print elements in-order
		void printPostOrder(node<T>*);	// recursive helper function to print elements in post-order
		T findMax(node<T>*);    	  // recursive helper function to find maximum element of the BST
		T search(node<T>*, T&);      // recursive helper function to find out if an element is in the BST

};

template <class T>
void BST<T>::insert(T& item) {
	insert(root, item);	// call recursive insert function
}

template <class T>
void BST<T>::insert(node<T>*& p, T& item) {

	// if p is null, create a new node w/ item
	if(p == NULL) {
		p = new node<T>;	// create new node pointed by p
		p-> data = item;	// set new node's data equal to item

		// set both node pointers in the new node to NULL
		p->left = NULL;
		p->right = NULL;
	} else if(item < (p->data)) { // if item is less-than current node, insert in left subtree
		insert(p->left, item);
	} else { // if the item is greater-than current node, insert in right subtree
		insert(p->right, item);
	}
}

template <class T>
void BST<T>::printPreOrder() {
	printPreOrder(root);
}

template <class T>
void BST<T>::printInOrder() {
	printInOrder(root);
}

template <class T>
void BST<T>::printPostOrder() {
	printPostOrder(root);
}

template <class T>
void BST<T>::printPreOrder(node<T>* p) {
	if(p != NULL) {
		std::cout << (p->data) << std::endl;
		printPreOrder(p->left);
		printPreOrder(p->right);
	}
}

template <class T>
void BST<T>::printInOrder(node<T>* p) {
	if(p != NULL) {
		printPreOrder(p->left);
		std::cout << (p->data) << std::endl;
		printPreOrder(p->right);
	}
}

template <class T>
void BST<T>::printPostOrder(node<T>* p) {
	if(p != NULL) {
		printPreOrder(p->left);
		printPreOrder(p->right);
		std::cout << (p->data) << std::endl;

	}
}

template <class T>
T BST<T>::search(T& item) {
	return search(root, item);
}

template <class T>
T BST<T>::search(node<T>* p, T& item) {
	if(p == NULL)
		throw std::exception();
	else if(item < p->data)
		return search(p->left, item);
	else if(item > p->data)
		return search(p->right, item);
	else
		return p->data;
}

template <class T>
T BST<T>::findMax() {
	return findMax(root);
}

template <class T>
T BST<T>::findMax(node<T>* p) {
	if(p==NULL)
		throw std::exception();
	else if (p->right == NULL)
		return p->data;
	else
		return findMax(p->right);

}
template <class T>
void BST<T>::deleteNode(node<T>*& p, T& item) {
	if(p == NULL)
		return;
	node<T>* temp = p;
	if(item < p->data)
		deleteNode(p->left, item);
	else if(item > p->data)
		deleteNode(p->right, item);

	// element found; handle three cases - case 1: leaf node,
	// case 2: one child, case 3: two children
	else {
		if(p->right != NULL && p->left != NULL) { //case 3
			T max = findMax(p->left, item);
			p->data = max;
			deleteNode(p->left, max);
		} else { //case 1 or 2
			if(p->left != NULL) { //case two; one left child
				p = p->left;
			} else if(p->right != NULL) { //case two;
				p = p->right;
			} else { //case 1
				p = NULL;
			}
		}
		delete temp;
	}
}
#endif /* BST_H */
