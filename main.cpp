#include "header.hpp"


int main() {

    /**
     * Arrays needed to keep track of the evlolution of the population
     * */

    vector<_ageCategory> population;

    _statistic statistic[year_max];


    /**
     * Initilizing the population
     * */

    _ageCategory tmp;
    tmp.age_value = 0;
    tmp.gender =  0.5;
    tmp.nb_individuals = 2;
    population.push_back(tmp);

    _ageCategory t;
    t.age_value = 1;
    t.gender =  0.6;
    t.nb_individuals = 30;
    population.push_back(t);

    for (int i = 2;  i < sizeP; i++) {
        _ageCategory tmp;
        tmp.age_value = i;
        tmp.gender =  0;
        tmp.nb_individuals = 0;
        population.push_back(tmp);
    }

    /**
     * Simulating the evlolution of the population
     * */

    for (int i = 0; i <year_max; i++){
        statistic[i].total_births = 0;
        statistic[i].total_deaths = 0;
        statistic[i].total_female = 0;
        statistic[i].total_population = 0;
    }

    for (int i = 0; i < year_max; i++) {
        Death (population , statistic[i]);
        Birth (population, statistic[i]);
        Update_total_individuals (population, statistic[i]);
        Gender(population);
        Update_total_female (population, statistic[i]);
        cout << "Happy new year !! " << i << "\tTotal babies: " << statistic[i].total_births << "\tTotal deaths: " << statistic[i].total_deaths <<"\tCard: " << statistic[i].total_population << endl;
        save_statistics(statistic[i]);
        save_nb_individuals_category(population);
        save_gender_category(population);
    }

    //free(population);
    //free(statistic);
}
