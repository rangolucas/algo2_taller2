#include <stack>

template <class T>
Conjunto<T>::Conjunto() {
    this->_raiz = nullptr;
}

template <class T>
Conjunto<T>::~Conjunto() {
  int i = 0;
  int cardinal = this->cardinal();
  if(cardinal == 0) return;
  T actual = this->minimo();
  while(i < cardinal) {
      this->remover(actual);
      actual = this->siguiente(actual);
      i++;
  }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Iterador iterador = Iterador();
    iterador.st.push(this->_raiz);
    return _buscar(clave, iterador).actual() != nullptr;
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

//pre: nodo tiene hijo derecho
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
    Iterador iterador = Iterador();
    iterador.st.push(this->_raiz);
    const Iterador &it = this->_buscar(clave, iterador);
    return it.siguiente()->valor;
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
    return this->_raiz->contarSubnodos() + 1;
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
const class Conjunto<T>::Iterador Conjunto<T>::_buscar(const T &clave, Iterador iterador) const {
    Nodo *pNodo = iterador.actual();
    if(pNodo == nullptr || pNodo->valor == clave) {
        return iterador;
    }

    if(clave < pNodo->valor) {
        iterador.st.push(pNodo->izq);
        return _buscar(clave, iterador);
    }

    if(clave > pNodo->valor) {
        iterador.st.push(pNodo->der);
        return _buscar(clave, iterador);
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
  unsigned int subnodos = 0;
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


template<class T>
Conjunto<T>::Iterador::Iterador(){
    this->st = stack<Nodo*>();
}

template<class T>
typename Conjunto<T>::Nodo* Conjunto<T>::Iterador::actual() const {
    return this->st.top();
}

//pre: hay siguiente
template<class T>
typename Conjunto<T>::Nodo* Conjunto<T>::Iterador::siguiente() const {
}
