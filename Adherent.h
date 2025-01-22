#ifndef ADHERENT_H
#define ADHERENT_H
#include <iostream>
#include "Livre.h"
#include "Bibliotheque.h"
#include "vecteur.h"  

class Adherent {
    private :
        std::string nom;
        std::string prenom;
        int NumeroAdherent;
        Bibliotheque* maBiblio;
        Livre* pLivre; 
        
    public : 

        Adherent(std::string nom, std::string prenom, int numeroAdherent, Bibliotheque* maBiblio)
        : nom(nom), prenom(prenom), NumeroAdherent(numeroAdherent), maBiblio(maBiblio) {
            
            pLivre = nullptr;
        }

        Adherent(const Adherent& other) {
            this->nom = other.getNom();
            this->prenom = other.getPrenom();
            this->NumeroAdherent = other.getNumeroAdherent();
            this->maBiblio = other.getMaBiblio();
            this->pLivre = other.getLivre();
        }

        // Getters
    std::string getNom() const {
        return nom;
    }

    std::string getPrenom() const {
        return prenom;
    }

    int getNumeroAdherent() const {
        return NumeroAdherent;
    }

    Bibliotheque* getMaBiblio() const {
        return maBiblio;
    }

    Livre* getLivre() const {
        return pLivre;
    }

    

    // Setters
    void setNom(const std::string& nouveauNom) {
        nom = nouveauNom;
    }

    void setPrenom(const std::string& nouveauPrenom) {
        prenom = nouveauPrenom;
    }

    void setNumeroAdherent(int nouveauNumero) {
        if (nouveauNumero > 0) {
            NumeroAdherent = nouveauNumero;
        } else {
            std::cout << "Numéro d'adhérent invalide.\n";
        }
    }

    void setMaBiblio(Bibliotheque* nouvelleBiblio) {
        maBiblio = nouvelleBiblio;
    }

    void setLivre(Livre* pLivre) {
        this->pLivre = pLivre;
    }

    int getNbEmprunts() {
        if (this->getLivre() == nullptr){
            return 0;
        }
        int n = 0;
        Livre* monPointeur = this->getLivre();
        while (monPointeur != nullptr) {
            n+=1;
            if (n > this->getMaBiblio()->getMax()) {
                break;
            }
            monPointeur = monPointeur->getProchain();
        }
        return n;
    }


    void afficher() const {
        std::cout << "Nom: " << nom << "\n";
        std::cout << "Prénom: " << prenom << "\n";
        std::cout << "Numéro d'adhérent: " << NumeroAdherent << "\n";
        std::cout << "Bibliothèque: " << maBiblio->getNom() << "\n"; // Affiche le nom de la bibliothèque associée

        std::cout << "Livres empruntés:\n";
        if (this->getLivre() == nullptr) {
            std::cout << "Aucun livre emprunté.\n";
        } else {
            int n = 0;
            Livre* monPointeur = this->getLivre(); // Premier livre
            while (monPointeur != nullptr && n < this->getMaBiblio()->getMax()) {
                n++;
                if (monPointeur != nullptr) {
                    monPointeur->Afficher();
                    monPointeur = monPointeur->getProchain();
                } else {
                    std::cout << "Prochain livre est nullptr\n";
                }
                
            }
            if (monPointeur == nullptr) {
                std::cout << "bien sorti\n";
            }
        }
    }

    // prendre en compte que une bibliotheque peut avoir plusieurs exemplaires d'un livre
    void Emprunter(Livre* monLivre) {
        try {
            if (monLivre == nullptr) {
                // pointeur nul
                throw std::runtime_error("Livre = nullptr");
            }
            
            else if (this->getNbEmprunts() >= this->getMaBiblio()->getMax()) {
                // trop de livres empruntes
                throw std::runtime_error("TROP DE LIVRES DEJA EMPRUNTES");
            } 
            else if (monLivre->EstLibre() == true && monLivre->getEstPreteAutreBiblio() == false && monLivre->getProprio() == this->getMaBiblio()) {
                // ici le livre original est libre
                // en plus il est prete et prete chez nous
                // ou alors pas prete et on est les proprietaires
                
                monLivre->setProchain(this->getLivre());
                this->setLivre(monLivre);
                // monLivre possede desormais un pointeur vers l ancien livre
                // monLivre devient le premier livre en tete de file des emprunt                        this->setLivre(monLivre);
                monLivre->SetEtat(Emprunte); // on oublie pas : desormais monLivre est emprunte
            }
            
            else if (this->AEmprunteCopie(monLivre) || this->AEmprunte(monLivre)) {
                // si ce livre est deja emprunte par cet adherent
                throw std::runtime_error("L'adhérent a déjà emprunté ce livre ou une copie");
            } else if (this->getMaBiblio()->ContientExemplaire(monLivre) == false) {
                // si pas ce livre dans la biblio
                throw std::runtime_error("Pas d'exemplaires de ce livre dans la bibliothèque");
            }
            else if (monLivre->EstLibre() == false && maBiblio->AutreExemplaireLibre(monLivre) == nullptr) {
                // si le livre est deja emprunte et ma bibliotheque n a pas d autres copie
                throw std::runtime_error("Erreur : livre déjà emprunté et pas de même exemplaire disponible");
            }
            
            else if (monLivre->EstLibre() == false && maBiblio->AutreExemplaireLibre(monLivre) != nullptr) {

                // CAS INTERESSANT
                // si le livre demande precisement est emprunte mais la biblio a une copie
                Livre* autreexemplaire = maBiblio->AutreExemplaireLibre(monLivre);
                if ((autreexemplaire->getEstPreteAutreBiblio() == false && autreexemplaire->getProprio() == this->getMaBiblio()) ||
                    (autreexemplaire->getEstPreteAutreBiblio() == true && autreexemplaire->getEmprunteuse() == this->getMaBiblio())) {
                        // la copie  est anous ou n est pas prete
                        // ou alors il est prete et il est prete a nous

                        // alors on met un pointeur vers le dernier livre emprunte
                        // puis on definit monLivre comme celui qui sera en tete de liste
                        std::cout<<"le livre exact est emprunte neanmoins la biblio possede une copie de ce live \n";
                        autreexemplaire->setProchain(this->getLivre());
                        this->setLivre(autreexemplaire);
                        // finalenent le livre en question autreexe;plaire est defini comme emprunte
                        autreexemplaire->SetEtat(Emprunte);
                    
                    // maBiblio->AutreExemplaireLibre(autreexemplaire)->SetEtat(Emprunte);
                    std::cout << "Le livre exact demandé n'était pas dispo mais l'adhérent a pu emprunter un autre exemplaire \n";
                } else {
                    throw std::runtime_error("Erreur : livre trouvé mais deja prete et la biblio ne possede pas d atres exemplaires \n");
                }
            }
            else if ((monLivre->getEstPreteAutreBiblio() == true && monLivre->getEmprunteuse() == this->getMaBiblio()) ||
                     (monLivre->getEstPreteAutreBiblio() == false && monLivre->getProprio() == this->getMaBiblio())) {
                        // ici le livre original est libre
                        // en plus il est prete et prete chez nous
                        // ou alors pas prete et on est les proprietaires

                        monLivre->setProchain(this->getLivre());
                        // monLivre possede desormais un pointeur vers l ancien livre
                        // monLivre devient le premier livre en tete de file des emprunts
                        this->setLivre(monLivre);
                        monLivre->SetEtat(Emprunte); // on oublie pas : desormais monLivre est emprunte
            }
            else {
                throw std::runtime_error("Erreur : livre qui nous appartient mais déjà prêté ailleurs");
            }
        }
        catch (const std::exception& e) {
            std::cout << "Exception Capturée: " << e.what() << "\n";
        }
    }


    void EmprunterCode(int monCode) {

    }

    // Vérifier si l'adhérent a emprunté ce livre
    bool AEmprunte(Livre* monLivre) {
        try {
            if (monLivre == nullptr) {
                throw std::runtime_error("Livre = nullptr");
            }
            if (this->getLivre() == nullptr) {
                return false;
            }
            int n = 0;
            Livre* monPointeur = this->getLivre();
            while (monPointeur != nullptr) {
                if (monPointeur == monLivre){
                    // si c est les memes objets ie mm adresses memoires
                    return true;
                }
                monPointeur = monPointeur->getProchain();
                n+=1;
                if (n> this->getMaBiblio()->getMax()) {
                    break;
                }
            }
            return false;
        }
        catch (const std::exception& e) {
            std::cout << "Exception Capturée: " << e.what() << "\n";
            return false;
        }
    }

    bool AEmprunteCopie(Livre* monLivre) {
        try {
            if (monLivre == nullptr) {
                throw std::runtime_error("Livre = nullptr");
            }
            if (this->getLivre() == nullptr) {
                return false;
            }
            if (this->AEmprunte(monLivre) == true) {
                throw std::runtime_error("livre originel deja emprunte par l utilisateur\n");
            }
        
            int n = 0;
            Livre* monPointeur = this->getLivre();
            while (monPointeur != nullptr) {
                // comparaison avec surcharge d operateurs
                if (*monPointeur == *monLivre){
                    return true;
                }
                monPointeur = monPointeur->getProchain();
                n+=1;
                if (n> this->getMaBiblio()->getMax()) {
                    break;
                }
            }
            return false;
        }
        catch (const std::exception& e) {
            std::cout << "Exception Capturée: " << e.what() << "\n";
            return false;
        }
    }

    Livre* getCopie(Livre* monLivre) {
        try {
            if (monLivre == nullptr) {
                throw std::runtime_error("Livre = nullptr");
            }
            if (this->AEmprunte(monLivre) == true) {
                throw std::runtime_error(" pas besoin d une copie l adherent a vraiment emprunte ce livre precisement \n");
            }
            if (this->AEmprunteCopie(monLivre) == false) {
                throw std::runtime_error(" Erreur l adherent n a pas emprunte de copie de ce livre \n");
            }
            int n = 0;
            Livre* monPointeur = this->getLivre();
            while (monPointeur != nullptr) {
                // comparaison avec surcharge d operateurs
                if (*monPointeur == *monLivre){
                    return monPointeur;
                }
                monPointeur = monPointeur->getProchain();
                n+=1;
                if (n> this->getMaBiblio()->getMax()) {
                    break;
                }
            }
            return nullptr;
        }
        catch (const std::exception& e) {
            std::cout << "Exception Capturée: " << e.what() << "\n";
            return nullptr;
        }
    }

    void SupprimerLivre(Livre* pmonlivre) {
        try {
            
            if (pmonlivre == nullptr) { throw std::runtime_error("Pointeur nul"); }
            if (this->AEmprunte(pmonlivre) == false && this->AEmprunteCopie(pmonlivre) == true) { 
                std::cout<< " l adherent n a pas exactement emprunte ce livre mais une copie, on s occupe de rendre la copie \n" ;
                SupprimerLivre(this->getCopie(pmonlivre));
                return; }
                
            if (this->AEmprunte(pmonlivre) == false) { throw std::runtime_error("Livre non présent dans les emprunts"); }
            // sinon livre existant et bien emprunte 
            // on doit faire une boucle for dans le liste chainee pour recuperer le livre d avant
            int n = 0;
            Livre* memoire = nullptr;
            Livre* monPointeur = this->getLivre();
            while (monPointeur != nullptr) {
                // comparaison des adresses memoires
                if (monPointeur == pmonlivre){
                    // dans ce cas on a trouve le bon livre
                    if (memoire == nullptr) {
                        // alors le livre a supprimer etait le premier
                        // on supprime le pointeur vers le prochain pour ce ivre et on dit que il est libre
                        // plus on change le premier livre en tete de file
                        this->setLivre(pmonlivre->getProchain());
                        pmonlivre->SetEtat(Libre);
                        pmonlivre->setProchain(nullptr);
                        
                    } else {
                        // alors ce n etait pas le premier donc on utilise le pointeur memoire
                        // le pointeur du precedent passe a celui d encore apres
                        memoire->setProchain(pmonlivre->getProchain());

                        // puis on libre de livre pmonlivre
                        pmonlivre->SetEtat(Libre);
                        pmonlivre->setProchain(nullptr);

                    }

                }
                memoire = monPointeur; // on garde en memoire l ancien 
                monPointeur = monPointeur->getProchain(); // on passe au prochain
                n+=1;
                if (n> this->getMaBiblio()->getMax()) {
                    break;
                }
            }
            
        }
        catch (const std::exception& e) {
            std::cout << "Exception Capturée: " << e.what() << "\n";
        }
    }

    void Rendre(Livre* monLivre) {
        try {
            if (monLivre == nullptr) {
                throw std::runtime_error("Livre = nullptr");
            }
            if (this->AEmprunte(monLivre) == false && this->AEmprunteCopie(monLivre) == true) {
                std::cout<< "l adherent n a pas exactement emprunte ce livre mais une copie, on s occupe de rendre la copie \n" ;
                this->getCopie(monLivre)->SetEtat(Libre);
                SupprimerLivre(this->getCopie((monLivre)));
            }
            if (this->AEmprunte(monLivre) == false) {
                throw std::runtime_error("L'utilisateur n'a pas emprunté ce livre");
            } else {
                monLivre->SetEtat(Libre);
                SupprimerLivre(monLivre);
            }
        }
        catch (const std::exception& e) {
            std::cout << "Exception Capturée: " << e.what() << "\n";
        }
    }

    void EmprunterParISBN(int isbn) {
    try {
        if (maBiblio == nullptr) {
            throw std::runtime_error("Aucune bibliothèque associée à cet adhérent.");
        }

        Livre* livre = maBiblio->RechercherParISBN(isbn);

        if (livre == nullptr) {
            throw std::runtime_error("Livre non trouvé dans la bibliothèque.");
        }

        // Vérifier si l'adhérent peut emprunter ce livre
        if (getNbEmprunts() >= maBiblio->getMax()) {
            throw std::runtime_error("Limite maximale d'emprunts atteinte.");
        }

        if (!livre->EstLibre()) {
            throw std::runtime_error("Le livre est déjà emprunté.");
        }

        // Ajouter le livre à la liste des emprunts
        livre->setProchain(this->getLivre());
        this->setLivre(livre);
        livre->SetEtat(Emprunte);

        std::cout << "Livre avec l'ISBN " << isbn << " emprunté avec succès.\n";
    }
    catch (const std::exception& e) {
        std::cout << "Exception Capturée: " << e.what() << "\n";
    }
}

    
};

#endif
