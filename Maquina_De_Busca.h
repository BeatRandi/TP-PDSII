#ifndef MAQUINA_DE_BUSCA_H_
#define MAQUINA_DE_BUSCA_H_

#include <map>
#include <set>
#include <string>
#include <vector>

using std::map;
using std::set;
using std::string;
using std::vector;

//Algoritmo para buscar palavras em documentos
class Maquina_De_Busca{

   public: 
      Maquina_De_Busca(string pasta_);

      // Realiza indexação
      void indexacao_();

       //retona os documentos em ordem de ocorrencia de cada plavra
       vector<string> recuperar(vector<string> buscar);



   private:
      //Recupera todos os documentos em dada pasta
      vector<string> localizarDocumentos();

      //Deixa todas as palavras apenas c letras minusculas
      string normalizar(string palavra_);

      //Conta a ocorrencia de cada palavra em cada documento
      void atualizarOcorrencia(string docs_, const vector<string> &palavras_);


   private:
      // Map que conecta a chave palavra ao número de vezes que aparece
      map<string, map<string,int>> ocorrencia_;

      //documentos da pasta
      set<string> docs_;

      //Nome da pasta
      string pasta_;


};

#endif // MAQUINA_DE_BUSCA_H_