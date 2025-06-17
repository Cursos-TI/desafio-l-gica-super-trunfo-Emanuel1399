#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARTAS   2       /* Mantém‑se 2 cartas para demonstrar a lógica   */
#define TAM_COD      6
#define TAM_NOME    50
#define TAM_ESTADO   3

/* -------- estrutura principal ----------------------------------- */
typedef struct {
    char codigo[TAM_COD];
    char nome[TAM_NOME];
    char estado[TAM_ESTADO];
    long   populacao;
    double area;
    double pib;              /* USD bilhões                                 */
    int    pontosTuristicos;
} Carta;

/* -------- enumeração de atributos ------------------------------- */
typedef enum {
    POPULACAO = 1,
    AREA,
    PIB,
    P_TURISTICOS,
    TOTAL_ATRIBUTOS = P_TURISTICOS
} Atributo;

/* Nomes apresentados nos menus (mesmo índice do enum acima)        */
const char *attrNome[] = {
    "Indefinido",
    "População",
    "Área",
    "PIB",
    "Pontos turísticos"
};

/* --------- protótipos ------------------------------------------- */
void limparBuffer(void);
void cadastrarCartas(Carta c[], int n);
void exibirCarta(const Carta *c);
double valorDoAtributo(const Carta *c, Atributo a);
int comparar(const Carta *c1, const Carta *c2,
             Atributo pri, Atributo sec, Atributo *attrDecisor);

/* ===================== FUNÇÃO PRINCIPAL ========================= */
int main(void)
{
    Carta cartas[MAX_CARTAS];
    int cadastradas = 0;
    int opcao;

    do {
        puts("\n===== SUPER TRUNFO – MENU PRINCIPAL =====");
        puts("1. Cadastrar cartas");
        puts("2. Comparar cartas (dois atributos)");
        puts("3. Exibir cartas cadastradas");
        puts("4. Sair");
        printf("Escolha: ");
        scanf("%d", &opcao); limparBuffer();

        switch (opcao) {

        case 1: /* cadastro ------------------------------------------------ */
            cadastrarCartas(cartas, MAX_CARTAS);
            cadastradas = 1;
            break;

        case 2: /* comparação ---------------------------------------------- */
            if (!cadastradas) {
                puts("[!] Cadastre as cartas primeiro!");
                break;
            }

            /* mostra menu de atributos gerado dinamicamente */
            printf("\nAtributos disponíveis:\n");
            for (int i = 1; i <= TOTAL_ATRIBUTOS; ++i)
                printf("%d. %s\n", i, attrNome[i]);

            int a1, a2;
            printf("Escolha o 1º atributo: ");
            scanf("%d", &a1); limparBuffer();
            printf("Escolha o 2º atributo (diferente do primeiro): ");
            scanf("%d", &a2); limparBuffer();

            /* validação simples */
            if (a1 < 1 || a1 > TOTAL_ATRIBUTOS ||
                a2 < 1 || a2 > TOTAL_ATRIBUTOS || a1 == a2) {
                puts("[!] Seleção inválida.");
                break;
            }

            Atributo decisivo;
            int vencedor = comparar(&cartas[0], &cartas[1],
                                    (Atributo)a1, (Atributo)a2, &decisivo);

            puts("\n===== RESULTADO =====");
            if (vencedor == 0)
                puts("Empate absoluto!");
            else {
                printf("Carta vencedora: %s (%s)\n",
                       cartas[vencedor-1].nome, cartas[vencedor-1].codigo);
                printf("Atributo decisivo: %s\n", attrNome[decisivo]);
            }
            break;

        case 3: /* listar cartas ------------------------------------------ */
            if (!cadastradas) { puts("[!] Nenhuma carta cadastrada."); break; }
            puts("\n--- Carta 1 ---"); exibirCarta(&cartas[0]);
            puts("\n--- Carta 2 ---"); exibirCarta(&cartas[1]);
            break;

        case 4:
            puts("Até a próxima!");
            break;

        default:
            puts("[!] Opção inválida.");
        }

    } while (opcao != 4);

    return 0;
}

/* ===================== IMPLEMENTAÇÕES ========================== */

/* --------------------------------------------------------------- */
void limparBuffer(void)
{
    int ch; while ((ch = getchar()) != '\n' && ch != EOF);
}

/* cadastro ------------------------------------------------------ */
void cadastrarCartas(Carta c[], int n)
{
    for (int i = 0; i < n; ++i) {
        printf("\n=== CADASTRO CARTA %d/%d ===\n", i+1, n);

        printf("Código (até %d chars): ", TAM_COD-1);
        scanf("%5s", c[i].codigo); limparBuffer();

        printf("Nome: ");
        fgets(c[i].nome, TAM_NOME, stdin);
        c[i].nome[strcspn(c[i].nome, "\n")] = '\0';

        printf("Estado/País (sigla): ");
        scanf("%2s", c[i].estado); limparBuffer();

        printf("População: ");
        scanf("%ld", &c[i].populacao); limparBuffer();

        printf("Área (km²): ");
        scanf("%lf", &c[i].area); limparBuffer();

        printf("PIB (USD bilhões): ");
        scanf("%lf", &c[i].pib); limparBuffer();

        printf("Nº de pontos turísticos: ");
        scanf("%d", &c[i].pontosTuristicos); limparBuffer();
    }
    puts("\n[OK] Cartas cadastradas.");
}

/* exibição ------------------------------------------------------ */
void exibirCarta(const Carta *c)
{
    printf("Código: %s\n", c->codigo);
    printf("Nome: %s\n", c->nome);
    printf("Sigla: %s\n", c->estado);
    printf("População: %ld\n", c->populacao);
    printf("Área: %.2f km²\n", c->area);
    printf("PIB: %.2f USD bilhões\n", c->pib);
    printf("Pontos turísticos: %d\n", c->pontosTuristicos);
}

/* valor numérico genérico de qualquer atributo ----------------- */
double valorDoAtributo(const Carta *c, Atributo a)
{
    switch (a) {
        case POPULACAO:      return (double)c->populacao;
        case AREA:           return c->area;
        case PIB:            return c->pib;
        case P_TURISTICOS:   return (double)c->pontosTuristicos;
        default:             return 0.0;
    }
}

/* comparação avançada (dois atributos) -------------------------- */
/* Retorno: 1 → carta1 vence | 2 → carta2 vence | 0 → empate       */
int comparar(const Carta *c1, const Carta *c2,
             Atributo pri, Atributo sec, Atributo *attrDecisor)
{
    double v1 = valorDoAtributo(c1, pri);
    double v2 = valorDoAtributo(c2, pri);

    /* operador ternário aninhado decide rápido                */
    int resultado =
        (v1 > v2) ? 1 :
        (v1 < v2) ? 2 :
        /* se empatou no primeiro, testa o segundo atributo     */
        (
            ( (v1 = valorDoAtributo(c1, sec)) > (v2 = valorDoAtributo(c2, sec)) ) ? 1 :
            (v1 < v2) ? 2 : 0
        );

    *attrDecisor = (resultado == 0) ? sec :       /* se ainda empate, sec foi último testado */
                    ( (v1 == v2) ? sec : pri );   /* caso vitória, ver qual atributo decidiu */

    return resultado;
}
