#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

main (){
	
	setlocale(LC_ALL,"");
	int cont;
	int escpass=1;
	int str;
	int opc;
	int veic;
	int criar=0;
	int correto=0;
	int esc;
	int i,j,l,k,c=4; //Dimenções das matrizes
	int n02=20; //Tamanho maximo dos nomes dos veiculos
	int reg=0; //local de por o registro(numero da linha vazio na matriz)
	char nome[n02];
	char ***nomes;
	int **estat;
	float soma, pass;
	float dinheiro;
	system("color F0");
	
	//Inicia leitura do arquivo de veiculos
	FILE *fp;
	fp=fopen("veiculos.txt","r");
	if(fp==NULL){
		printf("Não foi possivel encontrar o arquivo \"veiculos.txt\"\n");
		printf("O arquivo sera criado novamente\n");
		system("pause");
		fp=fopen("veiculos.txt","w");
		fprintf(fp,"0");
		fclose(fp);
	}
	
	fscanf(fp,"%d",&reg);//reg recebe o numero de veiculos cadastrados

	
	//inicialização da matriz
	char **veiculos;

	veiculos = (char**) malloc((reg+20)*sizeof(char*));
	for(i=0;i<reg+5;i++){
		veiculos[i]=malloc(n02*sizeof(char));
	}

	
	//Carrega os veiculos na matriz
	if(reg!=0){
	for(i=0;i<reg;i++){
		fscanf(fp,"%s",veiculos[i]);
	}
	fclose(fp);
	}
	
	while(esc!=4){
		system("cls");
		printf("1-Cadastrar veículos\n");
		printf("2-Lista de veículos\n");
		printf("3-Selecionar veículo\n");
		printf("4-Encerrar Programa\n");
		printf("\nEscolha: ");
		scanf("%d", &esc);
		
		switch(esc){
			case 1:
				//Realocação de memoria da matriz com os veiculos
				//insiro os dados do novo veiculos na matriz
				
				printf("Nome do veiculo novo:");
				scanf("%s", veiculos[reg]);
				printf("Numero de fileiras:");
				scanf("%d", &l);
				printf("Valor passagem: ");
				scanf("%f", &pass);
				
				//Grava arquivos de lotação
				sprintf(nome,"%s.lot.txt",veiculos[reg]);
				fp=fopen(nome,"w");
				fprintf(fp,"%d %d\n",l,c);
				for(i=0;i<l;i++){
					for(j=0;j<c;j++){
						fprintf(fp,"0 ");
					}
					fprintf(fp,"\n");
				}
				fclose(fp);
				
				//Grava arquivos de nomes
				sprintf(nome,"%s.nomes.txt",veiculos[reg]);
				fp=fopen(nome,"w");
				fprintf(fp,"%d %d\n",l,c);
				for(i=0;i<l;i++){
					for(j=0;j<c;j++){
						fprintf(fp,"vazio ");
					}
				fprintf(fp,"\n");
				}
				fclose(fp);
				
				//Grava arquivos de estatisticas
				sprintf(nome,"%s.est.txt",veiculos[reg]);
				fp=fopen(nome,"w");
				fprintf(fp,"%d %d %f %f\n",l,c,pass,0);
				for(i=0;i<l;i++){
					for(j=0;j<c;j++){
						for(k=0;k<3;k++){
							fprintf(fp,"0 ");
						}
					}
				fprintf(fp,"\n");
				}
				fclose(fp);
				reg++;
				//Salva os novos dados no arquivo de texto
				printf("Arquivo gravado\n");
				fp=fopen("veiculos.txt","w");
				fprintf(fp,"%d\n",reg);
				for(i=0;i<reg;i++){
					fprintf(fp,"%s\n",veiculos[i]);
				}
				fclose(fp);
				system("color 2F");
				system("cls");
				printf("\nVeículo Cadastrado com sucesso!\n\n");
				system("pause");
				system("color F0");
			break;
			
			case 2:
				system("cls");
				for(i=0;i<reg;i++){
					printf("%d-%s\n",i+1,veiculos[i]);
				}
				if(reg==0){
					printf("Nenhum veículo cadastrado!");
				}
				printf("\n");
				system("pause");
			break;
			
			case 3:
				//selecionar veiculo
				system("cls");
				int corrt=0;
				while(corrt==0){
				printf("***Veículos***\n");
				for(i=0;i<reg;i++){
					printf("%d-%s\n",i+1,veiculos[i]);
				}
				printf("\nEscolha um veículo: ");
				scanf("%d", &veic);
				if(veic>0 && veic<=reg){
					corrt=1;
				}
				else{
					system("color 4F");
					system("cls");
					printf("\nPor favor escolha uma das opções!\n\n");
					system("pause");
					system("color F0");
					system("cls");
				}
				}
				//aloca e carrega as matrizes as matrizes
				
				//inicialização da matriz de lotação
				sprintf(nome,"%s.lot.txt",veiculos[veic-1]);
				fp=fopen(nome,"r");
				fscanf(fp,"%d", &l);
				fscanf(fp,"%d", &c);
				int **lot = (int**) calloc(l,sizeof(int*));
				for(i=0;i<l;i++){
					lot[i]=calloc(c,sizeof(int));
				}
				for(i=0;i<l;i++){
					for(j=0;j<c;j++){
						fscanf(fp,"%d",&lot[i][j]);
					}
				}
				fclose(fp);
				
				//inicialiação da matriz de nomes
				sprintf(nome,"%s.nomes.txt",veiculos[veic-1]);
				fp=fopen(nome,"r");
				fscanf(fp,"%d", &l);
				fscanf(fp,"%d", &c);
				nomes = (char***) calloc(l,sizeof(char**));
				
				for(i=0;i<l;i++){
					nomes[i]=calloc(c,sizeof(char*));
				}
				
				for(i=0;i<l;i++){
					for(j=0;j<c;j++){
						nomes[i][j]=calloc(n02,sizeof(char));
					}
				}
				for(i=0;i<l;i++){
					for(j=0;j<c;j++){
						fscanf(fp,"%s", nomes[i][j]);
					}
				}
				fclose(fp);
				
				//inicializção da matriz de estatisticas
				sprintf(nome,"%s.est.txt",veiculos[veic-1]);
				fp=fopen(nome,"r");
				fscanf(fp,"%d", &l);
				fscanf(fp,"%d", &c);
				fscanf(fp,"%f", &pass);
				fscanf(fp,"%f", &dinheiro);
				float ***estat = (float***) calloc(l,sizeof(float**));
				for(i=0;i<l;i++){
					estat[i]=calloc(c,sizeof(float*));
				}
				for(i=0;i<l;i++){
					for(j=0;j<c;j++){
						estat[i][j]=calloc(3,sizeof(float));
					}
				}
				for(i=0;i<l;i++){
					for(j=0;j<c;j++){
						for(k=0;k<3;k++){
							fscanf(fp,"%f",&estat[i][j][k]);
						}
					}
				}
				fclose(fp);
				
				int sair=0;
				
				while(sair!=6){	
					//impressão dos lugares
					
					system("cls");
					sprintf(nome,"%s.lot.txt",veiculos[veic-1]);
					fp=fopen(nome,"w");
					fprintf(fp,"%d %d\n",l,c);
					for(i=0;i<l;i++){
						for(j=0;j<c;j++){
							fprintf(fp,"%d ",lot[i][j]);
							printf("%d ",lot[i][j]);
							}
						fprintf(fp,"\n");
						printf("\n");
						}
					fclose(fp);

					printf("\n1-Embarque");
					printf("\n2-Desembarque");
					printf("\n3-Esvaziar veículo");
					printf("\n4-Ver estatísticas");
					printf("\n5-Ver passageiros");
					printf("\n6-Voltar ao menu anterior\n");
					printf("\nEscolha: ");
					scanf("%d", &sair);
					
					switch(sair){
						case 1:
								correto=1;
								escpass=1;
								int coor=0;
								printf("\n1-Inteira\n2-Meia\n\nEscolha: ");
								scanf("%d", &escpass);
								if(escpass==1 || escpass==2){
									correto=1;
								}
								else{
									correto=0;
									system("cls");
									system("color 4F");
									printf("Opção Invalida\n");
									system("pause");
									system("color F0");
								}
								if(correto==1){
								printf("\nFileira: ");
								scanf("%d", &i);
								i--;
								printf("Coluna: ");
								scanf("%d", &j);
								j--;
								if(i>=0 && i<l && j>=0 && j<c){
									correto=1;
								}
								else{
									system("cls");
									system("color 4F");
									printf("Esse assento não existe no veículo\n\n");
									system("pause");
									system("color F0");
									system("cls");
									correto=0;
								}
								if(correto==1){
									if(lot[i][j]==1){
										system("color 4F");
										system("cls");
										printf("Assento ocupado, por favor escolha outra!\n");
										system("pause");
										system("color F0");
										correto=0;
									}
									else{
										printf("\nNome: ");
										scanf("%s", nomes[i][j]);
										lot[i][j]=1;
										if(escpass==1){
											dinheiro=dinheiro+pass;
											estat[i][j][2]=estat[i][j][2]+pass;
											estat[i][j][0]++;
										}
										else{
											dinheiro=dinheiro+(pass/2);
											estat[i][j][2]=estat[i][j][2]+(pass/2);
											estat[i][j][1]++;
										}
										sprintf(nome,"%s.est.txt",veiculos[veic-1]);
										fp=fopen(nome,"w");
										fprintf(fp,"%d %d %f %f\n",l,c,pass,dinheiro);
										for(i=0;i<l;i++){
											for(j=0;j<c;j++){
												for(k=0;k<3;k++){
													fprintf(fp,"%f ",estat[i][j][k]);
												}
											}
										fprintf(fp,"\n");
										}
										fclose(fp);
										
										sprintf(nome,"%s.nomes.txt",veiculos[veic-1]);
										fp=fopen(nome,"w");
										fprintf(fp,"%d %d\n",l,c);
										for(i=0;i<l;i++){
											for(j=0;j<c;j++){
												fprintf(fp,"%s ", nomes[i][j]);
											}
										fprintf(fp,"\n");
										}
										fclose(fp);
										
										correto=1;
										system("color 2F");
										system("cls");
										printf("\nEmbarque Realizado com sucesso!\n\n");
										system("pause");
										system("color F0");
									}	
								}
							}
						break;
						
						case 2:
							correto=1;
							printf("\nFileira: ");
							scanf("%d", &i);
							i--;
							printf("Coluna:");
							scanf("%d", &j);
							j--;
							if(i>=0 && i<l && j>=0 && j<c){
								correto=1;
							}
							else{
								correto=0;
								system("cls");
								system("color 4F");
								printf("Esse assento não existe no veículo\n\n");
								system("pause");
								system("color F0");
							}
							if(correto==1){
							if(lot[i][j]==0){
								printf("\nO lugar já está vazio!\n");
								system("pause");
							}
							else{
								lot[i][j]=0;
								printf("O assento [%d][%d] foi desocupado!\n",i,j);
								system("pause");
								strcpy(nomes[i][j],"vazio");
								sprintf(nome,"%s.nomes.txt",veiculos[veic-1]);
									fp=fopen(nome,"w");
									fprintf(fp,"%d %d\n",l,c);
									for(i=0;i<l;i++){
										for(j=0;j<c;j++){
											fprintf(fp,"%s ", nomes[i][j]);
										}
									fprintf(fp,"\n");
									}
									fclose(fp);
							}
						}
						break;
						
						case 3:
							printf("\nTem certeza que deseja continuar?\n1-Sim\n2-Não\n\nEscolha: ");
							int kk;
							scanf("%d", &kk);
							if(kk==1){
								for(i=0;i<l;i++){
									for(j=0;j<c;j++){
										lot[i][j]=0;
									}
								}
								system("color 2F");
								system("cls");	
								printf("\nTodos os lugares foram esvaziados!\n");
								system("pause");
								system("color F0");
							}
							else{
								printf("Operação cancelada!\n");
								system("pause");
							}
						break;
						
						case 4:
							system("cls");
							float total=0;//Total de ocupação
							float meias=0;
							float inteiras=0;
							soma=0;
							for(i=0;i<l;i++){
								for(j=0;j<c;j++){
									soma = soma + estat[i][j][2];
									total = total + estat[i][j][0];
									total = total + estat[i][j][1];
									meias = meias + estat[i][j][1];
									inteiras = inteiras + estat[i][j][0];
								}
							}
							printf("Valor da passagem: R$ %.2f\n",pass);
							printf("Dinheiro arrecadado: R$ %.2f\n",soma);
							printf("Total de Meias Passagens: %.f\n",meias);
							printf("Total de Passagens Inteiras: %.f\n",inteiras);
							printf("\nQuantidade de Valor arrecadado...\n");
							
							printf("\n");
							for(i=0;i<l;i++){
								for(j=0;j<c;j++){
										printf("R$ %.2f    \t",estat[i][j][2]);
								}
								printf("\n");
							}
							printf("\nQuantidade de Meias Passagens\n\n");
							
							for(i=0;i<l;i++){
								for(j=0;j<c;j++){
										printf("%.f\t",estat[i][j][1]);
									
								}
								printf("\n");
							}
							
							printf("\nQuantidade de Passagens Inteiras\n\n");
							
							for(i=0;i<l;i++){
								for(j=0;j<c;j++){
										printf("%.f\t",estat[i][j][1]);
									
								}
								printf("\n");
							}
							
							system("pause");
						break;
						
						case 5:
							system("cls");
							soma=0;
							for(i=0;i<l;i++){
								for(j=0;j<c;j++){
									str=strcmp(nomes[i][j],"vazio");
									if(str!=0){
										printf("Assento [%d][%d]: %s\n",i+1,j+1,nomes[i][j]);
										soma++;	
									}
								}
							}
							if(soma==0){
								printf("Não há passageiros no veículo\n\n");
							}
							system("pause");
						break;
						
						case 6:
							
						break;
						
						default:
							system("color 4F");
							system("cls");
							printf("\nPor favor escolha uma das opções!\n\n");
							system("pause");
							system("color F0");
						break;
					}
				}
				
				//Desalocar matrizes
				for(i=0;i<l;i++){
					free(lot[i]);
				}
				free(lot);
				for(i=0;i<l;i++){
					for(j=0;j<c;j++){
						free(estat[i][j]);
					}
				}
				for(i=0;i<l;i++){
					free(estat[i]);
				}
				free(estat);
				for(i=0;i<l;i++){
					for(j=0;j<c;j++){
						free(nomes[i][j]);
					}
				}
				for(i=0;i<l;i++){
					free(nomes[i]);
				}
				free(nomes);	
			break;
			
			case 4:
				
			break;

			default:
				system("color 4F");
				system("cls");
				printf("\nPor favor escolha uma das opções!\n\n");
				system("pause");
				system("color F0");
			break;
		}
	}
	system("cls");
	printf("Programa finalizado...\n\n");
	system("pause");
}
