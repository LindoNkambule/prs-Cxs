#include <stdlib.h>
#include <time.h>


double gen_rnd_number(int lower, int upper){

    // returns random double in the half-open interval [lower, upper)
    double rnd = ( (double)rand() * ( upper - lower ) ) / (double)RAND_MAX + lower;

    return rnd;

}
