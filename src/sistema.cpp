#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <utility>

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
  cout << "Usuário ID " << novoUsuarioId <<  " criado" << endl;
  // list_users();
  novoUsuarioId += 1;
  return "Usuário criado";
  return "create_user NÃO IMPLEMENTADO";
}

string Sistema::login(const string email, const string senha) {
  vector<Usuario>::iterator it;
  
  for (it = usuarios.begin(); it < usuarios.end(); it++){
    if (it->email == email && it->senha == senha){
      pair<string, string> servidor_canal("", "");

      // usuariosLogados.insert(pair<int, pair<string, string>>(it->id, servidor_canal));
      usuariosLogados[it->id] = servidor_canal;
      return "Usuário logado com sucesso.";
    }

  }
  return "Email ou senha inválidos";
}

string Sistema::disconnect(int id) {
  
  std::map< int, std::pair<std::string, std::string> >::iterator it;
  it = usuariosLogados.find(id);
  if (it != usuariosLogados.end()){
    usuariosLogados.erase(id);
    vector<Usuario>::iterator itera;
    for (itera = usuarios.begin(); itera != usuarios.end(); itera++){
      if (itera->id == id){
        cout << itera->email << endl;
        cout << "Desconectando usuario " << itera->email << endl;
      }
    }
    
  }
  else 
    return "Não está conectado.";
}

string Sistema::create_server(int id, const string nome) {
  std::map< int, std::pair<std::string, std::string> >::iterator it;
  it = usuariosLogados.find(id);
  std::vector<Servidor>::iterator itera; 
  if (it != usuariosLogados.end()){
    auto itera = servidores.begin();
    for (itera = servidores.begin(); itera != servidores.end(); itera++){
      if (itera->nome == nome){
        return "Servidor com esse nome já existe";
      }
      }
   Servidor novoServidor;
   novoServidor.usuarioDonoId = id;
   novoServidor.nome = nome;
   servidores.push_back(novoServidor);
   return "Servidor criado";
  }
  return "Usuario não logado";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  //verificar se usuario é dono do servidor
  //se for, muda a descrição; senao diz que nao é 
  std::map< int, std::pair<std::string, std::string> >::iterator it;
  it = usuariosLogados.find(id);
  std::vector<Servidor>::iterator itera;
  if (it != usuariosLogados.end()){
    auto itera = servidores.begin();
    for (itera = servidores.begin(); itera != servidores.end(); itera++){
      if (itera->nome == nome){
        if (itera->usuarioDonoId == id){
          itera->descricao = descricao;
          return "Descrição do servidor " +nome+ " modificada!";
        }
        else
          return "Você não pode alterar o código de convite de um servidor que não foi criado por você";
      }
    }
  }

  return "Servidor " +nome+ " não existe";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  std::map< int, std::pair<std::string, std::string> >::iterator it;
  int tamanho = codigo.length();
  it = usuariosLogados.find(id);
  std::vector<Servidor>::iterator itera;
  if (it != usuariosLogados.end()){
    auto itera = servidores.begin();
    for (itera = servidores.begin(); itera != servidores.end(); itera++){
      if (itera->nome == nome && itera->usuarioDonoId == id){
        if (tamanho == 0){
          return "Código de convite do servidor " +nome+ " removido!";
        }
        else
          itera->codigoConvite = codigo;
          return "Código de convite do servidor " +nome+ " modificado!";  
      }
      else
      return "Você não pode alterar o código de convite de um servidor que não foi criado por você";
    }
  }

  return "Servidor " +nome+ " não existe";
}

string Sistema::list_servers(int id) {
  if (usuariosLogados.find(id) != usuariosLogados.end()){
    for (auto it = servidores.begin(); it != servidores.end(); it++){
      cout << it->nome << endl;  
    }
  }
  else
    return "Usuario não logado.";

  return "";
}

string Sistema::remove_server(int id, const string nome) {
  std::map< int, std::pair<std::string, std::string> >::iterator it;
  it = usuariosLogados.find(id);
  if (it != usuariosLogados.end()){
    for (auto itera = servidores.begin(); itera != servidores.end(); itera++){
      if (itera->nome == nome){
        if (itera->usuarioDonoId == id){
          servidores.erase(itera);
          return "Servidor " +nome+ " removido!";
        }
        else
          return "O servidor  " +nome+ " não é seu."; 
      }
    }
    return "Servidor " +nome+ " não existe.";
  }
  return "Usuário não está logado";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  std::map< int, std::pair<std::string, std::string> >::iterator it;
  it = usuariosLogados.find(id);
  if (it != usuariosLogados.end()){
    for (auto itera = servidores.begin(); itera != servidores.end(); itera++){
      if (itera->nome == nome){
        if (itera->codigoConvite != "" && itera->codigoConvite != codigo){
          return "Servidor requer codigo de convite valido";
        }
        if (itera->codigoConvite != "" && itera->codigoConvite == codigo){
          auto encontrado = std::find(itera->participantesIDs.begin(), itera->participantesIDs.end(), id);
          if(encontrado == itera->participantesIDs.end()){
            itera->participantesIDs.push_back(id);
            it->second.first = nome;
            return "Usuario entrou com sucesso no servidor " +nome+ " e foi adicionado em usuariosLogados";
          }
          else
            return "Usuario já entrou no servidor.";
          
        // salvar a informação que o usuário logado está visualizando 
        // o servidor escolhido na tabela usuariosLogados.
          

        }
       auto encontrado = std::find(itera->participantesIDs.begin(), itera->participantesIDs.end(), id);
          if(encontrado == itera->participantesIDs.end()){
            itera->participantesIDs.push_back(id);
            it->second.first = nome;
            return "Usuario entrou com sucesso no servidor " +nome+ " e foi adicionado em usuariosLogados";
      }

    }
    return "Servidor " +nome+ " não existe.";
  }
  return "Usuário não está logado";
}
}

string Sistema::leave_server(int id, const string nome) {
  std::vector<Servidor>::iterator itServidor;
  string nome_servidor = nome;
  for (itServidor = servidores.begin(); itServidor != servidores.end(); itServidor++){
    if (itServidor->nome == nome_servidor){
      for (auto itParticipante = itServidor->participantesIDs.begin(); 
      itParticipante != itServidor->participantesIDs.end(); itParticipante++){
        if(*itParticipante == id){
          itServidor->participantesIDs.erase(itParticipante);
          return "Saindo do servidor " +nome_servidor+ " .";
        }
      }
    }
    
  }
  return "Você não está em nenhum servidor";
}

string Sistema::list_participants(int id) {
  stringstream listaUsuarios;
  std::map< int, std::pair<std::string, std::string> >::iterator it;
  it = usuariosLogados.find(id);
  if (it == usuariosLogados.end()){
    return "Usuário não está logado";
  }
  string nome_servidor = it->second.first;
  std::vector<Servidor>::iterator itServidor;
  for (itServidor = servidores.begin(); itServidor != servidores.end(); itServidor++){
    if (itServidor->nome == nome_servidor){
      for (auto itParticipante = itServidor->participantesIDs.begin(); 
      itParticipante != itServidor->participantesIDs.end(); itParticipante++){
        int idParticipante = *itParticipante;
        for (auto itUsuario = usuarios.begin(); itUsuario != usuarios.end(); itUsuario++){
          if (itUsuario->id == idParticipante){
            listaUsuarios << itUsuario->nome << endl; 
          }
        }

      }
      
    }

  }

    //usuario do id esta em um servidor
    //buscar servidor por nome
  return listaUsuarios.str();
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

void Sistema::list_users(){
  vector<Usuario>::iterator it;
  
  for (it = usuarios.begin(); it != usuarios.end(); it++){
    cout << it->id << " - " << it->email << endl;  
  }
}


/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
