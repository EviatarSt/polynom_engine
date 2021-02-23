#ifndef _COMPFUNC_f
#define _COMPFUNC_F

#include "func.h"

using namespace std;

class compfunc : public func {
public:
	/**
 * @brief Ctor of compfunc.
 * parameters: two functions, outer and inner.
 */
  compfunc(func& outer, func& inner);
	
  /**
 * @brief Dtor. doesn't need much, compfunc has no allocated memory of its own.
 */
	~compfunc();
	
  /**
 * @brief this method will calculate the value of x, when used in its polynomos.
 */
	virtual int calculate(int x);

protected:
  /**
 * @brief this method will print the compfunc, using the given format.
 */
	virtual ostream& print(ostream& ro) const;
 

	func* outer;

	func* inner;
};
#endif