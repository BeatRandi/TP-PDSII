#include "Maquina_De_Busca.h"

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