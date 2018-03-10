#include "Artifact.h"

using namespace std;

unsigned int Artifact::curr_index = 1;

Artifact::Artifact(const std::string& creator_,const time_t& year_):
Index(curr_index),Creator(creator_),year(year_)
{
	curr_index++;

	cout<<"Creating an instance of Artifact"<<endl;
}

void Artifact::getInfo() const{

	cout<<"Creator: "<<Creator<<endl;
	cout<<"Creation year: "<<year<<endl; 
}

Artifact::~Artifact(){
	cout<<"Destroying an instance of Artifact"<<endl<<endl;
}

Masterpiece::Masterpiece(const std::string& creator,const time_t& year,const mMovement& movement_,const mCondition& condition_):
Artifact(creator,year),movement(movement_),condition(condition_)
{
	cout<<"Creating an instance of Masterpiece"<<endl;
}

void Masterpiece::getInfo() const{
	Artifact::getInfo();			//Calling Artifact's getInfo() function

	cout<<"Movement: ";
	switch(movement){
		case IMPRESSIONISM:
			cout<<"Impressionism"<<endl;
			break;

		case EXPRESSIONISM:
			cout<<"Expresionism"<<endl;
			break;

		case NATURALISM:
			cout<<"Naturalism"<<endl;
			break;		
	}

	cout<<"Condition: ";
	switch(condition){
		case BAD:
			cout<<"Bad"<<endl;
			break;

		case GOOD:
			cout<<"Good"<<endl;
			break;

		case EXCELLENT:
			cout<<"Excellent"<<endl;
			break;		
	}

	return;
}

Masterpiece::~Masterpiece(){
	cout<<"Destroying an instance of Masterpiece"<<endl;
}

Painting::Painting(const std::string& creator,const time_t& year,const mMovement& movement,const mCondition& condition,const size_t& length_,const size_t& width_,const pTechnique& technique_):
Masterpiece(creator,year,movement,condition),length(length_),width(width_),technique(technique_),surface(length_*width_)
{
	cout<<"Creating an instance of Painting"<<endl<<endl;
}

void Painting::getInfo() const{
	cout<<"Painting Info"<<endl;		//Tells that Paintng's getIndo() function called
	Masterpiece::getInfo();

	cout<<"Length: "<<length<<endl;
	cout<<"Width: "<<width<<endl;
	cout<<"Surface: "<<length*width<<endl;

	cout<<"Technique: ";
	switch(technique){
		case OIL:
			cout<<"Oil"<<endl;
			break;

		case AQUARELLE:
			cout<<"Aquarelle"<<endl;
			break;

		case TEMPERA:
			cout<<"Tempera"<<endl;	
			break;	
	}

	return;
}

const bool Painting::evaluate(const mMovement& movement_,const mCondition& condition_) const  //Does the necessary matching
{
	return ((Masterpiece::getMovement() == movement_) && ((Masterpiece::getCondition() == condition_) || (Masterpiece::getCondition() == EXCELLENT && condition_ == GOOD)));	
}

const bool Painting::evaluate(const mMovement& movement) const{		//If I call the function like this

	return Painting::evaluate(movement,GOOD);						//It is like I consider by default the condition as GOOD
}


Painting::~Painting(){
	cout<<"Destroying an instance of Painting"<<endl;
}

Sculpture::Sculpture(const std::string& creator,const time_t& year,const mMovement& movement,const mCondition& condition,const size_t& volume_,const sMaterial& material_):
Masterpiece(creator,year,movement,condition),volume(volume_),material(material_)
{
	cout<<"Creating an instance of Sculpture"<<endl<<endl;
}

void Sculpture::getInfo() const{
	cout<<"Sculpture Info"<<endl;
	Masterpiece::getInfo();

	cout<<"Volume: "<<volume<<endl;

	cout<<"Material: ";
	switch(material){
		case IRON:
			cout<<"Iron"<<endl;
			break;

		case STONE:
			cout<<"Stone"<<endl;
			break;

		case WOOD:
			cout<<"Wood"<<endl;
			break;		
	}

	return;
}

const bool Sculpture::evaluate(const mMovement& movement_,const mCondition& condition_) const
{
	return ((Masterpiece::getMovement() == movement_) && (Masterpiece::getCondition() == condition_));
}

const bool Sculpture::evaluate(const mMovement& movement) const{

	return evaluate(movement,EXCELLENT);
}


Sculpture::~Sculpture(){
	cout<<"Destroying an instance of Sculpture"<<endl;
}
