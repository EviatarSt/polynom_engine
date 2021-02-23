#ifndef _FUNC
#define _FUNC
#include <map>
#include <iostream>



using std::map;
using std::ostream;


void swap(int& p1, int& p2);

class func {
 


 protected:
   
  
  int maxVal_; //maximum of all inputs
  int minVal_; //minimum of all inputs
  map<int,int> fmap_; //holds inputs and corresponding outputs
  void plot(ostream& os) const ; //plot fmap_
  

public:
	func();// the Ctor of the function.
 
  virtual ~func();// the Dtor of the function.
  
	func& operator<<(const int& x);/* operator override. calculates the value of "fx", 
  based on the function, and sets the couple (x, fx) in the map*/
  
	//opertor override. prints the format of func to the ostream ro.
  friend ostream& operator<<(ostream& ro, const func& func);
  
  //printing function. varies by the type of function, and therefore is pure here.
	virtual ostream& print(ostream& ro) const= 0;
 
 //a pure method, to calculate "fx", as mentioned above.
  virtual int calculate(int x)=0;

};


#endif
