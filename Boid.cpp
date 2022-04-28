#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <stdlib.h>
#include "SFML/Graphics.hpp"
#include "Boid.hpp"

// Global Variables for borders()
// desktopTemp gets screen resolution of PC running the program
sf::VideoMode desktopTemp = sf::VideoMode::getDesktopMode();
const int window_height = desktopTemp.height;
const int window_width = desktopTemp.width;

#define w_height window_height
#define w_width window_width
#define PI 3.141592635

// =============================================== //
// ======== Boid Functions from Boid.h =========== //
// =============================================== //

Boid::Boid()
{
    acceleration = Vecteur(0, 0);
    vitesse = Vecteur(-1 + (double)((double)rand()*3 / (RAND_MAX-1)), -1 + (double)((double)rand()*3 / (RAND_MAX-1)));
    position = Vecteur(-1 + (double)((double)rand()*3 / (RAND_MAX-1)), -1 + (double)((double)rand()*3 / (RAND_MAX-1)));
    vitesse_max = 2;
    force_max=0.05;
}


Boid::Boid(float x, float y, bool predCheck)
{
    predateur = predCheck;
    if (predCheck == true) {
        vitesse_max = 7.5;
        force_max = 0.5;
        vitesse = Vecteur(rand()%3 - 1, rand()%3 - 1);
    } else {
        vitesse_max = 3.5;
        force_max = 0.5;
        vitesse = Vecteur(rand()%3 - 2, rand()%3 - 2);
    }
    acceleration = Vecteur(0, 0);
    position  = Vecteur(x, y);
}
// Adds force Pvector to current force Pvector
void Boid::appl_force(const Vecteur& force)
{
    acceleration.ajout_vecteur(force);
}

// Separation
// Keeps boids from getting too close to one another
Pvector Boid::Separation(const vector<Boid>& boids)
{
    // Distance of field of vision for separation between boids
    float desiredseparation = 20;
    Vecteur steer(0, 0);
    int count = 0;
    // For every boid in the system, check if it's too close
    for (int i = 0; i < boids.size(); i++) {
        // Calculate distance from current boid to boid we're looking at
        float d = position.distance(boids[i].position);
        // If this is a fellow boid and it's too close, move away from it
        if ((d > 0) && (d < desiredseparation)) {
            Vecteur diff(0,0);
            diff = diff.soust_vecteur(location, boids[i].location);
            diff.normalise();
            diff.div_scalaire(d);      // Weight by distance
            steer.ajout_vecteur(diff);
            count++;
        }
        // If current boid is a predator and the boid we're looking at is also
        // a predator, then separate only slightly
        if ((d > 0) && (d < desiredseparation) && predateur == true
            && boids[i].predateur == true) {
            Vecteur pred2pred(0, 0);
            pred2pred = pred2pred.soust_vecteur(location, boids[i].location);
            pred2pred.normalise();
            pred2pred.div_scalaire(d);
            steer.ajout_vecteur(pred2pred);
            count++;
        }
        // If current boid is not a predator, but the boid we're looking at is
        // a predator, then create a large separation Pvector
        else if ((d > 0) && (d < desiredseparation+70) && boids[i].predator == true) {
            Vecteur pred(0, 0);
            pred = pred.soust_vecteur(location, boids[i].location);
            pred.mult_scalaire(900);
            steer.ajout_vecteur(pred);
            count++;
        }
    }
    // Adds average difference of location to acceleration
    if (count > 0)
        steer.div_scalaire((float)count);
    if (steer.norme() > 0) {
        // Steering = Desired - Velocity
        steer.normalise();
        steer.mult_scalaire(vitesse_max);
        steer.sous_scalaire(acceleration);
        steer.limite(force_max);
    }
    return steer;
}
// Alignment
// Calculates the average velocity of boids in the field of vision and
// manipulates the velocity of the current boid in order to match it
Vecteur Boid::Alignement(const vector<Boid>& Boids)
{
    force_max = 0.05;
    double da = 25; // Field of vision

    Vecteur somme(0, 0);
    int compt = 0;
    for (int i = 0; i < Boids.size(); i++) {
        float d = position.distance(Boids[i].position);
        if ((d > 0) && (d < da)) { // 0 < d < 50
            somme.ajout_vecteur(Boids[i].vitesse);
            compt++;
        }
    }
    // If there are boids close enough for alignment...
    if (compt > 0) {
        somme.div_scalaire((double)compt);// Divide sum by the number of close boids (average of velocity)
        somme.normaliser();            // Turn sum into a unit vector, and
        somme.mult_scalaire(vitesse_max);    // Multiply by maxSpeed
        // Steer = Desired - Velocity
        Vecteur s;
        s = s.diff_vecteurs(somme, vitesse); //sum = desired(average)
        s.limite(force_max);
        return s;
    } 
    else {
        Vecteur temp(0, 0);
        return temp;
    }
}

// Separation
// Keeps boids from getting too close to one another
Vecteur Boid::Separation(const vector<Proie>& Proies)
{
    double ds = 20.;
    // Distance of field of vision for separation between boids
    Vecteur s(0, 0);
    int compt = 0;
    // For every boid in the system, check if it's too close
    for (int i = 0; i < Boids.size(); i++) {
        // Calculate distance from current boid to boid we're looking at
        float d = position.distance(Boids[i].position);
        // If this is a fellow boid and it's too close, move away from it
        if ((d > 0) && (d < ds)) {
            Vecteur diff(0,0);
            diff = diff.diff_vecteurs(position, Boids[i].position);
            diff.normaliser();
            diff.div_scalaire(d);      // Weight by distance
            steer.ajout_vecteur(diff);
            compt++;
        }
    }
    // Adds average difference of location to acceleration
    if (compt > 0)
        s.div_scalaire((double)compt);
    if (s.norme() > 0) {
        // Steering = Desired - Velocity
        s.normalize();
        s.mult_scalaire(vitesse_max);
        s.sous_vecteur(vitesse);
        s.limite(force_max);
    }
    return s;
}



// Cohesion
// Finds the average location of nearby boids and manipulates the
// steering force to move in that direction.
Vecteur Proie::Cohesion(const vector<Proie>& Proies)
{
    double da = 25;
    Vecteur somme(0, 0);
    int compt = 0;
    for (int i = 0; i < Proies.size(); i++) {
        double d = position.distance(Proies[i].position);
        if ((d > 0) && (d < da)) {
            somme.ajout_vecteur(Proies[i].position);
            compt++;
        }
    }
    if (compt > 0) {
        somme.div_scalaire(compt);
        return seek(somme);
    } else {
        Vecteur temp(0,0);
        return temp;
    }
}

// Dispersion
// Keeps boids from getting too close to one another
Vecteur Proie::Dispersion(const vector<Proie>& Predateurs)
{
    double da = 25;
    force_max = 0.05; 
    // Distance of field of vision for separation between boids
    Vecteur s(0, 0);
    int compt = 0;
    // For every boid in the system, check if it's too close
    for (int i = 0; i < Predateurs.size(); i++) {
        // Calculate distance from current boid to boid we're looking at
        float d = position.distance(Predateurs[i].position);
        // If this is a fellow boid and it's too close, move away from it
        if ((d > 0) && (d < ds)) {
            Vecteur diff(0,0);
            diff = diff.diff_vecteurs(position, Predateurs[i].position);
            diff.normaliser();
            diff.div_scalaire(d*d);      // Weight by distance
            s.ajout_vecteur(diff);
            compt++;
        }
    }
    // Adds average difference of location to acceleration
    if (compt > 0)
        s.div_scalaire((double)compt);
    if (s.norme() > 0) {
        // Steering = Desired - Velocity
        s.normaliser();
        s.mult_scalaire(vitesse_max);
        s.sous_vecteur(vitesse);
        s.limite(force_max);
    }
    return s;
}

// Totale
// Keeps boids from getting too close to one another
Vecteur Proie::Total(const vector<Proie>& Proies, const vector<Predateur>& Predateurs)
{
  Vecteur steer(0, 0);
  Vecteur Fa = Alignement(Proies)
  Vecteur Fs = Separation(Proies)
  Vecteur Fd = Dispersion(Predateurs)
  Fs =  Fs.mult_scalaire(0.75);
  Fd =  Fd.mult_scalaire(0.75);
  Vecteur Fc = Cohesion(Proies)
  steer.ajout_vecteur(Fa);
  steer.ajout_vecteur(Fc);
  steer.ajout_vecteur(Fs);
  steer.ajout_vecteur(Fd);
}



//Attraction
Vecteur Predateur::Attraction(const vector<Proie>& Proies)
{
    double da = 25
    force_max = 0.05;
    // Distance of field of vision for separation between boids
    Vecteur s(0, 0);
    int compt = 0;
    // For every boid in the system, check if it's too close
    for (int i = 0; i < Proies.size(); i++) {
        // Calculate distance from current boid to boid we're looking at
        float d = position.distance(Proies[i].position);
        // If this is a fellow boid and it's too close, move away from it
        if ((d > 0) && (d < ds)) {
            Vecteur diff(0,0);
            diff = diff.diff_vecteurs(location, Proies[i].position);
            diff.normaliser();
            diff.div_scalaire(d*d);      // Weight by distance
            s.ajout_vecteur(diff);
            compt++;
        }
    }
    // Adds average difference of location to acceleration
    if (compt > 0)
        s.divScalar((double)compt);
    if (.magnitude() > 0) {
        // Steering = Desired - Velocity
        s.normaliser();
        s.mult_scalaire(vitesse_max);
        s.sous_vecteur(vitesse);
        s.limite(force_max);
    }
    return s;
}

// Repulsion
// Keeps boids from getting too close to one another
Vecteur Predateur::Repulsion(const vector<Proie>& Predateurs)
{
    double ds = 20;
    force_max = 0.05;
    // Distance of field of vision for separation between boids
    Vecteur s(0, 0);
    int compt = 0;
    // For every boid in the system, check if it's too close
    for (int i = 0; i < Predateurs.size(); i++) {
        // Calculate distance from current boid to boid we're looking at
        float d = position.distance(Predateurs[i].position);
        // If this is a fellow boid and it's too close, move away from it
        if ((d > 0) && (d < ds)) {
            Vecteur diff(0,0);
            diff = diff.diff_vecteurs(location, Predateurs[i].position);
            diff.normaliser();
            diff.div_scalaire(d);      // Weight by distance
            s.ajout_vecteur(diff);
            compt++;
        }
    }
    // Adds average difference of location to acceleration
    if (compt > 0)
        s.div_scalaire((double)compt);
    if (s.norme() > 0) {
        // Steering = Desired - Velocity
        s.normaliser();
        s.mult_scalaire(vitesse_max);
        s.sous_vecteur(vitesse);
        s.limite(force_max);
    }
    return s;
}

// Limits the maxSpeed, finds necessary steering force and
// normalizes vectors
Vecteur Boid::seek(const Vecteur& v)
{
    Vecteur desired;
    desired.soust_vecteur(v);  // A vector pointing from the location to the target
    // Normalize desired and scale to maximum speed
    desired.normaliser();
    desired.mult_scalaire(vitesse_max);
    // Steering = Desired minus Velocity
    acceleration.subTwoVector(desired, velocity);
    acceleration.limit(maxForce);  // Limit to maximum steering force
    return acceleration;
}

// Modifies velocity, location, and resets acceleration with values that
// are given by the three laws.
void Boid::update()
{
    //To make the slow down not as abrupt
    acceleration = Totale;
    // Update velocity
    vitesse.ajout_vecteur(acceleration);
    // Limit speed
    vitesse.limite(vitesse_max);
    location.ajout_vecteur(vitesse);
    // Reset accelertion to 0 each cycle
    //acceleration.mulScalar(0);
}

// Run flock() on the flock of boids.
// This applies the three rules, modifies velocities accordingly, updates data,
// and corrects boids which are sitting outside of the SFML window
void Boid::run(const vector <Boid>& v)
{
    flock(v);
    update();
    borders();
}

// Applies the three laws to the flock of boids
void Oiseau::flock(const vector<Boid>& v)
{
    Pvector sep = Separation(v);
    Pvector ali = Alignement(v);
    Pvector coh = Cohesion(v);
    // Arbitrarily weight these forces
    sep.mulScalar(1.5);
    ali.mulScalar(1.0); // Might need to alter weights for different characteristics
    coh.mulScalar(1.0);
    // Add the force vectors to acceleration
    appl_force(sep);
    appl_force(ali);
    appl_force(coh);
}

// Checks if boids go out of the window and if so, wraps them around to
// the other side.
void Oiseau::borders()
{
    if (position.x < 0)    position.x += w_width;
    if (position.y < 0)    position.y += w_height;
    if (position.x > 1000) position.x -= w_width;
    if (position.y > 1000) position.y -= w_height;
}

// Calculates the angle for the velocity of a boid which allows the visual
// image to rotate in the direction that it is going in.
double Oiseau::angle(const Vecteur& v)
{
    // From the definition of the dot product
    double angle = (double)(atan2(v.x, -v.y) * 180 / PI);
    return angle;
}
