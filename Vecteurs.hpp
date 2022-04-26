#include <iostream>

using namespace std;

#ifndef VECTEUR_H_
#define VECTEUR_H_

// The Pvector class implements Euclidian vectors -- that is, each vector has
// both a magnitude and a direction. We use Pvectors for implementing movement
// and the three Boid rules -- cohesion, separation, and matching velocity
// through the use of acceleration, force, and velocity vectors.

class Vecteur {

public:
    double x;
    double y;

    //Constructors
    Vecteur() {}

    Vecteur(double x1, double y1)
    {
        x = x1;
        y = y1;
    }

    //Mutator Functions
    void def_vecteur(double x, double y);

    //Scalar functions scale a vector by a float
    void ajout_vecteur(const Vecteur& v);
    void ajout_scalaire(float x);

    void subVector(const Pvector& v);
    Vecteurs subTwoVector(const Pvector& v, const Pvector& v2);
    void subScalar(float x);

    void mulVector(const Pvector& v);
    void mulScalar(float x);

    void divVector(const Pvector& v);
    void divScalar(float x);

    void limit(double max);

    //Calculating Functions
    float distance(const Pvector& v);
    float dotProduct(const Pvector& v);
    float magnitude();
    void setMagnitude(float x);
    float angleBetween(const Pvector& v);
    void normalize();

    Pvector copy(const Pvector& v);
};

#endif
