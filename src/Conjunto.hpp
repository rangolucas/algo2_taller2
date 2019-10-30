#include <stack>

template <class T>
Conjunto<T>::Conjunto() {
    this->_raiz = nullptr;
}

template <class T>
Conjunto<T>::~Conjunto() {
  int i = 0;
  int cardinal = this->cardinal();
  T actual = this->minimo();
  while(i < cardinal) {
      this->remover(actual);
      actual = this->siguiente(actual);
      i++;
  }
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
            Nodo *nodoABorrar;
            if(actual->izq == nullptr) nodoABorrar = actual->der;
            else nodoABorrar = actual->izq;
            actual->valor = nodoABorrar->valor;
            delete nodoABorrar;
            break;
        case 2:
            const Nodo *sucesor = this->_sucesor(actual);
            const T valorSucesor = sucesor->valor;
            this->remover(valorSucesor);
            actual->valor = valorSucesor;
            break;
    }
}

template <class T>
const class Conjunto<T>::Nodo* Conjunto<T>::_sucesor(const Nodo* nodo) const {
    Nodo* actual = nodo->der;
    while(actual->izq != nullptr) {
      actual = actual->izq;
    }
    return actual;
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    const Nodo* nodoClave = this->_buscar(clave, this->_raiz);
    return this->_sucesor(nodoClave)->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* actual = this->_raiz;
    while(actual->izq != nullptr) {
      actual = actual->izq;
    }

    return actual->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
  Nodo* actual = this->_raiz;
  while(actual->der != nullptr) {
    actual = actual->der;
  }

  return actual->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    if(this->_raiz == nullptr) return 0;
    return this->_raiz->contarSubnodos();
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& o) const {
    int i = 0;
    int cardinal = this->cardinal();
    T actual = this->minimo();
    while(i < cardinal) {
        o << actual + " ";
        actual = this->siguiente(actual);
        i++;
    }
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

template<class T>
const int Conjunto<T>::Nodo::cantidadHijos() const {
  int cantidad = 0;
  if(this->izq != nullptr) cantidad++;
  if(this->der != nullptr) cantidad++;
  return cantidad;
}

template<class T>
const unsigned int Conjunto<T>::Nodo::contarSubnodos() const {
  int subnodos = 0;
  if(this->izq != nullptr) {
    subnodos += 1 + this->izq->contarSubnodos();
  }

  if(this->der != nullptr) {
    subnodos += 1 + this->der->contarSubnodos();
  }

  return subnodos;
}

template<class T>
Conjunto<T>::Nodo::Nodo(const T &v) : valor(v), izq(nullptr), der(nullptr){}
