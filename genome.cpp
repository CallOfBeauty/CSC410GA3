#include "genome.h"
#include <iostream>

using namespace std;



genome::genome() { //This function initialized genes to Null and sets nGenes to 0 (constructor)
        genes = NULL;
        nGenes = 0;
        };

genome::~genome(){//This function deletes the space we assigned to genes (destructor)
      deallocate();
    };


void genome::allocate(int nGenes){//This function allocates an npixel sized array of RGB pixel values, that are initialized to 0
        if (this->genes !=NULL){ //checking if the array already exists
            deallocate();}
        genes = new Pixel[nGenes]; //allocating new pixel dynamic array
        this -> nGenes = nGenes;};
        
        
void genome:: deallocate(){//This function deletes the space in genes
      if (this->genes == NULL){ 
        return; // break
      }
      else{
       delete[]this-> genes;
       this-> genes = NULL;
       nGenes = 0;
    }}


    
void genome::randomize(){ //this function sets random values between 0 and 256 for each of the Red, Blue, and Green variables for each Pixel in the genes array
       for (int i =0; i<nGenes; i++){
        set_red(i, rand() %257); //generates random number
        set_green(i, rand() %257);
        set_blue(i, rand() %257);
      }}
   
   
void genome:: set_red( int index, int value){//finds the Pixel at index and sets Red
        this->genes[index].red = value;
    }
    
    
void genome:: set_green( int index, int value){//finds the Pixel at index and sets green
       this-> genes[index].green = value;
    }

void genome:: set_blue( int index, int value){//finds the Pixel at index and sets blue
       this->genes[index].blue = value;
    }
    
int genome::get_red( int index){// returns the red value of the Pixel at index, and -1 if it is invalid
      if (index<0 || index >nGenes){ 
        return -1;}
          return this->genes[index].red;}

int genome::get_green( int index){// returns the green value of the Pixel at index, and -1 if it is invalid
      if (index<0 || index >nGenes){ 
        return -1;}
          return this->genes[index].green;}
    
    
int genome::get_blue( int index){// returns the blue value of the Pixel at index, and -1 if it is invalid
      if (index<0 || index >nGenes){ 
        return -1;}
          return this->genes[index].blue;}


void genome:: print(){//function that will output the genes in a readable way to the console
     for (int i=0; i<nGenes; i++){ 
      cout << "The genome is"<< this->nGenes << " genes" << "(" << this->genes[i].red << "," << this->genes[i].green<< "," <<this->genes[i].blue<<")"<< endl;}}




//Implementation for GA2 **********************************************************
//*********************************************************************************
//*********************************************************************************

void genome::set_mRate(double val){ //it sets the member variable mRate, equal to val, if that val is valid (between 0 and 1, inclusive)
    if (val<=1 && val>=0){mRate=val;}    
    }  
    

double genome::get_mRate(){ //a function that returns the value of mRate
return mRate;}
    
void genome::mutate_gene(int index){ //for every colout in the Pixel at index, first calculates a randomly generated number between zero and one. If it is less than mRate, it assigns a random value between 0 and 255 to that colour
#generating nambers  
double temp_red = (double)rand() / (double)RAND_MAX ;
if (temp_red < mRate){this->genes[index].red = random() %256;}
double temp_green = (double)rand() / (double)RAND_MAX ;
if (temp_green < mRate){this->genes[index].green = random() %256;}
double temp_blue = (double)rand() / (double)RAND_MAX ; 
if (temp_blue < mRate){this->genes[index].blue = random() %256;}
 }

    
void genome::mutate(){ //this function traverses through the entire genes array and calls the mutate gene function on every element.
    for (int i=0, i<nGenes; i++){
    mutate_gene(i);}
    cout <<"New gene"<<endl;
    };
    
    
double genome::calculate_gene_fitness(int index, Pixel targetPixel){ //this function calculated the average difference between the target and the pixel values and return the percentage of the average difference
    double reddif;
    double greendif;
    double bluedif;
    double average_sum;
    
    reddif= targetPixel.red - this->genes[index].red;
    greendif= targetPixel.green - this->genes[index].green;
    bluedif= targetPixel.blue - this->genes[index].red;
    
    
    average_sum=(abs(reddif)+abd(greendif)+abd(bluedif))/3;
    average_sum=(average_sum/255.0)*100;

    return average_sum;
    };
    

double genome::calculate_overall_fitness(Pixel* target, int nPixels){ //takes the genome sequence that should be produced, and compares it with what was actually produced. It calculates the difference on each pixel and finds the average difference between the target and the actual sequence.
    if (nPixels == this->nGenes){
        double sum = 0;
        for(int i = 0; i < nPixels; i ++){
            double dif = calculate_gene_fitness(i, target[i]);
            sum += dif;}
        double fitness = sum/nPixels;
        return fitness;}
        else{return 0;};
};
    
    
void genome::set_pixel(int index, Pixel newPixel)//This function takes the newPixel and sets the Pixel at position of the index equal to it. It also makes sure that the index and the red green and ble values are valid.
    if (index>=0 && index<this->nGenes){
    if (0 <= newPixel.red && newPixel.red < 256){
            this->genes[index].red = newPixel.red;};
    if (0 <= newPixel.green && newPixel.green < 256){
            this->genes[index].green = newPixel.green;};
    if (0 <= newPixel.blue && newPixel.blue < 256){
            this->genes[index].blue = newPixel.blue;};}
};    
    

