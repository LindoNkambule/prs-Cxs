#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "../utils/utils.h"


double psi(double x, double alpha, double lam){
    double f = -alpha*(cosh(x)-1.0)-lam*(exp(x)-x-1.0);

    return f;
}



double dpsi(double x, double alpha, double lam){
    double f = -alpha*sinh(x)-lam*(exp(x)-1.0);

    return f;
}



double g(double x, double sd, double td, double f1, double f2){
    double f = 0;

    if (x >= -sd && x <= td){
        f = 1.0;
    }else if (x >td){
        f = f1;
    }else if (x < -sd){
        f = f2;
    }

    return f;
}


double gigrnd(double p, double a, double b){
    double lam = p;
    double omega = sqrt(a*b);

    bool swap = false;

    if (lam < 0){
        lam = -lam;
        swap = true;
    }else{
        swap = false;
    }

    double power = 2.0;
    double alpha = sqrt(pow(omega, power) + pow(lam, power)) - lam;

    // find t
    double x = -psi(1.0, alpha, lam);
    double t = 0.0;

    if (x >= 0.5 && x <= 2.0){
        t = 1.0;
    }
    
    else if (x > 2.0){
        if (alpha == 0 && lam == 0){
            t = 1.0;
        }else {
            t = sqrt(2.0/(alpha+lam));
        }
    }
    
    else if (x < 0.5){
        if (alpha == 0 && lam == 0){
            t = 1.0;
        }else{
            t = log(4.0/(alpha+2.0*lam));
        }
    }

    // find s
    x = -psi(-1.0, alpha, lam);
    double s = 0.0;

    if (x >= 0.5 && x <= 2.0){
        s = 1.0;
    }

    else if (x > 2.0){
        if (alpha == 0 && lam == 0){
            s = 1.0;
        }else {
            s = sqrt(4.0/(alpha*cosh(1)+lam));
        }
    }

    else if (x < 0.5){
        if (alpha == 0 && lam == 0){
            s = 1.0;
        }else if (alpha == 0){
            s = 1.0/lam;
        }else if (lam == 0){
            s = log(1.0+1.0/alpha+sqrt(1.0/pow(alpha,2)+2.0/alpha));
        }else{
            s = getMin(1.0/lam, log(1.0+1.0/alpha+sqrt(1.0/pow(alpha,2)+2.0/alpha)));
        }
    }

    // find auxiliary parameters
    double eta = -psi(t, alpha, lam);
    double zeta = -dpsi(t, alpha, lam);
    double theta = -psi(-s, alpha, lam);
    double xi = dpsi(-s, alpha, lam);

    p = 1.0/xi;
    double r = 1.0/zeta;

    double td = t-r*eta;
    double sd = s-p*theta;
    double q = td+sd;

    // random variate generation
    bool rand_generate = true;
    double rnd;

    while (rand_generate){
        srand(time(0));
        // the "random" value for using gen_rnd_number for the first time doesn't change much
        double __ = gen_rnd_number(0, 1);
        double U = gen_rnd_number(0, 1);
        double V = gen_rnd_number(0, 1);
        double W = gen_rnd_number(0, 1);
        if (U < q/(p+q+r)){
            rnd = -sd+q*V;
        }else if (U < (q+r)/(p+q+r)){
            rnd = td-r*log(V);
        }else{
            rnd = -sd+p*log(V);
        }

        double f1 = exp(-eta-zeta*(rnd-t));
        double f2 = exp(-theta+xi*(rnd+s));
        if ( W*g(rnd, sd, td, f1, f2) <= exp(psi(rnd, alpha, lam)) ) {
            break;
        }
    }

    // transform back to the three-parameter version gig(p,a,b)
    rnd = exp(rnd)*(lam/omega+sqrt(1.0+pow(lam,2)/pow(omega,2)));
    if (swap) {
        rnd = 1.0/rnd;
    }

    rnd = rnd/sqrt(a/b);

    return rnd;

}
