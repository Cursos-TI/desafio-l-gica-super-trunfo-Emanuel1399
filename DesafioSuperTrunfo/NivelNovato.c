#include <stdio.h>

// Função para cadastrar uma carta
void cadastrarCarta(char estado[], char codigo[], char nomeCidade[], int *populacao, float *area, float *pib, int *pontos, float *densidade) {
    printf("\n--- Cadastro da Carta ---\n");
    printf("Estado: ");
    scanf(" %[^\n]", estado);
    printf("Código da Carta: ");
    scanf(" %[^\n]", codigo);
    printf("Nome da Cidade: ");
    scanf(" %[^\n]", nomeCidade);
    printf("População: ");
    scanf("%d", populacao);
    printf("Área (em km²): ");
    scanf("%f", area);
    printf("PIB (em bilhões): ");
    scanf("%f", pib);
    printf("Número de Pontos Turísticos: ");
    scanf("%d", pontos);

    if (*area != 0)
        *densidade = *populacao / *area;
    else
        *densidade = 0;
}

// Função para exibir os dados de uma carta
void exibirCarta(char estado[], char codigo[], char nomeCidade[], int populacao, float area, float pib, int pontos, float densidade) {
    printf("\n--- Carta ---\n");
    printf("Estado: %s\n", estado);
    printf("Código: %s\n", codigo);
    printf("Cidade: %s\n", nomeCidade);
    printf("População: %d\n", populacao);
    printf("Área: %.2f km²\n", area);
    printf("PIB: %.2f bilhões\n", pib);
    printf("Pontos Turísticos: %d\n", pontos);
    printf("Densidade Populacional: %.2f\n", densidade);
}

// Função para comparar dois valores e retornar 1 se a carta1 vence, ou 2 se carta2 vence
int comparar(int opcao, int pop1, int pop2, float area1, float area2, float pib1, float pib2, int pontos1, int pontos2, float dens1, float dens2) {
    switch (opcao) {
        case 1:
            return (pop1 > pop2) ? 1 : 2;
        case 2:
            return (area1 > area2) ? 1 : 2;
        case 3:
            return (pib1 > pib2) ? 1 : 2;
        case 4:
            return (pontos1 > pontos2) ? 1 : 2;
        case 5:
            return (dens1 < dens2) ? 1 : 2;
        default:
            return 0;
    }
}

int main() {
    // Dados da carta 1
    char estado1[50], codigo1[20], cidade1[50];
    int populacao1, pontos1;
    float area1, pib1, densidade1;

    // Dados da carta 2
    char estado2[50], codigo2[20], cidade2[50];
    int populacao2, pontos2;
    float area2, pib2, densidade2;

    printf("🎮 Super Trunfo - Países (C - Nível Novato)\n");

    cadastrarCarta(estado1, codigo1, cidade1, &populacao1, &area1, &pib1, &pontos1, &densidade1);
    cadastrarCarta(estado2, codigo2, cidade2, &populacao2, &area2, &pib2, &pontos2, &densidade2);

    exibirCarta(estado1, codigo1, cidade1, populacao1, area1, pib1, pontos1, densidade1);
    exibirCarta(estado2, codigo2, cidade2, populacao2, area2, pib2, pontos2, densidade2);

    printf("\n📌 Atributos para comparação:\n");
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. PIB\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Populacional (vence o menor)\n");
    printf("Escolha um número: ");
    int escolha;
    scanf("%d", &escolha);

    int vencedor = comparar(escolha, populacao1, populacao2, area1, area2, pib1, pib2, pontos1, pontos2, densidade1, densidade2);

    printf("\n🏆 Carta Vencedora:");
    if (vencedor == 1)
        exibirCarta(estado1, codigo1, cidade1, populacao1, area1, pib1, pontos1, densidade1);
    else if (vencedor == 2)
        exibirCarta(estado2, codigo2, cidade2, populacao2, area2, pib2, pontos2, densidade2);
    else
        printf("\nErro na escolha do atributo!\n");

    return 0;
}
