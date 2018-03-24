# Hill_Climbing
Hill Climbing techniques used to find maximums (or minimums) of multi-dimensional functions using Greedy and Simulated Annealing search methods.

The traditional Sum of Gaussians is used to make a random function to test on. Our first goal was for a greedy method, "greedy.cpp". The second being a harder, but better solution of using Simulated Annealing, "sa.cpp". There's a bunch of scripts in that folder, mostly testing hundreds if not thousands of multi-dimensional Sum of Gaussian functions. Simulated annealing is interesting and not trivial at all.

See report for more details.

### Instructions:
1. compile the project with:
 ```make```
 
2. run the code for greedy hill climbing, where:
```./greedy seed number_of_dimensions number_of_gaussian_function_centers``<br>
or for simulated annealing:<br>
```./sa seed number_of_dimensions number_of_gaussian_function_centers 
