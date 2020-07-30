#include "mutacion.h"
#include "enfermedad.h"
#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

	/** @brief lee un fichero de mutaciones, linea a linea
	@param[in] s nombre del fichero
  @param[in,out] cm objeto tipo conjunto sobre el que se almacenan las mutaciones
	@return true si la lectura ha sido correcta, false en caso contrario
	*/

bool load(conjunto &  cm, const string & s) {
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
        // Insertar mutación en el conjunto
        cm.insert(mut);
        getline(fe,cadena,'\n');
    }

    fe.close();
    return true;
  } // else
  fe.close();
  return false;
 }


int main(int argc, char *argv[]){
    high_resolution_clock::time_point tantes,tdespues;
    duration<double> tiempo_transcurrido;
    conjunto conjuntoMutaciones;
    string query_str; 

    //Cargar las mutaciones en vectorSNPs
    load(conjuntoMutaciones, "clinvar_20160831.vcf");
    
    //Imprimir número de elementos almacenados en conjuntoMutaciones
    cout << "Lectura del fichero finalizada. Mutaciones cargadas: "<<conjuntoMutaciones.size()<<endl;  

    //Imprimir cuántas mutaciones están asociadas al cromosoma 1:
    cout << "Mutaciones asociadas a Chr 1: "<< conjuntoMutaciones.lower_bound("2", 1) - conjuntoMutaciones.begin() <<"\n" << endl; 

    /**@todo ¿Existe la mutación con ID "rs147165522"? Imprimir la mutación y las enfermedades asociadas */
    
    pair<conjunto::value_type,bool> res_find = conjuntoMutaciones.find("rs147165522");
    if(res_find.second)
        cout << "Se ha encontrado la mutación y es la siguiente: " << endl << res_find.first << endl;
    else
        cout << "No se ha encontrado la mutación con ID = rs147165522" << endl;

    /**@todo ¿Existe la mutación en chr/pos "14"/67769578? Imprimir la mutación y las enfermedades asociadas */
  
    res_find = conjuntoMutaciones.find("14",67769578);
    if(res_find.second)
        cout << "Se ha encontrado la mutación y es la siguiente: " << endl << res_find.first << endl;
    else
        cout << "No se ha encontrado la mutación con chr = 14 y Pos = 67769578" << endl;

    /**@todo ¿Cómo podríamos calcular el número de mutaciones del cromosoma 3? (utiliza lower_bound / upper_bound) */

    cout << "Mutaciones asociadas a Chr 3 utilizando lower_bound: " << conjuntoMutaciones.lower_bound("4",1) - conjuntoMutaciones.lower_bound("3",1) << endl;
    cout << "Mutaciones asociadas a Chr 3 utilizando upper_bound: " << conjuntoMutaciones.upper_bound("4",1) - conjuntoMutaciones.upper_bound("3",1) << endl; 
    
   return 0;
}
