#include <iostream>
#include<iterator>
#include <vector>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <fstream>
#include "registro.h"

#define TAM 1000

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

        getline(bgg,str);
        srand(time(NULL));//inicializando semente de randomizacao
        int random = 17065-TAM;
        random = rand() % random;
        int contN = 0;
	bgg.seekg(random, ios::beg);
	getline(file,str);
        while(getline(file, str)){
	    stringstream s(str);
            registro reg;
            getline(s, palavra, ',');
	    reg.setId(stoi(palavra));
            getline(s, palavra, ',');
            reg.setUser(palavra);
            getline(s, palavra, ',');
            if(palavra>="0.0" && palavra<="10.0"){
           	reg.setRating(stoi(palavra));
           	lista.push_back(reg);
            }
            else
               contN--;
            contN++;
            s.clear();
	    if(contN<TAM)
	    	break;
        }
    }
    else
	cout<<"Erro ao abrir arquivo bgg-13m-reviews.csv"<<endl;

    cout<<"abrindo games_detailed_info.csv"<<endl;
    if(file.is_open()){
	//linhas eh uma matrix que armazena todas as linhas e colunas

        int num = 17065;//numero de linhas no arquivo
        string str, palavra; //str eh usada para armazenar uma linha e palavra cada uma das colunas de str
        //conta a quantidade de linhas no arquivo(inutil, foi so pra rodar 1 vez)
	char separador = ',';
        //delimitador 2 e 3 antes ou depois da , indicam uma coluna
        char delimitador1 = ',';
        char delimitador2 = '"';

	int i = 0;
	cout<<"while eof"<<endl;
	while(!file.eof()){
	    getline(file, str); //le cada linha
	    stringstream s(str); //coloca a linha lida em uma stringstream
	    //lista eh um vetor que vai armazenar a linha completa
	    bool flag = 0;
	    cout<<"getline(s,str)"<<endl;
	    while(getline(s, str)){
	    	int inicio = 0;
		for(i = 0; i <str.length(); i++){
		    if(str[i] == separador){
		    	linha.push_back(str.substr(inicio, i-inicio));
			inicio = i+1;
		    }
		    else  if(str[i] == delimitador1 || str[i] == delimitador2){
		    	for(i = i++; i<=str.length(); i++){
			    if(i==str.length()){
			    	flag = 1;
				linha.push_back(str.substr(inicio, (i-1)-inicio));
				break;
			    }
			    if((str[i] == delimitador2 || str[i]== delimitador1)&& str[i+1] == separador){
			    	linha.push_back(str.substr(inicio, i-inicio+1));
				i++;
				inicio = i+1;
			    }
			}
			if(i>str.length())
			    break;
		    }
		}

		if(i - inicio != 0 && flag == false){
		    linha.push_back(str.substr(inicio, (i-1)-inicio));
		}

	    }
	    cout<<"final-getline(s,str)"<<endl;
    	    linhas.push_back(linha);
	 }
	cout<<"final-!file.eof()"<<endl;	
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
    
}
