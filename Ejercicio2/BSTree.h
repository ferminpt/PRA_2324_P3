#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"
using namespace std;
template <typename T> 
class BSTree {
    private:
       int nelem;
       BSNode<T> *root;

       BSNode<T>* search(BSNode<T>* n, T e) const{
		if( !n){
			throw runtime_error("Element not found");
		}
		if( e < n->elem){
			return search(n->left,e);
		}
		else if( e >n->elem){
			return search(n->right,e);
		}
		return n;
}
      BSNode<T>* insert(BSNode<T>* n, T e){
		if( !n){//No es el arbol con la raiz que buscamos, por tanto en elemento se inserta el primero, acaba siendo la raiz.
                       ++nelem;
           	       return new BSNode<T>(e);
                }
                if (e == n->elem) {//Elemento repetido
           	       throw runtime_error("Duplicated element");
        	} 	
		else if (e < n->elem) {//Se coloca en la izquierda, ya que es menor
            	       n->left = insert(n->left, e);
        	} 	
		else {//se coloca en la derecha ya que es mayor
            	       n->right = insert(n->right, e);
        	}
        	return n;
}
      void print_inorder(std::ostream &out, BSNode<T>* n) const{//Entender
	 	if (!n) return;
        	print_inorder(out, n->left);
        	out << n->elem << " ";
        	print_inorder(out, n->right);
}

       BSNode<T>* remove(BSNode<T>* n, T e) {
        	if (!n) {
            	throw runtime_error("Element not found");
        }
        	if (e < n->elem) {
            	n->left = remove(n->left, e);
        } 
		else if (e > n->elem) {
            	n->right = remove(n->right, e);
        } 
		else {
            		if (!n->left) {
                	BSNode<T>* temp = n->right;
                	delete n;
                	--nelem;
                	return temp;
        	} 
		else if (!n->right) {
                	BSNode<T>* temp = n->left;
                	delete n;
                	--nelem;
                	return temp;
          	 }	 
		 else {
                	T maxVal = max(n->left);
                	n->elem = maxVal;
                	n->left = remove_max(n->left);
            	}
        }
        		return n;
}
	
	T max(BSNode<T>* n) const {
        	while (n->right) {
            	n = n->right;
        }
        	return n->elem;
}

	BSNode<T>* remove_max(BSNode<T>* n) {
        	if (!n->right) {
            	return n->left;
        }
        	n->right = remove_max(n->right);
        	return n;
}
	
	void delete_cascade(BSNode<T>* n) {
        	if (!n) return;
        	delete_cascade(n->left);
       		 delete_cascade(n->right);
        	delete n;
}

    public:
        BSTree(){
	root = nullptr;
	nelem =0;
}
    	int size() const{
		return nelem;

}
	T search(T e) const{
		return search(root, e)->elem;
}
	T operator[](T e) const{
		BSNode<T> *node=search(root,e);
		return node -> elem; //Igualar el nodo a la funcion search que devuelve el elemento que buscamos(e) dentro del arbol, si 			lo encontramos se guarda en el nodo y se devuelve el nodo.

}
	void insert(T e){
		root =insert(root,e);
}
	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){//Entender
		bst.print_inorder(out, bst.root);
        	return out;
} 	
	void remove(T e) {
        root = remove(root, e);
}
	~BSTree() {
        delete_cascade(root);
}





};

#endif
