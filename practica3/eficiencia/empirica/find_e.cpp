#include "../../mutacion.h"
#include "../../enfermedad.h"
#include "../../conjunto.h"
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

bool load(conjunto &  cm, const string & s, int n) {
 ifstream fe;
 string cadena;
 int contador = 0;

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
    while ( !fe.eof() && contador < n){ 
        //cout << "leo:: "<< cadena << endl;
        // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
        mutacion mut = mutacion(cadena);
        // Insertar mutación en el conjunto
        cm.insert(mut);
		  contador++;
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

    for(int i = 1000; i < 140000; i += 5000){
		 load(conjuntoMutaciones, "clinvar_20160831.vcf", i);

		 tantes = high_resolution_clock::now();
		 conjuntoMutaciones.find(*conjuntoMutaciones.begin());
		 tdespues = high_resolution_clock::now();

		 tiempo_transcurrido  = duration_cast<duration<double> >(tdespues - tantes);
    	 cout << i << " " << tiempo_transcurrido.count() << endl;
		 conjuntoMutaciones.clear();
	}	
    
   return 0;
}
