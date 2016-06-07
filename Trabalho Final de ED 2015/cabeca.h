
//typedef char TipoInfo[1000];

typedef struct TNodoA pNodoA;
typedef struct TipoInfoNo InfoNo;
typedef struct TipoPtNo PtNo;

int Altura (pNodoA * a);
int Calcula_FB(pNodoA * a);
pNodoA * rotacao_direita(pNodoA * pt);
pNodoA * rotacao_esquerda(pNodoA * pt);
pNodoA * rotacao_dupla_direita (pNodoA * pt);
pNodoA * rotacao_dupla_esquerda (pNodoA * pt);
pNodoA * Caso1 (pNodoA * a , int *ok);
pNodoA * Caso2 (pNodoA * a , int *ok);
pNodoA * InsereAVL (pNodoA * a, char palavra[1000], int *ok , int linha);
void consultaAVL (pNodoA *a, char x[],FILE *arquivo);
void imprime(PtNo* l,FILE *arquivo);
PtNo* insereLSE (PtNo* l, InfoNo dados);

