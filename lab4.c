#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/* ---Used Data---
https://software.intel.com/content/www/us/en/develop/articles/introduction-to-intel-advanced-vector-extensions.html
https://en.wikipedia.org/wiki/Flynn%27s_taxonomy

*/
#define TAB_SIZE 8192
#define REPETITION 100

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
    printf("OiAK - Laboratorium 4\n");
    printf("Prowadzacy: mgr. Tomasz Serafin\n");


    return 0;
}

void generaetNumber(numericVector *dataSet){
    for(int i = 0; i<TAB_SIZE; ++i){
    dataSet[i].vecOne = ((float)(rand()%100000))/((float)(rand()%100000));
    dataSet[i].vecTwo = ((float)(rand()%100000))/((float)(rand()%100000));
    dataSet[i].vecThree = ((float)(rand()%100000))/((float)(rand()%100000));
    dataSet[i].vecFour = ((float)(rand()%100000))/((float)(rand()%100000));
    }
}

 void printVector(numericVector *dataSet){
    for(int i = 0; i<TAB_SIZE; ++i){
        printf("%lf, %lf, %lf, %lf, numer iteracji %d\n",
        dataSet[i].vecOne, 
        dataSet[i].vecTwo, 
        dataSet[i].vecThree, 
        dataSet[i].vecFour, i);
    }
}