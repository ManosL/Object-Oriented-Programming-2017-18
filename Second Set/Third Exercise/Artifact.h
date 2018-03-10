#ifndef __ARTIFACTS__
#define __ARTIFACTS__

#include <iostream>
#include <string>

enum mMovement{IMPRESSIONISM = 0,EXPRESSIONISM,NATURALISM}; //masterpiece movement
enum mCondition{BAD = 0,GOOD,EXCELLENT};					//masterpiece condition
enum pTechnique{OIL = 0,AQUARELLE,TEMPERA};					//painting technique
enum sMaterial{IRON = 0,STONE,WOOD};						//sculpture material

class Artifact
{
private:
	const unsigned int Index;
	const std::string Creator;
	const time_t year;

public:

	Artifact(const std::string&,const time_t&);

	static unsigned int curr_index;				//I have the curr_index as static because 
												//the first Artifact will have Index 1 the second Index 2 etc.

	virtual void getInfo() const;

	virtual const bool evaluate(const mMovement&,const mCondition&) const = 0;
	virtual const bool evaluate(const mMovement&) const = 0;

	void getIndex() const{ std::cout<<"Artifact's Index: "<<Index<<std::endl; }

	virtual ~Artifact();
};

class Masterpiece: public Artifact
{
private:
	const mMovement movement;
	mCondition condition;

public:
	Masterpiece(const std::string&,const time_t&,const mMovement&,const mCondition&);

	void getInfo() const;

	const mMovement& getMovement() const{ return movement; }
	const mCondition& getCondition() const{ return condition; }

	~Masterpiece();
};

class Painting: public Masterpiece
{
private:
	const size_t length;
	const size_t width;
	const size_t surface;
	const pTechnique technique;

public:

	Painting(const std::string&,const time_t&,const mMovement&,const mCondition&,const size_t&,const size_t&,const pTechnique&);

	void getInfo() const;

	const bool evaluate(const mMovement&,const mCondition&) const;
	const bool evaluate(const mMovement&) const;


	~Painting();
};

class Sculpture: public Masterpiece
{
private:
	const size_t volume;
	const sMaterial material;

public:

	Sculpture(const std::string&,const time_t&,const mMovement&,const mCondition&,const size_t&,const sMaterial&);

	void getInfo() const;

	const bool evaluate(const mMovement&,const mCondition&) const;
	const bool evaluate(const mMovement&) const;

	~Sculpture();
};


#endif