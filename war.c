#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("\nCadastro do território %d:\n", i + 1);
        printf("Digite o nome do território: ");
        scanf("%s", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os dados dos territórios
void exibirTerritorios(Territorio* mapa, int tamanho) {
    printf("\n=== Dados dos Territórios ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Quantidade de Tropas: %d\n\n", mapa[i].tropas);
    }
}

// Função que simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Ataque inválido! Os territórios têm a mesma cor.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nSimulação de ataque:\n");
    printf("%s (atacante) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (defensor) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = defensor->tropas / 2;
        printf("Resultado: %s conquistou %s!\n", atacante->nome, defensor->nome);
    } else {
        atacante->tropas = (atacante->tropas > 0) ? atacante->tropas - 1 : 0;
        printf("Resultado: %s falhou no ataque e perdeu uma tropa.\n", atacante->nome);
    }
}

// Função que sorteia uma missão para o jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Função que verifica se a missão foi cumprida (lógica simplificada)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strcmp(missao, "Conquistar 3 territórios seguidos") == 0) {
        int cont = 0;
        for (int i = 1; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, mapa[i - 1].cor) == 0) {
                cont++;
                if (cont >= 2) return 1;
            } else {
                cont = 0;
            }
        }
    } else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    // Outras missões podem ser adicionadas aqui
    return 0;
}

// Função para liberar memória alocada
void liberarMemoria(Territorio* mapa, char* missaoJogador) {
    free(mapa);
    free(missaoJogador);
}

int main() {
    srand(time(NULL));

    int quantidade;
    printf("Digite o número de territórios a cadastrar: ");
    scanf("%d", &quantidade);

    // Alocação dinâmica dos territórios
    Territorio* mapa = (Territorio*)calloc(quantidade, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Vetor de missões disponíveis
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar pelo menos 4 territórios",
        "Ter mais de 50 tropas no total",
        "Conquistar um território chamado Fortaleza"

    };
    int totalMissoes = 5;

    // Alocação da missão do jogador
    char* missaoJogador = (char*)malloc(100 * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memória para missão.\n");
        free(mapa);
        return 1;
    }

    // Atribuição e exibição da missão
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    printf("\nSua missão: %s\n", missaoJogador);

    // Cadastro e exibição inicial
    cadastrarTerritorios(mapa, quantidade);
    exibirTerritorios(mapa, quantidade);

    // Simulação de ataque
    int atacante, defensor;
    printf("\nEscolha o número do território atacante (1 a %d): ", quantidade);
    scanf("%d", &atacante);
    printf("Escolha o número do território defensor (1 a %d): ", quantidade);
    scanf("%d", &defensor);

    if (atacante < 1 || atacante > quantidade || defensor < 1 || defensor > quantidade) {
        printf("Índice inválido.\n");
    } else {
        atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
        exibirTerritorios(mapa, quantidade);

        // Verificação da missão
        if (verificarMissao(missaoJogador, mapa, quantidade)) {
            printf("\nParabéns! Você cumpriu sua missão: %s\n", missaoJogador);
        } else {
            printf("\nMissão ainda não cumprida.\n");
        }
    }

    // Liberação de memória
    liberarMemoria(mapa, missaoJogador);

    return 0;
}