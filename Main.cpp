#include	<iostream>
#include	<sstream>

#include	"LB.h"

template<typename T>
const std::string ToString(const T& val) {
	std::stringstream stream;
	stream << val;
	return stream.str();
}

int main() {
	LB	sim(1,1,1,1);
	//for (int i = 0; i < 1000; i++) 
		//sim.Step();
	for (int i = 0; i < 400; i++) {
		sim.PostProcessing(ToString(i) + ".txt");
		sim.Step();
		std::cout << sim.mRhoTot << std::endl;
	}
}