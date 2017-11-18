/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
#include <sstream>
#include <ctime>
using namespace std;

unsigned Jogo::numPalavras(string frase) {
	if (frase.length() == 0)
		return 0;
	int n = 1;
	int pos = frase.find(' ');
	while (pos != string::npos) {
		frase = frase.substr(pos + 1);
		pos = frase.find(' ');
		n++;
	}
	return n;
}

Jogo::Jogo() {
	this->criancas.clear();
}

Jogo::Jogo(list<Crianca>& lc2) {
	this->criancas = lc2;
}

void Jogo::insereCrianca(const Crianca &c1) {
	this->criancas.push_back(c1); // adds a new kid at the end of the list
}

list<Crianca> Jogo::getCriancasJogo() const {
	return this->criancas;
}

string Jogo::escreve() const {
	stringstream ss;
	for (auto it = criancas.cbegin(); it != this->criancas.cend(); it++) {
		ss << (*it).escreve() << endl;
	}

	return ss.str();
}

Crianca& Jogo::perdeJogo(string frase) {
	unsigned int n_words = numPalavras(frase); // phrase words
	unsigned int n_kids = this->criancas.size(); // number of kids playing
	list<Crianca>::iterator it = criancas.begin();
	while (criancas.size() > 1) {

		/*
		 * Iterators on list containers are Bidirectional, therefore don't allow arithmetic operations
		  	 except the increment/decrement operators
		 * This loop is just to find the kid who is saved on this round
		 * If (n_words - 1) % n_kids is 0, the first kid is saved, if it's 1 the second kid on list is saved, ...
		 */
		for (size_t i = 0; i < (n_words - 1) % n_kids; i++)
		{
			if(it == criancas.end()) it = criancas.begin();
			else ++it;
		}

		// remove saved kid from the game
		it = criancas.erase(it);

		/*
		 * erase method returns an iterator to the following element on the list
		 * if the saved kid was the last one, then 'it' is 'past-the-last' element and must be updated to 'first'
		 */
		if(it == criancas.end()) it = criancas.begin();

		// updates variable
		n_kids = this->criancas.size();
	}

	// create of a copy of the kid who lost this round, the remaining one
	Crianca *c1 = new Crianca(criancas.front().getNome(), criancas.front().getIdade());

	// return
	return *c1;
}

list<Crianca>& Jogo::inverte() {

	criancas.reverse();

	return criancas;
}

list<Crianca> Jogo::divide(unsigned id) {
	list<Crianca> lst;
	list<Crianca>::iterator it = criancas.begin();

	while(it != criancas.end())
	{
		if(it->getIdade() > id){
			lst.push_back(*it);
			it = criancas.erase(it);
		}
		else {
			it++;
		}

	}

	return lst;
}

void Jogo::setCriancasJogo(const list<Crianca>& l1) {
	this->criancas = l1;
}

bool Jogo::operator==(Jogo& j2) {

	list<Crianca>::const_iterator it1 = criancas.cbegin(), it2 = j2.criancas.cbegin();

	while(it1 != criancas.cend() && it2 != j2.criancas.cend())
	{
		if(it1->getNome() != it2->getNome() ||
				it1->getIdade() != it2->getIdade())
			return false;

		it1++;
		it2++;
	}

	return true;
}

list<Crianca> Jogo::baralha() const {

	list<Crianca> aux = criancas;
	list<Crianca> res;

	std::srand(std::time(0)); // random seed

	while(!aux.empty())
	{
		size_t pos = (rand() % aux.size()) + 1;
		list<Crianca>::const_iterator it = aux.cbegin();

		while(pos != 1) {
			it++;
			pos--;
		}

		res.push_back(*it);
		aux.erase(it);
	}

	return res;
}
