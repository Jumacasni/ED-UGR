/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Práctica Nmer ///////////////////////////////////////////////////////
/////////////////////////////////// ETSIIT Universidad de Granada ///////////////////////////////////////
/////////////////////////////////// Estructura de Datos 2016-2017 ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Juan Manuel Castillo Nievas /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "ktree.h"
#include "Nmer.h"

using namespace std;

int main(){

Nmer nm1, nm2, nm3, nm4, nm5, nm6, nm7, nm8, nm9, nm10;
nm1.loadNmer("./datos/1.txt", 3);

cout << "Nmer de ../datos/1.txt con longitud máxima 3" << endl;
nm1.list_Nmer();
cout << "Size: " << nm1.size() << " Longitud: " << nm1.length() << endl << endl;

cout << "rareNmer de ../datos/1.txt con threshold 100: " << endl << endl;
set<pair<string,int>, OrdenCre> rare = nm1.rareNmer(100);
for(auto it = rare.begin(); it != rare.end(); ++it){
  cout << (*it).first << " " << (*it).second << endl;
}
cout << endl << endl;

cout << "commonNmer de ../datos/1.txt con threshold 500: " << endl << endl;
set<pair<string,int>, OrdenDecre> common = nm1.commonNmer(500);
for(auto it = common.begin(); it != common.end(); ++it){
  cout << (*it).first << " " << (*it).second << endl;
}
cout << endl << endl;

cout << "Nmers de ../datos/1.txt con longitud 3: " << endl << endl;
set<pair<string,int>, OrdenCre> l = nm1.level(3);
for(auto it = l.begin(); it != l.end(); ++it){
  cout << (*it).first << " " << (*it).second << endl;
}
cout << endl << endl;

cout << "Cargando todos los datos con longitud máxima 20..." << endl;
nm1.loadNmer("./datos/1.txt", 20);
nm2.loadNmer("./datos/2.txt", 20);
nm3.loadNmer("./datos/3.txt", 20);
nm4.loadNmer("./datos/4.txt", 20);
nm5.loadNmer("./datos/5.txt", 20);
nm6.loadNmer("./datos/6.txt", 20);
nm7.loadNmer("./datos/7.txt", 20);
nm8.loadNmer("./datos/8.txt", 20);
nm9.loadNmer("./datos/9.txt", 20);
nm10.loadNmer("./datos/10.txt", 20);

cout << "Calculamos las distancias: " << endl;

float dist = nm1.distance(nm2);
cout << "Distancia entre ../datos/1.txt y ../datos/2.txt: " << dist << endl;

dist = nm1.distance(nm3);
cout << "Distancia entre ../datos/1.txt y ../datos/3.txt: " << dist << endl;

dist = nm1.distance(nm4);
cout << "Distancia entre ../datos/1.txt y ../datos/4.txt: " << dist << endl;

dist = nm1.distance(nm5);
cout << "Distancia entre ../datos/1.txt y ../datos/5.txt: " << dist << endl;

dist = nm1.distance(nm6);
cout << "Distancia entre ../datos/1.txt y ../datos/6.txt: " << dist << endl;

dist = nm1.distance(nm7);
cout << "Distancia entre ../datos/1.txt y ../datos/7.txt: " << dist << endl;

dist = nm1.distance(nm8);
cout << "Distancia entre ../datos/1.txt y ../datos/8.txt: " << dist << endl;

dist = nm1.distance(nm9);
cout << "Distancia entre ../datos/1.txt y ../datos/9.txt: " << dist << endl;

dist = nm1.distance(nm10);
cout << "Distancia entre ../datos/1.txt y ../datos/10.txt: " << dist << endl << endl;

cout << "A continuación se muestra el Nmer de ../datos/1.txt que tiene como prefijo ACTAAGATATATACAC (ACTAAGATATATACAC también está incluido):" << endl;
Nmer pre = nm1.prefix("actaagatatatacac");
pre.list_Nmer();
cout << endl << endl;

cout << "¿El Nmer de ../datos/1.txt contiene el Nmer ACTAAGA?:" << endl;
if(nm1.containsString("actaaga"))
  cout << "Sí lo contiene" << endl;
else
	cout << "No lo contiene" << endl;
cout << endl << endl;

cout << "¿El Nmer de ../datos/1.txt contiene el Nmer ACTAAGAATGAAGGAC?:" << endl;
if(nm1.containsString("actaagaatgaaggac"))
  cout << "Sí lo contiene" << endl;
else
	cout << "No lo contiene" << endl;
cout << endl << endl;

cout << "Cargo el Nmer de ../datos/1.txt con longitud 3 y el Nmer de ../datos/2.txt con longitud 5..." << endl;
nm1.loadNmer("./datos/1.txt", 3);
nm2.loadNmer("./datos/2.txt", 5);
cout << "La suma es el siguiente Nmer: " << endl;
Nmer suma = nm1.Union(nm2);
suma.list_Nmer();
cout << endl << endl;

cout << "¿El Nmer de ../datos/1.txt está incluido en el Nmer de ../datos/2.txt?:" << endl;
if(nm1.included(nm2))
  cout << "Sí está incluido" << endl;
else
	cout << "No está incluido" << endl;
cout << endl << endl;

cout << "¿El Nmer de ../datos/2.txt está incluido en el Nmer de ../datos/1.txt?:" << endl;
if(nm2.included(nm1))
  cout << "Sí está incluido" << endl;
else
	cout << "No está incluido" << endl;

return 0;

}