/**  AUTORES:

Rafael Carvalho Bergo - 2387190
Bruno Borges Camargo - 2319136

**/


#include "projeto2.h"
#include <stdlib.h>
void mudaGanho (double* dados, int n_amostras, double ganho)
{
    int i;
    for(i=0 ; i<n_amostras ; i++)
        dados[i]*=ganho; //Multiplica cada posição do vetor pelo ganho.
}
void ruidoUniforme (double* dados, int n_amostras, unsigned int seed, double nivel_max)
{
    int i;
    srand(seed);

    for(i=0; i< n_amostras; i++)
    {
        dados[i] += 2*nivel_max*rand()/RAND_MAX-nivel_max; //Gera valores no intervalo [-nivel_max,+nivel_max] e depois soma com a posição
        if(dados[i]> 1) //Se for maior que 1 ajusta para 1
            dados[i] = 1;
        else if(dados[i] < -1)// Se for menor que 1 ajusta para -1
            dados[i] = -1;
    }
}

void filtroDaMedia (double* dados, int n_amostras, int largura)
{
    int extremo, i, j;
    double media;

    if((largura<3 || largura>n_amostras) || (largura%2==0)) // Se a largura for menor que 3, maior que o n_amostras ou par o programa para
        return;

    extremo = (largura-1)/2; //calcula o extremo

    for(i=extremo ; i<n_amostras-extremo ; i++) //O laço começa em extremo e termina em n_amostras-extremo, pois as posições atrás da inicial e depois da última extrapolam as posições na hora de calcular a média.
    {
        media= 0;
        for(j=i-extremo ; j<=i+extremo ; j++) //Soma os termos v[-extremo]+...+v[i]+...+v[extremo]
            media+= dados[j];
        media/=largura; //Faz a média
        dados[i] = media;//Coloca a média na posição.
    }

}


void filtroDaMediaRapido (double* dados, int n_amostras, int largura)
{
    int i, extremo;
    double soma=0;

    if((largura<3 || largura>n_amostras) || (largura%2==0)) // Se a largura for menor que 3, maior que o n_amostras ou par o programa para
        return;
    extremo = (largura-1)/2; //calcula o extremo

    for(i=0 ; i< largura ; i++)
    {
        soma+= dados[i]; //Calcula a soma da primeira média.
    }
    dados[extremo]= soma/largura;// Calcula a primeira média.

    for(i=0; i<n_amostras-largura ; i++)
    {
        soma-=dados[i];//Elimina o primeiro termo da média passada.
        soma+=dados[i+largura];//Acresce o próximo termo.
        dados[i+extremo+1]= soma/largura; //Calcula a media.
    }

}






