#include "Oiseau.hpp"
#include "Nuee.hpp"

// =============================================== //
// ======== Flock Functions from Flock.h ========= //
// =============================================== //

int Nuee::taille()
{
    return nuee.size();
}

//Read only method that returns a copy of the Boid.
Boid Nuee::getOiseau(int i)
{
    return nuee[i];
}


void Nuee::ajout_oiseau(const Oiseau& b)
{
    nuee.push_back(std::move(b));
}

// Runs the run function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Nuee::flocking() 
{
    for (int i = 0; i < nuee.size(); i++)
        nuee[i].run(nuee);
}
