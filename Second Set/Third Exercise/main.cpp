#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>
#include <string>

#include "Artifact.h"

using namespace std;

static const time_t CURRENT_YEAR = 2018;   //I make this define's for better understanding of my program

static const size_t MIN_LENGTH = 150;
static const size_t MAX_LENGTH = 300;

static const size_t MIN_WIDTH = 150;
static const size_t MAX_WIDTH = 300;

static const size_t MIN_VOLUME = 150;
static const size_t MAX_VOLUME = 300;

void auction(const vector<Artifact*>&,const mMovement&,const mCondition&);
string num_to_string(const int&);

int main(int argc,char* argv[]){
	
	vector<Artifact*> artifacts;
	int artifact_number;
	mMovement auction_movement;
	mCondition auction_condition;

	srand(time(NULL));


	if(argc != 4){								//If the user don't give enough arguments
		cout<<"Wrong input"<<endl;
		cout<<"Right format of input"<<endl;
		cout<<"<number of artifacts> <movement value> <condition value>"<<endl;
		return -1;
	}

	if(atoi(argv[1]) <= 0){						//If the user give invalid number of artifacts
		cout<<"Wrong input"<<endl;
		cout<<"Number of artifacts should take a number bigger than 0."<<endl;
		return -1;
	}
	else{
		artifact_number = atoi(argv[1]);
	}

	//If the user give wrong values
	if(strcmp(argv[2],"impressionism") && strcmp(argv[2],"expressionism") && strcmp(argv[2],"naturalism")){
		cout<<"Wrong input"<<endl;
		cout<<"Movement should take these values: impressionism,expressionism or naturalism."<<endl;
		return -1;
	}
	else{
		if(!strcmp(argv[2],"impressionism")) auction_movement = IMPRESSIONISM;
			else
				if(!strcmp(argv[2],"expressionism")) auction_movement = EXPRESSIONISM;
			else
				if(!strcmp(argv[2],"naturalism")) auction_movement = NATURALISM;
	}

	if(strcmp(argv[3],"bad") && strcmp(argv[3],"good") && strcmp(argv[3],"excellent")){
		cout<<"Wrong input"<<endl;
		cout<<"Condition should take these values: bad,good or excellent."<<endl;
		return -1;
	}
	else{
		if(!strcmp(argv[3],"bad")) auction_condition = BAD;
			else
				if(!strcmp(argv[3],"good")) auction_condition = GOOD;
			else
				if(!strcmp(argv[3],"excellent")) auction_condition = EXCELLENT;
	}

	for(int i = 0;i < artifact_number;i++){
		string current = num_to_string(i + 1);				//I need this to have the creator name as Creator1,Creator2, etc.
		mMovement move = (mMovement) (rand() % 3);
		mCondition cond = (mCondition) (rand() % 3);

		if(rand() % 2 == 0){
			pTechnique tech = (pTechnique) (rand() % 3);
			artifacts.push_back(new Painting("Creator"+current,rand()%CURRENT_YEAR,move,cond,(rand()%(MAX_LENGTH - MIN_LENGTH))+ MIN_LENGTH,(rand()%(MAX_WIDTH - MIN_WIDTH))+MIN_WIDTH,tech));
		}
		else{
			sMaterial material = (sMaterial) (rand() % 3);
			artifacts.push_back(new Sculpture("Creator"+current,rand()%CURRENT_YEAR,move,cond,(rand()%(MAX_VOLUME-MIN_VOLUME))+MIN_VOLUME,material));
		}
	}

	auction(artifacts,auction_movement,auction_condition);		//Runs the auction function 

	for(int i = 0;i < artifact_number;i++){						//Deletes the artifacts
		delete artifacts[i];
	}

	return 0;
}

void auction(const vector<Artifact*>& artifacts,const mMovement& movement,const mCondition& condition){
	const size_t size = artifacts.size();

	for(int i = 0;i < size;i++){			//Does the necessary fields
		artifacts[i]->getIndex();
		artifacts[i]->getInfo();
		cout<<"Evaluate returned: "<<artifacts[i]->evaluate(movement,condition)<<endl<<endl;
	}

	return;
}

string num_to_string(const int& num){
	int curr_num = num;
	string result;

	while(curr_num != 0){
		result.insert(result.begin(),(char) ((curr_num % 10) + 48));
		curr_num /= 10;
	}

	return result;
}
