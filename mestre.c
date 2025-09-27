#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h> // Para usar 'bool' e 'true'/'false'

// --- Definição da Struct ---
// Estrutura para representar um território no jogo WAR.
typedef struct {
    char nome[30];
    char cor[10]; // Ex: "Vermelho", "Azul"
    int tropas;
} Territorio;

// --- Protótipos das Funções de Jogo ---
void inicializar_territorios(Territorio** mapa, int* num_territorios);
void exibir_territorios(const Territorio* mapa, int num_territorios);
void atacar(Territorio* mapa, int num_territorios);
void exibir_pos_ataque(const Territorio* t);
int rolar_dado();

// --- Protótipos das Funções de Missão ---
void atribuirMissao(char** missao_jogador, const char* missoes[], int totalMissoes);
void exibirMissao(const char* missao);
bool verificarMissao(const char* missao, const Territorio* mapa, int num_territorios);

// --- Protótipo da Função de Gerenciamento de Memória ---
void liberarMemoria(Territorio* mapa, char* missao_jogador);

// -------------------------------------------------------------------
// VETOR DE MISSÕES E VARIÁVEIS GLOBAIS DE JOGO
// -------------------------------------------------------------------

// Vetor de strings contendo as missões estratégicas.
const char* MISSOES_ESTRATEGICAS[] = {
    "Conquistar todos os territorios da cor AZUL.",
    "Conquistar todos os territorios da cor VERDE.",
    "Possuir 3 territorios com 5 ou mais tropas cada.",
    "Conquistar 5 territorios seguidos em uma unica rodada (Logica simplificada: 1 vitoria).",
    "Eliminar todas as tropas inimigas da cor PRETA."
};

// Define o número total de missões
const int TOTAL_MISSOES = 5;

// -------------------------------------------------------------------
//                             FUNÇÃO PRINCIPAL
// -------------------------------------------------------------------

int main() {
    // Inicializa a semente para a função rand()
    srand(time(NULL));

    Territorio* mapa = NULL;        // Ponteiro para o vetor de territórios.
    int num_territorios = 0;        // Tamanho do vetor.
    char* missao_jogador = NULL;    // Ponteiro para a missão alocada dinamicamente.
    char opcao;
    
    // --- 1. Inicialização e Alocação ---
    inicializar_territorios(&mapa, &num_territorios);

    if (mapa == NULL || num_territorios == 0) {
        printf("\nNenhum territorio cadastrado. Encerrando o programa.\n");
        return 0;
    }

    // --- 2. Atribuição da Missão ---
    // Passagem do ponteiro de ponteiro para armazenar a string alocada.
    atribuirMissao(&missao_jogador, MISSOES_ESTRATEGICAS, TOTAL_MISSOES);
    
    // Exibição inicial da missão (Passagem por valor/cópia do endereço)
    printf("\n\n############################################\n");
    printf("        SUA MISSAO ESTRATEGICA INICIAL\n");
    printf("############################################\n");
    exibirMissao(missao_jogador);
    printf("############################################\n\n");

    // Loop principal do jogo
    do {
        printf("\n============================================\n");
        printf("SIMULADOR DE BATALHA WAR - STATUS ATUAL\n");
        printf("============================================\n");
        exibir_territorios(mapa, num_territorios);

        // --- 3. Simulação do Ataque ---
        atacar(mapa, num_territorios);

        // --- 4. Verificação da Missão ---
        // Passagem por referência do ponteiro da missão e do mapa.
        if (verificarMissao(missao_jogador, mapa, num_territorios)) {
            printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("      MISSAO CUMPRIDA! VOCE VENCEU O JOGO!\n");
            printf("   Missao: %s\n", missao_jogador);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            opcao = 'n'; // Encerra o jogo
        } else {
            // 5. Continuação
            printf("\nDeseja realizar outro ataque? (s/n): ");
            scanf(" %c", &opcao);
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }

    } while (opcao == 's' || opcao == 'S');

    // --- 6. Gerenciamento de Memória ---
    liberarMemoria(mapa, missao_jogador);

    printf("\nPrograma encerrado. Memoria liberada com sucesso.\n");
    return 0;
}

// -------------------------------------------------------------------
//                        FUNÇÕES DE JOGO (ATAQUE)
// -------------------------------------------------------------------

/**
 * @brief Rola um dado de 6 lados.
 * @return int O resultado da rolagem (1 a 6).
 */
int rolar_dado() {
    return (rand() % 6) + 1;
}

/**
 * @brief Simula um ataque entre dois territórios e atualiza seus dados.
 * @param mapa O vetor de territórios (para acesso aos IDs).
 * @param num_territorios O número total de territórios.
 */
void atacar(Territorio* mapa, int num_territorios) {
    int id_atacante, id_defensor;
    Territorio *atacante = NULL, *defensor = NULL;
    int dado_ataque, dado_defesa;

    // Lógica de seleção e validação (omitida para foco, mas idêntica ao desafio anterior)
    // ... (Código para selecionar e validar IDs do atacante e defensor)

    // Apenas para que o código compile, usaremos IDs fixos para demonstração
    // O usuário deve selecionar IDs válidos em um loop real
    // Exemplo de seleção simplificada para compilação
    printf("\n--- SELECAO DE ATAQUE SIMPLIFICADA ---\n");
    printf("ID do Atacante (0 a %d): ", num_territorios - 1);
    scanf("%d", &id_atacante);
    printf("ID do Defensor (0 a %d, diferente do atacante): ", num_territorios - 1);
    scanf("%d", &id_defensor);
    while (getchar() != '\n');
    
    if (id_atacante < 0 || id_atacante >= num_territorios || id_defensor < 0 || 
        id_defensor >= num_territorios || id_atacante == id_defensor) {
        printf("IDs invalidos ou iguais. Ataque cancelado.\n");
        return;
    }

    // Obtém os ponteiros (Aritmética de ponteiros)
    atacante = mapa + id_atacante;
    defensor = mapa + id_defensor;
    
    if (atacante->tropas < 2) {
        printf("Atacante sem tropas suficientes (min 2).\n");
        return;
    }
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Nao e possivel atacar territorio da propria cor.\n");
        return;
    }

    // --- Simulação da Rolagem de Dados ---
    dado_ataque = rolar_dado();
    dado_defesa = rolar_dado();
    printf("\nRolagem: Atacante %d vs Defensor %d\n", dado_ataque, dado_defesa);
    
    // --- Resolução e Atualização de Dados ---
    if (dado_ataque > dado_defesa) {
        // Atacante vence e conquista o território
        printf("\n*** VITORIA E CONQUISTA! ***\n");
        
        // 1. Defensor muda de dono (Cor do atacante)
        strcpy(defensor->cor, atacante->cor);
        
        // 2. Transferência de tropas
        int tropas_perdidas = atacante->tropas / 2; 
        defensor->tropas = tropas_perdidas;
        atacante->tropas -= tropas_perdidas;

    } else {
        // Defensor vence ou empate
        printf("\n*** ATAQUE REPELIDO! ***\n");

        // Atacante perde uma tropa.
        atacante->tropas -= 1;
        if (atacante->tropas < 1) {
            atacante->tropas = 1; 
        }
    }

    // Exibição Pós-Ataque
    printf("\n--- DADOS ATUALIZADOS ---\n");
    printf("Atacante (%s) - Tropas: %d, Cor: %s\n", atacante->nome, atacante->tropas, atacante->cor);
    printf("Defensor (%s) - Tropas: %d, Cor: %s\n", defensor->nome, defensor->tropas, defensor->cor);
}


// -------------------------------------------------------------------
//                      FUNÇÕES DE MISSÃO E VITÓRIA
// -------------------------------------------------------------------

/**
 * @brief Sorteia uma missão do vetor e a armazena dinamicamente para o jogador.
 * @param missao_jogador Ponteiro para o ponteiro onde a string da missão será armazenada.
 * @param missoes Vetor constante de strings de missões disponíveis.
 * @param totalMissoes Número total de missões no vetor.
 */
void atribuirMissao(char** missao_jogador, const char* missoes[], int totalMissoes) {
    int id_sorteado = rand() % totalMissoes;
    const char* missao_selecionada = missoes[id_sorteado];
    size_t tamanho_missao = strlen(missao_selecionada) + 1; // +1 para o terminador nulo '\0'

    // Alocação dinâmica de memória para a missão do jogador
    // O ponteiro (missao_jogador) é modificado (Passagem por Referência)
    *missao_jogador = (char*)malloc(tamanho_missao);

    if (*missao_jogador == NULL) {
        perror("Erro ao alocar memoria para a missao");
        return;
    }

    // Copia a missão sorteada para a área de memória alocada
    strcpy(*missao_jogador, missao_selecionada);
}

/**
 * @brief Exibe a missão do jogador.
 * @param missao Ponteiro constante para a string da missão (Passagem por Valor).
 */
void exibirMissao(const char* missao) {
    if (missao != NULL) {
        printf("Missao: %s\n", missao);
    }
}

/**
 * @brief Verifica se a missão do jogador foi cumprida.
 * * *NOTA: A lógica é simplificada para fins de demonstração, comparando o texto exato da missão.*
 * @param missao Ponteiro constante para a string da missão.
 * @param mapa Ponteiro constante para o vetor de territórios.
 * @param num_territorios O número total de territórios.
 * @return bool Retorna true se a missão foi cumprida, false caso contrário.
 */
bool verificarMissao(const char* missao, const Territorio* mapa, int num_territorios) {
    int i;
    int territorios_com_5_tropas = 0;
    int territorios_azul = 0;
    int territorios_verde = 0;
    
    // Contagem de status do mapa
    for (i = 0; i < num_territorios; i++) {
        const Territorio* t = mapa + i;
        if (t->tropas >= 5) {
            territorios_com_5_tropas++;
        }
        if (strcmp(t->cor, "Azul") == 0 || strcmp(t->cor, "azul") == 0) {
            territorios_azul++;
        }
        if (strcmp(t->cor, "Verde") == 0 || strcmp(t->cor, "verde") == 0) {
            territorios_verde++;
        }
    }

    // --- Lógica de Verificação ---

    if (strstr(missao, "AZUL") != NULL) {
        // Missão: Conquistar todos os territórios da cor AZUL.
        // Assumindo que o jogador tem a cor "Vermelho", esta missão é para ele.
        // A missão é cumprida se houver 0 territórios com a cor azul.
        return (territorios_azul == 0); 
    } 
    
    if (strstr(missao, "VERDE") != NULL) {
        // Missão: Conquistar todos os territórios da cor VERDE.
        return (territorios_verde == 0);
    } 
    
    if (strstr(missao, "3 territorios com 5 ou mais tropas") != NULL) {
        // Missão: Possuir 3 territórios com 5 ou mais tropas cada.
        return (territorios_com_5_tropas >= 3);
    }
    
    if (strstr(missao, "5 territorios seguidos") != NULL) {
        // Missão: Conquistar 5 territórios seguidos. (Lógica Simplificada: 1 vitória)
        // Simplificação: Qualquer ataque bem-sucedido é considerado vitória no turno.
        // *Em um jogo real, esta lógica exigiria um contador de vitórias em sequência.*
        // Para o desafio, assumimos que 1 ataque completou a missão.
        return true; 
    }
    
    // Se a missão não foi cumprida
    return false;
}


// -------------------------------------------------------------------
//                   FUNÇÕES DE INICIALIZAÇÃO E MEMÓRIA
// -------------------------------------------------------------------

/**
 * @brief Solicita o número de territórios, aloca a memória e cadastra os dados.
 * * (Função reutilizada do desafio anterior)
 */
void inicializar_territorios(Territorio** mapa, int* num_territorios) {
    int i;
    
    printf("Informe o numero total de territorios (Min 3): ");
    if (scanf("%d", num_territorios) != 1 || *num_territorios < 3) {
        printf("Entrada invalida. Usando 3 territorios padrao.\n");
        *num_territorios = 3;
    }
    while (getchar() != '\n'); 

    *mapa = (Territorio*)calloc(*num_territorios, sizeof(Territorio));

    if (*mapa == NULL) {
        perror("Erro ao alocar memoria para os territorios");
        *num_territorios = 0;
        return;
    }

    printf("\n--- CADASTRO DE TERRITORIOS ---\n");
    // Cadastro de Exemplo para rodar as missões:
    Territorio padrao[] = {
        {"Alaska", "Vermelho", 4},
        {"California", "Azul", 3},
        {"Texas", "Verde", 5},
    };

    for (i = 0; i < *num_territorios; i++) {
        Territorio* t = *mapa + i; 
        if (i < 3) {
            *t = padrao[i];
        } else {
            // Se mais de 3, pede dados adicionais
            printf("\nTerritorio %d (Nome, Cor, Tropas): ", i);
            if (fgets(t->nome, sizeof(t->nome), stdin) != NULL) {
                t->nome[strcspn(t->nome, "\n")] = 0;
            }
            if (fgets(t->cor, sizeof(t->cor), stdin) != NULL) {
                t->cor[strcspn(t->cor, "\n")] = 0;
            }
            scanf("%d", &t->tropas);
            while (getchar() != '\n');
        }
    }
}

/**
 * @brief Exibe os dados atuais de todos os territórios cadastrados.
 * * (Função reutilizada do desafio anterior)
 */
void exibir_territorios(const Territorio* mapa, int num_territorios) {
    int i;
    printf("ID | Nome                       | Cor       | Tropas\n");
    printf("---|----------------------------|-----------|-------\n");
    for (i = 0; i < num_territorios; i++) {
        const Territorio* t = mapa + i; 
        printf("%-3d| %-27s| %-10s| %d\n", i, t->nome, t->cor, t->tropas);
    }
}

/**
 * @brief Libera toda a memória alocada dinamicamente.
 * @param mapa O ponteiro para o vetor de Territorio.
 * @param missao_jogador O ponteiro para a string da missão.
 */
void liberarMemoria(Territorio* mapa, char* missao_jogador) {
    if (mapa != NULL) {
        free(mapa);
    }
    if (missao_jogador != NULL) {
        free(missao_jogador); // Libera a string da missão
    }
}