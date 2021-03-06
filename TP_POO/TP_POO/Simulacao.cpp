#include "Simulacao.h"

Simulacao::Simulacao()
{
	m = new Mundo();
}

Simulacao::~Simulacao()
{
}

void Simulacao::setUp(){	
	string linha, cmd;

	do {	
		linha = f.setUp();
		stringstream is(linha);
		is >> cmd;
		
		if (cmd.compare("defmundo") == 0) {
			int aux1;
			is >> aux1;
			this->mundo = aux1;
		}
		else if (cmd.compare("defen") == 0) {
			int aux1;
			is >> aux1;
			this->en = aux1;
		}
		else if (cmd.compare("defpc") == 0) {
			int aux1;
			is >> aux1;
			this->pc = aux1;
		}
		else if (cmd.compare("defvt") == 0) {
			int aux1;
			is >> aux1;
			this->vt = aux1;
		}
		else if (cmd.compare("defmi") == 0) {
			int aux1;
			is >> aux1;
			this->mi = aux1;
		}
		else if (cmd.compare("defme") == 0) {
			int aux1;
			is >> aux1;
			this->me = aux1;
		}
		else if (cmd.compare("defnm") == 0) {
			int aux1;
			is >> aux1;
			this->nm = aux1;
		}
		else if (cmd.compare("executa") == 0) {
			string aux1;
			is >> aux1;
			ifstream infile;
			infile.open(aux1);
			infile >> linha;
			stringstream iss(linha);
			iss >> mundo >> en >> pc >> vt >> mi >> me >> nm;
		}
	} while (linha.compare("inicio") != 0);
}

void Simulacao::simulacao() {
	string linha, cmd;
	int x, y;
	m->setTam(mundo);

	srand((unsigned int)time(NULL));
	for (int i = 0; i < mundo*mundo*mi/100; i++) {
		do {
			x = rand() % mundo + 1;
			y = rand() % mundo + 1;
		} while (m->posicaoLivre(x, y) != true);
		m->novaMigalha(me, x, y);
	}

	do {
		linha = f.printInterface(m, mundo, focol, fococ);
		stringstream is(linha);
		is >> cmd;

		if (cmd.compare("ninho") == 0) {			
			int linha, coluna;
			is >> linha >> coluna;
			m->novoNinho(en, linha, coluna);
		}
		else if (cmd.compare("criaf") == 0) {
			int num, ninho, linha, coluna;
			string tipo;
			is >> num >> tipo >> ninho;

			for (int i = 0; i < num; i++) {
				do {
					linha = rand() % mundo + 1;
					coluna = rand() % mundo + 1;
				} while (m->posicaoLivre(linha, coluna) != true);
				m->novaFormiga(tipo, ninho, linha, coluna);
			}
		}
		else if (cmd.compare("cria1") == 0) {
			int ninho, linha, coluna;
			string tipo;
			is >> tipo >> ninho >> linha >> coluna;
			m->novaFormiga(tipo, ninho, linha, coluna);
		}
		else if (cmd.compare("migalha") == 0) {
			int linha, coluna;
			is >> linha >> coluna;
			m->novaMigalha(me, linha, coluna);
		}
		else if (cmd.compare("foca") == 0) {
			//ainda nao implementado
		}
		else if (cmd.compare("energninho") == 0) {
			int ninho, energia;
			is >> ninho >> energia;
			m->addEnergiaNinho(ninho, energia);
		}
		else if (cmd.compare("energformiga") == 0) {
			int linha, coluna, energia;
			is >> linha >> coluna >> energia;
			m->addEnergiaFormiga(linha, coluna, energia);
		}
		else if (cmd.compare("mata") == 0) {
			int linha, coluna;
			is >> linha >> coluna;
			for (int i = 0; i < m->getSizeNinhos(); i++) {
				for (int j = 0; j < m->getSizeOfNinhoX(i); j++) {
					if (m->getNinho(i)->getFormiga(j)->getLinha() == linha && m->getNinho(i)->getFormiga(j)->getColuna() == coluna)
						m->getNinho(i)->apagaFormiga(j);
				}
			}
		}
		else if (cmd.compare("inseticida") == 0) {
			int ninho;
			is >> ninho;
			m->apagaNinho(ninho-1);
		}
		else if (cmd.compare("listamundo") == 0) {
			for (int i = 0; i < m->getSizeNinhos(); i++) {
				cout << "Ninho: " << i + 1 << " / Energia: " << m->getNinho(i)->getEnergia() << " / Linha: " << m->getNinho(i)->getLinha() << " / Coluna: " << m->getNinho(i)->getColuna() << " / Formigas: " << m->getSizeOfNinhoX(i) << endl;
			}
			for (int i = 0; i < m->getSizeMigalhas(); i++) {
				cout << "Migalha: " << i + 1 << " / Energia: " << m->getMigalha(i)->getEnergia() << " / Linha: " << m->getMigalha(i)->getLinha() << " / Coluna: " << m->getMigalha(i)->getColuna() << endl;
			}
		}
		else if (cmd.compare("listaninho") == 0) {
			int ninho;
			is >> ninho;
			Ninho * n = m->getNinho(ninho - 1);
			for (int i = 0; i < m->getSizeOfNinhoX(ninho - 1); i++) {
				cout << "Formiga: " << n->getFormiga(i)->getIdentificador() << " / Energia: " << n->getFormiga(i)->getEnergia() << " / Linha:" << n->getFormiga(i)->getLinha() << " / Coluna: " << n->getFormiga(i)->getColuna() << endl;
			}
		}
		else if (cmd.compare("listaposicao") == 0) {
			int linha, coluna;
			is >> linha >> coluna;

			for (int i = 0; i < m->getSizeNinhos(); i++) {
				if(m->getNinho(i)->getLinha() == linha && m->getNinho(i)->getColuna() == coluna)
					cout << "Ninho: " << i + 1 << " / Energia: " << m->getNinho(i)->getEnergia() << " / Formigas: " << m->getSizeOfNinhoX(i) << endl;
				for (int j = 0; j < m->getSizeOfNinhoX(i); j++) {
					if(m->getNinho(i)->getFormiga(j)->getLinha() == linha && m->getNinho(i)->getFormiga(j)->getColuna() == coluna)
						cout << "Formiga: " << m->getNinho(i)->getFormiga(i)->getIdentificador() << " / Energia: " << m->getNinho(i)->getFormiga(i)->getEnergia() << endl;
				}
			}
			for (int i = 0; i < m->getSizeMigalhas(); i++) {
				if (m->getMigalha(i)->getLinha() == linha && m->getMigalha(i)->getColuna() == coluna)
					cout << "Migalha: " << i + 1 << " / Energia: " << m->getMigalha(i)->getEnergia() << endl;
			}
		}
		else if (cmd.compare("guarda") == 0) {

		}
		else if (cmd.compare("muda") == 0) {

		}
		else if (cmd.compare("apaga") == 0) {

		}
		else if (cmd.compare("tempo") == 0){
			//itera��o
			m->agirFormigas();
			m->agirNinhos(en, pc);
			m->agirMigalhas();
			//matar formigas, ninhos e migalhas se nao tiverem energia
			m->mataNinhos();
			m->mataFormigas();
			m->mataMigalhas();
		}
	} while (linha.compare("sair") != 0);
}