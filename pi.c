#include <stdio.h>
#include <omp.h>

double pi_calc()
{
    double sum, sum1=0, sum2=0, pi;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for(double i=1; i<1000000; i=i+2)
            {
                sum1 += (1/(2*i-1));
            }
        }

        #pragma omp section
        {
            for(double j=2; j<1000000; j+=2)
            {
                sum2 += (1/(2*j-1));
            }
        }
    }

    sum = sum1-sum2;

    pi = sum*4;

    return pi;

}
int main()
{
    double start, end, pi;

    start = omp_get_wtime();

    pi = pi_calc();

    end = omp_get_wtime();


    printf("\npi = %f\n\n", pi);
    printf("Execution time : %f seconds\n\n", end-start);

    return 0;
}
