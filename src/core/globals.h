#ifndef GLOBALS_H
#define GLOBALS_H

#include <cmath>

// Global setting variables
unsigned int windowWidth;
unsigned int windowHeight;
float windowRatio;

// Global math constants
const double PI = 3.141592653589793;
const double PHI = 1.618033988749894; // golden ratio
const double e = 2.718281828459045; // natural log base
const unsigned int c = 299792458; // speed of causality (light) in m/s
const double h = 6.62607015 * std::pow(10, -34); // Planck constant in J/Hz or J*s
const double kB = 1.380649 * pow(10, -23); // Boltzmann constant in J/K
const float G = 6.6743 * pow(10, -11); // gravitational constant in m^3/kg/s^2
const double NA = 6.02214076 * pow(10, 23); // Avogadro's constant in mol^-1

#endif // GLOBALS_H