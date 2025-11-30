#include <stdio.h>
#include <stdlib.h> // Para a função rand()
#include <string.h> // Para funções de string, embora não estritamente necessário aqui

// Define o tamanho máximo da fila de peças futuras.
#define TAMANHO_FILA 5

// -----------------------------------------------------------
// Definição da Struct Peca
// Representa uma peça do jogo com seu tipo e um ID único.
// -----------------------------------------------------------
typedef struct {
    char nome;  // Tipo da peça ('I', 'O', 'T', 'L', 'S', 'Z', 'J')
    int id;     // Identificador único da peça
} Peca;

// -----------------------------------------------------------
// Variáveis Globais para Controle da Fila
// -----------------------------------------------------------
Peca filaPecas[TAMANHO_FILA]; // O array que armazena as peças.
int frente = -1;             // Indica o índice da primeira peça da fila (dequeue).
int tras = -1;               // Indica o índice da última peça da fila (enqueue).
int proximoId = 1;           // Contador para gerar IDs únicos para cada nova peça.

// -----------------------------------------------------------
// Protótipos das Funções
// -----------------------------------------------------------
int filaVazia();
int filaCheia();
void inicializarFila();
Peca gerarPeca();
void enqueue(Peca novaPeca);
Peca dequeue();
void visualizarFila();

// -----------------------------------------------------------
// FUNÇÕES DE VALIDAÇÃO
// -----------------------------------------------------------

// Verifica se a fila está vazia.
// A fila está vazia se FRENTE for -1.
int filaVazia() {
    return (frente == -1);
}

// Verifica se a fila está cheia.
// A fila circular está cheia se TRAS + 1 for igual à FRENTE (circularmente).
int filaCheia() {
    return (frente == (tras + 1) % TAMANHO_FILA);
}

// -----------------------------------------------------------
// FUNÇÕES DE MANIPULAÇÃO DA FILA
// -----------------------------------------------------------

// Inicializa a fila preenchendo-a com o número máximo de peças iniciais.
void inicializarFila() {
    printf("\n--- Inicializando Fila de Peças Futuras ---\n");
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca p = gerarPeca();
        enqueue(p); // Adiciona a peça à fila.
    }
    printf("Fila inicializada com %d peças.\n", TAMANHO_FILA);
}

// Gera uma nova peça com um tipo aleatório e um ID único.
Peca gerarPeca() {
    Peca p;
    // Tipos de peças: T, O, I, L (tipos simplificados do Tetris clássico)
    char tipos[] = {'T', 'O', 'I', 'L', 'S', 'Z', 'J'}; 
    int numTipos = 7; 
    
    // Gera um índice aleatório entre 0 e numTipos-1
    int indiceAleatorio = rand() % numTipos;
    
    p.nome = tipos[indiceAleatorio];
    p.id = proximoId++; // Atribui o ID atual e incrementa para o próximo.
    
    return p;
}

// Insere uma nova peça no final da fila (enqueue).
void enqueue(Peca novaPeca) {
    if (filaCheia()) {
        printf("\nERRO: A fila de peças está cheia. Não é possível inserir mais.\n");
        return;
    }

    if (filaVazia()) {
        // Se for a primeira peça, a frente e a traseira apontam para o primeiro índice.
        frente = 0;
        tras = 0;
    } else {
        // Incrementa o índice da traseira de forma circular.
        tras = (tras + 1) % TAMANHO_FILA;
    }
    
    // Armazena a nova peça no índice da traseira.
    filaPecas[tras] = novaPeca;
    printf("\nSUCESSO: Peça %c (ID %d) inserida no final da fila.\n", novaPeca.nome, novaPeca.id);
}

// Remove e retorna a peça da frente da fila (dequeue).
Peca dequeue() {
    Peca pecaRemovida = {'\0', -1}; // Peça nula para erro.

    if (filaVazia()) {
        printf("\nERRO: A fila de peças está vazia! Não há peças para jogar.\n");
        return pecaRemovida;
    }
    
    // Pega a peça na frente.
    pecaRemovida = filaPecas[frente];
    
    if (frente == tras) {
        // Se havia apenas um elemento, a fila volta ao estado "vazia".
        frente = -1;
        tras = -1;
    } else {
        // Incrementa o índice da frente de forma circular.
        frente = (frente + 1) % TAMANHO_FILA;
    }

    printf("\nSUCESSO: Peça %c (ID %d) jogada (removida da frente).\n", pecaRemovida.nome, pecaRemovida.id);
    return pecaRemovida;
}

// Exibe o estado atual da fila de peças.
void visualizarFila() {
    printf("\n====================================\n");
    printf("        ESTADO ATUAL DA FILA        \n");
    printf("====================================\n");

    if (filaVazia()) {
        printf("Fila de peças está vazia.\n");
        printf("====================================\n");
        return;
    }

    printf("Fila de peças: [");
    
    int i = frente;
    // O laço percorre a fila a partir da 'frente' até a 'traseira' circularmente.
    do {
        printf(" %c ID %d ", filaPecas[i].nome, filaPecas[i].id);
        if (i != tras) {
            printf("] ["); // Separador entre as peças.
        }
        i = (i + 1) % TAMANHO_FILA;
    } while (i != (tras + 1) % TAMANHO_FILA);

    printf("]\n");
    printf("Tamanho: %d | Frente: %d | Traseira: %d\n", TAMANHO_FILA, frente, tras);
    printf("====================================\n");
}


// -----------------------------------------------------------
// FUNÇÃO PRINCIPAL
// -----------------------------------------------------------
int main() {
    int opcao;

    // 1. Inicializa a fila antes de entrar no menu.
    inicializarFila();
    visualizarFila();

    do {
        // Menu de opções
        printf("\n--- Opções de Ação ---\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        
        // Lê a opção do usuário.
        if (scanf("%d", &opcao) != 1) { 
             // Trata entrada inválida (não numérica)
             int c;
             while ((c = getchar()) != '\n' && c != EOF);
             opcao = -1; 
        }

        switch (opcao) {
            case 1:
                // Joga uma peça: remove da frente.
                dequeue();
                visualizarFila();
                break;

            case 2:
                // Insere uma nova peça: adiciona ao final e gera uma peça.
                Peca nova = gerarPeca();
                enqueue(nova);
                visualizarFila();
                break;

            case 0:
                printf("\nSaindo do simulador Tetris Stack...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}