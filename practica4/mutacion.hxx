/** @brief fichero de implementacion de la clase mutación

*/

/** @brief constructor por defecto

*/

mutacion::mutacion() {
	ID = "";
	chr = ""; 
	pos = 0;
	common = 0;
}

/** @brief constructor de copia
	@param m mutación para copiar
*/

mutacion::mutacion(const mutacion& m){
    ID = m.ID;
    chr = m.chr;
    pos = m.pos;
    ref_alt = m.ref_alt;
    genes = m.genes;
    common = m.common;
    caf = m.caf;
    enfermedades = m.enfermedades;
    clnsig = m.clnsig;
}

/** @brief función auxiliar para extraer subcadenas de una cadena
	@param str cadena de la que se desea extraer la subcadena.
	@param ini el valor de la posición a partir del cual queremos empezar a extraer una cadena
	@param fin el valor de la posición final de la subcadena que queremos extraer
	@param dato delimitador que indica el final de la subcadena a extraer
	@returns una subcadena
*/

string extraer_cadena(const string & str, size_t & ini, size_t & fin, const char dato) {
	fin = str.find(dato, ini);
	int lon = fin-ini;
	return str.substr(ini, lon);
}

/** @brief constructor a partir de un string
	@param str cadena de string de la mutación
*/

mutacion::mutacion(const string & str){
    size_t ini = 0, fin;

    chr = extraer_cadena(str, ini, fin, '\t');
    ini = fin + 1;

    pos = stoul(extraer_cadena(str, ini, fin, '\t'));
    ini = fin + 1;

    ID = extraer_cadena(str, ini, fin, '\t');
    ini = fin + 1; 

    for(int i = 0 ; i < 2 ; ++i){
        ref_alt.push_back(extraer_cadena(str, ini, fin, '\t'));
        ini = fin + 1;
    }
    
	// GENEINFO
    // Nos situamos en la posición donde se encuentra GNINFO:
    
    fin = str.find("GENEINFO", ini);
    ini = fin + 1;
    fin = str.find("=", ini);
    ini = fin + 1;
    
    // Extraemos todo el contenido de GENINFO junto con ";" que nos servirá de delimitador:
    
    string str_aux = extraer_cadena(str, ini, fin, ';');
    str_aux.push_back(';');
    ini = fin + 1;
    
    // Dividiremos a continuación las partes de geninfo:

    size_t cini = 0, cfin;
    bool fin_elementos = true;
    
	while(fin_elementos) {
	    if(str_aux.find('|', cini) != string::npos){
			genes.push_back(extraer_cadena(str_aux, cini, cfin, '|'));
			cini = cfin + 1;
		}
		else{
			genes.push_back(extraer_cadena(str_aux, cini, cfin, ';'));
			fin_elementos = false;
		}
	}
    
    // Realizamos el mismo procedimiento para CLNSIG
    
    fin = str.find("CLNSIG", ini);
    ini = fin + 1;
    fin = str.find("=", ini);
    ini = fin + 1;
    str_aux = extraer_cadena(str, ini, fin, ';');
    str_aux.push_back(';');
    ini = fin + 1;
    
    cini = 0, cfin;
    fin_elementos = true;
    
	while(fin_elementos) {
	    if(str_aux.find('|', cini) != string::npos){
			clnsig.push_back(stoi(extraer_cadena(str_aux, cini, cfin, '|')));
			cini = cfin + 1;
		}
		else if (str_aux.find(',', cini) != string::npos) {
		    clnsig.push_back(stoi(extraer_cadena(str_aux, cini, cfin, ',')));
			cini = cfin + 1;
		}
		else{
			clnsig.push_back(stoi(extraer_cadena(str_aux, cini, cfin, ';')));
			fin_elementos = false;
		}
	}
	
	// Lectura de las enfermedades:
    
    vector<string> CLNDSDB, CLNDSDBID, CLNDBN;
    
	// CLNDSDB
	
	fin = str.find("=", ini);
	ini = fin + 1;
	str_aux = extraer_cadena(str, ini, fin, ';');
    str_aux.push_back(';');
    ini = fin + 1;
    
    cini = 0, cfin;
    fin_elementos = true;
    
	while(fin_elementos) {
        if(str_aux.find('|', cini) != string::npos && str_aux.find('|', cini) < str_aux.find(',', cini)){
    		CLNDSDB.push_back(extraer_cadena(str_aux, cini, cfin, '|'));
    		cini = cfin + 1;
    	  }
  
        else if(str_aux.find(',', cini) != string::npos){
    		CLNDSDB.push_back(extraer_cadena(str_aux, cini, cfin, ','));
    		cini = cfin + 1;
    	}

    	else{
    		CLNDSDB.push_back(extraer_cadena(str_aux, cini, cfin, ';'));
    		fin_elementos = false;
    	}
    }
	
	// CLNDSDBID

	fin = str.find("=", ini);
	ini = fin + 1;
	str_aux = extraer_cadena(str, ini, fin, ';');
    str_aux.push_back(';');
    ini = fin + 1;
    
    cini = 0, cfin;
    fin_elementos = true;

	while(fin_elementos) {

      if(str_aux.find('|', cini) != string::npos && str_aux.find('|', cini) < str_aux.find(',', cini)){
    		CLNDSDBID.push_back(extraer_cadena(str_aux, cini, cfin, '|'));
    		cini = cfin + 1;
    	}

		else if(str_aux.find(',', cini) != string::npos){
    		CLNDSDBID.push_back(extraer_cadena(str_aux, cini, cfin, ','));
    		cini = cfin + 1;
    	}

    	else{
    		CLNDSDBID.push_back(extraer_cadena(str_aux, cini, cfin, ';'));
    		fin_elementos = false;
    	}
    }

    // CLNDBN
    
	fin = str.find("=", ini);
	ini = fin + 1;
	str_aux = extraer_cadena(str, ini, fin, ';');
   	str_aux.push_back(';');
   	ini = fin + 1;

    cini = 0, cfin;
    fin_elementos = true;
    
	while(fin_elementos) {
        if(str_aux.find('|', cini) != string::npos && str_aux.find('|', cini) < str_aux.find(',', cini)){
    		CLNDBN.push_back(extraer_cadena(str_aux, cini, cfin, '|'));
    		cini = cfin + 1;
    	 }

		  else if(str_aux.find(',', cini) != string::npos){
			CLNDBN.push_back(extraer_cadena(str_aux, cini, cfin, ','));
    		cini = cfin + 1;
		  }

    	else{
    		CLNDBN.push_back(extraer_cadena(str_aux, cini, cfin, ';'));
    		fin_elementos = false;
    	}
    }

	if(CLNDSDBID.size() < CLNDBN.size()){
		for(int i = CLNDSDBID.size(); i < CLNDBN.size(); ++i)
			CLNDSDBID.push_back("");
	}

	if(CLNDSDB.size() < CLNDBN.size()){
		for(int i = CLNDSDB.size(); i < CLNDBN.size(); ++i)
			CLNDSDB.push_back("");
	}


    // Creación de las enfermedades
    
    for(int i = 0 ; i < CLNDBN.size(); ++i)
        enfermedades.push_back(enfermedad(CLNDBN[i], CLNDSDBID[i], CLNDSDB[i]));

    if(str.find("CAF", ini) !=  string::npos) {
    
        fin = str.find("CAF", ini);
        ini = fin + 1;
        fin = str.find("=", ini);
        ini = fin + 1;
    
        // Extraemos todo el contenido de CAF junto con ";" que nos servirá de delimitador:
    
        string str_aux = extraer_cadena(str, ini, fin, ';');
        str_aux.push_back(';');
        ini = fin + 1;

        // Dividiremos a continuación las partes de caf:

        size_t cini = 0, cfin;
        bool fin_elementos = true;
        string cadena;
        
	    while(fin_elementos) {
	        if(str_aux.find(',', cini) != string::npos){
	            cadena = extraer_cadena(str_aux, cini, cfin, ',');

	            if (cadena.compare(".") == 0)
			        cadena = "0.000";
			        
			    	caf.push_back(stof(cadena));
			    	cini = cfin + 1;
		    }
		    else{
		        cadena = extraer_cadena(str_aux, cini, cfin, ';');
		        if (cadena.compare(".") == 0)
			        cadena = "0.000";
			        
			    caf.push_back(stof(cadena));
			    fin_elementos = false;
		    }
	   	}
		
		fin = str.find("=", ini);
        ini = fin + 1;

		if(extraer_cadena(str, ini, fin, '\n').compare("1") == 0)
            common = true;
        else
            common = false;
	}
}

/** @brief método para modificar la ID
	@param id identificador de la mutación
*/

void mutacion::setID(const string & id){
    ID = id;
}

/** @brief método para modificar el cromosoma
	@param cromosoma de la mutación
*/

void mutacion::setChr(const string & chr) {
    this->chr = chr;
}

/** @brief método para modificar la posición dentro del cromosoma
	@param pos identificador de la posición dentro del cromosoma
*/

void mutacion::setPos(const unsigned int & pos) {
    this->pos = pos;
}

/** @brief método para modificar base(s) en el genoma de referencia y alternativa(s) posible(s)
	@param ref_alt vector con las bases y alternativas posibles
*/
  
void mutacion::setRef_alt(const std::vector<string> & ref_alt) {
    this->ref_alt = ref_alt;
}

/** @brief método para modificar genes
	@param genes genes asociados al SNP
*/

void mutacion::setGenes (const std::vector<string> & genes) {
    this->genes = genes;
}

/** @brief método para modificar si una mutación es común o no
	@param common 1 si es común, 0 si no lo es
*/

void mutacion::setCommon (const bool & common) {
    this->common = common;
}
  
/** @brief método para modificar la frecuencia de cada base del SNP en la población
	@param caf vector con la frecuencia de cada base
*/

void mutacion::setCaf (const std::vector<float> & caf) {
    this->caf = caf;
}
 
/** @brief método para modificar las enfermedades asociadas a la mutación
	@param enfermedades enfermedades asociadas a la mutación
*/

void mutacion::setEnfermedades (const std::vector<enfermedad> & enfermedades) {
    this->enfermedades = enfermedades;
}
 
/** @brief método para modificar la relevancia clínica del SNP para cada enfermedad
	@param clnsig relevancia clínica del SNP 
*/
 
void mutacion::setClnsig (const std::vector<int> & clnsig) {
    this->clnsig = clnsig;
}

/** @brief método para obtener la ID
	@returns el identificador de la mutación
*/

string mutacion::getID( ) const {
    return ID;
}

/** @brief método para obtener el cromosoma de la mutación
	@returns cromosoma
*/

string mutacion::getChr( ) const {
    return chr;
}
 
/** @brief método para obtener el identificador de la posición dentro del cromosoma
	@returns identificador de la posición dentro del cromosoma
*/

unsigned int mutacion::getPos( ) const {
    return pos;
}

/** @brief método para obtener base(s) en el genoma de referencia y alternativa(s) posible(s)
	@returns base(s) en el genoma de referencia y alternativa(s) posible(s)
*/

const std::vector<string> & mutacion::getRef_alt () const {
    return ref_alt;
}
 
/** @brief método para obtener los genes
	@returns genes
*/

const std::vector<string> & mutacion::getGenes () const {
    return genes;
}
  
/** @brief método para saber si una mutación es común o no
	@returns 1 si es común, 0 en caso contrario
*/

bool mutacion::getCommon () const {
    return common;
}
 
/** @brief método para obtener la frecuencia de cada base de la mutación en la población
	@returns frecuencia de cada base de la mutación en la población
*/

const std::vector<float> & mutacion::getCaf () const {
    return caf;
}

/** @brief método para obtener las enfermedades asociadas a la mutación
	@returns enfermedades asociadas a la mutación
*/

const std::vector<enfermedad> & mutacion::getEnfermedades () const {
    return enfermedades;
}
  
/** @brief método para obtener la relevancia clínica del SNP para cada enfermedad
	@returns relevancia clínica del SNP para cada enfermedad
*/

const std::vector<int> & mutacion::getClnsig () const {
    return clnsig;
}

/** @brief operador de asignación
	@param mutación a asignar
	@returns la mutación sobre la que hemos asignado
*/

mutacion & mutacion::operator=(const mutacion & m) {
        ID = m.ID;
        chr = m.chr;
        pos = m.pos;
        ref_alt = m.ref_alt;
        genes = m.genes;
        common = m.common;
        caf = m.caf;
        enfermedades = m.enfermedades;
        clnsig = m.clnsig;
    
    return *this;
}

/** @brief operador de igualdad
	@returns verdadero si el ID de las mutaciones es igual, falso en caso contrario
*/

bool mutacion::operator==(const mutacion & m) const {
    if(ID.compare(m.ID) == 0)
        return true;
    else if(chr.compare(m.chr) == 0 && pos == m.pos)
        return true;
        
    return false;
}

/** @brief operador de comparación menor
	@param m mutación a comparar
	@returns verdadero si la mutación sobre la que se opera tiene un cromosoma de menor valor, si el cromosoma es
	el mismo, se ordenará según la posición, falso en caso contrario
*/

bool mutacion::operator<(const mutacion & m) const {
    string chr_aux1, chr_aux2;
    int chr_int1, chr_int2;
    
    if(chr.compare("X") == 0)
        chr_aux1 = "23";
    else if(chr.compare("Y") == 0)
        chr_aux1 = "24";
    else if(chr.compare("MT") == 0)
        chr_aux1 = "25";
    else
        chr_aux1 = chr;
        
    if(m.chr.compare("X") == 0)
        chr_aux2 = "23";
    else if(m.chr.compare("Y") == 0)
        chr_aux2 = "24";
    else if(m.chr.compare("MT") == 0)
        chr_aux2 = "25";
    else
        chr_aux2 = m.chr;
        
    chr_int1 = stoi(chr_aux1);
    chr_int2 = stoi(chr_aux2);
    
    if(chr_int1 == chr_int2) 
        return pos < m.pos;
    else
        return chr_int1 < chr_int2;
}

/** @brief operador de salida, imprime una mutación
	@param os flujo de salida
	@param m mutación a devolver
	@returns flujo de salida
*/

ostream& operator<< ( ostream& os, const mutacion& m) {
    os << m.getChr() << " " << m.getPos() << " " << m.getID() << endl;
 
    for(int i = 0; i < m.getGenes().size() ; ++i)
        os << m.getGenes().at(i) << " ";
        
    os << endl;
    
    for(int i = 0; i < m.getRef_alt().size() ; ++i)
        os << m.getRef_alt().at(i) << " ";
    
    os << endl;
    
   for(int i = 0; i < m.getClnsig().size() ; ++i)
        os << m.getClnsig().at(i) << " "; 
        
    os << endl;

    for(int i = 0; i < m.getEnfermedades().size() ; ++i)
        os << m.getEnfermedades().at(i) << " ";
    
	 os << endl;

    for(int i = 0; i < m.getCaf().size() ; ++i)
        os << m.getCaf().at(i) << " ";
    
	 os << endl;

    os << m.getCommon();    
    
	 os << endl;

    return os;
}

