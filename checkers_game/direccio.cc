#include "direccio.h"
using namespace std;

///////////////////////////////////////////
//// Implementació de la classe direcció ///


direccio::direccio() {
//pre: Cert
//post: Crear una direcció nova, amb el primer valor de la llista
  
}

int direccio::getDireccio() const {
//pre: Cert
//post: Obtenir la direcció
  return d;
}

bool direccio::is_stop() const {
//pre: Cert
//post: Veure si el valor de la direcció és el del final de la llista
	bool b;
	if (d == 4) b = true;
	else b = false;
	return b;
}

void direccio::init() {
//pre: Cert
//post: Canviar el valor de la direccio, posant-li el primer de la llista
  d = NO;
}

direccio& direccio::operator++() {
//pre: Cert
//post: Canviar el valor de la direcció pel següent de la llista
  if (not is_stop()) d = dirs(d + 1);
  return (*this);
}  

coord direccio::despl() const {
//pre: Cert                                                  
//post: Obtenir les components x,y que representen un moviment
	coord c;
  if (d == 0) c = coord(-1,-1);
  else if (d == 1) c = coord(-1,1);
  else if (d == 2) c = coord(1,1);
  else if (d == 3) c = coord(1,-1);
  else if (d == 4) c = coord(0,0);
  return c;
}

string direccio::mostra() const {
//pre: Cert
//post: Obtenir un string amb el nom de la direcció
  	string s;
  if (d == 0) s = "NO";
  else if (d == 1) s = "NE";
  else if (d == 2) s = "SE";
  else if (d == 3) s = "SO";
  else if (d == 4) s = "STOP";
  return s;
}

