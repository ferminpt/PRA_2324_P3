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
    BSNode<T>* root;

    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (!n) {
            throw runtime_error("Element not found");
        }
        if (e < n->elem) {//Es menor, recorres a la iquierda
            return search(n->left, e);
        } else if (e > n->elem) {//Es mayor, recorres a la derecha
            return search(n->right, e);
        }
        return n;//devuelve n, caso base, el número es el de la raiz
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (!n) {// N es un punture que va con los nodos, si es distinto de n significa que apunta a null por lo tanto se inserta despues.
            ++nelem;
            return new BSNode<T>(e);
        }
        if (e == n->elem) {//Metodo recursivo para insertar
            throw runtime_error("Duplicated element");
        } else if (e < n->elem) {
            n->left = insert(n->left, e);
        } else {
            n->right = insert(n->right, e);
        }
        return n;
    }

    void print_inorder(ostream &out, BSNode<T>* n) const {//Printea los elementos del arbol
        if (!n) return;
        print_inorder(out, n->left);//Recursivo para señalar izquierda
        out << n->elem << " ";
        print_inorder(out, n->right);//Recursivo para señalar a la derecha
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (!n) {
            throw runtime_error("Element not found");
        }
        if (e < n->elem) {//Recorrido para borrar
            n->left = remove(n->left, e);
        } else if (e > n->elem) {
            n->right = remove(n->right, e);
        } else {
            if (!n->left) {//Si no tiene izquierdo
                BSNode<T>* temp = n->right;
                delete n;
                --nelem;
                return temp;
            } else if (!n->right) {//Si no apunta al derecho
                BSNode<T>* temp = n->left;
                delete n;
                --nelem;
                return temp;
            } else {//Mirar
                T maxVal = max(n->left);
                n->elem = maxVal;
                n->left = remove_max(n->left);
            }
        }
        return n;
    }

    T max(BSNode<T>* n) const {//elemento mayor y ultimo de la derecha
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
        return n;//elimina el ultimo valor de la derecha(el mayor)
    }

    void delete_cascade(BSNode<T>* n) {
        if (!n) return;//Metodo recursivo, borrar elementos izquierda y derecha
	delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }

public:
    BSTree() : root(nullptr), nelem(0) {}//Constructor

    ~BSTree() {
        delete_cascade(root);//Elimina arbol de esa raiz, metodo lanzadera de delete_cascade
    }

    int size() const {//Devuelve el numero de elementos del arbol
        return nelem;
    }

    T search(T e) const {
        return search(root, e)->elem;//Devuelve el elemento buscado
    }

    void insert(T e) {//metodo lanzadera, sacada psudocodigo
        root = insert(root, e);
    }

    void remove(T e) {//Metodo lanzadera
        root = remove(root, e);
    }

    T operator[](T e) const{//metodo lanzadera de search(T e) para devolver el elemento.
        BSNode<T>* node = search(root, e);
        return node->elem;
    }

    friend ostream& operator<<(ostream &out, const BSTree<T> &bst) {
        bst.print_inorder(out, bst.root);//Printea a traves de print_inorder tree con root
        return out;
    } 
};

#endif 
