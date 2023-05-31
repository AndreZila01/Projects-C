#ifndef FISICA_H
#define FISICA_H

#include "models.h"

double pows(double values, int times);

double mySqrt(double x);

double FAcelaracao(double FResultante, double massa);

double FForcaGraf(double massa1, double massa2, double ra);

double FForceElet(double q1, double q2, double I);

double FPosicao(double pi, double veli, double tempo);

double distancia(Particle part1, Particle part2);

double FVeloc(double pi, double pf, double tempi, double tempf);

#endif
