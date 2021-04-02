#include "func.h"
#include<vector>

using namespace std;
using std::vector;

func::func(){
    minVal_ = 100;
    maxVal_ = -100;
    id = 0;
}

func::~func(){}



func& func::operator<<(const double& x) {
    int fx = calculate(x);
    fmap_[x] = fx;
    int MapSize = fmap_.size();
    if (MapSize == 1) {
        maxVal_ = x;
        minVal_ = x;
        return *this;
    }
    if (x > maxVal_) { maxVal_ = x; }
    if (x < minVal_) { minVal_ = x; }
    return *this;
}


ostream& operator<<(ostream& ro, const func& fu){
    fu.print(ro);
    return ro;
}



void func::plot(ostream& os) const {
 
  vector<int> sortImage;
    
  sortImage.clear();
  for ( auto it : fmap_){
      //complete code here: insert the image of the function into sortImage 
      sortImage.push_back(it.second);
  }
  //complete code here: sort sortImage
  int MapSize = fmap_.size();
  int temp = 0;
  for (int i = 0; i < MapSize; i++) {
    for (int j = 0;j < (MapSize-1); j++){
      if (sortImage.at(j) > sortImage.at(j+1)){
        temp = sortImage[j];
        sortImage[j] = sortImage[j + 1];
        sortImage[j + 1] = temp;
      }
    }
  }
  //complete code here: flip sortImage (reverse)
  int stop = MapSize / 2;
  for (int i = 0; i < stop; i++) {
        temp = sortImage[i];
        sortImage[i] = sortImage[MapSize - i-1];
        sortImage[MapSize - i-1] = temp;

  }
  for ( auto it_im = sortImage.begin();
       it_im != sortImage.end(); ++it_im) {
    if(it_im!=sortImage.begin() && *it_im==*(it_im-1)){ //remove repeated
      it_im = sortImage.erase(it_im-1);
      
    }
  }
 
  for (auto it_im = sortImage.begin();
       it_im != sortImage.end(); ++it_im) {
    int x_anchor=minVal_;
    if(*it_im<-9) 
      os <<*it_im;
    else
      if((*it_im<0) || (*it_im>9)) 
	os<<" "<<*it_im;
      else 
	os<<"  "<<*it_im;
    
    for (auto it_dom : fmap_) {
      if(it_dom.second == *it_im){
	int x=it_dom.first;
	int spaces= x-x_anchor;
	int i=0;
	while(i<spaces){
	  os<<"   ";
	  i++;
	}
	os<<"*  ";
	x_anchor=x+1;
      }

    }

    os<<endl;
    if((it_im+1)!=sortImage.end()){ //print empty lines
      int lines=*it_im-*(it_im+1)-1;
      int i=1;
      
      while(i<lines+1){
	if(*it_im-i<-9) 
	  os <<*it_im-i;
	else 
	  if( (*it_im-i<0) || (*it_im-i>9) )
	    os<<" "<<*it_im-i;
	  else 
	    os<<"  "<<*it_im-i;
	cout<<endl;
	i++;

      }
    }

  }//for sortImage

  //print x axis
  cout<< " ";
  for (auto i=minVal_; i<maxVal_+1;i++){
    if(i<0) os<<" "<<i;
    else os<<"  "<<i;
  
}
  os<<endl;
}
