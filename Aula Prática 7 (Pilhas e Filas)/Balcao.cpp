#include <queue>
#include <cstdlib>
#include "Balcao.h"

using namespace std;


Cliente::Cliente() {
	// a alterar
}


int Cliente::getNumPresentes() const {
	// a alterar
	return 0;
}


Balcao::Balcao(int te): tempo_embrulho(te) {
	// a alterar
}      


void Balcao:: proximoEvento()
{
	// a alterar
}


void Balcao::chegada()
{
	// a alterar
}   


void Balcao::saida()
{
	// a alterar
}


int Balcao::getTempoAtual() const { return tempo_atual; }


int Balcao::getProxChegada() const { return prox_chegada; }


ostream & operator << (ostream & out, const Balcao & b1)
{
	// a alterar
     return out;
}


int Balcao::getTempoEmbrulho() const {
	// a alterar
	return 0;
}


int Balcao::getProxSaida() const {
	// a alterar
	return 0;
}


int Balcao::getClientesAtendidos() const {
	// a alterar
	return 0;
}


Cliente & Balcao::getProxCliente() {
	// a alterar
	Cliente *c = new Cliente();
	return *c;
}

      
