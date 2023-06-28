/*
Gabriel Deodato Leite Brandão
2019134778
2022/2023
*/
#include <stdio.h>
#include "back_end.c"
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <unistd.h>

int main() {
    setlocale(LC_ALL, ""); // UTF-8
    SetConsoleOutputCP(CP_UTF8); //UTF-8 em consolas windows (cmd)
    Linha *listaLinhas = NULL;
    int opcao;

    printf("                                                                                                \n ");
    printf(" 88888888ba                             8b           d8 88                      88              \n ");
    printf(" 88      '8b                            `8b         d8' ''                      88              \n ");
    printf(" 88      ,8P                             `8b       d8'                          88              \n ");
    printf(" 88aaaaaa8P'  ,adPPYba, 88,dPYba,,adPYba, `8b     d8'   88 8b,dPPYba,   ,adPPYb,88  ,adPPYba,   \n ");
    printf(" 88''''''8b, a8P_____88 88P'   '88'    '8a `8b   d8'    88 88P'   `'8a a8'    `Y88 a8'     '8a  \n ");
    printf(" 88      `8b 8PP''''''' 88      88      88  `8b d8'     88 88       88 8b       88 8b       d8  \n ");
    printf(" 88      a8P '8b,   ,aa 88      88      88   `888'      88 88       88 '8a,   ,d88 '8a,   ,a8'  \n ");
    printf(" 88888888P'   `'Ybbd8'' 88      88      88    `8'       88 88       88  `'8bbdP'Y8  `'YbbdP''   \n ");
    printf("                                                                                                \n ");

    int i;
    int x = 0;
    int y = 3;
    int tempo = 1;

    printf("Loading");

    for (i = 0; i < 10; i++) {
        printf(".");
        x++;

        if (x > y) {
            x = 0;
            printf("\b\b\b   \b\b\b");
        }

        fflush(stdout);

        sleep(tempo);
    }

    printf("\n");

    system("cls");

    printf("****** Bem-vindo á gestão do Metro do Mondego de Coimbra ******\n");

    do {

        opcao = menu_principal();

        switch (opcao) {
            case 1: {
                int subOpcaoParagens;
                do {
                    subOpcaoParagens = menu_paragens();

                    switch (subOpcaoParagens) {
                        case 1:
                            registar_paragem(listaLinhas);
                            break;
                        case 2:
                            eliminar_paragem(listaLinhas);
                            break;
                        case 3:
                            mostrar_paragens(listaLinhas);
                            break;
                        case 4:
                            break;
                        default:
                            printf("Opção inválida.\n");
                            break;
                    }
                } while (subOpcaoParagens != 4);

                break;
            }
            case 2: {
                int subOpcaoLinhas;
                do {
                    subOpcaoLinhas = menu_linhas();

                    switch (subOpcaoLinhas) {
                        case 1:
                            printf("Escolheu adicionar uma nova linha.\n");
                            printf("Quer adicionar a linha aqui (X) ou a partir de um ficheiro .txt (Y)? ");
                            char opcao;
                            scanf(" %c", &opcao);

                            if (opcao == 'X' || opcao == 'x') {
                                adicionarlinhamanual(&listaLinhas);
                            } else if (opcao == 'Y' || opcao == 'y') {
                                adicionarlinhatxt(&listaLinhas);
                            } else {
                                printf("Opção inválida.\n");
                            }

                            break;
                        case 2:
                            atualizarlinha(listaLinhas);
                            break;
                        case 3:
                            mostrar_linhas(listaLinhas);
                            break;
                        case 4:
                            break;
                        default:
                            printf("Opção inválida.\n");
                            break;
                    }
                } while (subOpcaoLinhas != 4);

                break;
            }
            case 3:
                calcular_percurso(listaLinhas);
                break;
            case 4:
                armazenarEmFicheiro(listaLinhas);
                break;
            case 5:
                printf("Saindo do programa.\n");
                break;
        }
    } while (opcao != 5);

    libertar_linhas(listaLinhas); //Liberatar a memória alloc das structs

    return 0;
}