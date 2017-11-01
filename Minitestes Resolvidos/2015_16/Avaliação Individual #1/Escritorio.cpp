#include "Escritorio.h"
#include <iostream>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }

Documento Documento::operator+(const Documento &d) const{
	int numpag = this->numPaginas + d.numPaginas;
	float pP = (this->numPaginas*this->pPreto + d.numPaginas*d.pPreto)/numpag;
	float pA = (this->numPaginas*this->pAmarelo + d.numPaginas*d.pAmarelo)/numpag;

	return Documento(numpag, pP, pA);
}


//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }



//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }

bool ImpressoraPB::imprime(Documento doc1)
{
	if(doc1.getNumPaginas() > numPagImprimir)
		return false;

	// imprime
	docsImpressos.push_back(doc1);
	numPagImprimir -= doc1.getNumPaginas();
	return true;
}

string ImpressoraPB::getTipo()
{
	return "PB";
}


//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo) return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}

bool ImpressoraCores::imprime(Documento doc1)
{
	float pPreto = doc1.getPercentagemPreto(), pAmarelo = doc1.getPercentagemAmarelo();
	int numPag = doc1.getNumPaginas();
	if(numPag*pPreto > numPagImprimirPreto || numPag*pAmarelo > numPagImprimirAmarelo)
		return false;
	
	// imprime
	docsImpressos.push_back(doc1);
	numPagImprimirPreto -= numPag*pPreto;
	numPagImprimirAmarelo -= numPag*pAmarelo;
	return true;
}

string ImpressoraCores::getTipo()
{
	return "Cores";
}



//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }

//

int Escritorio::numImpressorasSemResponsavel() const
{
	// numero de impressoras no escritório
	int counter = impressoras.size();

	// determinar quantas impressoras têm um responsavel
	for(auto it = funcionarios.cbegin(); it != funcionarios.cend(); it++)
	{
		counter -= it->getImpressoras().size();
	}

	return counter;
}


vector<Impressora *> Escritorio::retiraImpressoras(int ano1)
{
	vector<Impressora *> v;
	for(auto i = impressoras.begin(); i != impressoras.end(); )
	{
		if((*i)->getAno() < ano1)
		{
			v.push_back(*i);
			i = impressoras.erase(i); // erase retorna iterator para elemento seguinte ao elemento removido
		}
		else
		{
			std::cout << endl;
			++i;
		}
	}

	return v;
}

Impressora * Escritorio::imprimeDoc(Documento doc1) const
{
	bool foundPrinter = false;
	for(auto i = impressoras.cbegin(); i != impressoras.cend() && !foundPrinter; i++)
	{
		foundPrinter = (*i)->imprime(doc1);

		if(foundPrinter) return *i;
	}

	return new ImpressoraPB("inexistente", 0, 0);
}

vector<Impressora *> Escritorio::tonerBaixo() const
{
	vector<Impressora *> imp;

	for(auto i = impressoras.cbegin(); i != impressoras.cend(); i++)
	{
		int numPaginasImprimirLimite;
		if((*i)->getTipo() == "PB")	numPaginasImprimirLimite = 30;
		else numPaginasImprimirLimite = 20;

		if((*i)->getNumPaginasImprimir() < numPaginasImprimirLimite)
			imp.push_back(*i);
	}

	return imp;
}

string Escritorio::operator()(string codImp) const
{
	for(auto i = funcionarios.cbegin(); i != funcionarios.cend(); i++)
	{
		vector<Impressora *> imp = i->getImpressoras();
		for(auto j = imp.cbegin(); j != imp.cend(); j++)
		{
			if((*j)->getCodigo() == codImp)
				return i->getCodigo();
		}
	}

	return "nulo";
}