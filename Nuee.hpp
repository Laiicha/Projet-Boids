#include <iostream>
#include <vector>
#include "Oiseau.h"

#ifndef NUEE_H_
#define NUEE_H_


// Brief description of Flock Class:
// This file contains the class needed to create a flock of boids. It utilizes
// the boids class and initializes boid flocks with parameters that can be
// specified. This class will be utilized in main.

class Nuee{
public:
    //Constructors
    Nuee() {}
    // Accessor functions
    int taille();
    //Read only and read/write methods.
    Oiseau getoiseau(int i);
    // Mutator Functions
    void ajout_oiseau(const Oiseau& b);
    void flocking();
private:
    vector<Oiseau> nuee;  
};

#endif
