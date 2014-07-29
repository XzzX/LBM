#include	"BoundaryConditions.h"

void	ZHPressureNorth(double f[LB::DIM_I], double u[2], const double rho) {
	u[1] = -1 + ( f[0] + f[1] + f[3] + 2 * ( f[4] + f[7] + f[8] ) ) / rho;
	double ru = rho *  u[1];
	f[2] = f[4] - 2.0 / 3.0 * ru;
	f[5] = f[7] - 1.0 / 6.0 * ru + 0.5 * ( f[3] - f[1] );
	f[6] = f[8] - 1.0 / 6.0 * ru + 0.5 * ( f[1] - f[3] );
}

void	ZHPressureSouth(double f[LB::DIM_I], double u[2], const double rho) {
	u[1] = -1 + ( f[0] + f[1] + f[3] + 2 * ( f[4] + f[7] + f[8] ) ) / rho;
	double ru = rho *  u[1];
	f[2] = f[4] - 2.0 / 3.0 * ru;
	f[5] = f[7] - 1.0 / 6.0 * ru + 0.5 * ( f[3] - f[1] );
	f[6] = f[8] - 1.0 / 6.0 * ru + 0.5 * ( f[1] - f[3] );
}

void	ZHPressureEast(double f[LB::DIM_I], double u[2], const double rho) {
	u[1] = 0;
	u[0] = -1 + ( f[0] + f[2] + f[4] + 2 * ( f[1] + f[5] + f[8] ) ) / rho;
	double ru = rho *  u[0];
	f[3] = f[1] - 2.0 / 3.0 * ru;
	f[7] = f[5] - 1.0 / 6.0 * ru + 0.5 * ( f[2] - f[4] );
	f[6] = f[8] - 1.0 / 6.0 * ru + 0.5 * ( f[4] - f[2] );
}

void	ZHPressureWest(double f[LB::DIM_I], double u[2], const double rho) {
	u[1] = 0;
	u[0] = -1.0 + ( f[0] + f[2] + f[4] + 2.0 * ( f[3] + f[7] + f[6] ) ) / rho;
	double ru = rho *  u[0];
	f[1] = f[3] - 2.0 / 3.0 * ru;
	f[5] = f[7] - 1.0 / 6.0 * ru + 0.5 * ( f[4] - f[2] );
	f[8] = f[6] - 1.0 / 6.0 * ru + 0.5 * ( f[2] - f[4] );
}