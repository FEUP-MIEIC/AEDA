/*
 * Condominio.cpp
 */

#include "Condominio.h"
#include <algorithm>
#include <iostream>
//////////////////////
// IMOVEL
/////////////////////

Imovel::Imovel(int areaH, string prop, int id): areaHabitacao(areaH), proprietario(prop), ID(id)
{}

int Imovel::getID() const
{ return ID; }

void Imovel::setID(int id)
{ ID=id; }

int Imovel::getAreaHabitacao() const
{ return areaHabitacao; }

string Imovel::getProprietario() const
{ return proprietario; }

float Imovel::mensalidade() const 
{
    return 50 + 0.2*areaHabitacao;
}

//////////////////////
// APARTAMENTO
/////////////////////
Apartamento::Apartamento(int areaH, int anda, string prop, int id): Imovel(areaH,prop,id), andar(anda)
{}

float Apartamento::mensalidade() const
{
    return Imovel::mensalidade() + andar;
}

//////////////////////
// VIVENDA
/////////////////////

Vivenda::Vivenda(int areaH, int areaExt, bool pisc, string prop, int id):Imovel(areaH,prop,id), areaExterior(areaExt), piscina(pisc)
{}

float Vivenda::mensalidade() const
{
    if(piscina) return  Imovel::mensalidade() + 0.1*areaExterior + 10;
    else return  Imovel::mensalidade() + 0.1*areaExterior;
}

int Vivenda::getAreaHabitacao() const
{
    return Imovel::getAreaHabitacao() + areaExterior;
}

//////////////////////
// URBANIZAÇÃO
/////////////////////
int Urbanizacao::static_id = 1;

Urbanizacao::Urbanizacao(string nm, int id): nome(nm), ID(id)
{}

Urbanizacao::Urbanizacao(string nm)
{
    this->nome = nm;
    this->ID = static_id;
    this->imoveis_id = 1;
    static_id++;
}
void Urbanizacao::adicionaImovel(Imovel *im1)
{ 
    im1->setID(imoveis_id);
    imoveis_id++;
    imoveis.push_back(im1); 
}


vector<Imovel *> Urbanizacao::getImoveis() const
{ return imoveis; }

string Urbanizacao::getNome() const
{ return nome; }

int Urbanizacao::getID() const
{ return ID; }

vector<Imovel *> Urbanizacao::areaSuperiorA(int area1) const
{
    vector<Imovel *> v;
    for(size_t i = 0; i < imoveis.size(); i++)
    {
        if(imoveis.at(i)->getAreaHabitacao() > area1)
            v.push_back(imoveis.at(i));
    }

    return v;
}

unsigned int Urbanizacao::getNumProprietarios() const 
{
    vector<string> proprietarios;

    for(size_t i = 0; i < imoveis.size(); i++)
    {
        string nome = imoveis.at(i)->getProprietario();
        if (find(proprietarios.begin(), proprietarios.end(), nome) == proprietarios.end())
            proprietarios.push_back(nome);
    }

    return proprietarios.size();
}

bool Urbanizacao::operator> (const Urbanizacao &u) const
{
    float a = this->getNumProprietarios(),
        b = u.getNumProprietarios();

    if(a != 0) a = 1/a * this->imoveis.size();
    
    if(b != 0) b = 1/b * u.imoveis.size();

    return a < b;
}

void Urbanizacao::resetID()
{
    static_id = 1;
}
//////////////////////
// Condominio
/////////////////////

void ECondominio::adicionaUrbanizacao(Urbanizacao urb1)
{ urbanizacoes.push_back(urb1); }

vector<Urbanizacao> ECondominio::getUrbanizacoes() const
{ return urbanizacoes; }

float ECondominio::mensalidadeDe(string nomeProp) const
{
    float custo = 0;
    for(auto i = urbanizacoes.cbegin(); i != urbanizacoes.cend(); i++)
    {
        vector<Imovel *> im = i->getImoveis();
        for(auto j = im.cbegin(); j != im.cend(); j++)
        {
            if((*j)->getProprietario() == nomeProp)
                custo += (*j)->mensalidade();
                
        }
    }

    return custo;
}

vector<Urbanizacao> ECondominio::removeUrbanizacaoDe(string nomeProp)
{
    vector<Urbanizacao> v;
    
    for(auto i = urbanizacoes.cbegin(); i != urbanizacoes.cend();i++)
    {
        vector<Imovel *> im = i->getImoveis();
        for(auto j = im.cbegin(); j != im.cend(); j++)
        {
            if((*j)->getProprietario() == nomeProp)
            {
                v.push_back(*i);
                i = urbanizacoes.erase(i); // remove urbanizacao da empresa
                i--;
                break;
            }
        }
    }

    return v;
}

vector<Imovel *> ECondominio::operator() (string nome) const
{
    for(size_t i = 0; i < urbanizacoes.size(); i++)
    {
        if(urbanizacoes.at(i).getNome() == nome)
            return urbanizacoes.at(i).getImoveis();
    }
    vector<Imovel *> v;
    return v;
}