#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

// -lwinmm
// < = 75, ^ = 72, > = 77, v = 80


/* Dada uma string e o seu comprimento, 
essa função imprime a string com background 
branco e texto preto, que é o inverso do padrão.*/
void highlight(char texto[], int n) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
	printf("%.*s", n, texto);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

/*O tabuleiro é dividido em 3 camadas, sendo a 
terceira camada a mais interna. Os pontos de cada 
camada estão numerados de 1 a 9, pulando o 5, já 
que não existe ponto no meio. Usando essa variáveis, 
essa função imprime o tabuleiro, usando o highlight() 
para simular um cursor, que indica qual casa está 
selecionada no momento.*/
void printTabuleiro(int camada, int ponto, int peca_1[], int peca_2[], int distancia[][9], char tabuleiro[]) {
	char str[2] = "\0";
	str[0] = tabuleiro[distancia[camada][ponto]];
	Sleep(4);

	printf("%.*s", distancia[camada][ponto], tabuleiro);
	highlight(str, 1);
	printf("%s", tabuleiro + distancia[camada][ponto] + 1);
	printf("%d) %d Pecas                Jogador |2|: (%d) %d Pecas\n", peca_1[0], peca_1[1], peca_2[0], peca_2[1]);
}

/*Dados uma string e seu comprimento, essa função 
simplesmente imprime um texto qualquer com pausas 
intermitentes de tempo*/
void slowPrint(char texto[], int length) {
	for (int i = 0; i < length; i++) {
		if (texto[i] == 0) {
			return;
		}
		printf("%c", texto[i]);
		if (texto[i] == ' ') {
			continue;
		}
		Sleep(1);
	}
}


int main(void) {
	char character, path[200];
	GetCurrentDirectory(200, path);
	int direct, length;
	int key = 0;
	int peca_1[] = {0, 9};
	int peca_2[] = {0, 9};
	char castle[4713] = {0};
	char tabuleiro[2300] = {0};

	strcpy(castle, "\n                    __      __                                                                                      __      __\n"
"              ||  ||  ||  ||  ||  ||                                                                          ||  ||  ||  ||  ||  ||\n"
"              ||__||  ||__||  ||__||                                                                          ||__||  ||__||  ||__||\n"
"              \\\\  \'        \'      //                                                                          \\\\      \'   \'      \'//\n"
"               \\\\      \'     \'   //                                                                            \\\\ \'          \'   //\n"
"                \\\\   \'   \'      //                                                                              \\\\     \'        //\n"
"                 | ; \'          |================================================================================| ;  \'      \'  |\n"
"                 | ;    \'       |                      ___                                                       | ;       \'    |\n"
"                 | ;   \'    \'   |        ========    ||   \\      ||      ||       ||    ||     //\\\\              | ;     \'      |\n"
"                 | ; \'    \'     |           ||       ||___|      ||      ||       ||====||    //  \\\\             | ; \'        \' |\n"
"                 | ;            |           ||       ||\\\\        ||      ||       ||    ||   //====\\\\            | ;        \'   |\n"
"                 | ;          \' |           ||       || \\\\       ||      ||====   ||    ||  //      \\\\           | ;     \'    \' |\n"
"                 | ; \'       \'  |                                                                                | ;   \'        |\n"
"                 | ;    \'   \'   |                                                                                | ;        \'   |\n"
"                 | ;            |                                                                                | ;  \'         |\n"
"                 | ;   \'  \'     |                                                                                | ;      \'     |\n"
"                 | ;         \'  |                                //=============\\\\                               | ;    \'     \' |\n"
"                 | ;  \'         |                               //               \\\\                              | ; \'      \'   |\n"
"                 | ;     \'      |                              //                 \\\\                             | ;      \'     |\n"  
"                 | ; \'        \' |                              ||                 ||                             | ;   \'       \'|\n"
"                 | ;  \'         |                              ||      JOGAR      ||                             | ;         \'  |\n"
"                 | ;       \'    |                              ||                 ||                             | ; \'      \'   |\n"
"                 | ;    \'       |                              ||                 ||                             | ;     \'      |\n"
"                 | ;  \'   \'   \' |                              ||                 ||                             | ;   \'      \' |\n"
"                 | ;            |                              ||      REGRAS     ||                             | ;        \'   |\n"
"                 | ;  \' \'   \'   |                              ||                 ||                             | ; \'    \'     |\n"
"                 | ;\' \'       \' |                              ||                 ||                             | ;    \'     \' |\n"
"                 | ; \'    \' \'  \'|                              ||                 ||                             | ;  \'   \'  \' \'|\n"
"=========================================================================================================================================================\n"
" *      ;    \'       ;                 \'      *                   ;         ;           \'  *            *                 ;     \'              *        \'\n"
"     *         \'   ;           *        ;   *  \'             * ;  \'        ;     *   ;     *             \'       ;                 *       ;        ;\n"
"  \'     ;   *         *     \'     ;   *            ;    \'            *      \'                 ;      *       \'         \'         *         \'    *    *\n"
" ;          ;       *           \'  ;     *           ; \'         *  ;     \'  *   ;    \'     *    ;     *     \'     *    ;    *   \'    \'   ;      *   \'\n"
"  \'    *  \'   *   ;   \'  *        *     \'  *   \'  ;   \'   ;     ;  *  \'    ;     *    ;   *    \'   ;   \';      *     ;   \'   *    *  ;   \'    *  ;   ;\n"
"   \"    ;   *   ; \"    \"  *   ;  \"   *   ;   *  ;   *   \"     ;    *   \"    *  \"   *    ;  \";      \"  *   ;   \" *        ;   *  \"    ;     \"    ;    *\n");


	strcpy(tabuleiro, "\n\n\n\n\n\n\n                            =======================================================\n"
"                            ||    _                   _                     _    ||\n"
"                            ||   |_|=================|_|===================|_|   ||\n"
"                            ||    |                   |                     |    ||\n"
"                            ||    |      _            |              _      |    ||\n"
"                            ||    |     |_|==========|_|============|_|     |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |      |       _    |    _         |      |    ||\n"
"                            ||    |      |      |_|==|_|==|_|        |      |    ||\n"
"                            ||    |      |       |         |         |      |    ||\n"
"                            ||    |      |       |         |         |      |    ||\n"
"                            ||   |_|====|_|=====|_|       |_|=======|_|====|_|   ||\n"
"                            ||    |      |       |         |         |      |    ||\n"
"                            ||    |      |       |    _    |         |      |    ||\n"
"                            ||    |      |      |_|==|_|==|_|        |      |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |     |_|==========|_|============|_|     |    ||\n"
"                            ||    |                   |                     |    ||\n"
"                            ||    |                   |                     |    ||\n"
"                            ||   |_|=================|_|===================|_|   ||\n"
"                            ||                                                   ||\n"
"                            =======================================================\n"
"\n                                                                          "
"\n                            Jogador |1|: (");

	PlaySound(TEXT(strcat(path, "\\sea-shanty-2.wav")), NULL, SND_ASYNC | SND_NODEFAULT | SND_LOOP | SND_FILENAME); /*Essa linha toca a música. Note que para que a música toque,
															  ela sempre tem que estar na mesma pasta que esse programa.*/
	system("cls");
	
	length = strlen(castle);
	// slowPrint(castle, length);

	int camada, ponto, jogador, remocao;
	camada = ponto = jogador = remocao = 0;
	int distancia[3][9] = {{209, 229, 251, 1049, 0, 1091, 1889, 1909, 1931}, {468, 481, 496, 1056, 0, 1084, 1644, 1657, 1672}, {812, 817, 822, 1064, 0, 1074, 1316, 1321, 1326}};
	/*distancia[][] se refere à lista de quantidade de caracteres antes de cada ponto, sendo a lista dividida em camadas, e depois em pontos.
	  Dessa forma, é possível usar o highlight para destacar apenas um ponto específico e nada mais.*/

	while (1) {
		Sleep(16);

		if (kbhit()) {
			direct = (int) getch();

			if (direct == 72) {
				system("cls");
				printf("%.2681s", castle);
				highlight(castle + 2681, 5);
				printf("%s", castle + 2686);
				key = 1;

			} else if (direct == 80) {
				system("cls");
				printf("%.3201s", castle);
				highlight(castle + 3201, 6);
				printf("%s", castle + 3207);
				key = 2;

			} else if (direct == 27) {
				return 0;

			} else if (direct == 13) {
				system("cls");

				if (key == 1) {
					printf("\n\n\n\n\n\n\n                            =======================================================\n"
"                            ||    _                   _                     _    ||\n"
"                            ||   |_|=================|_|===================|_|   ||\n"
"                            ||    |                   |                     |    ||\n"
"                            ||    |      _            |              _      |    ||\n"
"                            ||    |     |_|==========|_|============|_|     |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |      |       _    |    _         |      |    ||\n"
"                            ||    |      |      |_|==|_|==|_|        |      |    ||\n"
"                            ||    |      |       |         |         |      |    ||\n"
"                            ||    |      |       |         |         |      |    ||\n"
"                            ||   |_|====|_|=====|_|       |_|=======|_|====|_|   ||\n"
"                            ||    |      |       |         |         |      |    ||\n"
"                            ||    |      |       |    _    |         |      |    ||\n"
"                            ||    |      |      |_|==|_|==|_|        |      |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |     |_|==========|_|============|_|     |    ||\n"
"                            ||    |                   |                     |    ||\n"
"                            ||    |                   |                     |    ||\n"
"                            ||   |_|=================|_|===================|_|   ||\n"
"                            ||                                                   ||\n"
"                            =======================================================\n"
"\n                                                                          "
"\n                            Jogador |1|: (0) 9 Pecas                Jogador |2|: (0) 9 Pecas\n");

					while(1) {
						Sleep(16);

						if (kbhit()) {
							direct = (int) getch();

							if (direct == 72) {
								if (ponto != 7 && ponto > 2) {
									system("cls");
									ponto -= 3;
									printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);

								} else if (ponto == 7 && camada < 2) {
									system("cls");
									camada += 1;
									printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);

								} else if (ponto == 1 && camada > 0) {
									system("cls");
									camada -= 1;
									printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);
								}

							} else if (direct == 80) {
								if (ponto != 1 && ponto < 6) {
									system("cls");
									ponto += 3;
									printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);

								} else if (ponto == 1 && camada < 2) {
									system("cls");
									camada += 1;
									printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);

								} else if (ponto == 7 && camada > 0) {
									system("cls");
									camada -= 1;
									printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);
								}

							} else if (direct == 75) {
								if (ponto != 5 && ponto % 3 != 0) {
									system("cls");
									ponto -= 1;
									printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);

								} else if (ponto == 5 && camada < 2) {
									system("cls");
									camada += 1;
									printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);

								} else if (ponto == 3 && camada > 0) {
									system("cls");
									camada -= 1;
									printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);
								}

							} else if (direct == 77) {
								if (ponto != 3 && ponto % 3 != 2) {
									system("cls");
									ponto += 1;
									printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);

								} else if (ponto == 3 && camada < 2) {
									system("cls");
									camada += 1;
									printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);

								} else if (ponto == 5 && camada > 0) {
									system("cls");
									camada -= 1;
									printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);
								}

							} else if (direct == 13 && peca_2[1] > 0) {
								if (remocao > 0) {
									if (ponto == 1 || ponto == 7) {
										if (tabuleiro[distancia[camada][ponto+1]] == tabuleiro[distancia[camada][ponto]] && tabuleiro[distancia[camada][ponto-1]] == tabuleiro[distancia[camada][ponto]]) {
											if (remocao == 1) { 
												strcpy(tabuleiro + 2130,"                                      \n                            Jogador |1|: (");
											}
											remocao -= 1;
											continue;
										}

										if (tabuleiro[distancia[0][ponto]] == tabuleiro[distancia[1][ponto]] && tabuleiro[distancia[1][ponto]] == tabuleiro[distancia[2][ponto]]) {
											if (remocao == 1) { 
												strcpy(tabuleiro + 2130,"                                      \n                            Jogador |1|: (");
											}
											remocao -= 1;
											continue;
										}

									} else if (ponto == 3 || ponto == 5) {
										if (tabuleiro[distancia[camada][ponto+3]] == tabuleiro[distancia[camada][ponto]] && tabuleiro[distancia[camada][ponto-3]] == tabuleiro[distancia[camada][ponto]]) {
											if (remocao == 1) { 
												strcpy(tabuleiro + 2130,"                                      \n                            Jogador |1|: (");
											}
											remocao -= 1;
											continue;
										}

										if (tabuleiro[distancia[0][ponto]] == tabuleiro[distancia[1][ponto]] && tabuleiro[distancia[1][ponto]] == tabuleiro[distancia[2][ponto]]) {
											if (remocao == 1) { 
												strcpy(tabuleiro + 2130,"                                      \n                            Jogador |1|: (");
											}
											remocao -= 1;
											continue;
										}

									} else if (ponto == 0 || ponto == 2) {
										if (tabuleiro[distancia[camada][0]] == tabuleiro[distancia[camada][1]] && tabuleiro[distancia[camada][1]] == tabuleiro[distancia[camada][2]]) {
											if (remocao == 1) { 
												strcpy(tabuleiro + 2130,"                                      \n                            Jogador |1|: (");
											}
											remocao -= 1;
											continue;
										}

										if (tabuleiro[distancia[camada][ponto]] == tabuleiro[distancia[camada][ponto+3]] && tabuleiro[distancia[camada][ponto+3]] == tabuleiro[distancia[camada][ponto+6]]) {
											if (remocao == 1) { 
												strcpy(tabuleiro + 2130,"                                      \n                            Jogador |1|: (");
											}
											remocao -= 1;
											continue;
										}
									} else if (ponto == 6 || ponto == 8) {
										if (tabuleiro[distancia[camada][6]] == tabuleiro[distancia[camada][7]] && tabuleiro[distancia[camada][7]] == tabuleiro[distancia[camada][8]]) {
											if (remocao == 1) { 
												strcpy(tabuleiro + 2130,"                                      \n                            Jogador |1|: (");
											}
											remocao -= 1;
											continue;
										}

										if (tabuleiro[distancia[camada][ponto]] == tabuleiro[distancia[camada][ponto-3]] && tabuleiro[distancia[camada][ponto-3]] == tabuleiro[distancia[camada][ponto-6]]) {
											if (remocao == 1) { 
												strcpy(tabuleiro + 2130,"                                      \n                            Jogador |1|: (");
											}
											remocao -= 1;
											continue;
										}
									}
									if (jogador == 1 && tabuleiro[distancia[camada][ponto]] == '2') {
										tabuleiro[distancia[camada][ponto]] = '_';
										system("cls");
										peca_1[0] += 1;
										if (remocao == 1) {	
											strcpy(tabuleiro + 2130,"                                      \n                            Jogador |1|: (");
										}
										printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);
										remocao -= 1;

									} else if (jogador == 0 && tabuleiro[distancia[camada][ponto]] == '1') {
										tabuleiro[distancia[camada][ponto]] = '_';
										system("cls");
										peca_2[0] += 1;
										if (remocao == 1) {	
											strcpy(tabuleiro + 2130,"                                      \n                            Jogador |1|: (");
										}
										printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);
										remocao -= 1;
									}

								} else if (tabuleiro[distancia[camada][ponto]] == '_') {
									if (jogador == 0) {
										tabuleiro[distancia[camada][ponto]] = '1';
										system("cls");
										peca_1[1] -= 1;
										printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);
										jogador = 1;

									} else if (jogador == 1) {
										tabuleiro[distancia[camada][ponto]] = '2';
										system("cls");
										peca_2[1] -= 1;
										printTabuleiro(camada, ponto, peca_1, peca_2, distancia, tabuleiro);
										jogador = 0;
									}
									if (ponto == 1 || ponto == 7) {
										if (tabuleiro[distancia[camada][ponto+1]] == tabuleiro[distancia[camada][ponto]] && tabuleiro[distancia[camada][ponto-1]] == tabuleiro[distancia[camada][ponto]]) {
											remocao += 1;
											strcpy(tabuleiro + 2130, "                     Remova uma peca do seu opponente\n                            Jogador |1|: (");
										}

										if (tabuleiro[distancia[0][ponto]] == tabuleiro[distancia[1][ponto]] && tabuleiro[distancia[1][ponto]] == tabuleiro[distancia[2][ponto]]) {
											remocao += 1;
											strcpy(tabuleiro + 2130, "                     Remova uma peca do seu opponente\n                            Jogador |1|: (");
										}

									} else if (ponto == 3 || ponto == 5) {
										if (tabuleiro[distancia[camada][ponto+3]] == tabuleiro[distancia[camada][ponto]] && tabuleiro[distancia[camada][ponto-3]] == tabuleiro[distancia[camada][ponto]]) {
											remocao += 1;
											strcpy(tabuleiro + 2130, "                     Remova uma peca do seu opponente\n                            Jogador |1|: (");
										}

										if (tabuleiro[distancia[0][ponto]] == tabuleiro[distancia[1][ponto]] && tabuleiro[distancia[1][ponto]] == tabuleiro[distancia[2][ponto]]) {
											remocao += 1;
											strcpy(tabuleiro + 2130, "                     Remova uma peca do seu opponente\n                            Jogador |1|: (");
										}

									} else if (ponto == 0 || ponto == 2) {
										if (tabuleiro[distancia[camada][0]] == tabuleiro[distancia[camada][1]] && tabuleiro[distancia[camada][1]] == tabuleiro[distancia[camada][2]]) {
											remocao += 1;
											strcpy(tabuleiro + 2130, "                     Remova uma peca do seu opponente\n                            Jogador |1|: (");
										}

										if (tabuleiro[distancia[camada][ponto]] == tabuleiro[distancia[camada][ponto+3]] && tabuleiro[distancia[camada][ponto+3]] == tabuleiro[distancia[camada][ponto+6]]) {
											remocao += 1;
											strcpy(tabuleiro + 2130, "                     Remova uma peca do seu opponente\n                            Jogador |1|: (");
										}
									} else if (ponto == 6 || ponto == 8) {
										if (tabuleiro[distancia[camada][6]] == tabuleiro[distancia[camada][7]] && tabuleiro[distancia[camada][7]] == tabuleiro[distancia[camada][8]]) {
											remocao += 1;
											strcpy(tabuleiro + 2130, "                     Remova uma peca do seu opponente\n                            Jogador |1|: (");
										}

										if (tabuleiro[distancia[camada][ponto]] == tabuleiro[distancia[camada][ponto-3]] && tabuleiro[distancia[camada][ponto-3]] == tabuleiro[distancia[camada][ponto-6]]) {
											remocao += 1;
											strcpy(tabuleiro + 2130, "                     Remova uma peca do seu opponente\n                            Jogador |1|: (");
										}
									}
								}
									

							} else if (direct == 27) {
								return 0;

							} else if (direct == 8 || direct == 83) {
								system("cls");
								camada = ponto = jogador = 0;
								peca_1[0] = peca_2[0] = 0;
								peca_1[1] = peca_2[1] = 9;
								printf("%s", castle);
								strcpy(tabuleiro, "\n\n\n\n\n\n\n                            =======================================================\n"
"                            ||    _                   _                     _    ||\n"
"                            ||   |_|=================|_|===================|_|   ||\n"
"                            ||    |                   |                     |    ||\n"
"                            ||    |      _            |              _      |    ||\n"
"                            ||    |     |_|==========|_|============|_|     |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |      |       _    |    _         |      |    ||\n"
"                            ||    |      |      |_|==|_|==|_|        |      |    ||\n"
"                            ||    |      |       |         |         |      |    ||\n"
"                            ||    |      |       |         |         |      |    ||\n"
"                            ||   |_|====|_|=====|_|       |_|=======|_|====|_|   ||\n"
"                            ||    |      |       |         |         |      |    ||\n"
"                            ||    |      |       |    _    |         |      |    ||\n"
"                            ||    |      |      |_|==|_|==|_|        |      |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |      |            |              |      |    ||\n"
"                            ||    |     |_|==========|_|============|_|     |    ||\n"
"                            ||    |                   |                     |    ||\n"
"                            ||    |                   |                     |    ||\n"
"                            ||   |_|=================|_|===================|_|   ||\n"
"                            ||                                                   ||\n"
"                            =======================================================\n"
"\n                                                                          "
"\n                            Jogador |1|: (");
								break;

							}
						}
					}

				} else if (key == 2) {

					printf("\n\n ## DELETE / BACKSPACE = Voltar\n ## ESC = Fecha o Programa\n ## SETAS = Movimentar o Cursor\n ## ENTER = Selecionar\n"
						"\n\nCada jogador possui nove pecas. Ao comecar o jogo, cada jogador deve, alternadamente,\ncolocar uma das suas pecas em uma das 24 casas, "
						"sendo essa casa ainda desocupada.\n\nDepois, durante cada um de seus turnos, "
						"o jogador deve mover uma de suas pecas para um espaco vazio adjacente a ela.\n"
						"Toda vez que um jogador consegue colocar 3 pecas em fileira ou coluna, seja movendo ou colocando uma peca, ele pode remover uma peca do oponente.\n\n"
						"No entanto, pecas inimigas que tambem estao em fileira ou coluna de 3 estao protegidas. Quando so restarem 3 pecas a um jogador,\n"
						"ao inves de apenas as casas adjacentes, ele e permitido mover suas pecas para qualquer casa livre do tabuleiro.\n\n"
						"Perde o primeiro jogador a ficar so com duas pecas.");
					
					while (1) {
						Sleep(16);
						direct = (int) getch();

						if (direct == 8 || direct == 83) {
							system("cls");
							printf("%s", castle);
							break;

						} else if (direct == 27) {
							return 0;
						}
					}
				}
			}	
		}
	}
	

	return 0;
}