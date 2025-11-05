#include <stdio.h>
#include <string.h>

// Definição da estrutura Territorio
// Armazena o nome do território, a cor do exército e a quantidade de tropas
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Declaração de um vetor para armazenar 5 territórios
    struct Territorio territorios[5];

    // Loop para entrada dos dados dos 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("\nCadastro do território %d:\n", i + 1);

        // Entrada do nome do território
        printf("Digite o nome do território: ");
        scanf("%s", territorios[i].nome);  // Atenção: não aceita espaços

        // Entrada da cor do exército
        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);  // Atenção: não aceita espaços

        // Entrada da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    printf("\n--- Dados dos Territórios Cadastrados ---\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exercito: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;
}