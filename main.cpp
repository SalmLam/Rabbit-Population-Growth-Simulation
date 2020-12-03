#include "header.hpp"


int main() {

    /**
     * Arrays needed to keep track of the evlolution of the population
     * */

/*
    _ageCategory  popu [16];
    _ageCategory (& population) [16] = popu;*/

    vector<_ageCategory> population;

    _statistic statistic[year_max];

    //struct _ageCategory * population = (_ageCategory *) malloc (size * sizeof(_ageCategory));
    //_statistic * statistic = (_statistic *) malloc (year_max * sizeof(_statistic));


    /**
     * Initilizing the population
     * */

    _ageCategory tmp;
    tmp.age_value = 0;
    tmp.gender =  initial_female / initial_population;;
    tmp.nb_individuals = initial_population;
    population.push_back(tmp);

    for (int i = 1;  i < size; i++) {
        _ageCategory tmp;
        tmp.age_value = i;
        tmp.gender =  0;
        tmp.nb_individuals = 0;
        population.push_back(tmp);
    }
    /*
    population[0].age_value = 0;
    population[0].nb_individuals = initial_population;
    population[0].gender = initial_female / initial_population;

    for (int i = 1; i < size; i ++) {
        population[i].age_value = i;
        population[i].nb_individuals = 0;
        population[i].gender = 0;
    }*/

    /**
     * Simulating the evlolution of the population
     * */
    
    for (int i = 0; i < year_max; i++) {
        Death (population , statistic[i]);
        /*
        Birth (population, statistic[i]);
        Update_total_individuals (population, statistic[i]);
        Gender(population);
        Update_total_female (population, statistic[i]);*/
    }

    //free(population);
    //free(statistic);
}