#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10
#define MAX_NAVIOS 10

// Representações visuais
#define MAR ' '
#define NAVIO 'N'
#define ABATIDO '0'
#define TIRO_INVALIDO 'X'

// Tipos
typedef struct {
    int tamanho;
    int linha;
    int coluna;
    char direcao; // 'H' ou 'V'
} Navio;

// Variáveis globais
int total_navios = 6; // Ex: 1 de tamanho 4, 1 de tamanho 3, 3 de tamanho 1, 1 de tamanho 2

// Função para iniciar tabuleiro
void inicializaTabuleiro(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = MAR;
}

// Mostra tabuleiro do próprio jogador
void mostrarTabuleiro(char tab[TAM][TAM]) {
    printf("   ");
    for (int j = 0; j < TAM; j++)
        printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2c ", 'A' + i);
        for (int j = 0; j < TAM; j++) {
            printf("[%c]", tab[i][j]);
        }
        printf("\n");
    }
}

// Verifica se navio pode ser posicionado
int podePosicionar(char tab[TAM][TAM], Navio n) {
    for (int i = 0; i < n.tamanho; i++) {
        int lin = n.linha + (n.direcao == 'V' ? i : 0);
        int col = n.coluna + (n.direcao == 'H' ? i : 0);

        if (lin < 0 || lin >= TAM || col < 0 || col >= TAM || tab[lin][col] != MAR)
            return 0;
    }
    return 1;
}

// Posiciona navio
void posicionarNavio(char tab[TAM][TAM], Navio n) {
    for (int i = 0; i < n.tamanho; i++) {
        int lin = n.linha + (n.direcao == 'V' ? i : 0);
        int col = n.
