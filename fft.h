#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <complex>

using namespace std;

#define FALSE 0
#define TRUE 1

/* global constants */
#define pi 3.14159265358979323846
complex<double> i(0,1);

/* ------ RECURSIVE IMPLEMENTATION ------- */
// Moves all even indices to 1st half odd indices to 2nd half of inputs. 
// inputs : an array of complex numbers N : length of inputs array
void split(complex<double> *inputs, int N){
	
	complex<double>* even = new complex<double>[N/2];
	complex<double>* odd = new complex<double>[N/2];
	int ei = 0;
	int oi = 0;

	for (int j=0; j < N; j++){
		
		if ((j % 2) == 0) 
			even[ei++] = inputs[j]; 
		else 
			odd[oi++] = inputs[j]; 
	}

	int size = N/2;
	memcpy(inputs, even, sizeof(complex<double>)*size);
	memcpy(inputs+size, odd, sizeof(complex<double>)*size);

	delete[] even;
	delete[] odd;
}

// This function computes the fast fourier transform of a list of complex numbers 
// of length N.
// x : input array of complex number that represent a sampled function amplitude 
// N : the length of x must be a power of 2 

void fast_fourier(complex<double>* x, double N)
{
	// base of recursion
	if (N == 1)return;
	
	// no rounding needed if N is base 2
	int n = N/2;

	/* set primitive root of unity */
	complex<double> wn = exp((2*pi*i)/N);
	complex<double> w = 1;

	// move odd and even index to each half of array x
	split(x, 2*n);
	
	// even and odd
	fast_fourier(x, n);
	// pass pointer starting at the n/2th element
	fast_fourier(x+n, n);

	complex<double> even(0,0);
	complex<double> odd(0,0);

	for (int k = 0; k < n; k++){
 		even = x[k];
		odd = x[k+n];

		x[k] = even + w*odd;
		x[k+n] = even - w*odd;

		w = w*wn;
	}	
}

void ifft(complex<double>* x, double N)
{
	// base of recursion
	if (N == 1)return;
	
	/* no rounding needed if N is base 2 */
	int n = N/2;

	/* set primitive root of unity */
	complex<double> wn = exp((-2*pi*i)/N)/N;
	complex<double> w = 1;

	// move odd and evened indexed to each half of array x
	split(x, 2*n);
	
	// even and odd	
	ifft(x, n);
	// pass pointer starting at the n/2th element
	ifft(x+n, n);

	complex<double> even(0,0);
	complex<double> odd(0,0);

	for (int k = 0; k < n; k++){
		even = x[k];
		odd = x[k+n]; /* k + N/2 */

		x[k] = even + w*odd;
		x[k+n] = even - w*odd;

		w = w*wn;
	}	
}

// calculate the magnitude of a complex number 
double magnitude(complex<double> p, int N) 
{ 
	return 2*sqrt(pow(p.real(),2) + pow(p.imag(),2))/N;
}

// truncate very small numbers to 0
double approx_zero(double d) { 
	if (abs(d) < 0.0000000000001)	return 0;
	else 				return d;
}

// Default behavior prints the contents of a list. When extras == TRUE,
//   computes the magnitude and phase of complex inputs and displays
void printlist(complex<double>* l, int N, bool extras){
	
	for (int i = 0; i < N; i++)
		cout << " " << l[i];

	double mag = 0;
	double phase = 0; 

	if (extras){
		for (int i = 0; i < N; i++){
			mag = magnitude(l[i],N);
			phase = atan(l[i].imag()/l[i].real());

			cout << endl;
			cout << "Frequency bin ["<< i <<"]"<<endl;
			cout << "Magnitude: " << mag << endl;
			cout << "Phase: " << phase << endl;
		}
	}	
	cout << endl;
}

#pragma once
