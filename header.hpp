#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace::std;

/* Number of years to be simulated*/
const int year_max = 20;

typedef struct _ageCategory{
    int age_value;
    int nb_individuals;
    double gender;          // Percentage of female 
} _ageCategory;

typedef struct _statistic{
    int total_deaths;
    int total_births;
    int total_female;
    int total_population;
} _statistic;



/**size of the population table**/
const int sizeP = 16;

/** probabilities of the number women giving birth to 4, 5, 6, 7 and 8 litters in the current year respectively **/
const double litters_probabilities[] = {0.12, 0.25, 0.25, 0.25, 0.13};

/** probabilities of the number of babies beeing 3, 4, 5 and 6 per litter **/
const double babies_probabilities[] = {0.1, 0.1, 0.4, 0.4};

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

void print_statistics (_statistic & statistic);
void print_population (vector<_ageCategory> & population);

void save_statistics (_statistic & statistic);
void save_nb_individuals_category (vector<_ageCategory> & population);
void save_gender_category (vector<_ageCategory> & population);
