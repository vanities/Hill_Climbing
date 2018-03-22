/*	Adam Mischke
	9-30-17
	sa.cpp



	Create a C++ program which uses simulated annealing (SA) to obtain the maximum value of the SoG function in D dimensions (sa.cpp)
        The program should take 3 command-line arguments [integer: random number seed, 
        												  integer: number of dimensions for the SoG function, 
        												  integer: number of Gaussians for the SoG function]
        
        The program should start in a random location X in the [0,10] D-cube, where X is a D-dimensional vector
        
        The program should create an annealing schedule for the termperature (T), and slowly lowering T over time
        
        On each iteration, the program should generate a new location Y = X + runif(-0.01,0.01), 
       	and choose to accept it or reject it based on the metropolis criterion:
        if G(Y) > G(X) then accept Y; otherwise accept Y with probability e^((G(Y)-G(X))/T) 
        
        The program should terminate at a maximum of 100000 iterations
        
        The program should print the location (X) and SoG function value (G(X)) at each step (see requirements)

        T = 20000
        5 sdtep

*/

#include <iostream> // cout
#include <cstdlib>	// seed
#include <cmath>    // fabs 
#include <random>	// mt19937, uniform_real_distribution


#include "SumofGaussians.h"

#define MAX_ITER 100000
#define MIN 0.0
#define MAX 10.0
// .05 => .1
#define LIMIT .01

using namespace std;

void print(double input [], int dims);
double runif(double min, double max);

int main(int argc, char* argv[]){
	
  	int seed = atoi(argv[1]);			// set seed 1st arg
  	int dims = atoi(argv[2]);			// set dimensions 2nd arg
  	int ncenters = atoi(argv[3]);		// set number of centered Gaussian functions 3rd arg
  	//int LIMIT = atoi(argv[4]);
  	//LIMIT*=.01;
  	srand(seed);						// set seed
  	SumofGaussians sog(dims,ncenters);	// create Sum of Gaussian object

  	mt19937   gen(seed);
  	uniform_real_distribution<double> dist(MIN,MAX);
  	uniform_real_distribution<double> step(-0.01,0.01);


  	double input[dims];					// initial input

  	// set initial random state
  	for (int i = 0; i < dims; i++)
  		input[i] = dist(gen);

  	int len = sizeof(input)/sizeof(*input);		// used for copying arrays


  	/*	start Gradient Ascent	*/
  	double step_size;							// step size for gradient ascent
	double current[dims], neighbor[dims];		// current array and neighboring
	double temperature=1;						// set the temperature
	cout.precision(7);							

	double highest=0;
	copy(input, input+len, current);				// current <= input
        double c_eval, n_eval;

	for (int i=0; i<MAX_ITER; i++){

		print(current, dims);                                   // print the current
        c_eval = sog.eval(current);
		cout << fixed << c_eval << "\n";		        // evaluation of the current


		for (int x = 0; x < dims; x++){
			step_size = step(gen);	    					// take a step
			neighbor[x] = current[x] + step_size;			// neighbor <= current+step
		}

		//cout << "neighbor: " << sog.eval(neighbor) << " current: " << sog.eval(current) << " step size: " << step_size << "\n";
		//if (sog.eval(current) > highest)
		//	highest=sog.eval(current);

		// if G(Y) > G(X), accept
                n_eval = sog.eval(neighbor);
		if (n_eval >= c_eval)
		    copy(neighbor, neighbor+len, current);			// current <= neighbor
		

		// else accept Y with a probability of.. e^((G(Y)-G(X))/T)
		else{
			double probability = exp( (n_eval-c_eval) / temperature);
			// fun testing =>>>>> double result = runif(0.0,1.0);

			//cout << "temp: " << temperature << " prob: " << probability << "<" << LIMIT <<  "?\n";

			if (probability > LIMIT){
				//cout << "accepted.\n";
				copy(neighbor, neighbor+len, current);			// current <= neighbor
			}
			
			//else
			//	cout << "not accepted.\n";
			
			
		}
		// *= >=.99984.... .99985, .99987
		temperature*=.999;
	}
	//cout << "h= " << highest << "\n";
	//cout << "h= " << c_eval << "\n";
	return 0;	// we're done

}

// used for printing
void print(double input [], int dims){
	cout.precision(7);

	for (int x = 0; x < dims; x++){
		cout << fixed <<input[x] << " ";
	}
	//cout << "\n";
}
