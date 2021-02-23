#include "polynom.h"
#include <math.h>

using namespace std;


polynom::polynom(int order, int* coef_) : 
    func(), n_(order){
    coefs_ = new int[n_ + 1];
    for (int i = 0; i <= n_; i++) {
        coefs_[i] = coef_[i];
    }
}


polynom::polynom(const polynom& OldOne) : 
    func(), n_(OldOne.n_) {
    coefs_ = new int[n_ + 1];
    for (int i = 0; i <= n_; i++) {
        coefs_[i] = OldOne.coefs_[i];
    }
}


polynom::~polynom() { delete[] coefs_; }


int polynom::calculate(int x){
    int sum = 0;
    int index = 1;
    for (int i = 0; i <= n_; i++) {
        index = (int)pow((double)x, (double)i);
        sum += coefs_[i] * index;
        index = 1;
    }
    return sum;
}


polynom polynom::operator+(const polynom& OtherPol){
    int SumOrder = (OtherPol.n_ <= n_) ? n_ : OtherPol.n_;
    if (OtherPol.n_ == n_) {
        while ((SumOrder > 0) && ((OtherPol.coefs_[SumOrder-1] + coefs_[SumOrder-1]) == 0)) {
            SumOrder--;
        }
    }
    int* SumCoefs = new int[SumOrder + 1];
    for (int i = 0; i <= SumOrder; i++) { SumCoefs[i] = 0; }
    for (int i = 0; i <= SumOrder; i++) {
        if (i > n_) {
            SumCoefs[i] = OtherPol.coefs_[i];
            continue;
        }
        if (i > OtherPol.n_) {
            SumCoefs[i] = coefs_[i];
            continue;
        }
        SumCoefs[i] = OtherPol.coefs_[i] + coefs_[i];
    }
    polynom NewPol(SumOrder, SumCoefs);
    delete[] SumCoefs;
    return NewPol;
}


polynom polynom::operator-(const polynom& OtherPol) {
    int SumOrder = (OtherPol.n_ <= n_) ? n_ : OtherPol.n_;
    if (OtherPol.n_ == n_) {
        while ((SumOrder > 0) && ((coefs_[SumOrder - 1] - OtherPol.coefs_[SumOrder - 1]) == 0)) {
            SumOrder--;
        }
    }
    int* SumCoefs = new int[SumOrder + 1];
    for (int i = 0; i <= SumOrder; i++) {
        if (!coefs_[i]) {
            SumCoefs[i] = -(OtherPol.coefs_[i]);
            continue;
        }
        if (!OtherPol.coefs_[i]) {
            SumCoefs[i] = coefs_[i];
            continue;
        }
        SumCoefs[i] = coefs_[i] - OtherPol.coefs_[i];
    }
    polynom NewPol(SumOrder, SumCoefs);
    delete[] SumCoefs;
    return NewPol;
}


polynom polynom::operator*(const polynom& OtherPol) {
    int NewOrder = n_ + OtherPol.n_;
    if ((n_ == 0) || (OtherPol.n_ == 0)) {
        int check = (n_ == 0) ? coefs_[0] : OtherPol.coefs_[0];
        if (check == 0) {
            int* zero = new int[1];
            zero[0] = 0;
            polynom small(0, zero);
            delete[] zero;
            return small;
        }
    }
    int* NewCoef = new int[NewOrder + 1];
    for (int i = 0; i <= NewOrder; i++) { NewCoef[i] = 0; }
    for (int i = 0; i <= n_; i++) {
        for (int j = 0; j <= OtherPol.n_; j++) {
            NewCoef[i + j] += coefs_[i] * OtherPol.coefs_[j];
        }
    }
    polynom conclude(NewOrder, NewCoef);
    delete[] NewCoef;
    return conclude;
}

polynom polynom::Derivative() {
        if (n_ == 0){int NewCoef[1] = { 0 };
          polynom NewPol(n_, NewCoef);
          return NewPol;
        }
    int NewCoef[n_];
    for (int i = 1; i <= n_; i++) {
        NewCoef[i - 1] = i * coefs_[i];
    }
    polynom NewPol((n_- 1), NewCoef);
    return NewPol;
}

polynom polynom::Integral() {
    int* NewCoef = new int[n_ + 2];
    for (int i = 0; i <= n_; i++) {
        NewCoef[i + 1] = coefs_[i] / (i+1);
    }
    NewCoef[0] = 0;
    polynom NewPol((n_ + 1), NewCoef);
    delete[] NewCoef;
    return NewPol;
}

ostream& polynom::print(ostream& ro) const {
    polynom* temp = new polynom(*this);
    printcoefs(ro);
    ro << endl;
    polynom* der = new polynom((*temp).Derivative());
    polynom* Integ = new polynom((*temp).Integral());
    delete temp;
    ro << "Derivative: ";
    (*der).printcoefs(ro);
    ro << endl;
    ro << "Integral: ";
    (*Integ).printcoefs(ro);
    cout<< "+C" << endl;
    if(fmap_.size() >=1){plot(ro);}
    delete der;
    delete Integ;
    return ro;
}


void polynom::printcoefs(ostream& os)  const {
  int allZero = 1;
  for (auto i = n_ ; i>=0; i--) {
    if (coefs_[i]>0) {
      allZero = 0;
      if(i!=n_){
	os << "+";
      }
      if (coefs_[i]!=1 || i==0){
	os << coefs_[i];
      }
      if(i>0) {
	os << "x";
	if (i>1) 
	  os << "^" << i ;
      }
    }
    else if(coefs_[i]<0) {
      allZero = 0;
      if (coefs_[i]!=-1 || i==0){
	os << coefs_[i];
      }
      else 
	os << "-";
      if(i>0) {
	os << "x";
	if (i>1) 
	  os << "^" << i ;
      }
    }
    else if(i==0 && allZero == 1){ //coefs_[i]==0
        os << "0";
	continue;
    }
  }
}
