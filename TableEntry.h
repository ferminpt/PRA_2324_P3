#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

using namespace std;

template <typename V>
class TableEntry {
    public:
        string key;
        V value;
	//metodo constructor
        TableEntry (string key, V value){
                this->key = key;
                this->value = value;
        }
	//Una entrada solo con la llave
        TableEntry (string key){
                this->key = key;
        }
	//Entrada con la llave vacia
        TableEntry (){
                key = "";
        }
	//Asegurarse que dos instancias de TableEntry son iguales solo si comparten la misma llave
        friend bool operator== (const TableEntry<V> &te1, const TableEntry<V> &te2){
                return te1.key == te2.key;
        }
	//Asegurarse que dos instancias de TableEntry son distintas si sus llaves son distintas independientemente del valor que contengan
        friend bool operator!= (const TableEntry<V> &te1, const TableEntry<V> &te2) {
                return te1.key != te2.key;
        }
	//Imprimir la clave y el valor con el operador <<
        friend ostream& operator<<(ostream &out, const TableEntry<V> &te) {
                out << "Clave: " << te.key << "| Valor: " << te.value;
                return out;
        }

	bool operator<(const TableEntry& other) const {
        	return key < other.key;
    	}

    	bool operator>(const TableEntry& other) const {
        	return key > other.key;
    	}

};

#endif
