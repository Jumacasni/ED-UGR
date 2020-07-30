#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <vector> 
#include <string>
#include <chrono>
#include <algorithm>


using namespace std;
using namespace std::chrono;

void lee_fichero( const char * nf, vector<string> & V) {
 ifstream fe;
  string s;
 fe.open(nf, ifstream::in);
 while ( !fe.eof() )
   { fe >> s;
     if (!fe.eof())
       V.push_back(s);
   }
 fe.close();
}

void insercion(vector<string> & T, int ini, int n)
{
	int i,j;
	string v;
 
   for (i = ini; i < n; i++)
   {
   	v = T[i];
     	j = i;
      while (j > 0 && T[j-1] > v)
      {
      	T[j] = T[j-1];
         j--;
      }
             
       T[j] = v;
    }   
}


void calcula_tiempo(int tama, vector<string> & V){

high_resolution_clock::time_point tantes,tdespues;
duration<double> tiempo_transcurrido;

vector<string> aux(V.size());
aux = V;

  tantes = high_resolution_clock::now();
  insercion(aux,1,tama); // Solo queremos evaluar este algoritmo
  tdespues = high_resolution_clock::now();

  aux.clear();


tiempo_transcurrido  = duration_cast<duration<double> >(tdespues - tantes);
cout << tama << " " << tiempo_transcurrido.count() << endl;
 
}

int main(int argc, char * argv[]){
int tmin,tmax,inc; // tamaño minimo, maximo e incremento
// Llamada ejecutable minimo maximo inc 

  if (argc < 4) {
   cout << "Llamada ejecutable tminimo tmaximo inc" <<endl;
   return(0);
}
else {
   tmin = std::atoi(argv[1]);
   tmax = std::atoi(argv[2]);
   inc = std::atoi(argv[3]);
}

 vector<string> Dicc;
 vector<string> Q;

 lee_fichero("lema.txt", Dicc); // Ojo, el vector no esta ordenado!!!

 lee_fichero("quijote.txt", Q);

for (int i = tmin; i<=tmax; i+=inc)
   calcula_tiempo(i, Dicc);



  
return 0;

}
