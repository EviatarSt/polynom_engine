#include "compfunc.h"

using namespace std;

compfunc::compfunc(func& outside, func& inside) : 
func(), outer(&outside), inner(&inside) {}

compfunc::~compfunc() {}

int compfunc::calculate(int x) {
	int y = (*inner).calculate(x);
	return outer->calculate(y);
}

ostream& compfunc::print(ostream& ro) const{
  ro << endl;
  plot(ro);
	return ro;
}