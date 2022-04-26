#include <Vecteur.hpp>
#include <vector>
#include <iostream>
#include <stdlib.h>

#ifndef _OISEAUX_HPP_
#define _OISEAUX_HPP_
class Oiseau
{
public:
  Vecteur position;
  Vecteur vitesse;
  Vecteur acceleration;
  double vitesse_max;
	
	Vecteur seek(const Vecteur& v);
  void run(const vector<Oiseau>& v);
  void update();
  void flock(const vector<Oiseau>& v);
  void borders();
  double angle(const Vecteur& v);
};
class Proie : public Oiseau
{
public:
  Vecteur Alignement(const Vecteur<Proie>& Proie);
	Vecteur Separation(const Vecteur<Proie>& Proie);
  Vecteur Cohesion(const Vecteur<Proie>& Proie);	
	Vecteur Dispersion(const Vecteur<Proie>& Proie);
	Vecteur Total(const Vecteur<Proie>& Proie);
};
class Predateur : public Oiseau
{
public:
  Vecteur Attraction(const Vecteur<Predateur>& Predateur);
	Vecteur Repulsion(const Vecteur<Predateur>& Predateur);
};

#endif
