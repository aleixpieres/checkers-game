#include <iostream>
#include "casella.h"

///////////////////////////////////////////
//// Implementació de la classe casella ///

casella::casella() {  
//pre: cert
//post: Crea una casella amb valor inicial LLIURE
 color = 0;
 visitada = 0;
}

void casella::omple(int x) {
//pre: cert
//post: Modifica el color de la casella
  color = x;
  visitada = 1;
}

void casella::marca() {
//pre: cert
//post: Marcar la casella com a visitada.
  visitada = 1;
}

void casella::desmarca() {
//pre: cert
//post: Desmarca la casella (no visitada)
  visitada = 0;
}

int casella::valor() const {
//pre: cert
//post: Obté el contingut de la casella
  return color;
}

char casella::mostra() const {
//pre: cert
//post: Obté el el caràcter de la casella a dibuxar: BLANCA -> B, DAMA_BLANCA ->Q, NEGRA -> N, DAMA_NEGRA ->P, LLIURE -> -
	char c;
	if (color == 1) c = 'B';
	else if (color == 2) c = 'Q';
	else if (color == -1) c = 'N';
	else if (color == -2) c = 'P';
	else if (color == 0) c = '-';
	return c;
}

bool casella::es_visitada() const {
//pre: cert
//post: Consulta si la casella esta marcada com visitada
  return visitada;
}

