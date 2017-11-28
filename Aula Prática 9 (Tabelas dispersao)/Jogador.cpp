#include "Jogador.h"


void Jogador::adicionaAposta(const Aposta & ap)
{
	apostas.insert(ap);
}

unsigned Jogador::apostasNoNumero(unsigned num) const
{
	unsigned count = 0;

	for(auto it = apostas.begin(); it != apostas.end(); it++){
		if(it->contem(num))
			count++;
	}
	return count;
}


tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
	tabHAposta money;

	for(auto it_aposta = apostas.begin(); it_aposta != apostas.end(); it_aposta++){
		unsigned counter = 0;
		for(auto it_sort = sorteio.begin(); it_sort != sorteio.end() && counter < 3; it_sort++) {
			if(it_aposta->contem(*it_sort))
				counter++;
		}

		if(counter == 3) {
			money.insert(*it_aposta);
		}
	}
	return money;
}
