#include "Maquina_De_Busca.h"
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;

int main(){
    // Criacao da maquina e indexacao dos documentos
    Maquina_De_Busca maquina("./documentos/");
    maquina.indexacao_();

    // Recebe as palavras de busca do usuário
    vector<string> palavrasBusca;
    set<string> ja_apareceu;
    string palavra;
    while (cin >> palavra){
        if(ja_apareceu.count(palavra) == false){
            ja_apareceu.insert(palavra);
            palavrasBusca.push_back(palavra);
        }
    }



    return 0;
}
