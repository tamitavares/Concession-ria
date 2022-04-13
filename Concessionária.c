#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>


/*Grupo 11
Gabriela Rocha da Silva - RA 211152
Márcio Soares de Oliveira Filho - 200026
Mateus Martins Freitas - RA 210498
Tamiris Tavares Lemes - RA 210216*/

//struct e union concessionária
typedef struct endereco { 
 char logradouro[80]; 
 char bairro[15]; 
 char CEP[10]; 
 char cidade[15]; 
 char estado[3]; 
 char fone[12]; 
 char email[40]; 
}endereco; 
 
 
typedef struct infocarro { 
 char sigla; 
 int regcarro; 
}infocarro; 
 
 
typedef union dadoscarro { 
 char sigla; 
 struct infocarro reservado; 
}dadoscarro; 
 
 
typedef struct loja { 
 int regloja; //gerar automático 
 char nome[30]; 
 char CNPJ[19]; 
 struct endereco end; 
 int sold; 
 int reserved; 
 union  dadoscarro  tabela[3]; 
}loja;

//structs union carros
typedef struct infoloja { 
 char sigla; 
 char CNPJ[19]; 
}infoloja; 
 
typedef union dadosloja { 
 char sigla; 
 struct infoloja reserva; 
}dadosloja; 
 
typedef struct montadora { 
 int regcarro; //gerar automático 
 char modelo[20]; 
 char cor[10]; 
 float  valor; 
 union dadosloja status; 
}montadora;  


//structs e union historico
typedef struct data{ 
int dia;  
int mes;  
int ano;  
}data; 
 
typedef struct historicoVendas{ 
int reghist; 
int regcarro; 
char modelo[20]; 
char cor[10]; 
float valor;  
int regloja; 
char nome[30]; 
char cnpj[19]; 
struct data dataVenda; 
}historicoVendas; 

//funções da concessionária
void alocaLoja(loja **p, int tam);
int verifica();
void grava(loja *p);
void cadastroConcessionaria(loja *p, int qtde);
void mostratotal(loja *p, int qtde);
void alterarCadastroCon(loja *p, char *pcon);
char verificacnpj(loja *p, char *pcon);

//funções dos carros
void alocaCar(montadora **p, int tam);
int verificaCar();
void gravaCar(montadora *p);
void cadastroCar(montadora *p, int qtde);
void mostraCar(montadora *p, int qtde);
void alterarCadastroCar(montadora *p, int qtde);
char consultaTotal(montadora *p, int qtde);
char consultaPs(montadora *p, int qtde, char status);
char consultaPm(montadora *p, char *pm);

//funções de reserva
void carrosD(montadora *p);
void carrosV(loja *p, montadora *pm, char *pcon);
int verificacnpjCar(loja *p, char *pcon);
void reservarVeic(loja *p, montadora *pm, int nreg, char *pcon);
void liberarVeic(loja *p, montadora *pm, int nreg, char *pcon);
void comprarVeic(loja *p, montadora *pm, int nreg, char *pcon);
int verificaVeic(montadora *p,int reg);
int verificaVeicTermino(montadora *p,int reg);

void grava2(loja *p, char *str, int pos);
void gravaCar2(montadora *p, char *str, int pos);
int busca(loja *p, char *pcon);
int busca_vago(montadora *p, int qreg);
int buscaCar(montadora *p, int pcon);

//funções historico
void alocaHis(historicoVendas **p, int tam);
void gravaHis(historicoVendas *p);
void cadastroHistorico(historicoVendas *pv, loja *pl, montadora *pm, int nreg, char *pcon, int dia, int mes, int ano);
int verificaHis();
void gravaHis(historicoVendas *p);
void mostraHis(historicoVendas *p);
void comprarVeicSemAltera(loja *p, montadora *pm, int nreg, char *pcon);



int main(){	

setlocale(LC_ALL, "portuguese");
loja *pl=NULL;
montadora *pm=NULL;
historicoVendas *pv=NULL;
char *pmodelo=NULL;
char *pconsulta=NULL;
char op, opr, opconsult, consulta[19], modelo[20], status, opcompra, opcomp, opsim;
int opcao=0, opcao2=0, qtde, qtdeCar, nreg, opParcial, comp=0, reg, cnpj, vend, dia, mes, ano, sucessoReserva;
pconsulta=&consulta[19];
pmodelo=&modelo[20];
int j;

alocaLoja(&pl, 1);
alocaCar(&pm, 1);
alocaHis(&pv, 1);
qtde=verifica();
qtdeCar=verificaCar();


do{
system("cls");
printf("\nMenu:\n[1]Cadastro Concessionária\n[2]Consulta Concessionária\n[3]Cadastro de Carros\n[4]Consulta Carro\n[5]Reservar Carro\n[6]Terminar Reserva\n[7]Consultar Histórico de Vendas\n[8]Alteração de Cadastro\n[9]Saída\n\n");
scanf("%i", &opcao);
fflush(stdin);

switch (opcao){
	
	case 1:	    if(qtde>4){
				  system("cls");
				  printf("\nFoi atingido o número máximo de cadastros!\n");
				  system("pause");
				  op='N';
			    }//limite max
			    else{
				do{
					cadastroConcessionaria(pl,qtde+1);
					qtde++;
					do{
					printf("\nDeseja continuar <S/N>: ");
					scanf("%c", &op);
					fflush(stdin);
					op = toupper(op);
				}while(op!='S' && op!='N');
					mostratotal(pl, qtde);
					if(qtde>4){
						system("cls");
				  		printf("\nFoi atingido o número máximo de cadastros!\n");
				  		system("pause");
				  		op='N';
			        }//if			    	
			    }while(op!='n' && op!='N');
			    }//else
				break;
			
	case 2:     do{
					system("cls");
					printf("\nDigite o CNPJ da empresa para consultar: ");
					scanf("%s", pconsulta);
					fflush(stdin);
					verificacnpj(pl, pconsulta);
					do{
					printf("\n\nDeseja continuar <S/N>: ");
					scanf("%c", &op);
					fflush(stdin);
					op = toupper(op);
				    }while(op!='S' && op!='N');
					
				}while(op!='n' && op!='N');
				break;
				
	case 3:    if(qtdeCar>49){
					system("cls");
				  	printf("\nFoi atingido o número máximo de cadastros!\n");
				  	system("pause");
				  	op='N';
			    }//carro limite
			    else{
				do{
				   	cadastroCar(pm, qtdeCar+1);
				   	qtdeCar++;
				   	do{
				   	printf("\nDeseja continuar <S/N>: ");		
	               	scanf("%c", &op);
	               	fflush(stdin);
	               	op = toupper(op);
					}while(op!='S' && op!='N');
	            	mostraCar(pm, qtdeCar);
	               if(qtdeCar>49){
	             	system("cls");
	             	printf("\nFoi atingido o número máximo de cadastros!\n");
				  	system("pause");
				  	op='N';
				 	}//if	
	            }while(op!='n' && op!='N');
	            }//else
				break;
	
	case 4:   do{
				system("cls");
				printf("\tOpção de Consulta:");
				printf("\n\n[1]Consulta Total\n[2]Consulta Parcial\n[3]Saída\n\n");
				scanf("%c",&opcao2);
				fflush(stdin);
				switch (opcao2){
					case '1':   system("cls");
					            printf("\tConsulta Total:\n");
								consultaTotal(pm, qtdeCar);
								system("pause");
								break;
					
					case '2':   do{		
								system("cls");
								printf("\tConsulta Parcial:");
								printf("\n[1]Status\n[2]Modelo\n");
								scanf("%i", &opParcial);
								fflush(stdin);
								if(opParcial==1){								
								do{
									
									printf("\n\nDigite o status procurado: [r - reservado] [l - livre] ");;
									scanf("%c",&opconsult);
									fflush(stdin);
									opconsult=tolower(opconsult);
									if(opconsult!='r' && opconsult!='l')
										printf("\nStatus procurado não encontrado, digite novamente\n");
								}while(opconsult!='r' && opconsult!='l');
								
								switch(opconsult){
									case 'r': system("cls");
											  printf("\tConsulta por status");
											  status='R';
											  consultaPs(pm,qtdeCar,status);
											  printf("\n\n");
											  system("pause");
											  break;
											  
									case 'l': system("cls");
											  printf("\tConsulta por status");
											  status='L';
											  consultaPs(pm,qtdeCar,status);
											  printf("\n\n");
											  system("pause");
											  break;
								}//switch
								}//if
								else if(opParcial==2){									
											  system("cls");
											  printf("\tConsulta por modelo");
											  printf("\n\nDigite o modelo procurado: ");
											  scanf("%s", pmodelo);
											  fflush(stdin);
											  consultaPm(pm, pmodelo);
											  printf("\n\n");
											  system("pause");
											  break;
								}//else
							}while(opParcial!=1 && opParcial!=2);
						    break;
						
				}//switch opcao
				
				}while(opcao2!='3');
				break;
				
	case 5:   do{
					sucessoReserva = 0;
					system("cls");
					printf("\tReserva de veículo");
					printf("\n\nDigite o CNPJ da empresa: ");
					gets(pconsulta);
					fflush(stdin);
					
					/*--------inicio da reserva--------*/
					
					//veriica se cnpj é correto
					if(verificacnpjCar(pl, pconsulta)==7){
						system("cls");
						do{
							printf("\tReserva de veículo");
						 	system("cls");
						 	printf("\nDeseja verificar os veículos livres? S/N:  ");
						 	scanf("%c", &opsim);
						 	fflush(stdin);
						 	opsim = toupper(opsim);
					 	}while(opsim!='S' && opsim!='N');
					 	if(opsim == 'S'){
					 		printf("\tVeículos livres:");
					 		carrosD(pm);
					 		printf("\n\n");
					 		system("pause");
						}//carros disponiveis
						system("cls");
						printf("\tReserva de veículo");
						printf("\n\nNúmero de registro do veículo desejado: ");
						scanf("%i",&nreg);
						fflush(stdin);
						
					if(verificaVeic(pm,nreg)==1){
						system("cls");
						reservarVeic(pl,pm,nreg-1,pconsulta);
						printf("\tReserva de veículo");
						printf("\n\nVeículo reservado com sucesso!\n\n");
						sucessoReserva = 1;
						do{
							printf("Deseja reservar mais um?<S/N>\n");
							scanf("%c",&op);
							fflush(stdin);
							op = toupper(op);
						}while(op!='S' && op!='N');
					}//if verifica veiculo
					
					//veiculo nao disponivel
					else{
						system("cls");
						printf("\tReserva de veículo");
						printf("\n\nO veículo procurado não está disponível!\n");
						do{
							printf("Deseja tentar novamente?<S/N>\n");
							scanf("%c",&op);
							fflush(stdin);
							op = toupper(op);
						}while(op!='S' && op!='N');
						system("pause");
						}//else
					}//if verifica cnpj carro
				
					//caso tenha 3 cadastros
					else if(verificacnpjCar(pl, pconsulta)==8){
						system("cls");
						printf("\tReserva de veículo");
						printf("\n\nEssa empresa já registrou três veiculos\n");
						system("pause");
					}//ja registrou o max
							//caso nao esteja registrado
					else{
						system("cls");
						printf("\tReserva de veículo");
						printf("\n\nEsse CNPJ não está registrado no sistema!\n");
						do{
							printf("\nDeseja tentar novamente?<S/N>\n");
							scanf("%c",&op);
							fflush(stdin);
							op = toupper(op);
						}while(op!='N' && op!='S');
					}//else
				 system("cls");		
				
					/*--------fim da reserva--------*/
					if(sucessoReserva == 1){
						do{
							printf("\nDeseja realizar a compra ou liberação de um veículo? <S/N>:  ");
							scanf("%c", &opcompra);
							fflush(stdin);
							opcompra=toupper(opcompra);
						}while(opcompra!='S' && opcompra!='N');
						if(opcompra=='S')
							vend=0;
						else
							vend=1;
		
						while(vend==0){
							if(opcompra!='N'){
								printf("\tVeículos reservados:");
								carrosV(pl, pm, pconsulta);
							
								printf("\n\n");
								system("pause");
							}//carros disponiveis
										 
							printf("\n\n\tVerificação se será comprado ou liberado da reserva:\n");
							//comprado
							do{	
							printf("\n[1]Comprar\n[2]Liberar\n\n");
							scanf("%i", &comp);
							fflush(stdin);
							}while(comp!=1 && comp!=2);
									
							//continuacao
						
							if(comp==1 || comp==2){
								printf("\nRegistro do carro a realizar a ação: ");
								scanf("%i", &reg);
								fflush(stdin);
								if(comp==1){
								
									comprarVeicSemAltera(pl,pm,reg-1,pconsulta);
									printf("\n\tData:");
									printf("\n\nDia: ");
									scanf("%i", &dia);
									printf("\nMês: ");
									scanf("%i", &mes);
									printf("\nAno: ");
									scanf("%i", &ano);
								
									cadastroHistorico(pv, pl, pm, reg-1, pconsulta, dia, mes, ano);
									system("cls");
									printf("\n\t\tHistorico de Vendas:\n");
									mostraHis(pv);
									system("pause");
									comprarVeic(pl,pm,reg-1,pconsulta);
								}//comprado
								else if(comp==2){
									liberarVeic(pl,pm,reg-1,pconsulta);
								}//liberado
							}//if
							system("cls");
							verificacnpj(pl, pconsulta);
							printf("\n\n");
							system("pause");
							vend=1;
						
							}//while
				
						do{
							printf("Deseja voltar ao menu principal?<S/N>\n");
							scanf("%c",&op);
							fflush(stdin);
							op = toupper(op);
						}while(op!='N' && op!='S');
						if(op=='S')
							break;
			}
			}while(op!='n' && op!='N');
			break;
	case 6:
		 do{
					system("cls");
					printf("\tFinalização da Reserva de veículo");
					printf("\n\nDigite o CNPJ da empresa: ");
					gets(pconsulta);
					fflush(stdin);					
					
					//veriica se cnpj é correto
					if(verificacnpjCar(pl, pconsulta)==7){
						system("cls");
						printf("\tVeículos reservados:");
						carrosV(pl, pm, pconsulta);
						printf("\n\n");
						system("pause");
						printf("\n\nNúmero de registro do veículo desejado: ");
						scanf("%i",&nreg);
						fflush(stdin);
						
						if(verificaVeicTermino(pm,nreg)==1){
							system("cls");
							printf("\nEste veículo não está reservado\n");
							do{
								printf("Deseja finalizar mais uma reserva?<S/N>\n");
								scanf("%c",&op);
								fflush(stdin);
								op = toupper(op);
							}while(op!='S' && op!='N');
						}//if verifica veiculo

						else if(verificaVeicTermino(pm,nreg)==0){
							system("cls");
							printf("\n\nVeículo não foi encontrado\n");
							do{
								printf("Deseja tentar novamente?<S/N>\n");
								scanf("%c",&op);
								fflush(stdin);
								op = toupper(op);
							}while(op!='S' && op!='N');
							system("pause");
							}//else
							else{
								do{	
									printf("\n[1]Comprar\n[2]Liberar\n\n");
									scanf("%i", &comp);
									fflush(stdin);
								}while(comp!=1 && comp!=2);
							}
							
						if(comp==1 || comp==2){

								if(comp==1){
								
									comprarVeicSemAltera(pl,pm,nreg-1,pconsulta);
									printf("\n\tData:");
									printf("\n\nDia: ");
									scanf("%i", &dia);
									printf("\nMês: ");
									scanf("%i", &mes);
									printf("\nAno: ");
									scanf("%i", &ano);
								
									cadastroHistorico(pv, pl, pm, nreg-1, pconsulta, dia, mes, ano);
									system("cls");
									printf("\n\t\tHistorico de Vendas:\n");
									mostraHis(pv);
									system("pause");
									comprarVeic(pl,pm,nreg-1,pconsulta);
								}//comprado
								else if(comp==2){
									liberarVeic(pl,pm,nreg-1,pconsulta);
								}//liberado
							}//if
							
							system("cls");
							verificacnpj(pl, pconsulta);
							printf("\n\n");
							system("pause");
							vend=1;
							do{
								printf("Deseja voltar ao menu principal?<S/N>\n");
								scanf("%c",&op);
								fflush(stdin);
								op = toupper(op);
							}while(op!='N' && op!='S');
						if(op=='S')
							break; 
					}//if verifica cnpj carro
					else{
						system("cls");
						printf("\n\nEsse CNPJ não está registrado no sistema!\n");
						do{
							printf("\nDeseja tentar novamente?<S/N>\n");
							scanf("%c",&op);
							fflush(stdin);
							op = toupper(op);
						}while(op!='N' && op!='S');
						
					}//else
				 system("cls");							
			
			}while(op!='n' && op!='N');
		break;			
	case 7:	system("cls");
			printf("\n\t\tHistórico de Vendas:\n");
			mostraHis(pv);
			system("pause");
			break;
				
	case 8:
		do{
			system("cls");
			printf("\tAlteração de Cadastro\n");
			printf("Deseja alterar o cadastro de um carro ou de uma concessionária?\n[1]Carro\n[2]Concessionária\n");
			scanf("%i", &comp);	
			fflush(stdin);
			switch(comp){
				case 1:
					
					system("cls");
					printf("\tAlteração de Cadastro de Carro\n");
					consultaTotal(pm, qtde);
					alterarCadastroCar(pm, qtde);
					break;
				case 2:
					
					system("cls");
					mostratotal(pl, qtde);
					printf("\tAlteração de Cadastro de Concessionária\n");
					printf("\n\nDigite o CNPJ da empresa: ");
					gets(pconsulta);
					fflush(stdin);
					alterarCadastroCon(pl, pconsulta);
					
					break;
			}
		}
		while(comp!=1 && comp!=2);
		
		 do{
				system("cls");
				printf("Deseja voltar ao menu principal?<S/N>\n");
				scanf("%c",&op);
				fflush(stdin);
			}while(op!='s' && op!='S');
		break;
	
}//switch opcao
}while(opcao!=9);
system("cls");
return 0;
}//main


//funções concessionária

void alocaLoja(loja **p, int tam){
	if((*p=(loja*)realloc(*p, tam*sizeof(loja)))==NULL)
		exit(1);
}//alocaLoja

int verifica(){
	long int cont=0;
	FILE *fptr=NULL;
	if((fptr=fopen("concessionaria.bin","rb"))==NULL)
		return cont;
	else{
		fseek(fptr,0,2);
		cont=ftell(fptr)/sizeof(loja);
		fclose(fptr);
		return cont;
	}//else
}//verifica

void grava(loja *p){
	FILE *fptr=NULL;
	if((fptr=fopen("concessionaria.bin", "ab"))==NULL)  
		printf("\nErro ao abrir o arquivo");
	else{
		fwrite(p, sizeof(loja), 1, fptr);
	}
	fclose(fptr); 
}//grava

void cadastroConcessionaria(struct loja *p,int qtde){
	int i;
	system("cls");
	p->regloja=qtde;
	printf("\nRegistro: %i", p->regloja);
	printf("\nNome: ");
	gets(p->nome);
	fflush(stdin);
	printf("\nCNPJ: ");
	gets(p->CNPJ);
	fflush(stdin);
	printf("\n\nCadastro do Endereço \n");
	printf("\nLogradouro: ");
	gets(p->end.logradouro);
	fflush(stdin);
	printf("\nBairro: ");
	gets(p->end.bairro);
	fflush(stdin);
	printf("\nCEP: ");
	gets(p->end.CEP);
	fflush(stdin);
	printf("\nCidade: ");
	gets(p->end.cidade);
	fflush(stdin);
	printf("\nEstado: ");
	gets(p->end.estado);
	for(i=0; i<2; i++){
		if(*(p->end.estado)>=97 && *(p->end.estado)<=122)
			*(p->end.estado)-=32;
	}//for maiuscula
	printf("\nFone: ");
	gets(p->end.fone);
	fflush(stdin);
	printf("\nEmail: ");
	gets(p->end.email);
	fflush(stdin);
	p->sold=0;
	p->reserved=0;
	p->tabela[0].sigla='L';
	p->tabela[1].sigla='L';
	p->tabela[2].sigla='L';
	grava(p);
}//cadastro

void mostratotal(loja *p, int qtde){
int i;
FILE *fptr=NULL;
system("cls");
if((fptr=fopen("concessionaria.bin", "rb"))==NULL)
  printf("\nErro ao abrir o arquivo");
else{
	for(i=0;i<qtde;i++){
	 	fseek(fptr,i*sizeof(loja),0);
	 	fread(p,sizeof(loja),1,fptr);
	 	printf("\nRegistro: %i\nNome: %s\nCNPJ: %s\nSold: %i\nTabela 0: %c\nTabela 1: %c\nTabela 2: %c\n\n",p->regloja,p->nome,p->CNPJ,p->sold,p->tabela[0].sigla,p->tabela[1].sigla,p->tabela[2].sigla);
	 }//for
	 fclose(fptr);
}//else
system("pause");
}//mostra

char verificacnpj(loja *p, char *pcon){
	int aux, i, a, nao=0, sim=0;
	FILE *fptr=NULL;
	aux=verifica();
	
	if((fptr=fopen("concessionaria.bin","rb"))==NULL)
		printf("\nErro");
		
	else{
		for(i=0; i<aux; i++){
			fseek(fptr, i*sizeof(loja),0);
			fread(p, sizeof(loja), 1, fptr);
			
			if(strcmp(p->CNPJ, pcon)==0){
				sim=1;
				printf("\n\tNome\t\tSold\t\tReserved\tTabela 0\tTabela 1\tTabela 2\n\t%s\t\t%i\t\t%i\t\t%c\t\t%c\t\t%c",p->nome,p->sold,p->reserved,p->tabela[0].sigla, p->tabela[1].sigla, p->tabela[2].sigla);
			}
			else{
				nao=1;
			}
		}//for
		
		if(nao==1 && sim!=1){
			printf("\nNão há registro dessa empresa.\n");
		}
		
		fclose(fptr);
	}//else
	
}//verificacnpj


//funções carro

void alocaCar(montadora **p,int tam){
	if((*p=(montadora*)realloc(*p, tam*sizeof(montadora)))==NULL)
		exit(1);
}//aloca_car

int verificaCar(){
	long int cont=0;
	FILE *fptr=NULL;

	if((fptr=fopen("carro.bin","rb"))==NULL)
		return cont;
	else{
  		fseek(fptr,0,2);
  		cont=ftell(fptr)/sizeof(montadora);
  		fclose(fptr);
  		return cont;
	}//else
}//verifica carro

void gravaCar(montadora *p){
FILE *fptr=NULL;
if((fptr=fopen("carro.bin","ab"))==NULL)
 printf("\nErro ao abrir o arquivo");
else
  fwrite(p,sizeof(montadora),1,fptr);
fclose(fptr);
}//grava carro

void cadastroCar(montadora *p, int qtde){
	system("cls");
	int ind, qreg;
	qreg=verificaCar();
	ind=busca_vago(p,qtde-1);
/*	printf("\nNumero: %i\n", ind);
	printf("\nQreg: %i\n", qreg+1);*/
	
	if(ind!=-1)
		p->regcarro=ind+1;
	else
		p->regcarro=qreg+1;
	
	printf("\nRegistro: %i", p->regcarro);
	printf("\nModelo: ");
	gets(p->modelo);
	fflush(stdin);
	printf("\nCor: ");
	gets(p->cor);
	fflush(stdin);
	printf("\nValor: ");
	scanf("%f",&(p->valor));
	fflush(stdin);
	p->status.sigla='L';
	if(ind==-1)  //nao ha vago
		gravaCar(p);
	else
		gravaCar2(p, "rb+", ind);
}//cadastroCar

void mostraCar(montadora *p, int qtde){
	int qreg;
	qreg=verificaCar();
	int i;
	FILE *fptr=NULL;
	system("cls");
	if((fptr=fopen("carro.bin", "rb"))==NULL)
  	printf("\nErro ao abrir o arquivo");
	else{
	for(i=0;i<qreg;i++){
	 	fseek(fptr,i*sizeof(montadora),0);
	 	fread(p,sizeof(montadora),1,fptr);
	 	printf("\nRegistro: %i\nModelo: %s\nCor: %s\nValor: %.2f\nStatus: %c\n\n",p->regcarro,p->modelo,p->cor,p->valor,p->status.sigla);
	 }//for
	 fclose(fptr);
	}//else
	system("pause");
	
}//mostraCar

char consultaTotal(montadora *p, int qtde){
	FILE *fptr=NULL;
	int qreg;
	qreg=verificaCar();
	int i;
	if((fptr=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
	else{
  		printf("\n\tRegistro\tModelo\t\tCor\t\tValor\t\tStatus");
  		for(i=0;i<qtde;i++){
 	 		fseek(fptr,i*sizeof(montadora),0);
  	 		fread(p,sizeof(montadora),1,fptr);
  	 		printf("\n\t%i\t\t%s\t\t%s\t\t%.2f\t\t%c",p->regcarro,p->modelo,p->cor,p->valor,p->status.sigla);
		}//for
	printf("\n\n");
   	fclose(fptr);;
  }//else
}//consulta total

char consultaPs(montadora *p,int qtde,char status){
	FILE *fptr=NULL;
	int i;
	int qreg;
	qreg=verificaCar();
	if((fptr=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
	else{
  		printf("\n\tRegistro\tModelo\t\tCor\t\tValor\t\tStatus");
  		for(i=0;i<qreg;i++){
  			fseek(fptr,i*sizeof(montadora),0);
  	 		fread(p,sizeof(montadora),1,fptr);
  			if(p->status.sigla==status)
  				if(p->valor!=0)
  		 			printf("\n\t%i\t\t%s\t\t%s\t\t%.2f\t\t%c",p->regcarro,p->modelo,p->cor,p->valor,p->status.sigla);	
  		}//for
	fclose(fptr);
  }//else
}//consulta p status

char consultaPm(montadora *p, char *pmo){
	FILE *fptr=NULL;
	int i,aux, sim=0, nao=0;
	aux=verificaCar();
	if((fptr=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
	else{
  		
  		for(i=0;i<aux;i++){
  			
  			fseek(fptr, i*sizeof(montadora),0);
			fread(p, sizeof(montadora), 1, fptr);
			
			if(strcmp(p->modelo, pmo)==0){
				sim=1;
				printf("\n\tRegistro\tModelo\t\tCor\t\tValor\t\tStatus");
				printf("\n\t%i\t\t%s\t\t%s\t\t%.2f\t\t%c",p->regcarro,p->modelo,p->cor,p->valor,p->status.sigla);
			}
			else{
				nao=1;
			}
		}//for
		
		if(nao==1 && sim!=1){
			printf("\nNão há registro dessa empresa.\n");
		}
		
		fclose(fptr);
  		
  }//else
}//consulta p modelo

//funções de reserva

void carrosD(montadora *p){
	FILE *fptr=NULL;
	int i,aux;
	aux=verificaCar();

	if((fptr=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
	else{
  		printf("\n\tRegistro\tModelo\t\tCor\t\tValor\t\tStatus");
  		for(i=0;i<aux;i++){
  			fseek(fptr,i*sizeof(montadora),0);
  	 		fread(p,sizeof(montadora),1,fptr);
  	 		if(p->status.sigla=='L')
  	 			if(p->valor!=0)
  	  				printf("\n\t%i\t\t%s\t\t%s\t\t%.2f\t\t%c",p->regcarro,p->modelo,p->cor,p->valor,p->status.sigla);	
    	}//for
	fclose(fptr);
  }//else
}//carros disponiveis


void carrosV(loja *p, montadora *pm, char *pcon){
	FILE *fptr=NULL;
	int i,aux, pos;
	aux=verificaCar();
	pos=busca(p, pcon);

	if((fptr=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
	else{
  		printf("\n\tRegistro\tModelo\t\tCor\t\tValor\t\tStatus");
  		for(i=0;i<aux;i++){
  			fseek(fptr,i*sizeof(montadora),0);
  	 		fread(pm,sizeof(montadora),1,fptr);
  	 		
  	 		if(strcmp(p->CNPJ, pm->status.reserva.CNPJ)==0)
			   if(pm->status.sigla=='R')
  	  				printf("\n\t%i\t\t%s\t\t%s\t\t%.2f\t\t%c",pm->regcarro,pm->modelo,pm->cor,pm->valor,pm->status.sigla);	
    	}//for
	fclose(fptr);
  }//else
}//carros vagos


int verificacnpjCar(loja *p, char *pcon){
	int aux,i, pos;
	FILE *fptr=NULL;
	aux=verifica();
	pos=busca(p, pcon);

		if(pos==-1)
			printf("\nRegistro invalido\n\n");
		else{
			if(p->reserved>=3)
				return 8;
			
			else
				return 7;
	}//else
}//verifica cnpj carro

void reservarVeic(loja *p, montadora *pm, int nreg, char *pcon){
	FILE *fptr=NULL;
	int i, aux, pos;
	aux=verifica();
	pos=busca(p, pcon);
	
	
	if(pos==-1)
			printf("\nRegistro invalido\n\n");
		else{
			p->reserved++;
			
			if(p->reserved==1){
  					if(p->tabela[0].reservado.sigla=='L'){
  						p->tabela[0].reservado.sigla='R';
  						p->tabela[0].reservado.regcarro=nreg;
					}
				}
  			else if(p->reserved==2){
  					if(p->tabela[1].reservado.sigla=='L'){
  						p->tabela[1].reservado.sigla='R';
  						p->tabela[1].reservado.regcarro=nreg;
					}
				}
			else if(p->reserved==3){
  					if(p->tabela[2].reservado.sigla=='L'){
  						p->tabela[2].reservado.sigla='R';
  						p->tabela[2].reservado.regcarro=nreg;
					}
				}
			}//else
	
		pm->status.sigla='R';
		strcpy(pm->status.reserva.CNPJ, p->CNPJ);
  	  		
  		grava2(p, "rb+", pos);
    	gravaCar2(pm, "rb+", nreg);
			
	
}//reservar veiculo


void liberarVeic(loja *p, montadora *pm, int nreg, char *pcon){
	FILE *fptr=NULL;
	int i, pos, posCar;
	
	pos=busca(p, pcon);
	posCar=buscaCar(pm, nreg+1);
	system("pause");
	
	if(pos==-1)
			printf("\nRegistro invalido\n\n");
	else{
		p->reserved--;
		
		if(nreg==p->tabela[0].reservado.regcarro){
			if(p->tabela[0].reservado.sigla=='R')
  				p->tabela[0].reservado.sigla='L';
		}//if
		else if(nreg==p->tabela[1].reservado.regcarro){
			if(p->tabela[1].reservado.sigla=='R')
  				p->tabela[1].reservado.sigla='L';
		}//if
		else if(nreg==p->tabela[2].reservado.regcarro){
			if(p->tabela[2].reservado.sigla=='R')
  				p->tabela[2].reservado.sigla='L';
		}//if
		}
		grava2(p, "rb+", pos);
        pm->status.sigla='L';
        pm->regcarro=nreg+1;
        strcpy(pm->status.reserva.CNPJ, p->CNPJ);
        gravaCar2(pm, "rb+", posCar);

}//reservar veiculo


void comprarVeic(loja *p, montadora *pm, int nreg, char *pcon){
	FILE *fptr=NULL;
	int i, pos, posCar;
	
	pos=busca(p, pcon);
	posCar=buscaCar(pm, nreg+1);
	
	if(pos==-1)
			printf("\nRegistro invalido\n\n");
	else{
		p->reserved--;
		p->sold++;
		
		if(p->tabela[0].reservado.regcarro==nreg){
			if(p->tabela[0].reservado.sigla=='R')
  				p->tabela[0].reservado.sigla='L';
		}//if
		else if(p->tabela[1].reservado.regcarro==nreg){
			if(p->tabela[1].reservado.sigla=='R')
  				p->tabela[1].reservado.sigla='L';
		}//if
		else if(p->tabela[2].reservado.regcarro==nreg){
			if(p->tabela[2].reservado.sigla=='R')
  				p->tabela[2].reservado.sigla='L';
		}//if
		}
		
		grava2(p, "rb+", pos);
			  	
  	  	strcpy(pm->cor, "vago");
  	  	strcpy(pm->modelo, "vago");
  	  	
		pm->valor=0;		

        pm->status.sigla='L';
        pm->regcarro=nreg+1;
        strcpy(pm->status.reserva.CNPJ, p->CNPJ);
        gravaCar2(pm, "rb+", posCar);

}//comprar veiculo


int verificaVeic(montadora *p,int reg){
	FILE *fptr=NULL;
	if((fptr=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
	else{
  		fseek(fptr,(reg-1)*sizeof(struct montadora),0);
  		fread(p,sizeof(struct montadora),1,fptr);
  		if(p->status.sigla=='L')
  			return 1;	
  		else
  			return 0;
	fclose(fptr);
}//else
}//verifica veiculo
int verificaVeicTermino(montadora *p,int reg){
	FILE *fptr=NULL;
	if((fptr=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
	else{
  		fseek(fptr,(reg-1)*sizeof(struct montadora),0);
  		fread(p,sizeof(struct montadora),1,fptr);
  		if(p->status.sigla=='L')
  			return 1;	
  		else if(p->status.sigla=='R')
  			return 2;
  		else
  			return 0;
	fclose(fptr);
}//else
}//verifica veiculo

void grava2(loja *p, char *str, int pos){
	FILE *fptr=NULL;
	if((fptr=fopen("concessionaria.bin", str))==NULL)
		printf("\nErro ao abrir o arquivo");
	else{
		if(strcmp(str,"rb+")==0)  //compara string
			fseek(fptr, pos*sizeof(loja), 0);
			fwrite(p,sizeof(loja),1,fptr);
	}//else
	fclose(fptr);
}//grava


void gravaCar2(montadora *p, char *str, int pos){
	FILE *fptr=NULL;
	if((fptr=fopen("carro.bin", str))==NULL)
		printf("\nErro ao abrir o arquivo");
	else{
		if(strcmp(str,"rb+")==0)  //compara string
			fseek(fptr, pos*sizeof(montadora), 0);
			fwrite(p,sizeof(montadora),1,fptr);
	}//else		
fclose(fptr);
}//grava car


int busca(loja *p, char *pcon){
	FILE *fptr=NULL;
	int qreg, achou=-1, i;
	qreg=verifica();
	system("cls");
	if((fptr=fopen("concessionaria.bin", "rb"))==NULL)
		printf("\nErro");
	else{
		for(i=0; i<qreg; i++){
			fseek(fptr, i*sizeof(loja), 0);  //a partir de zero
			fread(p, sizeof(loja), 1, fptr);
			
			if(strcmp(p->CNPJ, pcon)==0){
				achou=i;
				i=qreg;  //forcar saida do for
			}//if
			else
				achou=-1;	
		}//for
		fclose(fptr);
	}//else	
	return achou; //posicao do registro
}//busca


int busca_vago(montadora *p, int qreg){
	FILE *fptr=NULL;
	int achou=-1, i;
	system("cls");
	if((fptr=fopen("carro.bin", "rb"))==NULL)
		return achou; 
	else{
		for(i=0; i<qreg; i++){
			fseek(fptr, i*sizeof(montadora), 0);  //a partir de zero
			fread(p, sizeof(montadora), 1, fptr);
			if(p->valor==0){  //achou vago
				achou=i;  //pos do reg vago
				i=qreg;  //forcar saida do for
				
			}//if
		}//for
		fclose(fptr);
		
	}//else	
	return achou; //posicao do registro
}//busca_vago

int buscaCar(montadora *p, int pcon){
	FILE *fptr=NULL;
	int qreg, achou=-1, i;
	qreg=verificaCar();
	system("cls");
	if((fptr=fopen("carro.bin", "rb"))==NULL)
		printf("\nErro");
	else{
		for(i=0; i<qreg; i++){
			fseek(fptr, i*sizeof(montadora), 0);  //a partir de zero
			fread(p, sizeof(montadora), 1, fptr);
			
			if(p->regcarro==pcon){
				achou=i;
				i=qreg;  //forcar saida do for
			}//if
			else
				achou=-1;	
		}//for
		fclose(fptr);
	}//else	
	return achou; //posicao do registro
}//busca

void alterarCadastroCon(loja *p, char *pcon){
	int pos, i, esc, qreg, vend=0, veri=0;
	char op;
	
	qreg=verifica();
			
				
					if(verificacnpjCar(p, pcon)==7){
							veri=1;
							pos=busca(p, pcon);
							mostratotal(p, qreg);
							if(pos==-1){
								printf("\nRegistro invalido\n\n");
								system("pause");
							}
							else{
									system("cls");
									mostratotal(p, qreg);
									
									printf("\nCaso deseje manter o mesmo, digite novamente!\n");
									printf("\nNome: ");
									gets(p->nome);
									fflush(stdin);
									printf("\nNova CNPJ: ");
									gets(p->CNPJ);
									fflush(stdin);
									
								grava2(p, "rb+", pos);
								printf("\nAlterado com sucesso!\n\n");
							
						}
						
					}
					
	

		system("pause");

}//alterarcadastrocon

void alterarCadastroCar(montadora *p, int qtde){
	int pos, i, nreg, esc, qreg;
	
	system("cls");
	qreg=verificaCar();

	consultaTotal(p, qreg);
	system("pause");
	system("cls");
	printf("\nDigite o número de registo do carro que deseja alterar:\n");
	scanf("%i", &nreg);	
	system("cls");
	fflush(stdin);
	pos=buscaCar(p, nreg);
	
	if(pos==-1){
		printf("\nRegistro invalido\n\n");
	}
	else{
		consultaTotal(p, qreg);
		printf("\nCaso deseje manter o mesmo, digite novamente!\n");
								printf("\nNovo Modelo: ");
								gets(p->modelo);
								fflush(stdin);
								
								printf("\nNova Cor: ");
								gets(p->cor);
								fflush(stdin);
								
								printf("\nNovo valor: ");
								scanf("%f", &p->valor);
								fflush(stdin);
		p->regcarro=nreg;						
		gravaCar2(p, "rb+", pos);
		printf("\nAlterado com sucesso!\n\n");
		
		system("pause");
	}//else
}//alterarcadastrocar

//funcoes historico

void alocaHis(historicoVendas **p, int tam){
	if((*p=(historicoVendas*)realloc(*p, tam*sizeof(historicoVendas)))==NULL)
		exit(1);
}//alocaLoja

void cadastroHistorico(historicoVendas *pv, loja *pl, montadora *pm, int nreg, char *pcon, int dia, int mes, int ano){
	int i, pos, posCar, qreg;
	system("cls");
	
	pv->dataVenda.dia=dia;
	pv->dataVenda.mes=mes;
	pv->dataVenda.ano=ano;
	
	qreg=verificaHis();
	
	pv->reghist=qreg+1;
	printf("\nregHis: %i", pv->reghist);

	pv->regcarro=pm->regcarro;
	strcpy(pv->modelo, pm->modelo);
	strcpy(pv->cor, pm->cor);
	pv->valor=pm->valor;
	
	//loja
	pv->regloja=pl->regloja;
	strcpy(pv->nome, pl->nome);
	strcpy(pv->cnpj, pl->CNPJ);
			
	gravaHis(pv);							
}//cadastro

int verificaHis(){
	long int cont=0;
	FILE *fptr=NULL;
	if((fptr=fopen("historico.bin","rb"))==NULL)
		return cont;
	else{
		fseek(fptr,0,2);
		cont=ftell(fptr)/sizeof(historicoVendas);
		fclose(fptr);
		return cont;
	}//else
}//verifica

void gravaHis(historicoVendas *p){
FILE *fptr=NULL;
if((fptr=fopen("historico.bin","ab"))==NULL)
 printf("\nErro ao abrir o arquivo");
else
  fwrite(p,sizeof(historicoVendas),1,fptr);
fclose(fptr);
}//grava his

void mostraHis(historicoVendas *p){
	FILE *fptr=NULL;
	int qreg;
	qreg=verificaHis();
	int i;
	if((fptr=fopen("historico.bin","rb"))==NULL)
		printf("\nErro");
	else{
  		printf("\n\tregHis\tregCar\tModelo\tCor\t  Valor\t   regLoja\tNome\tCNPJ\t\tdataVenda");
  		for(i=0;i<qreg;i++){
 	 		fseek(fptr,i*sizeof(historicoVendas),0);
  	 		fread(p,sizeof(historicoVendas),1,fptr);
  	 		printf("\n\t%i\t%i\t%s\t%s\t%.2f\t%i\t%s\t%s\t\t%i/%i/%i",p->reghist,p->regcarro,p->modelo,p->cor,p->valor,p->regloja,p->nome,p->cnpj,p->dataVenda.dia,p->dataVenda.mes,p->dataVenda.ano);
		}//for
	printf("\n\n");
   	fclose(fptr);;
   }
}//mostraCar

void comprarVeicSemAltera(loja *p, montadora *pm, int nreg, char *pcon){
	FILE *fptr=NULL;
	int i, pos, posCar;
	
	pos=busca(p, pcon);
	posCar=buscaCar(pm, nreg+1);
	grava2(p, "rb+", pos);
    gravaCar2(pm, "rb+", posCar);

}//comprar veiculo


