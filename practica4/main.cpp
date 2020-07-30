#include "mutacion.h"
#include "enfermedad.h"
#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

using namespace std;

class compara{
    public:
    bool operator()(const mutacion & a, const mutacion & b) {
        return a < b;
    }
};

int main(){
    
    mutacion m("1   2303008 rs775433131 C   T   .   .   RS=775433131;RSPOS=2303008;dbSNPBuildID=144;SSR=0;SAO=0;VP=0x050000000a05040002000100;GENEINFO=SKI:6497;WGT=1;VC=SNV;NSM;REF;ASP;VLD;CLNALLE=1;CLNHGVS=NC_000001.11:g.2303008C>T;CLNSRC=.;CLNORIGIN=1;CLNSRCID=.;CLNSIG=0;CLNDSDB=MedGen;CLNDSDBID=CN169374;CLNDBN=not_specified;CLNREVSTAT=single;CLNACC=RCV000198950.1");
    mutacion n("13	32326498	rs81002849	G	A	.	.	RS=81002849;RSPOS=32326498;dbSNPBuildID=132;SSR=0;SAO=1;VP=0x050160200005000002100100;GENEINFO=BRCA2:675;WGT=1;VC=SNV;PM;SLO;ASS;ASP;LSD;CLNALLE=1;CLNHGVS=NC_000013.11:g.32326498G>A;CLNSRC=Breast_Cancer_Information_Core_(BRCA2);CLNORIGIN=1;CLNSRCID=745-1&base_change\x3dG_to_A;CLNSIG=1|5|5;CLNDSDB=MedGen:OMIM:SNOMED_CT|MedGen:OMIM|MedGen:SNOMED_CT;CLNDSDBID=C0346153:114480:254843006|C2675520:612555|C0027672:699346009;CLNDBN=Familial_cancer_of_breast|Breast-ovarian_cancer\x2c_familial_2|Hereditary_cancer-predisposing_syndrome;CLNREVSTAT=no_assertion|single|single;CLNACC=RCV000044588.2|RCV000113730.1|RCV000131857.2");
	 conjunto<mutacion,less<mutacion>> conjuntomutaciones;
    conjuntomutaciones.insert(m);
	conjuntomutaciones.insert(n);
    cout << conjuntomutaciones.size() << endl;
	cout << conjuntomutaciones.count(m) << endl;
}
