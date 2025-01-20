#ifndef VECTEUR_H
#define VECTEUR_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Vecteur {
private:
    T* elements;        // Tableau dynamique d'éléments
    int taille;         // Taille actuelle du vecteur
    int capacite;       // Capacité totale du tableau

public:
    // Constructeur
    Vecteur(int capaciteInitiale = 10) : taille(0), capacite(capaciteInitiale) {
        elements = new T[capacite];
    }

    // Destructeur
    ~Vecteur() {
        delete[] elements;
    }

    // Ajouter un élément à la fin du vecteur
    void ajouter(const T& element) {
        if (taille >= capacite) {
            // Augmenter la capacité si nécessaire
            int nouvelleCapacite = capacite * 2;
            T* nouveauxElements = new T[nouvelleCapacite];
            
            // Copier les éléments existants
            for (int i = 0; i < taille; i++) {
                nouveauxElements[i] = elements[i];
            }
            
            delete[] elements;
            elements = nouveauxElements;
            capacite = nouvelleCapacite;
        }
        
        elements[taille] = element;
        taille++;
    }

    // Supprimer le dernier élément
    void supprimer() {
        if (taille > 0) {
            taille--;
        }
    }

    // Accéder à un élément
    T& operator[](int index) {
        if (index < 0 || index >= taille) {
            throw std::out_of_range("Index hors limite");
        }
        return elements[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= taille) {
            throw std::out_of_range("Index hors limite");
        }
        return elements[index];
    }

    // Obtenir la taille actuelle
    int getTaille() const {
        return taille;
    }

    bool estVide() const {
        return taille == 0;
    }

    // Supprimer un élément à un index spécifique
    void supprimerA(int index) {
        if (index < 0 || index >= taille) {
            throw std::out_of_range("Index hors limite");
        }
        for (int i = index; i < taille - 1; i++) {
            elements[i] = elements[i + 1];
        }
        taille--;
    }

    // Ajouter les méthodes begin() et end() pour l'itération
    T* begin() {
        return elements;
    }

    T* end() {
        return elements + taille;
    }

    const T* begin() const {
        return elements;
    }

    const T* end() const {
        return elements + taille;
    }
};

#endif