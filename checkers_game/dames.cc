#include "escaquer.h"
#include <vector>
#include <stack>
using namespace std;

//======================================== FUNCIONS JUGADOR vs JUGADOR ========================================
void canvi_jugador(int &jugador)
//pre:*cert*
//post:canvia el valor del jugador per el del contrari
{
	if(jugador == 1) jugador = -1;
	else jugador = 1;
}

void puntuacio(escaquer taula, int &jugador)
//pre:cert*
//post:retorna el resultad de la partida
{
	if (taula.avalua() == 0) cout << "EMPAT" <<  endl;
	else if (taula.avalua() > 0) cout << "Guanyen les blanques" <<  endl;
	else cout << "Guanyen les negres" <<  endl;

}

bool comprovacio_moviment(escaquer taula, int &jugador) 
//pre:*cert*
//post:retorna un bool que inidica si el jugador pot realitzar un moviment, en cas negatiu el bool es false.
//funcionament: contenplam tots els casos possibles mitjançant una cadena de if
{
	bool valid = true;
		if (jugador == 1) {
			if (not taula.pot_jugar(1) and taula.pot_jugar(2)){
				valid = false;
			}
		}
		else if (jugador == -1) {
			if (not taula.pot_jugar(-1) and taula.pot_jugar(-2)){
				valid = false;
			}
		}
	return valid;
}
	
void mostrar_pantalla(escaquer taula, int jugador) 
//pre:cert*
//post: mostra per pantalla el jugador que te el moviment i la taula amb els seus moviments possibles
{
	if (jugador == 1) cout << "========== Jugador B ==========" << endl;
	else if(jugador == -1) cout << "========== Jugador N ==========" << endl;
	taula.mostra(jugador);
	cout << "================================" << endl << endl;
}



bool mov_possibles(escaquer &taula, unsigned int n, int &jugador) 
//pre:cert*
//post:comprova si el moviment compleix les normes establertes, es a dir, si la coord inicial pertany al mateix color que al jugador que el moviment,
//si el moviment esta dins les dimensions i si et pot realitzar el moviment
{
	
	bool fora_limits = false, t = false;
	int a,b;

	cout << "Casella Origen \n Fila i Columna (1-" << n << "): ";
	cin >> a >> b;
	coord ini(a - 1, b - 1);
	if (not taula.dins_limits(ini)) return fora_limits = true;

	cout << "Casella Final \n Fila i Columna (1-" << n << "): ";
	cin >> a >> b;
    	coord fin(a - 1, b - 1);
    	if (not taula.dins_limits(fin)) return fora_limits = true;

    	list <coord> l;
    	list <coord>::iterator it;
   	if (not fora_limits) {
        	l = taula.mov_possibles(ini);
        		for (it = l.begin(); it != l.end() and t == false; ++it) {
            			if (fin == *it) t  = true;
        		}

		if(!(taula(ini).valor() == jugador or taula(ini).valor() == jugador+jugador)) t = false;
	
    	}  
 

    	if (t) taula.posa_fitxa(ini, fin, jugador);
    	else {
        	cout << "Error: Posició ja ocupada o moviment no vàlid." << endl;
        	fora_limits = mov_possibles(taula, n, jugador);
    	}

	return fora_limits;
}


void dos_jugadors(escaquer taula, unsigned int n)
//pre:cert*
//post:organitza els principals passos del sistema jugador contra jugador
{
	int jugador = 1; // 1 == Blanc | -1 == Negre
	bool fi_partida = false;
	while (not fi_partida) {
		puntuacio(taula,jugador);
		if (not comprovacio_moviment(taula,jugador)){
			canvi_jugador(jugador);
			fi_partida = !comprovacio_moviment(taula,jugador);
		}
			mostrar_pantalla(taula,jugador);
			fi_partida = mov_possibles(taula, n, jugador);
			canvi_jugador(jugador);
	
	}
		cout<<"FINAL DE PARTIDA !! "<<endl<<"===================="<<endl;
		taula.mostra();
		cout<<endl;
		puntuacio(taula,jugador);
	}
	
//======================================== FUNCIONS MAQUINA vs JUGADOR ========================================

void mostra_l(list<coord> l) 
//pre:cert*
//post:funcio auxiliar per mostar una llista per pantalla
{
	list <coord>::iterator it;
	for (it = l.begin(); it != l.end(); ++it) cout << (*it).mostra1() << " ";
		cout << endl;
}

arbre<coord> construccio_arbre (escaquer taula, coord maquina) 
//pre:cert*
//post: crea un arbre binari de tipus coord amb tots el moviments disponibles per una ficha especifica mitjançant una funcio recursiva
{

	list <coord> l = taula.mov_possibles(maquina); //llista amb els moviments possibles de la fitxa
	escaquer taula_aux_e = taula;
	escaquer taula_aux_d = taula;
	list <coord>::iterator it;
	it = l.begin();
	arbre <coord> fe; //arbre  fill esquerre
	arbre <coord> fd; //arbre fill dret
	if (not l.empty()) {
		
		taula_aux_e.posa_fitxa(maquina,*it, -1); 
		fe = construccio_arbre(taula_aux_e, *it);
		++it;
		if(it != l.end()) {
			taula_aux_d.posa_fitxa(maquina,*it, -1);		
			fd = construccio_arbre(taula_aux_d, *it);
		}
	
	}
	arbre<coord> a(maquina, fe , fd);
	return a;

} 

queue<coord> recorre_arbre_aux (arbre<coord> a, vector <queue <coord> > &vq, unsigned int &n) 
//pre:cert*
//post: Utilitzant if's observam totes les condicions possibles de cada arbre de manera que obtenim un vector de queue's on
//ens indica el cami mes optim de cada arbre llavors retornam el arbre amb el cami amb mes captures
{
 	queue <coord> q;
  	if (n == 0) {
  		vq.push_back(q);
  	}
		if (a.fd().es_buit() or a.fe().es_buit()) {
				if(a.fd().es_buit() and a.fe().es_buit()){ 
	              			vq[n].push(a.arrel());
	              			return q;
	              
	           		} else if (a.fd().es_buit() and not a.fe().es_buit()) {
	              			if (a.fe().arrel().x - a.arrel().x == 2) {
	             				vq[n].push(a.arrel());
	             				recorre_arbre_aux(a.fe(), vq, n);
	       			   	} else {
		     	 			vq[n].push(a.arrel());
						vq[n].push(a.fe().arrel());
	                   		}
	            		} else if(not a.fd().es_buit() and a.fe().es_buit()) {
	           		 	if (a.fd().arrel().x - a.arrel().x == 2) {
	             				vq[n].push(a.arrel());
	             				recorre_arbre_aux(a.fd(), vq, n);
	                 		} else {
		    			  	vq[n].push(a.arrel());
	                   			vq[n].push(a.fd().arrel());
		                 	}
	             
	            		}
      	
    		} else {
          			if (a.fd().arrel().x - a.arrel().x == 2 and a.fe().arrel().x - a.arrel().x == 2){
              				vq[n].push(a.arrel());
              				vq.push_back(vq[n]);
              				recorre_arbre_aux(a.fd(), vq, n);
              				++n;
              				recorre_arbre_aux(a.fe(), vq, n);

          			} else if (a.fd().arrel().x - a.arrel().x == 2 or a.fe().arrel().x - a.arrel().x == 2) {
            				if (a.fd().arrel().x - a.arrel().x == 2) {
             					vq[n].push(a.arrel());
             					recorre_arbre_aux(a.fd(), vq, n);
          				} else if (a.fe().arrel().x - a.arrel().x == 2) {
             					vq[n].push(a.arrel());
             					recorre_arbre_aux(a.fe(), vq, n);
       			   		}
       
          			} else {
	      				vq[n].push(a.arrel());
              				vq[n].push(a.fd().arrel());
         	 		}
   
      
      
    		}
	      
        
      	
  	unsigned int max = 0;
	for (unsigned int i = 0; i < vq.size(); ++i) {
       		if (vq[i].size() >= max) {
        		q = vq[i];
       			max = vq[i].size();
      		}
    	}

  return q;
}

void realitzar_mov_maquina(escaquer &taula, unsigned int n) 
//pre:cert*
//post:
{
 	vector<arbre<coord> > mov_maquina;
	stack <coord> coord_maquina;
	list <coord> l;

	for (unsigned int i = 0; i < n; ++i) {
		for (unsigned int j = 0; j < n; ++j) {
			coord c(i, j);
			if (taula(c).valor() == -1 or taula(c).valor() == -2) coord_maquina.push(c);
		}
	}

	
	while (not coord_maquina.empty()) {
		l = (taula.mov_possibles(coord(coord_maquina.top())));
		if (not l.empty()) {
			arbre <coord> a;
			a = construccio_arbre(taula, coord (coord_maquina.top().x, coord_maquina.top().y));
			mov_maquina.push_back(a);
		}
		coord_maquina.pop();
	}
	
	vector <queue <coord> > millor_mov;
	unsigned int aux = 0;
	vector <queue<coord> > vq;

	for (unsigned int i = 0; i < mov_maquina.size(); ++i) {
		millor_mov.push_back(recorre_arbre_aux(mov_maquina[i], vq, aux));
	}
	unsigned int f = 0;
	for (unsigned int i = 0; i < millor_mov.size(); ++i) {
		if (millor_mov[i].size() < f) aux = i;
	}
	int color = taula(millor_mov[aux].front()).valor();
	coord cini(0, 0);
	while (not millor_mov[aux].empty()) {
		cini = coord(millor_mov[aux].front().x, millor_mov[aux].front().y);
		cout<<cini.mostra1()<<endl;
		millor_mov[aux].pop();
		taula.posa_fitxa(cini, millor_mov[aux].front(), color);
	}
  
}
void jugador_maquina(escaquer taula, unsigned int n)
//pre:cert*
//post:realitzam totes les cridas a funcions necesaries per poder jugar la maquina vs el jugador
{
	
	int jugador = 1; // 1 == Blanc | -1 == Negre
	bool fi_partida = false;
	while (not fi_partida) {
		puntuacio(taula,jugador);
		if (not comprovacio_moviment(taula,jugador)){
			canvi_jugador(jugador);
			fi_partida = !comprovacio_moviment(taula,jugador);
		}
			mostrar_pantalla(taula,1);
			fi_partida = mov_possibles(taula, n, jugador);
			mostrar_pantalla(taula,-1);
			realitzar_mov_maquina(taula,n);
	
	}
		cout<<"FINAL DE PARTIDA !! "<<endl<<"===================="<<endl;
		taula.mostra();
		cout<<endl;
		puntuacio(taula,jugador);
	}

	
//========================================	  MAIN		========================================================
	
int main() 
{
	cout << "La Dimensió de l'escaquer ha de ser múltiple de 2 i 8 com a mínim.\nQuina és la Dimensió?: ";
	unsigned int n=1 ;
	bool dimensions_valides=false;

	while(not dimensions_valides) {
		if(n%2==0 and n%8==0) dimensions_valides=true;
		else cin >> n;
	
	}
	escaquer taula(n);
	cout << "Les Opcions disponibles son (1) Bàsic (2) Especial.\nQuina opció vols?: ";
	int opcio_joc;
	cin >> opcio_joc;
	cout << endl;

	while (opcio_joc != 1 and opcio_joc != 2) {
		cout << "Introdueix una opció vàlida: ";
		cin >> opcio_joc;
		cout << endl;
	}

	if (opcio_joc == 1) dos_jugadors(taula, n);
	else jugador_maquina(taula, n);
}     


