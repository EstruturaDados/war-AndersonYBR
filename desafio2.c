#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Definição da Struct ---
// Struct para representar um território no jogo WAR.
typedef struct {
    char nome[30];
    char cor[10]; // Ex: "Vermelho", "Azul"
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
void inicializar_territorios(Territorio** mapa, int* num_territorios);
void exibir_territorios(const Territorio* mapa, int num_territorios);
void atacar(Territorio* mapa, int num_territorios);
void exibir_pos_ataque(const Territorio* t);
int rolar_dado();
void liberarMemoria(Territorio* mapa);

// -------------------------------------------------------------------
//                             FUNÇÃO PRINCIPAL
// -------------------------------------------------------------------

int main() {
    // Inicializa a semente para a função rand() com base no tempo atual,
    // garantindo que os resultados dos dados sejam diferentes a cada execução.
    srand(time(NULL));

    Territorio* mapa = NULL; // Ponteiro para o vetor de territórios.
    int num_territorios = 0; // Variável para armazenar o tamanho do vetor.
    char opcao;

    // 1. Alocação Dinâmica e Cadastro Inicial
    inicializar_territorios(&mapa, &num_territorios);

    // Verifica se a alocação foi bem-sucedida e se há territórios para jogar
    if (mapa == NULL || num_territorios == 0) {
        printf("\nNenhum territorio cadastrado. Encerrando o programa.\n");
        return 0;
    }

    // Loop principal do jogo
    do {
        printf("\n============================================\n");
        printf("SIMULADOR DE BATALHA WAR - TERRITORIOS ATUAIS\n");
        printf("============================================\n");
        exibir_territorios(mapa, num_territorios);

        // 2. Simulação do Ataque
        atacar(mapa, num_territorios);

        // 3. Continuação
        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &opcao);
        while (getchar() != '\n'); // Limpa o buffer de entrada

    } while (opcao == 's' || opcao == 'S');

    // 4. Gerenciamento de Memória
    liberarMemoria(mapa);

    printf("\nPrograma encerrado. Memoria liberada com sucesso.\n");
    return 0;
}

// -------------------------------------------------------------------
//                        FUNÇÕES AUXILIARES
// -------------------------------------------------------------------

/**
 * @brief Solicita o número de territórios, aloca a memória e cadastra os dados.
 * * @param mapa Ponteiro para o ponteiro do vetor de Territorio.
 * @param num_territorios Ponteiro para a variável que armazenará o tamanho.
 */
void inicializar_territorios(Territorio** mapa, int* num_territorios) {
    int i;
    
    printf("Informe o numero total de territorios: ");
    if (scanf("%d", num_territorios) != 1 || *num_territorios <= 0) {
        printf("Entrada invalida. Usando 3 territorios padrao.\n");
        *num_territorios = 3;
    }
    while (getchar() != '\n'); // Limpa o buffer de entrada

    // Alocação dinâmica de memória para o vetor de Territorio
    // Usando calloc para inicializar a memória com zeros (boas práticas).
    *mapa = (Territorio*)calloc(*num_territorios, sizeof(Territorio));

    if (*mapa == NULL) {
        perror("Erro ao alocar memoria para os territorios");
        *num_territorios = 0;
        return;
    }

    printf("\n--- CADASTRO DE TERRITORIOS ---\n");
    for (i = 0; i < *num_territorios; i++) {
        // Acesso e manipulação dos dados utilizando aritmética de ponteiros
        Territorio* t = *mapa + i; 

        printf("\nTerritorio %d:\n", i);
        printf("Nome: ");
        // Leitura segura do nome
        if (fgets(t->nome, sizeof(t->nome), stdin) != NULL) {
             t->nome[strcspn(t->nome, "\n")] = 0; // Remove o '\n'
        }

        printf("Cor do exercito: ");
        if (fgets(t->cor, sizeof(t->cor), stdin) != NULL) {
            t->cor[strcspn(t->cor, "\n")] = 0; // Remove o '\n'
        }
        
        // Garante que o território comece com no mínimo 1 tropa para poder atacar
        do {
            printf("Numero de tropas (min 1): ");
        } while (scanf("%d", &t->tropas) != 1 || t->tropas < 1);
        while (getchar() != '\n');
    }
}

/**
 * @brief Exibe os dados atuais de todos os territórios cadastrados.
 * * @param mapa Ponteiro constante para o vetor de Territorio.
 * @param num_territorios O número total de territórios.
 */
void exibir_territorios(const Territorio* mapa, int num_territorios) {
    int i;
    printf("ID | Nome                       | Cor       | Tropas\n");
    printf("---|----------------------------|-----------|-------\n");
    for (i = 0; i < num_territorios; i++) {
        // Acesso de leitura aos dados utilizando aritmética de ponteiros
        const Territorio* t = mapa + i; 
        printf("%-3d| %-27s| %-10s| %d\n", i, t->nome, t->cor, t->tropas);
    }
}

/**
 * @brief Rola um dado de 6 lados.
 * * @return int O resultado da rolagem (1 a 6).
 */
int rolar_dado() {
    // rand() % 6 gera um número de 0 a 5. Somamos 1 para obter 1 a 6.
    return (rand() % 6) + 1;
}

/**
 * @brief Simula um ataque entre dois territórios e atualiza seus dados.
 * * @param mapa O vetor de territórios.
 * @param num_territorios O número total de territórios.
 */
void atacar(Territorio* mapa, int num_territorios) {
    int id_atacante, id_defensor;
    Territorio *atacante = NULL, *defensor = NULL;
    int dado_ataque, dado_defesa;
    
    // --- Seleção e Validação dos IDs ---
    printf("\n--- SELECAO DE ATAQUE ---\n");

    do {
        printf("ID do Territorio Atacante: ");
        if (scanf("%d", &id_atacante) != 1) {
            id_atacante = -1; // Força repetição
        }
        while (getchar() != '\n');

        // Validação básica do ID
        if (id_atacante < 0 || id_atacante >= num_territorios) {
            printf("ID de atacante invalido. Tente novamente.\n");
            continue;
        }

        // Obtém o ponteiro do atacante (Aritmética de ponteiros)
        atacante = mapa + id_atacante;

        // Validação de tropas: precisa de pelo menos 2 tropas para atacar (1 fica).
        if (atacante->tropas < 2) {
            printf("O territorio %s tem apenas %d tropas. Precisa de no minimo 2 para atacar.\n", 
                   atacante->nome, atacante->tropas);
            atacante = NULL; // Força repetição
        }

    } while (atacante == NULL);
    
    do {
        printf("ID do Territorio Defensor: ");
        if (scanf("%d", &id_defensor) != 1) {
            id_defensor = -1; // Força repetição
        }
        while (getchar() != '\n');

        // Validação básica do ID
        if (id_defensor < 0 || id_defensor >= num_territorios) {
            printf("ID de defensor invalido. Tente novamente.\n");
            defensor = NULL;
            continue;
        }

        // Validação: Não pode ser o mesmo território
        if (id_atacante == id_defensor) {
            printf("O atacante nao pode atacar a si mesmo. Escolha outro ID.\n");
            defensor = NULL;
            continue;
        }

        // Obtém o ponteiro do defensor (Aritmética de ponteiros)
        defensor = mapa + id_defensor;

        // Validação: Não pode atacar um território da própria cor
        if (strcmp(atacante->cor, defensor->cor) == 0) {
            printf("O atacante nao pode atacar um territorio da propria cor (%s). Escolha outro defensor.\n", atacante->cor);
            defensor = NULL;
        }

    } while (defensor == NULL);

    printf("\n--- INICIO DA BATALHA ---\n");
    printf("%s (Cor: %s, Tropas: %d) ATACA %s (Cor: %s, Tropas: %d)\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);

    // --- Simulação da Rolagem de Dados ---
    dado_ataque = rolar_dado();
    dado_defesa = rolar_dado();

    printf("\nRolagem de Dados:\n");
    printf("  Atacante (dado): %d\n", dado_ataque);
    printf("  Defensor (dado): %d\n", dado_defesa);
    
    // --- Resolução e Atualização de Dados ---
    if (dado_ataque > dado_defesa) {
        // Atacante vence
        printf("\n*** VITORIA DO ATACANTE! ***\n");
        printf("Territorio %s CONQUISTADO!\n", defensor->nome);

        // 1. Defensor muda de dono (Cor do atacante)
        strcpy(defensor->cor, atacante->cor);
        
        // 2. Transferência de tropas
        // O atacante perde metade das tropas (arredondado para baixo) para a conquista.
        int tropas_perdidas = atacante->tropas / 2; 

        // O defensor recebe as tropas transferidas.
        defensor->tropas = tropas_perdidas;

        // O atacante mantém o restante das suas tropas.
        atacante->tropas -= tropas_perdidas;

    } else {
        // Defensor vence ou empate (Defensor sempre vence em caso de empate)
        printf("\n*** VITORIA DO DEFENSOR! ***\n");
        printf("Ataque repelido.\n");

        // O atacante perde uma tropa.
        atacante->tropas -= 1;

        // Validação: Se o atacante ficar com 0 tropas, define para 1 (Regra do WAR: sempre deve sobrar 1 no território)
        if (atacante->tropas < 1) {
            atacante->tropas = 1; 
        }
    }

    // --- Exibição Pós-Ataque ---
    printf("\n--- DADOS ATUALIZADOS ---\n");
    printf("\nTerritorio Atacante (%s):\n", atacante->nome);
    exibir_pos_ataque(atacante);

    printf("\nTerritorio Defensor (%s):\n", defensor->nome);
    exibir_pos_ataque(defensor);
}

/**
 * @brief Exibe os dados de um único território após um ataque.
 * * @param t Ponteiro constante para o território a ser exibido.
 */
void exibir_pos_ataque(const Territorio* t) {
    // Acesso aos dados por meio do ponteiro ->
    printf("  - Cor Atual: %s\n", t->cor);
    printf("  - Tropas Atuais: %d\n", t->tropas);
}

/**
 * @brief Libera a memória alocada dinamicamente para o vetor de Territorio.
 * * @param mapa Ponteiro para o vetor de Territorio a ser liberado.
 */
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
}