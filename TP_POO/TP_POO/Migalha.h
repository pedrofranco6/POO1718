#pragma once
#ifndef MIGALHA_H
#define MIGALHA_H

class Migalha
{
	int energia, linha, coluna;
public:
	Migalha(int energia, int linha, int coluna);
	~Migalha();
	int getLinha();
	int getColuna();
	int getEnergia();
	void setEnergia(int energia);
};

#endif