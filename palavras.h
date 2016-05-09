#ifndef PALAVRAS_H_INCLUDED
#define PALAVRAS_H_INCLUDED
#endif // PALAVRAS_H_INCLUDED
//Biblioteca com fun��es para o programa de ca�a palavras

//Fun��o que aloca uma matriz dinamicamente
char** alocarMatriz (int linhas, int colunas) {

    int i;
    char **m = (char**) malloc(linhas*sizeof(char*)); //Alocando o n�mero de linhas
    //Alocando o n�mero de colunas
    for (i = 0; i < linhas; i++) {
        m[i] = (char*) malloc(colunas * sizeof(char));
    }

    return (m);
 }

//Procedimento que procura uma palavra na horizontal
void procuraHorizontal (char palavra[50], int linhas, int colunas, int tam, char** matrizBusca, int* achaPalavra) {
    //Declarando �ndices. I s�o linhas, J colunas, C � o �ndice de cada Char e T � o controle da forma que a matriz ser� rodada
    int c = 0;
    int i = 0;
    int j = 0;
    int t = 0;

    //Declarando vari�veis de coordenadas das posi��es iniciais e finais de I e J
    int auxMatrizI;
    int auxMatrizJ;
    int auxFimMatrizI;
    int auxFimMatrizJ;

    /*Declarando vari�veis que v�o armazenar um peda�o da matriz em uma string. A vari�vel 'compara' � a string que ser�
    comparada com nossa palavra. */
    char compara[50];


    /*La�o que ir� percorrer a matriz, pegar o n�mero de caracteres correspondente ao tamanho da nossa palavra
    e comparar se s�o iguais. O la�o para quando chegarmos ao final da matriz*/
    while (j != (colunas) && i != (linhas)) {
        for (c = 0; c < tam; c ++) {
                //No in�cio salvamos as posi��es de I e J. Elas ser�o exibidas caso a string salva seja igual a palavra digitada
                if (c == 0) {
                        auxMatrizI = i;
                        auxMatrizJ = j;
                    }
        //Motamos a string de acordo com cada caractere da matriz
        compara[c] = matrizBusca[i][j];
        //Como se trata de palavras na horizontal, sempre mudamos as colunas
        j++;
    }
    //Como o la�o conta uma vez a mais J, devemos subtra�-lo para ter a informa��o da posi��o final correta
    j--;
    /*A fun��o strnmp compara se duas strings s�o iguais at� o tamanho dado. Comparamos se a string montada � id�ntica
    a palavra digitada. Caso seja, esta fun��o retorna um valor zero armazenada na vari�vel retorno*/
    int retorno = strncmp(palavra, compara, tam);
    //Armazenamos as posi��es finais que ser�o exibidas caso a palavra seja id�ntica
    auxFimMatrizI = i;
    auxFimMatrizJ = j;

        if (retorno == 0){
            //Exibindo coordenadas acrescido de 1 pois a matriz em C come�a em zero mas um ca�a-palavras geralmente come�a em 1
            printf ("%d,%d:%d,%d ", auxMatrizI+1, auxMatrizJ+1, auxFimMatrizI+1, auxFimMatrizJ+1);
            *achaPalavra = 1; //O controle se torna verdade
            c = 0; //Zeramos a vari�vel C para contarmos a pr�xima string da matriz
        }
    //Caso contr�rio n�o exibimos nada, apenas zeramos a vari�vel C
        else if (retorno != 0) {
            c = 0;
        }
    /*Acrescentamos um a t, pois agora ele ir� montar uma palavra a partir de t+1. Se montamos uma palavra inicialmente
    em i = 0 e j = 0, por exemplo, agora ele ir� montar uma palavra a partir de i = 0 e j = 1, at� que seja necess�rio mudar
    de linha. Um exemplo visual:
    0 1 2 3 4 5 6 7 8
   0A B C D E F G H I
   1J K L M N O P Q R
   Inicialmente montamos a palavra ABCD. Depois acrescentamos um a T (controle de Tempo) e montamos BCDE at� que n�o seja mais
   poss�vel montar uma palavra na linha (quando o valor da coluna estourar)*/
    t++;
    j = t;
        //Quando J estourar as colunas, resetamos o T (controle de tempo) e o J, e vamos para a pr�xima linha
        if (j >= colunas) {
            j = 0;
            t = 0;
            i++;

        }
    }
}

void procuraVertical (char palavra[50], int linhas, int colunas, int tam, char** matrizBusca, int* achaPalavra) {
    //A l�gica para a vertical � bem parecido, as vari�veis utilizadas tem as mesmas fun��es
    int c = 0;
    int i = 0;
    int j = 0;
    int t = 0;

    int auxMatrizI;
    int auxMatrizJ;
    int auxFimMatrizI;
    int auxFimMatrizJ;

    char compara[50];
    /*A montagem de palavras segue exatamente a mesma l�gica. A �nica diferen�a � que agora mudamos de linha (I) constantemente
    enquanto o n�mero de colunas s� muda determinadas vezes (mesma ocorr�ncia para colunas e linhas na horizontal*/
    while (j != (colunas) && i != (linhas)) {
        for (c = 0; c < tam; c ++) {
            if (c == 0) {
                auxMatrizI = i;
                auxMatrizJ = j;
            }

        compara[c] = matrizBusca[i][j];
        i++;

            if (i >= linhas) {
                i = 0;
                t = 0;
                j++;
                break;
            }
        }

        if ( i != 0 ) {
            i --;
        }

    int retorno = strncmp(palavra, compara, tam);

    auxFimMatrizI = i;
    auxFimMatrizJ = j;

        if (retorno == 0){
            printf ("%d,%d:%d,%d ", auxMatrizI+1, auxMatrizJ+1, auxFimMatrizI+1, auxFimMatrizJ+1);
            *achaPalavra = 1;
            c = 0;
        }
        else if (retorno != 0) {
            c = 0;
        }

        if (i != 0) {
            t++;
            i = t;
        }
    }
}

/*A l�gica para procurar a palavra na diagonal parte de uma l�gica parecida com as anteriores. Neste caso temos que
alternar I e J na mesma medida sendo que o I n�o se inicial mais do zero e sim do �ndice final da matriz. Por isso nosso
controle de tempo vai alterar J de maneira similar ao modo de procurar na horizontal e I sempre vai voltar para a posi��o
inicial*/

void procuraDiagonal (char palavra[50], int linhas, int colunas, int tam, char **matrizBusca, int *achaPalavra) {
    /*As vari�veis tem as mesmas fun��es dos procedimentos anteriores. iInicial e tempoJ tem a mesma fun��o de controle
    da vari�vel T dos outros procedimentos*/

    int  c = 0;
    int iInicial = linhas-1;
    int tempoJ = 0;
    int i = linhas - 1;
    int  j = 0;

    int auxMatrizI;
    int auxMatrizJ;
    int auxFimMatrizI;
    int auxFimMatrizJ;

    char compara[50];
    //Mesma l�gica de montagem. Entretanto, I e J se alternam na mesma medida
    while (1) {
        for (c = 0; c < tam; c ++) {
            if (c == 0) {
                auxMatrizI = i;
                auxMatrizJ = j;

            }

            compara[c] = matrizBusca[i][j];
                 i--;
                 j++;
        }

        i++;
        j--;

    int retorno = strncmp(palavra, compara, tam);

    auxFimMatrizI = i;
    auxFimMatrizJ = j;

        if (retorno == 0){
            printf ("%d:%d, %d:%d ", auxMatrizI+1, auxMatrizJ+1, auxFimMatrizI+1, auxFimMatrizJ+1);
            *achaPalavra = 1;
            c = 0;
        }

        else if (retorno != 0) {
            c = 0;
        }
        //Para a diagonal, existe uma condi��o espec�fica de parada que deve ser atingida neste ponto
        if (j == colunas-1 && i == 0) {
            break;
        }
    //O controle � feito desta maneira, retornamos I na posi��o inicial e o J ganha uma nova posi��o
    tempoJ ++;
    j = tempoJ;
    i = iInicial;
        /*Caso J exceda a diferen�a de colunas e o tamanho da palavra, significa que n�o � poss�vel formar
        uma nova palavra naquela linha. Ent�o o Iinicial muda de posi��o e o tempoJ retorna a zero.*/
        if (j > colunas-tam) {
            tempoJ = 0;
            j = tempoJ;
            iInicial--;
            i = iInicial;
        }
    }
}
