
#ifndef BANDEDESSINEE_H
#define BANDEDESSINEE_H
#include "Livre.h"  
#include <iostream>

class BandeDessinee : public Livre {
    private:
        std::string Dessinateur;

    public:
        BandeDessinee(int monCode, std::string monAuteur, std::string monEditeur, 
                      int monISBN, std::string monPublic, Etat monetat, 
                      std::string mondessinateur) 
            : Livre(monCode, monAuteur, monEditeur, monISBN, monPublic, monetat),
              Dessinateur(mondessinateur)
        {
            this->myBT = BT_bandeDessinee;
        }

        BandeDessinee(const BandeDessinee& maBD) 
            : Livre(maBD), 
              Dessinateur(maBD.GetDessinateur())
        {
            this->myBT = BT_bandeDessinee;
        }

        std::string GetDessinateur() const {
            return Dessinateur;
        }

        virtual Booktype getBT() const  {
            return myBT;
        }

        virtual void Afficher()  {
            Livre::Afficher();
            std::cout << "Dessinateur : " << GetDessinateur() << "\n";
        }
};

#endif
