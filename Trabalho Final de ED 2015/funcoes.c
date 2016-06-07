#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cabeca.h"



struct TipoInfoNo{
       int list; //Dado da lista que conterá as linhas em que se encontra a palavra
       };

struct TipoPtNo{  //Struct de Lista Encadeada Simples, que será percorrida para obter todos os valores de quais linhas estavam tal palavra
       InfoNo info;
       PtNo *prox;
       };


struct TNodoA
{
    int FB;
    char palavra[100]; //A palavra poderia ter até 100 caracteres
    PtNo *linhas; //Ponteiro para a Lista Encadeada
    struct TNodoA *esq;
    struct TNodoA *dir;
};


PtNo* cria_lista(void)
{
       return NULL;
}

PtNo* insereLSE (PtNo* l, InfoNo dados)
{
       PtNo *novo; //novo elemento
       PtNo *ant = NULL; //ponteiro auxiliar para a posição anterior
       PtNo *ptaux = l; //ponteiro auxiliar para percorrer a lista

       /*aloca um novo nodo */
    novo = (PtNo*) malloc(sizeof(PtNo));
    /*insere a informação no novo nodo*/
    novo->info = dados;
    /*Não precisa procurar a posição de inserção, pois o valor em que o
    numero da linha a ser inserido sempre será colocado no final, uma vez que as palavras a serem colocadas na AVL
     sempre já estarão em ordem as linhas em que se encontram, pois se obtem as palavras do inicio do texto até o final*/

    while ((ptaux!=NULL))
    {
        if(ptaux->info.list == dados.list) //Caso já foi adicionada essa linha, não é necessário adicionar denovo na lista
        {
            return l;
        }

        ant = ptaux;
        ptaux = ptaux->prox;



    }

       if (ant == NULL) /*Significa que é o primeiro elemento*/
       {

               novo->prox = l;
               l = novo;
       }
       else /*Insere no final*/
       {
            novo->prox = ant->prox;
            ant->prox = novo;
       }


    return l;
}
void imprime(PtNo* l,FILE *arquivo)
{
    PtNo* ptaux;
    if (l == NULL) //Se a lista encadeada estiver vazia, significa que nada foi adicionada nela e portanto a palavra não foi encontrada em nenhuma linha
    {
        puts("nao foi encontrada em nenhuma linha \n");
        fprintf(arquivo, "nao foi encontrada em nenhuma linha\n");

    }

    else
    {
        printf("foi encontrada na(s) linha(s): ");
        fprintf(arquivo, "foi encontrada na(s) linha(s): ");
        for (ptaux=l; ptaux!=NULL; ptaux=ptaux->prox) //Percorre a lista encadeada, obtendo e printando os valores da lista onde a mesma é encontrada
        {
            printf("%d, ",ptaux->info.list);
            fprintf(arquivo, "%d, ",ptaux->info.list);
        }
        printf("\n");
        fprintf(arquivo,"\n");
    }

}




int Altura (pNodoA *a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else
    {
        Alt_Esq = Altura (a->esq);
        Alt_Dir = Altura (a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}



pNodoA* rotacao_direita(pNodoA *pt)
{
    pNodoA* ptu;

    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

pNodoA* rotacao_esquerda(pNodoA *pt)
{
    pNodoA* ptu;

    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

pNodoA* rotacao_dupla_direita (pNodoA* pt)
{
    pNodoA* ptu, *ptv;

    ptu = pt->esq;
    ptv = ptu->dir;
    ptu->dir = ptv->esq;
    ptv->esq = ptu;
    pt->esq = ptv->dir;
    ptv->dir = pt;
    if (ptv->FB == 1)   pt->FB = -1;
    else pt->FB = 0;
    if (ptv->FB == -1)  ptu->FB = 1;
    else ptu->FB = 0;
    pt = ptv;
    return pt;
}

pNodoA* rotacao_dupla_esquerda (pNodoA* pt)
{
    pNodoA *ptu, *ptv;

    ptu = pt->dir;
    ptv = ptu->esq;
    ptu->esq = ptv->dir;
    ptv->dir = ptu;
    pt->dir = ptv->esq;
    ptv->esq = pt;
    if (ptv->FB == -1) pt->FB = 1;
    else pt->FB = 0;
    if (ptv->FB == 1) ptu->FB = -1;
    else ptu->FB = 0;
    pt = ptv;
    return pt;
}


pNodoA* Caso1 (pNodoA* a , int *ok)
{
    pNodoA *ptu;

    ptu = a->esq;
    if (ptu->FB == 1)
    {
      //  printf("fazendo rotacao direita em %s\n",a->palavra);
        a = rotacao_direita(a);
    }
    else
    {
      //  printf("fazendo rotacao dupla direita em %s\n",a->palavra);
        a = rotacao_dupla_direita(a);
    }

    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA* Caso2 (pNodoA *a , int *ok)
{
    pNodoA *ptu;

    ptu = a->dir;
    if (ptu->FB == -1)
    {

     //   printf("fazendo rotacao esquerda em %s\n",a->palavra);
        a=rotacao_esquerda(a);
    }
    else
    {

      //  printf("fazendo rotacao dupla esquerda em %s\n",a->palavra);
        a=rotacao_dupla_esquerda(a);
    }
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA* InsereAVL (pNodoA *a, char x[], int *ok, int linha)
{
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
     x, a chave a ser inserida e h a altura da árvore */

    if (a == NULL)
    {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        strcpy(a->palavra,x);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        a->linhas = cria_lista();


        *ok = 1;
    }
    if (strcmp(a->palavra,x) == 0) //Sao iguais as palavras, soma mais uma informação de que linha foi encontrada
        {
           InfoNo dados;
           dados.list = linha;
           a->linhas = insereLSE(a->linhas, dados);
        }


    else{

        if (strcmp(a->palavra,x) > 0)
        {


            a->esq = InsereAVL(a->esq,x,ok,linha);
            if (*ok)
            {
                switch (a->FB)
                {
                case -1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case  0:
                    a->FB = 1;
                    break;
                case  1:
                    a=Caso1(a,ok);
                    break;
                }
            }
        }



        if((strcmp(a->palavra,x) < 0))
        {
        //    printf("Foi pra direita -> Palavra: %s", a->palavra);
            a->dir = InsereAVL(a->dir,x,ok,linha);
            if (*ok)
            {
                switch (a->FB)
                {
                case  1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case  0:
                    a->FB = -1;
                    break;
                case -1:
                    a = Caso2(a,ok);
                    break;
                }
            }
        }


    }
    return a;
}



void consultaAVL (pNodoA *a, char x[],FILE *arquivo)
{
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
      x, a chave a ser inserida e h a altura da árvore */
    int h=0;
    int anterior=0;
    if (a == NULL)
    {
        /* Se chegar na folha, significa que não achou a palavra  */
        printf("A palavra %s nao foi encontrada \n" , x);
        fprintf(arquivo, "A palavra %s nao foi encontrada \n" , x);

    }
    else if (strcmp(a->palavra,x) > 0)
    {

        consultaAVL(a->esq,x,arquivo);

    }
    else if((strcmp(a->palavra,x) < 0))
    {

        consultaAVL(a->dir,x,arquivo);

    }

    else if (strcmp(a->palavra,x) == 0) //Sao iguais as palavras, soma mais uma informação de que linha foi encontrada
    {
        printf("A palavra * %s * ", x);
        fprintf(arquivo, "A palavra * %s * ", x);
        imprime(a->linhas,arquivo);

    }
    return;
}




