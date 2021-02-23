#ifndef _POLY_F
#define _POLY_F

#include "func.h"

using namespace std;


class polynom : public func {
 public:

  void printcoefs(ostream&)  const ;//prints the array coefs_ on the ostream, in the format of a polynom

  polynom(int order, int* coefs); //a Ctor of polynom, using given order and array of values.

  polynom(const polynom& OldOne);//a Ctor of polynom, using given parameters of another polynom

  virtual ~polynom();//the Dtor. frees the allocated array of the polynom.

  polynom Derivative();//returns the polynom, that is the Derivative of the invoking polynom

  polynom Integral();//returns the polynom, that is the Integral of the invoking polynom.

  polynom operator+(const polynom& OtherPol);//overrides the '+' sign, for polynom summation. returns the result as a polynom.

  polynom operator-(const polynom& OtherPol);//overrides the '-' sign, for polynom subtraction. returns the result as a polynom.

  polynom operator*(const polynom& OtherPol);//overrides the '*' sign, for polynom multiplication. returns the result as a polynom.

  virtual ostream& print(ostream& ro) const;// prints the polynom by given format, including a plot.
  
  virtual int calculate(int x);//calculates what is "fx", if x is the parameter in the polynom. returns an integer.

  protected:

  int n_; //order of the polynom
  int* coefs_; //coefficients 

};



#endif
 
