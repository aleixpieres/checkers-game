#ifndef ARBRE_H
#define ARBRE_H

#include <string>
#include <cstdlib>
#include <iostream>

/// -----------------------------------------
///
///  Declaraci� operacions tipus ARBRE BINARI
///
/// -----------------------------------------

template <typename T>
class arbre {

  private:
    struct node {
      node* f_esq;
      node* f_dret;
      T info;
    };
    node* _arrel;

    static node* copia_nodes(node* m);
    /* Pre: cert */
    /* Post: si m �s NULL, el resultat �s NULL; sin�,
       el resultat apunta al primer node d'un arbre binari
       de nodes que s�n c�pia de l'arbre apuntat per m */
    static void esborra_nodes(node* m);
    /* Pre: cert */
    /* Post: no fa res si m �s NULL, sin� allibera
       espai dels nodes de l'arbre binari apuntat per m */

  public:
    //constructors
    arbre();
    /* Pre: cert */
    /* Post: el resultat �s un arbre sense cap element */
    arbre(const arbre<T> &a);
    /* Pre: cert */
    /* Post: el resultat �s una c�pia de l'arbre rebut */
    arbre(const T &x,const arbre<T> &ae,const arbre<T> &ad);
    /* Pre: cert */
    /* Post: el resultat �s un arbre amb un element i dos
       subarbres */

   //destructor: esborra autom�ticament els objectes locals
   //en sortir d'un �mbit de visibilitat
   ~arbre();

    //modificadors
    void a_buit();
    /* Pre: cert */
    /* Post: el par�metre impl�cit no t� cap element */
    arbre<T>& operator=(const arbre<T> &a);
    /* Pre: cert */
    /* Post: operaci� d'assignaci� d'arbres  */

   //consultors
   const T& arrel() const;
   /* Pre: el par�metre impl�cit no �s buit */
   /* Post: el resultat �s l'arrel del par�metre impl�cit */
   arbre<T> fe() const;
   /* Pre: el par�metre impl�cit no �s buit */
   /* Post: el resultat �s el fill esquerre del p.i. original */
   arbre<T> fd() const;
   /* Pre: el par�metre impl�cit no �s buit */
   /* Post: el resultat �s el fill dret del p.i. original */
   bool es_buit() const;
   /* Pre: cert */
   /* Post: el resultat indica si el p.i. �s buit o no */
};


/// ------------------------------------------
///
///  Codificaci� operacions tipus ARBRE BINARI
///
/// ------------------------------------------

//privades ----------------------
template <typename T>
typename arbre<T>::node* arbre<T>::copia_nodes(node* m) {
  node* n;
  if (m == NULL) n = NULL;
  else {
    n = new node;
    try {
      n->info = m->info;
      n->f_esq = copia_nodes(m->f_esq);
      n->f_dret = copia_nodes(m->f_dret);
    } catch(...) {
      delete n;
      throw;
    }
  }
  return n;
};

template <typename T>
void arbre<T>::esborra_nodes(node* m) {
  if (m != NULL) {
    esborra_nodes(m->f_esq);
    esborra_nodes(m->f_dret);
    delete m;
  }
};

//constructors ----------------------
template <typename T>
arbre<T>::arbre()
/* Pre: cert */
/* Post: el resultat �s un arbre sense cap element */
{
  _arrel = NULL;
}

template <typename T>
arbre<T>::arbre(const arbre<T>& a)
/* Pre: cert */
/* Post: el resultat �s una c�pia de a */
{
  _arrel = copia_nodes(a._arrel);
}

template <typename T>
arbre<T>::arbre(const T& x, const arbre<T>& ae, const arbre<T>& ad)
/* Pre: cert */
/* Post: el resultat �s un arbre amb x com arrel, ae com a fill
esquerre i ad com a fill dret */
{
  _arrel = new node;
  try {
    _arrel->info = x;
    _arrel->f_esq = copia_nodes(ae._arrel);
    _arrel->f_dret = copia_nodes(ad._arrel);
  }
  catch (...) {
    delete _arrel;
    throw;
  }
}

//destructor ----------------------
template <typename T>
arbre<T>::~arbre() {
  esborra_nodes(_arrel);
}

//modificadors ----------------------
template <typename T>
void arbre<T>::a_buit()
/* Pre: cert */
/* Post: el par�metre impl�cit no t� cap element */
{
  esborra_nodes(_arrel);
  _arrel = NULL;
}

template <typename T>
arbre<T>& arbre<T>::operator=(const arbre<T>& a) {
  if (this != &a) {
    node* aux;
    aux = copia_nodes(a._arrel);
    esborra_nodes(_arrel);
    _arrel = aux;
  }
  return (*this);
}

//consultors ----------------------
template <typename T>
const T& arbre<T>::arrel() const {
/* Pre: el par�metre impl�cit no �s buit */
/* Post: el resultat �s l'arrel del par�metre impl�cit */
  if (this->es_buit()) {
    std::cout<<"ERROR - Operaci� 'arrel' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  return _arrel->info;
}

template <typename T>
arbre<T> arbre<T>::fe() const
/* Pre: el par�metre impl�cit no �s buit */
/* Post: el resultat �s el fill esquerre del p.i. original */
{
  if (this->es_buit()) {
    std::cout<<"ERROR - Operaci� 'fe' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  arbre<T> a;
  a._arrel = copia_nodes(_arrel->f_esq);
  return a;
}

template <typename T>
arbre<T> arbre<T>::fd() const
/* Pre: el par�metre impl�cit no �s buit */
/* Post: el resultat �s el fill dret del p.i. original */
{
  if (this->es_buit()) {
    std::cout<<"ERROR - Operaci� 'fd' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  arbre<T> a;
  a._arrel = copia_nodes(_arrel->f_dret);
  return a;
}

template <typename T>
bool arbre<T>::es_buit() const
/* Pre: cert */
/* Post: el resultat indica si el p.i. �s buit o no */
{
  return (_arrel == NULL);
}

#endif
