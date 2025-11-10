// Desenvolvido por Alessandro João Brassanini
// Data: 04 de Dezembro de 2023

// Editado por:     Allan Carneiro da Cunha Silveira
//                  Isadora Voss Brugnera
//                  Jenifer Beatriz Nunes Ribeiro
// Data: 06 de Junho de 2024

/*
Uso de matriz bidimensional (5x5) para armazenar o cenário.
Laços de repetição para imprimir o labirinto a cada rodada.
Condicionais para validar os movimentos e impedir atravessar paredes.
Leitura de teclado com scanf para capturar as direções.
Verificação de vitória quando o jogador chega na saída.

Beep(frequencia, duracao) - frequência em Hertz (Hz) e duração em milissegundos (ms).
Valores típicos de frequência:

400 Hz - som grave
750 Hz - som médio
1000 a 2000 Hz - som agudo (usado para vitória)

Movimento válido - som curto e médio.
Batida na parede - som grave mais longo.
Chegada na saída - som agudo de comemoração.


Regras:

P - posição atual do jogador.
0 - caminho livre.
1 - parede (não pode atravessar).
S - saída (objetivo do jogo).

*/

/*PARA FAZER:

01 - Aumentar o tamanho do labirinto de 5x5 para 10x10
02 - Usar emojis ou caracteres ASCII diferentes (@ para
jogador, X para parede, O para saída).
Usar a criatividade.
03 - Recursos de som
Usar Beep(frequencia, duracao) com mais efeitos.
Diferenciar sons de parede, movimento e vitória.
Criar sons personalizados para cada tipo de movimento.
Exemplo: Som mais rápido ao andar, som longo ao bater na
parede.
Trabalho da N2 – peso 3
04 - Adicionar contador de passos ou movimentos.
Exemplo: mostrar quantos movimentos o jogador fez até a
vitória.
05 - Adicionar sistema de pontuação.
Exemplo: Pontos para cada movimento correto, penalidades
ao bater na parede.
Usar a criatividade.
06 - Adicionar armadilhas ou “buracos”.
Trabalho da N2 – peso 3
07 - Realizar melhoria da estrutura do código.
Modularização usando funções:
Exemplo: void mostrarLabirinto(), int validarMovimento(),
void tocarSom().
Objetivo é incentivar programação estruturada e
reaproveitamento de código.
08 - Mostrar coordenadas (linha/coluna) para jogadores.
Exemplo: Mostrar a linha e coluna em que esta na hora de
navegar.
09 - Adicionar cores no joguinho.

*/

#include <stdio.h>   // Para printf e scanf
#include <stdlib.h>  // Para system (limpar tela)
#include <ctype.h>   // Para toupper (converter comandos)
#include <windows.h> //Para beep

#define N 10 // Tamanho da matriz do labirinto

int movimentos = 0; // Declarando variveis para contagem dos movimentos
int pontos = 0;     // e para a contagem de pontos

//---------------------------------FUNÇÕES------------------------------------------
// Mostrar o labirinto
void mostrarLabirinto(int matriz[N][N], int x, int y, int pontos)
{
    printf("\x1b[1;37mJogo do Labirinto 10x10 com Som!\x1b[0m\n");
    printf("Use W (cima), S (baixo), A (esquerda), D(direita)\n");
    printf("Objetivo: chegar na saida (\x1b[32mS\x1b[0m)\n\n");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == x && j == y)           printf("\x1b[33m:)\x1b[0m"); // Jogador
            else if (matriz[i][j] == 1)     printf("\x1b[31mX\x1b[0m "); // Parede
            else if (matriz[i][j] == -1)    printf("\x1b[32m[]\x1b[0m"); // Saída
            else if (matriz[i][j] == 3)     printf("\x1b[38;5;208m@\x1b[0m "); // buraco
            else                            printf("\x1b[34m.\x1b[0m "); // Caminho
        }
        printf("\n");
    }
    printf("\nPosicao: (\x1b[36m%d\x1b[0m, \x1b[36m%d\x1b[0m)\n", x, y);
    printf("Pontuacao: \x1b[35m%d\x1b[0m\n", pontos);
}

// Validar movimento
int validarMovimento(int novoX, int novoY, int matriz[N][N])
{
    int dentroDosLimites = (novoX >= 0 && novoX < N && novoY >= 0 && novoY < N);

    if (dentroDosLimites && (matriz[novoX][novoY] == 0 || matriz[novoX][novoY] == -1))  return 0;
    else if (dentroDosLimites && matriz[novoX][novoY] == 2)                             return 2; // Bomba
    else if (dentroDosLimites && matriz[novoX][novoY] == 3)                             return 3; // Buraco
    else                                                                                return 1; // Parede ou fora dos limites
}

// tocar som
void tocarSomVitoria()
{
    Beep(659, 140);  Sleep(30);  // E5
    Beep(784, 140);  Sleep(30);  // G5
    Beep(1047, 260); Sleep(60);  // C6 (sustentado)
    Beep(880, 180);  Sleep(40);  // A5
    Beep(784, 140);  Sleep(30);  // G5
    Beep(659, 140);  Sleep(30);  // E5
    Beep(523, 140);  Sleep(30);  // C5
    Beep(659, 260);  Sleep(60);  // E5 (resolucao)
    // Flourish final
    Beep(1047, 180); Sleep(40);  // C6
    Beep(1319, 180); Sleep(40);  // E6
    Beep(1568, 320);             // G6 (final)
    // Beep(1000, 300);
    // Beep(1500, 300);
    // Beep(2000, 500);
}
void tocarSomMovimento()
{
    Beep(500, 100);
}
void tocarSomErro()
{
    Beep(250, 100);
    Sleep(50);
    Beep(250, 100);
    Sleep(300);
}
void tocarSomBomba()
{
    Beep(200, 300);
    Sleep(100);
    Beep(150, 300);
    Sleep(100);
    Beep(100, 500);
    Sleep(500);
}
void tocarSomBuraco()
{
    Beep(300, 300);
    Beep(200, 400);
    Beep(100, 600);
}

//-------------------------------------MAIN-----------------------------------------

int main()
{
    // Matriz do labirinto: 0 = caminho, 1 = parede, -1 = saída
    int labirinto[N][N] =
        {
            {0, 1, 0, 0, 2, 0, 0, 0, 0, 0},
            {0, 1, 0, 1, 1, 0, 1, 0, 1, 0},
            {0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
            {1, 1, 0, 1, 0, 1, 1, 0, 1, 1},
            {0, 1, 0, 1, 0, 0, 2, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 0, 2, 0, 0, 0, 0},
            {0, 1, 0, 2, 0, 1, 0, 1, 1, 0},
            {0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
            {0, 0, 0, 1, 1, 1, 1, 1, 0, -1}};

    int x = 0, y = 0; // Posição inicial do jogador
    char comando;
    int jogando = 1;
    int pontos = 0; // Controle do loop do jogo
    while (jogando)
    {
        system("cls"); // Limpa a tela no Windows
        
        // Mostra o labirinto
        mostrarLabirinto(labirinto, x, y, pontos);
        
        // Verifica se o jogador chegou a saída
        if (labirinto[x][y] == -1)
        {
            pontos += 50;
            printf("\nParabens! Voce encontrou a saida! Ganhe mais 50 :D \n");
            printf("Total de pontos: %d", pontos);
            // Som de vitória: frequência alta
            tocarSomVitoria();
            break;
        }
        
        // Entrada de movimento

        printf("\nDigite seu movimento (W/A/S/D): ");
        scanf(" %c", &comando);
        comando = toupper(comando); // Normaliza para maiúscula
        // Verifica tecla válida
        if (comando != 'W' && comando != 'A' && comando != 'S' && comando != 'D')
        {
            printf("\x1b[31mComando invalido! Use W, A, S ou D.\x1b[0m\n");
            tocarSomErro();
            continue;            
        }        

        int novoX = x;
        int novoY = y;

        if (comando == 'W')         novoX--;
        else if (comando == 'S')    novoX++;
        else if (comando == 'A')    novoY--;
        else if (comando == 'D')    novoY++;
        else                        printf("Comando invalido!\n");

        int movimentoValido = validarMovimento(novoX, novoY, labirinto);

        if (movimentoValido == 0)
        {
            x = novoX;
            y = novoY;
            tocarSomMovimento();
            pontos += 10;
        }
        else if (movimentoValido == 1)
        {
            printf("\x1b[31mMovimento invalido! Parede ou fora dos limites!\x1b[0m\n");
            printf("\x1b[31mPerdeu 5 pontos :(\x1b[0m\n");
            tocarSomErro();
            pontos -= 5;
        }
        else if (movimentoValido == 2)
        {
            x = 0;
            y = 0;
            printf("\x1b[1;91mKABUMMMMMM!\x1b[0m\x1b[31m\nPerdeu 200 pontos! e voltou para a posição inicial.\x1b[0m\n");
            tocarSomBomba();
            labirinto[novoX][novoY] = 3; // Remove a bomba após cair nela
            pontos -= 200;
        }
        else if (movimentoValido == 3)
        {
            printf("\x1b[31mCaiu em um buraco! Fim de jogo!\x1b[0m\n");
            tocarSomBuraco();
            printf("Total de pontos: %d\n", pontos);
            break;
        }
        
    }

    return 0;
}
