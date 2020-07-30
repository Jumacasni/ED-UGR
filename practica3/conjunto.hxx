/** @brief fichero de implementacion de la clase conjunto

*/

/* Como se trata de un conjunto ordenado, el chr y el pos son vitales para su correcto
   funcionamiento por tanto crearemos una función para comprobar su validez en varios métodos */

bool chr_correcto(const conjunto::value_type & e){
    string chr_aux;
    int chr_num;
    
    if(e.getChr() == "")
        return false;
    
    if(e.getChr().compare("X") == 0)
        chr_aux = "23"; 
    else if(e.getChr().compare("Y") == 0)
        chr_aux = "24";
    else if(e.getChr().compare("MT") == 0)
        chr_aux = "25";
    else
        chr_aux = e.getChr();
    
    chr_num = stoi(chr_aux);
    
    return (1 <= chr_num && chr_num <= 25 && e.getPos() > 0);
}

conjunto::conjunto(){ }

conjunto::conjunto (const conjunto & d){
    vm = d.vm;
}

pair<conjunto::value_type,bool>  conjunto::find (const string & chr, const unsigned int & pos) const{

    value_type m_aux;
    m_aux.setChr(chr);
    m_aux.setPos(pos);
    return find(m_aux);
    
}

// No se puede utilizar la búsqueda binaria para buscar una mutación solo por su ID:

pair<conjunto::value_type,bool>  conjunto::find (const string & ID) const{

    conjunto::const_iterator it;
    
    for(it = vm.begin() ; it != vm.end(); ++it){
        if( it->getID() == ID )
            return pair<conjunto::value_type,bool>(*it,true);
    }

    return pair<conjunto::value_type,bool>(mutacion(),false);
}

pair<conjunto::value_type,bool>  conjunto::find (const conjunto::value_type & e)const {
    
    conjunto::const_iterator it;
    
    int Iarriba = vm.size()- 1;
    int Iabajo = 0;
    int Icentro;
    
    while (Iabajo <= Iarriba)
    {
        Icentro = (Iarriba + Iabajo)/2;

        if (this->vm.at(Icentro) == e){
            it = vm.begin() + Icentro;
            return pair<value_type,bool>(*it,true);
        }
        
        else if (e < this->vm.at(Icentro))
            Iarriba=Icentro-1;
            
        else
            Iabajo=Icentro+1;
    }
    
    return pair<value_type,bool>(mutacion(),false);
}

conjunto::size_type conjunto::count (const string & chr, const unsigned int & pos) const{
    value_type e_aux;
    e_aux.setChr(chr);
    e_aux.setPos(pos);
    return count(e_aux);
}

conjunto::size_type conjunto::count (const string & ID) const{
    value_type e_aux;
    e_aux.setID(ID);
    return count(e_aux);
}

conjunto::size_type conjunto::count (const conjunto::value_type & e) const{
    size_type contador = 0;
    
    for(auto it = vm.begin(); it != vm.end(); ++it){
        if(*it == e)
            contador++;
    }

    return contador;
}

// Precondición: Al menos el cromosoma y la posición deben tener valores válidos.

bool conjunto::insert(const conjunto::value_type & e){
    
    if(chr_correcto(e)) {
        pair<conjunto::value_type,bool> e_aux = find(e);
        conjunto::iterator it;
        
        if (e_aux.second == false){
            it = lower_bound(e);
            
            if(it == vm.end()){
                vm.push_back(e);
                return true;
            }
            
            else{
                vm.insert(it, e);
                return true;
            }
        }
    }
    
    return false;
}

bool conjunto::erase(const string & chr, const unsigned int & pos){
    value_type e_aux;
    e_aux.setChr(chr);
    e_aux.setPos(pos);
    return erase(e_aux);
}

/* No se puede utilizar el método implementado, puesto que emplea lower_bound que implementa una
   búsqueda binaria y no sería válido. */

bool conjunto::erase(const string & ID){
    conjunto::iterator it;
    
    for(it = vm.begin() ; it != vm.end(); ++it){
        if( it->getID() == ID ){
            vm.erase(it);
            return true;
        }
    }

    return false;
}

bool conjunto::erase(const conjunto::value_type & e){
    pair<conjunto::value_type,bool> e_aux = find(e); 
    conjunto::iterator it;
    
    if(e_aux.second == true){
        it = lower_bound(e);
        vm.erase(it);
        return true;
    }
    
    return false;
}

void conjunto::clear(){
    vm.clear();
}

conjunto::size_type conjunto::size() const{
    return vm.size();
}

bool conjunto::empty() const{
    if(size() == 0)
        return true;
        
    return false;
}

conjunto & conjunto::operator=(const conjunto & org){
    vm = org.vm;
}

conjunto::iterator conjunto::begin(){
    return vm.begin();
}

conjunto::iterator conjunto::end(){
    return vm.end();
}

conjunto::const_iterator conjunto::cbegin() const{
    return vm.cbegin();
}

conjunto::const_iterator conjunto::cend() const{
    return vm.cend();
}

conjunto::iterator conjunto::lower_bound (const string & chr, const unsigned int & pos) {
    value_type m_aux;
    m_aux.setChr(chr);
    m_aux.setPos(pos);
    return lower_bound(m_aux);
}

conjunto::iterator conjunto::lower_bound (const conjunto::value_type & e){
    conjunto::iterator it, first, last;
    
    first = vm.begin();
    last = vm.end();
    
    typename iterator_traits<conjunto::const_iterator>::difference_type contador, step;
    contador = distance(first, last);
 
    while (contador > 0) {
        it = first; 
        step = contador / 2; 
        advance(it, step);
        if (*it < e) {
            first = ++it;
            contador -= step + 1;
        } else contador = step;
    }
    
    return first;
}

conjunto::iterator conjunto::upper_bound (const string & chr, const unsigned int & pos){
    value_type m_aux;
    m_aux.setChr(chr);
    m_aux.setPos(pos);
    return upper_bound(m_aux);
}

conjunto::iterator conjunto::upper_bound (const conjunto::value_type & e){

    conjunto::iterator it, first, last;
    
    first = vm.begin();
    last = vm.end();
    
    typename iterator_traits<conjunto::iterator>::difference_type contador, step;
    contador = distance(first, last);
 
    while (contador > 0) {
        it = first; 
        step = contador / 2; 
        advance(it, step);
        if (!(e < *it)) {
            first = ++it;
            contador -= step + 1;
        } else contador = step;
    }
    
    return first;
}

bool conjunto::cheq_rep() const{
    bool condicion = true;
    
    for(int i = 0 ; i < vm.size()-1; ++i){
        if(!chr_correcto(vm.at(i)))
            condicion = false;
            
        if(!(vm.at(i) < vm.at(i+1)))
            condicion = false;
    }
    
    if(!chr_correcto(vm.at(vm.size()-1)))
        condicion = false;
        
    return condicion;
}

ostream& operator<< ( ostream & sal, const conjunto & C){
    for(auto it = C.cbegin(); it != C.cend(); it++){
        sal << *it << endl;
    }
    
    return sal;
}
