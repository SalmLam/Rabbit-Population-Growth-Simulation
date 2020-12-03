#include <iostream>
#include <math.h>

#include "header.hpp"


int main() {

    /**
     * Arrays needed to keep track of the evlolution of the population
     * */

    struct _ageCategory * population = (_ageCategory *) malloc (size * sizeof(_ageCategory));
    struct _statistic * statistic = (_statistic *) malloc (year_max * sizeof(_statistic));


    /**
     * Initilizing the population
     * */
     
    population[0].age_value = 0;
    population[0].nb_individuals = initial_population;
    population[0].gender = initial_female / initial_population;

    for (int i = 1; i < size; i ++) {
        population[i].age_value = i;
        population[i].nb_individuals = 0;
        population[i].gender = 0;
    }

    /**
     * Simulating the evlolution of the population
     * */
    
    for (int i = 0; i < year_max; i++) {
        Death (population , statistic[i]);
        Birth (population, statistic[i]);
        Update_total_individuals (population, statistic[i]);
        Gender(population);
        Update_total_female (population, statistic[i]);
    }

    free(population);
    free(statistic);
}