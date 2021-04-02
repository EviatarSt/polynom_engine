#include "compfunc.h"

using namespace std;

compfunc::compfunc(func& outside, func& inside, char* outerName, char* innerName) :
func(), outer(&outside), inner(&inside), FuncProperty(string(outerName) + "(" + string(innerName) + ")") {
	id = 2;
}

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

string* compfunc::getName() {
	return &FuncProperty;
}
