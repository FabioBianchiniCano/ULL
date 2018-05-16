#include <iostream>
#include <cstddef>

using namespace std;

class nodoAVL {
    private:
        int dato, clave, bal;
        nodoAVL *izdo;
        nodoAVL *dcho;

    public:
    friend class ArbolAVL;

    nodoAVL(int dat, int cl, nodoAVL *iz=NULL,nodoAVL *de=NULL) :
        dato(dat),
        clave(cl), bal(0), izdo(iz),
        dcho(de) {}

    int get_data() {
        return dato;
    }
};

class ArbolAVL {
    private:
    nodoAVL *raiz;
    public:

    ArbolAVL():
    raiz(NULL){}

    void rotacion_II (nodoAVL* &nodo) {
        nodoAVL* nodo1 = nodo->izdo;
        nodo->izdo = nodo1->dcho;
        nodo1->dcho = nodo;
        if (nodo1->bal == 1) {
            nodo->bal = 0;
            nodo1->bal = 0;
        }
        else { // nodo1->bal == 0
            nodo->bal = 1;
            nodo1->bal = -1;
        }
        nodo = nodo1;
    }
    void rotacion_DD (nodoAVL* &nodo) {
        nodoAVL* nodo1 = nodo->dcho;
        nodo->dcho = nodo1->izdo;
        nodo1->izdo = nodo ;
        if (nodo1->bal == -1) {
            nodo->bal = 0;
            nodo1->bal = 0;
        }
        else { // nodo1->bal == 0
            nodo->bal = -1;
            nodo1->bal = 1;
        }
        nodo = nodo1;
    }
    void rotacion_ID (nodoAVL* &nodo) {
        nodoAVL* nodo1 = nodo->izdo;
        nodoAVL* nodo2 = nodo1->dcho;
        nodo->izdo = nodo2->dcho;
        nodo2->dcho = nodo;
        nodo1->dcho = nodo2->izdo;
        nodo2->izdo = nodo1;
        if (nodo2->bal == -1){
            nodo1->bal = 1;}
        else {
            nodo1->bal = 0;
            if (nodo2->bal == 1){
                nodo->bal = -1;}
            else {
                nodo->bal = 0;
                nodo2->bal = 0;
                nodo = nodo2;}
    }}
    void rotacion_DI (nodoAVL* &nodo) {
        nodoAVL* nodo1 = nodo->dcho;
        nodoAVL* nodo2 = nodo1->izdo;
        nodo->dcho = nodo2->izdo;
        nodo2->izdo = nodo;
        nodo1->izdo = nodo2->dcho;
        nodo2->dcho = nodo1;
        if (nodo2->bal == 1)
            nodo1->bal = -1;
        else nodo1->bal = 0;
            if (nodo2->bal == -1)
                nodo->bal = 1;
            else nodo->bal = 0;
                nodo2->bal = 0;
                nodo = nodo2;
    }
    void Insertar(int ClaveDada) {
        nodoAVL *nuevo = new nodoAVL( ClaveDada, 0 );
        bool crece = false;
        inserta_bal( raiz, nuevo, crece);
    }
    void inserta_bal(nodoAVL* &nodo, nodoAVL* nuevo, bool &crece) {
        if (nodo == NULL) {
            nodo = nuevo;
            crece = true;
            }
        else if (nuevo->clave < nodo->clave) {
            inserta_bal(nodo->izdo,nuevo,crece);
                if (crece){
                    insert_re_balancea_izda(nodo,crece);//mod añadido bool crece
                }
                else {
                    inserta_bal(nodo->dcho,nuevo,crece);
                    if (crece) insert_re_balancea_dcha(nodo,crece);//mod añadido bool crece
                }
        }
    }
    void insert_re_balancea_izda(nodoAVL* &nodo,bool& crece) {
        switch (nodo->bal) {
            case -1: nodo->bal = 0;
            crece = false;
            break;
            case 0: nodo->bal = 1 ;
            break;
            case 1: nodoAVL* nodo1 = nodo->izdo;
            if (nodo1->bal == 1)
                rotacion_II(nodo);
            else rotacion_ID(nodo);
                crece = false;
        }
    }
    void insert_re_balancea_dcha (nodoAVL* &nodo,bool& crece) {
        switch (nodo->bal) {
            case 1: nodo->bal = 0;
                crece = false;
            break;
            case 0: nodo->bal = -1;
            break;
            case -1: nodoAVL* nodo1 = nodo->dcho;
                if (nodo1->bal == -1)
                rotacion_DD(nodo);
                else rotacion_DI(nodo);
                crece = false;
        }
    }
    void eliminar( int clave_dada) {
        bool decrece = false;
        elimina_rama( raiz, clave_dada, decrece);
    }
    void elimina_rama( nodoAVL* &nodo,int clave_dada, bool& decrece) {
        if (nodo == NULL) return;
        if (clave_dada < nodo->clave) {
            elimina_rama(nodo->izdo,clave_dada,decrece);
        if (decrece)
            eliminar_re_balancea_izda(nodo,decrece);
        }
        else if (clave_dada > nodo->clave) {
            elimina_rama(nodo->dcho,clave_dada,decrece);
        if (decrece)
            eliminar_re_balancea_dcha(nodo,decrece);
        }
        else { // clave_dada == nodo->clave(encontrado)
        nodoAVL* Eliminado = nodo;
        if (nodo->izdo == NULL) {
            nodo = nodo->dcho;
            decrece = true;
        }
        else if (nodo->dcho == NULL) {
            nodo = nodo->izdo;
            decrece = true;
        }
        else {
            sustituye(Eliminado,nodo->izdo,decrece);
        if (decrece)
            eliminar_re_balancea_izda(nodo,decrece);
        }
        delete Eliminado;
        }
    }
    void sustituye(nodoAVL* &eliminado,nodoAVL* &sust, bool &decrece) {
        if (sust->dcho != NULL) {
            sustituye(eliminado, sust->dcho, decrece);
        if (decrece)
            eliminar_re_balancea_dcha(sust, decrece);
        }
        else {
            eliminado->dato = sust->dato;
            eliminado->clave = sust->clave;
            eliminado = sust;
            sust = sust->izdo;
            decrece = true;
        }
    }
    void eliminar_re_balancea_izda (nodoAVL* &nodo, bool& decrece) {
        nodoAVL* nodo1 = nodo->dcho;
        switch (nodo->bal) {
            case -1: //nodoAVL* nodo1 = nodo->dcho; cross refference initialization
            if (nodo1->bal > 0)
                rotacion_DI(nodo);
            else {
                if (nodo1->bal == 0)
                    decrece = false;
                    rotacion_DD(nodo);
                }
            break;
            case 0: nodo->bal = -1;
                decrece = false;
            break;
            case 1: nodo->bal = 0;
        }
    }
    void eliminar_re_balancea_dcha (nodoAVL* &nodo, bool& decrece) {
        nodoAVL* nodo1 = nodo->izdo;
    switch (nodo->bal) {
        case 1: //nodoAVL* nodo1 = nodo->izdo;
        if (nodo1->bal < 0)
            rotacion_ID(nodo);
        else {
        if (nodo1->bal == 0)
            decrece = false;
            rotacion_II(nodo);
        }
        break ;
        case 0: nodo->bal = 1;
            decrece = false;
        break;
        case -1: nodo->bal = 0;
    }
    }

    void llamada() {
        Preorden(raiz);
    }

    void Preorden(nodoAVL *nodo) {
        if (nodo == NULL) {
            //std::cout << "d\n";
            return;
        }
        Preorden(nodo->izdo);
        write(nodo->dato);
        Preorden(nodo->dcho);
    }

    ostream& write(int dato) {
        ostream&os=std::cout;
        os << dato << std::endl;
        return os;
    }


};
