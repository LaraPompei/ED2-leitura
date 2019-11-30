#include <iostream>
#include<iterator>
#include <vector>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <fstream>
#include "registro.h"

#define TAM 10

using namespace std;

/*
 **********************************************************************************************
 *                                                                                            *
 * Funcao responsavel pela leitura de um bloco de dados de tamanho N do arquivo e armazena-lo *
 * em uma lista de registros                                                                  *
 *                                                                                            *
 **********************************************************************************************
 */
void leitura(vector<registro>& lista, vector<string>& linha, vector<vector<string>>& linhas){
    fstream file, bgg;
    if(TAM>17065)
	cout<<"tamanho especificado maior do que o arquivo games_detailed_info.csv"<<endl;
    file.open("games_detailed_info.csv", ios::in);
    bgg.open("bgg-13m-reviews.csv", ios::in);
    cout<<"abrindo bgg-13m-reviews.csv"<<endl;
    if(bgg.is_open()){
        int num = 0;//numero de linhas no arquivo
        string str,palavra;
        //reinicializando o arquivo
        bgg.clear();
        bgg.seekg(0, ios::beg);

        getline(bgg,str); // pula cabeçalho
        srand(time(NULL));//inicializando semente de randomizacao
        int random = 17065-TAM; //pegando TAM linhas dentre as 17065 primeiras linhas do arquivo
        random = rand() % random; //sorteia numero aleatorio
        int contN = 0;
	//seta o ponteiro do arquivo na linha sorteada
	cout<<random<<endl;
        for(int j = 0; j< random; j++){
	    getline(bgg,str);
	}
	while(getline(bgg, str)){
	    stringstream s(str);//joga a string str para uma stringstream
            registro reg; //cria um registro
            getline(s, palavra, ','); //pega a primeira coluna => id
	    reg.setId(stoi(palavra)); //define id como o numero lido do arquivo
            getline(s, palavra, ','); //pega a segunda coluna => user
            reg.setUser(palavra); //define o user como oo lido do arquivo
            getline(s, palavra, ','); //pega a proxima coluna => rating
            if(palavra>="0.0" && palavra<="10.0"){ //se o valor lido for um rating armazena-lo no registro
           	reg.setRating(stoi(palavra));
           	lista.push_back(reg); // jogar o registro para dentro do vetor passado por parametro da funcao
            }
            else //se nao, desconsidera a linha
               contN--;
            contN++;
            s.clear();
	    if(contN>=TAM)
	    	break;
        }
	cout<<contN<<endl;
    }
    else
	cout<<"Erro ao abrir arquivo bgg-13m-reviews.csv"<<endl;

    cout<<"abrindo games_detailed_info.csv"<<endl;
    if(file.is_open()){
	string str;
    	vector<registro>::iterator it;
	int cont = 0;
	file.seekg(0,ios::beg);//joga o ponteiro pro inicio do arquivo
	getline(file, str); // pula o cabecalho
	int i = 0;
	//cout<<lista.size()<<endl;
	for(it = lista.begin(); it != lista.end(); ++it){ //pega apenas as linhas pegas ao ler o bgg
	   while(i<it->getId()){ //caminha ate a primeira linha que o lida pelo bgg
	   	getline(file,str);
		i++;
	   }
	   cout<<i<<endl; 
	   stringstream s(str); //joga o str pro stringstream
	   getline(s, str, ','); //pega a primeira linha => id
	   cout<<str<<endl;
	   i = stoi(str);
	   getline(s, str, '"');
	   cout<<str<<endl;
	   getline(s, str, '"');//pega o comentario
	   cout<<str<<endl;
	   it->setDescricao(str);//joga pro registro
	   cont++;
	       	       
       }
    }
    else
	 cout<<"erro ao abrir o arquivo info"<<endl;
    file.close();
    bgg.close();
}

int main(){
    vector<registro> lista;
    vector<string> linha;
    vector<vector<string>> linhas;
    leitura(lista,linha, linhas);
    vector<registro>::iterator it;
    for(it = lista.begin(); it != lista.end(); ++it){
	    cout<<"ID: "<<it->getId()<<endl;
	    cout<<"User: "<<it->getUser()<<endl;
	    cout<<"Rating: "<<it->getRating()<<endl;
	    cout<<"Descricao: "<<it->getDescricao()<<endl;
    }
}
