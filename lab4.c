#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

/* ---Used Data---
https://software.intel.com/content/www/us/en/develop/articles/introduction-to-intel-advanced-vector-extensions.html
https://en.wikipedia.org/wiki/Flynn%27s_taxonomy
https://pl.wikibooks.org/wiki/C/Czytanie_i_pisanie_do_plik%C3%B3w

*/
#define TAB_SIZE 8192
#define REPETITION 10
#define TIMES_ARRAY_SIZE 4

clock_t timeOfStart_t, timeOfEnd_t;
double timePassed_t;
double timePassed = 0;

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

//SIMD operations - returning time passed
double additionSIMD(numericVector *setA ,numericVector* setB, int numbers);
double subtractionSIMD(numericVector* setA ,numericVector* setB, int numbers);
double multiplicationSIMD(numericVector* setA ,numericVector* setB, int numbers);
double divisionSIMD(numericVector* setA ,numericVector* setB, int numbers);

//SIMD operations - returning results
numericVector additionSIMDResult(numericVector *setA ,numericVector *setB, int numbers);
numericVector subtractionSIMDResult(numericVector* setA ,numericVector* setB, int numbers);
numericVector multiplicationSIMDResult(numericVector* setA ,numericVector* setB, int numbers);
numericVector divisionSIMDResult(numericVector* setA ,numericVector* setB, int numbers);

//SISD operations - returning time passed
double additionSISD(float *a, float *b, int numbers);
double subtractionSISD(float *a, float *b, int numbers);
double multiplicationSISD(float *a, float *b, int numbers);
double divisionSISD(float *a, float *b, int numbers);

//SISD operations - returning results
float additionSISDResult(float *a, float *b, int numbers);
float subtractionSISDResult(float *a, float *b, int numbers);
float multiplicationSISDResult(float *a, float *b, int numbers);
float divisionSISDResult(float *a, float *b, int numbers);


int main(){
    double times[TIMES_ARRAY_SIZE];
    int numberAmount[] = {2048, 4096, 8192};
    

    srand(time(NULL));
    //generating vectors
    numericVector setA[TAB_SIZE];
    numericVector setB[TAB_SIZE];

    int numberOfNumbers[3] = {2048,4096,8192};

    //testing loop - SIMD
for(int j = 0; j < 3;++j){
    for(int i = 0; i < REPETITION; ++i){
    generaetNumber(setA);
    generaetNumber(setB);
        for(int k = 0; k<numberOfNumbers[j]; ++k){
            additionSIMD(&setA[k], &setB[k], 0);
            times[0] += (double)additionSIMD(&setA[k], &setB[k], 0);
            times[1] += (double)subtractionSIMD(&setA[k], &setB[k], 0);
            times[2] += (double)multiplicationSIMD(&setA[k], &setB[k], 0);
            times[3] += (double)divisionSIMD(&setA[k], &setB[k], 0);
        }
    
    }
    printf("------ %d -------\n", numberOfNumbers[j]);
    printf("Czas trwania dodawania %lf\n",times[0]);
    printf("Czas trwania odejmowania %lf\n",times[1]);
    printf("Czas trwania mnożenia %lf\n",times[2]);
    printf("Czas trwania dzielenia %lf\n",times[3]);
    for(int k = 0; k<4; ++k){
        times[k] = 0;
    }
}

    
    //printVector(setA);
    //printVector(setB);
    //double x = additionSIMD(setA, setB, 4096);
  
    printf("OiAK - Laboratorium 4\n");
    printf("Prowadzacy: mgr. Tomasz Serafin\n");


    return 0;
}

void generaetNumber(numericVector *dataSet){
    for(int i = 0; i<TAB_SIZE; ++i){
    dataSet[i].vecOne = ((float)(rand()%100000));
    dataSet[i].vecTwo = ((float)(rand()%100000));
    dataSet[i].vecThree = ((float)(rand()%100000));
    dataSet[i].vecFour = ((float)(rand()%100000));
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
//SIMD operations - returning time passed
double additionSIMD(numericVector* setA ,numericVector* setB, int numbers){
    numericVector result;

    timeOfStart_t = clock();

    asm(
        "movq %1, %%rax\n"
        "movups (%%rax), %%xmm0\n"
        "movq %2, %%rax\n"
        "movups (%%rax), %%xmm1\n"
        "addps %%xmm1, %%xmm0\n"
        "movups %%xmm0, %0\n"
        :"=g"(result)
        :"g"(setA), "g"(setB)
        :"rax"
    );

    timeOfEnd_t= clock();
    timePassed = (double)(timeOfEnd_t- timeOfStart_t);

    return timePassed;
}
double subtractionSIMD(numericVector* setA ,numericVector* setB, int numbers){
    numericVector result;

    timeOfStart_t = clock();

    asm(
        "movq %1, %%rax\n"
        "movups (%%rax), %%xmm0\n"
        "movq %2, %%rax\n"
        "movups (%%rax), %%xmm1\n"
        "subps %%xmm1, %%xmm0\n"
        "movups %%xmm0, %0\n"
        :"=g"(result)
        :"g"(setA), "g"(setB)
        :"rax"
    );

    timeOfEnd_t= clock();
    timePassed = (double)(timeOfEnd_t - timeOfStart_t);
    
    return timePassed;
}
double multiplicationSIMD(numericVector* setA ,numericVector* setB, int numbers){
    numericVector result;

    timeOfStart_t = clock();

    asm(
        "movq %1, %%rax \n"
		"movups (%%rax), %%xmm0 \n"
		"movq %2, %%rax \n\t"
		"movups (%%rax), %%xmm1 \n"
		"mulps %%xmm1, %%xmm0 \n"
		"movups %%xmm0, %0 \n"
		:"=g"(result)
		:"g"(setA), "g"(setB)
		:"rax"
    );

    timeOfEnd_t = clock();
    timePassed = (double)(timeOfEnd_t - timeOfStart_t);
    
    return timePassed;
}
double divisionSIMD(numericVector* setA ,numericVector *setB, int numbers){
    numericVector result;

    timeOfStart_t = clock();

    asm(
        "movq %1, %%rax\n"
        "movups (%%rax), %%xmm0\n"
        "movq %2, %%rax\n"
        "movups (%%rax), %%xmm1\n"
        "divps %%xmm1, %%xmm0\n"
        "movups %%xmm0, %0\n"
        :"=g"(result)
        :"g"(setA), "g"(setB)
        :"rax"
    );

    timeOfEnd_t = clock();
    timePassed= ((double)(timeOfEnd_t - timeOfStart_t));
    
    return timePassed;
}

//SIMD operations - returning results
numericVector additionSIMDResult(numericVector *setA ,numericVector* setB, int numbers){

}
numericVector subtractionSIMDResult(numericVector* setA ,numericVector* setB, int numbers){

}
numericVector multiplicationSIMDResult(numericVector *setA ,numericVector* setB, int numbers){

}
numericVector divisionSIMDResult(numericVector* setA ,numericVector* setB, int numbers){

}

//SISD operations - returning time passed
double additionSISD(float *a, float *b, int numbers){

}
double subtractionSISD(float *a, float *b, int numbers){

}
double multiplicationSISD(float *a, float *b, int numbers){

}
double divisionSISD(float *a, float *b, int numbers){

}

//SISD operations - returning results
float additionSISDResult(float *a, float *b, int numbers){

}
float subtractionSISDResult(float *a, float *b, int numbers){

}
float multiplicationSISDResult(float *a, float *b, int numbers){

}
float divisionSISDResult(float *a, float *b, int numbers){

}