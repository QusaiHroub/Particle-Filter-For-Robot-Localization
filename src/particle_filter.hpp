#ifndef PARTICLE_FILTER_HPP_INCLUDED
#define PARTICLE_FILTER_HPP_INCLUDED

#include <vector>
#include <cmath>
#include "particle.hpp"
#include "maplevel99plus.hpp"
#include "utilities.hpp"

const double pi = 3.14159265;

/**
To calculate the weights using gaussian formula */
double weight(double x, double u, double q) {
	return ((1 / (q * sqrt(2 * pi))) * exp(-1 * pow((x - u), 2) / 2 * pow(q, 2)));
}
/*
To nornormalize the weights
**/
Particle normalize(Particle p, double w) {
	p.setWeight(p.getWeight() / w);
	return p;
}


std::vector<Particle> Particle_filter(std::vector<Particle>v, int U, double Z, double avg, double standardDeviation, int currentPosition, double arr[]) {
	std::vector<Particle> newS;
	MapLevel99Plus map;
	map.buildForVector(v);
	double weightSum = 0;
	for (int i = 0; i < v.size(); i++) {
		Particle randomParticle = Particle(&getRandomParticle(map));
		if (randomParticle.getPosition() + U >= 1000)
			randomParticle.setPosition((rand() % (1000- currentPosition))+ currentPosition);
		else
			randomParticle.setPosition(randomParticle.getPosition() + U);
		double weightParicle = weight(Z - arr[randomParticle.getPosition()], avg, standardDeviation);
		randomParticle.setWeight(weightParicle);
		weightSum += weightParicle;
		newS.push_back(randomParticle);
	};
	for (int i = 0; i < v.size(); i++) {
		v[i] = newS[i];
	}
	for (int i = 0; i < v.size(); i++)
		v[i] = normalize(v[i], weightSum);


	return v;
}

#endif // PARTICLE_FILTER_HPP_INCLUDED