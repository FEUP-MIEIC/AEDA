#include "Aposta.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>

using namespace std;

bool Aposta::contem(unsigned num) const
{
	return numeros.find(num) != numeros.end();
}


void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
	for(size_t i = 0; i < valores.size() && numeros.size() < n; i++){
		numeros.insert(valores.at(i)); // if it fails, doesn't matter, attempts to insert the next number
	}

}


unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
	unsigned certos = 0;

	for(auto it = sorteio.begin(); it != sorteio.end(); it++){
		if(numeros.find(*it) != numeros.end())
			certos++;
	}

	return certos;
}




