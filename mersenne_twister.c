/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] = 
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void)
{
    return (long)(genrand_int32()>>1);
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void)
{
    return genrand_int32()*(1.0/4294967295.0); 
    /* divided by 2^32-1 */ 
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32()*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void) 
{ 
    unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6; 
    return(a*67108864.0+b)*(1.0/9007199254740992.0); 
} 


/**
 * ********************************************************************************************************************
 * Question 2 :  Genaration of random numbers between A and B
 **********************************************************************************************************************
 * * * uniform : Returns a number between two parameters a and b using a pseudo-random number between o and 1
 * * * Input   : a and b (two rea; number that define the interval [A , B])
 *               x (real pseudo random number between 0 and 1) 
 * * * Output  : real number between a and b
 * 
 * *********************************************************************************************************************
 **/


double uniform(double a, double b, double x) {
	double y = x * (b - a) + a;
	return y;
}

/**
 * ********************************************************************************************************************
 * Question 3.a :  Reproduction of discrete empirical distributions with three classes A, B and C
 **********************************************************************************************************************
 * * * three_classes_discrete_distribution     : Simulates a population of three species A, B and C using cumulative
 *                                               probabilities and pseudo random number generator between 0 and 1
 * * * Input                                   : n (Integer that represents the size of the population)
 * * * Output                                  : Array of floats giving the percentage of each class
 * *********************************************************************************************************************
 **/

double* three_classes_discrete_distribution(int n) {
	double random = -1;
	double percentage[3];
	percentage[0]=0.0;
	percentage[1]=0.0;
	percentage[2]=0.0;
	for(int i = 0; i < n; i++) {
		random = genrand_real2();
		if (random < 0.5) {
			printf(" A ");
			percentage[0] += 1;
		}else if (random < 0.6) {
			printf(" B ");
			percentage[1] += 1;
		}else {
			printf(" C ");
			percentage[2] += 1;
		}
        if (i % 5 == 4) printf("\n");
	}
	printf("****************************************\n");
	printf("A : %10.8f % \n", (percentage[0] / n) * 100);
	printf("B : %10.8f % \n", (percentage[1] / n) * 100);
	printf("C : %10.8f % \n", (percentage[2] / n) * 100);
    printf("****************************************\n");

    return percentage;

}

/**
 * ********************************************************************************************************************
 * Question 3.b.a :  Reproduction of discrete empirical distributions with three classes A, B and C
 **********************************************************************************************************************
 * * * binary_search     : Return the class of a random number using binary search and cumulative probabilities
 *                         probabilities and pseudo random number generator between 0 and 1
 * * * Input             : a and b (two integers defining the first and the last index of the array )
 *                         values (array of floats)
 *                         x (random number to wich we are going to assing a class)
 * * * Output            : Array of floats giving the percentage of each class
 * *********************************************************************************************************************
 * * * generic_discrete_distribution     : Simulates a population of three species A, B and C using cumulative
 *                                         probabilities and pseudo random number generator between 0 and 1
 * * * Input                             : n (Integer that represents the size of the population)
 * * * Output                            : Array of floats giving the percentage of each class
 * *********************************************************************************************************************
 **/

int binary_search(int a, int b, double x, double * values) {
    int m = (b + a) / 2;
    if (x < values[m]) return binary_search(a, m, x, values);
    else if (x <= values[m + 1]) return m;
    else return binary_search(m + 1, b, x, values);
}

int n_search(int size, double x, double * array) {
    for (int i = 0; i < size; i++) {
        if (x < array[i]) return i;
    }
}

void generic_discrete_distribution(int size, int * individuals_per_class) {
	double * probabilities = (double *)malloc (size * sizeof(double));
    double * cumulative_probabilities =  (double *) malloc (size * sizeof(double));
	int population_size = 0;
    double random = -1;
    int individual = -1;

    /*Number of individuals in the population*/
	for (int i = 0; i < size; i++) {
		population_size += individuals_per_class[i];
	}
	printf("population size : %d \n", population_size);
	

    printf("\n\n Probabilities\n");
    /*Probability of being in each class*/
    for (int i = 0; i < size; i++) {
		probabilities[i] = (double) individuals_per_class[i] / population_size;
		printf (" %10.8f ", probabilities[i]);
	}


    printf("\n\n cumulative probabilities \n");
    /*Cumulative probabilities */
    cumulative_probabilities[0] = probabilities[0];
    for (int i = 1; i < size; i++) {
		cumulative_probabilities[i] = cumulative_probabilities[i-1] + probabilities[i]; 
        printf ("%lf ", cumulative_probabilities[i]);
	}

    printf("\n\n Simulation \n");
    /*Simulation of the population*/
    for (int i = 0; i < 1000; i++) {
        random = uniform(probabilities[0], 1, genrand_real2());
        individual = binary_search (0, size - 1, random, cumulative_probabilities);
        //individual = n_search(size, random, cumulative_probabilities);
        printf (" %d ", individual);
        if (i % 5 == 4) printf("\n");
    }

 	free (probabilities);
    free (cumulative_probabilities);
    printf("end_generic_simulation");
}	


/**
 * ********************************************************************************************************************
 * Question 4.a :  Reproduction of continuous distribution
 **********************************************************************************************************************
 * * * negExp     : Simulates the law F(x) = 1 - exp [(-1 / M ) * x] analogue 
 *                  of the poisson distribution 
 * * * Input      : m (float number representing the mean value of the law F)
 * * * Output     : Random float number ditributed according to the law F
 * *********************************************************************************************************************
 **/

double negExp(double m) {
    double random = genrand_real1();
    return (-m) * log(1 - random);
}

/**
 * ********************************************************************************************************************
 * Question 4.b :  Reproduction of continuous distribution
 **********************************************************************************************************************
 * * * test_negExp     : Calculates the mean of the distribution obtained by simulating the law F 
 * * * Input           : m (float number representing the mean value of the law F)
 *                       n (integeer denoting the number of experiences) 
 * * * Output          : displays the mean of the distribution obtained
 * *********************************************************************************************************************
 **/


void Test_negExp(double m, int n) {
    double mean = 0.0;
    for (int i = 0; i < n; i++) {
        mean += negExp(m);
    }
    mean = mean / n;
    printf("The mean value is : %10.8f \n", mean);
 }

 /**
 * ********************************************************************************************************************
 * Question 4.c :  Reproduction of continuous distribution
 **********************************************************************************************************************
 * * * print_histogram : Prints the histogram of the densty function 
 * * * Input           : values (itegers denoting the values to be printed)
 *                       size (integer denoting the number of values)
 * * * Output          : void
 * *********************************************************************************************************************
 **/
 void print_histogram(int size, int * values) {

    /*Looking for the max value*/
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (values[i] > max) max = values[i];
    }

    /*Drawing the histogram*/
    while(max > 0) {
        for (int i = 0; i < size-1; i++) {
            if (values[i] >= max) printf("***  ");
            else printf("     ");
        }
        printf("\n");
        max--;
    }
    for (int i = 0; i < size; i++) {
        printf(" %d   ", i);
    }
    
}

 /**
 * ********************************************************************************************************************
 * Question 4.c :  Reproduction of continuous distribution
 **********************************************************************************************************************
 * * * biased_dice     : Calculates the mean of the distribution obtained by simulatinf the law F 
 * * * Input           : m (float number representing the mean value of the law F)
 *                       n (integeer denoting the number of experiences) 
 * * * Output          : displays the mean of the distribution obtained
 * *********************************************************************************************************************
 **/




int *  biased_dice(int m, int n) {
    int test20bins[21];
    double binary_search_array[21];
    double random = -1;
    int index = -1;
    double mean = 0;

    for (int i = 0; i < 21; i++) {
        test20bins[i] = 0;
        binary_search_array[i] = i;
    }
    for (int i = 0; i < n; i++) {
        random = negExp(m);
        mean += random;
        if (random > 20) index = 20;
        else index = binary_search(0, 20, random, binary_search_array);
        test20bins[index] ++;
    }

    /*Dispalying results*/
    for (int i = 0; i < 20; i++) {
        printf("%d :=> %d\n", i, test20bins[i]);
    }

    /*Mean value*/
    mean = mean / n;
    printf("The mean value is : %10.8f \n", mean);

    print_histogram(21, test20bins);

}

/**
 * ********************************************************************************************************************
 * Question 5 :  Simulating non reversible distribution laws 
 **********************************************************************************************************************
 * * * box_muller_centered_reduced : Generates gaussian distribution N(0,1)
 * * * Input                : n (integeer denoting the number of experiences) 
 * * * Output               : void
 * *********************************************************************************************************************
 **/

void box_muller_centered_reduced (int n) {
    int test6bins[7];
    double binary_search_array[7];
    double random = -1;
    int index = -1;
    double mean = 0;
    test6bins[0] = 0;
    binary_search_array[0] = -0.3;
    double p1 = 0;
    for (int i = 1; i < 7; i++) {
        test6bins[i] = 0;
        binary_search_array[i] = binary_search_array[i - 1] + 0.1;
    }
    for (int i = 0; i < n; i++) {
    double random1 = genrand_real2();
    double random2 = genrand_real2();
    double x[2];
    x[0] = cos(2 * M_PI * random1) * sqrt(-2 * log(random2));
    x[1] = sin(2 * M_PI * random1) * sqrt(-2 * log(random2));
    // printf("x1 : %10.8f", x[0]);
    // printf("x2 : %10.8f", x[1]);
        for (int j = 0; j < 2; j++) {
            random = x[j];
            mean += random;
            if (random > -1 && random < 1) p1 ++;
            if (random > 0.3) index = 6;
            else index = n_search(7, x[j], binary_search_array);
            test6bins[index] ++;
        }
    }

    /*Dispalying results*/
    for (int i = 0; i < 6; i++) {
        printf("\n ---------%d :=> %d\n", i, test6bins[i]);
    }

    /*Mean value*/
    mean = mean / n;
    printf("The mean value is : %10.8f \n", mean);


    /*Cechking the Statistics*/
    p1 = p1 / (2*n);
    printf("The percentage in the center is  : %10.8f % \n", p1 * 100);

    print_histogram(7, test6bins);

}
/**
 * ********************************************************************************************************************
 * Question 5 :  Simulating non reversible distribution laws 
 **********************************************************************************************************************
 * * * box_muller           : Generates gaussian distribution N(mu, sigma)
 * * * Input                : n (integeer denoting the number of experiences)
 *                            mu (float denoting the mean value)
 *                            sigma (float denoting the variance)
 * * * Output               : void
 * *********************************************************************************************************************
 **/
void box_muller (int n, double mu, double sigma) {
    int test6bins[7];
    double binary_search_array[7];
    double random = -1;
    int index = -1;
    double mean = 0;
    test6bins[0] = 0;
    binary_search_array[0] = -0.3;
    double p1 = 0, p2 = 0, p3 = 0;
    for (int i = 1; i < 7; i++) {
        test6bins[i] = 0;
        binary_search_array[i] = binary_search_array[i - 1] + 0.1;
    }
    for (int i = 0; i < n; i++) {
    double random1 = genrand_real2();
    double random2 = genrand_real2();
    double x[2];
    x[0] = mu + sigma * cos(2 * M_PI * random1) * sqrt(-2 * log(random2));
    x[1] = mu + sigma * sin(2 * M_PI * random1) * sqrt(-2 * log(random2));
    // printf("x1 : %10.8f", x[0]);
    // printf("x2 : %10.8f", x[1]);
        for (int j = 0; j < 2; j++) {
            random = x[j];
            mean += random;
            if (random > mu - sigma && random < mu + sigma) p1 ++;
            if (random > 0.3) index = 6;
            else index = n_search(7, x[j], binary_search_array);
            test6bins[index] ++;
        }
    }

    /*Dispalying results*/
    for (int i = 0; i < 6; i++) {
        printf("\n ---------%d :=> %d\n", i, test6bins[i]);
    }

    /*Mean value*/
    mean = mean / (2*n);
    printf("The mean value is : %10.8f \n", mean);

    /*Cechking the Statistics*/
    p1 = p1 / (2*n);
    printf("The percentage in the center is  : %10.8f \n", p1 * 100);

    //print_histogram(7, test6bins);

}
/* These real versions are due to Isaku Wada, 2002/01/09 added */

int main(void)
{
     int i;
     unsigned long init[4] = {0x123, 0x234, 0x345, 0x456}, length = 4;
    init_by_array(init, length);
    printf("1000 outputs of genrand_int32()\n");
    
    
    
    for (i=0; i<1000; i++) {
      printf("%10.8f ", genrand_int32( ));
      //if (i%5==4) 
      printf("\n");
    }



    printf("\n1000 outputs of genrand_real2()\n");
    for (i=0; i<1000; i++) {
      //printf("%10.8f ", genrand_real2());
      /*Question 2 */
      printf("%10.8f ", uniform(5.0, 6.0, genrand_real2()));
      if (i%5==4) printf("\n");
    }


      /*Question 3.a*/
      double* percentage_1000 = three_classes_discrete_distribution(1000000);
      double* percentage_1000000 = three_classes_discrete_distribution(1000000);


      /*Question 3.b*/
      int individuals_per_class[10];
      individuals_per_class[0] = 0;
      individuals_per_class[1] = 55;
      individuals_per_class[2] = 44;
      individuals_per_class[3] = 63;
      individuals_per_class[4] = 12;
      individuals_per_class[5] = 5;
      individuals_per_class[6] = 29;
      individuals_per_class[7] = 30;
      individuals_per_class[8] = 74;
      individuals_per_class[9] = 15;
      generic_discrete_distribution(10 ,individuals_per_class);
    
      double array[4] = {0.76, 0.78, 2.6, 5};
      int c = binary_search(0, 3, 5.0, array);
      printf("-- %d --", c);
      
      /*Question 4*/
       Test_negExp(10, 1000000);
       int * test2bins= biased_dice(10, 500);

     /*Question 5*/
      box_muller_centered_reduced(1000);
      
    
}
