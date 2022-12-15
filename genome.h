using namespace std; 

struct Pixel {//in order to have all the colors in one place 
int red;
int blue;
int green;
};

class genome {
private://initializing the number of genes and the mutation rate, from the gene class
  Pixel* genes; 
  int nGenes;
  double mRate; 
  
public:
    genome(); // constructor
    ~genome(); // destructor
    void allocate(int nGenes);
    void deallocate();
    void randomize();
    void set_red( int index, int value);
    void set_green(int index, int value);
    void set_blue(int index, int value);
    int get_red( int index);
    int get_green( int index);
    int get_blue( int index);
    void print();
  
//*************************************GA2*****************************************************
  void set_mRate(double val); //sets the member variable mRate equal to val
  double get_mRate(); //returns member varaible mRate
  void mutate_gene(int index);
  void mutate();
  double calculate_gene_fitness(int index, Pixel targetPixel);
  double calculate_overall_fitness(Pixel* target, int nPixels);
  void set_pixel(int index, Pixel newPixel);    
  
};
