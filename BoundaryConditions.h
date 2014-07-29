#ifndef BOUNDARYCONDITIONS_H_INCLUDED
#define BOUNDARYCONDITIONS_H_INCLUDED

#include	"LB.h"

void	ZHPressureNorth(double f[LB::DIM_I], double u[2], const double rho);
void	ZHPressureSouth(double f[LB::DIM_I], double u[2], const double rho);
void	ZHPressureEast(double f[LB::DIM_I], double u[2], const double rho);
void	ZHPressureWest(double f[LB::DIM_I], double u[2], const double rho);

#endif