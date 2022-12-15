#include "genome.h"

// The population class represents a collection of genomes.
class population {
private:
	// An array of pointers to genomes.
	genome** individuals;

	// The target genome that the population is trying to evolve towards.
	genome::Pixel* targetGenome;

	// The number of individuals in the population.
	int nIndividuals;

	// The indexes of the two selected parents.
	int parent_1, parent_2;

	// The number of crossovers to perform during reproduction.
	int nCrossover;

	// Perform a crossover operation between the individuals at index idx and iOffspring.
	void crossover(int idx, int iOffspring);

public:
	// Construct a new population.
	population();

	// Destroy the population.
	~population();

	// Generate a population of size popSize and with nGenes genes per individual.
	void generate_population(int popSize, int nGenes);

	// Set the target genome that the population is trying to evolve towards.
	void set_target(genome::Pixel* target, int imageSize);

	// Select two parents for reproduction.
	void select_parents();

	// Set the number of crossovers to perform during reproduction.
	void set_nCrossover(int nCrossover);

	// Get the number of crossovers to perform during reproduction.
	int get_nCrossover();

	// Set the mutation rate for all individuals in the population.
	void set_mutation(double mRate);

	// Generate a new population by performing reproduction and mutation.
	void generate_new_population(int useRoulette);

	// Calculate the overall fitness of the population.
	double calculate_overall_fitness();

	// Print the parents that have been selected for reproduction.
	void print_parents();

	// Print the individuals in the population.
	void print_population();
};
