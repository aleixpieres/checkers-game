#include "arbreIOcoord.h"
#include <stack>
#include <string>
#include <fstream>

//Lectura
arbre<coord> construeix_arbre_coord (char* nomf)
/* Pre: nomf conte el nom d'un fitxer amb els nodes d'un arbre en
   postordre; per cada node s'indica el seu valor i el nombre de fills */
/* Post: el resultat es un arbre binari creat a partir del nodes que es
   troben al fitxer nomf */  
{  
  ifstream fin(nomf);
  coord node;
  int nf;

  stack<arbre<coord> > p;
  arbre<coord> a;
  
  while (fin>>node.x>>node.y>>nf) {
        
        if (nf == 0) {  //fills buits
            arbre<coord> fbe;
            arbre<coord> fbd;
            arbre<coord> a(node, fbe, fbd);
            p.push(a);
        }
        else {
        	if (nf==-1){  //nf=-1 --> nomes un fill, l'esquerre
        		arbre<coord> fbd;
            	arbre<coord> fe = p.top();
            	p.pop();
            	arbre<coord> a(node, fe, fbd);
            	p.push(a);
        	}
        	else {
        		if (nf==1){  //nf=1 --> nomes un fill, el dret
        			arbre<coord> fbe;
            		arbre<coord> fd = p.top();
            		p.pop();
            		arbre<coord> a(node, fbe, fd);
            		p.push(a);
        		}
        		else {  //nf=2 --> dos fills no buits
        			arbre<coord> fd = p.top();
            		p.pop();
            		arbre<coord> fe = p.top();
            		p.pop();
            		arbre<coord> a(node, fe, fd);
            		p.push(a);
            	}
        	}
            
        }
  }
  if (not p.empty()) a = p.top();
  return a;
}

//Escriptura
string dep=""; 
ostream& operator<<(ostream &os, const arbre<coord> &x) 
/* Pre: cert */
/* Post: s'han escrit al canal estandard de sortida els elements de x */  
{
  string d1=dep;
  if (x.es_buit()) 
    os<<".";
  else {
    os<< "["<<x.arrel().mostra1()<<"]\n"<<d1<<" \\__";
    dep = d1+" |  ";
    os<< x.fd();
    os<<"\n"<<d1<<" \\__";
    dep = d1+"    ";
    os<< x.fe();
  }
  dep=d1;
  return os;
}

