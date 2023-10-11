/*
    Autor: Bruno Borges Camargo
*/

#include "trabalho1.h"
#include <math.h>

unsigned int fourcc (char c1, char c2, char c3, char c4)
{

    return c1+c2*0x100+c3*0x10000+c4*0x1000000;//A multiplicação por 0x(100)^n movimenta os números, em base hexadecimal, em 2*n casas. Ex: FE+E3*100=E3FE

}
int calculaInterseccao (int n_retangulos)
{
    int x_menor_a, x_maior_a, y_menor_a, y_maior_a;
    int i, x_menor_b, x_maior_b, y_menor_b, y_maior_b;

    x_menor_a= pegaXSE (i);
    x_maior_a= pegaXID (i);

    y_menor_a= pegaYID (i);
    y_maior_a= pegaYSE (i);

    for(i=1; i<n_retangulos; i++)
    {
        x_menor_b= pegaXSE (i);
        x_maior_b= pegaXID (i);

        y_menor_b= pegaYID (i);
        y_maior_b= pegaYSE (i);

        if(x_menor_b>x_menor_a) //O maior valor do extremo esquerdo do intervalo.Ex: (3 (5  -->  (5
            x_menor_a= x_menor_b;
        if(x_maior_b<x_maior_a)//O menor valor do extremo direito do intervalo. Ex: 20) 10) --> 10)
            x_maior_a= x_maior_b;
        if(x_maior_a<=x_menor_a)//Se o extremo direito for maior que o extremo esquerdo significa que essa intersecção existe. Ex:(5,10) existe.
            return 0;//Para se a intersecção não existir.

        if(y_menor_b>y_menor_a)//Segue a mesma lógica de x, só que agora no eixo y.
            y_menor_a= y_menor_b;
        if(y_maior_b<y_maior_a)
            y_maior_a= y_maior_b;
        if(y_maior_a<=y_menor_a)
            return 0;//Para se a intersecção não existir.
    }

    return ((x_maior_a-x_menor_a)*(y_maior_a-y_menor_a)); //retorna a área do retângulo.

}
double raizAproximada (double x, double erro_minimo)
{
    double min, max, palpite, teste;

    for(max=1; max*max<x; max++); //Procura a primeira potência inteira maior;

    min=max-1; //Última potência inteira menor;
    palpite=(max+min)/2;//Termo médio do intervalo [min,max]
    teste= palpite*palpite;
    while(fabs(teste-x)>erro_minimo)//Faz o módulo da diferença entre palpite.palpite-x, se ele for maior que o erro, o laço continua, do contrário, encerra.
    {

        if(teste>x)//Se palpite.palpite for maior que x, significa que o palpite deve ser menor, então o valor max do intervalo recebe palpite.
            max=palpite;
        else
            min=palpite;//Se palpite.palpite for menor que x, significa que o palpite deve ser maior, então o valor min do intervalo recebe palpite.

        palpite=(min+max)/2;//palpite recebe o valor médio do novo intervalo.
        teste= palpite*palpite;
    }
    return palpite;
}

