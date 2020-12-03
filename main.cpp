#include <iostream>
#include <math.h>

#include "header.hpp"


int main() {

    /**
     * Initilize the population
     * */

    struct _ageCategory * population = (_ageCategory *) malloc (16 * sizeof(_ageCategory));
    struct _statistiques * statistiques = (_statistiques *) malloc (16 * sizeof(_statistiques));


    /**
     * Initilize the population
     * */
     
    population[0].age_value = 0;
    population[0].nb_individuals = 2;
    population[0].gender = 0.5;

    for (int i = 0; i < year_max; i ++) {

    }
    

}