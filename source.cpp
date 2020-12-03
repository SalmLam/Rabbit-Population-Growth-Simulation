#include "header.hpp"

/**
 * ********************************************************************************************************************
 * * * Death   : Computes the the total number of deaths per year of each age category
 * * * Input   : a table of size 16 where each cell is of type struct _Age
 * * * Output  : An integer denoting the total number of deaths per year 
 * *********************************************************************************************************************
 **/

int Death (_ageCategory (& population)[]) {
    int total = 0;
    int category_total = 0;
    for (int i = 0; i < size; i++) {
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

    return total;
} 

/**
 * ********************************************************************************************************************
 * * * Birth   : Computes the number of litters born per year and uses the result to compute the number 
 *               of babies born per year
 * * * Input   : a table of size 16 where each cell is of type struct _Age
 * * * Output  : An integer denoting the total number of births per year 
 * *********************************************************************************************************************
 **/

int Birth (_ageCategory (& population)[]) {
    int total_females = 0;
    int total_litters = 0;
    int total_babies = 0;


    for (int i = 1; i < size; i++) {

        /** Iniitialize **/
        total_litters = 0;

        /** Get the number of females in the current age_category **/
            total_females = population[i].nb_individuals * population[i].gender;


        /** Computes the number of litters in the current year **/
            for (int j = 0; j < 5; j++) {
                total_litters += total_females * litters_probabilities[j];
            }


        /** Computes the number of babies born in the current years **/
            for (int j = 0; j < 4; j++) {
                total_babies += total_litters * babies_probabilities[j] * (j + 3);
            }
    }

    return total_babies;
}

/**
 * ********************************************************************************************************************
 * * * Gender  : Updates the percentage of females in the population
 * * * Input   : a table of size 16 where each cell is of type struct _Age
 * * * Output  : void 
 * *********************************************************************************************************************
 **/

void Gender(_ageCategory (& population)[]) {
    double random = 0.0;
    for (int i = 0; i < size; i++) {
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
 * * * Gender  : Updates the total number of individuals in the population each year
 * * * Input   : a table of size 16 where each cell is of type struct _Age and the computed number of births 
 * * * Output  : the total number of individualss 
 * *********************************************************************************************************************
 **/

int Update_total_individuals (_ageCategory (& population)[], _statistiques & statistiques) {

    /** update the number of deaths by adding the old inviduals that will die (> 15 yo) **/
    statistiques.total_deaths += population[size - 1].nb_individuals;

    /** Updates the nuber of individuals of each category**/
    for (int i = 0; i < size - 1; i++) {
        population[size - i].nb_individuals = population[size - i -1].nb_individuals;
    }

    population[0].nb_individuals = statistiques.total_births;
}