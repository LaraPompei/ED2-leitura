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
void leitura(vector<registro>& lista){
    fstream file, bgg;
    int linha = 0;
    if(TAM>17065)
	cout<<"tamanho especificado maior do que o arquivo games_detailed_info.csv"<<endl;
    file.open("games_detailed_info.csv", ios::in);
    bgg.open("bgg-13m-reviews.csv", ios::in);
    cout<<"abrindo bgg-13m-reviews.csv"<<endl;
    if(bgg.is_open()){
        int num = 0;//numero de linhas no arquivo
        string str,palavra;
        while(bgg)
        {
            getline(bgg,str);
            num++;
        }
	cout<<"Total de linhas no bgg-13m-reviews.csv: "<<num<<endl;
        //reinicializando o arquivo
        bgg.clear();
        bgg.seekg(0, ios::beg);

        getline(bgg,str);
        srand(time(NULL));//inicializando semente de randomizacao
        int random = 17065-TAM;
        random = rand() % random;
        int contN = 0;
        while(getline(bgg, str))
        {
            stringstream s(str);
            if(contN >= random && contN <=random+TAM)
            {
                registro reg;
                getline(s, palavra, ';');
                getline(s, palavra, ';');
                reg.setUser(palavra);
                getline(s, palavra, ';');
                if(palavra>="0.0" && palavra<="10.0")
                {
                    reg.setRating(stoi(palavra));
                    lista.push_back(reg);
                }
                else
                    contN--;
            }
            contN++;
            s.clear();
        }
    }
    else
	cout<<"Erro ao abrir arquivo bgg-13m-reviews.csv"<<endl;

    cout<<"abrindo games_detailed_info.csv"<<endl;
    if(file.is_open()){
        int num = 0;//numero de linhas no arquivo
        string str, palavra; //str eh usada para armazenar uma linha e palavra cada uma das colunas de str
        //conta a quantidade de linhas no arquivo(inutil, foi so pra rodar 1 vez)
	while(file){
            getline(file,str);
            num++;
	}
	cout<<"total de linhas do games_detailed_info: "<<num<<endl;

        //reinicializando o arquivo
        file.clear();
        file.seekg(0, ios::beg);

        getline(file,str);//pula primeira linha
        int cont = 0;
	vector<registro> ::iterator it;
	for (it = lista.begin(); it != lista.end(); ++it){
            while(getline(file, str) && cont<=it->getId())
            {
            	stringstream s(str);
            	if(cont == it->getId())
            	{
                    registro reg;
                    for(int i = 1; i<= 31; i++){
                    	getline(s, palavra, ',');
                    }
                    getline(s,palavra,',');
		    //reg.setDescricao(str);
	       }
               cont++;
               s.clear();
           }
	}
    }
    else
	 cout<<"erro ao abrir o arquivo info"<<endl;
    file.close();
/*
    cout<<"abrindo o bgg-13m-reviews.csv"<<endl; 
    if(bgg.is_open()){
        linha = 0;
	string str, palavra;
	vector<registro>::iterator aux = lista.begin();
	getline(bgg, str); //pula primeira linha do arquivo
	while(getline(bgg, str)){
            stringstream s(str);
	    getline(s,palavra, ',');
      	    cout<<"aux->getId() = "<<endl;
	    cout<<aux->getId()<<endl;
	    cout<<stoi(palavra)<<endl;
	    if(stoi(palavra) == aux->getId()){
		cout<<"aux->getId() = "<<aux->getId()<<endl;
		while(linha<TAM){
	    	    getline(s, palavra, ',');
                    aux->setUser(palavra);
                    getline(s, palavra, ',');
		    aux->setRating(stoi(palavra));
		    linha++;
		}
		break;
	    }
    	} 
        cout<<endl<<"linhas: "<<linha<<endl;
    }
    else
	cout<<"Erro ao abrir o bgg-13m-reviews.csv"<<endl;
	*/
    bgg.close();
}

int main(){
    vector<registro> lista;
    leitura(lista);
}
