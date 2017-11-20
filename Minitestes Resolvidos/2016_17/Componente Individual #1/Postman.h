/*
 * Postman.h
 */

#ifndef SRC_POSTMAN_H_
#define SRC_POSTMAN_H_

#include "Mail.h"
#include <string>
#include <vector>

class Postman {
	unsigned int id;
	string name;
	vector<Mail *> myMail;
public:
	Postman();
	Postman(string name);
	void setName(string nm);
	void addMail(Mail *m);
	void addMail(vector<Mail *> mails);
	string getName() const;
	vector<Mail *> getMail() const;
	unsigned int getID() const;
	static unsigned int postman_counter;
	bool operator< (Postman &p);
	unsigned int diff_zipcodes();
};

class NoPostmanException
{
public:
	NoPostmanException(string name);
	string getName() const;
private:
	string name;
};

#endif /* SRC_POSTMAN_H_ */
