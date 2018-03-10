#include <iostream>
#include <cstdlib>
#include <ctime>

#include "train_simulation.h"

using namespace std;

int main(int argc,char* argv[]){
	Train* train;

	srand(time(NULL));

	if(argc < 3 || argc > 3){
		cout<<"Wrong input"<<endl;
		return -1;
	}

	train = new Train(atoi(argv[1]),atoi(argv[2]));   //argv[1] = stations argv[2] = waggons

	train->operate();								  //The train begins

	train->printStatistics();						  //after the operations prints the statistics

	delete train;

	return 0;
}