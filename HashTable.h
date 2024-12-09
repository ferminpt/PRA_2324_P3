#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"
using namespace std;

template <typename V>
class HashTable: public Dict<V> {

private:
	int n;//Numero de elementos almacenados en la Tabla
	int max;//Tamaño Tabla Hash
	ListLinked<TableEntry<V>>* table;
	//Devuelve la posicion de key en la tabla hash
	int h(string key){
		int n = key.length();//Longitud de la key la guardas en n
		int sum = 0;
		char c;

		for(int i=0; i<n; i++){
			c = key.at(i);//Guarda el valor situado en la posicion i
			sum += int(c);//Permite obtener el valor ASCII numérico del carácter c.
		}

		return sum % max;//La posicion se devuelve con el resto entre la suma de los valores ASCII y el tamaño de la tabla hash 
	};

public:
    HashTable(int size) : n(0), max(size) {//inicializar valores:Valores almacenados 0 y max igual a size
	table =new ListLinked<TableEntry<V>>[max];//Tabla con ListLinked y tamaño max igualado anteriormente.
    }

    ~HashTable() {
        delete[] table;//Borrar la tabla
    }

    void insert(string key, V value) override {
        int index = h(key);//Con h(key) devolvemos la posicion que queremos y la guardamos en index
        ListLinked<TableEntry<V>>& bucket = table[index];//Creamos una tabla de indice hasta el que hemos econtrado.
        for (int i = 0; i < bucket.size(); ++i) {//Hacemos un recorrido con el tamaño
            if (bucket.get(i).key == key) {//Si cuincide no la podemos insertar.Runtime
                throw runtime_error("La clave ya existe en el diccionario.");
            }
        }
        bucket.insert(bucket.size(), TableEntry<V>(key, value));//Lo insertamos con insert, bucket.size()es la posición, y Table Entry<v>(key, v	//alue) es el valor
        ++n;
    }

    V search(string key) override {
        int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];
        for (int i = 0; i < bucket.size(); ++i) {
            if (bucket.get(i).key == key) {
                return bucket.get(i).value;//Devolvemos el valor de esa key
            }
        }
        throw runtime_error("Clave no encontrada en el diccionario.");
    }

    V remove(string key) override {
        int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];
        for (int i = 0; i < bucket.size(); ++i) {
            if (bucket.get(i).key == key) {
                V value = bucket.get(i).value;//Guardamos el valor
                bucket.remove(i);//borramos con remove la llave
                --n;//rectamos una al tamaño
                return value;
            }
        }
        throw runtime_error("Clave no encontrada en el diccionario.");
    }

    int entries() override {//Devuelve el número de elementos actualmente almacenados en la tabla
        return n;
    }

    int capacity() {//Devuelve el numero de cubetas de la tabla.
        return max;
    }

    friend ostream& operator<<(ostream &out,const  HashTable<V> &th) {//Imprimir contenido Tabla Hash por pantalla.
        for (int i = 0; i < th.max; ++i) {
            out << "Cubeta " << i << ": ";
            ListLinked<TableEntry<V>>& bucket = th.table[i];
            if (bucket.size() == 0) {
                out << "(vacía)";
            } else {
                for (int j = 0; j < bucket.size(); ++j) {
                    out << "[" << bucket.get(j).key << " -> " << bucket.get(j).value << "] ";
                }
            }
            out << endl;
        }
        return out;
    }

    V operator[](string key) {//Devuelve el valor correspondiente a key
        return search(key);
    }


};

#endif

