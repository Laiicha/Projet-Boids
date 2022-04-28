#include <Vecteur.hpp>
#include <vector>
#include <iostream>
#include <stdlib.h>

#ifndef BOID_H_
#define BOID_H_
// The Boid Class
//
// Attributes
//  bool predator: flag that specifies whether a given boid is a predator.
//  Pvector location: Vector that specifies a boid's location.
//  Pvector velocity: Vector that specifies a boid's current velocity.
//  Pvector acceleration: Vector that specifies a boid's current acceleration.
//  float maxSpeed: Limits magnitude of velocity vector.
//  float maxForce: Limits magnitude of acceleration vector. (F = m*a!)
//
// Methods
//  applyForce(Pvector force): Adds the given vector to acceleration
//
//  Pvector Separation(vector<Boid> Boids): If any other boids are within a
//      given distance, Separation computes a a vector that distances the
//      current boid from the boids that are too close.
//
//  Pvector Alignment(vector<Boid> Boids): Computes a vector that causes the
//      velocity of the current boid to match that of boids that are nearby.
//
//  Pvector Cohesion(vector<Boid> Boids): Computes a vector that causes the
//      current boid to seek the center of mass of nearby boids.
class Boid
{
public:
	bool predateur;
	Vecteur position;  
	Vecteur vitesse;  
	Vecteur acceleration;
	double vitesse_max;
	Boid() {}
	Boid(bool pred);
	void appl_force(const Vecteur& force);
	Vecteur seek(const Vecteur& v);  
	void run(const vector<Boid>& v);  
	void update();  
	void nuee(const vector<Boid>& v);  
	void bords();  
	double angle(const Vecteur& v);

	
    Vecteur Alignement(const vector<Boid>& Boids);
	Vecteur Separation(const vector<Boid>& Boids);
    Vecteur Cohesion(const vector<Boid>& Boids);
	Vecteur Dispersion(const vector<Boid>& Boids);
	Vecteur Attraction(const vector<Boid>& Boids);
	Vecteur Repulsion(const vector<Boid>& Boids);
};

#endif
