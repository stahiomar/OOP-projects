#include <iostream>
#include <stdlib.h>
using namespace std;

class Client{
    protected:
    string nom, adresse, tel;
    float montant;
    public:
    Client(){
        nom=adresse=tel="null";
        montant=0;
    }
    Client(string n, string ad, string t, float m){
        nom=n;
        adresse=ad;
        tel=t;
        montant=m;
    }
    virtual void facturer(){
        cout<<"walo";
    }
};

class CIndividuel : virtual public Client{
    private:
    string dateNaissance, CIN;
    public:
    CIndividuel(){
        dateNaissance=CIN="null";
    }
    CIndividuel(string n, string ad, string t, float m, string d, string c) : Client(n, ad, t, m){
        dateNaissance=d;
        CIN=c;
    }
    void facturer(){
        cout<<"Montant a payer : "<<montant<<endl;
    }
};

class CEntreprise : virtual public Client{
    private:
    string nomEntreprise;
    int numIdentificationFiscale;
    public:
    CEntreprise(){
        nomEntreprise="null";
        numIdentificationFiscale=0;
    }
    CEntreprise(string n, string ad, string t, float m, string ne, int num) : Client(n, ad, t, m){
        nomEntreprise=ne;
        numIdentificationFiscale=num;
    }
    void facturer(){
        montant+=montant*0.2;
        cout<<"Montant a payer : "<<montant<<endl;
    }
};

class CPremium : public CIndividuel, public CEntreprise{
    private:
    float remiseSpeciale;
    string avantagesExclusifs;
    public:
    CPremium(){
        remiseSpeciale=0;
        avantagesExclusifs="null";
    }
    CPremium(string n, string ad, string t, float m, string d, string c, string ne, int num, float rs, string ae) : 
        Client(n, ad, t, m), CIndividuel(n, ad, t, m, d, c), CEntreprise(n, ad, t, m, ne, num){
        remiseSpeciale=rs;
        avantagesExclusifs=ae;
    }
    void facturer(){
        montant+=remiseSpeciale*0.2;
        cout<<"Montant a payer : "<<montant<<endl;
    }
};
int main(){
    Client *T[5];
    T[0]=new CIndividuel("Imrane","Hay Salam","0602452132",500,"01-05-2001","F4DFD5G");
    T[1]=new CEntreprise("Adullah","Diar","0615653287",450,"ETP",1);
    T[2]=new CEntreprise("Saad","Tabrekt","0698563221",250,"ABC",2);
    T[3]=new CPremium("Hassan","Joulane","0745563215",500,"12-05-1995","D564WX","EDE",3,200,"aaaaa");
    T[4]=new CPremium("Mohammed","Joulane","0612235489",300,"02-05-1998","DF5VZE","FQF",4,250,"bbbbb");
    for(int i=0;i<5;i++)
    T[i]->facturer();
    return 0;
}
