#ifndef ALBUM_H 
#define ALBUM_H 
#include <iostream> 
#include "Livre.h"

class Album : public Livre {
    private:
        std::string illustrations;

    public:
        Album(int monCode, std::string monAuteur, std::string monEditeur, 
              int monISBN, std::string monPublic, Etat monetat, 
              std::string mesillustrations)
            : Livre(monCode, monAuteur, monEditeur, monISBN, monPublic, monetat),
              illustrations(mesillustrations)
        {
            myBT = BT_album;  
        }

        Album(const Album& monAlbum)
            : Livre(monAlbum),
              illustrations(monAlbum.getIllustrations())
        {
            myBT = BT_album;  
        }

        std::string getIllustrations() const {
            return illustrations;
        }

        virtual Booktype getBT() const  {  
            return myBT;
        }

        virtual void Afficher()  {  
            Livre::Afficher();
            std::cout << "Illustrations : " << getIllustrations() << "\n";
        }
};

#endif