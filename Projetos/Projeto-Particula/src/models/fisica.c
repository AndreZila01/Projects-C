#include "models.h"
#include "fisica.h"

double pows(double values, int times)
{
    double value = 0;
    for (int d = 0; d < times; d++)
        value += values;
    return value;
}

double mySqrt(double x)
{
    if (x < 0)
        return -1.0;

    double guess = x;
    double epsilon = 1e-7; // Set a small value for precision

    while ((guess * guess - x) > epsilon)
    {
        guess = 0.5 * (guess + x / guess);
    }

    return guess;
}

double FAcelaracao(double FResultante, double massa) //(double pi, double veli, int tempo, double posicao)
{
    return FResultante / massa;
    // return ((pi + (veli * tempo) - posicao) * (-2 / (pow(tempo, 2))));
}

double FForcaGraf(double massa1, double massa2, double ra)
{
    return ((6.67430e-11 * massa1 * massa2) / (pows(ra, 2)));
}

double FForceElet(double q1, double q2, double I)
{
    return (8.99e9 * ((q1 * q2) / pows(I, 2)));
}

double FPosicao(double pi, double veli, double tempo)
{
    return pi + (veli * tempo);
    // return pi + (veli * tempo) + (0.5 * acel * pow(tempo, 2));
}

double distancia(Particle part1, Particle part2)
{
    double dx = part1->x - part2->x;
    double dy = part1->y - part2->y;
    double dz = part1->z - part2->z;
    return mySqrt((dx * dx + dy * dy + dz * dz));
}

double FVeloc(double pi, double pf, double tempi, double tempf)
{
    return (pf - pi) / (tempf - tempi);
}