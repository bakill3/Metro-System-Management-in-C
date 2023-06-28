/*
Gabriel Deodato Leite Brandão
2019134778
2022/2023
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -*- coding: utf-8 -*-


// Estrutura das Paragens
typedef struct Paragem {
    char nome[50];
    char codigo[5];
    struct Paragem* proxima;
} Paragem;

// Estrutura das Linhas
typedef struct Linha {
    char nome[50];
    struct Paragem* paragens;
    struct Linha* proxima;
} Linha;

void adicionarlinhamanual(Linha** listaLinhas);
void adicionarlinhatxt(Linha** listaLinhas);
void atualizarlinha(Linha* listaLinhas);
void mostrar_linhas(Linha* listaLinhas);
//void mostrarparagens_xlinha(Linha linha);
void calcular_percurso(Linha* listaLinhas);
void registar_paragem(Linha* listaLinhas);
void eliminar_paragem(Linha* listaLinhas);
void mostrar_paragens(Linha* listaLinhas);
void adicionarLinha(Linha** listaLinhas, Linha* novaLinha);
