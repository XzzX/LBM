#include	"LB.h"

#include	"BoundaryConditions.h"

#include	<iostream>
#include	<fstream>

// lattice weights
const double LB::t[DIM_I] = { 4. / 9., 1. / 9., 1. / 9., 1. / 9., 1. / 9.,
1. / 36., 1. / 36., 1. / 36., 1. / 36. };
// lattice velocities
const double LB::c[DIM_I][2] = {
	{ 0, 0 },
	{ 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 },
	{ 1, 1 }, { -1, 1 }, { -1, -1 }, { 1, -1 }
};

const int LB::opposite[DIM_I] = { 0, 3, 4, 1, 2, 7, 8, 5, 6 };

LB::LB(const double xMax, const double yMax, const double tau, const double tPostProcessing) :
mXMax(xMax),
mYMax(yMax),
mTau(tau),
mTPostProcessing(tPostProcessing) {
	InitWall();
	InitDistributions();
}

LB::~LB() {}

void LB::computeVariables(const double f[DIM_I], double& rho, double& ux, double& uy, double& uSqr) {
	rho = 0;
	ux = 0;
	uy = 0;
	uSqr = 0;

	for (int iF = 0; iF<DIM_I; ++iF){
		rho += f[iF];
		ux += f[iF] * c[iF][0];
		uy += f[iF] * c[iF][1];
	}
	ux /= rho;
	uy /= rho;
	uSqr += ux * ux + uy * uy;
}

double LB::fEq(const int iF, const double rho, const double ux, const double uy, const double uSqr) {
	double c_u = c[iF][0] * ux + c[iF][1] * uy;
	return rho * t[iF] * ( 1. + 3.*c_u + 4.5*c_u*c_u - 1.5*uSqr );
}

void	LB::InitWall() {
	for (unsigned int x = 0; x < DIM_X; x++) 
		for (unsigned int y = 0; y < DIM_Y; y++) {
			mWall[x][y] = BOUNDARY_CONDITION::FLUID;
			if ((x == 0) || (x == DIM_X-1 ))
				mWall[x][y] = BOUNDARY_CONDITION::NO_SLIP;
			if (( y == 0 ) || ( y == DIM_Y - 1 ))
				mWall[x][y] = BOUNDARY_CONDITION::NO_SLIP;
		}
	mWall[20][9] = BOUNDARY_CONDITION::NO_SLIP;
	mWall[20][10] = BOUNDARY_CONDITION::NO_SLIP;
	mWall[20][11] = BOUNDARY_CONDITION::NO_SLIP;
	mWall[19][10] = BOUNDARY_CONDITION::NO_SLIP;
	mWall[21][10] = BOUNDARY_CONDITION::NO_SLIP;
}

void	LB::InitDistributions() {
	for (unsigned int x = 0; x < DIM_X; x++)
		for (unsigned int y = 0; y < DIM_Y; y++)
			for (unsigned int i = 0; i < DIM_I; i++) {
				mF[x][y][i] = fEq(i, 1.5, 0.0, 0, 0.00);
				computeVariables(mF[x][y], mRho[x][y], mU[x][y][0], mU[x][y][1], mU2[x][y]);
			}
}

void	LB::Propagate() {
	for (int x = 0; x<DIM_X; x++)
		for (int y = 0; y<DIM_Y; y++)
			for (int i = 0; i < DIM_I; i++) {
				mFTemp[x][y][i] = mF[x][y][i];
				mF[x][y][i] = 0;
			}

	for (int x = 0; x < DIM_X; x++)
		for (int y = 0; y < DIM_Y; y++)
			if (mWall[x][y] == BOUNDARY_CONDITION::FLUID) {
				for (int i = 0; i < DIM_I; i++) {
					int nextX = x + c[i][0];
					int nextY = y + c[i][1];
					if (mWall[nextX][nextY] == BOUNDARY_CONDITION::FLUID)
						mF[nextX][nextY][i] = mFTemp[x][y][i];
					if (mWall[nextX][nextY] == BOUNDARY_CONDITION::NO_SLIP)
						mF[x][y][opposite[i]] = mFTemp[x][y][i];
				}
			}
}

void	LB::DoBoundary() {
	for (int y = 1; y < DIM_Y - 1; y++) {
		ZHPressureWest(mF[1][y], mU[1][y], 2);
		ZHPressureEast(mF[DIM_X - 2][y], mU[DIM_X - 2][y], 1);
	}
}

void	LB::Collide(){
	mRhoTot = 0;
	for (int x = 0; x<DIM_X; x++) {
		for (int y = 0; y<DIM_Y; y++) {
			if (mWall[x][y] == BOUNDARY_CONDITION::FLUID) {
				computeVariables(mF[x][y], mRho[x][y], mU[x][y][0], mU[x][y][1], mU2[x][y]);
				mRhoTot += mRho[x][y];
				for (int i = 0; i < DIM_I; i++) {
					mF[x][y][i] = ( 1. - mOmega )*mF[x][y][i] + mOmega*fEq(i, mRho[x][y], mU[x][y][0], mU[x][y][1], mU2[x][y]);
				}
			}
		}
	}
}

void	LB::Step() {
	Propagate();
	DoBoundary();
	Collide();
}

void	LB::PostProcessing(const std::string& filename) {
	std::ofstream	oFile(filename);
	for (int x = 0; x < DIM_X; x++)
		for (int y = 0; y < DIM_Y; y++)
			oFile << x << "\t" << y << "\t" << mU[x][y][0] << "\t" << mU[x][y][1] << "\t" << mRho[x][y] << std::endl;
	oFile.close();
}