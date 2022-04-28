#include "fft.h"

int main(int argc, const char* argv[]){
	
	double amplitude = 0;
	/* change samples for more data points */
	int samples = 64;
	double interval = (2*pi)/(double)samples;
	double theta = 0;

	cout << "The Fast Fourier Transform" << endl;

	complex<double>* s = new complex<double>[samples];

	/* to store for plotting */
	double* tvalues = new double[samples];
	double* amplitudes = new double[samples];

	/* sample over a function */
	for (int t = 0; t < samples; t++)
	{
		theta = t*interval;

		amplitude = sin(6*theta)+0.3*sin(2*theta)+0.7*sin(35*theta)+0.1*sin(theta)+0.5*cos(theta*theta/387);

		tvalues[t] = theta;
		amplitudes[t] = amplitude;

		s[t].real(amplitude);
		s[t].imag(0);
	}	

	cout << "Input array:" << endl;
	printlist(s, samples, FALSE);
	
	fast_fourier(s,samples);

	cout << "Output array: " << endl;
	printlist(s,samples,TRUE);

	/* send values to file for plotting */
	ofstream outdata;
	outdata.open("data.txt");
	int idx=0;

	outdata.precision(4);
	for (idx=0; idx < samples; idx++)
		outdata << tvalues[idx] << " ";
	outdata << endl;

	for (idx=0; idx < samples; idx++)
		outdata << approx_zero(amplitudes[idx]) << " ";
	outdata << endl;

	for (idx=0; idx < samples; idx++)
		outdata << idx << " ";
	outdata << endl;

	for (idx=0; idx < samples; idx++)
		outdata << approx_zero(magnitude(s[idx],samples)) << " ";

	outdata << endl;

	outdata.close();

	ifft(s,samples);
	ofstream q;
	q.open("q.txt");
	idx=0;

	q.precision(4);
	for (idx=0; idx < samples; idx++)
		q << tvalues[idx] << " ";
	q << endl;

	for (idx=0; idx < samples; idx++)
		q << approx_zero(amplitudes[idx]) << " ";
	q << endl;

	for (idx=0; idx < samples; idx++)
		q << idx << " ";
	q << endl;

	for (idx=0; idx < samples; idx++)
		q << approx_zero(magnitude(s[idx],samples)) << " ";

	q << endl;

	q.close();

	delete[] s;
	delete[] tvalues;
	delete[] amplitudes;
}
