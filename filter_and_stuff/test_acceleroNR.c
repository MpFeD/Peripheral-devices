/* ------------------------- */
/* --- test_acceleroNR.c --- */
/* ------------------------- */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 * University Pierre et Marie Curie
 */

#include <stdio.h>
#include <math.h>

#include "def.h"
#include "nrutil.h"
#include "noise.h"
#include "sampleNR.h"
#include "filterNR.h"
#include "my_paths.h"

#include "acceleroNR.h"

#define FILENAME_SIZE 128

// ---------------------------------------------------
float32 calc_sigma(float32 S, float32 Sx, float32 Sxx)
// ---------------------------------------------------
{
    return sqrt((S * Sxx - Sx * Sx) / (S * S));
}
// ---------------------------------------
void test_gaussian_noise_computation(void)
// ---------------------------------------
{
    // pour valider que le generateur aleatoire a bien
    // les bons parametres statistiques ...
    
    int i;
    int n = 1000000;
    float32 x, sx, sxx;
    
    puts("-------------------------------------");
    puts("-- test_gaussian_noise_computation --");
    puts("-------------------------------------");
    
    sx = 0.0f; sxx = 0.0f;
    for(i = 0; i < n; i++) {
        x = gaussian_noise(0, 10);
        //printf("%10.4f\n", x);
        sx += x;
        sxx += x*x;
    }
    printf("average = %10.3f sigma = %10.3f\n", sx/n, calc_sigma(n, sx, sxx));
    
    sx = 0.0f; sxx = 0.0f;
    for(i = 0; i < n; i++) {
        x = gaussian_noise(0, 20);
        //printf("%10.4f\n", x);
        sx += x;
        sxx += x*x;
    }
    printf("average = %10.3f sigma = %10.3f\n", sx/n, calc_sigma(n, sx, sxx));
}
// --------------------
void test_aduino1(void)
// --------------------
{
    arduino_init1();
    arduino_loop1();
}
// --------------------
void test_aduino2(void)
// --------------------
{
    arduino_init2();
    arduino_loop2();
}
// -----------------------------------------------
int test_acceleroNR(int argc, const char * argv[])
// -----------------------------------------------
{
    puts("=======================");
    puts("=== test_acceleroNR ===");
    puts("=======================");
    
    //test_gaussian_noise_computation();
    // -- fonctions de debruitage
    //test_linear_filter();
    //test_median_filter();
    
    //test_aduino1();
    test_aduino2();
    return 0;
}
