#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

static int novoUsuarioId = 1;
/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
  auto it = usuarios.begin();
  while (it < usuarios.end()){
    if (it->email == email){
      return "Usuário já existe";
    }
    it++;
  }
  Usuario novoUsuario;
  novoUsuario.id = novoUsuarioId;
  novoUsuario.nome = nome;
  novoUsuario.email = email;
  novoUsuario.senha = senha;

  usuarios.push_back(novoUsuario);
  novoUsuarioId += 1;
  cout << "Usuário ID " << novoUsuarioId << endl;
  return "Usuário criado";
  return "create_user NÃO IMPLEMENTADO";
}

string Sistema::login(const string email, const string senha) {
  vector<Usuario>::iterator it;
  
  for (it = usuarios.begin(); it < usuarios.end(); it++){
    if (it->email == email && it->senha == senha){
      pair<string, string> servidor_canal("", "");

      usuariosLogados.insert(pair<int, pair<string, string>>(it->id, servidor_canal));
      return "Usuário logado com sucesso.";
    }

  }
  return "Email ou senha inválidos";
  return "login NÃO IMPLEMENTADO";
}

string Sistema::disconnect(int id) {
  return "disconnect NÃO IMPLEMENTADO";
}

string Sistema::create_server(int id, const string nome) {
  return "create_server NÃO IMPLEMENTADO";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  return "set_server_desc NÃO IMPLEMENTADO";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  return "set_server_invite_code NÃO IMPLEMENTADO";
}

string Sistema::list_servers(int id) {
  return "list_servers NÃO IMPLEMENTADO";
}

string Sistema::remove_server(int id, const string nome) {
  return "remove_server NÃO IMPLEMENTADO";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  return "enter_server NÃO IMPLEMENTADO";
}

string Sistema::leave_server(int id, const string nome) {
  return "leave_server NÃO IMPLEMENTADO";
}

string Sistema::list_participants(int id) {
  return "list_participants NÃO IMPLEMENTADO";
}

string Sistema::list_channels(int id) {
  return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(int id, const string nome) {
  return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
  return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
  return "list_messages NÃO IMPLEMENTADO";
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
