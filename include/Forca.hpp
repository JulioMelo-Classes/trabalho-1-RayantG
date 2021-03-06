#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>


class Forca {    
    private:
        //TODO: armazenar os scores?\
 
        unsigned int dificuldade; //<! dificuldade do jogo
 
        std::string palavra_atual; //<! palavra sendo testada atualmente
 
        int tentativas_restantes = 6; //<! tentativas restantes

        int contadificil = 0;

        std::vector<char> progresso;
    public:
        /**
         * Cria a classe Forca
         * O construtor pode ou não validar os arquivos de entrada, no entanto, mesmo com 
         * os arquivos inválidos o objeto deve ser construído. Para o caso de arquivos de palavras
         * ou scores inválidos, use o método eh_valido.
         * @param palavras o arquivo que contém as palavras
         * @param scores o nome do arquivo que contém os scores
         * @see eh_valido
         */
        int pontuacao = 0;
        int jogardenovo = 0;
        std::string nome;
        std::vector<std::string> toda_palavra;
        std::vector<std::string> pontos;
        Forca( std::vector<std::string> palavras, std::vector<std::string> scores)
        {
            toda_palavra = palavras;
            pontos = scores;
        };
       
 
        /**
         * Valida os arquivos de entrada de acordo com as especificações.
         * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a 
         * razão correspondente de acordo com as especificações.
         * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
         */
        void eh_valido()
        {
        
                for (std::size_t i = 0; i < toda_palavra.size(); i++)
            {
                if(i%2 == 0)
                {
                if(stoi(toda_palavra[i])<=10)
                    {
                    std::cout<<"Arquivo não aceito :(" << std::endl;
                    exit(EXIT_SUCCESS);
                    }
                }
                else
                {
                for (std::size_t j = 0; j < toda_palavra[i].size(); j++)
                {
                  //||||for(auto f: toda_palavra)||||
                    
                  if(toda_palavra[i][j] == '?' || toda_palavra[i][j] == '/' || toda_palavra[i][j] == '>')
                    {
                    std::cout<<"Arquivo não aceito :(" << std::endl;
                    exit(EXIT_SUCCESS);
                    } 
                }
                }
                
            }
            std::cout <<" Arquivos OK!" << std::endl;    
        }
        /**
         * Carrega os arquivos de scores e palavras preenchendo **ao menos** a estrutura m_palavras
         */

 
        /**
         * Modifica a dificuldade do jogo.
         * De acordo com a dificuldade configurada, o método proxima_palavra retornará palavras
         * diferentes.
         * @param d a dificuldade desejada
         * @see proxima_palavra
         */
        int set_dificuldade()
        {
            int d;
            std::cout << "Escolha a sua dificuldade:" << std::endl;
            std::cout << "0 - Fácil" << std::endl;
            std::cout << "1 - Médio" << std::endl;
            std::cout << "2 - Difícil" << std::endl;
            
            while(dificuldade>2)
            {
              std::cin >> dificuldade;
            }
          return dificuldade;
        }

        unsigned int get_dificuldade()
        {
          return dificuldade;
        }
 
        /**
         * Retorna a próxima palavra de acordo com a dificuldade atual.
         * Este método deve atualizar o atributo m_palavra_atual e retornar a palavra um texto no formato
         * "_ _ _ _ ... _" dependendo do tamanho de m_palavra_atual. O método também deve sortear as 
         * letras que devem aparecer dependendo do nível de dificuldade.
         * @return a próxima palavra do conjunto de palavras disponível de acordo com a dificuldade atual.
         */
        bool proxima_palavra(int d)
        {
          srand(time(0));
          bool espera=0;
          int aleatorio;
          switch(d)
          {
            case 0:
                aleatorio = rand()%40;
                      if(aleatorio%2==0)
                      {
                        palavra_atual = toda_palavra.at(aleatorio+1);
                        espera = 1;
                      }
                      else
                      {
                        palavra_atual = toda_palavra.at(aleatorio);
                        espera = 1;
                      }; break;
            case 1:
               aleatorio = 30 + rand()%60;   
                        if(aleatorio%2==0 && contadificil<3)
                        {
                            palavra_atual = toda_palavra.at(aleatorio+1);
                            contadificil++;
                            espera = 1;
                        }
                        else if(aleatorio%2!=0 && contadificil<3)
                        {
                          palavra_atual = toda_palavra.at(aleatorio);
                          contadificil++;
                          espera = 1;
                        }
                        else
                        {
                            proxima_palavra(2);
                        }; break;
            case 2:
                    aleatorio = 80 + rand()%60;
                        if(aleatorio%2==0)
                        {
                          palavra_atual = toda_palavra.at(aleatorio+1);
                          espera=1;
                        }
                        else
                        {
                          palavra_atual = toda_palavra.at(aleatorio);
                          espera=1;
                        }; break;   
            }
            criar_progresso();
            return espera;
        }

 
        /**
         * Retorna a palavra atual que está sendo jogada.
         * @return o valor do atributo m_palavra_atual.
         */
        std::string get_palavra_atual()
        {
            return palavra_atual;
        }
 
        /**
         * Testa se uma letra pertence á palavra atual, retorna T se a letra pertence.
         * Este método testa se uma letra pertence à palavra atual e retorna True caso pertença. 
         * Caso contrário, o método deve atualizar o atributo m_tentativas_restantes, decrementando 
         * em 1, e retornar False.
         * @param palpite uma letra, que deve ser testada se pertence à palavra.
         * @return T se a palpite pertence à palavra, F caso contrário.
         */
        bool palpite(char letra)
        {
            int indice;
            bool erro=1;
            for(int i=0; i<palavra_atual.size(); i++)
            {
                if(letra == palavra_atual.at(i))
                {
                    erro = 0;
                    set_progresso(i);
                }
            }
            return erro;
        }

        void criar_progresso()
        {
          for(int i=0;i<palavra_atual.size();i++)
          {
            progresso.push_back('_');
          }
        }

        void set_progresso(int index)
        {
              progresso.at(index) = palavra_atual.at(index);
        }
 
        /**
         * Em caso de Game Over este método deve retornar T.
         * @return T caso o m_tentativas_restantes do jogo esteja igual a 0, F caso contrário.
         */
        std::vector<char> get_progresso()
        {
            return progresso;
        }
        
        bool checa_vitoria(Forca x)
        {
            int escolha;
            bool rep = 1;

            for(int i=0;i<palavra_atual.size();i++)
            {
              if(progresso.at(i) != palavra_atual.at(i))
              {
                rep=0;
              }
            }
            if(rep==1)
            {
              std::cout << palavra_atual << std::endl;
              std::cout << "Parabéns, você venceu!" << std::endl;
              std::cout << "O que deseja fazer agora?" << std::endl;
              std::cout << "1 - Voltar ao menu" << std::endl;
              std::cout << "2 - Encerrar" << std::endl;
              std::cin >> escolha;
              switch(escolha)
              {
                  case 1: return rep; break;
                  case 2: std::cout << "Obrigado por jogar! :)" << std::endl; exit(EXIT_SUCCESS); break;
              }
            }
          set_pontos();
          return rep;   
        }        
        
        bool game_over(Forca y)
        {
            int jogador;
            bool escolha=0;
            std::cout << "você perdeu, que pena... :(" << std::endl;
            std::cout << "O que deseja fazer agora?" << std::endl;
            std::cout << "1 - Voltar ao menu" << std::endl;
            std::cout << "2 - Encerrar" << std::endl;
            std::cin >> jogador; 
            switch(jogador)
            {
                case 1: tentativas_restantes = 6; escolha = 1; break;
                case 2: std::cout << "Obrigado por jogar! :)" << std::endl; exit(EXIT_SUCCESS); break;
            }
          set_pontos();
          return escolha;
        }
        
        /**
         * Atualiza o número de tentativas restantes.
         * Este método é útil no caso do jogador escolher continuar o jogo.
         * @param tentativas atualiza o valor da variável m_tentativas_restantes.
         */
        void set_tentativas_restantes(int tentativas)
        {
            tentativas_restantes--;
        }
 
        /**
         * Retorna a quantidade de tentativas restantes.
         * @return a quantidade de tentativas restantes.
         */
        int get_tentativas_restantes()
        {
            return tentativas_restantes;
        }

        void set_pontos()
        {
          std::ofstream file("Scores.txt", std::ios::app);

          switch (dificuldade)
          {
            case 0: file << "fácil; "; break;
            case 1: file << "médio; "; break;
            case 2: file << "difícil "; break;
          }
          file << nome << "; ";
          file << pontuacao;
            
          file.close();
        }
 
};
