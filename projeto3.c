/**
Autores:

Bruno Borges Camargo - 2319136
Rafael Carvalho Bergo - 2387190

**/
#include "trabalho3.h"
#include <stdlib.h>

#define PRETOINICIAL 78


int** alocaMatriz(int altura, int largura);
void  destroiMatriz(int** matriz,int altura);
void  zeraPrimeiraColuna(int** matrizPosicao, int altura);
int** criaMatrizPreto(Imagem1C* img);
int** engordaLinha(int** matriz, int altura, int largura);
int** geraMatrizPosicao(int** matrizPosicao,int altura,int largura,int *linhaUltimaPosicao,int *colunaUltimaPosicao, int *distanciaDoInicio);
void  melhorCaminho(Coordenada** caminho,int** matrizPosicao,int linhaUltimaPosicao, int colunaUltimaPosicao,int distanciaInicio);

int encontraCaminho (Imagem1C* img, Coordenada** caminho)
{
    int distanciaInicio=1;
    int posicaoUltimaLinha, posicaoUltimaColuna;
    int **matrizPosicao;

    matrizPosicao = geraMatrizPosicao(criaMatrizPreto(img),img->altura,img->largura,&posicaoUltimaLinha,&posicaoUltimaColuna, &distanciaInicio);//

    melhorCaminho(caminho, matrizPosicao, posicaoUltimaLinha, posicaoUltimaColuna,distanciaInicio);

    destroiMatriz(matrizPosicao, img->altura);

    return distanciaInicio;
}

int** alocaMatriz(int altura, int largura)
{
    int i;
    int** matriz;

    matriz = (int**) malloc(altura * sizeof(int*));
    for(i=0 ; i<altura ; i++)
        matriz[i] = (int*) malloc(largura * sizeof(int));
    return matriz;
}
void destroiMatriz(int** matriz, int altura)
{
    int i;

    for(i=0 ; i<altura ; i++)
        free(matriz[i]);
    free(matriz);
}

void zeraPrimeiraColuna(int** matrizPosicao, int altura)//Onde � preto(-1) recebe o valor 0 com o objetivo de estabelecer as primeiras posi��es.
{
    int i;

    for(i=0 ; i<altura ; i++)
    {
        if(matrizPosicao[i][0]==-1)
            matrizPosicao[i][0] = 0;
    }
}



int** criaMatrizPreto(Imagem1C* img) //gera a matriz preto(-1) e branco(-2)
{
    int temPreto=0, preto=PRETOINICIAL, i, j;
    int** matrizPosicao;

    matrizPosicao = alocaMatriz(img->altura, img->largura);
    while(!temPreto) //enquanto todas as colunas n�o tiverem pelo menos 1 preto, a toler�ncia aumenta at� ter.
    {
        temPreto = 1;
        for(j=0 ; j<img->largura && temPreto ; j++)
        {
            temPreto = 0;
            for(i=0 ; i<img->altura ; i++)
            {
                if(img->dados[i][j]<preto)
                {
                    matrizPosicao[i][j]=-1;
                    temPreto = 1;
                }
                else
                    matrizPosicao[i][j]=-2;
            }
        }
        if(!temPreto)
            preto+=10;
    }
    zeraPrimeiraColuna(matrizPosicao, img->altura);

    return matrizPosicao;
}


int** engordaLinha(int** matriz, int altura, int largura) //respons�vel por corrigir diagonaliza��es.
{
    int** matrizGorda;
    int i, j;

    matrizGorda = alocaMatriz(altura, largura);

    for(i=0 ; i<altura; i++)//coloca -2 em todas as posi��es
    {
        for(j=0 ; j<largura ; j++)
            matrizGorda[i][j]=-2;
    }

    for(i=1 ; i<altura-1 ; i++)
    {
        if(matriz[i][0]>=-1)//engorda as posi��es da primeira coluna
        {
            matrizGorda[i][0]=-1;
            matrizGorda[i+1][0]=-1;
            matrizGorda[i-1][0]=-1;
            matrizGorda[i][1]=-1;
            matrizGorda[i-1][1]=-1;
            matrizGorda[i+1][1]=-1;
        }
        if(matriz[i][largura-1]>=-1)//engorda as posi��es da �ltima coluna
        {
            matrizGorda[i][largura-1]=-1;
            matrizGorda[i-1][largura-1]=-1;
            matrizGorda[i+1][largura-1]=-1;
            matrizGorda[i][largura-2]=-1;
            matrizGorda[i-1][largura-2]=-1;
            matrizGorda[i+1][largura-2]=-1;
        }
    }

    for(i=1 ; i<altura-1 ; i++)//engorda as posi��es que est�o entre a primeira e a �ltima coluna, e entre a primeira e �ltima linha
    {
        for(j=1 ; j<largura-1; j++)
        {
            if(matriz[i][j]>=-1)
            {
                matrizGorda[i][j]=-1;
                matrizGorda[i-1][j]=-1;
                matrizGorda[i-1][j+1]=-1;
                matrizGorda[i-1][j-1]=-1;
                matrizGorda[i+1][j]=-1;
                matrizGorda[i+1][j+1]=-1;
                matrizGorda[i+1][j-1]=-1;
                matrizGorda[i][j+1]=-1;
                matrizGorda[i][j-1]=-1;
            }
        }
    }
    zeraPrimeiraColuna(matrizGorda, altura);

    destroiMatriz(matriz, altura); //destroi a matriz antiga.

    return matrizGorda;//retorna o endere�o da nova matriz gerada
}

int** geraMatrizPosicao(int** matrizPosicao,int altura,int largura,int *linhaUltimaPosicao,int *colunaUltimaPosicao, int *distanciaDoInicio)//gera a matriz posi��o, a matriz numerada do in�cio ao fim
{
    int distanciaInicio=1, mudou = 1, encontrouFim=1;
    int i, j;

    while(encontrouFim)
    {
        distanciaInicio=1;
        mudou = 1;
        while(mudou)
        {
            mudou = 0;
            for(i=0 ; i<altura && encontrouFim ; i++)//para com a flag quando um termo chega na �ltima coluna.
            {
                for(j=0 ; j<largura-1 ; j++)
                {
                    if(matrizPosicao[i][j]==distanciaInicio-1) // Procura k-1 e preenche ao entorno com k.
                    {
                        if( j-1>=0)//esquerda
                        {
                            if(matrizPosicao[i][j-1]==-1)
                            {
                                matrizPosicao[i][j-1]=distanciaInicio;
                                mudou=1;
                            }
                        }
                        if(matrizPosicao[i][j+1]==-1)//direita
                        {
                            matrizPosicao[i][j+1]=distanciaInicio;
                            mudou=1;
                            if(j+1==(largura)-1)//A itera��o para quando encontrar a �ltima coluna.
                            {
                                mudou = 0;
                                encontrouFim = 0;
                                break;
                            }
                        }
                        if(i-1>=0)//cima
                        {
                            if(matrizPosicao[i-1][j]==-1)
                            {
                                matrizPosicao[i-1][j]=distanciaInicio;
                                mudou=1;
                            }
                        }
                        if(i+1<altura)//baixo
                        {
                            if(matrizPosicao[i+1][j]==-1)
                            {
                                matrizPosicao[i+1][j]=distanciaInicio;
                                mudou=1;
                            }
                        }
                    }
                }
            }
            distanciaInicio++;
        }
        if(encontrouFim) //se n�o preencher uma posi��o na �ltima coluna, a matriz engorda.
        {
            matrizPosicao = engordaLinha(matrizPosicao, altura, largura);
        }
    }
    *linhaUltimaPosicao=i-1;//passa a linha,a coluna e a distancia para serem usadas posteriormente na passagem das coordenadas.
    *colunaUltimaPosicao=j+1;
    *distanciaDoInicio = distanciaInicio;

    return matrizPosicao;//retorna a matriz posi��o.
}

void  melhorCaminho(Coordenada** caminho,int** matrizPosicao,int linhaUltimaPosicao, int colunaUltimaPosicao,int distanciaInicio)
{
    int i, j;
    /**O conte�do apontado por caminho(um ponteiro de coordenada)vai receber um endere�o de um espa�o alocado dinamicamente.**/
    *caminho = (Coordenada*)malloc(distanciaInicio*sizeof(Coordenada));

    /**Envia as posi��es**/
    distanciaInicio--;
    (*caminho)[distanciaInicio].y =  linhaUltimaPosicao;
    (*caminho)[distanciaInicio].x =  colunaUltimaPosicao;

    i=linhaUltimaPosicao;
    j=colunaUltimaPosicao;
    while(distanciaInicio)//percorre da �ltima posi��o at� a posi��o 0
    {
        if(matrizPosicao[i][j-1] == distanciaInicio-1)//esquerda
            j--;

        else if(matrizPosicao[i-1][j] == distanciaInicio-1)//cima
            i--;

        else if(matrizPosicao[i+1][j] == distanciaInicio-1)//baixo
            i++;

        else if(matrizPosicao[i][j+1] == distanciaInicio-1)//direita
            j++;

        distanciaInicio--;

        (*caminho)[distanciaInicio].y =  i;
        (*caminho)[distanciaInicio].x =  j;
    }

}



