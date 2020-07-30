/** @brief fichero de implementacion de la clase enfermedad

*/

#include "enfermedad.h"

/** @brief constructor por defecto
	@returns una enfermedad por defecto
*/

enfermedad::enfermedad(){
   name = "";
   ID = "";
   database = "";
}

/** @brief constructor
	@param name nombre de la enfermedad
	@param ID identificador de la enfermedad
	@param database base de datos de la enfermedad
*/

enfermedad::enfermedad(const string & name, const string & ID, const string & database){
   this->name = name;
   this->ID = ID;
   this->database = database;
}

/** @brief método para modificar el nombre
	@param name nombre de la enfermedad
*/

void enfermedad::setName(const string & name){
   this->name = name;
}

/** @brief método para modificar la ID
	@param ID identificador de la enfermedad
*/

void enfermedad::setID(const string & ID){
   this->ID = ID;
}

/** @brief método para modificar la base de datos
	@param database base de datos de la enfermedad
*/

void enfermedad::setDatabase(const string & database){
   this->database = database;
}
 
/** @brief método para obtener el nombre
	@returns nombre de la enfermedad
*/
 
string enfermedad::getName() const{
   return name;
}

/** @brief método para obtener la ID
	@returns ID de la enfermedad
*/

string enfermedad::getID() const{
   return ID;
}

/** @brief método para obtener la base de datos
	@returns base de datos de la enfermedad
*/

string enfermedad::getDatabase() const{
   return database;
}

/** @brief operador de asignación
	@param e enfermedad a asignar
	@returns la enfermedad asignada
*/

enfermedad& enfermedad::operator=(const enfermedad & e){
  if(*this != e){
     name = e.name;
     ID = e.ID;
     database = e.database;
  }
  
  return *this;
}

/** @brief método para pasar a string la enfermedad
	@returns el valor de la enfermedad en string
*/

string enfermedad::toString() const{
    return name + " " + ID + " " + database;
}

/** @brief operador de comparación
	@param e enfermedad a comparar
	@returns verdadero si las dos enfermedades tienen un ID igual, falso en caso contrario
*/

bool enfermedad::operator==(const enfermedad & e) const{
  if(ID == e.ID)
    return true;
  
  return false;
}

/** @brief operador de desigualdad
	@param e enfermedad a comparar
	@returns verdadero si las enfermedades tienen un ID distinto, falso en caso contrario
*/

bool enfermedad::operator!=(const enfermedad & e) const {
  if(ID != e.ID)
    return true;
  
  return false;
}

/** @brief método para saber si una enfermedad contiene una cadena
	@param str cadena que queremos comprobar
	@returns verdadero si la enfermedad contiene la cadena, falso en caso contrario
*/

 bool enfermedad::nameContains(const string & str) const {
    string name_en_minuscula = name;
	 string str_en_minuscula = str;

    for (unsigned int i=0; i<name.length(); ++i)
        name_en_minuscula[i] = tolower(name[i]);

	 for (unsigned int i=0; i<str.length(); ++i)
		  str_en_minuscula[i] = tolower(str[i]);
    
    if (name_en_minuscula.find(str_en_minuscula) != string::npos)
        return true;
        
    return false;
 }
 
/** @brief operador salida
	@param os flujo de salida
	@param e enfermedad
	@returns toda la información sobre la enfermedad
*/

 ostream& operator<< ( ostream& os, const enfermedad & e) {
    os << e.getName() << " " << e.getID() << " " << e.getDatabase();
	 os << endl;
 
   return os;
 }
   
   
 
