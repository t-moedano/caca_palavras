//*******************************************************************
// Lista de Exerc�cios : Aula ?
// Autor: Thauany Moedano
// Matricula: 92486
// Data: 19/09/2014
// Curso : BCT Noturno - Turma B
// Prof: Val�rio Rosset
//*******************************************************************

/* EXERC�CIO. LAB01 - CA�A PALAVRAS. Fazer um ca�a palavras*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavras.h" //Implementando biblioteca palavras. Sugiro que leia esta biblioteca primeiro


int main() {
    //Abrindo o programa MatrizLetras.txt
    printf ("~~~Lendo o arquivo....\n");
    FILE *cacaPalavras;
    cacaPalavras = fopen("MatrizLetras.txt", "r");

    //Declarando vari�veis para contar quantas linhas e colunas tem a matriz do arquivo
    int marcacao;
    int linhas = 1;
    int caracteres = 0;
    int colunas;

    //Se o arquivo n�o for encontrado, uma mensagem de erro ser� exibida
    if(cacaPalavras == NULL) {
        printf("Erro! Arquivo nao encontrado\n");
        return(0);
    }
    else
        printf ("Arquivo lido com sucesso! Transpondo matriz.... \n");

    //Contando n�mero de caracteres e linhas
    while ((marcacao = fgetc(cacaPalavras))!= EOF){
        caracteres ++;
        if(marcacao =='\n' || marcacao == '\l') {
            linhas++;
        }
    }
    //Deduzindo o n�mero de colunas a partir do n�mero de caracteres e linhas
    colunas = caracteres / linhas;
    //Fechando o arquivo
    fclose(cacaPalavras);

/************************************************/

    /*Alocando a matriz dinamicamente. ATEN��O: EM COMPUTADORES LINUX (COMO OS DA FACULDADE), A FORMATA��O
    FAZ COM Q O LINUX LEIA UMA COLUNA A MAIS QUE O WINDOWS. PARA O PROGRAMA FUNCIONAR CORRETAMENTE EM LINUX
    BASTA TIRAR O +1 DE COLUNAS+1 DA ALOCA��O DINAMICA E DO FOR DE PREENCHIMENTO DA MATRIZ*/
    char **matrizBusca;
    matrizBusca = alocarMatriz(linhas, colunas+1);
    //Caso n�o haja mem�ria suficiente, uma mensagem de erro ser� exibida
    if (matrizBusca == NULL) {
        printf ("Nao foi possivel alocar a matriz!");
        return(0);
    }

/************************************************/

    //Reabrindo o arquivo de matriz
    FILE *matrizLetras;
    matrizLetras = fopen("MatrizLetras.txt", "r");

    //Transpondo o arquivo de matriz para uma matriz alocada dinamicamente
    int i;
    int j;

    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas+1; j++) {
            matrizBusca[i][j] = fgetc(matrizLetras);
        }
    }
    //Fechando o arquivo
    fclose(matrizLetras);

/************************************************/

    printf("Digite uma palavra: ");
    //Lendo do teclado a palavra a ser procurada
    char palavra[50];
    scanf ("%s", &palavra);
    //Verificando o tamanho da palavra. Ser� utilizado para procur�-la na matriz
    int tam;
    tam = strlen(palavra);

    //Controle que verifica se uma palavra foi encontrada.
    int achaPalavra = 0;
    //Se o usu�rio inserir uma palavra que estoure a matriz, uma mensagem de erro ser� exibid
    if (tam > colunas || tam > linhas) {
        printf ("Estouro de memoria. Palavra muito grande. Erro \n");
        return (0);
    }
    //Procurando a palavra na horizontal, vertical e diagonal
    procuraHorizontal(palavra, linhas, colunas, tam, matrizBusca, &achaPalavra);
    procuraVertical(palavra, linhas, colunas, tam, matrizBusca, &achaPalavra);
    procuraDiagonal(palavra, linhas, colunas, tam, matrizBusca, &achaPalavra);

/************************************************/
//Invertendo a palavra para procur�-la de tr�s para frente
    //Declarando �ndices
    int r;
    int s = 0;
    char palavraInvertida[50];
    /*Invertendo a palavra. Existe uma fun��o da biblioteca <string.h> chamada strrev() que faz a mesma coisa,
    por�m ela n�o funciona no Linux!*/
    for (r = tam-1; r >= 0; r--) {
        palavraInvertida[s] = palavra[r];
        s++;
    }
    //Procurando a palavra de tr�s pra frente na horizontal, vertical e diagonal
    procuraHorizontal(palavraInvertida, linhas, colunas, tam, matrizBusca, &achaPalavra);
    procuraVertical(palavraInvertida, linhas, colunas, tam, matrizBusca, &achaPalavra);
    procuraDiagonal(palavraInvertida, linhas, colunas, tam, matrizBusca, &achaPalavra);
    //Se nenhuma palavra foi encontrda, um X ser� exibido na tela.
    if (achaPalavra == 0) {
        printf ("X");
    }

    //Liberando a mem�ria da matriz e encerrando o programa
    free(matrizBusca);
    return (0);
 }
