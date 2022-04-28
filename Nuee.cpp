#include "Boid.hpp"
#include "Nuee.hpp"

//definition des fonctions de Nuee

int Nuee::taille()
{
    return nuee.size();
}

//Read only method that returns a copy of the Boid.
Boid Nuee::get_boid(int i)
{
    return nuee[i];
}


void Nuee::ajout_boid(const Boid& b)
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
