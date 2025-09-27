⚔️ Simulador de Batalha WAR Estruturado em C
Este projeto implementa uma simulação básica de batalhas entre territórios do jogo de tabuleiro WAR (similar ao Risco). O sistema utiliza alocação dinâmica de memória para gerenciar os territórios e ponteiros para manipular seus dados, focando em boas práticas de programação em C.

🌟 Funcionalidades
Alocação Dinâmica (calloc): O número de territórios é definido pelo usuário no início e o espaço é alocado dinamicamente.

Gestão por Ponteiros: Todos os acessos e modificações aos dados dos territórios (nome, cor, tropas) são realizados diretamente por ponteiros.

Simulação de Ataque: Implementa a função atacar que simula a rolagem de um dado de 6 lados para o atacante e o defensor.

Atualização de Status:

Vitória do Atacante: O território defensor muda de dono (recebe a cor do atacante) e recebe metade das tropas do atacante.

Vitória do Defensor: O atacante perde 1 tropa.

Gerenciamento de Memória: A memória alocada é liberada corretamente ao final do programa usando free().

⚙️ Requisitos do Sistema
Para compilar e executar este programa, você precisará de:

Um Compilador C (ex: GCC, MinGW, Clang).

Um Ambiente de Desenvolvimento ou terminal compatível.

🚀 Como Compilar e Executar
1. Salvar o Código
Salve o código-fonte (fornecido anteriormente) em um arquivo chamado desafio_war.c.

2. Compilação (Usando GCC/MinGW)
Abra seu terminal ou prompt de comando e use o seguinte comando para compilar o código:

Bash

gcc desafio_war.c -o desafio_war
3. Execução
Execute o programa compilado:

Bash

./desafio_war
🎮 Instruções de Uso
Ao executar, o programa pedirá:

Número de Territórios: Digite quantos territórios farão parte do jogo.

Cadastro Inicial: Para cada território, insira o Nome, a Cor do exército e o número inicial de Tropas (mínimo 1).

Ataque: O sistema exibirá uma lista de IDs. Para atacar, você deve fornecer:

ID do Território Atacante: Deve ter no mínimo 2 tropas.

ID do Território Defensor: Não pode ter a mesma cor do atacante.

O resultado da batalha (rolagem de dados) será exibido, e os dados dos territórios serão atualizados e mostrados.

O programa perguntará se você deseja realizar outro ataque (s/n).

🧠 Estrutura do Código
Função	Descrição
main()	Função principal. Inicializa a semente aleatória (srand), chama o cadastro e executa o loop de ataques.
inicializar_territorios()	Solicita o número de territórios, aloca o vetor dinamicamente e cadastra os dados iniciais. Utiliza calloc.
exibir_territorios()	Exibe a lista completa de territórios e seus status.
rolar_dado()	Retorna um número aleatório entre 1 e 6.
atacar()	Controla a seleção de atacante/defensor, valida as regras, simula a rolagem e atualiza o nome, cor e tropas dos territórios via ponteiros.
exibir_pos_ataque()	Exibe os dados de um único território após um ataque.
liberarMemoria()	Função essencial que utiliza free() para liberar a memória alocada dinamicamente, evitando vazamentos.

Exportar para as Planilhas
📝 Tecnologias
Linguagem: C

Bibliotecas: stdio.h, stdlib.h, string.h, time.h