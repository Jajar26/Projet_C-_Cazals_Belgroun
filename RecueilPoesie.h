
#ifndef RECUEILPOESIE_H
#define RECUEILPOESIE_H
#include "Livre.h"

class RecueilPoesie : public Livre {
     private :
        std::string Indicateur;

    public : 

        RecueilPoesie(int monCode, std::string monAuteur, std::string monEditeur, int monISBN, std::string monPublic, Etat monetat, std::string monIndicateur ) : Livre(monCode, monAuteur, monEditeur, monISBN, monPublic, monetat), Indicateur(monIndicateur)
            {
                myBT = BT_recueilPoesie;
            }
        
        RecueilPoesie( const RecueilPoesie& monLIvre) : Livre(monLIvre), Indicateur(monLIvre.getIndicateur()){
            this->setBT(BT_recueilPoesie);
        }

        Booktype getBT() const{
            return myBT;
        }

        std::string getIndicateur() const{
            return Indicateur;
        }

        void Afficher()
            {
            Livre::Afficher();
            std::cout<< "Indicateur" << getIndicateur() << "\n";
            
        }
};
#endif
