#include "Maquina_De_Busca.h"

#include <algorithm> //sort

#include <cctype>
#include <fstream>     // Ler arquivos
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

void Maquina_De_Busca::atualizarOcorrencia(string docs_, const vector<string> &palavras_) {

    // Aumenta em uma ocorrência cada palavra que foi encontrada
    for (const auto &palavra : palavras_) {
        ocorrencia_[palavra][docs_]++;
    }
}

void Maquina_De_Busca::indexacao_() {
    // Faz a leitura de cada documento
    for (const string &doc : docs_) {
        std::ifstream arquivo(pasta_ + doc);
        std::string linha;
        vector<string> palavras;
        while (std::getline(arquivo, linha)) {
            string palavra;
            size_t inicio = 0;
            size_t fim = 0;
            while (fim != std::string::npos) {
                fim = linha.find(' ', inicio);
                palavra = linha.substr(inicio, fim - inicio);
                string palavraNormalizada = normalizar(palavra);
                if (!palavraNormalizada.empty()) {
                    palavras.push_back(palavraNormalizada);
                }
                inicio = fim + 1;
            }
        }
        atualizarOcorrencia(doc, palavras);
    }
}

vector<string> Maquina_De_Busca::recuperar(vector<string> buscar){
    vector<string> documentosEncontrados;
    set<string> palavrasNormalizadas;

    //Normaliza a palavra de busca
    //Palavras repetidas não sao readicioandas 
    for(auto &palavra : buscar){
        palavrasNormalizadas.insert(normalizar(palavra));
    }

    //verifica se alguma busca foi feita
    if(buscar.empty()){
        return documentosEncontrados;
    }

    //Verifica se a palavra esta presente em cada documento
    for (const auto &palavra: palavrasNormalizadas){
        if(ocorrencia_.count(palavra) == 0){
            //Plavra não encontrada, retornar lista vazia
            return documentosEncontrados;
        }
    }

    //Encontrar documentos q contem todas as palavras
    for(const auto &docContagens : ocorrencia_.at(*palavrasNormalizadas.begin())){
        const string &documento = docContagens.first;
        bool todasPalavrasPresentes = true;

        for(const auto &palavra : palavrasNormalizadas){
            if(ocorrencia_.at(palavra).count(documento) == 0 ){
                todasPalavrasPresentes = false;
                break;
            }
        }

        if(todasPalavrasPresentes){
            documentosEncontrados.push_back(documento);
        }

    }

    //Ordenar documentos por numero de hits e lexicograficamente
    sort(documentosEncontrados.begin(), documentosEncontrados.end()
       [this, palavrasNormalizadas](const string& doc1, const string& doc2) {
            int numHitsDoc1 = 0;
            int numHitsDoc2 = 0;

            for (const auto& palavra : palavrasNormalizadas) {
                if (ocorrencia_.at(palavra).count(doc1) > 0) {
                    numHitsDoc1 += ocorrencia_.at(palavra).at(doc1);
                }
                if (ocorrencia_.at(palavra).count(doc2) > 0) {
                    numHitsDoc2 += ocorrencia_.at(palavra).at(doc2);
                }   
            }

            if(numHitsDoc1 != numHistDoc2){
                return numHitsDoc1 > numHitsDoc2;
            }

            return doc1 < doc2; //Ordem alfabetica em caso de empate
    });
    return documentosEncontrados;
}

vector<string>Maquina_De_Busca::localizarDocumentos(){
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