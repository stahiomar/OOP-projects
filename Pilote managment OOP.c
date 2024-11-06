#include <iostream>
#include<stdlib.h>
using namespace std;

class pilote{
    int code;
    string nom;
    public:
    static int nbrP;
    pilote():code(++nbrP),nom("null"){}
    pilote(string n):code(++nbrP),nom(n){}
    string getNom(){return nom;}
    int getCode(){return code;}
    static int getNbPilotes(){return nbrP;}
    void setNom(string n){
        nom=n;
    }
    void afficher(){
        cout<<"le code : "<<code<<endl<<"le nom : "<<nom<<endl;
    }
};

int pilote::nbrP=0;

class vehicule{
    protected:
    int num,carburant;
    bool estDemarre;
    pilote p;
    float vitesse;
    public:
    static int nbrV;
    vehicule():p(){
        num=++nbrV;
    }
    void demarre(){
        if(carburant>0){
            cout<<"Demarre!!"<<endl;
            estDemarre=true;
        }
        else
            cout<<"on ne peut pas demarre"<<endl;
    }
    void accelerer(){
        if(estDemarre){
            vitesse++;
            carburant--;
            if(carburant<=0){
                estDemarre=false;
                cout<<"<<carburant indisponible>>"<<endl;
            }
        }
    }
    void afficher(){
        cout<<"le numero : "<<num<<endl<<"le carburant : "<<carburant<<endl;
        cout<<"la vitesse : "<<vitesse<<endl;
        p.afficher();
    }
    void addCarburant(int c){
        carburant+=c;
    }
    int getNum(){return num;}
    int getCarburant(){return carburant;}
};

int vehicule::nbrV=0;

class voiture:public vehicule{
    float capaciteReservoir=80;
    int nb_roues=4;
    public:
    voiture():vehicule(){
        carburant=0;
    }
    void faireLePlein(){
        carburant=capaciteReservoir;
    }
    void addCarburant(int c){
        float MAX=capaciteReservoir-carburant;
        if(c<=capaciteReservoir){
            carburant+=MAX;
        }
        else{
            carburant+=c;
            cout<<"le plein a ete fait mais la quantite "<<c-MAX<<"a debordee"<<endl;
        }
    }
    void afficher(){
        vehicule::afficher();
        cout<<"nombre de roues : "<<nb_roues<<endl<<"capacite de reservoir : "<<capaciteReservoir<<endl;
    }
    int getNbroues(){return nb_roues;}
};

class moto:public vehicule{
    float capaciteReservoir=30;
    int nb_roues=2;
    public:
    moto():vehicule(){
        carburant=0;
    }
    void faireLePlein(){
        carburant=capaciteReservoir;
    }
    void addCarburant(int c){
        float MAX=capaciteReservoir-carburant;
        if(c<=capaciteReservoir){
            carburant+=MAX;
        }
        else{
            carburant+=c;
            cout<<"le plein a ete fait mais la quantite "<<c-MAX<<"a debordee"<<endl;
        }
    }
    void afficher(){
        vehicule::afficher();
        cout<<"nombre de roues : "<<nb_roues<<endl<<"capacite de reservoir : "<<capaciteReservoir<<endl;
    }
    int getNbroues(){return nb_roues;}
};

class course{
    vehicule **T;
    int N,max;
    public:
    course(){
        N=0;
        max=10;
        T=(vehicule**)malloc(max*sizeof(vehicule*));
    }
    
    void addVehicule(vehicule* v){
        if(N==max) {
            max+=1;
            T=(vehicule**)realloc(T,max*sizeof(vehicule*));
        }
        T[N]=v;
        N++;
    }
    void afficherTotaleCarburant(){
        int total=0;
        for(int i=0;i<N;i++){
            T[i]->afficher();
            total+=T[i]->getCarburant();
        }
        cout<<"\t\ttotal carburant : "<<total<<endl;
    }
    vehicule* getVehicule(int num){
        for(int i=0;i<N;i++){
            if(T[i]->getNum() == num){
                return T[i];
            }
        }
        return NULL;
    }
    void demarreTous(){
        for(int i=0;i<N;i++){
            T[i]->demarre();
        }
    }
    void demarreVoitures(){
        for(int i=0;i<N;i++){
            voiture *v=(voiture*)T[i];
            if(v->getNbroues()==4)
            v->demarre();
            else
            cout<<"###########"<<endl;
        }
    }
};
int main(){
    course c;
    pilote p1,p2;
    moto m;
    m.addCarburant(10);
    voiture v; 
    c.addVehicule(&m);
    c.addVehicule(&v);
    v.addCarburant(10);
    if(c.getVehicule(2)!=NULL && m.getNbroues()==2){
        m.accelerer();
    }
    c.demarreVoitures();
    return 0;
}
