#include "Maquina_De_Busca.h"

#include <cctype>
#include <set>
#include <string>
#include <dirent.h>  //Recuperar arquivos no diretório
#include <sys/types.h>  //Recuperar arquivos no diretório

Maquina_De_Busca::Maquina_De_Busca(string pasta_):pasta_(pasta_){
    
    //Armazena os documentos e a pasta em variáveis
    vector<string> documentos = localizarDocumentos();
    for (auto documento : documentos){
        if((documento == "." || documento == "..")==false){
            docs_.insert(documento);
        }
    }
}

string Maquina_De_Busca::normalizar(string palavra_) {
    string normalizada_;

    // Ignora todos os símbolos que não são letras
    // e transforma as letra em minúsculas
    for (char c : palavra_) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            normalizada_ += tolower(c);
        }
    }
    return normalizada_;
}

void Maquina_De_Busca::atualizarOcorrencia(string docs_,
                                           const vector<string> &palavras_) {

    // Aumenta em uma ocorrência cada palavra que foi encontrada
    for (const auto &palavra : palavras_) {
        ocorrencia_[palavra][docs_]++;
    }
}



vector<string>
Maquina_De_Busca::localizarDocumentos(){
    DIR *diretorio;
    struct dirent *arquivo;

    //Abre o diretório
    diretorio = opendir(pasta_.c_str());

    vector<string> documentosEncontrados;

    //Salva os nomes dos documentos encontrados em um vetor
    if(diretorio){
        while((arquivo = readdir(diretorio))!=NULL){
            documentosEncontrados.push_back(arquivo->d_name);
        }
        closedir(diretorio);
    }
    return documentosEncontrados;
}