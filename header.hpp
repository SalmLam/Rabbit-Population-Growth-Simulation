

typedef struct _ageCategory{
    int age_value;
    int nb_individuals;
    double gender; //percentage of female
} _ageCategory;

typedef struct _statistiques{
    int initial_population;
    int total_deaths;
    int total_births;
    int total_female; 
} _statistiques;



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


int Death (_ageCategory (& population)[]);
int Birth (_ageCategory (& population)[]);
void Gender (_ageCategory (& population)[]);
int update_total_individuals (_ageCategory (& population)[]);


