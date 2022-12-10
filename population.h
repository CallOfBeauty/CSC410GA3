#include "genome.h"

class population {
    
public:
    struct Pixel {
        int red;
        int green;
        int blue;
    }

    population();
    ~population();
    void gen_pop(int popSize, int nGenes);
    void set_target(Pixel* target, int imageSize);
    void select_parents();
    void set_nCrossover(int nCrossover);
    int get_nCrossover();
    void set_mutation(double mRate);
    void generate_new_population(int useRoulette);
    double calculate_overall_fitness();
    void print_parents();
    void print_population();

private:
    genome** individuals;
    Pixel* targetGenome;
    int nIndividuals;

};

