#include <stdio.h>
#include <string.h>

#define MAX_CARTAS 2        /* quantidade fixa só para demonstração */
#define TAM_COD    6
#define TAM_NOME  50
#define TAM_ESTADO 3

typedef struct {
    char codigo[TAM_COD];           /* código da carta, ex.: “C01”   */
    char nome[TAM_NOME];            /* nome da cidade / país         */
    char estado[TAM_ESTADO];        /* UF ou sigla de país           */
    long  populacao;                /* habitantes                    */
    double area;                    /* km²                           */
    double pib;                     /* PIB em USD bilhões            */
    int   pontosTuristicos;         /* quantidade                    */
} Carta;

/* ===== PROTÓTIPOS ================================================= */
void cadastrarCartas(Carta cartas[], int n);
void mostrarCarta(const Carta *c);
int  compararCartas(const Carta *c1, const Carta *c2, int atributoEscolhido,
                    int *atributoUsado);

/* ===== FUNÇÃO PRINCIPAL =========================================== */
int main(void)
{
    Carta cartas[MAX_CARTAS];
    int cadastradas = 0;
    int opcao, atributo, atributoUsado;

    do {
        puts("\n=== MENU SUPER TRUNFO – NÍVEL AVENTUREIRO ===");
        puts("1. Cadastrar cartas");
        puts("2. Comparar cartas");
        puts("3. Sair");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCartas(cartas, MAX_CARTAS);
                cadastradas = 1;
                break;

            case 2:
                if (!cadastradas) {
                    puts("[!] Cadastre as cartas primeiro!");
                    break;
                }
                puts("\nAtributos disponíveis:");
                puts("1. População");
                puts("2. Área");
                puts("3. PIB");
                puts("4. Pontos turísticos");
                printf("Escolha o atributo principal: ");
                scanf("%d", &atributo);

                int vencedor = compararCartas(&cartas[0], &cartas[1],
                                               atributo, &atributoUsado);

                puts("\n=== RESULTADO ===");
                printf("Carta vencedora: %s (%s)\n",
                       cartas[vencedor].nome, cartas[vencedor].codigo);

                const char *nomesAttr[] = {
                    "Indefinido", "População", "Área", "PIB",
                    "Pontos turísticos"
                };
                printf("Atributo decisivo: %s\n", nomesAttr[atributoUsado]);
                break;

            case 3:
                puts("Saindo… Até a próxima!");
                break;

            default:
                puts("[!] Opção inválida.");
        }
    } while (opcao != 3);

    return 0;
}

/* ===== IMPLEMENTAÇÕES ============================================ */

/* 1. Cadastro ------------------------------------------------------ */
void cadastrarCartas(Carta cartas[], int n)
{
    for (int i = 0; i < n; ++i) {
        printf("\n--- Carta %d de %d ---\n", i + 1, n);

        printf("Código (até %d chars): ", TAM_COD - 1);
        scanf("%s", cartas[i].codigo);

        printf("Nome: ");
        getchar();                         /* limpa \n pendente */
        fgets(cartas[i].nome, TAM_NOME, stdin);
        cartas[i].nome[strcspn(cartas[i].nome, "\n")] = '\0';

        printf("Estado/País (sigla): ");
        scanf("%s", cartas[i].estado);

        printf("População: ");
        scanf("%ld", &cartas[i].populacao);

        printf("Área (km²): ");
        scanf("%lf", &cartas[i].area);

        printf("PIB (USD bilhões): ");
        scanf("%lf", &cartas[i].pib);

        printf("Nº de pontos turísticos: ");
        scanf("%d", &cartas[i].pontosTuristicos);
    }
    puts("\n[OK] Cartas cadastradas!");
}

/* 2. Comparar ------------------------------------------------------ */
/* Retorna 0 ou 1 (índice da carta vencedora).
   AtributoEscolhido: 1‑4 conforme menu.
   atributoUsado devolve qual atributo foi realmente decisivo.        */
int compararCartas(const Carta *c1, const Carta *c2, int atributoEscolhido,
                   int *atributoUsado)
{
    /* Ordem de desempate: atributoEscolhido → População → PIB → Área → PontosTuristicos */
    int ordem[] = { atributoEscolhido, 1, 3, 2, 4 };

    for (int i = 0; i < 5; ++i) {
        switch (ordem[i]) {
            case 1: /* População (maior ganha) */
                if (c1->populacao != c2->populacao) {
                    *atributoUsado = 1;
                    return c1->populacao > c2->populacao ? 0 : 1;
                }
                break;

            case 2: /* Área (maior ganha) */
                if (c1->area != c2->area) {
                    *atributoUsado = 2;
                    return c1->area > c2->area ? 0 : 1;
                }
                break;

            case 3: /* PIB (maior ganha) */
                if (c1->pib != c2->pib) {
                    *atributoUsado = 3;
                    return c1->pib > c2->pib ? 0 : 1;
                }
                break;

            case 4: /* Pontos turísticos (maior ganha) */
                if (c1->pontosTuristicos != c2->pontosTuristicos) {
                    *atributoUsado = 4;
                    return c1->pontosTuristicos > c2->pontosTuristicos ? 0 : 1;
                }
                break;
        }
    }
    /* Empate absoluto – devolve primeira carta por convenção */
    *atributoUsado = 0;
    puts("[=] Empate total!");
    return 0;
}
