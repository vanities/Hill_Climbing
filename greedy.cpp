/*	Adam Mischke
	9-30-17
	greedy.cpp

	
	command line arguments:
		[1 integer: random number seed, 
		 2 integer: number of dimensions (D) for the SoG function, 
		 3 integer: number of Gaussians (N) for the SoG function]

	    The program should start in a random location X in the [0,10] D-cube, where X is a D-dimensional vector
        The program should use a step size of (0.01*dG(X)/dX) to perform gradient ascent
        The program should terminate when the value of the function no longer increases (within 1e-8 tolerance)
        The program should print the location (X) and SoG function value (G(X)) at each step (see requirements)


        cat data-1.in | ./a.out 5 1 10 > data-1.out
        cat data-1.in | ./a.out 10 1 10 > data-1.out

        ./greedy 10 1 10 > temp-1.out

*/

#include <iostream> // cout
#include <cstdlib>	// seed
#include <cmath>    // fabs 
#include <random>	// mt19937, uniform_real_distribution

#include "SumofGaussians.h"

#define TOLERANCE 0.00000001
#define MIN 0.0
#define MAX 10.0
#define MAX_ITER 10000


using namespace std;

void print(double input [], int);
double runif(double min, double max);

int main(int argc, char* argv[]){

	int seed = atoi(argv[1]);				// first arg
	int dims = atoi(argv[2]);				// second
	int ncenters = atoi(argv[3]);			// third
	
	srand(seed);		// set seed

	SumofGaussians sog(dims,ncenters);		// Sum of Gaussians funtction

	mt19937 gen(seed);
  	uniform_real_distribution<double> dist(MIN,MAX);

	double input[dims];	// input

	// set initial random state
  	for (int i = 0; i < dims; i++)
  		input[i] = dist(gen);

  	int len = sizeof(input)/sizeof(*input);		// used for copying arrays


  	/*	start Gradient Ascent	*/
  	double step_size;							// step size for gradient ascent
	double dz[dims];							// array for derivative
	double current[dims], neighbor[dims];		// current array and neighboring
	double c_eval, n_eval;
	cout.precision(7);							

	copy(input, input+len, current);			// current <= input

	int i =0;
	while(i<MAX_ITER){
		i++;
		print(current, dims);							// print the current
        c_eval = sog.eval(current);
		cout << fixed << c_eval << "\n";		// evaluation of the current
		//cout << i << "\n";
		sog.deriv(current,dz);	// derive dz <= current

		for (int x = 0; x < dims; x++){
			//cout << dz[x] << "\n";

			if (dz[x] > 10)
				step_size = (0.0001 * dz[x]);	
			else
				step_size = (0.01 * dz[x]);					// take a step up
			neighbor[x] = current[x] + step_size;		// neighbor <= current+step
			//cout << "neighbor: " << neighbor[x] << " current: " << current[x] << " step size: " << step_size << "\n";

		}

		//cout << "neighbor: (" << neighbor[0] << "," <<  sog.eval(neighbor) << ") current: (" << current[0] << "," << sog.eval(current) << ") step size: " << step_size << "\n";
                
                n_eval = sog.eval(neighbor);
		// if | neighbor - current | < .0000001, break
		if (fabs(n_eval - c_eval) <= TOLERANCE)
			break; //current[dims];
		

		copy(neighbor, neighbor+len, current);			// current <= neighbor

	}
	//cout << "h= " << c_eval << "\n";

  	return 0;	// we're done

}

double runif(double min, double max){
	return (max - min) * ( (double)rand() / (double)RAND_MAX ) + min;
}

// used for printing
void print(double input [], int dims){
	cout.precision(7);

	for (int x = 0; x < dims; x++){
		cout << fixed <<input[x] << " ";
	}
	//cout << "\n";
}
