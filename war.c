#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  // para usar srand() e time()

#define MAX_POSSIVEL 10000

// Estrutura do território
struct territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Limpa o buffer de entrada
void limparbufferentrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ---------------------------
// Função que simula um ataque
// ---------------------------
void atacar(struct territorio *atacante, struct territorio *defensor) {
    printf("\n===== Iniciando ataque =====\n");
    printf("%s (%s) está atacando %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    // Cada um rola um dado (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nDado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Comparação dos resultados
    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu esta rodada!\n");
        defensor->tropas -= 1;  // defensor perde 1 tropa
        if (defensor->tropas <= 0) {
            printf("\nO território %s foi conquistado por %s!\n",
                   defensor->nome, atacante->cor);
            defensor->tropas = 1; // assume controle com 1 tropa
            strcpy(defensor->cor, atacante->cor); // muda a cor (dono)
        }
    } else {
        printf("\nO defensor resistiu ao ataque!\n");
        atacante->tropas -= 1; // atacante perde 1 tropa
        if (atacante->tropas < 0) atacante->tropas = 0;
    }

    // Exibe a situação após o ataque
    printf("\n--- Situação após o ataque ---\n");
    printf("Atacante: %s | Cor: %s | Tropas: %d\n",
           atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s | Cor: %s | Tropas: %d\n",
           defensor->nome, defensor->cor, defensor->tropas);
    printf("------------------------------\n");
}

int main() {
    struct territorio *guerra = NULL;
    int capacidade = 0;
    int totalterritorio = 0;
    int opcao;

    srand(time(NULL)); // inicializa gerador aleatório

    printf("Quantos territórios você quer alocar? ");
    scanf("%d", &capacidade);
    limparbufferentrada();

    if (capacidade <= 0 || capacidade > MAX_POSSIVEL) {
        printf("Número inválido.\n");
        return 1;
    }

    guerra = (struct territorio *) calloc((size_t)capacidade, sizeof(struct territorio));
    if (guerra == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    do {
        printf("\n============ WAR ============\n");
        printf("1 - Registrar novo território.\n");
        printf("2 - Listar territórios criados.\n");
        printf("3 - Simular ataque entre territórios.\n");
        printf("0 - Sair do jogo.\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparbufferentrada();

        switch (opcao) {
            // Cadastrar
            case 1:
                if (totalterritorio < capacidade) {
                    printf("Digite o nome do território: ");
                    fgets(guerra[totalterritorio].nome, sizeof(guerra[totalterritorio].nome), stdin);

                    printf("Digite a cor do exército: ");
                    fgets(guerra[totalterritorio].cor, sizeof(guerra[totalterritorio].cor), stdin);

                    guerra[totalterritorio].nome[strcspn(guerra[totalterritorio].nome, "\n")] = '\0';
                    guerra[totalterritorio].cor[strcspn(guerra[totalterritorio].cor, "\n")] = '\0';

                    printf("Digite o número de tropas: ");
                    scanf("%d", &guerra[totalterritorio].tropas);
                    limparbufferentrada();

                    totalterritorio++;
                    printf("\nTerritório cadastrado com sucesso!\n");
                } else {
                    printf("Limite de territórios atingido!\n");
                }
                printf("\nPressione Enter para continuar...\n");
                getchar();
                break;

            // Listar
            case 2:
                if (totalterritorio == 0) {
                    printf("Nenhum território cadastrado.\n");
                } else {
                    for (int i = 0; i < totalterritorio; i++) {
                        printf("-----------------------------\n");
                        printf("Território %d:\n", i + 1);
                        printf("Nome: %s\n", guerra[i].nome);
                        printf("Cor: %s\n", guerra[i].cor);
                        printf("Tropas: %d\n", guerra[i].tropas);
                    }
                }
                printf("\nPressione Enter para continuar...\n");
                getchar();
                break;

            // Simular ataque
            case 3:
                if (totalterritorio < 2) {
                    printf("É necessário ter pelo menos dois territórios.\n");
                } else {
                    printf("\n--- Territórios disponíveis ---\n");
                    for (int i = 0; i < totalterritorio; i++) {
                        printf("%d - %s (%s), Tropas: %d\n",
                               i + 1, guerra[i].nome, guerra[i].cor, guerra[i].tropas);
                    }

                    int a, d;
                    printf("\nEscolha o número do território atacante: ");
                    scanf("%d", &a);
                    printf("Escolha o número do território defensor: ");
                    scanf("%d", &d);
                    limparbufferentrada();

                    a--; d--; // ajusta para índice do vetor

                    if (a >= 0 && a < totalterritorio && d >= 0 && d < totalterritorio && a != d) {
                        atacar(&guerra[a], &guerra[d]);
                    } else {
                        printf("Índices inválidos.\n");
                    }
                }
                printf("\nPressione Enter para continuar...\n");
                getchar();
                break;

            // Sair
            case 0:
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opção inválida.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                break;
        }

    } while (opcao != 0);

    free(guerra);
    return 0;
}
