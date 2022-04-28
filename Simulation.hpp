#include <iostream>
#include "Nuee.hpp"
#include "Boid.hpp"
#include "Vecteur.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#ifndef SIMULATION_H
#define SIMULATION_H

// Game handles the instantiation of a flock of boids, game input, asks the
// model to compute the next step in the stimulation, and handles all of the
// program's interaction with SFML. 

class Simulation {
private:
    sf::RenderWindow fenetre;
    int largeur_fenetre;
    int longueur_fenetre;

    Nuee nuee;
    float taille_boid;
    vector<sf::CircleShape> forme;

    void Render();
    void HandleInput();

public:
    simulation();
    void Run(int nbre_predateurs, int nbre_proies);
};

#endif
