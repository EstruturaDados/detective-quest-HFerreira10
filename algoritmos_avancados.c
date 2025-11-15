#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Sala {
    char nome[50];         
    struct Sala *esquerda; 
    struct Sala *direita;  
} Sala;

Sala* criarSala(const char *nome) {    
    Sala *nova_sala = (Sala *)malloc(sizeof(Sala));
    
    if (nova_sala == NULL) {
        perror("Erro ao alocar memória para a sala");
        exit(EXIT_FAILURE);
    }

    strncpy(nova_sala->nome, nome, sizeof(nova_sala->nome) - 1);
    nova_sala->nome[sizeof(nova_sala->nome) - 1] = '\0';
    
    nova_sala->esquerda = NULL;
    nova_sala->direita = NULL;
    
    return nova_sala;
}

Sala* montarMapa() {
    Sala *hall = criarSala("Hall de Entrada");

    Sala *sala_estar = criarSala("Sala de Estar");
    Sala *biblioteca = criarSala("Biblioteca");
    hall->esquerda = sala_estar;
    hall->direita = biblioteca;

    Sala *jardim = criarSala("Jardim de Inverno");
    Sala *cozinha = criarSala("Cozinha");
    Sala *quarto_principal = criarSala("Quarto Principal");
    sala_estar->esquerda = jardim;
    sala_estar->direita = cozinha;
    biblioteca->esquerda = quarto_principal;

    Sala *despensa = criarSala("Despensa");
    cozinha->esquerda = despensa; 
    return hall;
}

void liberarMapa(Sala *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarMapa(raiz->esquerda);
    liberarMapa(raiz->direita);
    free(raiz);
}

void explorarSalas(Sala *raiz) {
    Sala *sala_atual = raiz;
    char escolha;

    printf("\n--- Detective Quest ---\n");
    printf("Você está no **%s**. Onde deseja ir?\n", sala_atual->nome);

    while (sala_atual != NULL) {
        bool tem_caminho = false;
        printf("\nCaminhos disponíveis:\n");
        if (sala_atual->esquerda != NULL) {
            printf("  [e] Esquerda (-> %s)\n", sala_atual->esquerda->nome);
            tem_caminho = true;
        }
        if (sala_atual->direita != NULL) {
            printf("  [d] Direita (-> %s)\n", sala_atual->direita->nome);
            tem_caminho = true;
        }

        if (!tem_caminho) {
            printf("\n Você alcançou o **%s**.\n", sala_atual->nome);
            printf("Este cômodo não tem mais caminhos (nó-folha). Fim da exploração.\n");
            break;
        }
        
        printf("  [s] Sair do Jogo\n");

        printf("Escolha (e/d/s): ");
        if (scanf(" %c", &escolha) != 1) {
            while(getchar() != '\n'); 
            continue; 
        }

        Sala *proxima_sala = NULL;
        
        if (escolha == 'e' || escolha == 'E') {
            proxima_sala = sala_atual->esquerda;
            if (proxima_sala == NULL) {
                printf(" Caminho para a esquerda bloqueado/inexistente. Tente outra direção.\n");
            }
        } else if (escolha == 'd' || escolha == 'D') {
            proxima_sala = sala_atual->direita;
            if (proxima_sala == NULL) {
                printf(" Caminho para a direita bloqueado/inexistente. Tente outra direção.\n");
            }
        } else if (escolha == 's' || escolha == 'S') {
            printf("\n Exploração encerrada pelo jogador.\n");
            break;
        } else {
            printf(" Escolha inválida. Use 'e' (esquerda), 'd' (direita) ou 's' (sair).\n");
        }

        if (proxima_sala != NULL) {
            sala_atual = proxima_sala;
            printf("\n-> Você entrou no **%s**.\n", sala_atual->nome);
        }
    }
}

int main() {
    Sala *hall_de_entrada = montarMapa();

    if (hall_de_entrada != NULL) {
        explorarSalas(hall_de_entrada);
    } else {
        printf("Erro: Não foi possível montar o mapa da mansão.\n");
    }

    liberarMapa(hall_de_entrada);

    return 0;
}
