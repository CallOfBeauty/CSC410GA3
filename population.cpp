#include "population.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;


population::population() { //initializing the individuals, along with the parents 1 and 2
    individuals = nullptr;
    targetGenome = nullptr;
    nIndividuals = 0;
    nCrossover = 1; // the start value is 1
    parent_1 = -1; //giving them non real values
    parent_2 = -1;
}


population::~population() {
    // Free memory for individuals array
    if (individuals != nullptr) {
        delete[] individuals;
        individuals = nullptr;
        nIndividuals = 0;
    }

    // Free memory for targetGenome array
    if (targetGenome != nullptr) {
        delete[] targetGenome;
        targetGenome = nullptr;
    }
}

void population::generate_population(int popSize, int nGenes) {
    // Create array of genome objects
    individuals = new genome * [popSize];
    nIndividuals = popSize;

    // Generate genome objects and randomize them
    for (int i = 0; i < popSize; i++) {
        individuals[i] = new genome();
        individuals[i]->allocate(nGenes); // create base pixel array for genome
        individuals[i]->randomize(); // randomize pixel array
    }
}


void population::set_target(genome::Pixel* target, int imageSize) {
    // Create pixel array
    this->targetGenome = new genome::Pixel[imageSize];

    // Iterate over target pixel array and copy RGB values to targetGenome array
    for (int i = 0; i < imageSize; i++) {
        targetGenome[i].red = target[i].red;
        targetGenome[i].green = target[i].green;
        targetGenome[i].blue = target[i].blue;
    }
}

void population::select_parents() {
    // Initialize top_primary and top_secondary to the maximum possible fitness value
    double top_primary = 1.0;
    double top_secondary = 1.0;

    int top_primary_idx = 0;
    int top_secondary_idx = 0;

    // Iterate over individuals and find the first and second best fitness values
    for (int i = 0; i < this->nIndividuals; i++) {
        int nPixels = individuals[i]->get_ngenes();

        // Calculate fitness for current genome
        double cur_fitness = individuals[i]->calculate_overall_fitness(targetGenome, nPixels);

        // If current fitness is less than or equal to the first best value, update first best value and index
        if (cur_fitness <= top_primary) {
            top_primary_idx = i;
            top_primary = cur_fitness;
        }

        // If current fitness is less than or equal to the second best value but greater than the first best value and not the same as the first best index, update second best value and index
        if (cur_fitness <= top_secondary && cur_fitness >= top_primary && i != top_primary_idx) {
            top_secondary_idx = i;
            top_secondary = cur_fitness;
        }
    }

    // Save the first and second best fitness values as the selected parents
    this->parent_1 = top_primary_idx;
    this->parent_2 = top_secondary_idx;
}


void population::set_nCrossover(int nCrossover) {
    this->nCrossover = nCrossover;
}

int population::get_nCrossover() {
    return this->nCrossover;
}

void population::set_mutation(double mRate) {
    // Set mutation rate for each individual in the population
    for (int i = 0; i < this->nIndividuals; i++) {
        individuals[i]->set_mRate(mRate);
    }
}

void population::crossover(int idx, int iOffspring) {
    int nGenes = individuals[idx]->get_ngenes();

    // Calculate size of partitions
    // There will be nCrossover + 1 partitions
    // The last partition may be a bit longer if the division is uneven
    int size = (int)(nGenes / (this->nCrossover + 1));

    // Initialize left and right boundaries for the first partition
    int l = 0;
    int r = l + size - 1;

    // Initialize current parent to the first parent
    int cur_parent = this->parent_1;

    // If this is the second offspring, swap starting parent
    if (iOffspring == 1) {
        cur_parent = this->parent_1;
    }
    else if (iOffspring == 2) {
        cur_parent = this->parent_2;
    }

    // Continue until right boundary is beyond the last gene
    while (r < nGenes) {
        // Iterate over current partition and set genes of current individual to parent's genes
        for (int i = l; i <= r; i++) {
            individuals[idx]->set_pixel(i, individuals[cur_parent]->get_pixel(i));
        }

        // Shift left boundary to right boundary for next partition
        l = r + 1;

        // Check if right boundary has evenly ended at the last gene
        // If so, terminate the loop
        if (r == nGenes - 1) {
            r++;
        }
        // If right boundary has ended unevenly, assign right boundary to the last gene
        else if (r + size > nGenes) {
            r = nGenes - 1;
            // No need to swap parent because it is still the same partition
        }
        // Otherwise, increment right boundary by size of partition
        // Also swap parents who will share the genes
        else {
            r += size;
            if (cur_parent == parent_1) {
                cur_parent = parent_2;
            }
            else if (cur_parent == parent_2) {
                cur_parent = parent_1;
            }
        }
    }
}

void population::generate_new_population(int useRoulette) {
// Determine two best fitting individuals
    select_parents();

    // Counter for crossover offsprings
    int child = 1;

    // Iterate over individuals
    for (int i = 0; i < nIndividuals; i++) {
        // Skip the first and second best individuals, as they will be preserved in the next generation
        if (i != this->parent_1 && i != this->parent_2) {
            // Perform crossover for the first two offspring
            if (child <= 2) {
                crossover(i, child);
                child++;
            }
            else {
                // Mutate other individuals
                individuals[i]->mutate();
            }
        }
    }
}


double population::calculate_overall_fitness() {
    double avg = 0.0;

    // Sum up the average fitness for each individual
    for (int i = 0; i < nIndividuals; i++) {
        int nPixels = individuals[i]->get_ngenes();
        double fitness = individuals[i]->calculate_overall_fitness(this->targetGenome, nPixels);
        avg += fitness;
    }

    // Return average fitness
    return avg / nIndividuals;
}



void population::print_parents() {
    // Check if parents have been selected
    if (parent_1 == -1 && parent_2 == -1) {
        cout << "no selected parents" << endl;
    }
    else {
        // Print indices of selected parents
        cout << "parent 1 is " << parent_1 << endl;
        cout << "parent 2 is " << parent_2 << endl;
    }
}

void population::print_population() {
    // Print number of crossover points
    cout << "Crossovers:  " << nCrossover << endl;

    // Iterate over individuals
    for (int i = 0; i < nIndividuals; i++) {
        // Print individual index and mutation rate
        cout << "Individuals:  " << i << endl;
        cout << "mutation rate:  " << individuals[i]->get_mRate() << endl;

        // Print genome as an array of pixels
        cout << "[";
        for (int j = 0; j < individuals[i]->get_ngenes(); j++) {
            cout << "{";
            cout << individuals[i]->get_red(j) << ",";
            cout << individuals[i]->get_green(j) << ",";
            cout << individuals[i]->get_blue(j) << "}";
        }
        cout << "]" << endl;

        // Print separator line
        cout << "********************************************************************" << endl;
    }
}
