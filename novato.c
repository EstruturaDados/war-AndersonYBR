// =========================================================
// PROJETO WAR - NÍVEL NOVATO: CONSTRUÇÃO DOS TERRITÓRIOS
// OBJETIVO: Cadastrar e exibir dados de 5 territórios usando um vetor de structs.
// =========================================================

#include <stdio.h>  // Para funções de entrada/saída como printf, scanf
#include <string.h> // Para manipulação de strings (embora não estritamente necessário aqui, é boa prática para strings)

// Constante para definir o número fixo de territórios a serem cadastrados
#define NUM_TERRITORIOS 5

// ---------------------------------------------------------
// 1. DEFINIÇÃO DA STRUCT (REQUISITO: Criação da struct)
// Define a estrutura de dados que agrupa as informações de um único Território.
// char nome[30], char cor[10] e int tropas.
// ---------------------------------------------------------
typedef struct {
    char nome[30];  // Nome do território (ex: Brasil)
    char cor[10];   // Cor do exército que o domina (ex: Vermelho)
    int tropas;     // Número de exércitos no território
} Territorio;

// Função auxiliar para limpar o buffer após o uso do scanf, 
// prevenindo quebra de leitura nas chamadas subsequentes de entrada.
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ---------------------------------------------------------
// FUNÇÃO PRINCIPAL
// ---------------------------------------------------------
int main() {
    // 2. DECLARAÇÃO DO VETOR DE STRUCTS (REQUISITO: Vetor com capacidade para 5)
    // Cria um vetor (array) que pode armazenar 5 estruturas do tipo Territorio.
    Territorio mapa[NUM_TERRITORIOS]; 
    int i; // Variável de controle para os laços 'for'

    printf("===================================================\n");
    printf("     SISTEMA DE CADASTRO DE TERRITÓRIOS (WAR)\n");
    printf("===================================================\n");
    printf("Iniciando o cadastro de %d territórios...\n\n", NUM_TERRITORIOS);

    // ---------------------------------------------------------
    // 3. ENTRADA DE DADOS (REQUISITO: Cadastro dos territórios)
    // Utiliza um laço 'for' para preencher os dados dos 5 territórios.
    // Usabilidade: Mensagens claras para orientar o usuário.
    // ---------------------------------------------------------
    for (i = 0; i < NUM_TERRITORIOS; i++) {
        printf("--- Cadastro do Território #%d ---\n", i + 1);

        // NOME (Usando scanf para simplicidade, mas é crucial limpar o buffer antes)
        printf("   Digite o NOME: ");
        // Usamos scanf para a string, mas ele lê até o primeiro espaço/quebra de linha.
        // O tamanho [29] é para garantir que não ultrapasse 30 (30 é o limite + \0)
        if (scanf("%29s", mapa[i].nome) != 1) { 
            limparBuffer();
            printf("Erro na leitura do nome. Tente novamente.\n");
            i--; // Volta uma iteração
            continue;
        }
        limparBuffer(); // Limpa a entrada após o scanf

        // COR DO EXÉRCITO
        printf("   Digite a COR do Exército (ex: Vermelho): ");
        if (scanf("%9s", mapa[i].cor) != 1) { 
            limparBuffer();
            printf("Erro na leitura da cor. Tente novamente.\n");
            i--;
            continue;
        }
        limparBuffer(); // Limpa a entrada após o scanf

        // TROPAS (Usando scanf)
        printf("   Digite a quantidade de TROPAS: ");
        if (scanf("%d", &mapa[i].tropas) != 1) {
            limparBuffer();
            printf("Entrada inválida para tropas. Digite um número inteiro.\n");
            i--; // Volta uma iteração
            continue;
        }
        limparBuffer(); // Limpa o buffer após a leitura do número
        printf("------------------------------------\n");
    }

    // ---------------------------------------------------------
    // 4. EXIBIÇÃO DE DADOS (REQUISITO: Exibição dos dados)
    // Percorre o vetor e exibe os dados de cada território com formatação clara.
    // Desempenho: O sistema exibe os dados imediatamente após o laço de cadastro.
    // ---------------------------------------------------------
    printf("\n\n===================================================\n");
    printf("           DADOS DOS TERRITÓRIOS CADASTRADOS\n");
    printf("===================================================\n");

    for (i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Território #%d:\n", i + 1);
        printf("  > NOME: %s\n", mapa[i].nome);
        printf("  > COR DO EXÉRCITO: %s\n", mapa[i].cor);
        printf("  > TROPAS: %d\n", mapa[i].tropas);
        printf("---------------------------------------------------\n");
    }

    printf("\nFim do programa de cadastro de territórios.\n");
    return 0;
}