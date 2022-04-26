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
    void def_vecteur(double a, double b);

    //Scalar functions scale a vector by a float
    void ajout_vecteur(const Vecteur& v);
    void ajout_scalaire(double s);

    void soust_vecteur(const Vecteur& v);
    Vecteur diff_vecteurs(const Vecteur& v, const Vecteur& v2);
    void sous_scalaire(double s);

    void mult_vecteur(const Vecteur& v);
    void mult_scalaire(double s);

    void div_vecteur(const Vecteur& v);
    void div_scalaire(double s);

    void limite(double max);

    //Calculating Functions
    float distance(const Vecteur& v);
    float prod_scal(const Vecteur& v);
    float norme();
    void setMagnitude(double x);
    float angle(const Vecteur& v);
    void normaliser();

    Vecteur copy(const Vecteur& v);
};

#endif
