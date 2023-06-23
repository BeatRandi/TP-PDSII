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



   private:
      //Recupera todos os documentos em dada pasta
      vector<string> localizarDocumentos();


   private:
      // Map que conecta a chave palavra ao número de vezes que aparece
      map<string, map<string,int>> ocorrencia_;

      //documentos da pasta
      set<string> docs_;

      //Nome da pasta
      string pasta_;


};

#endif // MAQUINA_DE_BUSCA_H_