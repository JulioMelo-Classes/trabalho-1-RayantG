#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "/mnt/c/Users/Rayant/Downloads/Faculdade/Terceiro semestre/LP1/Trabalho 1/trabalho-1-RayantG/include/Forca.hpp"
using namespace std;


void inicio(Forca p1)
{
    int input;
    cout << "Escolha o que quer fazer" << endl;
    cout << "1 - Jogar" << endl;
    cout << "2 - Ver os scores" << endl;
    
    while(input !=1 && input !=2)
    {
      cin >> input;
    }
    switch(input)
    {
        case 1: p1.set_dificuldade(); break;
        case 2: for(int i=0; i< p1.pontos.size(); i++)
                {
                    cout << p1.pontos.at(i) << endl;
                }; break;
    }
}

void game(Forca p2)
{
    int tenta = p2.get_tentativas_restantes();
    char letra;
    bool tentativa;
    int erros = tenta;
    vector<char> andamento;
    switch(erros)
    {
        case 6:
            cout << "|  O  |" << endl;
            cout << "| /|) |" << endl;
            cout << "| / | |" << endl;
        break;
        case 5:
            cout << "|  O  |" << endl;
            cout << "| /|) |" << endl;
            cout << "| /   |" << endl;
        break; 
        case 4:
            cout << "|  O  |" << endl;
            cout << "| /|) |" << endl;
            cout << "|     |" << endl;
        break; 
        case 3:
            cout << "|  O  |" << endl;
            cout << "| /|  |" << endl;
            cout << "|     |" << endl;
        break;
        case 2:
            cout << "|  O  |" << endl;
            cout << "|  |  |" << endl;
            cout << "|     |" << endl;
        break; 
        case 1:
            cout << "|  O  |" << endl;
            cout << "|     |" << endl;
            cout << "|     |" << endl;
        break;
        case 0:
            cout << "Game Over! " << endl;
            string palavrinha = p2.get_palavra_atual();
            cout << "A palavra era :" << palavrinha << endl;
            p2.game_over(p2);
        break;
    }
    
    if(erros>0)
    {
      andamento = p2.get_progresso();
      for(int i=0;i<andamento.size();i++)
      {
      cout << andamento.at(i);
      cout << " ";
      }
      cout << endl;
      cout << " Digite uma letra" << endl;
      cin >> letra;
      tentativa = p2.palpite(letra);
      if(tentativa)
      {
        p2.set_tentativas_restantes(tenta);
      }
    //p2.checa_vitoria(p2);
    game(p2);
  }
    
}


int main(int argc, char* argv[])
{
    int indice;
    int jogarnovamente;
    int dif;
    vector<string> words;
    vector<string> points;
    ifstream arquivo_palavras("Palavras.txt");
    ifstream arquivo_scores(argv[1]);
    string pegascores;
    string pegapalavras;
    
    while(arquivo_palavras >> pegapalavras)
    {
        words.push_back(pegapalavras);
    }
    while(getline(arquivo_scores,pegascores))
    {
        points.push_back(pegascores);
    }
    Forca p(words, points);
    p.proxima_palavra(0);
    p.criar_progresso();
    p.eh_valido();
    inicio(p);
    dif = p.get_dificuldade();
    if(dif<=2)
    {
      game(p);
    }
}


