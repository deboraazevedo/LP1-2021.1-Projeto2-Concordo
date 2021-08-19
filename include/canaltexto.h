#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <vector>
#include <string>

using namespace std;

class Mensagem{
	public:
    string dataHora;
    int enviadaPor;
    string conteudo;
};

class CanalTexto{
	public:
	string nome;
	vector<Mensagem> mensagens;

	/*
		TODO implementação dos atributos e métodos
	*/
};

#endif
