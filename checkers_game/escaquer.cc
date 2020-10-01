#include <iostream>
#include <algorithm>
#include <math.h>
#include "escaquer.h"

///////////////////////////////////////////
//// Implementació de la classe escaquer ///


escaquer::escaquer(nat n) {
//Pre: n és parell i n>= 8
//Post: crea un escaquer de mida n x n inicialitzada amb les peces inicials d'una partida de Dames.
  // crea taula de mida n x n
  taula = vector<vector<casella> >(n,vector<casella>(n,casella()));

  // inicialitza les caselles del escaquer
  for (unsigned int i = 0; i < n; ++i) {
    for (unsigned int j = 0; j < n; ++j){
      if (i < 3) {
        if (i%2 == 0) {
          if (j%2 != 0) taula[i][j].omple(casella::NEGRA);
        }
        else {
          if (j%2 == 0) taula[i][j].omple(casella::NEGRA);
        }
      }
      else if (i > n - 4) {
        if (i%2 == 0) {
          if (j%2 != 0) taula[i][j].omple(casella::BLANCA);
        }
        else {
          if (j%2 == 0) taula[i][j].omple(casella::BLANCA);
        }
      } 
    }
  }
  
}


bool escaquer::dins_limits(coord p) const {
// Pre: *Cert*
// Post: Diu si les coord p estan dins dels limits del escaquer.
  bool b;
  int size = taula.size();
  if (p.x < size and p.x >= 0 and p.y < size and p.y >= 0) b = true;
  else b = false;
  return b;

}


casella& escaquer::operator()(coord p) {
// Pre: *Cert*
// Post: Escriu a la pantalla el contingut del escaquer.
  if (dins_limits(p)) {
	
     return taula[p.x][p.y];
  }
}

void escaquer::mostra() const {
// Pre: 0 <= color < 5
// Post: treu per pantalla el contingut del escaquer marcant amb '?'
// les caselles on es poden posar fitxes del color donat.
  cout<<" ";
  for (unsigned int t = 1; t <= taula.size(); ++t) cout << " " << t;
  cout << endl;
  for (unsigned int i = 0; i < taula.size(); ++i) {
    cout << i + 1 << " ";
    for (unsigned int j = 0; j < taula.size(); ++j) {
      cout << taula[i][j].mostra() << " ";
    }
    cout << endl;
  }
}


void escaquer::mostra(int color) const {
// Pre: *Cert*
// Post: dona el valor de restar el número de 
// blanques menys el número de negres.
  direccio dir;
  dir.init();
  coord c,c2;
  bool b = false, t = false;
  vector <coord> vc;
  cout << " ";
  for (unsigned int t = 1; t <= taula.size(); ++t) cout << " " << t;
  cout << endl;
  for (unsigned int i = 0; i < taula.size(); ++i) {
    for (unsigned int j = 0; j < taula.size(); ++j) {
      coord c2(i, j);
      if (taula[i][j].valor() == color) { 
        if (color == 1) {
          while (dir.getDireccio() < 2){
            es_pot_capturar(c2, dir, b, c);

            if (b) {
              for (unsigned int a = 0; a < vc.size(); ++a){
                if (c == vc[a]) t = true; 
              } 
              if (not t) { 
                vc.push_back(c);
              }
            }
            t = false;
            ++dir;
          }
          dir.init();
          while (dir.getDireccio() < 2){
            es_pot_despl(c2, dir, b, c);
            if (b) {
              for (unsigned int a = 0; a < vc.size(); ++a){
                if (c == vc[a]) t = true; 
              }
              if (not t) { 
                vc.push_back(c);
              }
            }
            t = false;
            ++dir;
          }
        }
        else if (color == -1) {
          ++dir;
          ++dir;
          ++dir;
            es_pot_capturar(c2, dir, b, c);
            if (b) {
              for (unsigned int a = 0; a < vc.size(); ++a){
                if (c == vc[a]) t = true; 
              }
              if (not t){ 
                vc.push_back(c);
              }
            }
            t = false;
            dir.init();
            ++dir;
            ++dir;
            es_pot_capturar(c2, dir, b, c);
            if (b) {
              for (unsigned int a = 0; a < vc.size(); ++a){
                if (c == vc[a]) t = true; 
              }
              if (not t){ 
                vc.push_back(c);
              }
            }
            dir.init();
          ++dir;
          ++dir;
          ++dir;
            es_pot_despl(c2, dir, b, c);
            if (b) {
              for (unsigned int a = 0; a < vc.size(); ++a){
                if (c == vc[a]) t = true; 
              }
              if (not t){ 
                vc.push_back(c);
              }
            }
            t = false;
            dir.init();
            ++dir;
            ++dir;
            es_pot_despl(c2, dir, b, c);
            if (b) {
              for (unsigned int a = 0; a < vc.size(); ++a){
                if (c == vc[a]) t = true; 
              }
              if (not t){ 
                vc.push_back(c);
              }
            }
         }
         else if (color == 2 or color == -2) {
          while (not dir.is_stop()){
            es_pot_despl(c2, dir, b, c);
            if (b) {
              for (unsigned int a = 0; a < vc.size(); ++a){
                if (c == vc[a]) t = true; 
              }
              if (not t) { 
                vc.push_back(c);
              }
            }
            t = false;
            ++dir;
          }
          dir.init();
          while (dir.getDireccio() < 4){
           es_pot_capturar(c2, dir, b, c);
            if (b) {
              for (unsigned int a = 0; a < vc.size(); ++a){
                if (c == vc[a]) t = true; 
              }
              if (not t) { 
                vc.push_back(c);
              }
            }
            t = false;
            ++dir;
          }
         }


        dir.init();
      }
    }
  }
bool k = false;
  for (unsigned int i = 0; i < taula.size(); ++i) {
    cout << i + 1 << " ";
    for (unsigned int j = 0; j < taula.size(); ++j) {
      coord f(i, j);
      for (unsigned int y = 0; y < vc.size(); ++y) {
        if (vc[y] == f) k = true;

      }
     if (k) cout << "? ";
    else cout << taula[i][j].mostra() << " ";
    k = false;
    }
    cout << endl;
  }
}
 
int escaquer::avalua() const {
//pre:
//post:Avalua les fitxes del escaquer num_caselles_blanques - num_caselles_negres
  int num = 0;
  for (unsigned int i = 0; i < taula.size(); ++i) {
    for (unsigned int j = 0; j < taula.size(); ++j) {
      if (taula[i][j].valor() == -1 or taula[i][j].valor() == -2) --num;
      else if (taula[i][j].valor() == 1 or taula[i][j].valor() == 2) ++num;
    }
  }
  return num;
}


void escaquer::es_pot_despl(coord cini, direccio d, bool &despl, coord &c) const {
//pre: La coordenada ha d'estar dins els limits i la posicio a la que et vols desplaçar ha de estar buida(valor)
//post: Comprova si es pot despl desde la coordenada cini en la direcció d, Retorna: despl (si es pot despl o no), c (coordenada final després del moviment)
  coord c2 = cini + d.despl();
  coord c3(c2.x, c2.y);
  if (dins_limits(c3) and taula[c2.x][c2.y].valor() == 0) {
    despl = true;
    c = coord(c2.x, c2.y); 
  }
  else despl = false;
}

void escaquer::es_pot_capturar(coord cini, direccio d, bool &capturar, coord &c) const {
//pre: La coordenada ha d'estar dins el limits del escaquer
//post: Comprova si es pot capturar desde la coordenada cini en la direcció d, Retorna: capturar (si es pot capturar o no), c (coordenada final després de la captura)
  coord coord1(cini.x, cini.y);
  coord coord2(cini.x + d.despl().x, cini.y + d.despl().y);
  coord coord3(cini.x + d.despl().x * 2, cini.y + d.despl().y * 2);

  if (dins_limits(coord1) and dins_limits(coord2) and dins_limits(coord3)) {
  int col1 = taula[cini.x ][cini.y ].valor();
  int col2 = taula[cini.x + d.despl().x][cini.y + d.despl().y].valor();
  int col3 = taula[cini.x + d.despl().x * 2][cini.y + d.despl().y * 2].valor();

  if ((((col1 == 1 or col1 == 2) and (col2 == -1 or col2 == -2)) and col3 == 0) or (((col1 == -1 or col1 == -2) and (col2 == 1 or col2 == 2)) and col3 == 0)) {
    capturar = true;
    c = coord(cini.x + d.despl().x * 2, cini.y + d.despl().y * 2);

  }

  else capturar = false;
  }
 }


list<coord> escaquer::mov_possibles(coord c) const {
//pre: Cert
//post: Comprova si es pot posar una peça de color de la coordena c
  list <coord> l;
  direccio dir;
  coord c2;
  bool b;
  dir.init();
  if (taula[c.x][c.y].valor() == 1) {
    while (dir.getDireccio() < 2) {
      b = false;
      c2 = c + dir.despl();
      es_pot_despl(c, dir, b, c2);
      if (b) l.push_back(c2);
      es_pot_capturar(c, dir, b, c2);
      if (b) l.push_back(c2);
      ++dir;
    }
  }  
  else if (taula[c.x][c.y].valor() == -1) {
   
    dir.init();
    ++dir;
    ++dir;
    while (dir.getDireccio() < 4) {
      b = false;
      c2 = c + dir.despl();
      es_pot_despl(c, dir, b, c2);
      if (b) l.push_back(c2);
      es_pot_capturar(c, dir, b, c2);
      if (b) l.push_back(c2);
      ++dir;
    }

  }
  else if (taula[c.x][c.y].valor() == 2 or taula[c.x][c.y].valor() == -2) {
    while (dir.getDireccio() < 4) {
      b = false;
      c2 = c + dir.despl();
      es_pot_despl(c, dir, b, c2);
      if (b) l.push_back(c2);
      es_pot_capturar(c, dir, b, c2);
      if (b) l.push_back(c2);
      ++dir;

    }
  }

  return l;
}



bool escaquer::pot_jugar(int color) const {
//pre: Cert
//post: Comprova si el color pot jugar (la peça de color es pot col·locar en algun lloc)
  bool b = false;
  vector < list <coord> > vl;
  for (unsigned int i = 0; i < taula.size() and b == false; ++i) { 
    for (unsigned int j = 0; j < taula.size() and b == false; ++j) {
      if (taula[i][j].valor() == color) {
        coord c(i,j);
        list <coord> l = mov_possibles(c);
        if (l.size() > 0) vl.push_back(l);
      }
    }
  }
  if (vl.size() > 0) b = true;
  else b = false;
  return b;
}

bool escaquer::posa_fitxa(coord c, coord cf, int color) {
//pre: Si el color de la posicio ha de ser el mateix que el del paremetre y la nova posicio ha d'estar dins els limits
//post: Col·loca la fitxa de color, a la coordena c, i captura les fitxes (si es poden capturar) segons regles de les dames
  bool b = false;
  if (taula[c.x][c.y].valor() == color and dins_limits(cf)) {
    list <coord> l = mov_possibles(c);
    list <coord>::iterator it;
    if (l.size() > 0) {
    list <coord>::iterator it;
      for (it = l.begin(); it != l.end(); ++it)  {
        if ((*it) == cf) {
          b = true;
	  if (cf.x == 0 and color == 1) {
            taula[c.x][c.y].omple(casella::LLIURE);
            taula[cf.x][cf.y].omple(casella::DAMA_BLANCA);
          }
          else if (cf.x == taula.size() - 1 and color == -1){
            taula[c.x][c.y].omple(casella::LLIURE);
            taula[cf.x][cf.y].omple(casella::DAMA_NEGRA);
          }
      else {    
          taula[cf.x][cf.y].omple(color);
          taula[c.x][c.y].omple(casella::LLIURE);
	   }
    if((c.x-cf.x)%2==0 and (c.y-cf.y)%2==0) taula[cf.x+((c.x-cf.x)/2)][cf.y+((c.y-cf.y)/2)].omple(casella::LLIURE);
	  	
        }
      }
    }
  }
  return b;
}





