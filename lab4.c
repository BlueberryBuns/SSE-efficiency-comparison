#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/* ---Used Data---
https://software.intel.com/content/www/us/en/develop/articles/introduction-to-intel-advanced-vector-extensions.html
https://en.wikipedia.org/wiki/Flynn%27s_taxonomy

*/
#define TAB_SIZE 8192; 
double time_passed;


// Initialising the struct of 128-bit vector
typedef struct{
    float vecOne;
    float vecTwo;
    float vecThree;
    float vecFour;
}numericVector;

//filling vectors with randomly generated data
void generaetNumber(numericVector *dataSet);

//printing the vector
void printVector(numericVector *dataSet);


int main(){
    srand(time(NULL));
    numericVector setA[TAB_SIZE];
    numericVector setB[TAB_SIZE];
    generaetNumber(setA);
    generaetNumber(setB);
    printVector(setA);
    printVector(setB);
    println("OiAK - Laboratorium 4");
    println("Prowadzacy: mgr. Tomasz Serafin");


    return 0;
}

void generaetNumber(numericVector *dataSet){
    dataSet->vecOne = (double)(rand()%10E3);
    dataSet->vecTwo = (double)(rand()%10E3);
    dataSet->vecThree = (double)(rand()%10E3);
    dataSet->vecFour = (double)(rand()%10E3);
}

 void printVector(numericVector *dataSet){
    for(int i = 0; i<TAB_SIZE; ++i){
        println(dataSet[i]);
    }
}