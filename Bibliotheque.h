
#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <string>
#include <algorithm>
 
#include "Livre.h"
#include "Album.h"
#include "BandeDessinee.h"
#include "Roman.h"
#include "RecueilPoesie.h"  
#include "Piecetheatre.h"
#include "vecteur.h"  

class Bibliotheque {
    private :
        int Code;
        std::string nom;
        std::string adresse;
        // Dico avec des pointeurs comme valeurs à la place des instances elles-mêmes
        // On utilise comme clé le type de livre (Booktype)
        std::map<Booktype, Vecteur<Livre*>> monDictionnaire;  

        
        int NbEmpruntsMax;

    public :

        Bibliotheque (int monCode, std::string monNom, std::string monAdresse, std::map<Booktype, Vecteur<Livre*>> maListe, int monMax) {
            Code = monCode;
            nom = monNom;
            adresse = monAdresse;
            monDictionnaire = maListe;
            NbEmpruntsMax = monMax;

             
        }

        int getMax() {
            return NbEmpruntsMax;
        }

        std::map<Booktype, Vecteur<Livre*>> getDico() {
            return monDictionnaire;
        }

        std::string getNom() {
            return this->nom;
        }

        void AjouterLivre(Livre* pmonLivre) {
            try {
                if (pmonLivre == nullptr) {
                    throw std::runtime_error("livre = pointeur nul");
                }
                monDictionnaire[pmonLivre->getBT()].ajouter(pmonLivre);
                pmonLivre->setProprietaire(this);

            }
            catch (const std::exception& e) {
                std::cout << "Exception Capturee : on ne peut pas ajouter un nullptr\n";
            }
        }

        void AjouterLivreDePret(Livre* pmonLivre) { // Cas où on ajoute un livre qui nous a été prêté
            try {
                if (pmonLivre == nullptr) {
                    throw std::runtime_error("livre = pointeur nul");
                }
                // Ajout du livre au vecteur de prêt et mise à jour de son état
                pmonLivre->setReceveuse(this);
                pmonLivre->setPreteAutreBiblio(true);
                monDictionnaire[pmonLivre->getBT()].ajouter(pmonLivre);
            }
            catch (const std::exception& e) {
                std::cout << "Exception Capturee : on ne peut pas ajouter un nullptr\n";
            }
        }

        // Méthode qui vérifie si la bibliothèque contient cet exemplaire du livre
        bool ContientLivre(Livre* MonLivre) {
            try {
                if (MonLivre == nullptr) {
                    throw std::runtime_error("pointeur nul");
                }
                Vecteur<Livre*>& monvecteur = monDictionnaire[MonLivre->getBT()];
                for (int i = 0; i < monvecteur.getTaille(); i++) {
                    if (monvecteur[i] == MonLivre) {
                        return true;
                    }
                }
                return false;
            }
            catch (const std::exception& e) {
                std::cout << "Exception Capturee: " << e.what() << "\n";
                return false;
            }
        }


        bool ContientExemplaire(Livre* MonLivre) {
            try {
                if (MonLivre == nullptr) {
                    throw std::runtime_error("pointeur nul");
                }
                Vecteur<Livre*>& monvecteur = monDictionnaire[MonLivre->getBT()];
                for (int i = 0; i < monvecteur.getTaille(); i++) {
                    if (*monvecteur[i] == *MonLivre) {
                        return true;
                    }
                }
                return false;
            }
            catch (const std::exception& e) {
                std::cout << "Exception Capturee: " << e.what() << "\n";
                return false;
            }
        }

        // Méthode pour emprunter un autre exemplaire d'un livre
        Livre* AutreExemplaireLibre(Livre* pMonLivre) {
            try {
                if (pMonLivre == nullptr) {
                    throw std::runtime_error("pointeur nul");
                }
                Vecteur<Livre*>& monvecteur = monDictionnaire[pMonLivre->getBT()];
                for (int i = 0; i < monvecteur.getTaille(); i++) {
                    if (*monvecteur[i] == *pMonLivre && monvecteur[i]->EstLibre()) {
                        return monvecteur[i];
                    }
                }
                throw std::runtime_error("Pas de même exemplaire de ce livre ou déjà emprunté");
            }
            catch (const std::exception& e) {
                std::cout << "Exception Capturee: " << e.what() << "\n";
                return nullptr;
            }
        }

       void SupprimerLivre(Livre* pmonlivre) {
            try {
                if (pmonlivre == nullptr) {
                    throw std::runtime_error("pointeur nul");
                }
                if (pmonlivre->getEtat() == Emprunte) {
                    throw std::runtime_error("livre actuellement emprunte on ne peut pas le jeter\n");
                }
                if (pmonlivre->getProprio() != this) {
                    throw std::runtime_error("cette biblio n est pas la proprio du livre impossible pour elle de le jeter \n");
                }
                if (pmonlivre->getEstPreteAutreBiblio() == true) {
                    throw std::runtime_error("livre actuellement prete dans une autre biblio\n");
                }
                Vecteur<Livre*>& monvecteur = monDictionnaire[pmonlivre->getBT()];
                for (int i = 0; i < monvecteur.getTaille(); i++) {
                    if (*monvecteur[i] == *pmonlivre) {
                        monvecteur.supprimerA(i);  
                        break;
                    }
                }
            }
            catch (const std::exception& e) {
                std::cout << "Exception Capturee: " << e.what() << "\n";
            }
            }

        void SupprimerLivre2(Livre* pmonLivre) {
            try {
                if (this->ContientLivre(pmonLivre)) {
                    Vecteur<Livre*>& monvecteur = monDictionnaire[pmonLivre->getBT()];
                    for (int i = 0; i < monvecteur.getTaille(); i++) {
                if (*monvecteur[i] == *pmonLivre) {
                    monvecteur.supprimerA(i);  
                    break;
                }
                }
                }  
                else {
                    throw std::runtime_error("Livre non existant");
                }
                }
                catch (const std::exception& e) {
                std::cout << "Exception Capturee: " << e.what() << "\n";
                }
                }

        void Afficher(Booktype montype = BT_none) {
            if (montype == BT_none) {
                for (const auto& paire : monDictionnaire) {
                    std::cout << "\n";
                    const Booktype& maclef = paire.first;
                    const Vecteur<Livre*>& monvecteur = paire.second;
                    std::cout << "pour le type " << booktypeToString(maclef) << "\n";
                    for (Livre* livre : monvecteur) {
                        livre->Afficher();
                    }
                }
            } else {
                for (int i = 0; i < monDictionnaire[montype].getTaille(); i++) {
                    monDictionnaire[montype][i]->Afficher();
                }
            }
        }

        void Demander(Livre* pMonLivre, Bibliotheque& maBiblio) {
            try {
                if (pMonLivre == nullptr) {
                    throw std::runtime_error("livre passé en argument = pointeur nul");
                }
                if (!(maBiblio.ContientLivre(pMonLivre) && pMonLivre->EstLibre())) {
                    throw std::runtime_error("La Bibliothèque demandée ne possède pas ce livre ou il est déjà emprunté");
                }
                if (pMonLivre->getEstPreteAutreBiblio() == true) {
                    throw std::runtime_error("déjà prêté ailleurs");
                }

                pMonLivre->setPreteAutreBiblio(true);
                pMonLivre->setReceveuse(this);
                this->AjouterLivreDePret(pMonLivre);
            }
            catch (const std::exception& e) {
                std::cout << "Exception Capturee: " << e.what() << "\n";
            }
        }

        void Rendre(Livre* pMonLivre) {
            try {
                if (!this->ContientLivre(pMonLivre)) {
                    throw std::runtime_error("Livre pas dans cette bibliothèque!");
                }
                if (!pMonLivre->getEstPreteAutreBiblio()) {
                    throw std::runtime_error("Livre qui n'a pas été emprunté par une autre biblio!");
                }
                if (pMonLivre->EstLibre() == false) {
                    throw std::runtime_error("Livre actuellement emprunté par un adhérent!");
                } else {
                    pMonLivre->setPreteAutreBiblio(false); 
                    pMonLivre->setReceveuse(nullptr);
                }
            }
            catch (const std::exception& e) {
                std::cout << "Exception Capturee: " << e.what() << "\n";
            }
        }

        Livre* RechercherParISBN(int isbn) {
            for (const auto& paire : monDictionnaire) {
            const Vecteur<Livre*>& livres = paire.second;
            for (Livre* livre : livres) {
                if (livre && livre->getISBN() == isbn) {
                    return livre;
                    }   
                }
            }
            return nullptr; // Aucun livre trouvé
        }

        int getCompteurLocalInstances() const {
            // Initialise un compteur pour suivre le nombre de livres disponibles
            int compteur = 0;
            // Parcourt chaque paire dans le dictionnaire de la bibliothèque
            for (const auto& paire : monDictionnaire) {
            // Récupère le vecteur de livres 
            const Vecteur<Livre*>& livres = paire.second;
            // Parcourt chaque livre dans le vecteur
            for (const Livre* livre : livres) {
                // Vérifie si le pointeur du livre n'est pas nul et si le livre est libre
                if (livre && livre->EstLibre()) {
                    // Incrémente le compteur si le livre est libre
                    compteur++;
                    }
                }
            }

            // Retourne le nombre total de livres libres dans la bibliothèque
            return compteur;
            }




         ~Bibliotheque() {
        for (auto& pair : monDictionnaire) {
            for (Livre* livre : pair.second) {
                delete livre;
            }
        }
    }

    
};

#endif
