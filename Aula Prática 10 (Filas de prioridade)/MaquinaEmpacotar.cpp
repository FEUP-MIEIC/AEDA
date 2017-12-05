/*
 * Empacotador.cpp
 */

#include "MaquinaEmpacotar.h"


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


/* a implementar pelos estudantes */

unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
	unsigned counter = 0;

	for(auto it = objs.begin(); it != objs.end(); it++) {
		if(it->getPeso() <= capacidadeCaixas) {
			objetos.push(*it);
			it = objs.erase(it);
			it--;
			counter++;
		}
	}
	return counter;
}


Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	/*
	 * On a priority queue, we only have access to the top element!
	 * The boxes are sorted by least free weight, so I need to remove the top elements
	 	 until I find a box with enough free weight for 'obj'. The removed boxes are preserved
	 	 on vector 'aux', and will be later re-added to 'caixas' (priority queue)
	 */
	vector<Caixa> aux;
	bool found = false;
	Caixa cx;

	while(!caixas.empty() && !found) {
		if(caixas.top().getCargaLivre() >= obj.getPeso()) {
			cx = caixas.top();
			caixas.pop();
			found = true;
		}
		else {
			aux.push_back(caixas.top());
			caixas.pop();
		}
	}

	// re-add the boxes
	for(size_t i = 0; i < aux.size(); i++) {
		caixas.push(aux.at(i));
	}

	return cx;
}


unsigned MaquinaEmpacotar::empacotaObjetos() {
	// TODO
	return 0;
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
	// TODO
	return "";
}



Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	// TODO
	Caixa cx;
	return cx;
}



