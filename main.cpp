#include "header.hpp"


int main() {

    /**
     * Arrays needed to keep track of the evlolution of the population
     * */

/*
    _ageCategory  popu [16];
    _ageCategory (& population) [16] = popu;*/

    
    //svector<_statistic> statistic;

    

    //struct _ageCategory * population = (_ageCategory *) malloc (size * sizeof(_ageCategory));
    //_statistic * statistic = (_statistic *) malloc (year_max * sizeof(_statistic));


    /**
     * Initilizing the population
     * */

    
    _statistic statistic[year_max];

    for (int i = 0;  i < year_max; i++) {
        statistic[i].total_births = 0;
        statistic[i].total_deaths = 0;
        statistic[i].total_female = 0;
        statistic[i].total_population = 0;
        
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

    
    vector<_ageCategory> population;
    
    _ageCategory tmp;
    tmp.age_value = 0;
    tmp.gender =  initial_female / initial_population;;
    tmp.nb_individuals = initial_population;
    population.push_back(tmp);

    for (int i = 1;  i < size; i++) {
        _ageCategory tmp;
        tmp.age_value = i;
        tmp.gender =  0.5;
        int random = genrand_real1();
        random = uniform(1, 7, random);
        tmp.nb_individuals = random;
        population.push_back(tmp);
    }
    


    for (int i = 0; i < year_max; i++) {
        std::cout <<" HAPPY NEW YEAR  "<< i << " . " << std::endl;
        Death (population , statistic[i]);
        Birth (population, statistic[i]);
        Update_total_individuals (population, statistic[i]);
        Gender(population);
        Update_total_female (population, statistic[i]);
        //print_statistics(statistic[i]);
        //print_population(population);
        save_statistics(statistic[i]);
        save_nb_individuals_category(population);
        save_gender_category(population);
    }

    //free(population);
    //free(statistic);
}