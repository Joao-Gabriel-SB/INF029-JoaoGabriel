#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

typedef struct{
	int capacidade;
	int ocupado;
	int* inicio;
}estruturaFixa;

estruturaFixa* vetorPrincipal[TAM];

int sort(int vet[], int tam){
	
	int i,j,menor;
	int aux;

	for( i = 0; i < tam - 1; i++ ){
	
		menor = i;
		for( j = i+1; j < tam; j++)
			if( vet[menor] > vet[j] ){
				menor = j;
		}
		
		if( menor != i ){
			aux = vet[i];
			vet[i] = vet[menor];
			vet[menor] = aux;	
		}
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
int criarEstruturaAuxiliar(int posicao, int tamanho){

    int retorno = 0;

	 // se posição é um valor válido {entre 1 e 10}
	 if( posicao < 1 || posicao > 10 )
    	retorno = POSICAO_INVALIDA;
	 
    // a posicao pode já existir estrutura auxiliar
	 else if( vetorPrincipal[posicao -1] )
	 			if( vetorPrincipal[posicao - 1]->inicio )
    				retorno = JA_TEM_ESTRUTURA_AUXILIAR;
	
    // o tamanho ser muito grande
	 else if( tamanho > 10 )
    	retorno = SEM_ESPACO_DE_MEMORIA;

    // o tamanho nao pode ser menor que 1
	 else if( tamanho < 1 )
    	retorno = TAMANHO_INVALIDO;

    // deu tudo certo, crie
	 else{
	 	
	 	vetorPrincipal[posicao - 1]->inicio = malloc(tamanho * sizeof(int));

		if(!vetorPrincipal[posicao - 1]->inicio)
			printf("falha ao alocar memória");
		else {
			vetorPrincipal[posicao-1]->capacidade = tamanho;
			retorno = SUCESSO;
		}
	 }
//	 printf("%d: ",retorno);
    return retorno;
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
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;
	 int index;

	 if( vetorPrincipal[posicao -1] )
		 if( vetorPrincipal[posicao - 1]->inicio )
		 	existeEstruturaAuxiliar = 1;	

	 if( posicao < 1 || posicao > 10 )
	 	posicao_invalida = 1;
	 
	if( vetorPrincipal[posicao - 1] )
		if( vetorPrincipal[posicao - 1]-> ocupado < vetorPrincipal[posicao - 1]-> capacidade )
			temEspaco = 1;

    if (posicao_invalida)
        retorno = POSICAO_INVALIDA;
    else{
        // testar se existe a estrutura auxiliar
        if (existeEstruturaAuxiliar)
        {
            if (temEspaco)
            {
                //insere
					 index = vetorPrincipal[posicao-1]->ocupado;
					 vetorPrincipal[posicao-1]->inicio[index] = valor;
					 vetorPrincipal[posicao-1]->ocupado++;
                retorno = SUCESSO;
            }
            else{
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
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
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    int retorno = 0;

	 if( posicao < 1 || posicao > 10 )
	 		retorno = POSICAO_INVALIDA;
	
	 else if( vetorPrincipal[posicao-1] ){
		
	 	if( vetorPrincipal[posicao-1]->inicio ){
	 		if( vetorPrincipal[posicao-1]->ocupado == 0 )
				retorno = ESTRUTURA_AUXILIAR_VAZIA;
			else{

				vetorPrincipal[posicao-1]->ocupado--;

				retorno = SUCESSO;		
			}
				
	 	}else{
			retorno = SEM_ESTRUTURA_AUXILIAR;
	 	}
	}

//	printf("%d: ",vetorPrincipal[posicao-1]->ocupado);		
	return retorno;

}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia -
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar -
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar -

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor){
	 
    int retorno = 0;
	 int achou = 0; 
	 int aux;

	 if( posicao > 0 && posicao < 10){

		estruturaFixa *atual = vetorPrincipal[posicao-1];
	 	retorno = POSICAO_INVALIDA;

	 	if( atual ){
	 	
		 	if( atual->inicio ){

				if( atual->ocupado == 0 ){
					retorno = ESTRUTURA_AUXILIAR_VAZIA;
				}else {

					for( int i = 0; i < atual->ocupado; i++ ){
						if( atual->inicio[i] == valor ){
							achou = 1; aux = i; break; 
						}
						if(!achou) break;
					}

					if(!achou){ 
						retorno = NUMERO_INEXISTENTE;
					}else{
						
						if( aux - atual->ocupado == 1 ){
							atual->ocupado--;
							retorno = SUCESSO;
						}else{

							while( aux < atual->ocupado-1 ){

								atual->inicio[aux] = atual->inicio[aux + 1];	
								aux++;
							}
							atual->inicio[aux] = valor;
							atual->ocupado--;
							retorno = SUCESSO;
						}	
					}
				}
							
			}else retorno = SEM_ESTRUTURA_AUXILIAR;
  	 	}
	 }else retorno = POSICAO_INVALIDA;

    return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
	 
    int retorno = 0;

	 if( ehPosicaoValida(posicao) == SUCESSO ){

		estruturaFixa *atual = vetorPrincipal[posicao-1]; 

	 	if( atual ){
	 		if( atual->inicio ){
				for(int i = 0; i < atual->ocupado;i++)
					vetorAux[i] = atual->inicio[i];
				retorno = SUCESSO;
			}else retorno = SEM_ESTRUTURA_AUXILIAR;
		}
	}else retorno = POSICAO_INVALIDA;
    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{

    int retorno = 0;

	 if( retorno = ehPosicaoValida(posicao) == SUCESSO){

	 	estruturaFixa *atual = vetorPrincipal[posicao-1]; 

	 	if( atual ){
	 		if( atual->inicio ){
				for(int i = 0; i < atual->ocupado;i++)
					vetorAux[i] = atual->inicio[i];
				sort( vetorAux, atual->ocupado );
				retorno = SUCESSO;
			}else retorno = SEM_ESTRUTURA_AUXILIAR;
		}
	 }else retorno = POSICAO_INVALIDA;
    
    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
	 int vazias = 0;
	 int j = 0;

	 for( int i = 0; i < 10; i++ ){

	 		if( vetorPrincipal[i] ){
	 			if( vetorPrincipal[i]->inicio ){
					if( vetorPrincipal[i]->ocupado == 0 ){
						vazias++;
					}else{

						for( int k = 0; k < vetorPrincipal[i]->ocupado; k++,j++)
							vetorAux[j] = vetorPrincipal[i]->inicio[k];
						retorno = SUCESSO;

					}
				}else vazias++;
			}
	 }

	 if(vazias == 10){
		
		retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
	 }

    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{

    int retorno = 0;
	 int vazias = 0;
	 int qtTotal = 0;
	 int j = 0;
	 
	 for( int i = 0; i < 10; i++ ){

	 	if( vetorPrincipal[i] ){
	 		if( vetorPrincipal[i]->inicio ){
				if( vetorPrincipal[i]->ocupado == 0 ){
						vazias++;
				}else{
					for(int k = 0; k < vetorPrincipal[i]->ocupado;k++,j++)
						vetorAux[j] = vetorPrincipal[i]->inicio[k];
					sort( vetorAux, vetorPrincipal[i]->ocupado );
					qtTotal += vetorPrincipal[i]->ocupado;
					retorno = SUCESSO;
				}
			}else vazias++;
		}
	 }
	
	 if(vazias == 10)
		retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
	 else{
	 	sort(vetorAux,qtTotal);
	 }
    return retorno;
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
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    int retorno = 0;
	 int *backup;

	 if( ehPosicaoValida(posicao) == SUCESSO){

		estruturaFixa *atual = vetorPrincipal[posicao - 1];
		int tamanhoFinal = atual->capacidade + novoTamanho;

		if ( tamanhoFinal < 1 )
			retorno = NOVO_TAMANHO_INVALIDO;
	 	else if( atual ) 

			if( atual->inicio ){

				backup = (int*) realloc( atual->inicio, tamanhoFinal * sizeof(int));

			if(backup){
				atual->inicio = backup;
				atual->capacidade = tamanhoFinal;
					if( atual->ocupado > atual->capacidade )
						atual->ocupado = atual->capacidade;
				retorno = SUCESSO;
         }else retorno = SEM_ESPACO_DE_MEMORIA;

		}else retorno = SEM_ESTRUTURA_AUXILIAR;

	 }else retorno = POSICAO_INVALIDA;
	
    return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{

    int retorno = 0;
	 
	 if( ehPosicaoValida(posicao) == SUCESSO ){

		estruturaFixa *atual = vetorPrincipal[ posicao - 1 ];
	
	 	if( atual ){

			if( atual->inicio ){

				if( atual-> ocupado == 0)
					retorno = ESTRUTURA_AUXILIAR_VAZIA;
				else	retorno = atual->ocupado;

			}else retorno = SEM_ESTRUTURA_AUXILIAR;
		
		}

	 }else retorno = POSICAO_INVALIDA;
	
    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote(){

    No *head = (No*)malloc(sizeof(No));
    No *retorno;
    int qtdElementos = 0;
    
    head->prox = NULL;
    head->conteudo = 0;
    No *ultimo = head;

    for( int i = 0; i < TAM; i++){

	if( vetorPrincipal[i] ){	
	   if( vetorPrincipal[i]->inicio ){

	      for( int j = 0; j < vetorPrincipal[i]->ocupado; j++ ){

		  No *novo = (No*)malloc(sizeof(No));
		  if(!novo) return head;
		  novo->conteudo = vetorPrincipal[i]->inicio[j];
 	          novo->prox = NULL;

		  ultimo->prox = novo;
		  ultimo = novo;
		  head->conteudo++;

	        }

	      }
         }
       retorno = head;
    }

    if( !head->prox ) retorno = NULL;
    return retorno;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]){

	No *aux = inicio->prox;

	for( int i = 0; i < inicio->conteudo; i++ ){

		vetorAux[i] = aux->conteudo;
		aux = aux->prox;

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

	No *atual = *inicio;
	No *proximo;

	while(atual){

		proximo = atual->prox;
		free(atual);
		atual = proximo;
	}

	*inicio = NULL;

}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar(){

	for( int i = 0; i < TAM; i++){
		vetorPrincipal[i] = (estruturaFixa*) malloc(sizeof(estruturaFixa));
	
		if(vetorPrincipal[i]){
			vetorPrincipal[i]->capacidade = 0;
			vetorPrincipal[i]->ocupado = 0;
			vetorPrincipal[i]->inicio = NULL;
		}else{
			printf("\tfalhou!\n");
		}
	}
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{

	for(int i = 0; i < TAM; i++){

		if( vetorPrincipal[i] ){

			if( vetorPrincipal[i]->inicio ){
				free(vetorPrincipal[i]->inicio);
				vetorPrincipal[i]->inicio = NULL;
			}
		}
	
		free(vetorPrincipal[i]);
		vetorPrincipal[i] = NULL;	
	}
}




