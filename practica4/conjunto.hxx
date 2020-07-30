template <typename T, typename CMP>
conjunto<T,CMP>::conjunto(){ }

template <typename T, typename CMP>
conjunto<T,CMP>::conjunto (const conjunto<T,CMP> & d){
    vm = d.vm;
    comp = d.comp;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::find (const value_type & s){

    conjunto::iterator it;

    int Iarriba = vm.size()- 1;
    int Iabajo = 0;
    int Icentro;

    while (Iabajo <= Iarriba){
        Icentro = (Iarriba + Iabajo)/2;

        if (!comp(this->vm.at(Icentro),s) && !comp(s,this->vm.at(Icentro))){
            it = vm.begin() + Icentro;
            return it;
        }

        else if (comp(s,this->vm.at(Icentro)))
            Iarriba=Icentro-1;

        else
            Iabajo=Icentro+1;
    }

    return this->vm.end();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::find (const value_type & s) const {
    
    conjunto::const_iterator it;
    
    int Iarriba = vm.size()- 1;
    int Iabajo = 0;
    int Icentro;

    while (Iabajo <= Iarriba){
        Icentro = (Iarriba + Iabajo)/2;

        if (!comp(this->vm.at(Icentro),s) && !comp(s,this->vm.at(Icentro))){
            it = vm.begin() + Icentro;
            return it;
        }

        else if (comp(s,this->vm.at(Icentro)))
            Iarriba=Icentro-1;

        else
            Iabajo=Icentro+1;
    }

    return this->vm.end();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::count (const value_type & e){
    conjunto<T,CMP>::size_type contador = 0;

    for(conjunto<T,CMP>::iterator it = vm.begin(); it != vm.end(); ++it){
        if(!comp(*it,e) && !comp(e,*it))
            contador++;
    }

    return contador;
}

template <typename T, typename CMP>
pair<typename conjunto<T,CMP>::iterator,bool> conjunto<T,CMP>::insert (const value_type& val) {
    

    conjunto<T,CMP>::iterator it = lower_bound(val);

    if(it == vm.end()) {
        
        vm.push_back(val);
        return pair<conjunto::iterator,bool>(it-1,true);
    }
    else if(!(!comp(*it,val) && !comp(val, *it))){
        
        vm.insert(it, val);
        return pair<conjunto::iterator,bool>(it,true);
    }
        
    return pair<conjunto::iterator,bool>(vm.end(),false);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::erase (const iterator position){
    return vm.erase(position);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::erase (const value_type& val) {
    typename conjunto<T,CMP>::iterator it = vm.begin();
    conjunto::size_type cont = 0;
    
    while(it != vm.end()){
        if(!comp(*it,val) && !comp(val,*it)){
            it = vm.erase(it);
            cont++;
        }
        else
            it++;
    }
    
    return cont;
}

template <typename T, typename CMP>
void conjunto<T,CMP>::clear() {
    vm.clear();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::size() const{
    return vm.size();
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::empty() const {
    return (vm.size() == 0);
}

template <typename T, typename CMP>
conjunto<T,CMP> & conjunto<T,CMP>::operator=( const conjunto<T,CMP> & org) {
    vm = org.vm;
    comp = org.comp;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::begin () {
    return vm.begin();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::end () {
    return vm.end();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cbegin () const {
    return vm.cbegin();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cend () const {
    return vm.cend();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::lower_bound (const value_type& val) {
    conjunto::iterator it, first, last;

    first = vm.begin();
    last = vm.end();

    typename iterator_traits<conjunto::iterator>::difference_type contador, step;
    contador = distance(first, last);

    while (contador > 0) {
        it = first;
        step = contador / 2;
        advance(it, step);
        if (comp(*it, val)) {
            first = ++it;
            contador -= step + 1;
        } else contador = step;
    }

    return first;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::lower_bound (const value_type& val) const {
    conjunto::const_iterator it, first, last;

    first = vm.cbegin();
    last = vm.cend();

    typename iterator_traits<conjunto::const_iterator>::difference_type contador, step;
    contador = distance(first, last);

    while (contador > 0) {
        it = first;
        step = contador / 2;
        advance(it, step);
        if (comp(*it, val)) {
            first = ++it;
            contador -= step + 1;
        } else contador = step;
    }

    return first;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::upper_bound (const value_type& val){
    conjunto::iterator it, first, last;

    first = vm.begin();
    last = vm.end();

    typename iterator_traits<conjunto::iterator>::difference_type contador, step;
    contador = distance(first, last);

    while (contador > 0) {
        it = first;
        step = contador / 2;
        advance(it, step);
        if (!(comp(val,*it))) {
            first = ++it;
            contador -= step + 1;
        } else contador = step;
    }

    return first;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::upper_bound (const value_type& val) const{
    conjunto::const_iterator it, first, last;

    first = vm.cbegin();
    last = vm.cend();

    typename iterator_traits<conjunto::const_iterator>::difference_type contador, step;
    contador = distance(first, last);

    while (contador > 0) {
        it = first;
        step = contador / 2;
        advance(it, step);
        if (!(comp(val,*it))) {
            first = ++it;
            contador -= step + 1;
        } else contador = step;
    }

    return first;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::cheq_rep( ) const {
    bool condicion = true;
    
    for(int i = 0 ; i < vm.size()-1; ++i){
        if(!(comp(vm.at(i), vm.at(i+1))))
            condicion = false;
    }
    
    return condicion;
}

template <typename T, typename CMP>
ostream &  operator << ( ostream & sal, const conjunto<T,CMP> & C){
    for(auto it = C.cbegin(); it != C.cend(); it++){
        sal << *it << endl;
    }

    return sal;
}