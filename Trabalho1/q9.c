// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: João Gabriel de Santana Bispo
//  email: joao_gabriel_bispo@hotmail.com
//  Matrícula:20242160011@ifba.edu.br
//  Semestre:2025.1

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021

// #################################################
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
        int col = n.coluna + (n.direcao == 'H' ? i : 0);
        tab[lin][col] = NAVIO;
    }
}

// Lê navio do usuário
Navio lerNavio(int jogador, int tamanho) {
    Navio n;
    char entrada[10];

    while (1) {
        printf("Jogador %d, posicione navio de tamanho %d (ex: A1 H): ", jogador, tamanho);
        fgets(entrada, sizeof(entrada), stdin);
        char linhaChar, direcao;
        int coluna;
        if (sscanf(entrada, "%c%d %c", &linhaChar, &coluna, &direcao) == 3) {
            n.linha = toupper(linhaChar) - 'A';
            n.coluna = coluna;
            n.direcao = toupper(direcao);
            n.tamanho = tamanho;
            if (n.direcao == 'H' || n.direcao == 'V')
                return n;
        }
        printf("Entrada inválida. Tente novamente.\n");
    }
}

// Jogador realiza um tiro
void realizarTiro(char tab[TAM][TAM], int jogador) {
    char entrada[10];
    char linhaChar;
    int coluna;
    int linha;

    while (1) {
        printf("Jogador %d, digite sua jogada (ex: B2): ", jogador);
        fgets(entrada, sizeof(entrada), stdin);
        if (sscanf(entrada, "%c%d", &linhaChar, &coluna) == 2) {
            linha = toupper(linhaChar) - 'A';
            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                if (tab[linha][coluna] == NAVIO) {
                    printf("Acertou!\n");
                    tab[linha][coluna] = ABATIDO;
                } else if (tab[linha][coluna] == MAR) {
                    printf("Água.\n");
                    tab[linha][coluna] = TIRO_INVALIDO;
                } else {
                    printf("Tiro repetido. Tente novamente.\n");
                    continue;
                }
                break;
            }
        }
        printf("Entrada inválida. Tente novamente.\n");
    }
}

// Conta navios abatidos
int contarNaviosRestantes(char tab[TAM][TAM]) {
    int vivos = 0;
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tab[i][j] == NAVIO)
                vivos++;
    return vivos;
}

// Função principal
int main() {
    char tabuleiro1[TAM][TAM], tabuleiro2[TAM][TAM];
    int tamanhos[] = {4, 3, 1, 1, 1, 2}; // Tamanhos obrigatórios
    inicializaTabuleiro(tabuleiro1);
    inicializaTabuleiro(tabuleiro2);

    printf("### BATALHA NAVAL ###\n");

    // Posicionamento jogador 1
    for (int i = 0; i < total_navios; i++) {
        mostrarTabuleiro(tabuleiro1);
        Navio n;
        do {
            n = lerNavio(1, tamanhos[i]);
        } while (!podePosicionar(tabuleiro1, n));
        posicionarNavio(tabuleiro1, n);
    }

    // Posicionamento jogador 2
    for (int i = 0; i < total_navios; i++) {
        mostrarTabuleiro(tabuleiro2);
        Navio n;
        do {
            n = lerNavio(2, tamanhos[i]);
        } while (!podePosicionar(tabuleiro2, n));
        posicionarNavio(tabuleiro2, n);
    }

    // Jogo
    while (1) {
        printf("\n--- Jogador 1 ---\n");
        mostrarTabuleiro(tabuleiro2);
        realizarTiro(tabuleiro2, 1);
        if (contarNaviosRestantes(tabuleiro2) == 0) {
            printf("Jogador 1 venceu!\n");
            break;
        }

        printf("\n--- Jogador 2 ---\n");
        mostrarTabuleiro(tabuleiro1);
        realizarTiro(tabuleiro1, 2);
        if (contarNaviosRestantes(tabuleiro1) == 0) {
            printf("Jogador 2 venceu!\n");
            break;
        }
    }

    return 0;
}
