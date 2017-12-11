/*
 * Caixa.cpp
 */

#include "Caixa.h"
#include <sstream>


Objeto::Objeto(unsigned idObj, unsigned pesoObj): id(idObj), peso(pesoObj)
{}

unsigned Objeto::getID() const {
	return id;
}

unsigned Objeto::getPeso() const {
	return peso;
}

Caixa::Caixa(unsigned cap): id(ultimoId++), capacidade(cap), cargaLivre(cap)
{}

unsigned Caixa::getID() const {
	return id;
}

unsigned Caixa::getCargaLivre() const {
	return cargaLivre;
}

void Caixa::addObjeto(Objeto& obj) {
	cargaLivre -= obj.getPeso();
	objetos.push(obj);
}

void Caixa::resetID(){
	ultimoId = 1;
}

unsigned Caixa::getSize() const {
	return objetos.size();
}


ostream& operator<<(ostream& os, Objeto obj) {
	os << "O" << obj.getID() << ": " << obj.getPeso();
	return os;
}

unsigned Caixa::ultimoId = 1;


/* a implementar pelos estudantes */

bool Objeto::operator<(const Objeto& o1) const {
	return this->getPeso() < o1.getPeso();
}

bool Caixa::operator<(const Caixa& c1) const {
	return this->getCargaLivre() > c1.getCargaLivre();
}


string Caixa::imprimeConteudo() const {
	stringstream ss;
	if(objetos.empty()) {
		ss << "Caixa " << id << " vazia!\n";
		return ss.str();
	}

	STACK_OBJS obj = objetos;
	ss << "C" << id << "[ ";
	while(!obj.empty()) {
		 ss << obj.top() << " ";
		 obj.pop();
	}
	ss << "]";

	return ss.str();
}


