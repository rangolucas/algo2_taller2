#include <stack>

template <class T>
Conjunto<T>::Conjunto() {
    this->_raiz = nullptr;
}

template <class T>
Conjunto<T>::~Conjunto() { 
    // Completar
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    return _buscar(clave, this->_raiz) != nullptr;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    Nodo *nuevoNodo = new Nodo(clave);
    
    if(this->_raiz == nullptr) {
        this->_raiz = nuevoNodo;
        return;
    }

    Nodo *anterior = this->_raiz;
    Nodo *actual = anterior;

    while(actual != nullptr) {
        anterior = actual;
        if(clave < actual->valor) {
            actual = actual->izq;
        } else {
            actual = actual->der;
        }
    }

    if(clave < anterior->valor) {
        anterior->izq = nuevoNodo;
    } else {
        anterior->der = nuevoNodo;
    }

    return;
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    Nodo *actual = this->_raiz;
    Nodo *anterior = actual;
    while(actual->valor != clave) {
        if(clave < actual->valor) actual = actual->izq;
        else actual = actual->der;
    }

    switch(actual->cantidadHijos()) {
        case 0:
            if(anterior->izq == actual) anterior->izq = nullptr;
            else anterior->der = nullptr;
            delete actual;
            break;
        case 1:
            if(actual->izq == nullptr) actual->valor = actual->der->valor;
            delete actual->der;
            break;
        case 2: {
            const Nodo *sucesor = this->_sucesor(actual);
            actual->valor = sucesor->valor;
            delete sucesor;
        }
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo *anterior = this->_raiz;
    Nodo *actual = anterior;

    while(actual != nullptr) {
        if(clave < actual->valor) actual = actual->izq;
        else actual = actual->der;
    }
}

template <class T>
const T& Conjunto<T>::minimo() const {
    assert(false);
}

template <class T>
const T& Conjunto<T>::maximo() const {
    assert(false);
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    assert(false);
    return 0;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

template<class T>
const class Conjunto<T>::Nodo* Conjunto<T>::_buscar(const T &clave, const Conjunto::Nodo *nodo) const {
    if(nodo == nullptr) {
        return nullptr;
    }

    if(nodo->valor == clave) {
        return nodo;
    }

    if(clave < nodo->valor) {
        return _buscar(clave, nodo->izq);
    }

    if(clave > nodo->valor) {
        return _buscar(clave, nodo->der);
    }
}

