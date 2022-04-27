#include <math.h>
#include "Vecteur.hpp"

// =================================================== //
// ======== Pvector Functions from Pvector.h ========= //
// =================================================== //

#define PI 3.141592635

// Sets values of x and y for Pvector
void Vecteur::def_vecteur(double a, double b)
{
    x = a;
    y = b;
}

void Vecteur::ajout_vecteur(const Vecteur& v)
{
    x = x + v.x;
    y = y + v.y;
}

// Adds to a Pvector by a constant number
void Vecteur::ajout_scalaire(double s)
{
    x = x + s;
    y = y + s;
}

// Subtracts 2 vectors
void Vecteur::soust_vecteur(const Vecteur& v)
{
    x = x - v.x;
    y = y - v.y;
}

// Subtracts two vectors and returns the difference as a vector
Vecteur Vecteur::diff_vecteurs(const Vecteur& v, const Vecteur& v2)
{
    Vecteur tmp(v.x - v2.x, v.y - v2.y);
    return std::move(tmp);
}

// Adds to a Pvector by a constant number
void Vecteur::sous_scalaire(double s)
{
    x = x - s;
    y = y - s;
}

// Multiplies 2 vectors
void Vecteur::mult_vecteur(const Vecteur& v)
{
    x = x * v.x;
    y = y * v.y;
}

// Adds to a Pvector by a constant number
void Vecteur::mult_scalaire(double s);
{
    x = x * s;
    y = y * s;
}

// Divides 2 vectors
void Vecteur::div_vecteur(const Vecteur& v)
{
    x = x/v.x;
    y = y/v.y;
}

// Adds to a Pvector by a constant number
void Vecteur::div_scalaire(double s);
{
    x = x/s;
    y = y/s;
}

void Vecteur::limite(double max)
{
    double s = norme();

    if (s > max) {
        set(x / s, y / s);
    }
}

// Calculates the distance between the first Pvector and second Pvector
float Vecteur::distance(const Vecteur& v)
{
    double dx = x - v.x;
    double dy = y - v.y;
    double dist = sqrt(dx*dx + dy*dy);
    return dist;
}

// Calculates the dot product of a vector
double Vecteur::prod_scal(const Vecteur& v)
{
    double prod = x * v.x + y * v.y;
    return prod;
}

// Calculates magnitude of referenced object
double Vecteur::norme()
{
    return sqrt(x*x + y*y);
}

void Vecteur::set_norme(double x)
{
    normalize();
    mulScalar(x);
}

// Calculate the angle between Pvector 1 and Pvector 2
double Vecteur::angle(const Vecteur& v)
{
    if (x == 0 && y == 0) return 0.0;
    if (v.x == 0 && v.y == 0) return 0.0;

    double dot = x * v.x + y * v.y;
    double v1mag = sqrt(x * x + y * y);
    double v2mag = sqrt(v.x * v.x + v.y * v.y);
    double amt = dot / (v1mag * v2mag); //Based of definition of dot product
    //dot product / product of magnitudes gives amt
    if (amt <= -1) {
        return PI;
    } else if (amt >= 1) {
        return 0;
    }
    double tmp = acos(amt);
    return tmp;
}

// normalize divides x and y by magnitude if it has a magnitude.
void Vecteur::normaliser()
{
    double m = magnitude();

    if (m > 0) {
        set(x / m, y / m);
    } else {
        set(x, y);
    }
}

// Creates and returns a copy of the Pvector used as a parameter
Vecteur Vecteur::copy(const Vecteur& v)
{
    Vecteur copy(v.x, v.y);
    return copy;
}
