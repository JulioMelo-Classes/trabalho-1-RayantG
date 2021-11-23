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
            //p2.game_over(p2);
        break; 
    }
    p2.get_progresso();
    cout << " Digite uma letra" << endl;
    cin >> letra;
    tentativa = p2.palpite(letra, p2);
    if(tentativa)
    {
        p2.set_tentativas_restantes(tenta);
    }
    //p2.checa_vitoria(p2);
    game(p2);
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
    p.eh_valido();
    p.criar_progresso();
    inicio(p);
    vector<char> ajuda = p.get_progresso();
    for(int i=0; i<ajuda.size();i++)
            {
                cout << ajuda.at(i);
            }
    /*
    
    dif = p.get_dificuldade();
    if(dif<=2)
    {
      game(p);
    }
    
    jogarnovamente = p.get_tentativas_restantes();
    if(jogarnovamente>0)
    {
      inicio(p);
    }
    else
    {
      exit(EXIT_SUCCESS);
    }
    */
}

