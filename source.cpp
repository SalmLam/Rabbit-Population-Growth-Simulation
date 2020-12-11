#include "header.hpp"

/**
 * ********************************************************************************************************************
 * * * Death   : Computes the the total number of deaths per year of each age category
 * * * Input   : a table of size 16 where each cell is of type struct _Age
 * * * Output  : An integer denoting the total number of deaths per year 
 * *********************************************************************************************************************
 **/

void Death (vector<_ageCategory> & population, _statistic & statistic) {
    int total = 0;
    int category_total;
    for (int i = 0; i < sizeP; i++) {
        category_total = 0;
        if (population[i].age_value < 1) {
            category_total = population[i].nb_individuals * 0.65;
            population[i].nb_individuals -= category_total;
        } else if (population[i].age_value < 10) {
            category_total = population[i].nb_individuals * 0.4;
            population[i].nb_individuals -= category_total;
        } else {
            category_total = population[i].nb_individuals * ((60 - (population[i].age_value - 10) * 10) / 100);
            population[i].nb_individuals -= category_total;
        } 

        total += category_total;
    }
    /*Update annual death statistics*/
    statistic.total_deaths = total;

} 

/**
 * ********************************************************************************************************************
 * * * Birth   : Computes the number of litters born per year and uses the result to compute the number 
 *               of babies born per year
 * * * Input   : a table of size 16 where each cell is of type struct _Age
 * * * Output  : An integer denoting the total number of births per year 
 * *********************************************************************************************************************
 **/

void Birth (vector<_ageCategory> & population, _statistic & statistic) {
    int total_females = 0;
    int total_litters = 0;
    int total_babies = 0;

    for (int i = 1; i < sizeP; i++) {

        /** Iniitialize **/
        total_litters = 0;

        /** Get the number of females in the current age_category **/
        total_females = population[i].nb_individuals * population[i].gender;
        
        /** Computes the number of litters in the current year **/
        for (int j = 0; j < 5; j++) {
            total_litters += total_females * litters_probabilities[j] * (j + 4); //************************ we forgot to multiply by j+4
        }


        /** Computes the number of babies born in the current years **/
        for (int j = 0; j < 4; j++) {
            total_babies += total_litters * babies_probabilities[j] * (j + 3);
        }
    }

    /*Update annual birth statistics*/
    statistic.total_births = total_babies;

}

/**
 * ********************************************************************************************************************
 * * * Gender  : Updates the percentage of females in the population
 * * * Input   : a table of size 16 where each cell is of type struct _Age
 * * * Output  : void 
 * *********************************************************************************************************************
 **/

void Gender(vector<_ageCategory> & population) {
    double random = 0.0;
    for (int i = 0; i < sizeP; i++) {
        /** generates a random number between 1 and 20**/
            random = genrand_real1();
            random = uniform(1, 20, random);
        /** update randomly the females's percentage **/
            if (random < 10) {
                population[i].gender = 0.5 - (random / 100);
            }else {
                population[i].gender = 0.5 + (random / 100);
            }
    }

}

/**
 * ********************************************************************************************************************
 * * * Update_total_individuals  : Updates the total number of individuals in the population each year
 * * * Input   : a table of size 16 where each cell is of type struct _Age and the computed number of births 
 * * * Output  : the total number of individualss 
 * *********************************************************************************************************************
 **/

void Update_total_individuals (vector<_ageCategory> & population, _statistic & statistic) {
   
    /** update the number of deaths by adding the old inviduals that will die (> 15 yo) **/
    statistic.total_deaths += population[sizeP - 1].nb_individuals;

    /** Updates the number of individuals of each category**/
    for (int i = 0; i < sizeP - 1; i++) {
        population[sizeP - i - 1].nb_individuals = population[sizeP - i - 2].nb_individuals; //********** pay attention to it: sizeP-i-1 et nn pas sizeP - i
    }

    population[0].nb_individuals = statistic.total_births;

    for(int i = 0; i < sizeP; i++){
        statistic.total_population += population[i].nb_individuals;
    }

}

/**
 * ********************************************************************************************************************
 * * * Update_total_female  : Updates the total number of females in the population each year
 * * * Input   : a table of size 16 where each cell is of type struct _ageCategory 
 * * *         : a table size equal to the number of years studied where each cell is of type _statistic  
 * * * Output  : the total number of individualss 
 * *********************************************************************************************************************
 **/

void Update_total_female (vector<_ageCategory> & population, _statistic & statistic) {

    int total_female = 0;
    for (int i = 0; i < sizeP ; i++) {
        total_female += population[i].nb_individuals * population[i].gender;
    } 
    statistic.total_female = total_female;

}

