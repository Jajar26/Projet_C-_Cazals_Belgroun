#ifndef ROMAN_H
#define ROMAN_H
#include <iostream>
#include "Livre.h"

class Roman : public Livre {
    private :
        std::string genre;

    public :
        Roman(int monCode, std::string monAuteur, std::string monEditeur, int monISBN, std::string monPublic, Etat monetat, std::string monGenre ) : Livre(monCode, monAuteur, monEditeur, monISBN, monPublic, monetat), genre(monGenre)
            {
                Livre::myBT = BT_rman;
            }

        Roman (const Roman& monLivre) : Livre (monLivre), genre(monLivre.getGenre()) {
            
            this->setBT(BT_rman);

        }

        Booktype getBT(){
            return myBT;
        }
        std::string getGenre() const{
            return genre;
        }

        void Afficher()
            {
            Livre::Afficher();
            std::cout<< "Genre" << getGenre() << "\n";
            
        }
};
#endif