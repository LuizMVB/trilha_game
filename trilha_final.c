#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* CONSTANTES DE CONFIGURAÇÃO */
#define CASTLE_LAYOUT_PATH "tela/layout/castle.txt"
#define OPCAO_INVALIDA_PATH "tela/layout/opcao_invalida.txt"
#define TABULEIRO_PATH "tela/layout/tabuleiro.txt"
#define ESCOLHA_PADRAO_PATH "tela/layout/escolha_padrao.txt"
#define VEZ_DO_JOGADOR_PATH "tela/layout/vez_do_jogador.txt"
#define ARQUIVO_RENDERING_PATH "tela/rendering.txt"
#define ARQUIVO_TEMPORARIO_PATH "tela/tmp.txt"
#define ERRO_ABERTURA_ARQUIVO "\nERRO: O SEGUINTE ARQUIVO NÃO PODE SER ABERTO\n"
#define WIDTH_TOTAL_RENDERIZACAO 1000

/* CONSTANTES DO SISTEMA */
#define N_TOTAL_DE_PECAS 24
#define NM_JOGADOR "JOGADOR @"
#define NM_JOGADOR_1 "CORAÇÃO"
#define NM_JOGADOR_2 "MÚSICA"

void verificar_abertura_arquivo(FILE *file){
    if(file == NULL){
        printf(ERRO_ABERTURA_ARQUIVO);
        exit(1);
    }
}

/**
* O arquivo "rendering.txt" é referente ao conteúdo que
* será "renderizado" para o usuário durante o jogo
*/
void criar_arquivo_rendering(){
    FILE *rendering = fopen(ARQUIVO_RENDERING_PATH, "w");
    verificar_abertura_arquivo(rendering);
    fclose(rendering);
}

void alterar_conteudo_arquivo(FILE *de, FILE *para){
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
    alterar_conteudo_arquivo(layout, rendering);
    fclose(layout);
    fclose(rendering);
}

void construir_tela_menu_principal(){
    FILE *layout = fopen(CASTLE_LAYOUT_PATH, "r");
    FILE *rendering = fopen(ARQUIVO_RENDERING_PATH, "w");
    alterar_conteudo_arquivo(layout, rendering);
    fclose(layout);
    fclose(rendering);
}

void construir_tela_regras(){
    printf("Construindo tela de regras");
}

void construir_tela_tabuleiro(){
    FILE *layout = fopen(TABULEIRO_PATH, "r");
    FILE *rendering = fopen(ARQUIVO_RENDERING_PATH, "w");
    alterar_conteudo_arquivo(layout, rendering);
    fclose(layout);
    fclose(rendering);
}
/*
char * formatar_string(char * string, char * substring, char caracter_substituido){
    int posicao;
    int tamanho_string = strlen(string);
    int tamanho_sbstring = strlen(substring);
    int i, j;
    int tamanho_completo = (strlen(string) + strlen(substring)) - 1;
    char string_completa[tamanho_completo];
    int posicao_final_da_substring;
    for(i=0; i<tamanho_string; i++){
        if(string[i] == caracter_substituido){
            posicao = i;
            break;
        }
    }
    posicao_final_da_substring = posicao + strlen(substring) - 1;
    for(i=0; i<tamanho_string; i++){
        string_completa[i] = string[i];
    }
    for(i=posicao; i<tamanho_sbstring+posicao; i++){
        string_completa[i] = substring[i-posicao];
    }
    j=0;
    for(i=tamanho_completo-1; i>posicao_final_da_substring; i--){
        string_completa[i] = string[tamanho_string-j-1];
        j++;
    }
    return string_completa;
}

void inserir_string_na_tela(char *inserido, char caracter_substituido){
    char linha[WIDTH_TOTAL_RENDERIZACAO];
    FILE *arquivo = fopen(ARQUIVO_RENDERING_PATH, "r+");
    FILE *arquivo_temporario = fopen(ARQUIVO_TEMPORARIO_PATH, "a+");
    verificar_abertura_arquivo(arquivo);
    while(fgets(linha, WIDTH_TOTAL_RENDERIZACAO, arquivo) != NULL){
        linha = formatar_string(linha, inserido, caracter_substituido);
        fputs(linha, arquivo_temporario);
    }
    alterar_conteudo_arquivo(arquivo_temporario, arquivo);
    fclose(arquivo);
    fclose(arquivo_temporario);
}
*/
void fase_1(int jogador_da_vez){
    char *msg_jogador;
    int pecas_adicionadas = 0;
    //int escolha;
    construir_tela_tabuleiro();
    acrescentar_na_tela(VEZ_DO_JOGADOR_PATH);
    while(pecas_adicionadas != N_TOTAL_DE_PECAS){
        if(jogador_da_vez == 1){
            msg_jogador = formatar_string(NM_JOGADOR, NM_JOGADOR_1, '@');
            printf("MSG_JOGADOR_DA_VEZ = %s", msg_jogador);
            //scanf("%d", &escolha);
            jogador_da_vez = 2;
        }else if(jogador_da_vez == 2){
            //msg_jogador = formatar_string(NM_JOGADOR, NM_JOGADOR_2, '@');
            jogador_da_vez = 1;
        }
        inserir_string_na_tela(msg_jogador, '@');
        /*pecas_adicionadas++;*/
        /*renderizar_tela();*/
    }
}

int main(void) {

    int n_pecas_jogador_1 = N_TOTAL_DE_PECAS / 2;
    int n_pecas_jogador_2 = N_TOTAL_DE_PECAS / 2;

    int jogo_rodando = 1;
    int jogador_da_vez = 1;
    int opcao;

    char trilha[7][7] = {
                {' ', '#', '#', ' ', '#', '#', ' '},
                {'#', ' ', '#', ' ', '#', ' ', '#'},
                {'#', '#', ' ', ' ', ' ', '#', '#'},
                {' ', ' ', ' ', '#', ' ', ' ', ' '},
                {'#', '#', ' ', ' ', ' ', '#', '#'},
                {'#', ' ', '#', ' ', '#', ' ', '#'},
                {' ', '#', '#', ' ', '#', '#', ' '}
            };

    int espelho_trilha[24] = [648, 668, 690, 994, 1007,
                              1022, 1454, 1459, 1464, 1778,
                              1785, 1793, 1803, 1813, 1820,
                              2132, 2137, 2142, 2576, 2589,
                              2604, 2908, 2928, 2950];

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
                /* limpando o buffer */
                while ((clear_buffer = getchar()) != '\n' && clear_buffer != EOF){}
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