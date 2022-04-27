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
	Vecteur Alignement(const vector<Proie>& Proies);
	Vecteur Separation(const vector<Proie>& Proies);
	Vecteur Cohesion(const vector<Proie>& Proies);	
	Vecteur Dispersion(const vector<Proie>& Proies);
	Vecteur Total(const vector<Proie>& Proies);
};

class Predateur : public Oiseau
{
public:
	Vecteur Attraction(const vector<Predateur>& Predateurs);
	Vecteur Repulsion(const vector<Predateur>& Predateurs);
};

#endif
