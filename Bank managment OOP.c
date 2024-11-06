#include <iostream>
using namespace std;

class CompteBancaire{
    protected:
    string numero;
    double solde;
    public:
    CompteBancaire();
    CompteBancaire(string,double);
    void deposer(double);
    void retirer(double);
    virtual void afficher();
    string getNumero();
    double getSolde();
};

CompteBancaire::CompteBancaire(){
    numero="null";
    solde=0;
}

CompteBancaire::CompteBancaire(string num,double s){
    numero=num;
    solde=s;
}

void CompteBancaire::deposer(double montant){
    solde+=montant;
}

void CompteBancaire::retirer(double montant){
    if(solde>=montant)
    solde-=montant;
    else
    cout<<"votre solde est insuffisant";
}

void CompteBancaire::afficher(){
    cout<<"numero : "<<numero<<endl;
    cout<<"solde : "<<solde<<endl;
}

string CompteBancaire::getNumero(){return numero;}

double CompteBancaire::getSolde(){return solde;}

class CompteCourant:virtual public CompteBancaire{
    protected:
    double decouvertAutorise;
    public:
    CompteCourant();
    CompteCourant(double,string,double);
    void retirer(double);
    void afficher();
};

CompteCourant::CompteCourant():CompteBancaire(){
    decouvertAutorise=0;
}

CompteCourant::CompteCourant(double dec,string num,double s):CompteBancaire(num,s){
    decouvertAutorise=dec;
}

void CompteCourant::retirer(double montant){
    if(solde+decouvertAutorise>=montant)
    solde-=montant;
    else
    cout<<"votre decouvert autorise est depasse"<<endl;
}

void CompteCourant::afficher(){
    CompteBancaire::afficher();
    cout<<"decouvert autorise : "<<decouvertAutorise<<endl;
}

class CompteEpargne:virtual public CompteBancaire{
    protected:
    double tauxInteret;
    public:
    CompteEpargne();
    CompteEpargne(double,string,double);
    void deposer(double);
    void afficher();
};

CompteEpargne::CompteEpargne():CompteBancaire(){
    tauxInteret=0;
}

CompteEpargne::CompteEpargne(double taux,string num,double s):CompteBancaire(num,s){
    tauxInteret=taux;
}

void CompteEpargne::deposer(double montant){
    double interet=montant*tauxInteret/100;
    solde+=montant+interet;
}

void CompteEpargne::afficher(){
    CompteBancaire::afficher();
    cout<<"taux d'interet : "<<tauxInteret<<"%"<<endl;
}

class CompteCourantEpargne:public CompteCourant,public CompteEpargne{
    public:
    CompteCourantEpargne();
    CompteCourantEpargne(string,double,double,double);
    void deposer(double);
    void retirer(double);
    void afficher();
};

CompteCourantEpargne::CompteCourantEpargne()
    :CompteBancaire(),CompteCourant(),CompteEpargne(){}
    
CompteCourantEpargne::CompteCourantEpargne(string num,double s,double taux,double dec)
    :CompteBancaire(num,s),CompteCourant(dec,num,s),CompteEpargne(taux,num,s){}

void CompteCourantEpargne::deposer(double montant) {
    CompteEpargne::deposer(montant);
}

void CompteCourantEpargne::retirer(double montant) {
    CompteCourant::retirer(montant);
}

void CompteCourantEpargne::afficher() {
    cout << "Numero : " << numero << endl;
    cout << "Solde : " << solde << endl;
    cout << "Taux d'interet : " << tauxInteret << "%" << endl;
    cout << "Decouvert autorise : " << decouvertAutorise << endl;
}

class Banque{
    CompteBancaire **comptesBancaires;
    int nbComptes,max;
    public:
    Banque();
    void ajouterCompte(CompteBancaire*);
    void supprimerCompte(string numero);
    void afficherComptes();
    double getTotalSoldes();
};

Banque::Banque(){
    nbComptes=0;
    max=10;
    comptesBancaires=(CompteBancaire**)malloc(max*sizeof(CompteBancaire*));
}

void Banque::ajouterCompte(CompteBancaire* compte){
    if(nbComptes==max) {
        max+=1;
        comptesBancaires=(CompteBancaire**)realloc(comptesBancaires,max*sizeof(CompteBancaire*));
    }
        comptesBancaires[nbComptes]=compte;
        nbComptes++;
}

void Banque::supprimerCompte(string numero){
    for(int i=0; i<nbComptes;i++){
        if(comptesBancaires[i]->getNumero()==numero) {
            for(int j=i;j<nbComptes-1;j++){
                comptesBancaires[j]=comptesBancaires[j+1];
            }
            delete comptesBancaires[nbComptes];
            nbComptes--;
            break;
        }
    }
}

void Banque::afficherComptes() {
    for(int i=0;i<nbComptes;i++) {
        comptesBancaires[i]->afficher();
    }
}

double Banque::getTotalSoldes() {
    double total = 0;
    for(int i = 0; i < nbComptes; i++) {
        total += comptesBancaires[i]->getSolde();
    }
    return total;
}
int main(){
    Banque b;
    CompteEpargne c1;
    c1.deposer(10);
    CompteCourantEpargne c("1",200,10,12);
    b.ajouterCompte(&c);
    b.ajouterCompte(&c1);
    b.supprimerCompte("1");
    b.afficherComptes();
    return 0;
}


