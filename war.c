#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do território
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Função para cadastrar territórios
void cadastrarTerritorios(struct Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do território %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);  // aceita espaços
        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os territórios
void exibirTerritorios(struct Territorio* mapa, int n) {
    printf("\n--- Territórios ---\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n\n", mapa[i].tropas);
    }
}

// Função de ataque entre dois territórios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: não é possível atacar um território da mesma cor!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nSimulação de ataque:\n");
    printf("%s (atacante) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (defensor) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Vitória do atacante!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("Defensor resistiu ao ataque.\n");
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

// Função para liberar memória
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL));  // inicializa aleatoriedade

    int n;
    printf("Digite o número de territórios: ");
    scanf("%d", &n);

    // Alocação dinâmica
    struct Territorio* mapa = (struct Territorio*) calloc(n, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);
    exibirTerritorios(mapa, n);

    // Loop de ataque
    char continuar;
    do {
        int a, d;
        printf("\nEscolha o território atacante (1 a %d): ", n);
        scanf("%d", &a);
        printf("Escolha o território defensor (1 a %d): ", n);
        scanf("%d", &d);

        if (a < 1 || a > n || d < 1 || d > n || a == d) {
            printf("Escolhas inválidas.\n");
        } else {
            atacar(&mapa[a - 1], &mapa[d - 1]);
            exibirTerritorios(mapa, n);
        }

        printf("Deseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa);
    return 0;
}