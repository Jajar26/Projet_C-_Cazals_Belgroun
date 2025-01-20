#ifndef PIECETHEATRE_H
#define PIECETHEATRE_H
#include <iostream>
#include "Livre.h"

class PieceTheatre : public Livre {
    private :
        int siecle;

    public :

        PieceTheatre(int monCode, std::string monAuteur, std::string monEditeur, int monISBN, std::string monPublic, Etat monetat, int monsiecle ) : Livre(monCode, monAuteur, monEditeur, monISBN, monPublic, monetat), siecle(monsiecle)
            {
                myBT = BT_pieceTheatre;
            }

        PieceTheatre(const PieceTheatre& monLivre): Livre(monLivre), siecle(monLivre.getSiecle()){ 
            this->setBT(BT_pieceTheatre);
         }
        Booktype getBT(){
            return myBT;
        }

        int getSiecle() const{
            return siecle;
        }

        void Afficher()
            {
            Livre::Afficher();
            std::cout<< "Siecle" << getSiecle() << "\n";
            
        }

};

#endif