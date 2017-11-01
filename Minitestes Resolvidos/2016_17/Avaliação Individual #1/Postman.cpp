/*
 * Postman.cpp
 */
#include "Postman.h"

unsigned int Postman::postman_counter = 1;

Postman::Postman(): id(0) {}

Postman::Postman(string name)
{
	this->id = postman_counter;
	this->name = name;

	postman_counter++;
}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator< (Postman &p)
{
	return this->diff_zipcodes() < p.diff_zipcodes();
}

unsigned int Postman::diff_zipcodes()
{
	unsigned int counter = 0;
	for(auto i = this->myMail.cbegin(); i != this->myMail.cend(); i++)
	{
		bool foundEqualElem = false;
		for(auto j = i+1; j != this->myMail.cend() && !foundEqualElem; j++)
		{
			if ((*j)->getZipCode() == (*i)->getZipCode()) foundEqualElem = true;
		}
		if(!foundEqualElem) counter++;
	}

	return counter;
}