#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <stdexcept>
#include <string>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"
using namespace std;

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>> tree;//Arbol con elementos de tipo TableEntry<V>.

public:
    BSTreeDict() {}

    ~BSTreeDict() {}

    void insert(string key, V value) override {//Inserta en tree con la llave y el valor que se pasa por referencia.
        tree.insert(TableEntry<V>(key, value));
    }

    V search(string key) override {//Busca el valor del elemento, metodo recursivo, y se pasa como llave, TableEntry(key,V()).valor
        return tree.search(TableEntry<V>(key, V())).value;
    }

    V remove(string key) override {
        TableEntry<V> entry(key, V());
	//Se pasa un TableEntry, llamado entry, con key y un valor ficticio ya que el constructor de TableEntry pasa la key y el value
        V value = tree.search(entry).value; // Obtenemos el valor antes de eliminar utilizando el search de arriba
        tree.remove(entry);
        return value;
    }

    int entries() override {//Devolver el nelem del arbol
        return tree.size();
    }

    V operator[](string key) {//Metodo lanzadera para el search(string key)
        return search(key);
    }

    friend ostream& operator<<(ostream &out, const BSTreeDict<V> &dict) {
        out << dict.tree;//Imprimir el arbol tree= es el arbol con los elementos de TableEntry y dict es el pasado por referencia.
        return out;
    }
};

#endif

