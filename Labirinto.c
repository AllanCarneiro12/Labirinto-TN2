// Desenvolvido por Alessandro João Brassanini
// Data: 04 de Dezembro de 2023

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

#include <stdio.h>    // Para printf e scanf
#include <stdlib.h>   // Para system (limpar tela)
#include <ctype.h>    // Para toupper (converter comandos)
#include <windows.h>  // Para Beep()

#define N 5 // Tamanho da matriz do labirinto

int main()
{
    // Matriz do labirinto: 0 = caminho, 1 = parede, -1 = saída
    int labirinto[N][N] =
    {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, -1}
    };

    int x = 0, y = 0;      // Posição inicial do jogador
    char comando;          // Entrada do usuário
    int jogando = 1;       // Controle do loop do jogo

    while (jogando)
    {
        system("cls"); // Limpa a tela no Windows

        // Mostra o labirinto
        printf("Jogo do Labirinto 5x5 com Som\n");
        printf("Use W (cima), S (baixo), A (esquerda), D (direita)\n");
        printf("Objetivo: chegar na saida (S)\n\n");

        int i, j;
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (i == x && j == y)
                {
                    printf("P "); // Jogador
                }
                else if (labirinto[i][j] == 1)
                {
                    printf("# "); // Parede
                }
                else if (labirinto[i][j] == -1)
                {
                    printf("S "); // Saída
                }
                else
                {
                    printf(". "); // Caminho livre
                }
            }
            printf("\n");
        }

        // Verifica se o jogador chegou a saída
        if (labirinto[x][y] == -1)
        {
            printf("\nParabens! Voce encontrou a saida!\n");
            // Som de vitória: frequência alta
            Beep(1000, 300);
            Beep(1500, 300);
            Beep(2000, 500);
            break;
        }

        // Entrada de movimento
        printf("\nDigite seu movimento (W/A/S/D): ");
        scanf(" %c", &comando);
        comando = toupper(comando); // Normaliza para maiúscula

        int novoX = x;
        int novoY = y;

        if (comando == 'W')
        {
            novoX--;
        }
        else if (comando == 'S')
        {
            novoX++;
        }
        else if (comando == 'A')
        {
            novoY--;
        }
        else if (comando == 'D')
        {
            novoY++;
        }
        else
        {
            printf("Comando invalido!\n");
        }

        // Verifica se a nova posição é válida
        if (novoX >= 0 && novoX < N && novoY >= 0 && novoY < N && labirinto[novoX][novoY] != 1)
        {
            x = novoX;
            y = novoY;
            // Som de movimento: frequência média e curto
            Beep(750, 100);
        }
        else
        {
            printf("Movimento invalido! Parede ou fora dos limites!\n");
            // Som de erro: frequência baixa e longo
            Beep(400, 300);
        }
    }

    return 0;
}
