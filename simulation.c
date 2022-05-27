#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define real double

// Solar constant W / m ^ 2
#define S0 1370

// Stefan - Boltzmann constant W / m2 / K4
#define SIGMA 0.00000005670367

// Temperature inertia (in years)
#define THETA 100.0

// Albedo, in this simulation albedo is considered constant
// in reality albedo can become lower with increased temperatures
// due to ice cap melting
#define ALBEDO 0.33

// Initial values

// Simulation starùts in 2007
static const real t0 = 2007.0;
// Temperaturature in 2007 in K
static const real T0 = 288.45;
// CO2 concentration in 2007 in ppm
static const real CO20 = 370.0;

//la variation de la concentration de co2
static real co2(real t)
{   
    real tmps=2000;
    real res=CO20;
    FILE *file = NULL;
    file = fopen("co2.dat", "wb");
    if (!file)
    {
        printf("erreur d'ouverture\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 20; i <=200 ; i*=2){
    fprintf(file ,"CO2 (%f) = %f\n", tmps, res);
    tmps+=i;
    res = (3.3)*(tmps- t0) + CO20;
    
    //printf("CO2 (%f) = %f\n", t, res);
    }
    fclose(file);
    return res;
    //return CO20;
}
// Greenhouse gaz fraction
static real G(real t, real T) //T ET t
{
    return 3.35071874e-03 * T + 3.20986702e-05 * co2(t) - 0.561593690144655;
}

static real P_in(void)
{

    return (1 - ALBEDO) * (S0 / 4);
}

static real P_out(real t, real T)
{

    return (1 - G(t, T)) * SIGMA * pow(T,4);
}
static real F(real t, real T)
{
    return (P_in() - P_out(t, T))/ THETA;
}

 
static real euler(real t_final, int steps)
{

    real h = (t_final - t0) / steps;
    real T_n = T0;
    real t_n = t0;
    FILE *fp = NULL;
    fp = fopen("output.dat", "wb");
    if (!fp)
    {
        printf("erreur d'ouverture\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < steps; i++)
    {  
        /*printf("hier:  %lf %lf\n",t_n,T_n);*/
        fprintf(fp, "%lf %lf\n", t_n, T_n);
        T_n += h * F(t_n, T_n);
        t_n = t0 + i*h;
    }
    fclose(fp);
    return T_n;
}

/*static real error()
{  
    real Tref = euler(2107,1000);
    real T=0.0;
    real E=0.0;
    FILE *fpc= NULL;
    fpc = fopen("error.dat", "wb");
    if (!fpc)
    {
        printf("erreur d'ouverture\n");
        exit(EXIT_FAILURE);
    }
    for(int steps=16;steps<=65536;steps*=2)
    {   
        fprintf(fpc, "Error (%d)=%lf\n",steps,fabs(E));
        T = euler(2017,steps);
        E=Tref-T;
        printf("Error (%d) = %lf \n",steps,fabs(E));
        }
    fclose(fpc);
    return fabs(E);
}*/

int main(int argc, char **argv)
{   
    // real error();
     real co2(real t);
    
      

    real T_n = euler(2107, 100);
    printf("temperature final: %lf\n", T_n);
    //real T_cp6=euler(2107,100);
    //printf("temperature en final RCP6.0: %lf\n",T_cp6);
    printf("Simple climate simulation\n");

    return 0;
}

