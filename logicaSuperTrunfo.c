#include <stdio.h>
#include <string.h>

// Definindo a struct Territorio para armazenar os dados de cada território
struct Territorio {
    char nome[30];      // Nome do território (até 29 caracteres + '\0')
    char cor[10];       // Cor do exército (até 9 caracteres + '\0')
    int tropas;         // Quantidade de tropas
};

int main() {
    // Vetor para armazenar 5 territórios
    struct Territorio territorios[5];

    printf("=== CADASTRO DE TERRITORIOS ===\n");

    // Loop para cadastrar os 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d:\n", i + 1);

        // Nome
        printf("Nome: ");
        scanf("%29s", territorios[i].nome);  // Lê até 29 caracteres para evitar overflow

        // Cor do exército
        printf("Cor do exercito: ");
        scanf("%9s", territorios[i].cor);    // Lê até 9 caracteres

        // Quantidade de tropas
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        // Limpa o buffer do teclado para evitar problemas no próximo scanf
        while (getchar() != '\n');
    }

    // Exibição dos dados cadastrados
    printf("\n=== DADOS DOS TERRITORIOS ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}