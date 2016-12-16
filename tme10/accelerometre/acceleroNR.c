/* ------------------ */
/* --- filterNR.c --- */
/* ------------------ */

/*
 * Copyright (c) 2011-2015 Lionel Lacassagne, all rights reserved,  LRI,  University Paris Sud 11
 * Copyright (c) 2015-2016 Lionel Lacassagne, all rights reserved,  LIP6, UPMC
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"
//#include "util.h"
//#include "kernel.h"

//#include "all.h"
//#include "mem.h"
//#include "outils.h"

#include "gauss.h"
#include "noise.h"
#include "acceleroNR.h"

#define SIZE 4

uint16 X_sig[SIZE+1]; // signal bruite
uint16 X_fir[SIZE+1]; // signal filtre FIR
uint16 X_iir[SIZE+1]; // signal filtre IIR

int g_c; // compteur
int g_i; // indice

#define NEXT1(x) x=x+1; if(x>SIZE) x=0
#define NEXT2(x) if(x<SIZE) x=x+1; else x=0;
#define NEXT(x) NEXT2(x)

// pour la fonction calc_stats
uint32 S_sig, Sx_sig, Sxx_sig;
uint32 S_fir, Sx_fir, Sxx_fir;
uint32 S_iir, Sx_iir, Sxx_iir;

// FIR: *S = Somme précédente
uint16 SS = 0;
// --------------------------
uint16 input_var_signal(void)
// --------------------------
{
	// generateur pseudo aleatoire
	static uint16 x = 9;

	x = x + 1;
	return x;

}
// ----------------------------
uint16 input_noised_signal(void)
// ----------------------------
{
    // generateur pseudo aleatoire
    uint16 x;
    
    x = 100;
    x += (uint16) gaussian_noise(0, 10);
    return x;
}
// ------------------------------------------------------
void acquisition(int *global_i, int *global_c, uint16 *X)
// ------------------------------------------------------
{
    int i = *global_i;
    
    uint16 x;
    
    // increment de l'indice et du compteur
    *global_c = *global_c + 1;
    if(i < SIZE) i = i + 1; else i = 0;
    
    // lecture du signal bruite
    //x = input_var_signal();
    x = input_noised_signal();
    
    X[i] = x;
    printf("X[%3d] <- %3d ", i, x);
    
    *global_i = i;
    return ;
}
// --------------------
void display(uint16 *X)
// --------------------
{
    putchar('[');
    for(int i = 0; i <= SIZE; i++) {
        printf("%2d ", X[i]);
    }
    putchar('[');
    //putchar('\n');
}
// ----------------------90+100+92--
void display_mod(uint16 *X)
// ------------------------
{
    for(int i = 0; i <= SIZE; i++) {
        //printf("%2d ", X[i + g_i]);
    }
    putchar('\n');
}
// -------------------------------------------------------------------------
void calc_stats(int i, int c, uint16* X, uint32 *S, uint32 *Sx, uint32 *Sxx)
// -------------------------------------------------------------------------
{
    uint32 moyenne, variance, ecart_type;		
	uint16 new,old;
	new = X[i];
	old = X[(i+1)%(SIZE+1)];
	uint32 s = *S;
 	uint32 sx =  *Sx;
 	uint32 sxx = *Sxx;
	//printf("i = %d et c = %d\n", i, c);
	if(c <= SIZE){
		s = c;
		sx += new;
		sxx += new*new;
	}else{
		s = SIZE;
		sx += new;
		sx -= old;
		sxx += new*new;
		sxx -= old*old;
	}
	*S=s;
	*Sx=sx;
	*Sxx=sxx;
    moyenne = round((sx+s/2)/s);
	variance = round(((s*sxx)-(sx*sx)+(s*s)/2)/(s*s));
    /*ecart_type = sqrt(variance);*/
    printf("Sx = %3d moy = %3d var = %3d ",*Sx, moyenne, variance);
}
// ----------------------------------------------
void calc_fir(uint16* S ,int i, int c, uint16 *X, uint16 *Y, uint16* S)
// ----------------------------------------------
{	
    uint16 y, nb, somme, old;
	old = X[(i+1)%(SIZE+1)];

	if(c <= SIZE){
		nb = c;
		somme = *S + X[i];
	}else{
		nb = SIZE;
		somme = *S + X[i] - old;
	}
	
	y = (somme + (nb/2)) / nb;
	*S = somme;	

    printf("FIR = %3d SOMME = %3d", y, somme);
	
    Y[i] = y;
}
// ----------------------------------------------
void calc_iir(int i, int c, uint16 *X, uint16 *Y)
// ----------------------------------------------
{
    uint16 y;
	uint16 alpha, beta;

	alpha = 1;
	beta = (1 << c) - alpha;
    
	y = ((alpha * X[i]) + (beta * Y[(i-1)%(SIZE+1)]) + (alpha + beta)/2) / (alpha + beta);

    Y[i] = y;
    
    printf("IIR = %3d c = %3d alpha = %3d beta = %3d", y, c, alpha, beta);
}
// ---------------------
void arduino_init1(void)
// ---------------------
{
	g_c = 0;
    g_i = SIZE + 1;
    
    S_sig = Sx_sig = Sxx_sig = 0;
    S_fir = Sx_fir = Sxx_fir = 0;
    S_iir = Sx_iir = Sxx_iir = 0;
}
// ---------------------
void arduino_loop1(void)
// ---------------------
{
	int iter, n = 5 * SIZE;

	for(iter = 0; iter < n; iter++) {
        printf("iter = %3d ", iter);
		//acquisition();
        //display();
        
        //calc_bruit1();
        //calc_stats(X_sig, &S_sig, &Sx_sig, &Sxx_sig);
        //calc_fir();
        //calc_iir();
        
        putchar('\n');
	}
}
// ---------------------
void arduino_init2(void)
// ---------------------
{
	g_c = 0;
    g_i = SIZE + 1;
    
    S_sig = Sx_sig = Sxx_sig = 0;
    S_fir = Sx_fir = Sxx_fir = 0;
    S_iir = Sx_iir = Sxx_iir = 0;
}
// ---------------------
void arduino_loop2(void)
// ---------------------
{
	int iter, n = 5 * SIZE;
    
    // activer les fonctions au fur et a mesure
    
	for(iter = 0; iter < n; iter++) {
        printf("iter = %3d ", iter);
		acquisition(&g_i, &g_c, X_sig); printf("  |  ");
        calc_stats(  g_i,  g_c, X_sig, &S_sig, &Sx_sig, &Sxx_sig); printf("  |  ");
        
        calc_fir  (  g_i,  g_c, X_sig, X_fir, &SS); printf("  |  ");
        //calc_stats(  g_i,  g_c, X_fir, &S_fir, &Sx_fir, &Sxx_fir); printf("  |  ");
        
        calc_iir  (  g_i,  g_c, X_sig, X_iir); printf("  |  ");
        //calc_stats(  g_i,  g_c, X_iir, &S_iir, &Sx_iir, &Sxx_iir); printf("  |  ");
        
        putchar('\n');
	}
}
