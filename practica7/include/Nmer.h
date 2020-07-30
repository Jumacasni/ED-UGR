
/**
 * @file Nmer.h
 * @brief TDA Nmer
 *   Representa un conjunto de Nmer subsecuencias de tamaño 1 hasta N que se pueden obtener a partir de una cadena de ADN
 * @author alumno
 * @bug Por espeficicar
 */
#ifndef __NMER_H
#define __NMER_H

#include "ktree.h"
#include <string>
#include <set>

using namespace std;

class OrdenCre{
  public:
    bool operator()(const pair<string,int> & a, const pair<string,int> & b){
      if(a.second < b.second)
        return true;
      
      else if(a.second > b.second)
        return false;

      else{
        if(a.first < b.first)
          return true;
        else
          return false;
      }
    }
};

class OrdenDecre{
  public:
    bool operator()(const pair<string,int> & a, const pair<string,int> & b){
      if(a.second > b.second)
        return true;
      
      else if(a.second < b.second)
        return false;

      else{
        if(a.first < b.first)
          return true;
        else
          return false;
      }
    }
};

class Nmer {
public:

  typedef unsigned int size_type;
  
  /** @brief Constructor primitivo .
      Crea un Nmer de longitud maxima 0, con el valor ('-',0) en la raíz
  */
  Nmer();
  
  /** @brief lectura fichero serializado
   * @param nombre_fichero fichero serializado con extension .srl
   *
   * Genera a partir del fichero el ktree que contiene todos los kmers asociados a una cadena de ADN
   *
   * La cadena original viene descrita en el fichero serializado
   */ 
  bool loadSerialized(const string & nombre_fichero);
  
  
  /** @brief Imprime los Nmers
   * @todo Debemos de implementar este método de forma que nos garantizemos que se imprimen todos los Nmers.
   */ 
   void list_Nmer() const;
   
   
  /** @brief Máxima longitud de los Nmers almacenados
   */ 
   unsigned int length()const;
   
     
  /** @brief Número de Nmers almacenados
   */ 
   size_type size() const;

  /** @brief Operador de asignación de Nmer 
   * @param a Nmer que se va a asignar
   */
   Nmer & operator=(const Nmer & a);

  /** @brief Devuelve un Nmer con todas las subcadenas asociadas a un prefijo
   * @param adn prefijo
   * @returns Nmer con todas las subcadenas asociadas al prefijo, con el prefijo incluido
   */ 
   Nmer prefix(string adn);

  /** @brief Lectura de fichero para cargar un Nmer
   * @param fichero nombre del fichero 
   * @param l longitud máxima de la cadena
   * @returns true si se ha cargado con éxito, false en caso contrario
   */
   bool loadNmer(const string & fichero, unsigned int l);

  /** @brief Construir un Nmer a partir de una cadena de ADN
   * @param l longitud de la cadena
   * @param adn cadena de ADN
   */
   void sequenceADN(unsigned int l, const string & adn);

   /** @brief Recorre en preorden un Nmer
   * @param n un nodo del árbol del Nmer
   */
   void recorrido_preorden(ktree<pair<char,int>,4>::const_node n) const;

   /** @brief Buscar subcadenas que aparecen menos de threshold veces en el Nmer 
   * @param threshold numero de apariciones
   * @returns set con las subcadenas que aparecen menos de threshold veces ordenadas en orden creciente según frecuencia
   */
   set<pair<string,int>, OrdenCre> rareNmer(int threshold);

   /** @brief Función auxiliar para rareNmer 
   * @param n nodo a partir del cual empezamos a recorrer el Nmer
   * @param salida set con las subcadenas almacenadas
   * @param string subcadena de un Nmer
   * @param threshold número de apariciones
   */
   void auxRareNmer(ktree<pair<char,int>,4>::const_node n, set<pair<string,int>, OrdenCre> &salida, string & cadena, int threshold);

   /** @brief Función auxiliar para auxRareNmer 
   * @param n nodo actual
   * @param salida set con las subcadenas almacenadas
   * @param string subcadena de un Nmer
   * @param frecuencia frecuencia del Nmer
   * @param threshold número de apariciones
   */
   void almacenar_cadena_RareNmer(ktree<pair<char,int>,4>::const_node n, set<pair<string,int>, OrdenCre> &salida, string & cadena, int frecuencia, int threshold);

   /** @brief Listar todos los Nmer
   * @param n nodo a partir del cual se comienza a listar
   * @param cadena subcadena del Nmer
   */
   void listar(ktree<pair<char,int>,4>::const_node n, string & cadena) const;

   /** @brief Función auxiliar de listar que construye la subcadena de Nmer de un nodo 
   * @param n nodo actual
   * @param frecuencia frecuencia del Nmer
   */
   void construir(ktree<pair<char,int>,4>::const_node n, string & cadena, int frecuencia) const;

   /** @brief Comprobar si un nodo es hoja 
   * @param n nodo
   * @returns true si es hoja, false en caso contrario
   */
   bool es_hoja(ktree<pair<char,int>,4>::const_node n);

   /** @brief Buscar subcadenas que aparecen menos de threshold veces en el Nmer 
   * @param threshold numero de apariciones
   * @returns set con las subcadenas que aparecen más de threshold veces ordenadas en orden decreciente según frecuencia
   */
   set<pair<string,int>, OrdenDecre> commonNmer(int threshold);

   /** @brief Función auxiliar para commonNmer 
   * @param n nodo a partir del cual empezamos a recorrer el Nmer
   * @param salida set con las subcadenas almacenadas
   * @param string subcadena de un Nmer
   * @param threshold número de apariciones
   */
   void auxCommonNmer(ktree<pair<char,int>,4>::node n, set<pair<string,int>, OrdenDecre> &salida, string & cadena, int threshold);

   /** @brief Función auxiliar para auxCommonNmer 
   * @param n nodo actual
   * @param salida set con las subcadenas almacenadas
   * @param string subcadena de un Nmer
   * @param frecuencia frecuencia del Nmer
   * @param threshold número de apariciones
   */
   void almacenar_cadena_CommonNmer(ktree<pair<char,int>,4>::const_node n, set<pair<string,int>, OrdenDecre> &salida, string & cadena, int frecuencia, int threshold);

   /** @brief Función auxiliar para auxCommonNmer 
   * @param n nodo actual
   * @param threshold número de apariciones
   * @returns true si el nodo actual es el de mayor threshold con respecto a su subárbol, false en caso contrario
   */
   bool hijo_con_mayor_threshold(ktree<pair<char,int>,4>::const_node n, int threshold);

   /** @brief Buscar Nmers con una longitud exacta 
   * @param l longitud
   * @returns set de Nmers almacenados en orden creciente
   */
   set<pair<string,int>, OrdenCre> level(int l);

   /** @brief Función auxiliar para almacenar la cadena de un nivel
   * @param l longitud de la cadena
   * @param n nodo actual
   * @param salida conjunto de subcadenas almacenado
   */
   void almacenar_level(int l, ktree<pair<char,int>,4>::const_node n, set<pair<string,int>, OrdenCre> & salida);

   /** @brief Averiguar profundidad de un nodo 
   * @param n nodo
   * @param profundidad_nodo profundidad almacenada hasta el momento
   * @param cadena subcadena almacenada del Nmer
   */
   void profundidad(ktree<pair<char,int>,4>::const_node n, int & profundidad_nodo, string & cadena);

   /** @brief Distancia entre dos Nmer
   * @param nm Nmer
   * @returns distancia entre los Nmer
   */
   float distance(Nmer & nm);

   /** @brief Función auxiliar para distance
    * @returns set con el Nmer almacenado en orden decreciente según frecuencia
   */
   set<pair<string,int>, OrdenDecre> ordenar_nmer();

   /** @brief Función auxiliar para ordenar_nmer
   * @param n nodo a partir del cual se va a ordenar
   * @param salida conjunto almacenado de Nmers
   * @param cadena subcadena almacenada
   */
   void aux_ordenar_nmer(ktree<pair<char,int>,4>::const_node n, set<pair<string,int>, OrdenDecre> &salida, string & cadena);

   /** @brief Función auxiliar para aux_ordenar_nmer
   * @param n nodo actual
   * @param salida conjunto almacenado de Nmers
   * @param cadena subcadena almacenada
   * @param frecuencia frecuencia del Nmer
   */
   void almacenar_cadena_ordenada(ktree<pair<char,int>,4>::const_node n, set<pair<string,int>, OrdenDecre> &salida, string & cadena, int frecuencia);

   /** @brief Calcular el máximo
   * @param a primer número
   * @param b segundo número
   * @returns el máximo de a y b
   */
   float maximo(const unsigned int & a, const unsigned int & b);

   /** @brief Calcular la suma de dos Nmer 
   * @param reference
   * @returns Nmer con la suma de los dos
   */
   Nmer Union(const Nmer & reference);

   /** @brief Función auxiliar para Union 
   * @param n_this nodo del Nmer contenido en *this
   * @param n_reference nodo del Nmer contenido en el Nmer reference
   * @param arbol árbol del Nmer reference
   * @param nodo_padre nodo padre de n_this
   */
   void unir_nodos(ktree<pair<char,int>,4>::node n_this, ktree<pair<char,int>,4>::node n_reference, ktree<pair<char,int>,4> & arbol, ktree<pair<char,int>,4>::node nodo_padre);

   /** @brief Comprobar si una cadena está representada en el árbol 
   * @param adn cadena
   * @returns true si la cadena está representada en el árbol, falso en caso contrario
   */
   bool containsString(const string adn) const;

   /** @brief Comprobar si un Nmer está contenido en otro 
   * @param reference Nmer
   * @returns true si cada nodo de *this está también en reference, false en caso contrario
   */
   bool included(const Nmer & reference) const;

   /** @brief Función auxiliar para included 
   * @param n_this nodo del árbol contenido en *this
   * @param n_reference nodo del árbol contenido en reference
   * @returns true si n_this está contenido en n_reference
   */
   bool comprobar_nodos(ktree<pair<char,int>,4>::const_node n_this, ktree<pair<char,int>,4>::const_node n_reference) const;

private:
  ktree<pair<char,int>,4> el_Nmer; // subsecuencias 
  unsigned int max_long; // Mayor longitud de la cadena representada, esto es, el nivel máximo del árbol
 
 /** @brief Función auxiliar sequenceADN
   * @param cadena subcadena de adn
   */
  void insertar_cadena(const string & cadena);

  /** @brief Functor para convertir un string en un pair<char,int>
   * se utiliza en loadSerialized
   */
  class String2Base {
   public:
    pair<char,int> operator()( const string & cad) {
	    pair<char,int> salida;
	    salida.first = cad[0];
	    salida.second = std::stoi(cad.substr(1)); 
	    return salida;
    }
  };

   /** @brief Functor para convertir un pair<char,int> en un string 
    * Necesario para serializar un Nmer.
   */
  class Base2String {
   public:
     string operator()( const pair<char,int> & x) {
       string salida = string(1,x.first) + " " +std::to_string(x.second); 
       return salida;
     }
  };
};

#endif
