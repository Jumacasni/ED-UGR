#include "Nmer.h"

#include <fstream>
#include <algorithm>
#include <map>

template<typename T, int K>
extern void recorrido_preorden(typename ktree<T,K>::const_node n);


Nmer::Nmer() {
  max_long = 0;
  el_Nmer = ktree<pair<char,int>,4>(pair<char,int>('-',0));
  
}

bool Nmer::loadNmer(const string & fichero, unsigned int l) {
 string cadena;
 ifstream fe;
 
 fe.open(fichero.c_str(), ifstream::in);
 if (fe.fail()){
    cerr << "Error al abrir el fichero " << fichero << endl;
 } 
 else {
    getline(fe,cadena,'\n');
    sequenceADN(l, cadena); 
    fe.close();
    return true;
 } 
 fe.close();
 return false;
}

bool Nmer::loadSerialized(const string & fichero) {
 string cadena;
 ifstream fe;
 pair<char,int> nulo('x',-1);
 Nmer::String2Base stb;
 
 fe.open(fichero.c_str(), ifstream::in);
 if (fe.fail()){
    cerr << "Error al abrir el fichero " << fichero << endl;
 } 
 else {
    //leo la cabecera del fichero (líneas que comienzan con #)
    do{ 
      getline(fe,cadena,'\n'); 
    } while (cadena.find("#")==0 && !fe.eof());
    // leemos Nmer_length
     max_long = std::stoi(cadena);
     // leemos cadena serializada
    getline(fe,cadena,'\n');
    el_Nmer.deserialize(cadena,nulo,';',stb); 
    fe.close();
    return true;
 } // else
 fe.close();
 return false;
}
 
void Nmer::list_Nmer() const {
	string cadena = "";
    if (!el_Nmer.root().null())
      listar(el_Nmer.root(), cadena);
}
 
unsigned int Nmer::length() const {
   return max_long;
}
 
Nmer::size_type Nmer::size() const{
  return el_Nmer.size()-1;
}

Nmer & Nmer::operator=(const Nmer & a){
	if(this != &a){
		el_Nmer = a.el_Nmer;
		max_long = a.max_long;
	}

	return *this;
}

Nmer Nmer::prefix(string adn){
	int hijo;
	ktree<pair<char,int>,4>::node n_act = el_Nmer.root();

	Nmer res_Nmer;
	Nmer aux_Nmer;
	ktree<pair<char,int>,4>::node nodo = aux_Nmer.el_Nmer.root();

	for(auto it = adn.begin(); it != adn.end(); ++it){
		if(*it == 'a')
      	hijo = 0;
    	else if (*it == 'g')
      	hijo = 1;
    	else if(*it == 'c')
      	hijo = 2;
    	else
      	hijo = 3;

      n_act = n_act.k_child(hijo);
      pair<char,int> datos((*n_act).first, (*n_act).second);

      aux_Nmer.el_Nmer.insert_k_child(nodo, hijo, datos);
      nodo = nodo.k_child(hijo);
	}

	res_Nmer.el_Nmer.assing(el_Nmer, n_act);

	aux_Nmer.el_Nmer.insert_k_child(nodo.parent(), hijo, res_Nmer.el_Nmer);

	return aux_Nmer;
}

void Nmer::sequenceADN(unsigned int l, const string & adn){
	el_Nmer = ktree<pair<char,int>,4>(pair<char,int>('-',0));
	max_long = l;
  int tamanio = adn.size() - 1;

  for(int i = 0; i < tamanio; ++i){
    string cadena = adn.substr(i, l);
    insertar_cadena(cadena);
  }
}   

void Nmer::insertar_cadena(const string & cadena){
  ktree<pair<char,int>,4>::node n_act = el_Nmer.root();
  int hijo;

  for(auto it = cadena.begin(); it != cadena.end(); ++it){

    if(*it == 'a')
      hijo = 0;
    else if (*it == 'g')
      hijo = 1;
    else if(*it == 'c')
      hijo = 2;
    else
      hijo = 3;

    if(!(n_act.k_child(hijo).null())){
      (*(n_act.k_child(hijo))).second++;
    }
    
    else{
      pair<char,int> datos_hijo(*it, 1);
      el_Nmer.insert_k_child(n_act,hijo,datos_hijo);
    }

    n_act = n_act.k_child(hijo);
  }
}

void Nmer::recorrido_preorden(ktree<pair<char,int>,4>::const_node n) const{
  if (!n.null()){
    cout << (*n).first << " " << (*n).second << endl;
    for (ktree<pair<char,int>,4>::const_node hijo : n)
      recorrido_preorden(hijo);
  }
}

void Nmer::listar(ktree<pair<char,int>,4>::const_node n, string & cadena) const{
  if (!n.null()){
  	 string cadena = "";
  	 int frecuencia = (*n).second;
  	 construir(n, cadena, frecuencia);

    for (ktree<pair<char,int>,4>::const_node hijo : n)
      listar(hijo, cadena);
  }
}

void Nmer::construir(ktree<pair<char,int>,4>::const_node n, string & cadena, int frecuencia) const{
	if(n == el_Nmer.root()){
		if(frecuencia != 0){
			std::reverse(cadena.begin(), cadena.end());
			cout << cadena << " " << frecuencia << endl;
		}
	}

	else{
		cadena += (*n).first;
		construir(n.parent(), cadena, frecuencia); 
	}
}

set<pair<string,int>, OrdenCre> Nmer::rareNmer(int threshold){
  set<pair<string,int>, OrdenCre> sal;
  ktree<pair<char,int>,4>::const_node n = el_Nmer.root();
  string cadena;

  auxRareNmer(n, sal, cadena, threshold);

  return sal;
}

void Nmer::auxRareNmer(ktree<pair<char,int>,4>::const_node n, set<pair<string,int>, OrdenCre> &salida, string & cadena, int threshold){
	if (!n.null()){
  	 string cadena = "";
  	 int frecuencia = (*n).second;
  	 if(es_hoja(n))
  	 	almacenar_cadena_RareNmer(n, salida, cadena, frecuencia, threshold);

    for (ktree<pair<char,int>,4>::const_node hijo : n){
      auxRareNmer(hijo, salida, cadena, threshold);
    }
  }
}

void Nmer::almacenar_cadena_RareNmer(ktree<pair<char,int>,4>::const_node n, set<pair<string,int>, OrdenCre> &salida, string & cadena, int frecuencia, int threshold){
	if(n == el_Nmer.root()){
		if(frecuencia != 0 && frecuencia <= threshold){
			std::reverse(cadena.begin(), cadena.end());
			pair<string, int> aux(cadena, frecuencia);

			salida.insert(aux);
		}
	}

	else{
		cadena += (*n).first;
		almacenar_cadena_RareNmer(n.parent(), salida, cadena, frecuencia, threshold); 
	}
}

bool Nmer::es_hoja(ktree<pair<char,int>,4>::const_node n){
	for (ktree<pair<char,int>,4>::const_node hijo : n){
		if(!hijo.null())
			return false;
	}

	return true;
}

set<pair<string,int>, OrdenDecre> Nmer::commonNmer(int threshold){
	set<pair<string,int>, OrdenDecre> sal;
	ktree<pair<char,int>,4>::node n = el_Nmer.root();
	string cadena;

	auxCommonNmer(n, sal, cadena, threshold);

	return sal;
}

void Nmer::auxCommonNmer(ktree<pair<char,int>,4>::node n, set<pair<string,int>, OrdenDecre> &salida, string & cadena, int threshold){
	if (!n.null()){
  		string cadena = "";
  		int frecuencia = (*n).second;
  		if(!hijo_con_mayor_threshold(n, threshold))
  			almacenar_cadena_CommonNmer(n, salida, cadena, frecuencia, threshold);

  		else{
   		for (ktree<pair<char,int>,4>::node hijo : n){
   			auxCommonNmer(hijo, salida, cadena, threshold);
   	}
    }
  }
}

void Nmer::almacenar_cadena_CommonNmer(ktree<pair<char,int>,4>::const_node n, set<pair<string,int>, OrdenDecre> &salida, string & cadena, int frecuencia, int threshold){
	if(n == el_Nmer.root()){
		if(frecuencia != 0 && frecuencia >= threshold){
			std::reverse(cadena.begin(), cadena.end());
			pair<string, int> aux(cadena, frecuencia);

			salida.insert(aux);
		}
	}

	else{
		cadena += (*n).first;
		almacenar_cadena_CommonNmer(n.parent(), salida, cadena, frecuencia, threshold); 
	}
}

bool Nmer::hijo_con_mayor_threshold(ktree<pair<char,int>,4>::const_node n, int threshold){
	for (ktree<pair<char,int>,4>::const_node hijo : n){
		if(!hijo.null()){
			if((*hijo).second >= threshold)
				return true;
		}
	}

	return false;
}

set<pair<string,int>, OrdenCre> Nmer::level(int l){
	set<pair<string,int>, OrdenCre> sal;
	ktree<pair<char,int>,4>::node n = el_Nmer.root();

	almacenar_level(l, n, sal);

	return sal;
}

void Nmer::almacenar_level(int l, ktree<pair<char,int>,4>::const_node n,set<pair<string,int>, OrdenCre> & salida){
	int profundidad_nodo = 0;
	string cadena = "";
	profundidad(n, profundidad_nodo, cadena);
	std::reverse(cadena.begin(), cadena.end());

	if(profundidad_nodo <= l){
		if(profundidad_nodo == l){
			pair<string, int> aux(cadena, (*n).second);
			salida.insert(aux);
		}

		else{
			for (ktree<pair<char,int>,4>::const_node hijo : n)
   			almacenar_level(l, hijo, salida);
		}
	}

}

void Nmer::profundidad(ktree<pair<char,int>,4>::const_node n, int & profundidad_nodo, string & cadena){
	if(!n.null()){
		if(n != el_Nmer.root()){
			cadena += (*n).first; 
			profundidad_nodo++;
			profundidad(n.parent(), profundidad_nodo, cadena);
		}
	}
}

float Nmer::distance(Nmer & nm){
	set<pair<string,int>, OrdenDecre> nmX = ordenar_nmer();
	set<pair<string,int>, OrdenDecre> nmY = nm.ordenar_nmer();;

	map<string, int> rankingX;
	int contador = 1;

	for(auto it = nmX.begin(); it != nmX.end(); ++it){
		rankingX[it->first] = contador;
		contador++;
	}

	map<string, int> rankingY;
	contador = 1;
	
	for(auto it = nmY.begin(); it != nmY.end(); ++it){
		rankingY[it->first] = contador;
		contador++;
	}

	float max = maximo(rankingX.size(), rankingY.size());
	float dist = 0;
	float valor;

	for(auto it = rankingX.begin(); it != rankingX.end(); ++it){
		auto pos_rankingY = rankingY.find(it->first);

		if(pos_rankingY != rankingY.end()){
			int posX = it->second;
			int posY = pos_rankingY->second;

			valor = abs(posX-posY)/max;
		}

		else
			valor = 1;

		dist += valor;
	}

	return dist/rankingX.size();
}

set<pair<string,int>, OrdenDecre> Nmer::ordenar_nmer(){
  set<pair<string,int>, OrdenDecre> sal;
  ktree<pair<char,int>,4>::const_node n = el_Nmer.root();
  string cadena;

  aux_ordenar_nmer(n, sal, cadena);

  return sal;
}

void Nmer::aux_ordenar_nmer(ktree<pair<char,int>,4>::const_node n, set<pair<string,int>, OrdenDecre> &salida, string & cadena){
	if (!n.null()){
  	 string cadena = "";
  	 int frecuencia = (*n).second;
  	 almacenar_cadena_ordenada(n, salida, cadena, frecuencia);

    for (ktree<pair<char,int>,4>::const_node hijo : n){
      aux_ordenar_nmer(hijo, salida, cadena);
    }
  }
}

void Nmer::almacenar_cadena_ordenada(ktree<pair<char,int>,4>::const_node n, set<pair<string,int>, OrdenDecre> &salida, string & cadena, int frecuencia){
	if(n == el_Nmer.root()){
		if(frecuencia != 0){
			std::reverse(cadena.begin(), cadena.end());
			pair<string, int> aux(cadena, frecuencia);

			salida.insert(aux);
		}
	}

	else{
		cadena += (*n).first;
		almacenar_cadena_ordenada(n.parent(), salida, cadena, frecuencia); 
	}
}

float Nmer::maximo(const unsigned int & a, const unsigned int & b){
	if(a >= b)
		return a;

	return b;
}

Nmer Nmer::Union(const Nmer & reference){
	Nmer resultado;
	resultado.max_long = maximo(max_long, reference.max_long);

	resultado.el_Nmer = el_Nmer;

	ktree<pair<char,int>,4> arbol;
	arbol = reference.el_Nmer;
	ktree<pair<char,int>,4>::node n_reference = arbol.root();

	resultado.unir_nodos(resultado.el_Nmer.root(), n_reference, arbol, resultado.el_Nmer.root().parent());

	return resultado;
}

void Nmer::unir_nodos(ktree<pair<char,int>,4>::node n_this, ktree<pair<char,int>,4>::node n_reference, ktree<pair<char,int>,4> & arbol, ktree<pair<char,int>,4>::node nodo_padre){

	if(!n_this.null() && !n_reference.null()){
		if((*n_this).first == (*n_reference).first)
				(*n_this).second += (*n_reference).second;

		nodo_padre = n_this;
		for(int i = 0; i < 4; ++i)
			unir_nodos(n_this.k_child(i), n_reference.k_child(i), arbol, nodo_padre);
	}

	else if(n_this.null() && !n_reference.null()){
		ktree<pair<char,int>,4> aux;
		aux.assing(arbol, n_reference);
		
		el_Nmer.insert_k_child(nodo_padre, n_reference.child_number(), aux);
		nodo_padre = n_this;
	}
}

bool Nmer::containsString(const string adn) const{
	ktree<pair<char,int>,4>::const_node n = el_Nmer.root();
	int hijo;

	for(auto it = adn.begin(); it != adn.end(); ++it){
		if(*it == 'a')
      hijo = 0;
    else if (*it == 'g')
      hijo = 1;
    else if(*it == 'c')
      hijo = 2;
    else if(*it == 't')
      hijo = 3;
    else
    	return false;

   	if(n.k_child(hijo).null())
   		return false;

   	n = n.k_child(hijo);
	}

	return true;
}

bool Nmer::included(const Nmer & reference) const{
	if(!comprobar_nodos(el_Nmer.root(), reference.el_Nmer.root()))
		return false;

	return true;
}

bool Nmer::comprobar_nodos(ktree<pair<char,int>,4>::const_node n_this, ktree<pair<char,int>,4>::const_node n_reference) const{
	for (ktree<pair<char,int>,4>::const_node hijo : n_this){
		ktree<pair<char,int>,4>::const_node n_act = n_reference.k_child(hijo.child_number());

		if(n_act.null())
			return false;

		else if(!comprobar_nodos(hijo, n_act))
			return false;
	}

	return true;
}