#include <iostream>
#include <string>
#include <map>

#include "Bibliotheque.h"
#include "Livre.h"
#include "BandeDessinee.h"
#include "PieceTheatre.h"
#include "Roman.h"
#include "RecueilPoesie.h"
#include "Album.h"
#include "Adherent.h"
#include "vecteur.h"

int main() {
    // Création des dictionnaires vides
    std::map<Booktype, Vecteur<Livre*>> dictionnaire1;
    std::map<Booktype, Vecteur<Livre*>> dictionnaire2;
    std::map<Booktype, Vecteur<Livre*>> dictionnaire3;

    // Création des bibliothèques
    Bibliotheque bibliotheque1(1, "Bibliothèque Municipale", "123 Rue de Paris", dictionnaire1, 3);
    Bibliotheque bibliotheque2(2, "Bibliothèque Centrale", "45 Avenue des Champs", dictionnaire2, 5);
    Bibliotheque bibliotheque3(3, "Bibliothèque Universitaire", "678 Rue des Sciences", dictionnaire3, 7);

    // Création des livres
    BandeDessinee* Biblio1_BD1 = new BandeDessinee(101, "Hergé", "Casterman", 123456789, "Tout public", Libre, "Hergé");
    BandeDessinee* Biblio1_BD2 = new BandeDessinee(102, "Franquin", "Dupuis", 234567890, "Adolescents", Libre, "Franquin");
    Roman* Biblio1_Roman1 = new Roman(201, "Victor Hugo", "Gallimard", 112233445, "Tout public", Libre, "Classique");
    Roman* Biblio1_Roman2 = new Roman(202, "George Orwell", "Secker & Warburg", 223344556, "Adolescents", Libre, "Dystopie");

    Livre* Biblio2_BD1 = new BandeDessinee(103, "Goscinny", "Dargaud", 345678901, "Enfants", Libre, "Uderzo");
    Livre* Biblio2_BD2 = new BandeDessinee(104, "Moebius", "Les Humanoïdes", 456789012, "Adultes", Libre, "Moebius");
    Livre* Biblio2_Roman1 = new Roman(203, "Flaubert", "Folio", 334455667, "Tout public", Libre, "Classique");
    Livre* Biblio2_Roman2 = new Roman(204, "J.K. Rowling", "Bloomsbury", 445566778, "Enfants", Emprunte, "Fantastique");

    BandeDessinee* Biblio3_BD1 = new BandeDessinee(105, "Morris", "Dupuis", 567890123, "Tout public", Emprunte, "Morris");
    BandeDessinee* Biblio3_BD2 = new BandeDessinee(106, "Peyo", "Dupuis", 678901234, "Tout public", Libre, "Peyo");
    Roman* Biblio3_Roman1 = new Roman(205, "Albert Camus", "Gallimard", 556677889, "Adultes", Libre, "Existentialisme");
    Roman* Biblio3_Roman2 = new Roman(206, "Hemingway", "Scribner", 667788990, "Adultes", Libre, "Drame");

    // Ajout des livres aux bibliothèques
    bibliotheque1.AjouterLivre(Biblio1_BD1);
    bibliotheque1.AjouterLivre(Biblio1_BD2);
    bibliotheque1.AjouterLivre(Biblio1_Roman1);
    bibliotheque1.AjouterLivre(Biblio1_Roman2);

    bibliotheque2.AjouterLivre(Biblio2_BD1);
    bibliotheque2.AjouterLivre(Biblio2_BD2);
    bibliotheque2.AjouterLivre(Biblio2_Roman1);
    bibliotheque2.AjouterLivre(Biblio2_Roman2);

    bibliotheque3.AjouterLivre(Biblio3_BD1);
    bibliotheque3.AjouterLivre(Biblio3_BD2);
    bibliotheque3.AjouterLivre(Biblio3_Roman1);
    bibliotheque3.AjouterLivre(Biblio3_Roman2);

    // Affichage des compteurs
    std::cout << "Nombres de livres disponibles dans bibliothèque 1 : " << bibliotheque1.getCompteurLocalInstances() << "\n";
    std::cout << "Nombres de livres disponibles dans bibliothèque 2 : " << bibliotheque2.getCompteurLocalInstances() << "\n";
    std::cout << "Nombres de livres disponibles dans bibliothèque 3 : " << bibliotheque3.getCompteurLocalInstances() << "\n";

    // Création des adhérents
    Adherent adherent1("Dupont", "Jean", 1, &bibliotheque1);
    Adherent adherent2("Martin", "Claire", 2, &bibliotheque1);
    Adherent adherent3("Lemoine", "Paul", 3, &bibliotheque2);
    Adherent adherent4("Durand", "Sophie", 4, &bibliotheque2);
    Adherent adherent5("Bertrand", "Pierre", 5, &bibliotheque3);

    // Affichage des livres dans la bibliothèque
    std::cout << "\n** Livres disponibles dans la bibliothèque 1 **\n";
    bibliotheque1.Afficher();

    // Emprunter un livre par ISBN
    std::cout << "\n** Emprunt par ISBN (123456789) par Jean Dupont **\n";
    adherent1.EmprunterParISBN(123456789);

    // Affichage des livres empruntés par Jean
    std::cout << "\n** Livres empruntés par Jean Dupont **\n";
    adherent1.afficher();

    // Tentative d'emprunt d'un livre déjà emprunté par un autre adhérent
    std::cout << "\n** Tentative d'emprunt du même ISBN (123456789) par Claire Martin **\n";
    adherent2.EmprunterParISBN(123456789);

    // Emprunt d'un autre livre disponible
    std::cout << "\n** Emprunt par ISBN (234567890) par Claire Martin **\n";
    adherent2.EmprunterParISBN(234567890);

    //Nombre de livres disponible dans bibliothèque 1
    std::cout << "Nombre de livres disponibles dans bibliothèque 1 après emprunts : " << bibliotheque1.getCompteurLocalInstances() << "\n";

    // Retour du livre par Jean
    std::cout << "\n** Retour du livre emprunté (123456789) par Jean Dupont **\n";
    adherent1.Rendre(Biblio1_BD1);

    // Affichage des livres disponibles après le retour
    std::cout << "\n** Livres disponibles dans la bibliothèque 1 après retour : **\n";
    bibliotheque1.Afficher();

    // Emprunt direct par l’adhérent
    std::cout << "\n** Emprunt direct du livre Bande Dessinée par Claire Martin **\n";
    adherent2.Emprunter(Biblio1_BD1);
    
    // Erreur suppression d'un livre pas dans la bonne bibliothèque
    bibliotheque1.SupprimerLivre(Biblio2_BD1);

    // Erreur suppression d'un livre emprunté
    bibliotheque1.SupprimerLivre(Biblio1_BD1);

    // Suppression d'un livre
    bibliotheque2.SupprimerLivre(Biblio2_BD2);
    std::cout << "Livres dans bibliothèque 2 après suppression : " << bibliotheque2.getCompteurLocalInstances() << "\n";


    // Simulation d'un prêt entre deux bibliothèques
    std::cout << "\n** Simulation d'un prêt entre Bibliothèque 2 et Bibliothèque 3 **\n";

    // Recherche d'un livre dans Bibliothèque 3
    Livre* livreAPreter = bibliotheque3.RechercherParISBN(667788990);

    // Tentative de prêt
    bibliotheque2.Demander(livreAPreter, bibliotheque3);

    // Affichage des bibliothèques après le prêt
    std::cout << "\n** Livres disponibles dans la bibliothèque 3 après prêt **\n";
    bibliotheque3.Afficher();

    std::cout << "\n** Livres disponibles dans la bibliothèque 2 après prêt **\n";
    bibliotheque2.Afficher();

    // Nettoyage de la mémoire
    delete Biblio1_BD1;
    delete Biblio1_BD2;
    delete Biblio1_Roman1;
    delete Biblio1_Roman2;
    delete Biblio2_BD1;
    delete Biblio2_BD2;
    delete Biblio2_Roman1;  
    delete Biblio2_Roman2;
    delete Biblio3_Roman1;
    delete Biblio3_Roman2;
    delete Biblio3_BD1;
    delete Biblio3_BD2;
    

    return 0;
}
