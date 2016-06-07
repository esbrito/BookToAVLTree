#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "cabeca.h"
#include <time.h>


int main(int argc, char *argv[] )
//argc eh um inteiro que conta quantos parametros foram passados pela linha de comando  *Comentarios feitos pela prória professora no arquivo exemplo *
//argv guarda o texto dos parametros, argv[1] eh o primeiro parametro, argv[2] eh o segundo paramento, etc *Comentarios feitos pela prória professora no arquivo exemplo *
{
    char palavra[100] = ""; //Para armazenar cada palavra do texto individualmente antes de chamar a funcao
    char p_consulta[100] = "";
    FILE *texto, *consulta, *saida;
    pNodoA *arv = NULL;
    int k =0, ok,contador_linha=0;
    char c;

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados  *Comentarios feitos pela prória professora no arquivo exemplo *

    if (argc != 4)
    {
        printf("Numero incorreto de parametros.\n Sintaxe: copia arq_origem arq_destino\n Argumentos: %d" , argc);
        return 1;
    }
    else
    {
        texto = fopen (argv[1], "r"); // Abre para ler o arquivo do livro alienista
        consulta = fopen (argv[2],"r"); //Abre arquivo de consulta, em que terá as palavras consultadas na arvore gerada
        saida = fopen (argv[3],"w");  // Cria aqruivo de saida, que terá os resultados de todas as palavras pesquisadas com as linhas em que foram encontradas
        if (texto == NULL || consulta == NULL || saida == NULL)
        {
            printf("Arquivo nao encontrado.\n");
            return 1;
        }
        else
        {
            contador_linha = 1;
            /*Foi feita a leitura caracter a caracter, para poder obter palavra por palavra, usando cpomo referencia,
            espaços ou pontuações para saber que cada palavra terminou e então adiciona-la a estrutura de dados */
            while((c = fgetc(texto))!= EOF)
            {

                if(c == '\n' ) //Se for Enter conta uma linha
                {
                    contador_linha++; //Contador de linha, que é enviado para a função que faz a inserção das palavras na arvore avl, para ionserir as linhas em que a palavra foi encontrada
                }

               if(c == ' ' || c == ',' || c == '.' || c == ';'|| c == '?'|| c == '!' || c == '\n' ||
                 c == '-' || c == '*' || c == '/' || c == '*'|| c == ':'|| c == '|'
                 || c == '(' || c == ')' || c == ')' || c == '_'|| c == '['|| c == ']' || c == '='  || c == '"' || c == '\t' || c == '>' || c == '<' || c == '+' || c == '{' || c == '}' )
                 {

                   palavra[k] = '\0';

                    strlwr(palavra); //Transforma a string em minuscula, já que não é para ter diferenciação de maiusculas e minusculas
                    printf("%s ",palavra);
                    arv = InsereAVL(arv, palavra,&ok,contador_linha);
                    k=0;
                    palavra[k]= '\0'; //Zera a string, para estar vazia para a proxima palavra

                }
                else //Se não tiver nenhuma pontuação ou espaço, adiciona mais esse caracter no vetor de caracteres (string)
                {
                    palavra[k] = c;
                    k++;
                }



            }
            /* Usado para inserir ultima palavra caso não tenha um ENTER ou espaço nela*/
            palavra[k] = '\0';

            strlwr(palavra); //Transforma a string em minuscula, já que não é para ter diferenciação de maiusculas e minusculas
            printf("%s ",palavra);
            arv = InsereAVL(arv, palavra,&ok,contador_linha);
            k=0;
            palavra[k]= '\0'; //Zera a string, para estar vazia para a proxima palavra



            printf ("\n");
            k=0; //Zera k, para poder ser usado agora na leitura do arquivo de consulta

            clock_t start = clock(); //Inicia relogio, para poder ter o tempo que leva para a consulta
            clock_t diff;
            /* Mesma lógica aplicada para adicionar as palavras a estrutura de dados, mas dessa vez cada palavra é usada na função de oonsulta da AVL */



            while((c = fgetc(consulta))!= EOF)
            {


                if(c == ' ' || c == ',' || c == '.' || c == ';'|| c == '?'|| c == '!' || c == '\n' ||
                 c == '-' || c == '*' || c == '/' || c == '*'|| c == ':'|| c == '|'
                 || c == '(' || c == ')' || c == ')' || c == '_'|| c == '['|| c == ']' || c == '='  || c == '"' || c == '\t' || c == '>' || c == '<' || c == '+' || c == '{' || c == '}' )   //Se leu espaço ou pontuacoes significa que acabou palavra, logo adiciona ela a struct AVL
                {

                    p_consulta[k] = '\0';
                    strlwr(p_consulta);

                    if(strcmp(p_consulta,"") !=0)
                        consultaAVL(arv, p_consulta,saida);
                    k=0;
                    p_consulta[k]= '\0'; //Zera a string, para estar vazia para a proxima palavra

                }
                else
                {

                    p_consulta[k] = c;
                    k++;
                }


            }
            /* Usado para consultar ultima palavra caso não tenha um ENTER ou espaço nela*/
            p_consulta[k] = '\0';
            strlwr(p_consulta);
            if(strcmp(p_consulta,"") !=0)
                consultaAVL(arv, p_consulta,saida);
            k=0;
            p_consulta[k]= '\0'; //Zera a string, para estar vazia para a proxima palavra


            diff = clock() - start; //Diferença entre o tempo que iniciou com o tempo atual, para saber o tempo de consulta
            int msec = diff * 1000 / CLOCKS_PER_SEC;
            printf("\nTempo gasto na consulta %d segundos %d milisegundos", msec/1000, msec%1000);
            fprintf(saida,"\nTempo gasto na consulta %d segundos %d milisegundos", msec/1000, msec%1000); //Adicionada a informação no arquivo de saida
        }

        fclose(texto);
        fclose(consulta);
        fclose(saida);

        return 0;
    }

}
