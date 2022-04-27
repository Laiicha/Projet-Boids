#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "Oiseau.hpp"

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

Oiseau::Oiseau()
{
    acceleration = Vecteur(0, 0);
    vitesse = Vecteur(-1 + (double)((double)rand()*3 / (RAND_MAX-1)), -1 + (double)((double)rand()*3 / (RAND_MAX-1)));
    position = Vecteur(-1 + (double)((double)rand()*3 / (RAND_MAX-1)), -1 + (double)((double)rand()*3 / (RAND_MAX-1)));
    vitesse_max = 2;
}


// Adds force Pvector to current force Pvector
void Oiseau::applyForce(const Pvector& force)
{
    acceleration.addVector(force);
}

// Alignment
// Calculates the average velocity of boids in the field of vision and
// manipulates the velocity of the current boid in order to match it
Vecteur Proie::Alignement(const vector<Proie>& Proies)
{
    double da = 25; // Field of vision

    Vecteur somme(0, 0);
    int compt = 0;
    for (int i = 0; i < Proies.size(); i++) {
        float d = position.distance(Proies[i].position);
        if ((d > 0) && (d < neighbordist)) { // 0 < d < 50
            somme.ajout_vecteur(Proies[i].vitesse);
            compt++;
        }
    }
    // If there are boids close enough for alignment...
    if (count > 0) {
        sum.div_scalaire((double)count);// Divide sum by the number of close boids (average of velocity)
        sum.normaliser();            // Turn sum into a unit vector, and
        sum.mult_scalaire(vitesse_max);    // Multiply by maxSpeed
        // Steer = Desired - Velocity
        Vecteur steer;
        steer = steer.diff_vecteurs(sum, velocity); //sum = desired(average)
        steer.limite(maxForce);
        return steer;
    } 
    else {
        Pvector temp(0, 0);
        return temp;
    }
}

// Separation
// Keeps boids from getting too close to one another
Vecteur Proie::Separation(const vector<Proie>& Proies)
{
    double ds = 20
    // Distance of field of vision for separation between boids
    Vecteur steer(0, 0);
    int count = 0;
    // For every boid in the system, check if it's too close
    for (int i = 0; i < Proies.size(); i++) {
        // Calculate distance from current boid to boid we're looking at
        float d = position.distance(Proies[i].position);
        // If this is a fellow boid and it's too close, move away from it
        if ((d > 0) && (d < ds)) {
            Vecteurr diff(0,0);
            diff = diff.diff_vecteurs(location, Proies[i].position);
            diff.normaliser();
            diff.div_scalaire(d);      // Weight by distance
            steer.ajout_vecteur(diff);
            count++;
        }
    }
    // Adds average difference of location to acceleration
    if (count > 0)
        steer.divScalar((float)count);
    if (steer.magnitude() > 0) {
        // Steering = Desired - Velocity
        steer.normalize();
        steer.mulScalar(maxSpeed);
        steer.subVector(velocity);
        steer.limit(maxForce);
    }
    return steer;
}



// Cohesion
// Finds the average location of nearby boids and manipulates the
// steering force to move in that direction.
Vecteur Proie::Cohesion(const vector<Proie>& Proies)
{
    double da = 25;
    Vecteur sum(0, 0);
    int count = 0;
    for (int i = 0; i < Proies.size(); i++) {
        double d = position.distance(Proies[i].position);
        if ((d > 0) && (d < da)) {
            sum.ajout_vecteur(Proies[i].position);
            count++;
        }
    }
    if (count > 0) {
        sum.div_scalaire(count);
        return seek(sum);
    } else {
        Vecteur temp(0,0);
        return temp;
    }
}

// Dispersion
// Keeps boids from getting too close to one another
Vecteur Proie::Dispersion(const vector<Proie>& Predateurs)
{
    double da = 25
    // Distance of field of vision for separation between boids
    Vecteur diff(0, 0);
    int count = 0;
    // For every boid in the system, check if it's too close
    for (int i = 0; i < Predateurs.size(); i++) {
        // Calculate distance from current boid to boid we're looking at
        float d = position.distance(Predateurs[i].position);
        // If this is a fellow boid and it's too close, move away from it
        if ((d > 0) && (d < ds)) {
            Vecteurr diff(0,0);
            diff = diff.diff_vecteurs(location, Predateurs[i].position);
            diff.normaliser();
            diff.div_scalaire(d*d);      // Weight by distance
            steer.ajout_vecteur(diff);
            count++;
        }
    }
    // Adds average difference of location to acceleration
    if (count > 0)
        diff.divScalar((float)count);
    if (diff.magnitude() > 0) {
        // Steering = Desired - Velocity
        diff.normalize();
        diff.mulScalar(maxSpeed);
        diff.subVector(velocity);
        diff.limit(maxForce);
    }
    return diff;
}

// Totale
// Keeps boids from getting too close to one another
Vecteur Proie::Total(const vector<Proie>& Proies)
{
  Vecteur steer(0, 0);
  Vecteur Fa = Alignement(Proies)
  Vecteur Fs = Separation(Proies)
  Vecteur Fd = Dispersion(Proies)
  Fs =  Fs.mult_scalaire(0.75);
  Fd =  Fd.mult_scalaire(0.75);
  Vecteur Fc = Cohesion(Proies)
  steer.ajout_vecteur(Fa);
  steer.ajout_vecteur(Fc);
  steer.ajout_vecteur(Fs);
  steer.ajout_vecteur(Fd);
}



//Attraction
Vecteur Predateur::Dispersion(const vector<Proie>& Proies)
{
    double da = 25
    // Distance of field of vision for separation between boids
    Vecteur diff(0, 0);
    int count = 0;
    // For every boid in the system, check if it's too close
    for (int i = 0; i < Proies.size(); i++) {
        // Calculate distance from current boid to boid we're looking at
        float d = position.distance(Proies[i].position);
        // If this is a fellow boid and it's too close, move away from it
        if ((d > 0) && (d < ds)) {
            Vecteurr diff(0,0);
            diff = diff.diff_vecteurs(location, Proies[i].position);
            diff.normaliser();
            diff.div_scalaire(d*d);      // Weight by distance
            steer.ajout_vecteur(diff);
            count++;
        }
    }
    // Adds average difference of location to acceleration
    if (count > 0)
        diff.divScalar((float)count);
    if (diff.magnitude() > 0) {
        // Steering = Desired - Velocity
        diff.normalize();
        diff.mulScalar(maxSpeed);
        diff.subVector(velocity);
        diff.limit(maxForce);
    }
    return diff;
}

// Repulsion
// Keeps boids from getting too close to one another
Vecteur Predateur::Separation(const vector<Proie>& Predateurs)
{
    double ds = 20
    // Distance of field of vision for separation between boids
    Vecteur steer(0, 0);
    int count = 0;
    // For every boid in the system, check if it's too close
    for (int i = 0; i < Predateurs.size(); i++) {
        // Calculate distance from current boid to boid we're looking at
        float d = position.distance(Predateurs[i].position);
        // If this is a fellow boid and it's too close, move away from it
        if ((d > 0) && (d < ds)) {
            Vecteurr diff(0,0);
            diff = diff.diff_vecteurs(location, Predateurs[i].position);
            diff.normaliser();
            diff.div_scalaire(d);      // Weight by distance
            steer.ajout_vecteur(diff);
            count++;
        }
    }
    // Adds average difference of location to acceleration
    if (count > 0)
        steer.divScalar((float)count);
    if (steer.magnitude() > 0) {
        // Steering = Desired - Velocity
        steer.normalize();
        steer.mulScalar(maxSpeed);
        steer.subVector(velocity);
        steer.limit(maxForce);
    }
    return steer;
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
    velocity.addVector(acceleration);
    // Limit speed
    velocity.limit(maxSpeed);
    location.addVector(velocity);
    // Reset accelertion to 0 each cycle
    acceleration.mulScalar(0);
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
    Pvector ali = Alignment(v);
    Pvector coh = Cohesion(v);
    // Arbitrarily weight these forces
    sep.mulScalar(1.5);
    ali.mulScalar(1.0); // Might need to alter weights for different characteristics
    coh.mulScalar(1.0);
    // Add the force vectors to acceleration
    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
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
