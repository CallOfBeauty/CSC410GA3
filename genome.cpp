#include "genome.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;



genome::genome() { //This function initialized genes to Null and sets nGenes to 0 (constructor)
        genes = NULL;
        nGenes = 0;
        mRate = 0;//initializing the mutation rate at 0
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
    
    
double genome::calculate_gene_fitness(int index, Pixel targetPixel) {
  // Calculate the average percent difference of the RGB values between 
  // targetPixel and genes[index].

  double red_d = targetPixel.red - this->genes[index].red;
  double green_d = targetPixel.green - this->genes[index].green;
  double blue_d = targetPixel.blue - this->genes[index].blue;

  // Calculate the sum of the absolute differences in the RGB values.
  double avg = 0;
  avg += abs(red_d) + abs(green_d) + abs(blue_d);

  // Calculate the average sum.
  double av_diff = (avg / 3)/255.0;

  // Calculate the percent average difference.
  double diff = av_diff* 100;
  return diff;
}
    


double genome::calculate_overall_fitness(Pixel* target, int nPixels) {
  // Calculate the overall fitness. If nPixels is not equal to nGenes, 
  // return 0.
  if (nPixels == nGenes) {
    double sum_diff = 0;
    for (int i = 0; i < nPixels; i++) {
      // Calculate the fitness of the gene at index i.
      double diff = calculate_gene_fitness(i, target[i]);
      sum_diff += diff;
    }

    // Calculate the average fitness.
    double overall_fitness = sum_diff / nPixels;
    return overall_fitness;
  } else {
    return 0;
  }
}
    
    
void genome::set_pixel(int index, Pixel newPixel) {
  // Check if the index is valid (between 0 and the number of genes - 1).
  if (index >= 0 && index <= nGenes - 1) {
    // Check that the red, green, and blue values of the newPixel are valid.
    if (newPixel.red >= 0 && newPixel.red <= 255) {
      // Set the red value of the gene at position index to the red value of the newPixel.
      this->genes[index].red = newPixel.red;
    }
    if (newPixel.green >= 0 && newPixel.green <= 255) {
      // Set the green value of the gene at position index to the green value of the newPixel.
      this->genes[index].green = newPixel.green;
    }
    if (newPixel.blue >= 0 && newPixel.blue <= 255) {
      // Set the blue value of the gene at position index to the blue value of the newPixel.
      this->genes[index].blue = newPixel.blue;
    }
  }
}
//tests*********************************

void genome::test_set_mRate(double testing, double real) {
  // Compare the testing_value to the expected_value.
  if (testing == real) {
    cout << "psdd" << endl;
  } else {
    cout << "fail" << endl;
  }
}



    

