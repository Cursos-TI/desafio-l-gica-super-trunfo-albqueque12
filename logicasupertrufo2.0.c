#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para representar um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para atribuir uma missão aleatória ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Função simples para verificar se a missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Lógica de verificação básica - pode ser expandida conforme necessário
    if (strstr(missao, "Conquistar 3 territórios seguidos")) {
        // Verifica se o jogador tem 3 territórios consecutivos
        for (int i = 0; i < tamanho - 2; i++) {
            if (mapa[i].cor[0] != '\0' && 
                strcmp(mapa[i].cor, mapa[i+1].cor) == 0 && 
                strcmp(mapa[i+1].cor, mapa[i+2].cor) == 0) {
                return 1;
            }
        }
    } else if (strstr(missao, "Eliminar todas as tropas da cor vermelha")) {
        // Verifica se não há mais tropas vermelhas
        int vermelhas = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 0) {
                vermelhas++;
            }
        }
        return vermelhas == 0;
    } else if (strstr(missao, "Controlar 5 territórios")) {
        // Verifica se controla pelo menos 5 territórios
        int controlados = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].cor[0] != '\0') {
                controlados++;
            }
        }
        return controlados >= 5;
    }
    // Adicione mais condições para outras missões aqui
    return 0;
}

// Função para simular um ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n%s (%s) atacando %s (%s)\n", 
           atacante->nome, atacante->cor, 
           defensor->nome, defensor->cor);
    
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    
    printf("Dados: Atacante %d x Defensor %d\n", dadoAtacante, dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");
        // Transferir cor e metade das tropas
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= atacante->tropas / 2;
    } else {
        printf("Defensor venceu!\n");
        // Atacante perde uma tropa
        atacante->tropas--;
    }
}

// Função para exibir o mapa
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%s - Cor: %s, Tropas: %d\n", 
               mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função para liberar memória alocada
void liberarMemoria(Territorio* mapa, char** missoesJogadores, int numJogadores) {
    free(mapa);
    for (int i = 0; i < numJogadores; i++) {
        free(missoesJogadores[i]);
    }
    free(missoesJogadores);
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    
    // Vetor de missões disponíveis
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar 5 territórios",
        "Conquistar todos os territórios da Ásia",
        "Destruir todas as tropas do jogador azul"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);
    
    // Número de jogadores e territórios
    int numJogadores = 2;
    int numTerritorios = 10;
    
    // Alocar memória para as missões dos jogadores
    char** missoesJogadores = malloc(numJogadores * sizeof(char*));
    for (int i = 0; i < numJogadores; i++) {
        missoesJogadores[i] = malloc(100 * sizeof(char));
        atribuirMissao(missoesJogadores[i], missoes, totalMissoes);
        printf("Jogador %d: Missao atribuida - %s\n", i+1, missoesJogadores[i]);
    }
    
    // Inicializar o mapa
    Territorio* mapa = calloc(numTerritorios, sizeof(Territorio));
    for (int i = 0; i < numTerritorios; i++) {
        sprintf(mapa[i].nome, "Territorio_%d", i+1);
        // Distribuir cores aleatoriamente
        int cor = rand() % 3;
        if (cor == 0) strcpy(mapa[i].cor, "vermelho");
        else if (cor == 1) strcpy(mapa[i].cor, "azul");
        else strcpy(mapa[i].cor, "verde");
        
        mapa[i].tropas = rand() % 5 + 1; // 1-5 tropas
    }
    
    exibirMapa(mapa, numTerritorios);
    
    // Simulação do jogo
    int turno = 1;
    int vencedor = -1;
    
    while (vencedor == -1) {
        printf("\n=== TURNO %d ===\n", turno);
        
        for (int jogador = 0; jogador < numJogadores && vencedor == -1; jogador++) {
            printf("\nJogador %d (%s) atacando...\n", jogador+1, 
                   jogador == 0 ? "vermelho" : "azul");
            
            // Escolher territórios para ataque (simplificado)
            int atacanteIdx = rand() % numTerritorios;
            int defensorIdx = rand() % numTerritorios;
            
            // Garantir que são territórios diferentes e cores diferentes
            while (defensorIdx == atacanteIdx || 
                   strcmp(mapa[atacanteIdx].cor, mapa[defensorIdx].cor) == 0) {
                defensorIdx = rand() % numTerritorios;
            }
            
            atacar(&mapa[atacanteIdx], &mapa[defensorIdx]);
            exibirMapa(mapa, numTerritorios);
            
            // Verificar se a missão foi cumprida
            if (verificarMissao(missoesJogadores[jogador], mapa, numTerritorios)) {
                printf("\nJogador %d cumpriu a missao: %s\n", jogador+1, missoesJogadores[jogador]);
                vencedor = jogador;
            }
        }
        
        turno++;
        if (turno > 10) break; // Limite de turnos para o exemplo
    }
    
    if (vencedor != -1) {
        printf("\nJogador %d venceu o jogo!\n", vencedor+1);
    } else {
        printf("\nO jogo terminou sem vencedor.\n");
    }
    
    // Liberar memória alocada
    liberarMemoria(mapa, missoesJogadores, numJogadores);
    
    return 0;
}