/** @file clinvar.cpp
    @brief fichero de implementacion de la clase clinvar
    @author Juan Manuel Castillo Nievas
    @date 24/Diciembre/2016
*/

#include "mutacion.h"
#include "enfermedad.h"
#include "clinvar.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){

    clinvar clin;
    clin.load("datos/clinvar_20160831.vcf");
    clin.size();
    cout << endl;

    mutacion mut("1	55555555	rs666666666	C	T	.	.	RS=786201005;RSPOS=1014143;dbSNPBuildID=144;SSR=0;SAO=1;VP=0x050060000605000002110100;GENEINFO=geninventado;WGT=1;VC=SNV;PM;NSN;REF;ASP;LSD;OM;CLNALLE=1;CLNHGVS=NC_000001.11:g.1014143C>T;CLNSRC=OMIM_Allelic_Variant;CLNORIGIN=1;CLNSRCID=147571.0003;CLNSIG=5;CLNDSDB=MedGen:OMIM;CLNDSDBID=idenf;CLNDBN=enfermedadinventada;CLNREVSTAT=no_criteria;CLNACC=RCV000162196.3");
    clin.insert(mut);
    mutacion mut2("1	66666666	rs5555555555	C	T	.	.	RS=786201005;RSPOS=1014143;dbSNPBuildID=144;SSR=0;SAO=1;VP=0x050060000605000002110100;GENEINFO=geninventado;WGT=1;VC=SNV;PM;NSN;REF;ASP;LSD;OM;CLNALLE=1;CLNHGVS=NC_000001.11:g.1014143C>T;CLNSRC=OMIM_Allelic_Variant;CLNORIGIN=1;CLNSRCID=147571.0003;CLNSIG=5;CLNDSDB=MedGen:OMIM;CLNDSDBID=idenf2;CLNDBN=enfermedadinventada;CLNREVSTAT=no_criteria;CLNACC=RCV000162196.3");
	clin.insert(mut2);
    clin.erase("rs666666666");

    clinvar::iterator fmut = clin.find_Mut("rs666666666");
    if(fmut == clin.end())
        cout << "No se ha encontrado la mutación" << endl;

    cout << endl;
    cout << "Enfermedades asociadas a la mutación " << endl;
    vector<enfermedad> ve = clin.getEnfermedades(mut2);
    for(auto it = ve.begin(); it != ve.end(); ++it)
        cout << *it << endl;
    cout << endl;

    cout << "Lista de IDenf de las enfermedades que contienen la palabra 'cancer':" << endl;
    list<clinvar::IDenf> lista = clin.getEnfermedades("cancer");
    for(auto it = lista.begin(); it != lista.end(); ++it)
        cout << *it << endl;
    cout << endl;
    
    cout << "Conjunto de identificadores de mutaciones que contienen la enfermedad con ID CN029768:" << endl;
    set<clinvar::IDmut> ids = clin.getMutacionesEnf("CN029768");
    for(auto it = ids.begin(); it != ids.end(); ++it)
        cout << *it << endl;
    cout << endl;

    cout << "Conjunto de identificadores de mutaciones que contienen el gen APC:324:" << endl;
    set<clinvar::IDmut> idg = clin.getMutacionesGen("APC:324");
    for(auto it = idg.begin(); it != idg.end(); ++it)
        cout << *it << endl;
    cout << endl;

    cout << "Conjunto de las mutaciones más probables que contienen enfermedades con 'cancer' en su nombre:" << endl;
    set<mutacion,ProbMutaciones> aux = clin.topKMutaciones(10, "cancer");
    for(auto it = aux.begin(); it != aux.end(); ++it){
		cout << *it << endl;
    }

    return 0;
}
