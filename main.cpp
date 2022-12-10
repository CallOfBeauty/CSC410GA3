#include "genome.h"
#include <iostream>
#include <cmath>

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

 
genome::Pixel* mypixel = new genome::Pixel[3];

mypixel[0].red = 212;
mypixel[0].green = 31;
mypixel[0].blue = 0;
mypixel[1].red = 0;
mypixel[1].green = 0;
mypixel[1].blue = 22;
double gen = myGenome.calculate_overall_fitness(mypixel, 2);

cout<<gen<<endl;
  
return 0;
}



//Unit tests:
