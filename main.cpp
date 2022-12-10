#include "genome.h"
#include <iostream>
using namespace std; 


int main(){
genome myGenome;
myGenome.print();
  
myGenome.allocate(4);
  
myGenome.print();
  
myGenome.randomize();
  
myGenome.print();
  
myGenome.set_red(1, 2); 
myGenome.set_green(3, 54);
myGenome.set_blue(0,226);
  
myGenome.print();

//**************************GA2*******************************88

genome test_genome;
 
test_genome.set_mRate(2);
test_genome.get_mRate();
cout << endl;
  
return 0;
};



//Unit tests:
