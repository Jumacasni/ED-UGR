/** @file clinvar.cpp
	@brief fichero de implementacion de la clase clinvar
	@author Juan Manuel Castillo Nievas
	@date 24/Diciembre/2016
*/

#include "clinvar.h"
#include <algorithm>
#include <queue>
#include <unordered_set>

/** @brief lee un fichero de mutaciones, linea a linea
	@param[in] nombreDB nombre del fichero
*/

void clinvar::load (string nombreDB){
	ifstream fe;
 	string cadena;

 	cout << "Abrimos "<< nombreDB << endl;
 	fe.open(nombreDB.c_str(), ifstream::in);
 	if (fe.fail()){
   	cerr << "Error al abrir el fichero " << nombreDB << endl;
 	}
 	else {
    	
    	do{
      	getline(fe,cadena,'\n');
    	}while (cadena.find("#")==0 && !fe.eof());

    	while ( !fe.eof() ){

        	mutacion mut = mutacion(cadena);

        	insert(mut);
        	getline(fe,cadena,'\n');
    	}

    	fe.close();
    	
  	}
  	fe.close();
}

/** @brief insertar una mutacion en clinvar
	@param[in] x mutacion a insertar
*/

void clinvar::insert (const mutacion & x){

	// Insertar en mutBD
	pair<set<mutacion>::iterator, bool> it = mutBD.insert(x);

	// Insertar en IDm_map
	pair<IDmut, set<mutacion>::iterator> IDm((*(it.first)).getID(), it.first);
	IDm_map.insert(IDm);

	// Insertar en gen_map
	vector<string> genes_actual_mutacion = (*(it.first)).getGenes();

	for(auto it_gen = genes_actual_mutacion.begin(); it_gen != genes_actual_mutacion.end(); ++it_gen){
		string gen_actual = *it_gen;
		map<IDgen, list<set<mutacion>::iterator > >::iterator it_aux = gen_map.find(gen_actual);

		if(it_aux != gen_map.end())
			it_aux->second.push_back(it.first);

		else{
			list<set<mutacion>::iterator> list;
			list.push_back(it.first);

			gen_map[gen_actual] = list;
		}
	}

	// Insertar en EnfDB
	vector<enfermedad> ve = (*(it.first)).getEnfermedades();

	for(auto it_enf = ve.begin(); it_enf != ve.end(); ++it_enf){
		EnfDB[(*it_enf).getID()] = *it_enf;
	}

	// Insertar en IDenf_map
	set<mutacion>::iterator it_enf;

	vector<enfermedad> enf_mutacion = (*(it.first)).getEnfermedades();

	for(auto it_enf_actual = enf_mutacion.begin(); it_enf_actual != enf_mutacion.end(); ++it_enf_actual){
		pair<IDenf, set<mutacion>::iterator> enf_aux((*it_enf_actual).getID(), it.first);
		IDenf_map.insert(enf_aux);	
	}

}

/** @brief eliminar una mutacion de clinvar
	@param[in] ID identificador de la mutacion
*/

bool clinvar::erase (IDmut ID){

	bool borrado = false;

	clinvar::iterator itc = find_Mut(ID);
	
	if(itc != end()){
		borrado = true;
		
		// Eliminar de mutBD
		set<mutacion>::iterator it_mut = itc.it;
		mutBD.erase(it_mut);

		// Eliminar de IDm_map
		auto it_map = IDm_map.find(ID);
		IDm_map.erase(it_map);

		// Eliminar de gen_map
		for(auto it_gen = gen_map.begin(); it_gen != gen_map.end(); ++it_gen){
			for(auto it_lista = it_gen->second.begin(); it_lista != it_gen->second.end(); ++it_lista){
				if(*(*it_lista) == *itc){
					it_gen->second.erase(it_lista);
					--it_lista;
					if(it_gen->second.empty())
						gen_map.erase(it_gen);
				}

			}
		}

		// Eliminar de IDenf_mmap y de EnfDB en su respectivo caso
		for(auto itmap = IDenf_map.begin(); itmap != IDenf_map.end(); ++itmap){
			if(ID == (*(itmap->second)).getID()){
				string enfID = (*itmap).first;
				IDenf_map.erase(itmap);

				if(IDenf_map.count(enfID) == 0)
					EnfDB.erase(itmap->first);
			}
		}

	}

	return borrado;
}

/** @brief consultar el tamaño de todas las estructuras de clinvar
*/

void clinvar::size(){
	cout << "Se han cargado " << mutBD.size() << " mutaciones" << endl;

	cout << "Hay " << IDm_map.size() << " ID asociadas a mutaciones" << endl;

	cout << "Hay " << gen_map.size() << " genes asociados a mutaciones" << endl;

	cout << "Se han cargado " << EnfDB.size() << " enfermedades" << endl;

	cout << "Hay " << IDenf_map.size() << " enfermedades asociadas a mutaciones" << endl;
	
}

/** @brief buscar una mutacion en clinvar
	@param[in] ID identificador de la mutacion
	@returns iterador con la posicion de la mutacion dentro de mutBD, end() si no lo encuentra

*/

clinvar::iterator clinvar::find_Mut(string ID){

	clinvar::iterator itc = end();
	
	auto it = IDm_map.find(ID);
	if(it != IDm_map.end())
		itc.it = it->second;

	return itc;
}

/** @brief buscar una enfermedad en clinvar
	@param[in] ID identificador de la enfermedad
	@returns iterador con la posicion de la mutacion dentro de enfDB, end() si no lo encuentra
*/

clinvar::enfermedad_iterator clinvar::find_Enf(IDenf ID){
	clinvar::enfermedad_iterator it = EnfDB.find(ID);

	return it;
}

/** @brief buscar todas las enfermedades asociadas a una mutacion
	@param[in] mut mutacion con las enfermedades buscadas
	@returns vector con todas las enfermedades de la mutacion
*/

vector<enfermedad> clinvar::getEnfermedades(mutacion & mut){
	clinvar::iterator it = find_Mut(mut.getID());
	vector<enfermedad> ve;

	if(it != end())
		ve = mut.getEnfermedades();

	return ve;
}

/** @brief buscar enfermedades
	@param[in] keyword palabra que forma parte del nombre de la enfermedad
	@returns lista con los identificadores de las enfermedades
*/

list<clinvar::IDenf> clinvar::getEnfermedades(const string & keyword){
	list<clinvar::IDenf> lista;

	for(auto it = ebegin(); it != eend(); ++it){
		if(it->second.nameContains(keyword))
			lista.push_back(it->first);
	}

	return lista;
}

/** @brief buscar enfermedades
	@param[in] ID identificador de la enfermedad
	@returns conjunto ordenado (en orden creciente) de todas las mutaciones que se encuentran asociadas a la enfermedad
*/

set<clinvar::IDmut> clinvar::getMutacionesEnf (IDenf ID){
	set<clinvar::IDmut> mut;

	if(IDenf_map.count(ID) > 0){
		auto it = IDenf_map.equal_range(ID);
		for(auto aux = it.first; aux != it.second; ++aux){
			mut.insert(aux->second->getID());
		}
	}

	return mut;
}

/** @brief buscar mutaciones
	@param[in] ID identificador del gen
	@returns conjunto ordenado (en orden creciente) de todas las mutaciones asociadas al gen
*/

set<clinvar::IDmut> clinvar::getMutacionesGen (IDgen ID){
	set<clinvar::IDmut> mut;

	auto it = gen_map.find(ID);
	for(auto inicio = it->second.begin(); inicio != it->second.end(); ++inicio){
		mut.insert((*inicio)->getID());
	}

	return mut;
}

/** @brief buscar mutaciones más probables
	@param[in] k numero de mutaciones buscadas
	@param[in] keyword palabra que forma parte del nombre de las enfermedades
	@returns conjunto ordenado (de mayor a menor probabilidad) de las k mutaciones más frecuentes asociadas a las enfermedades
*/

set<mutacion,ProbMutaciones> clinvar::topKMutaciones (int k, string keyword){
	set<mutacion,ProbMutaciones> sal;
	set<mutacion> mutaciones;
	priority_queue<mutacion, vector<mutacion>, ProbMutaciones> pq;
	
	// Determinar enfermedades que contienen keyword
	list<clinvar::IDenf> enf = getEnfermedades(keyword);

	// Para cada enfermedad encontrada, determinar las mutaciones asociadas que tengan información de su probabilidad
	for(auto it = enf.begin(); it != enf.end(); ++it){
		set<clinvar::IDmut> mut = getMutacionesEnf(*it);
		for(auto it_mut = mut.begin(); it_mut != mut.end(); ++it_mut){
			clinvar::iterator itc = find_Mut(*it_mut);
			if((*itc).getCaf().size() > 0)
				mutaciones.insert(*itc);
		}
	}

	// Insertar las primeras k mutaciones (o todas las mutaciones en caso de que haya menos de k mutaciones)
	unordered_set<clinvar::IDmut> idmut;

	auto mutacion = mutaciones.begin();
	int tama = mutaciones.size();

	for(int i = 0; i < k && i < tama; ++i){
		auto it = idmut.insert((*mutacion).getID());
		if(it.second)
			pq.push(*mutacion);

		++mutacion;
	}

	// Comprobar la probabilidad del resto de mutaciones. Si es mayor, se inserta un nuevo elemento en la cola
	int tama_pq;

	for(auto resto_mutaciones = mutacion; resto_mutaciones != mutaciones.end(); ++resto_mutaciones){
		if((*resto_mutaciones).getCaf().size() > 0 && (1-(*resto_mutaciones).getCaf().at(0)) > (1-pq.top().getCaf().at(0))){
			tama_pq = pq.size();
			auto it = idmut.insert((*resto_mutaciones).getID());
			if(it.second){
				if(tama_pq >= k)
					pq.pop();

				pq.push(*resto_mutaciones);
			}
		}
	}

	// Soltar los elementos de la cola en el set que hay que devolver
	while(!pq.empty()){
		sal.insert(pq.top());
		pq.pop();
	}

	return sal;
}

/** @brief buscar mutaciones por rango
	@param[in] cromosoma cromosoma de la mutacion
	@param[in] posicion posicion dentro del cromosoma
	@returns iterador que apunta a la primera mutacion mayor o igual a los parametros
*/

clinvar::iterator clinvar::lower_bound(string cromosoma, unsigned int posicion){
	 set<mutacion>::iterator it, first, last;
    clinvar::iterator sal;
    mutacion mut;
    mut.setChr(cromosoma);
    mut.setPos(posicion);

    first = mutBD.begin();
    last = mutBD.end();

    iterator_traits<set<mutacion>::iterator >::difference_type contador, step;
    contador = distance(first, last);

    while (contador > 0) {
        it = first;
        step = contador / 2;
        advance(it, step);
        if (*it < mut) {
            first = ++it;
            contador -= step + 1;
        } else contador = step;
    }

    sal.it = first;

    return sal;
}

/** @brief buscar mutaciones por rango
	@param[in] cromosoma cromosoma de la mutacion
	@param[in] posicion posicion dentro del cromosoma
	@returns iterador que apunta a la primera mutacion estrictamente mayor a los parametros
*/

clinvar::iterator clinvar::upper_bound(string cromosoma, unsigned int posicion){
	 set<mutacion>::iterator it, first, last;
    clinvar::iterator sal;
    mutacion mut;
    mut.setChr(cromosoma);
    mut.setPos(posicion);

    first = mutBD.begin();
    last = mutBD.end();

    iterator_traits<set<mutacion>::iterator >::difference_type contador, step;
    contador = distance(first, last);

    while (contador > 0) {
        it = first;
        step = contador / 2;
        advance(it, step);
        if (!(mut < *it)) {
            first = ++it;
            contador -= step + 1;
        } else contador = step;
    }

    sal.it = first;

    return sal;
}

/** @brief iterador de mutacion
	@returns iterador apuntando a la primera mutacion
*/

clinvar::iterator clinvar::begin(){
	clinvar::iterator sal;
	
	sal.it = mutBD.begin();

	return sal;
}

/** @brief iterador de mutacion
	@returns iterador apuntando al siguiente elemento de la ultima mutacion
*/

clinvar::iterator clinvar::end(){
	clinvar::iterator sal;

	sal.it = mutBD.end();

	return sal;
}

/** @brief iterador de enfermedad
	@returns iterador apuntando a la primera enfermedad
*/

clinvar::enfermedad_iterator clinvar::ebegin(){
	return EnfDB.begin();
}

/** @brief iterador de mutacion
	@returns iterador apuntando al siguiente elemento de la ultima enfermedad
*/

clinvar::enfermedad_iterator clinvar::eend(){
	return EnfDB.end();
}

/** @brief iterador de genes
	@returns iterador apuntando al primer gen
*/

clinvar::gen_iterator clinvar::gbegin(){
	clinvar::gen_iterator sal;

	sal.itmap = gen_map.begin();
	sal.itlist = sal.itmap->second.begin();
	sal.ptrclinvar = this;

	return sal;
}

/** @brief iterador de mutacion
	@returns iterador apuntando al siguiente elemento del último gen
*/

clinvar::gen_iterator clinvar::gend(){
	clinvar::gen_iterator sal;

	sal.itmap = gen_map.end();
	sal.itlist = sal.itmap->second.begin();
	sal.ptrclinvar = this;

	return sal;
}

// ITERATOR

clinvar::iterator::iterator(){

}

clinvar::iterator::iterator(const iterator &  x){
	it = x.it;
}

const mutacion & clinvar::iterator::operator*(){
	return *it;
}

clinvar::iterator & clinvar::iterator::operator++(){
	++it;

	return *this;
}

clinvar::iterator clinvar::iterator::operator++(int i){
	clinvar::iterator sal(*this);

	++it;

	return sal;
}

clinvar::iterator & clinvar::iterator::operator--(){
	--it;

	return *this;
}

clinvar::iterator clinvar::iterator::operator--(int i){
	clinvar::iterator sal(*this);

	--it;

	return sal;
}

bool clinvar::iterator::operator==(const iterator & x) const{
	return (x.it == it);
}

bool clinvar::iterator::operator!=(const iterator & x) const{
	return (x.it != it);
}

clinvar::iterator & clinvar::iterator::operator=(const iterator & x){
	if(*this != x)
		it = x.it;

	return *this;
}

// GEN_ITERATOR

clinvar::gen_iterator::gen_iterator(){

}

clinvar::gen_iterator::gen_iterator(const gen_iterator &  x){
	itmap = x.itmap;
	itlist = x.itlist;
	ptrclinvar = x.ptrclinvar;
}

const mutacion & clinvar::gen_iterator::operator*(){
	return *(*itlist);
}

clinvar::gen_iterator & clinvar::gen_iterator::operator++(){
	++itlist;

	if(itlist == itmap->second.end()){
		++itmap;
		itlist = itmap->second.begin();
	}

	return *this;
}

clinvar::gen_iterator clinvar::gen_iterator::operator++(int i){
	clinvar::gen_iterator sal(*this);

	++itlist;

	if(itlist == itmap->second.end()){
		++itmap;
		itlist = itmap->second.begin();
	}

	return sal;
}

clinvar::gen_iterator & clinvar::gen_iterator::operator--(){
	--itlist;

	if(itlist == itmap->second.end()){
		--itmap;
		itlist = itmap->second.begin();
	}

	return *this;
}

clinvar::gen_iterator clinvar::gen_iterator::operator--(int i){
	clinvar::gen_iterator sal(*this);

	--itlist;

	if(itlist == itmap->second.end()){
		--itmap;
		itlist = itmap->second.begin();
	}

	return sal;
}

bool clinvar::gen_iterator::operator==(const gen_iterator & x) const{
	return (x.itmap == itmap && x.itlist == itlist && x.ptrclinvar == ptrclinvar);
}

bool clinvar::gen_iterator::operator!=(const gen_iterator & x) const{
	return (x.itmap != itmap || x.itlist != itlist || x.ptrclinvar != ptrclinvar);
}

clinvar::gen_iterator & clinvar::gen_iterator::operator=(const gen_iterator & x){
	if(*this != x){
		itmap = x.itmap;
		itlist = x.itlist;
		ptrclinvar = x.ptrclinvar;
	}

	return *this;
}