// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: João Gabriel de Santana Bispo
//  email: joao_gabriel_bispo@hotmail.com
//  Matrícula:20242160011@ifba.edu.br
//  Semestre:2025.1

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JoaoBispo.h" // Substitua pelo seu arquivo de header renomeado

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

void extrairDMA( char data[], char dia[], char mes[], char ano[]){

	int i,j;

	for( i=0; data[i] != '/'; i++){
		dia[i] = data[i];
	}dia[i] = '\0';

	for( j=0, i=i+1; data[i] != '/'; i++, j++){
		mes[j] = data[i];
	}mes[j] = '\0';

	for( j=0, i=i+1; data[i] != '\0'; i++, j++){
		ano[j] = data[i];
	}ano[j] = '\0';

}

int dataToInt(char data[], int op){

	int i,j;
	int dia = 0, mes = 0, ano = 0;
	char sdia[3],smes[3], sano[5];

	for( i=0; data[i] != '/'; i++){
		sdia[i] = data[i];
	}sdia[i] = '\0';

	for( j=0, i=i+1; data[i] != '/'; i++, j++){
		smes[j] = data[i];
	}smes[j] = '\0';

	for( j=0, i=i+1; data[i] != '\0'; i++, j++){
		sano[j] = data[i];
	}sano[j] = '\0';

	for(i = 0, j = 10; sdia[i] != '\0'; i++, j /= 10){
		if(strlen(sdia) > 1){dia = dia + (sdia[i] - 48) * j;}
		else{dia = dia + (sdia[i] - 48) * j/10;}
	}
	for(i = 0, j = 10; smes[i] != '\0'; i++, j /= 10){
		if(strlen(smes) >1){mes = mes + (smes[i] - 48) * j;}
		else{mes = mes +(smes[i] - 48)* j/10;}
	}
	for(i = 0, j = 1000; sano[i] != '\0'; i++, j /= 10){
		if(strlen(sano) >2){ano = ano + (sano[i] - 48) * j;}
		else{ano = ano + (sano[i] - 48) * j/100;}
	}if(strlen(sano) == 2)ano = ano+2000;

	switch(op){
		case 1: return dia;
		case 2: return mes;
		case 3: return ano;
		default: return 0;
	}
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
	int datavalida = 1;
	int i, j;
	int isBissexto = 0;
	int dia = 0, mes = 0, ano = 0;
	char sDia[3],sMes[3],sAno[5];
	//quebrar a string data em strings sDia, sMes, sAno

	
	dia = dataToInt(data,1);
	mes = dataToInt(data,2);
	ano = dataToInt(data,3);

	/*
	printf("%d\n", dia);
	printf("%d\n", mes);
	printf("%d\n", ano);
	*/

	if( (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0) ){
		isBissexto = 1;
	}

	datavalida = ano > 0 ? 1 : 0;
	if(datavalida)
		datavalida = mes > 0 && mes < 12 ? 1 : 0;

	if(datavalida)
		if( mes == 1  || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
			datavalida = dia > 0 && dia <= 31 ? 1 : 0;
		}else{
			datavalida = dia > 0 && dia < 31 ? 1 : 0;
		}


	if(datavalida)
		if(mes == 2){
			if( isBissexto ){
				datavalida = dia > 0 && dia <= 29 ? 1 : 0;
			}else{
				datavalida = dia > 0 && dia < 29 ? 1 : 0;			
			}
		}

	if (datavalida)
   	return 1;
	else
   	return 0;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */


DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;
	 char diaI[3],mesI[3],anoI[5],diaF[3],mesF[3],anoF[5];
	 int intdiaI, intmesI, intanoI, intdiaF, intmesF, intanoF;
	 long int intInicio = 0, intFinal = 0;
	 int i, j;


    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{
      //verifique se a data final não é menor que a data inicial
		intdiaI = dataToInt(datainicial, 1);
		intmesI = dataToInt(datainicial, 2);
		intanoI = dataToInt(datainicial, 3);
		intdiaF = dataToInt(datafinal, 1);
		intmesF = dataToInt(datafinal, 2);
		intanoF = dataToInt(datafinal, 3);

		intInicio = intanoI * 10000 + intmesI * 100 + intdiaI;
		intFinal = intanoF * 10000 + intmesF * 100 + intdiaF;

		if(intInicio > intFinal){
			dma.retorno = 4;
			return dma;		
		}

		/*
		printf("%s\n",datainicial);
		printf("%ld\n",intInicio);
		printf("%ld\n",intFinal);*/
      //calcule a distancia entre as datas

      dma.qtdAnos = intanoF - intanoI;
		dma.qtdMeses = intmesF - intmesI;
			if(dma.qtdMeses < 0){
				dma.qtdAnos--;
				dma.qtdMeses += 12;
			}
		dma.qtdDias = intdiaF - intdiaI;
			if(dma.qtdDias < 0){
				dma.qtdMeses--;
				if( dma.qtdMeses == 1  || dma.qtdMeses == 3 || dma.qtdMeses == 5 || dma.qtdMeses == 7 || dma.qtdMeses == 8 || dma.qtdMeses == 10 || dma.qtdMeses == 12){
					dma.qtdDias += 31; 
				}else if(dma.qtdMeses == 4 || dma.qtdMeses == 6 || dma.qtdMeses == 9 || dma.qtdMeses == 11){
					dma.qtdDias += 30;
				}else{
					if((intanoF % 4 == 0 && intanoF % 100 != 0) || (intanoF % 400 == 0))
						dma.qtdDias += 29;
					else
						dma.qtdDias += 28;
				}
			}
      //se tudo der certo
      dma.retorno = 1;
      return dma;
      
    }
    
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
	 int i;
	 char copia[250];

	for(i=0; texto[i]!='\0';i++){
		copia[i] = texto[i];	
	}copia[i] = '\0';
	for(i = 0; copia[i] != '\0'; i++){
		if(copia[i] >= 'A' && copia[i] <= 'Z'){
			copia[i] = copia[i] + 32;
		}
	}

	if(isCaseSensitive){

		 for(int i = 0; texto[i] != '\0'; i++){
		 	if(c == texto[i])
				qtdOcorrencias++;
		 }		

	}else{

		if(c >= 'A' && c <= 'Z')
			c = c+32;
		for(int i = 0; copia[i] != '\0'; i++){
		 	if(c == copia[i])
				qtdOcorrencias++;
		 }	
	
	}


    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
   int qtdOcorrencias = 0;
	int letrasIguais;
	int inicio,fim,acento = 0;
	int i,j,k;
	int qtd=0;
	for(i=0; strTexto[i]!='\0'; i++){
		if( strTexto[i] == -61)
			acento++;
		//printf("%c: %d\n",strTexto[i],strTexto[i]);

		letrasIguais = 0;
		if(strTexto[i] == strBusca[0]){
			letrasIguais++;
		
		//printf("i:%d j:%d\n",i,j);
			inicio = i+1;
			for(j=i+1,k=1; strTexto[j] == strBusca[k];j++,k++){

				letrasIguais++;
/*
				printf("t:%c\n",strTexto[j]);
				printf("b:%c\n",strBusca[k]);
*/				
			}
			fim = j;
		}
		
//		printf("lt:%d\n",letrasIguais);
		if(letrasIguais == strlen(strBusca)){
			qtdOcorrencias++;
			posicoes[qtd] = inicio-acento;
			posicoes[qtd+1] = fim-acento;
			printf("in:%d f:%d\n",posicoes[qtd],posicoes[qtd+1]);
			qtd+=2;
		}

//		printf("occ: %d\n",qtdOcorrencias);
	}
	
   return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
	int aux = 0,s = 0;
	//printf("nmr:%d\n",num);
	while(num!=0){		
			aux = num%10;
			num = num/10;
			s = s*10 + aux;
	}
	//printf("inv:%d\n",s);
	num = s;
   return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
	 int aux = 0,copia=numerobase, copiaBusca=numerobusca;
	 int digitosBase = 0;
	 int digitosBusca = 0;
	 int i,j,k,s=0;

	 while(copiaBusca!=0){
		 aux = copiaBusca%10;
		 copiaBusca /= 10; 
		 digitosBusca++;
	 }
	
	 while(copia!=0){
		 aux = copia%10;
		 copia /= 10; 
		 digitosBase++;
	 }int vetBase[digitosBase];

	 copia=numerobase;
	 for(i=0;copia!=0;i++){
		 aux = copia%10;
		 copia /= 10; 
		 vetBase[i] = aux;
	 }

	 for(i=digitosBase; i>0; i--){
		s=0;
		for(j = i-1, k=0; k<digitosBusca && j>=0;k++, j--){
			
			s= s*10 + vetBase[j];
			
		}
	 		if(s == numerobusca) qtdOcorrencias++;
		//printf("%d",vetBase[i]);
	 }
    /*printf("nmr:  %d\n",numerobase);
	 printf("busca:%d\n",numerobusca);
	 printf("occ:  %d\n",qtdOcorrencias);*/
    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5])
 {
     int achou;
     return achou;
 }



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  	char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}
