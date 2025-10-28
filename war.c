#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// número máximo de territórios
#define maxterritorio 5   

// Estrutura que representa um território do jogo
struct territorio {  
    char nome[30];
    char cor[10];
    int tropas;
};

// limpa o buffer do teclado
void limparbufferentrada() {  
    int c; 
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct territorio guerra[maxterritorio];
    int totalterritorio = 0;
    int opcao;

    do {
        printf("\n============ WAR ============\n");
        printf("1 - Registrar novo território.\n");
        printf("2 - Listar territórios criados.\n");
        printf("0 - Sair do jogo.\n\n");
        printf("Escolha uma opção: ");

        scanf("%d", &opcao);
        limparbufferentrada();

        switch (opcao) {
            // cadastrar novo território
            case 1:  
                if (totalterritorio < maxterritorio) {
                    printf("Digite o nome do territorio: ");
                    fgets(guerra[totalterritorio].nome, 30, stdin);

                    printf("Digite a cor do territorio: ");
                    fgets(guerra[totalterritorio].cor, 10, stdin);

                    // remove o '\n' do final das strings
                    guerra[totalterritorio].nome[strcspn(guerra[totalterritorio].nome, "\n")] = '\0';
                    guerra[totalterritorio].cor[strcspn(guerra[totalterritorio].cor, "\n")] = '\0';

                    printf("Digite quantas são as tropas do territorio: ");
                    scanf("%d", &guerra[totalterritorio].tropas);
                    limparbufferentrada();

                    totalterritorio++;  // adiciona 1 ao total
                    printf("\nTerritório cadastrado com sucesso!\n");
                } else {
                    printf("Limite de territórios atingido!\n");
                }
                printf("\nPressione pra continuar...\n");
                getchar();
                break;

            // listar territórios
            case 2:  
                if (totalterritorio == 0) {
                    printf("Nenhum território cadastrado.\n");
                } else {
                    for (int i = 0; i < totalterritorio; i++) {
                        printf("-----------------------------\n");
                        printf("Território: %d\n", i + 1);
                        printf("Nome: %s\n", guerra[i].nome);
                        printf("Cor: %s\n", guerra[i].cor);
                        printf("Tropas: %d\n", guerra[i].tropas);
                    }
                }
                printf("\nPressione pra continuar...\n");
                getchar();
                break;

            // sair do programa
            case 0: 
                printf("Saindo do sistema...\n");
                break;

            // opção inválida
            default:
                printf("Opcao invalida, tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                break;
        }

    } while (opcao != 0);  // repete até sair

    return 0;
}