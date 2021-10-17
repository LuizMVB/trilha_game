#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* CONSTANTES DE CONFIGURAÇÃO */
#define CASTLE_LAYOUT_PATH "tela/layout/castle.txt"
#define OPCAO_INVALIDA_PATH "tela/layout/opcao_invalida.txt"
#define TABULEIRO_PATH "tela/layout/tabuleiro.txt"
#define ESCOLHA_PADRAO_PATH "tela/layout/escolha_padrao.txt"
#define ARQUIVO_RENDERING_PATH "tela/rendering.txt"
#define ERRO_ABERTURA_ARQUIVO "\nERRO: O SEGUINTE ARQUIVO NÃO PODE SER ABERTO\n"
#define WIDTH_TOTAL_RENDERIZACAO 1000

/* CONSTANTES DO SISTEMA */
#define N_TOTAL_DE_PECAS 24
#define MSG_OPCAO_INVALIDA "Opção inválida, pressione ENTER para escolher novamente"

void verificar_abertura_arquivo(FILE *file){
    if(file == NULL){
        printf(ERRO_ABERTURA_ARQUIVO);
        exit(1);
    }
}

void criar_arquivo_rendering(){
    FILE *rendering = fopen(ARQUIVO_RENDERING_PATH, "w");
    verificar_abertura_arquivo(rendering);
    fclose(rendering);
}

void copiar_conteudo_arquivo(FILE *de, FILE *para){
    char leitor[WIDTH_TOTAL_RENDERIZACAO];
    verificar_abertura_arquivo(de);
    verificar_abertura_arquivo(para);
    while(fgets(leitor, WIDTH_TOTAL_RENDERIZACAO, de) != NULL)
    fputs(leitor, para);
}

void acrescentar_conteudo_arquivo(FILE *de, FILE *para){
    char leitor[WIDTH_TOTAL_RENDERIZACAO];
    verificar_abertura_arquivo(de);
    verificar_abertura_arquivo(para);
    while(fgets(leitor, WIDTH_TOTAL_RENDERIZACAO, de) != NULL)
    fputs(leitor, para);
}

void ler_conteudo_arquivo(char *path_arquivo){
    char linha[WIDTH_TOTAL_RENDERIZACAO];
    FILE *arquivo = fopen(path_arquivo, "r");
    verificar_abertura_arquivo(arquivo);
    while(fgets(linha, WIDTH_TOTAL_RENDERIZACAO, arquivo) != NULL){
        printf("%s", linha);
    }
    fclose(arquivo);
}

void renderizar_tela(){
    system("clear");
    ler_conteudo_arquivo(ARQUIVO_RENDERING_PATH);
}

void acrescentar_na_tela(char *layout_path){
    FILE *layout = fopen(layout_path, "r");
    FILE *rendering = fopen(ARQUIVO_RENDERING_PATH, "a");
    acrescentar_conteudo_arquivo(layout, rendering);
    fclose(layout);
    fclose(rendering);
}

void construir_tela_menu_principal(){
    FILE *layout = fopen(CASTLE_LAYOUT_PATH, "r");
    FILE *rendering = fopen(ARQUIVO_RENDERING_PATH, "w");
    copiar_conteudo_arquivo(layout, rendering);
    fclose(layout);
    fclose(rendering);
}

void construir_tela_regras(){
    printf("Construindo tela de regras");
}

void construir_tabuleiro(){
    FILE *layout = fopen(TABULEIRO_PATH, "r");
    FILE *rendering = fopen(ARQUIVO_RENDERING_PATH, "w");
    copiar_conteudo_arquivo(layout, rendering);
    fclose(layout);
    fclose(rendering);
}

void fase_1(int jogador_da_vez){
    int pecas_adicionadas = 0;
    construir_tabuleiro();
    renderizar_tela();
    while(pecas_adicionadas != N_TOTAL_DE_PECAS){
        if(jogador_da_vez == 1){
            /*faça alguma coisa*/
            jogador_da_vez = 2;
        }else if(jogador_da_vez == 2){
            /*faça alguma coisa*/
            jogador_da_vez = 1;
        }
        /*pecas_adicionadas++;*/
    }
}

int main(void) {

    /**
     * A representação do tabuleiro se dá por meio de matrizes
     * cada matriz representa uma parte da trilha desenhada no
     * tabuleiro.
     * externa: última camada de trilhas
     *      *----*----*
     *      |         |
     *      |         |
     *      *         *
     *      |         |
     *      |         |
     *      *----*----*
     * central: segunda camada de trilhas
     *      *----*----*
     *      | *--*--* |
     *      | |     | |
     *      * *     * *
     *      | |     | |
     *      | *--*--* |
     *      *----*----*
     * interna: primeira camada de trilhas
     *      *----*----*
     *      | *--*--* |
     *      | | *** | |
     *      * * * * * *
     *      | | *** | |
     *      | *--*--* |
     *      *----*----*
     * O tabuleiro deverá ser preenchido com
     * 0 (zeros): para casas vazias;
     * 1 (um): para casas ocupadas pelo primeiro jogador
     * 2 (dois): para casas ocupadas pelo segundo jogador
     */
    int trilha[6][6];

    int n_pecas_jogador_1 = N_TOTAL_DE_PECAS / 2;
    int n_pecas_jogador_2 = N_TOTAL_DE_PECAS / 2;

    int jogo_rodando = 1;
    int jogador_da_vez = 1;
    int opcao;

    /**
     * O arquivo "rendering.txt" é referente ao conteúdo que
     * será "renderizado" para o usuário durante o jogo
     */
    criar_arquivo_rendering();

    while(jogo_rodando){
        construir_tela_menu_principal();
        acrescentar_na_tela(ESCOLHA_PADRAO_PATH);
        renderizar_tela();
        while(1){
            scanf("%d", &opcao);
            if(opcao == 1){
                fase_1(jogador_da_vez);
                break;
            }else if(opcao == 2){
                construir_tela_regras();
                renderizar_tela();
                break;
            }
            else{
                construir_tela_menu_principal();
                acrescentar_na_tela(OPCAO_INVALIDA_PATH);
                acrescentar_na_tela(ESCOLHA_PADRAO_PATH);
                renderizar_tela();
            }
        }
        printf("saindo");
        printf("\n");
    }

    return 0;
}