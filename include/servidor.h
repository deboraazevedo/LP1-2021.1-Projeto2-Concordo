#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <string>
#include "canaltexto.h"
#include <vector>

class Servidor{
	public:
	int usuarioDonoId;
	string nome;
	string descricao;
	string codigoConvite;
	vector<CanalTexto> canaisTexto;
	vector<int> participantesIDs;
	/*
		TODO implementação dos atributos e métodos
	*/
};

#endif
