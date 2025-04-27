#include <stdio.h>

#define TAMANHO_TABULEIRO 10 // Tamanho fixo do tabuleiro (10x10)
#define TAMANHO_NAVIO 3      // Tamanho fixo dos navios (3 posições)

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== Tabuleiro ===\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]); // Imprime cada célula do tabuleiro
        }
        printf("\n"); // Quebra de linha após cada linha do tabuleiro
    }
}

// Função para verificar se o navio cabe no tabuleiro sem sobreposição
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao) {
    if (orientacao == 0) { // Horizontal
        // Verifica se o navio cabe horizontalmente
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Erro: Navio horizontal fora dos limites.\n");
            return 0;
        }
        // Verifica se há sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != 0) {
                printf("Erro: Sobreposição detectada na posição (%d, %d).\n", linha, coluna + i);
                return 0;
            }
        }
        // Posiciona o navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = 3;
        }
    } else if (orientacao == 1) { // Vertical
        // Verifica se o navio cabe verticalmente
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Erro: Navio vertical fora dos limites.\n");
            return 0;
        }
        // Verifica se há sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != 0) {
                printf("Erro: Sobreposição detectada na posição (%d, %d).\n", linha + i, coluna);
                return 0;
            }
        }
        // Posiciona o navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = 3;
        }
    } else if (orientacao == 2) { // Diagonal principal (linha e coluna aumentam simultaneamente)
        // Verifica se o navio cabe na diagonal
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Erro: Navio diagonal principal fora dos limites.\n");
            return 0;
        }
        // Verifica se há sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna + i] != 0) {
                printf("Erro: Sobreposição detectada na posição (%d, %d).\n", linha + i, coluna + i);
                return 0;
            }
        }
        // Posiciona o navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna + i] = 3;
        }
    } else if (orientacao == 3) { // Diagonal secundária (linha aumenta, coluna diminui)
        // Verifica se o navio cabe na diagonal
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna - TAMANHO_NAVIO < -1) {
            printf("Erro: Navio diagonal secundária fora dos limites.\n");
            return 0;
        }
        // Verifica se há sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna - i] != 0) {
                printf("Erro: Sobreposição detectada na posição (%d, %d).\n", linha + i, coluna - i);
                return 0;
            }
        }
        // Posiciona o navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna - i] = 3;
        }
    }
    return 1; // Posicionamento bem-sucedido
}

int main() {
    // Inicializa o tabuleiro com 0s (água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Coordenadas iniciais dos navios (podem ser alteradas diretamente no código)
    int linhaNavio1 = 2, colunaNavio1 = 3; // Navio horizontal
    int linhaNavio2 = 5, colunaNavio2 = 7; // Navio vertical
    int linhaNavio3 = 1, colunaNavio3 = 1; // Navio diagonal principal
    int linhaNavio4 = 3, colunaNavio4 = 8; // Navio diagonal secundária

    // Posiciona os navios
    if (!posicionarNavio(tabuleiro, linhaNavio1, colunaNavio1, 0)) {
        printf("Erro ao posicionar o primeiro navio (horizontal). Verifique as coordenadas e o tamanho.\n");
        return 1;
    }
    if (!posicionarNavio(tabuleiro, linhaNavio2, colunaNavio2, 1)) {
        printf("Erro ao posicionar o segundo navio (vertical). Verifique as coordenadas e o tamanho.\n");
        return 1;
    }
    if (!posicionarNavio(tabuleiro, linhaNavio3, colunaNavio3, 2)) {
        printf("Erro ao posicionar o terceiro navio (diagonal principal). Verifique as coordenadas e o tamanho.\n");
        return 1;
    }
    if (!posicionarNavio(tabuleiro, linhaNavio4, colunaNavio4, 3)) {
        printf("Erro ao posicionar o quarto navio (diagonal secundária). Verifique as coordenadas e o tamanho.\n");
        return 1;
    }

    // Exibe o tabuleiro com os navios posicionados
    imprimirTabuleiro(tabuleiro);

    return 0;
}