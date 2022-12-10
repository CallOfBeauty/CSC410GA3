#include "population.h"

#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;


population::population() {
    individuals = NULL;
    target = NULL;
    n_indi = 0; //number of individuals
}

~population::population() {
    if (individuals != NULL) {
        delete[] individuals;
        individuals = NULL;
        n_indi = 0;}
    if (target_gen != NULL) {//making sure there is nothing in the target genome
        delete[] target_gen;
        target_gen = NULL;}}
        
population::set_target(Pixel* target, int imgsize) {//reaching the target genome for red, green, blue
    this->target_gen = new Pixel[imgsize];
    for (int i = 0; i < imgsize; i++) {
        target[i].red = target[i].red; 
        target[i].green = target[i].green;
        target[i].blue = target[i].blue;}}

population::gen_pop(int size, int nGenes) {//generates the populations, using the size and the previous nGenes
    individuals = new genome*[size];
    n_indi = size; //number of individuals in the population
    for (int i = 0;i < size;i++) {//making the new populations, of size, size
        individuals[i] = new genome ();
        individuals[i].allocate(nGenes);
        individuals[i].randomize();
    }
}


