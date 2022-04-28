#include <iostream>
#include "Nuee.hpp"
#include "Boid.hpp"
#include "Vecteur.hpp"
#include "Simulation.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

// Construct window using SFML
Simulation::Simulation()
{
    this->taille_boid = 3.0;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    this->longueur_fenetre = desktop.height;
    this->largeur_fenetre  = desktop.width;
    this->fenetre.create(sf::VideoMode(largeur_fenetre, longueur_fenetre, desktop.bitsPerPixel), "Boids", sf::Style::None);
    
    // Try to achieve 60 FPS.
    fenetre.setFramerateLimit(60);
}

// Run the simulation. Run creates the boids that we'll display, checks for user
// input, and updates the view
void Game::Run()
{
    for (int i = 0; i < 250; i++) {
       // Boid b(largeur_fenetre/3,longueur_fenetre/3); // Starts all boids in the center of the screen
        Boid b();
        sf::CircleShape shape(8, 3);

        // Changing the Visual Properties of the shape
        // shape.setPosition(b.location.x, b.location.y); // Sets position of shape to random location that boid was set to.
        shape.setPosition(largeur_fenetre, longueur_fenetre); // Testing purposes, starts all shapes in the center of screen.
        shape.setOutlineColor(sf::Color(0,255,0));
        shape.setFillColor(sf::Color::Green);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(1);
        shape.setRadius(taille_boid);

        // Adding the boid to the flock and adding the shapes to the vector<sf::CircleShape>
        nuee.ajout_boid(b);
        forme.push_back(shape);
    }
    while (fenetre.isOpen()) {
        HandleInput();
        Render();
    }
}

void simulation::HandleInput()
{
    sf::Event event;
    while (fenetre.pollEvent(event)) {
        // "close requested" event: we close the window
        // Implemented alternate ways to close the window. (Pressing the escape, X, and BackSpace key also close the program.)
        if ((event.type == sf::Event::Closed) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::Escape) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::BackSpace) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::X))
             {
            fenetre.close();
        }
    }

    // Check for mouse click, draws and adds boid to flock if so.
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Gets mouse coordinates, sets that as the location of the boid and the shape
        sf::Vector2i mouseCoords = sf::Mouse::getPosition(fenetre);
        Boid b(mouseCoords.x, mouseCoords.y, false);
        sf::CircleShape shape(10,3);

        // Changing visual properties of newly created boid
        shape.setPosition(mouseCoords.x, mouseCoords.y);
        shape.setOutlineColor(sf::Color(255, 0, 0));
        shape.setFillColor(sf::Color(255, 0, 0));
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(1);
        shape.setRadius(taille_boid);

        // Adds newly created boid and shape to their respective data structure
        nuee.addBoid(b);
        forme.push_back(shape);

        // New Shape is drawn
        fenetre.draw(forme[forme.size()-1]);
    }
}

void Simulation::Render()
{
    fenetre.clear();

    // Draws all of the Boids out, and applies functions that are needed to update.
    for (int i = 0; i < forme.size(); i++) {
        fenetre.draw(forme[i]);

        //cout << "Boid "<< i <<" Coordinates: (" << shapes[i].getPosition().x << ", " << shapes[i].getPosition().y << ")" << endl;
        //cout << "Boid Code " << i << " Location: (" << flock.getBoid(i).location.x << ", " << flock.getBoid(i).location.y << ")" << endl;

        // Matches up the location of the shape to the boid
        forme[i].setPosition(nuee.get_boid(i).position.x, nuee.get_boid(i).position.y);

        // Calculates the angle where the velocity is pointing so that the triangle turns towards it.
        double theta = nuee.get_boid(i).angle(nuee.get_boid(i).vitesse);
        forme[i].setRotation(theta);

        // Prevent boids from moving off the screen through wrapping
        // If boid exits right boundary
        if (forme[i].getPosition().x > largeur_fenetre)
            forme[i].setPosition(forme[i].getPosition().x - largeur_fenetre, forme[i].getPosition().y);
        // If boid exits bottom boundary
        if (forme[i].getPosition().y > longueur_fenetre)
            forme[i].setPosition(forme[i].getPosition().x, forme[i].getPosition().y - longueur_fenetre);
        // If boid exits left boundary
        if (forme[i].getPosition().x < 0)
            forme[i].setPosition(forme[i].getPosition().x + largeur_fenetre, forme[i].getPosition().y);
        // If boid exits top boundary
        if (forme[i].getPosition().y < 0)
            forme[i].setPosition(forme[i].getPosition().x, forme[i].getPosition().y + longueur_fenetre);
    }

    // Applies the three rules to each boid in the flock and changes them accordingly.
    nuee.flocking();

    fenetre.display();
}
