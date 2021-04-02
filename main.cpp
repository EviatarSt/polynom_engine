#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <stdexcept>
#include "func.h"
#include "polynom.h"
#include "compfunc.h"

using namespace std;

const int MAXLINE = 256;



int main() {
   map<string,func*> func_list;
  char func_cmd[MAXLINE], func_name[MAXLINE], func_value[MAXLINE];
  char* token;
  
 
  while(!cin.eof()) {
      cin >> func_cmd >> func_name >> func_value;
    if (!strcmp(func_cmd, "//")) {
      continue;
    }
    
    if (!strcmp(func_cmd, "SetPolynom")) {
      int order;
      int* coefs;
      token = strtok(func_value, ",");
      order = atoi(token);
      token = strtok(NULL, ",");
      coefs= new int[order+1];
      for(auto i=0; i<=order && token; i++) {
	coefs[i] = atof(token);
	token = strtok(NULL, ",");

      }
      func_list[func_name]=new polynom(order,coefs);
      delete [] coefs;
    }
   
    if (!strcmp(func_cmd, "SetCompFunc")) {
      func* outer;
      func* inner;
      char* outer_name = strtok(func_value, ",");
      char* inner_name = strtok(NULL, ","); 
      
      try{
	outer = func_list.at(outer_name);
	inner = func_list.at(inner_name);
	func_list[func_name]=new compfunc(*outer,*inner, outer_name, inner_name);
      }
      catch(exception& e){
	cout<<"Error SetCompFunc:"<< e.what()<< endl;
      }
    }
    if (!strcmp(func_cmd, "AddPoint")) {
      
      token = strtok(func_value, ",");
      
      try{
	*(func_list.at(func_name))<< atoi(token);
      }
      catch(exception& e){
	cout<<"Error AddPoint 1:"<< e.what()<< endl;
      }
      while((token = strtok(NULL, ",")) != NULL){
	try{
	  *(func_list.at(func_name))<< atoi(token);
	}
	catch(exception& e){
	  cout<<"Error AddPoint 2:"<< e.what()<< endl;
	  
	}
      }
    }
    
    if (!strcmp(func_cmd, "MathPolynom")) {
      char *Op;
      polynom *f1,*f2;
      try{

	token = strtok(func_value, ",");

	f1 = (polynom*)func_list.at(token);
	Op = strtok(NULL, ",");

	token = strtok(NULL, ",");



	f2 = (polynom*)func_list.at(token);

	switch(*Op){
	case '+':
	  func_list[func_name]=new polynom((*f1)+(*f2));
	  break;
	case '-':
	  func_list[func_name]=new polynom((*f1)-(*f2));
	  break;
	case '*':
	  func_list[func_name]=new polynom((*f1)*(*f2));

	  break;
	}
      }
      catch(exception& e){
	cout<<"Error MathPolynom: "<< e.what()<< endl;
      }
    }

    

    if (!strcmp(func_cmd, "Print")) {
  
      if (strcmp(func_name, "All")){//not all
	try{
        if((func_list[func_name]->getID()) == 1){ 
            cout << func_name << "(x)=" << *(func_list[func_name]) << endl; }
        else if ((func_list[func_name]->getID()) == 2) {
            compfunc* temp = (compfunc*)func_list[func_name];
            cout << *(temp->getName()) << "(x)=" << *temp << endl;
        }
	}
	catch(exception& e){
	  cout<<"Error Print:"<< e.what()<< endl;
	}
      }
      else{
	for (auto it : func_list){
        if((it.second->getID()) == 1){
            cout << it.first << "(x)=" << *(it.second) << endl;
        }
        else if ((it.second->getID()) == 2) {
            compfunc* temp = (compfunc*)it.second;
            cout << *(temp->getName()) << "(x)=" << *temp << endl;
        }
	  
	}
      }
    }
  }
  for (auto it : func_list){

    delete it.second;
  }
  return 0;
}
