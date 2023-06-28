/*
Gabriel Deodato Leite Brandão
2019134778
2022/2023
*/

#include "back_end.h"

// MENU PRINCIPAL
int menu_principal() {
    int opcao;
    printf("****** MENU PRINCIPAL ******\n");
    printf("1. Paragens\n");
    printf("2. Linhas\n");
    printf("3. Cálculo de Percurso\n");
    printf("4. Armazenar em Ficheiro\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

// MENU DAS PARAGENS
int menu_paragens() {
    int opcao;
    printf("****** MENU PARAGENS ******\n");
    printf("1. Registar Paragem\n");
    printf("2. Eliminar Paragem\n");
    printf("3. Visualizar Paragens\n");
    printf("4. Voltar ao Menu Principal\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

// MENU DAS LINHAS
int menu_linhas() {
    int opcao;
    printf("****** MENU LINHAS ******\n");
    printf("1. Adicionar Linha\n");
    printf("2. Atualizar Linha\n");
    printf("3. Visualizar Linhas\n");
    printf("4. Voltar ao Menu Principal\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

// Verificar se X linha existe
int linhaExiste(Linha* listaLinhas, char* nomeLinha) {
    Linha* linhaAtual = listaLinhas;
    while (linhaAtual != NULL) {
        if (strcmp(linhaAtual->nome, nomeLinha) == 0) {
            return 1;
        }
        linhaAtual = linhaAtual->proxima;
    }
    return 0;
}

// Criar nova Linha
Linha* criarLinha(char* nomeLinha) {
    Linha* novaLinha = (Linha*)malloc(sizeof(Linha));
    strcpy(novaLinha->nome, nomeLinha);
    novaLinha->paragens = NULL;
    novaLinha->proxima = NULL;
    return novaLinha;
}

// Verificar se X paragem existe
int paragemExiste(Linha* linha, char* codigoParagem) {
    Paragem* paragemAtual = linha->paragens;
    while (paragemAtual != NULL) {
        if (strcmp(paragemAtual->codigo, codigoParagem) == 0) {
            return 1;
        }
        paragemAtual = paragemAtual->proxima;
    }
    return 0;
}

// Adicionar paragem a X linha
void adicionarParagem(Linha** linha, char* nomeParagem, char* codigoParagem) {
    Paragem* novaParagem = (Paragem*)malloc(sizeof(Paragem));
    strcpy(novaParagem->nome, nomeParagem);
    strcpy(novaParagem->codigo, codigoParagem);
    novaParagem->proxima = NULL;

    if ((*linha)->paragens == NULL) {
        (*linha)->paragens = novaParagem;
    } else {
        Paragem* paragemAtual = (*linha)->paragens;
        while (paragemAtual->proxima != NULL) {
            paragemAtual = paragemAtual->proxima;
        }
        paragemAtual->proxima = novaParagem;
    }
}

// Adicionar uma nova linha á lista
void adicionarLinha(Linha** listaLinhas, Linha* novaLinha) {
    if (*listaLinhas == NULL) {
        *listaLinhas = novaLinha;
    } else {
        Linha* linhaAtual = *listaLinhas;
        while (linhaAtual->proxima != NULL) {
            linhaAtual = linhaAtual->proxima;
        }
        linhaAtual->proxima = novaLinha;
    }
}

// Adicionar nova linha manualmente (no programa)
void adicionarlinhamanual(Linha** listaLinhas) {
    Linha* novaLinha = (Linha*)malloc(sizeof(Linha));
    printf("Digite o nome da nova linha: ");
    scanf("%s", novaLinha->nome);

    novaLinha->paragens = NULL;
    novaLinha->proxima = *listaLinhas;
    *listaLinhas = novaLinha;
    printf("Nova linha adicionada com sucesso!\n");
}

// Adicionar nova linha através de um ficheiro (txt)
void adicionarlinhatxt(Linha** listaLinhas) {
    char nome_ficheiro[50];
    printf("Digite o nome do ficheiro de texto: ");
    scanf("%s", nome_ficheiro);

    // Abrir o ficheiro de texto
    FILE* arquivo = fopen(nome_ficheiro, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    // Ler o nome da linha a partir do ficheiro
    char nomeLinha[50];
    fgets(nomeLinha, 50, arquivo);
    nomeLinha[strcspn(nomeLinha, "\n")] = '\0'; // Remover o caractere de nova linha

    // Verificar se a linha já existe
    if (linhaExiste(*listaLinhas, nomeLinha)) {
        printf("A linha '%s' já existe.\n", nomeLinha);
        fclose(arquivo);
        return;
    }

    // Criar a nova linha
    Linha* novaLinha = criarLinha(nomeLinha);

    // Ler as paragens a partir do ficheiro
    char paragem[50];
    while (fgets(paragem, 50, arquivo) != NULL) {
        paragem[strcspn(paragem, "\n")] = '\0'; // Remover o char da nova linha

        // Separar o nome da paragem e o código
        char* nomeParagem = strtok(paragem, "#");
        char* codigoParagem = strtok(NULL, "#");

        // Verificar se a paragem já existe
        if (!paragemExiste(novaLinha, codigoParagem)) {
            // Adicionar a paragem à linha
            adicionarParagem(&novaLinha, nomeParagem, codigoParagem);
        }
    }


    fclose(arquivo); // Fechar o ficheiro

    // Adicionar a nova linha à lista de linhas
    adicionarLinha(listaLinhas, novaLinha);

    printf("Linha '%s' adicionada com sucesso.\n", nomeLinha);
}

//Atualizar Linha
void atualizarlinha(Linha* listaLinhas) {
    char nome[50];
    printf("Digite o nome da linha a ser atualizada: ");
    scanf("%s", nome);

    Linha* linhaAtual = listaLinhas;
    while (linhaAtual != NULL) {
        if (strcmp(linhaAtual->nome, nome) == 0) {
            printf("Nova informação para a linha %s:\n", linhaAtual->nome);
            // Pedir ao user um novo nome para a Linha
            printf("Digite o novo nome da linha: ");
            scanf("%s", linhaAtual->nome);

            printf("Linha atualizada com sucesso!\n");
            return;
        }

        linhaAtual = linhaAtual->proxima;
    }

    printf("Linha não encontrada.\n");
}

// MOSTRAR TODAS AS LINHAS EXISTENTES/REGISTADAS
void mostrar_linhas(Linha* listaLinhas) {
    if (listaLinhas == NULL) {
        printf("Nenhuma linha registada.\n");
        return;
    }

    Linha* linhaAtual = listaLinhas;
    while (linhaAtual != NULL) {
        printf("Linha: %s\n", linhaAtual->nome);
        linhaAtual = linhaAtual->proxima;
    }
}

// MOSTRAR PARAGENS DE X LINHA
/*
void mostrarparagens_xlinha(Linha linha) {
    printf("Paragens da linha %s:\n", linha.nome);
    Paragem* paragemAtual = linha.paragens;
    while (paragemAtual != NULL) {
        printf("- %s\n", paragemAtual->nome);
        paragemAtual = paragemAtual->proxima;
    }
}
 NÃO ACABEI --------
 */

// ENCONTRAR UMA PARAGEM PELO NOME NUMA LINHA ESPECIFICA
Paragem* encontrarParagemNaLinha(Linha linha, char nomeParagem[]) {
    Paragem* paragemAtual = linha.paragens;
    while (paragemAtual != NULL) {
        if (strcmp(paragemAtual->nome, nomeParagem) == 0) {
            return paragemAtual;
        }
        paragemAtual = paragemAtual->proxima;
    }
    return NULL;
}

// CALCULAR O PERCURSO ENTRE X E Y PARAGEM COM ou SEM MUNDANÇA DE LINHA
void calcular_percurso(Linha* listaLinhas) {
    char partida[50];
    char chegada[50];
    printf("Digite o ponto de partida: ");
    scanf("%s", partida);
    printf("Digite o ponto de chegada: ");
    scanf("%s", chegada);

    Linha* linhaAtual = listaLinhas;
    while (linhaAtual != NULL) {
        Paragem* partidaEncontrada = encontrarParagemNaLinha(*linhaAtual, partida);
        Paragem* chegadaEncontrada = encontrarParagemNaLinha(*linhaAtual, chegada);

        if (partidaEncontrada != NULL && chegadaEncontrada != NULL) {
            printf("Percurso encontrado na linha %s:\n", linhaAtual->nome);
            Paragem* paragemAtual = partidaEncontrada;
            while (paragemAtual != chegadaEncontrada->proxima) {
                printf("- %s\n", paragemAtual->nome);
                paragemAtual = paragemAtual->proxima;
            }
            if (paragemAtual == chegadaEncontrada->proxima) {
                printf("\nChegou à paragem de chegada.\n\n");
                return;
            }
        }

        linhaAtual = linhaAtual->proxima;
    }

    // Verificar a mudança de linha
    linhaAtual = listaLinhas;
    while (linhaAtual != NULL) {
        Paragem* partidaEncontrada = encontrarParagemNaLinha(*linhaAtual, partida);
        if (partidaEncontrada != NULL) {
            Linha* linhaDestino = listaLinhas;
            while (linhaDestino != NULL) {
                Paragem* chegadaEncontrada = encontrarParagemNaLinha(*linhaDestino, chegada);
                if (chegadaEncontrada != NULL && linhaDestino != linhaAtual) {
                    printf("Percurso com mudança de linha:\n");
                    printf("Linha %s:\n", linhaAtual->nome);
                    Paragem* paragemAtual = partidaEncontrada;
                    while (paragemAtual != NULL) {
                        printf("- %s\n", paragemAtual->nome);
                        paragemAtual = paragemAtual->proxima;
                        if (paragemAtual == chegadaEncontrada->proxima) {
                            printf("\nChegou ao ponto de transferência.\n");
                            break;
                        }
                    }
                    printf("\nMudar para linha %s:\n", linhaDestino->nome);
                    paragemAtual = linhaDestino->paragens;
                    while (paragemAtual != NULL) {
                        printf("- %s\n", paragemAtual->nome);
                        paragemAtual = paragemAtual->proxima;
                        if (paragemAtual == chegadaEncontrada) {
                            printf("\nChegou à paragem de chegada.\n\n");
                            return;
                        }
                    }
                }
                linhaDestino = linhaDestino->proxima;
            }
        }
        linhaAtual = linhaAtual->proxima;
    }

    printf("Percurso não encontrado.\n");
}



// REGISTAR UMA NOVA PARAGEM
void registar_paragem(Linha* listaLinhas) {
    char nome[50];
    char codigo[5];
    printf("Digite o nome da paragem: ");
    scanf("%s", nome);
    printf("Digite o código da paragem: ");
    scanf("%s", codigo);

    // Mostrar as linhas disponíveis para que o user selecionar
    printf("Linhas disponíveis:\n");
    mostrar_linhas(listaLinhas);

    char nomeLinha[50];
    printf("Digite o nome da linha à qual a paragem pertence: ");
    scanf("%s", nomeLinha);

    // Encontrar a linha correspondente ao nome
    Linha* linhaAtual = listaLinhas;
    while (linhaAtual != NULL) {
        if (strcmp(linhaAtual->nome, nomeLinha) == 0) {
            // Criar a nova paragem
            Paragem* novaParagem = (Paragem*)malloc(sizeof(Paragem));
            strcpy(novaParagem->nome, nome);
            strcpy(novaParagem->codigo, codigo);
            novaParagem->proxima = NULL;

            // Adicionar a nova paragem à linha
            if (linhaAtual->paragens == NULL) {
                linhaAtual->paragens = novaParagem;
            } else {
                Paragem* paragemAtual = linhaAtual->paragens;
                while (paragemAtual->proxima != NULL) {
                    paragemAtual = paragemAtual->proxima;
                }
                paragemAtual->proxima = novaParagem;
            }

            printf("Paragem registada com sucesso!\n");
            return;
        }

        linhaAtual = linhaAtual->proxima;
    }

    printf("Linha não encontrada.\n");
}

// ELIMINAR UMA PARAGEM
void eliminar_paragem(Linha* listaLinhas) {
    char paragem_nome[50];
    printf("Digite o nome da paragem a ser eliminada: ");
    scanf("%s", paragem_nome);

    Linha* linhaAtual = listaLinhas;
    while (linhaAtual != NULL) {
        Paragem* paragemAtual = linhaAtual->paragens;
        Paragem* paragemAnterior = NULL;

        while (paragemAtual != NULL) {
            if (strcmp(paragemAtual->nome, paragem_nome) == 0) {
                if (paragemAnterior == NULL) {
                    linhaAtual->paragens = paragemAtual->proxima;
                } else {
                    paragemAnterior->proxima = paragemAtual->proxima;
                }

                free(paragemAtual);
                printf("Paragem eliminada com sucesso!\n");
                return;
            }

            paragemAnterior = paragemAtual;
            paragemAtual = paragemAtual->proxima;
        }

        linhaAtual = linhaAtual->proxima;
    }

    printf("Paragem não encontrada.\n");
}

// MOSTRAR TODAS AS PARAGENS
void mostrar_paragens(Linha* listaLinhas) {
    Linha* linhaAtual = listaLinhas;

    // Se não existirem paragens
    if (linhaAtual == NULL) {
        printf("Não há paragens disponíveis.\n");
        return;
    }


    while (linhaAtual != NULL) {
        printf("Paragens da linha %s:\n", linhaAtual->nome);
        Paragem* paragemAtual = linhaAtual->paragens;
        while (paragemAtual != NULL) {
            printf("- %s (%s)\n", paragemAtual->nome, paragemAtual->codigo);
            paragemAtual = paragemAtual->proxima;
        }
        linhaAtual = linhaAtual->proxima;
    }
}
// ARMAZENAR TODAS AS PARAGENS E LINHAS NUM ARQUIVO BINÁRIO (.bin)
void armazenarEmFicheiro(Linha* listaLinhas) {
    FILE* arquivo = fopen("mondego_data_exportada.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    Linha* linhaAtual = listaLinhas;
    while (linhaAtual != NULL) {
        fwrite(linhaAtual, sizeof(Linha), 1, arquivo);
        Paragem* paragemAtual = linhaAtual->paragens;
        while (paragemAtual != NULL) {
            fwrite(paragemAtual, sizeof(Paragem), 1, arquivo);
            paragemAtual = paragemAtual->proxima;
        }
        linhaAtual = linhaAtual->proxima;
    }

    fclose(arquivo);
    printf("Dados armazenados com sucesso!\n");
}

// Libertar a memória alocada para as paragens de uma linha
void libertar_paragens(Paragem* paragens) {
    Paragem* paragemAtual = paragens;
    while (paragemAtual != NULL) {
        Paragem* paragemAnterior = paragemAtual;
        paragemAtual = paragemAtual->proxima;
        free(paragemAnterior);
    }
}

// Libertar a memória alocada para as linhas
void libertar_linhas(Linha* linhas) {
    Linha* linhaAtual = linhas;
    while (linhaAtual != NULL) {
        Linha* linhaAnterior = linhaAtual;
        linhaAtual = linhaAtual->proxima;
        libertar_paragens(linhaAnterior->paragens);
        free(linhaAnterior);
    }
}