#include <iostream>
#include <math.h>
#include <vector>

using namespace::std;

/* Number of years to be simulated*/
const int year_max = 1;

/*Defining parameters to initialize the population*/
const int initial_population = 20;
const int initial_female = 10;

typedef struct _ageCategory{
    int age_value;
    int nb_individuals;
    double gender; //percentage of female
} _ageCategory;

typedef struct _statistic{
    int total_deaths;
    int total_births;
    int total_female;
    int total_population;
} _statistic;



/**size of the population table**/
const int size = 16;

/** probabilities of the number women giving birth to 3, 4, 5 and 6 litters in the current year respectively **/
const double litters_probabilities[] = {0.12, 0.25, 0.25, 0.25, 0.13};

/** probabilities of the number of babies beeing 3, 4, 5 and 6 per litter **/
const double babies_probabilities[] = {0.25, 0.25, 0.25, 0.25};

/** functionns needed in randomization**/
double genrand_real1(void);
unsigned long genrand_int32();
double uniform(double a, double b, double x);




/* Functions*/

void Death (vector<_ageCategory> & population, _statistic & statistic);
void Birth (vector<_ageCategory> & population,_statistic & statistic);
void Gender (vector<_ageCategory> & population);
void Update_total_individuals (vector<_ageCategory> & population, _statistic & statistic);
void Update_total_female (vector<_ageCategory> & population, _statistic & statistic);

