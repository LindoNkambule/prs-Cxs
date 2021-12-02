#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "methods/methods.h"
#include "utils/utils.h"

int main(){
    double xpsi = psi(4.0, 5.0, 4.0);
    double xdpsi = dpsi(4.0, 5.0, 4.0);

    printf("The value of xpsi is: %f\n", xpsi);
    printf("The value of xdpsi is: %f\n", xdpsi);

    int lower = 0, upper = 1;
    
    // srand(time(0));
    // srand(time(NULL));
    srand( (unsigned int) time(NULL) );
    double __ = gen_rnd_number(lower, upper);
    double U = gen_rnd_number(lower, upper);
    double V = gen_rnd_number(lower, upper);
    double W = gen_rnd_number(lower, upper);

    printf("U=%f  V=%f  W=%f\n", U, V, W);
    

}

