/*
 * Condominio.h
 */

#ifndef CONDOMINIO_H_
#define CONDOMINIO_H_

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Imovel {
	int areaHabitacao;
	string proprietario;
	int ID;
public:
	Imovel(int areaH, string prop, int id=0);
	int getID() const;
	virtual int getAreaHabitacao() const;
	string getProprietario() const;
	void setID(int id);
	virtual float mensalidade() const;
};

class Apartamento: public Imovel {
	int andar;
public:
	Apartamento(int areaH, int anda, string prop, int id=0);
	float mensalidade() const;

};

class Vivenda: public Imovel {
   int areaExterior;
   bool piscina;
public:
   Vivenda(int areaH, int areaExt, bool pisc, string prop, int id=0);
   float mensalidade() const;
   int getAreaHabitacao() const;
};


class Urbanizacao {
	string nome;
	int ID;
	vector<Imovel *> imoveis;
	static int static_id;
	int imoveis_id;
public:
	Urbanizacao(string nm, int id);
	Urbanizacao(string nm);
	void adicionaImovel(Imovel *im1);
	vector<Imovel *> getImoveis() const;
	string getNome() const;
	int getID() const;
	vector<Imovel *> areaSuperiorA(int area1) const;
	bool operator> (const Urbanizacao &u) const;
	unsigned int getNumProprietarios() const;
	static void resetID();
};


class ECondominio {
	vector<Urbanizacao> urbanizacoes;
public:
	void adicionaUrbanizacao(Urbanizacao urb1);
	vector<Urbanizacao> getUrbanizacoes() const;
	float  mensalidadeDe(string nomeProp) const;
	vector<Urbanizacao> removeUrbanizacaoDe(string nomeProp);
	vector<Imovel *> operator() (string nome) const;
};

#endif /* CONDOMINIO_H_ */
