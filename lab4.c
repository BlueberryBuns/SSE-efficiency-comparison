#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

/* ---Used Data---
https://software.intel.com/content/www/us/en/develop/articles/introduction-to-intel-advanced-vector-extensions.html
https://en.wikipedia.org/wiki/Flynn%27s_taxonomy
https://pl.wikibooks.org/wiki/C/Czytanie_i_pisanie_do_plik%C3%B3w

*/

#define TAB_SIZE 2048
#define REPETITION 100
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
double additionSIMD(numericVector *setA ,numericVector* setB);
double subtractionSIMD(numericVector* setA ,numericVector* setB);
double multiplicationSIMD(numericVector* setA ,numericVector* setB);
double divisionSIMD(numericVector* setA ,numericVector* setB);

//SIMD operations - returning results
numericVector additionSIMDResult(numericVector *setA ,numericVector *setB);
numericVector subtractionSIMDResult(numericVector* setA ,numericVector* setB);
numericVector multiplicationSIMDResult(numericVector* setA ,numericVector* setB);
numericVector divisionSIMDResult(numericVector* setA ,numericVector* setB);

//SISD operations - returning time passed
double additionSISD(float *a, float *b);
double subtractionSISD(float *a, float *b);
double multiplicationSISD(float *a, float *b);
double divisionSISD(float *a, float *b);

//SISD operations - returning results
float additionSISDResult(float *a, float *b);
float subtractionSISDResult(float *a, float *b);
float multiplicationSISDResult(float *a, float *b);
float divisionSISDResult(float *a, float *b);


int main(){
    FILE *f;
    f = fopen("result.txt", "w");

    double times[TIMES_ARRAY_SIZE];
    for(int i=0;i<TIMES_ARRAY_SIZE;++i){
        times[i] =0;
    }
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
        for(int k = 0; k<(numberOfNumbers[j]/4); ++k){
            //additionSIMD(&setA[k], &setB[k]);
            times[0] += (double)additionSIMD(&setA[k], &setB[k]);
            times[1] += (double)subtractionSIMD(&setA[k], &setB[k]);
            times[2] += (double)multiplicationSIMD(&setA[k], &setB[k]);
            times[3] += (double)divisionSIMD(&setA[k], &setB[k]);
        }
    
    }

    fprintf(f,"Typ obliczen: SIMD\nLiczba liczb: %d, Sredni czas[s]:\n", numberOfNumbers[j]);
    fprintf(f,"+ %lf\n",times[0]/10.0f);
    fprintf(f,"- %lf\n",times[1]/10.0f);
    fprintf(f,"* %lf\n",times[2]/10.0f);
    fprintf(f,"/ %lf\n\n",times[3]/10.0f);
    // printf("------ %d -------\n", numberOfNumbers[j]);
    // printf("Czas trwania dodawania %lf\n",times[0]);
    // printf("Czas trwania odejmowania %lf\n",times[1]);
    // printf("Czas trwania mnożenia %lf\n",times[2]);
    // printf("Czas trwania dzielenia %lf\n",times[3]);
    for(int k = 0; k<4; ++k){
        times[k] = 0;
    }
}
fprintf(f,"\n");
    //testing loop - SISD
for(int j = 0; j < 3;++j){
    for(int i = 0; i < REPETITION; ++i){
    generaetNumber(setA);
    generaetNumber(setB);
        for(int k = 0; k<(numberOfNumbers[j]/4); ++k){
            additionSISD(&setA[k].vecOne, &setB[k].vecOne);
            times[0] += (double)additionSISD(&setA[k].vecOne, &setB[k].vecOne);
            times[1] += (double)subtractionSISD(&setA[k].vecOne, &setB[k].vecOne);
            times[2] += (double)multiplicationSISD(&setA[k].vecOne, &setB[k].vecOne);
            times[3] += (double)divisionSISD(&setA[k].vecOne, &setB[k].vecOne);
        }
        for(int k = 0; k<(numberOfNumbers[j]/4); ++k){
            additionSISD(&setA[k].vecTwo, &setB[k].vecTwo);
            times[0] += (double)additionSISD(&setA[k].vecTwo, &setB[k].vecTwo);
            times[1] += (double)subtractionSISD(&setA[k].vecTwo, &setB[k].vecTwo);
            times[2] += (double)multiplicationSISD(&setA[k].vecTwo, &setB[k].vecTwo);
            times[3] += (double)divisionSISD(&setA[k].vecTwo, &setB[k].vecTwo);
        }
        for(int k = 0; k<(numberOfNumbers[j]/4); ++k){
            additionSISD(&setA[k].vecThree, &setB[k].vecThree);
            times[0] += (double)additionSISD(&setA[k].vecThree, &setB[k].vecThree);
            times[1] += (double)subtractionSISD(&setA[k].vecThree, &setB[k].vecThree);
            times[2] += (double)multiplicationSISD(&setA[k].vecThree, &setB[k].vecThree);
            times[3] += (double)divisionSISD(&setA[k].vecThree, &setB[k].vecThree);
        }
        for(int k = 0; k<(numberOfNumbers[j]/4); ++k){
            additionSISD(&setA[k].vecFour, &setB[k].vecFour);
            times[0] += (double)additionSISD(&setA[k].vecFour, &setB[k].vecFour);
            times[1] += (double)subtractionSISD(&setA[k].vecFour, &setB[k].vecFour);
            times[2] += (double)multiplicationSISD(&setA[k].vecFour, &setB[k].vecFour);
            times[3] += (double)divisionSISD(&setA[k].vecFour, &setB[k].vecFour);
            divisionSISDResult(&setA[k].vecFour, &setB[k].vecFour);
        }
    }

    fprintf(f,"Typ obliczen: SISD\nLiczba liczb: %d, Sredni czas[s]:\n", numberOfNumbers[j]);
    fprintf(f,"+ %lf\n",times[0]/10.0f);
    fprintf(f,"- %lf\n",times[1]/10.0f);
    fprintf(f,"* %lf\n",times[2]/10.0f);
    fprintf(f,"/ %lf\n\n\n",times[3]/10.0f);
    printf("XD");
    // printf("------ %d -------\n", numberOfNumbers[j]);
    // printf("Czas trwania dodawania %lf\n",times[0]);
    // printf("Czas trwania odejmowania %lf\n",times[1]);
    // printf("Czas trwania mnożenia %lf\n",times[2]);
    // printf("Czas trwania dzielenia %lf\n",times[3]);
    for(int k = 0; k<4; ++k){
        times[k] = 0;
    }
}
    fclose(f);
    //printVector(setA);
    //printVector(setB);
    //double x = additionSIMD(setA, setB, 4096);
  
    printf("OiAK - Laboratorium 4\n");
    printf("Prowadzacy: mgr. Tomasz Serafin\n");


    return 0;
}

void generaetNumber(numericVector *dataSet){
    for(int i = 0; i<TAB_SIZE; ++i){
    dataSet[i].vecOne = (((float)(rand()%100000))/((float)(rand()%100)+1));
    dataSet[i].vecTwo = (((float)(rand()%100000))/((float)(rand()%100)+1));
    dataSet[i].vecThree = (((float)(rand()%100000))/((float)(rand()%100)+1));
    dataSet[i].vecFour = (((float)(rand()%100000))/((float)(rand()%100)+1));
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
double additionSIMD(numericVector* setA ,numericVector* setB){
    numericVector result;

    timeOfStart_t = clock();

    asm(
        "movq %1, %%rax\n"
        "movups (%%rax), %%xmm0\n"
        "movq %2, %%rax\n"
        "movups (%%rax), %%xmm1\n"
        "addps %%xmm1, %%xmm0\n"
        "movups %%xmm0, %0\n"
        :"=m"(result)
        :"m"(setA), "m"(setB)
        :"rax"
    );

    timeOfEnd_t= clock();
    timePassed = (double)(timeOfEnd_t - timeOfStart_t)/CLOCKS_PER_SEC;

    return timePassed;
}
double subtractionSIMD(numericVector* setA ,numericVector* setB){
    numericVector result;

    timeOfStart_t = clock();

    asm(
        "movq %1, %%rax\n"
        "movups (%%rax), %%xmm0\n"
        "movq %2, %%rax\n"
        "movups (%%rax), %%xmm1\n"
        "subps %%xmm1, %%xmm0\n"
        "movups %%xmm0, %0\n"
        :"=m"(result)
        :"m"(setA), "m"(setB)
        :"rax"
    );

    timeOfEnd_t= clock();
    timePassed = (double)(timeOfEnd_t - timeOfStart_t)/CLOCKS_PER_SEC;
    
    return timePassed;
}
double multiplicationSIMD(numericVector* setA ,numericVector* setB){
    numericVector result;

    timeOfStart_t = clock();

    asm(
        "movq %1, %%rax \n"
		"movups (%%rax), %%xmm0 \n"
		"movq %2, %%rax \n\t"
		"movups (%%rax), %%xmm1 \n"
		"mulps %%xmm1, %%xmm0 \n"
		"movups %%xmm0, %0 \n"
		:"=m"(result)
		:"m"(setA), "m"(setB)
		:"rax"
    );

    timeOfEnd_t = clock();
    timePassed = (double)(timeOfEnd_t - timeOfStart_t)/CLOCKS_PER_SEC;
    
    return timePassed;
}
double divisionSIMD(numericVector* setA ,numericVector *setB){
    numericVector result;

    timeOfStart_t = clock();

    asm(
        "movq %1, %%rax\n"
        "movups (%%rax), %%xmm0\n"
        "movq %2, %%rax\n"
        "movups (%%rax), %%xmm1\n"
        "divps %%xmm1, %%xmm0\n"
        "movups %%xmm0, %0\n"
        :"=m"(result)
        :"m"(setA), "m"(setB)
        :"rax"
    );

    timeOfEnd_t = clock();
    timePassed= (double)(timeOfEnd_t - timeOfStart_t)/CLOCKS_PER_SEC;
    
    return timePassed;
}

//SIMD operations - returning results
numericVector additionSIMDResult(numericVector *setA ,numericVector* setB){
    numericVector result;

    asm(
        "movq %1, %%rax \n"
		"movups (%%rax), %%xmm0 \n"
		"movq %2, %%rax \n\t"
		"movups (%%rax), %%xmm1 \n"
		"addps %%xmm1, %%xmm0 \n"
		"movups %%xmm0, %0 \n"
		:"=m"(result)
		:"m"(setA), "m"(setB)
		:"rax"
    );

printf("%lf, %lf, %lf, %lf\n", result.vecOne, result.vecTwo, result.vecThree, result.vecFour);
}
numericVector subtractionSIMDResult(numericVector* setA ,numericVector* setB){
    numericVector result;

    asm(
        "movq %1, %%rax \n"
		"movups (%%rax), %%xmm0 \n"
		"movq %2, %%rax \n\t"
		"movups (%%rax), %%xmm1 \n"
		"subps %%xmm1, %%xmm0 \n"
		"movups %%xmm0, %0 \n"
		:"=m"(result)
		:"m"(setA), "m"(setB)
		:"rax"
    );

printf("%lf, %lf, %lf, %lf\n", result.vecOne, result.vecTwo, result.vecThree, result.vecFour);
}
numericVector multiplicationSIMDResult(numericVector *setA ,numericVector* setB){
    numericVector result;

    asm(
        "movq %1, %%rax \n"
		"movups (%%rax), %%xmm0 \n"
		"movq %2, %%rax \n\t"
		"movups (%%rax), %%xmm1 \n"
		"mulps %%xmm1, %%xmm0 \n"
		"movups %%xmm0, %0 \n"
		:"=g"(result)
		:"m"(setA), "m"(setB)
		:"rax"
    );

printf("%lf, %lf, %lf, %lf\n", result.vecOne, result.vecTwo, result.vecThree, result.vecFour);
}
numericVector divisionSIMDResult(numericVector* setA ,numericVector* setB){
    numericVector result;
    asm(
        "movq %1, %%rax\n"
        "movups (%%rax), %%xmm0\n"
        "movq %2, %%rax\n"
        "movups (%%rax), %%xmm1\n"
        "divps %%xmm1, %%xmm0\n"
        "movups %%xmm0, %0\n"
        :"=m"(result)
        :"m"(setA), "m"(setB)
        :"rax"
    );

 printf("%lf, %lf, %lf, %lf\n", result.vecOne, result.vecTwo, result.vecThree, result.vecFour);
}

//SISD operations - returning time passed
double additionSISD(float *a, float *b){
float result;
timeOfStart_t = clock();

asm(
    "fld %1\n"
    "fadd %2 \n"
    :"=t"(result)
    :"m"(*a), "m"(*b)

);
timeOfEnd_t = clock();
timePassed= (double)(timeOfEnd_t - timeOfStart_t)/CLOCKS_PER_SEC;
return timePassed;
}
double subtractionSISD(float *a, float *b){
float result;
timeOfStart_t = clock();

asm(
    "fld %1\n"
    "fsub %2 \n"
    :"=t"(result)
    :"m"(*a), "m"(*b)

);
timeOfEnd_t = clock();
timePassed= (double)(timeOfEnd_t - timeOfStart_t)/CLOCKS_PER_SEC;
return timePassed;
}
double multiplicationSISD(float *a, float *b){
float result;
timeOfStart_t = clock();

asm(
    "fld %1\n"
    "fmul %2 \n"
    :"=t"(result)
    :"m"(*a), "m"(*b)

);
timeOfEnd_t = clock();
timePassed= (double)(timeOfEnd_t - timeOfStart_t)/CLOCKS_PER_SEC;
return timePassed;
}
double divisionSISD(float *a, float *b){
float result;
timeOfStart_t = clock();

asm(
    "fld %1\n"
    "fdiv %2 \n"
    :"=t"(result)
    :"m"(*a), "m"(*b)

);
timeOfEnd_t = clock();
timePassed= (double)(timeOfEnd_t - timeOfStart_t)/CLOCKS_PER_SEC;
return timePassed;
}

//SISD operations - returning results
float additionSISDResult(float *a, float *b){
float result;
timeOfStart_t = clock();

asm(
    "fld %1\n"
    "fdiv %2 \n"
    :"=t"(result)
    :"m"(*a), "m"(*b)

);
printf("%lf ", result);
}
float subtractionSISDResult(float *a, float *b){
float result;
timeOfStart_t = clock();

asm(
    "fld %1\n"
    "fsub %2 \n"
    :"=t"(result)
    :"m"(*a), "m"(*b)

);
printf("%lf ", result);
}
float multiplicationSISDResult(float *a, float *b){
float result;
timeOfStart_t = clock();

asm(
    "fld %1\n"
    "fmul %2 \n"
    :"=t"(result)
    :"m"(*a), "m"(*b)

);
printf("%lf ", result);
}
float divisionSISDResult(float *a, float *b){
float result;
timeOfStart_t = clock();

asm(
    "fld %1\n"
    "fdiv %2 \n"
    :"=t"(result)
    :"m"(*a), "m"(*b)

);
printf("%lf ", result);
}