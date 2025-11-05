// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Estrutura de território */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* Protótipos das funções (modularização) */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
void exibirMissao(const char* missao); /* passagem por valor para exibição */
int verificarMissao(char* missao, Territorio* mapa, int tamanho); /* verificação "silenciosa" */
void atacar(Territorio* atacante, Territorio* defensor);
void exibirMapa(Territorio* mapa, int tamanho);
void liberarMemoria(char* missaoJogador, Territorio* mapa);

/* Vetor de missões (pelo menos 5) */
char* missoesDisponiveis[] = {
    "Conquistar 3 territorios seguidos",
    "Eliminar todas as tropas da cor vermelha",
    "Controlar todos os territorios azuis",
    "Ter mais de 20 tropas no total",
    "Dominar metade do mapa"
};

int main() {
    srand((unsigned) time(NULL));

    int totalMissoes = sizeof(missoesDisponiveis) / sizeof(missoesDisponiveis[0]);

    /* --- Criando mapa de exemplo (alocado dinamicamente) --- */
    int tamanhoMapa = 6;
    Territorio* mapa = (Territorio*) calloc(tamanhoMapa, sizeof(Territorio));
    if (!mapa) {
        perror("Erro alocacao mapa");
        return 1;
    }

    /* Inicializa alguns territórios de exemplo */
    strcpy(mapa[0].nome, "TerritorioA"); strcpy(mapa[0].cor, "azul");    mapa[0].tropas = 5;
    strcpy(mapa[1].nome, "TerritorioB"); strcpy(mapa[1].cor, "vermelho"); mapa[1].tropas = 4;
    strcpy(mapa[2].nome, "TerritorioC"); strcpy(mapa[2].cor, "verde");   mapa[2].tropas = 3;
    strcpy(mapa[3].nome, "TerritorioD"); strcpy(mapa[3].cor, "azul");    mapa[3].tropas = 6;
    strcpy(mapa[4].nome, "TerritorioE"); strcpy(mapa[4].cor, "vermelho"); mapa[4].tropas = 2;
    strcpy(mapa[5].nome, "TerritorioF"); strcpy(mapa[5].cor, "amarelo"); mapa[5].tropas = 8;

    /* --- Criando missão do jogador (armazenada dinamicamente) --- */
    char* missaoJogador = (char*) malloc(128 * sizeof(char)); /* espaço suficiente */
    if (!missaoJogador) {
        perror("Erro alocacao missao");
        free(mapa);
        return 1;
    }

    atribuirMissao(missaoJogador, missoesDisponiveis, totalMissoes);
    /* Exibir missão apenas uma vez (interface intuitiva) */
    printf(">>> MISSÃO RECEBIDA (apenas uma vez):\n");
    exibirMissao(missaoJogador);
    printf("\n");

    /* Exibir mapa inicial */
    printf("Mapa inicial:\n");
    exibirMapa(mapa, tamanhoMapa);
    printf("\n");

    /* Simulação simples de turnos: tentamos ataques aleatórios e checamos missão silenciosamente */
    int maxTurnos = 50;
    int vencedor = 0; /* 0 = ninguém, 1 = jogador cumpriu missão */

    for (int turno = 1; turno <= maxTurnos && !vencedor; turno++) {
        /* tentar encontrar um par válido (atacante != defensor e cores diferentes e atacante com tropas > 0) */
        int tentativas = 0;
        int idxAtq = -1, idxDef = -1;
        while (tentativas < 50) {
            int a = rand() % tamanhoMapa;
            int d = rand() % tamanhoMapa;
            if (a == d) { tentativas++; continue; }
            if (strcmp(mapa[a].cor, mapa[d].cor) == 0) { tentativas++; continue; } /* só atacar inimigo */
            if (mapa[a].tropas <= 0) { tentativas++; continue; }
            idxAtq = a; idxDef = d;
            break;
        }

        if (idxAtq == -1) {
            /* nenhum ataque possível no turno */
            //printf("Turno %d: sem ataques possíveis.\n", turno);
        } else {
            //printf("Turno %d: %s (cor %s, tropas %d) ataca %s (cor %s, tropas %d)\n",
            //       turno, mapa[idxAtq].nome, mapa[idxAtq].cor, mapa[idxAtq].tropas,
            //       mapa[idxDef].nome, mapa[idxDef].cor, mapa[idxDef].tropas);

            atacar(&mapa[idxAtq], &mapa[idxDef]);
        }

        /* Verifica missão silenciosamente ao fim de cada turno */
        if (verificarMissao(missaoJogador, mapa, tamanhoMapa)) {
            printf("\n>>> MISSÃO CUMPRIDA NO TURNO %d! Você venceu.\n", turno);
            exibirMapa(mapa, tamanhoMapa);
            vencedor = 1;
            break;
        }

        /* opcional: pequenas pausas/feedback podem ser descomentadas para ver simulação detalhada */
        //exibirMapa(mapa, tamanhoMapa);
    }

    if (!vencedor) {
        printf("\nFim da simulação: missão não cumprida em %d turnos.\n", maxTurnos);
        exibirMapa(mapa, tamanhoMapa);
    }

    /* liberar toda memória alocada */
    liberarMemoria(missaoJogador, mapa);

    return 0;
}

/* --------------------------------------------------------------
   atribuirMissao
   Sorteia uma missão e copia para 'destino' usando strcpy.
   'destino' deve apontar para memória alocada pelo chamador.
   -------------------------------------------------------------- */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    if (!destino || !missoes || totalMissoes <= 0) return;
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

/* --------------------------------------------------------------
   exibirMissao
   Recebe a missão por valor (const char*), exibe ao jogador.
   -------------------------------------------------------------- */
void exibirMissao(const char* missao) {
    if (!missao) {
        printf("Nenhuma missão atribuída.\n");
        return;
    }
    printf("%s\n", missao);
}

/* --------------------------------------------------------------
   verificarMissao
   Avalia se a missão foi cumprida com uma lógica simples.
   Retorna 1 se cumprida, 0 caso contrário.
   Implementa checks para cada missão do vetor de exemplo.
   -------------------------------------------------------------- */
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (!missao || !mapa || tamanho <= 0) return 0;

    /* Conquistar 3 territorios seguidos
       Interpretado como existir uma sequência de 3 territorios adjacentes
       no vetor que pertençam à mesma cor. (lógica simples para demo) */
    if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0) {
        for (int i = 0; i <= tamanho - 3; i++) {
            if (strlen(mapa[i].cor) == 0) continue;
            if (strcmp(mapa[i].cor, mapa[i+1].cor) == 0 &&
                strcmp(mapa[i].cor, mapa[i+2].cor) == 0 &&
                mapa[i].tropas > 0 && mapa[i+1].tropas > 0 && mapa[i+2].tropas > 0) {
                return 1;
            }
        }
        return 0;
    }

    /* Eliminar todas as tropas da cor vermelha
       Interpretado como não existir território com cor 'vermelho' com tropas > 0 */
    if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 0) return 0;
        }
        return 1;
    }

    /* Controlar todos os territorios azuis
       Interpretado como todos os territorios terem cor 'azul' e tropas > 0 */
    if (strcmp(missao, "Controlar todos os territorios azuis") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") != 0) return 0;
            if (mapa[i].tropas <= 0) return 0;
        }
        return 1;
    }

    /* Ter mais de 20 tropas no total */
    if (strcmp(missao, "Ter mais de 20 tropas no total") == 0) {
        int total = 0;
        for (int i = 0; i < tamanho; i++) total += mapa[i].tropas;
        return (total > 20) ? 1 : 0;
    }

    /* Dominar metade do mapa
       Interpretado como existir alguma cor que controle >= metade dos territórios */
    if (strcmp(missao, "Dominar metade do mapa") == 0) {
        /* conta ocorrências por cor simples (até 10 cores diferentes suportadas) */
        char cores[10][12];
        int cont[10];
        int coresCount = 0;

        for (int i = 0; i < 10; i++) cont[i] = 0;
        for (int i = 0; i < tamanho; i++) {
            int j;
            for (j = 0; j < coresCount; j++) {
                if (strcmp(mapa[i].cor, cores[j]) == 0) {
                    cont[j]++;
                    break;
                }
            }
            if (j == coresCount) {
                /* nova cor */
                strncpy(cores[coresCount], mapa[i].cor, sizeof(cores[0])-1);
                cores[coresCount][sizeof(cores[0])-1] = '\0';
                cont[coresCount] = 1;
                coresCount++;
                if (coresCount >= 10) break;
            }
        }
        for (int k = 0; k < coresCount; k++) {
            if (cont[k] * 2 >= tamanho) return 1; /* >= metade */
        }
        return 0;
    }

    /* Missão não reconhecida */
    return 0;
}

/* --------------------------------------------------------------
   atacar
   Simula um ataque usando rand() (1..6). Valida se é ataque contra inimigo.
   Se atacante ganhar: transfere a cor do atacante para defensor e move metade
   das tropas do atacante para o defensor. Se perder: atacante perde 1 tropa.
   -------------------------------------------------------------- */
void atacar(Territorio* atacante, Territorio* defensor) {
    if (!atacante || !defensor) return;

    /* validações: não atacar se mesmas cores (não faz sentido) e atacante sem tropas */
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        // ataque inválido: mesmo dono
        return;
    }
    if (atacante->tropas <= 0) {
        // sem tropas para atacar
        return;
    }

    int dadoAtq = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    if (dadoAtq > dadoDef) {
        /* atacante vence */
        /* quantidade a transferir: metade das tropas do atacante (inteiro) */
        int transfer = atacante->tropas / 2;
        if (transfer < 1) transfer = 1; /* garante transferência mínima */
        /* atualiza defensor */
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = transfer;
        /* atacante perde as tropas transferidas */
        atacante->tropas -= transfer;
        if (atacante->tropas < 0) atacante->tropas = 0;
    } else {
        /* defensor vence ou empata -> atacante perde 1 tropa */
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

/* --------------------------------------------------------------
   exibirMapa
   Mostra nome, cor e tropas de cada território.
   -------------------------------------------------------------- */
void exibirMapa(Territorio* mapa, int tamanho) {
    if (!mapa || tamanho <= 0) return;
    printf("Mapa (territorio - cor - tropas):\n");
    for (int i = 0; i < tamanho; i++) {
        printf("  %s - %s - %d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

/* --------------------------------------------------------------
   liberarMemoria
   Libera memória alocada dinamicamente (missão e mapa).
   -------------------------------------------------------------- */
void liberarMemoria(char* missaoJogador, Territorio* mapa) {
    if (missaoJogador) free(missaoJogador);
    if (mapa) free(mapa);
}