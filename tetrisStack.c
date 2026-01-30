#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

// Variáveis globais
char tipos[4] = {'I', 'O', 'T', 'L'}; // Tipos de peças
int contadorId = 0;

// Struct das peças
typedef struct {
    char nome;
    int id;
} Peca;

// Struct da fila
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// ====================================
//         Funções da fila
// ====================================

// Inicializar a fila com 0 como padrão
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Inserir Peça na fila
void inserirNovaPeca(Fila *f, Peca p) {
    if(filaCheia(f)) {
        printf("\nErro, fila cheia!\n");
        return;
    }

    f->itens[f->fim] = p; // Insere a peça no fim da fila
    f->fim = (f->fim + 1) % MAX; // Lógica circular, atualiza o fim da fila
    f->total++; // Incrementa em 1 o tamanho da fila
}

// Remover (Jogar) Peça na fila
void jogarPeca(Fila *f, Peca *pJogada) {
    if(filaVazia(f)) {
        printf("\nErro, fila vazia!\n");
        return;
    }

    *pJogada = f->itens[f->inicio]; // Remove a peça do ínicio da fila (Jogada)
    f->inicio = (f->inicio + 1) % MAX; // Lógica circular, atualiza o inicio da fila
    f->total--; // Decrementa em 1 o tamanho da fila

    printf("\nPeça Jogada -> [%c, %d]\n", pJogada->nome, pJogada->id);


}

// Função para mostra a fila de peças
void mostrarFilaPeca(Fila *f) {
    printf("\n--- FILA DE PEÇAS ---\n");

    for(int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c, %d]", f->itens[idx].nome, f->itens[idx].id);
    }

    printf("\n");
}

// ====================================
//         Funções auxiliares
// ====================================

// Função para gerar peças automaticamente
void gerarPeca(char t[], int *idUnico, Peca *p) {
    int indiceAleatorio = rand() % 4; // Gera um número aleatório entre 0 e 3

    p->nome = t[indiceAleatorio];
    p->id = *idUnico;
    (*idUnico)++;
}

void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// FUNÇÃO PRINCIPAL (MAIN)

int main() {
    srand(time(NULL)); // Semeia o gerador de números aleátórios

    Fila f; // Variável para armazenar a fila
    Peca p; // Variável para armazenar a peça gerada pela função gerar peça
    Peca jogada; // Armazena a peça que foi removida(jogada).
    int opcaoMenu = -1;

    inicializarFila(&f);
    
    // Este loop serve para preencher a fila com as primeiras peças do jogo
    for(int i = 0; i < MAX; i++) {
        gerarPeca(tipos, &contadorId, &p);
        inserirNovaPeca(&f, p);
    }


    do {
    mostrarFilaPeca(&f);
    printf("\n====== MENU ======\n");
    printf("1. Jogar peça\n");
    printf("2. Inserir nova peça\n");
    printf("0. Sair\n");
    printf("Escolha o seu movimento: ");
    scanf("%d", &opcaoMenu);
    limparBuffer();

    switch(opcaoMenu) {
        case 1:
            jogarPeca(&f, &jogada);
            break;
        
        case 2:
            gerarPeca(tipos, &contadorId, &p);
            inserirNovaPeca(&f, p);
            break;
        case 0:
            printf("Saindo...\n");
    }
    } while(opcaoMenu != 0);


    return 0;
}