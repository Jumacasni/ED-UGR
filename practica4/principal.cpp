/* Juan Manuel Castillo Nievas: 50%
   Álvaro Fernández García: 50%
*/

#include "mutacion.h"
#include "enfermedad.h"
#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

using namespace std;

// Implementación de los functores:

class MayorPosChr{
    public:
    bool operator()(const mutacion & a, const mutacion & b) {
        return !(a<b) && !(a == b);
    }
};

class MenorID{
    public:
    bool operator()(const mutacion & a, const mutacion & b){
      return a.getID() < b.getID();
    }
};

class MayorID{  
  public:
    bool operator()(const mutacion & a, const mutacion & b){
      return a.getID() > b.getID();
    }
};

class MenorE{
    public:
    bool operator()(const enfermedad & a, const enfermedad & b){
        return a.getID() < b.getID();     
    }
};

class MayorE{
    public:
    bool operator()(const enfermedad & a, const enfermedad & b){
        return a.getID() > b.getID();     
    }
};

/** @brief lee un fichero de mutaciones, linea a linea
@param[in] s nombre del fichero
@param[in,out] cm objeto tipo conjunto sobre el que se almacenan las mutaciones
@return true si la lectura ha sido correcta, false en caso contrario
*/

template < typename CMP>
bool load(conjunto<mutacion,CMP> &  cm, const string & s) {
 ifstream fe;
 string cadena;
 
 cout << "Abrimos "<< s << endl;
 fe.open(s.c_str(), ifstream::in);
 if (fe.fail()){
   cerr << "Error al abrir el fichero " << s << endl;
 }
 else {
    //leo la cabecera del fichero (líneas que comienzan con #)
    do{
      getline(fe,cadena,'\n');
    }while (cadena.find("#")==0 && !fe.eof());

    //leo la tabla de mutaciones, una línea cada vez
    while ( !fe.eof() ){
        //cout << "leo:: "<< cadena << endl;
        // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
        mutacion mut = mutacion(cadena);
        cm.insert(mut);
        getline(fe,cadena,'\n');
    }

    fe.close();
    return true;
  } // else
  fe.close();
  return false;
 }


// Método para extraer un conjunto de enfermedades a partir del archivo de mutaciones: 
 
template <typename CMP>
bool loadE(conjunto<enfermedad,CMP> &  ce, const string & s) {
 ifstream fe;
 string cadena;
 
 cout << "Abrimos "<< s << endl;
 fe.open(s.c_str(), ifstream::in);
 if (fe.fail()){
   cerr << "Error al abrir el fichero " << s << endl;
 }
 else {
    //leo la cabecera del fichero (líneas que comienzan con #)
    do{
      getline(fe,cadena,'\n');
    }while (cadena.find("#")==0 && !fe.eof());

    //leo la tabla de mutaciones, una línea cada vez
    while ( !fe.eof() ){
        //cout << "leo:: "<< cadena << endl;
        // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
        mutacion mut = mutacion(cadena);
        for(int i = 0; i < mut.getEnfermedades().size();++i)
            ce.insert(mut.getEnfermedades().at(i));
            
        getline(fe,cadena,'\n');
    }

    fe.close();
    return true;
  } // else
  fe.close();
  return false;
 }

int main(int argc, char *argv[]){
    
    // Seleccionar que tipo de conjunto queremos cargar:    
    
/*-------------------------------------------------------------* /    
    conjunto<mutacion, less<mutacion>> conjuntoMutaciones;
/*-------------------------------------------------------------* /        
    conjunto<mutacion, MayorPosChr> conjuntoMutaciones;
/*-------------------------------------------------------------* /        
    conjunto<mutacion, MenorID> conjuntoMutaciones;
/*-------------------------------------------------------------* /        
    conjunto<mutacion, MayoID> conjuntoMutaciones;
/*-------------------------------------------------------------*/        
    conjunto<enfermedad, MenorE> conjuntoEnfermedades;
/*-------------------------------------------------------------* /   
    conjunto<enfermedad, MayorE> conjuntoEnfermedades;
/*-------------------------------------------------------------*/       
    
    string query_str;
    
/*-----------------------------------------------------------------------------------------------------------------* /          
    //Cargar las mutaciones en vectorSNPs
    load(conjuntoMutaciones, "clinvar_20160831.vcf");
    cout << "Lectura del fichero finalizada. Mutaciones cargadas: "<< conjuntoMutaciones.size() <<endl;
 /*-----------------------------------------------------------------------------------------------------------------*/   
    //Cargar las enfermedades en vectorSNPs
    loadE(conjuntoEnfermedades, "clinvar_20160831.vcf");
    cout << "Lectura del fichero finalizada. Enfermedades cargadas: "<< conjuntoEnfermedades.size() <<endl;
/*-----------------------------------------------------------------------------------------------------------------*/
    
   return 0;
}
