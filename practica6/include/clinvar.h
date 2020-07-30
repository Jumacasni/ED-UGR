#ifndef __CLINVAR_H
#define __CLINVAR_H

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <list>
#include <unordered_map>

#include "mutacion.h"

using namespace std;

class ProbMutaciones{
		public:
	    bool operator()(const mutacion & a, const mutacion & b) {
	        return ((1-a.getCaf().at(0)) >= (1-b.getCaf().at(0)));
	    }
};

class clinvar{
public:

	class iterator;
	class gen_iterator;

	typedef string IDgen;
	typedef string IDmut;
	typedef string IDenf;
	typedef map<IDenf, enfermedad>::iterator enfermedad_iterator;
	
	void load (string nombreDB);
	void insert (const mutacion & x);
	bool erase (IDmut ID);

	void size ();

	iterator find_Mut (IDmut ID);

	enfermedad_iterator find_Enf(IDenf ID);

	vector<enfermedad> getEnfermedades(mutacion & mut);

	list<IDenf> getEnfermedades(const string & keyword);

	set<IDmut> getMutacionesEnf (IDenf ID);
	set<IDmut> getMutacionesGen (IDgen ID);
	set<mutacion,ProbMutaciones> topKMutaciones (int k, string keyword);
	
	iterator begin();
	iterator end();

	iterator lower_bound(string cromosoma, unsigned int posicion);
	iterator upper_bound(string cromosoma, unsigned int posicion);

	enfermedad_iterator ebegin();
	enfermedad_iterator eend();

	gen_iterator gbegin();
	gen_iterator gend();
	
	class iterator{
		public:
			iterator();
			iterator(const iterator &  x);
			
			const mutacion & operator*();
			iterator & operator++();
			iterator operator++(int i);
			iterator & operator--();
			iterator operator--(int i);
			bool operator==(const iterator & x) const ;		  
			bool operator!=(const iterator & x) const ;
			iterator & operator=(const iterator & x);	

		private:
			set<mutacion>::iterator it;
			friend class clinvar;
	};

	class gen_iterator{
		public:
			gen_iterator();
			gen_iterator(const gen_iterator &  x);
			
			const mutacion & operator*();
			gen_iterator & operator++();
			gen_iterator operator++(int i);
			gen_iterator & operator--();
			gen_iterator operator--(int i);
			bool operator==(const gen_iterator & x) const;		  
			bool operator!=(const gen_iterator & x) const;
			gen_iterator & operator=(const gen_iterator & x);

		private:
			map<IDgen, list<set<mutacion>::iterator> >::iterator itmap;
			list<set<mutacion>::iterator>::iterator itlist;
			clinvar *ptrclinvar;
			friend class clinvar;
	};

private:

	set<mutacion> mutBD;													// Base de datos que contiene toda la información asociada a una mutación
	unordered_map<IDmut, set<mutacion>::iterator> IDm_map;	// Asocia IDmutacion con mutación
	map<IDgen, list<set<mutacion>::iterator>> gen_map;			// Asocia genes con mutaciones
	map<IDenf, enfermedad> EnfDB;										// Base de datos de enfermedades
	multimap<IDenf,set<mutacion>::iterator> IDenf_map;			// Asocia enfermedad con mutaciones
};

#endif