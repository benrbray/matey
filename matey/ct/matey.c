#include <stdio.h>

// sums a list of numbers
int sum(int size, int *numbers){
	int result = 0;
	
	for(int i = 0; i < size; i++){
		result += numbers[i];
	}
	
	return result;
}

// computes <a,b>
double dot(int size, double *a, double *b){
	double result = 0;
	
	for(int k = 0; k < size; k++){
		result += a[k] * b[k];
	}
	
	return result;
}

// y := y + ax
void saxpy(int size, double a, double *x, double *y){
	for(int k = 0; k < size; k++){
		y[k] += a * x[k];
	}
}
