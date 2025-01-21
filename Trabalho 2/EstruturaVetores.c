#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"


typedef struct pos
{
    int *array;
    int ultima;
    int tamanho;
}Pos;
Pos *arrayPrincipal;


// Verifica se tá entre 1 e 10
int validarPos(int pos)
{
    if(pos < 1 || pos > 10) return POSICAO_INVALIDA; 
    return SUCESSO;
}
/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/
void inicializar()
{
    arrayPrincipal = malloc(sizeof(Pos) * TAM);
    for(int i = 0; i < TAM; i++)
    {
        arrayPrincipal[i].array = NULL;
        arrayPrincipal[i].ultima = 0;
        arrayPrincipal[i].tamanho = 0;
    }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int pos, int tamanho)
{
    if (tamanho <= 0) return TAMANHO_INVALIDO;

    if (arrayPrincipal[pos-1].array != NULL) return JA_TEM_ESTRUTURA_AUXILIAR;
     
    if (validarPos(pos)==POSICAO_INVALIDA) return POSICAO_INVALIDA;

    arrayPrincipal[pos-1].array = malloc(sizeof(int) * tamanho);
    
    if (arrayPrincipal[pos-1].array == NULL) return SEM_ESPACO_DE_MEMORIA;

    arrayPrincipal[pos-1].ultima = 0;
    arrayPrincipal[pos-1].tamanho = tamanho;

    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int pos, int val)
{
    int posExiste = 0;
    int cheio = 0;

    if(validarPos(pos)==POSICAO_INVALIDA) return POSICAO_INVALIDA;

    if (arrayPrincipal[pos-1].array != NULL) posExiste = 1;
    if (posExiste == 0)return SEM_ESTRUTURA_AUXILIAR;

    if (arrayPrincipal[pos-1].ultima == arrayPrincipal[pos-1].tamanho) cheio = 1;
    if (cheio == 1) return SEM_ESPACO;

    arrayPrincipal[pos-1].array[arrayPrincipal[pos-1].ultima] = val;
    arrayPrincipal[pos-1].ultima++;
    
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int pos)
{
    if(validarPos(pos)==POSICAO_INVALIDA) return POSICAO_INVALIDA;
    
    if(arrayPrincipal[pos-1].array == NULL) return SEM_ESTRUTURA_AUXILIAR;
    
    if(arrayPrincipal[pos-1].ultima == 0) return ESTRUTURA_AUXILIAR_VAZIA;
    
    arrayPrincipal[pos-1].ultima--;
    
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    NUMERO_INEXISTENTE - Número não existe
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int pos, int val)
{
    if(validarPos(pos)==POSICAO_INVALIDA) return POSICAO_INVALIDA;

    if(arrayPrincipal[pos-1].array == NULL) return SEM_ESTRUTURA_AUXILIAR;

    if(arrayPrincipal[pos-1].ultima == 0) return ESTRUTURA_AUXILIAR_VAZIA;

    for(int i = 0; i < arrayPrincipal[pos-1].ultima; i++)
    {
        if(arrayPrincipal[pos-1].array[i] == val)
        {
            for(int j = i; j < arrayPrincipal[pos-1].ultima; j++)
            {
                arrayPrincipal[pos-1].array[j] = arrayPrincipal[pos-1].array[j+1];
            }
            arrayPrincipal[pos-1].ultima--;
            return SUCESSO;
        }
    }
    
    return NUMERO_INEXISTENTE;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int pos, int vet[])
{

    if(validarPos(pos)==POSICAO_INVALIDA) return POSICAO_INVALIDA;

    if(arrayPrincipal[pos-1].array == NULL) return SEM_ESTRUTURA_AUXILIAR;

    for(int i = 0; i < arrayPrincipal[pos-1].ultima; i++)
    {
        vet[i] = arrayPrincipal[pos-1].array[i];
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int pos, int vet[])
{
    int aux;

    if(validarPos(pos)==POSICAO_INVALIDA) return POSICAO_INVALIDA;

    if(arrayPrincipal[pos-1].array == NULL) return SEM_ESTRUTURA_AUXILIAR;

    for(int i = 0; i < arrayPrincipal[pos-1].ultima; i++)
    {
        vet[i] = arrayPrincipal[pos-1].array[i];
    }
    
    for(int i = 0; i < arrayPrincipal[pos-1].ultima-1; i++)
    {
        for(int j = i+1; j < arrayPrincipal[pos-1].ultima; j++)
        {
            if(vet[i] > vet[j])
            {
                aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
        }
    }
    
    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vet[])
{
    int vazia = 1;
    int base = 0;

    for(int i = 0; i < TAM; i++)
    {
        if(arrayPrincipal[i].array != NULL && arrayPrincipal[i].ultima != 0)
        {
            vazia = 0;
            break;
        }
    }

    if(vazia == 1) return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    for(int i = 0; i < TAM; i++)
    {
        if(arrayPrincipal[i].array == NULL) continue;
        for(int j = 0; j < arrayPrincipal[i].ultima; j++)
        {
            vet[base] = arrayPrincipal[i].array[j];
            base++;
        }
    }
    
    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vet[])
{
    int vazia = 1;
    int base = 0, aux;

    for(int i = 0; i < TAM; i++)
    {
        if(arrayPrincipal[i].array != NULL && arrayPrincipal[i].ultima != 0)
        {
            vazia = 0;
            break;
        }
    }

    if(vazia == 1) return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    for(int i = 0; i < TAM; i++)
    {
        if(arrayPrincipal[i].array == NULL) continue;
        for(int j = 0; j < arrayPrincipal[i].ultima; j++)
        {
            vet[base] = arrayPrincipal[i].array[j];
            base++;
        }
    }

    for(int i = 0; i < base-1; i++)
    {
        for(int j = i+1; j < base; j++)
        {
            if(vet[i] > vet[j])
            {
                aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
        }
    }


    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int pos, int novotamanho)
{
    if(validarPos(pos) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if(arrayPrincipal[pos-1].array == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if(arrayPrincipal[pos-1].tamanho + novotamanho < 1) return NOVO_TAMANHO_INVALIDO;

    int *temp = realloc(arrayPrincipal[pos-1].array, sizeof(int) * (arrayPrincipal[pos-1].tamanho + novotamanho));
    if(temp == NULL) return SEM_ESPACO_DE_MEMORIA;

    arrayPrincipal[pos-1].array = temp;
    arrayPrincipal[pos-1].tamanho += novotamanho;
    if(arrayPrincipal[pos-1].ultima > arrayPrincipal[pos-1].tamanho) arrayPrincipal[pos-1].ultima = arrayPrincipal[pos-1].tamanho;
    
    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)'
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    if(validarPos(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if(arrayPrincipal[posicao-1].array == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if(arrayPrincipal[posicao-1].ultima == 0) return ESTRUTURA_AUXILIAR_VAZIA;

    return arrayPrincipal[posicao-1].ultima;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    No *list = NULL;

    for(int i = 0; i < TAM; i++)
    {
        if(arrayPrincipal[i].array == NULL) continue;
        for(int j = 0; j < arrayPrincipal[i].ultima; j++)
        {
            if(list == NULL)
            {
                list = malloc(sizeof(No));
                list->conteudo = arrayPrincipal[i].array[j];
                list->prox = NULL;
            }
            else
            {
                No *listaP2 = list;
                No *newL = malloc(sizeof(No));
                if(listaP2 != NULL)
                {
                    while(listaP2->prox != NULL)
                    {
                        listaP2 = listaP2->prox;
                    }
                    newL->conteudo = arrayPrincipal[i].array[j];
                    newL->prox = NULL;
                    listaP2->prox = newL;
                }
                else
                {
                    newL->conteudo = arrayPrincipal[i].array[j];
                    newL->prox = NULL;
                    list = newL;
                }
            }

        }
    }
    return list;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *list, int vet[])
{
    No *listaP2 = list;
    int i = 0;

    while(listaP2 != NULL)
    {
        vet[i] = listaP2->conteudo;
        listaP2 = listaP2->prox;
        i++;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No *listaP2 = *inicio;
    No *aux;

    while(listaP2 != NULL)
    {
        aux = listaP2->prox;
        free(listaP2);
        listaP2 = aux;
    }
    *inicio = NULL;
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    for(int i = 0; i < TAM; i++)
    {
        if(arrayPrincipal[i].array != NULL)
        {
            free(arrayPrincipal[i].array);
            arrayPrincipal[i].array = NULL;
        }
    }
    free(arrayPrincipal);
    arrayPrincipal = NULL;
}
