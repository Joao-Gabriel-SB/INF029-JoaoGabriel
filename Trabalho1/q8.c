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
#include <string.h>
#include <ctype.h>

#define LINHAS 3
#define COLUNAS 3

void inicializarTabuleiro(char tab[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            tab[i][j] = ' ';
}

void mostrarTabuleiro(char tab[LINHAS][COLUNAS]) {
    printf("   1   2   3\n");
    for (int i = 0; i < LINHAS; i++) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < COLUNAS; j++) {
            printf(" %c ", tab[i][j]);
            if (j < 2) printf("|");
        }
        if (i < 2) printf("\n  ---|---|---\n");
    }
    printf("\n");
}

int verificarVencedor(char tab[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        // Verifica linhas
        if (tab[i][0] != ' ' && tab[i][0] == tab[i][1] && tab[i][1] == tab[i][2])
            return tab[i][0];
        // Verifica colunas
        if (tab[0][i] != ' ' && tab[0][i] == tab[1][i] && tab[1][i] == tab[2][i])
            return tab[0][i];
    }
    // Verifica diagonais
    if (tab[0][0] != ' ' && tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2])
        return tab[0][0];
    if (tab[0][2] != ' ' && tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0])
        return tab[0][2];
    
    return 0;
}

int jogadaValida(char jogada[], int *linha, int *coluna) {
    if (strlen(jogada) != 2)
        return 0;

    char l = toupper(jogada[0]);
    char c = jogada[1];

    if (l < 'A' || l > 'C' || c < '1' || c > '3')
        return 0;

    *linha = l - 'A';
    *coluna = c - '1';

    return 1;
}

int main() {
    char tabuleiro[LINHAS][COLUNAS];
    char jogada[10];
    int linha, coluna, jogador = 1, movimentos = 0;
    char simbolo;

    inicializarTabuleiro(tabuleiro);

    while (1) {
        mostrarTabuleiro(tabuleiro);
        simbolo = jogador == 1 ? 'X' : 'O';

        printf("Jogador %d, informe sua jogada (ex: B2): ", jogador);
        fgets(jogada, sizeof(jogada), stdin);
        jogada[strcspn(jogada, "\n")] = '\0'; // remove newline

        if (!jogadaValida(jogada, &linha, &coluna)) {
            printf("Jogada inválida! Tente novamente.\n");
            continue;
        }

        if (tabuleiro[linha][coluna] != ' ') {
            printf("Célula ocupada! Tente novamente.\n");
            continue;
        }

        tabuleiro[linha][coluna] = simbolo;
        movimentos++;

        int vencedor = verificarVencedor(tabuleiro);
        if (vencedor) {
            mostrarTabuleiro(tabuleiro);
            printf("Jogador %d (%c) venceu!\n", jogador, vencedor);
            break;
        } else if (movimentos == 9) {
            mostrarTabuleiro(tabuleiro);
            printf("Empate! Ninguém venceu.\n");
            break;
        }

        jogador = 3 - jogador; // alterna entre 1 e 2
    }

    return 0;
}
