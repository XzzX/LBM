#ifndef LB_H_INCLUDED
#define LB_H_INCLUDED

#include	<stdint.h>
#include	<string>

class LB {
public:
	enum class BOUNDARY_CONDITION {
		FLUID,
		NO_SLIP,
		FREE_SLIP,
		INFLOW
	};

	static const uint32_t DIM_X = 60;
	static const uint32_t DIM_Y = 20;
	static const uint32_t DIM_I = 9;

	static const double	c[DIM_I][2];
	static const int	opposite[DIM_I];
	static const double t[DIM_I];

	double	mF[DIM_X][DIM_Y][DIM_I];
	double	mFTemp[DIM_X][DIM_Y][DIM_I];
	double	mRho[DIM_X][DIM_Y];
	double	mU[DIM_X][DIM_Y][2];
	double	mU2[DIM_X][DIM_Y];
	double	mXMax;
	double	mYMax;
	double	mTau;
	double	mTPostProcessing;
	double	mOmega = 1;
	double	mRhoTot = 0;
	BOUNDARY_CONDITION	mWall[DIM_X][DIM_Y];

	LB(const double xMax, const double yMax, const double tau, const double tPostProcessing);
	~LB();

	void	Step();
	void	PostProcessing(const std::string& filename);

private:
	void	computeVariables(const double f[DIM_I], double& rho, double& ux, double& uy, double& uSqr);
	double	fEq(const int iF, const double rho, const double ux, const double uy, const double uSqr);

	void	InitWall();
	void	EqDistribution(const double rho, const double u);
	void	InitDistributions();

	void	Propagate();
	void	DoBoundary();
	void	Collide();
};

#endif // !LB_H_INCLUDED