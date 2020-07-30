template <typename T, typename CMP>
conjunto<T,CMP>::conjunto(){ }

template <typename T, typename CMP>
conjunto<T,CMP>::conjunto (const conjunto<T,CMP> & d){
    vm = d.vm;
    comp = d.comp;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::find (const value_type & s){

    conjunto<T,CMP>::iterator sal;

    int Iarriba = vm.size()- 1;
    int Iabajo = 0;
    int Icentro;

    while (Iabajo <= Iarriba){
        Icentro = (Iarriba + Iabajo)/2;

        if (!comp(this->vm.at(Icentro),s) && !comp(s,this->vm.at(Icentro))){
            sal.it = vm.begin() + Icentro;
			sal.elvector = &vm;
            return sal;
        }

        else if (comp(s,this->vm.at(Icentro)))
            Iarriba=Icentro-1;

        else
            Iabajo=Icentro+1;
    }

    return end();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::find (const value_type & s) const {
    
    conjunto<T,CMP>::const_iterator sal;
    
    int Iarriba = vm.size()- 1;
    int Iabajo = 0;
    int Icentro;

    while (Iabajo <= Iarriba){
        Icentro = (Iarriba + Iabajo)/2;

        if (!comp(this->vm.at(Icentro),s) && !comp(s,this->vm.at(Icentro))){
            sal.it = vm.begin() + Icentro;
            sal.elvector = &vm;
            return sal;
        }

        else if (comp(s,this->vm.at(Icentro)))
            Iarriba=Icentro-1;

        else
            Iabajo=Icentro+1;
    }

    return end();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::count (const value_type & e){
    conjunto<T,CMP>::size_type contador = 0;

    for(typename vector<value_type>::iterator it = vm.begin(); it != vm.end(); ++it){
        if(!comp(*it,e) && !comp(e,*it))
            contador++;
    }

    return contador;
}

template <typename T, typename CMP>
pair<typename conjunto<T,CMP>::iterator,bool> conjunto<T,CMP>::insert (const value_type& val) {
    
    conjunto<T,CMP>::iterator sal = lower_bound(val);

    if(sal.it == vm.end()) {
        
        vm.push_back(val);
        sal.it = sal.it-1;
        sal.elvector = &vm;
        return pair<conjunto<T,CMP>::iterator,bool>(sal,true);
    }
    else if(!(!comp(*sal,val) && !comp(val, *sal))){
        
        vm.insert(sal.it, val);
        sal.it = sal.it;
        sal.elvector = &vm;
        return pair<conjunto<T,CMP>::iterator,bool>(sal,true);
    }
        
    return pair<conjunto<T,CMP>::iterator,bool>(end(),false);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::erase (const iterator position){
    conjunto<T,CMP>::iterator sal;

    sal.it = vm.erase(position.it);
    sal.elvector = &vm;
    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::erase (const value_type& val) {
    typename vector<value_type>::iterator it = vm.begin();
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

    return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::begin () {
    conjunto<T,CMP>::iterator sal;

    sal.it = vm.begin();
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::end () {
    conjunto<T,CMP>::iterator sal;

    sal.it = vm.end();
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cbegin () const {
    conjunto<T,CMP>::const_iterator sal;

    sal.it = vm.cbegin();
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cend () const {
    conjunto<T,CMP>::const_iterator sal;

    sal.it = vm.cend();
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator conjunto<T,CMP>::sbegin () {
    conjunto<T,CMP>::secure_iterator sal;

    sal.it = vm.begin();
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator conjunto<T,CMP>::csbegin () const{
    conjunto<T,CMP>::const_secure_iterator sal;

    sal.it = vm.cbegin();
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator conjunto<T,CMP>::send () {
    conjunto<T,CMP>::secure_iterator sal;

    sal.it = vm.end();
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator conjunto<T,CMP>::csend () const{
    conjunto<T,CMP>::const_secure_iterator sal;

    sal.it = vm.cend();
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::impar_iterator conjunto<T,CMP>::ibegin () {
    conjunto<T,CMP>::impar_iterator sal;

    sal.it = vm.begin();
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_impar_iterator conjunto<T,CMP>::cibegin () const{
    conjunto<T,CMP>::const_impar_iterator sal;

    sal.it = vm.cbegin();
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::impar_iterator conjunto<T,CMP>::iend () {
    conjunto<T,CMP>::impar_iterator sal;

    sal.it = vm.end();
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_impar_iterator conjunto<T,CMP>::ciend () const{
    conjunto<T,CMP>::const_impar_iterator sal;

    sal.it = vm.cend();
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::lower_bound (const value_type& val) {
    typename vector<value_type>::iterator it, first, last;
    conjunto<T,CMP>::iterator sal;

    first = vm.begin();
    last = vm.end();

    typename iterator_traits<typename vector<value_type>::iterator>::difference_type contador, step;
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

    sal.it = first;
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::lower_bound (const value_type& val) const {
    typename vector<value_type>::const_iterator it, first, last;
    conjunto<T,CMP>::const_iterator sal;

    first = vm.cbegin();
    last = vm.cend();

    typename iterator_traits<typename vector<value_type>::const_iterator>::difference_type contador, step;
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

    sal.it = first;
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::upper_bound (const value_type& val){
    typename vector<value_type>::iterator it, first, last;
    conjunto<T,CMP>::iterator sal;

    first = vm.begin();
    last = vm.end();

    typename iterator_traits<typename vector<value_type>::iterator>::difference_type contador, step;
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

    sal.it = first;
    sal.elvector = &vm;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::upper_bound (const value_type& val) const{
    typename vector<value_type>::const_iterator it, first, last;
    conjunto<T,CMP>::const_iterator sal;

    first = vm.cbegin();
    last = vm.cend();

    typename iterator_traits<typename vector<value_type>::const_iterator>::difference_type contador, step;
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

    sal.it = first;
    sal.elvector = &vm;

    return sal;
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

/************************************************************************************************/
// ITERATOR

template <typename T, typename CMP>
conjunto<T,CMP>::iterator::iterator(){
}

template <typename T, typename CMP>
conjunto<T,CMP>::iterator::iterator(const iterator & x){
    it = x.it;
    elvector = x.elvector;
}

template <typename T, typename CMP>
conjunto<T,CMP>::iterator::iterator(const secure_iterator & x){
    it = x.it;
    elvector = x.elvector;
}

template <typename T, typename CMP>
const T & conjunto<T,CMP>::iterator::operator*(){
    return *it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator & conjunto<T,CMP>::iterator::operator++(){
    ++it;

    return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::iterator::operator++(int i){
    conjunto<T,CMP>::iterator sal(*this);
    ++it;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator & conjunto<T,CMP>::iterator::operator--(){
    --it;

    return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::iterator::operator--(int i){
    conjunto<T,CMP>::iterator sal(*this);
    --it;

    return sal;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::iterator::operator==(const iterator & x) const{
    return (it == x.it && elvector == x.elvector);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::iterator::operator!=(const iterator & x) const{
    return (it != x.it || elvector != x.elvector);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator & conjunto<T,CMP>::iterator::operator=(const iterator & x){
    it = x.it;
    elvector = x.elvector;

    return *this;
}

// CONST_ITERATOR

template <typename T, typename CMP>
conjunto<T,CMP>::const_iterator::const_iterator(){
}

template <typename T, typename CMP>
conjunto<T,CMP>::const_iterator::const_iterator(const const_iterator & x){
    it = x.it;
    elvector = x.elvector;
}

template <typename T, typename CMP>
conjunto<T,CMP>::const_iterator::const_iterator(const const_secure_iterator & x){
    it = x.it;
    elvector = x.elvector;
}

template <typename T, typename CMP>
const T & conjunto<T,CMP>::const_iterator::operator*() const{
    return *it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator & conjunto<T,CMP>::const_iterator::operator++(){
    ++it;

    return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::const_iterator::operator++(int i){
    conjunto<T,CMP>::const_iterator sal(*this);
    ++it;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator & conjunto<T,CMP>::const_iterator::operator--(){
    --it;

    return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::const_iterator::operator--(int i){
    conjunto<T,CMP>::const_iterator sal(*this);
    --it;

    return sal;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_iterator::operator==(const const_iterator & x) const{
    return (it == x.it && elvector != x.elvector);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_iterator::operator!=(const const_iterator & x) const{
    return (it != x.it || elvector != x.elvector);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator & conjunto<T,CMP>::const_iterator::operator=(const const_iterator & x) const{
    it = x.it;
    elvector = x.elvector;

    return *this;
}

// IMPAR_ITERATOR

template <typename T, typename CMP>
conjunto<T,CMP>::impar_iterator::impar_iterator(){
}

template <typename T, typename CMP>
conjunto<T,CMP>::impar_iterator::impar_iterator(const impar_iterator & x){
	it = x.it;
	elvector = x.elvector;
}

template <typename T, typename CMP>
const T & conjunto<T,CMP>::impar_iterator::operator*(){
	return *it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::impar_iterator & conjunto<T,CMP>::impar_iterator::operator++(){
	conjunto<T,CMP>::impar_iterator sal;
	
	++it;
	while((*it).getPos() % 2 == 0 && it != elvector->end())
		++it;

	return *this;	
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::impar_iterator conjunto<T,CMP>::impar_iterator::operator++(int i){
	conjunto<T,CMP>::impar_iterator sal(*this);
	
	++it;
	while((*it).getPos() % 2 == 0 && it != elvector->end())
		++it;

	return sal;	
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::impar_iterator::operator==(const impar_iterator & x) const{
	return (it == x.it && elvector == x.elvector);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::impar_iterator::operator!=(const impar_iterator & x) const{
	return (it != x.it || elvector != x.elvector);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::impar_iterator & conjunto<T,CMP>::impar_iterator::operator=(const impar_iterator & x){
	it = x.it;
	elvector = x.elvector;

	return *this;
}

// CONST_IMPAR_ITERATOR

template <typename T, typename CMP>
conjunto<T,CMP>::const_impar_iterator::const_impar_iterator(){
}

template <typename T, typename CMP>
conjunto<T,CMP>::const_impar_iterator::const_impar_iterator(const const_impar_iterator & x){
	it = x.it;
	elvector = x.elvector;
}

template <typename T, typename CMP>
const T & conjunto<T,CMP>::const_impar_iterator::operator*() const{
	return *it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_impar_iterator & conjunto<T,CMP>::const_impar_iterator::operator++(){
	conjunto<T,CMP>::const_impar_iterator sal;
	
	++it;
	while((*it).getPos() % 2 == 0 && it != elvector->end())
		++it;

	return *this;	
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_impar_iterator conjunto<T,CMP>::const_impar_iterator::operator++(int i){
	conjunto<T,CMP>::const_impar_iterator sal(*this);
	
	++it;
	while(*it.getPos() % 2 == 0 && it != elvector->end())
		++it;

	return sal;	
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_impar_iterator::operator==(const const_impar_iterator & x) const{
	return (it == x.it && elvector == x.elvector);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_impar_iterator::operator!=(const const_impar_iterator & x) const{
	return (it != x.it || elvector != x.elvector);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_impar_iterator & conjunto<T,CMP>::const_impar_iterator::operator=(const const_impar_iterator & x) const{
	it = x.it;
	elvector = x.elvector;

	return *this;
}

// SECURE_ITERATOR

template <typename T, typename CMP>
conjunto<T,CMP>::secure_iterator::secure_iterator(){
}

template <typename T, typename CMP>
conjunto<T,CMP>::secure_iterator::secure_iterator(const secure_iterator & x){
	it = x.it;
	elvector = x.elvector;
}

template <typename T, typename CMP>
const T & conjunto<T,CMP>::secure_iterator::operator*(){
    assert(elvector->begin() <= it && it < elvector->end());

	return *it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator & conjunto<T,CMP>::secure_iterator::operator++(){
	assert(elvector->begin() <= (it+1) && (it+1) <= elvector->end());

    ++it;

    return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator conjunto<T,CMP>::secure_iterator::operator++(int i){
    conjunto<T,CMP>::secure_iterator sal(*this);

    assert(elvector->begin() <= (it+1) && (it+1) <= elvector->end());

    ++it;

    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator & conjunto<T,CMP>::secure_iterator::operator--(){
    assert(elvector->begin() <= (it-1) && (it-1) <= elvector->end());

    --it;

    return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator conjunto<T,CMP>::secure_iterator::operator--(int i){
    conjunto<T,CMP>::secure_iterator sal(*this);

    assert(elvector->begin() <= (it-1) && (it-1) <= elvector->end());

    --it;

    return sal;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::secure_iterator::operator==(const secure_iterator & x) const{
    assert(elvector->begin() <= it && elvector->begin() <= x.it && it <= elvector->end() && x.it <= elvector->end());

    return (it == x.it && elvector == x.elvector);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::secure_iterator::operator!=(const secure_iterator & x) const{
    assert(elvector->begin() <= it && elvector->begin() <= x.it && it <= elvector->end() && x.it <= elvector->end());

    return (it != x.it || elvector != x.elvector);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator & conjunto<T,CMP>::secure_iterator::operator=(const secure_iterator & x){
    assert(elvector->begin() <= it && it <= elvector->end());
    
    it = x.it;
    elvector = x.elvector;

    return *this;
}

// CONST_SECURE_ITERATOR

template <typename T, typename CMP>
conjunto<T,CMP>::const_secure_iterator::const_secure_iterator(){
}

template <typename T, typename CMP>
conjunto<T,CMP>::const_secure_iterator::const_secure_iterator(const const_secure_iterator & x){
    it = x.it;
    elvector = x.elvector;
}

template <typename T, typename CMP>
const T & conjunto<T,CMP>::const_secure_iterator::operator*() const{
    assert(elvector->cbegin() <= it && it < elvector->cend());

    return *it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator & conjunto<T,CMP>::const_secure_iterator::operator++(){
    assert(elvector->cbegin() <= (it+1) && (it+1) <= elvector->cend());

    ++it;

    return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator conjunto<T,CMP>::const_secure_iterator::operator++(int i){
    conjunto<T,CMP>::const_secure_iterator sal(*this);

    assert(elvector->cbegin() <= (it+1) && (it+1) <= elvector->cend());

    ++it;
    return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator & conjunto<T,CMP>::const_secure_iterator::operator--(){
    assert(elvector->cbegin() <= (it-1) && (it-1) <= elvector->cend());

    --it;

    return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator conjunto<T,CMP>::const_secure_iterator::operator--(int i){
    conjunto<T,CMP>::const_secure_iterator sal(*this);

    assert(elvector->cbegin() <= (it-1) && (it-1) <= elvector->cend());

    --it;
    return sal;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_secure_iterator::operator==(const const_secure_iterator & x) const{
    assert(elvector->cbegin() <= it && elvector->cbegin() <= x.it && it <= elvector->cend() && x.it <= elvector->cend());

    return (it == x.it && elvector == x.elvector);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_secure_iterator::operator!=(const const_secure_iterator & x) const{
    assert(elvector->cbegin() <= it && elvector->cbegin() <= x.it && it <= elvector->cend() && x.it <= elvector->cend());

    return (it != x.it || elvector != x.elvector);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator & conjunto<T,CMP>::const_secure_iterator::operator=(const const_secure_iterator & x) const{
    assert(elvector->cbegin() <= it && it <= elvector->cend());    

    it = x.it;
    elvector = x.elvector;

    return *this;
}