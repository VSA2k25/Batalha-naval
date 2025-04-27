#include <stdio.h>

#define TAMANHO_TABULEIRO 10 // Tamanho fixo do tabuleiro (10x10)
#define TAMANHO_HABILIDADE 5 // Tamanho das matrizes de habilidade (5x5)

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== Tabuleiro ===\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("~ "); // Água
            } else if (tabuleiro[i][j] == 3) {
                printf("N "); // Navio
            } else if (tabuleiro[i][j] == 5) {
                printf("* "); // Área afetada pela habilidade
            }
        }
        printf("\n"); // Quebra de linha após cada linha do tabuleiro
    }
}

// Função para criar uma matriz de habilidade Cone
void criarCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Condição para formar um cone apontando para baixo
            if (i >= j && i >= TAMANHO_HABILIDADE - 1 - j) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar uma matriz de habilidade Cruz
void criarCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Condição para formar uma cruz
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar uma matriz de habilidade Octaedro
void criarOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Condição para formar um losango (octaedro visto de frente)
            if (i + j >= TAMANHO_HABILIDADE / 2 && i + j <= TAMANHO_HABILIDADE / 2 + TAMANHO_HABILIDADE - 1 &&
                i - j <= TAMANHO_HABILIDADE / 2 && j - i <= TAMANHO_HABILIDADE / 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar a habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linhaOrigem, int colunaOrigem) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linhaTabuleiro = linhaOrigem - TAMANHO_HABILIDADE / 2 + i;
            int colunaTabuleiro = colunaOrigem - TAMANHO_HABILIDADE / 2 + j;

            // Verifica se a posição está dentro dos limites do tabuleiro
            if (linhaTabuleiro >= 0 && linhaTabuleiro < TAMANHO_TABULEIRO &&
                colunaTabuleiro >= 0 && colunaTabuleiro < TAMANHO_TABULEIRO &&
                habilidade[i][j] == 1) {
                tabuleiro[linhaTabuleiro][colunaTabuleiro] = 5; // Marca a área afetada
            }
        }
    }
}

int main() {
    // Inicializa o tabuleiro com 0s (água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Posiciona alguns navios no tabuleiro
    tabuleiro[2][3] = 3; // Navio horizontal
    tabuleiro[5][6] = 3; // Navio vertical
    tabuleiro[1][1] = 3; // Navio diagonal principal
    tabuleiro[3][8] = 3; // Navio diagonal secundária

    // Cria as matrizes de habilidade
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Define pontos de origem para as habilidades
    int linhaOrigemCone = 4, colunaOrigemCone = 4;
    int linhaOrigemCruz = 7, colunaOrigemCruz = 7;
    int linhaOrigemOctaedro = 2, colunaOrigemOctaedro = 2;

    // Aplica as habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, linhaOrigemCone, colunaOrigemCone);
    aplicarHabilidade(tabuleiro, cruz, linhaOrigemCruz, colunaOrigemCruz);
    aplicarHabilidade(tabuleiro, octaedro, linhaOrigemOctaedro, colunaOrigemOctaedro);

    // Exibe o tabuleiro com os navios e as áreas afetadas pelas habilidades
    imprimirTabuleiro(tabuleiro);

    return 0;
}