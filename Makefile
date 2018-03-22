# make build for p1
all:SumofGaussians.h SumofGaussians.cpp greedy.cpp sa.cpp 
	g++ -std=c++11 SumofGaussians.cpp greedy.cpp -o greedy
	g++ -std=c++11 SumofGaussians.cpp sa.cpp -o sa

clean: 
	$(RM) greedy sa
