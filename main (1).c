#include <stdio.h>
#include <string.h>
#include <time.h>

struct info {
	char *id;
	char *nome;
	};

int main(){
	
	FILE *arquivo;
	FILE *output;
	FILE *database;
	FILE *log;
    struct tm *data_hora_atual;
	struct info user_info;
	char id[8];
	char nome[50];
	char line[500];
	char key[8] = "A";
	char file_path[50];
	char c;
	int key_ascii;
	int c_ascii;
	int i= 0;
	int access;
	int mode=2;
	time_t segundos;
	
	time(&segundos);
	data_hora_atual = localtime(&segundos);
	
	database = fopen("database.csv", "r");
	if(database==NULL) {
		printf("Nao foi possivel acessar o banco de dados...");
		return 0;
		}
		
	log = fopen("log.csv", "a");
	if(log==NULL) {
		printf("Nao foi possivel acessar o log de eventos...");
		return 0;
		}
		
	printf("Digite um id valido \n");
	gets(id);
	
	while(fgets(line, sizeof(line), database)) {
		char *token;
		
		token = strtok(line, ",");
		user_info.id = token;
		
		token = strtok(NULL, ",");
		user_info.nome = token;
		
		if(strcmp(user_info.id, id)==0) {
			printf("ID validado! Bem vindo(a) %s \n", user_info.nome);
			access = 1;
			break;
		}
	}
	
	if(access==1) {
			printf("Deseja usar o modo de criptografia (1) ou descriptografia(2) \n");
			scanf("%d", &mode);
			fflush(stdin);
			
			printf("Digite o caminho do arquivo...");
			gets(file_path);
			
			arquivo = fopen(file_path, "r");
			if(arquivo==NULL) {
				printf("O arquivo nao pode ser aberto...");
				return 0;
			}
			
			printf("Digite o caminho de saida do arquivo...");
			gets(file_path);
			
			output = fopen(file_path, "w");
			if(output==NULL) {
				printf("O arquivo de saida nao pode ser criado...");
				return 0;
			}
			
			if(mode==1) {
				
				printf("Digite a chave de criptografia... \n");
				gets(key);
				
				while((c=fgetc(arquivo)) != EOF) {
					
					c_ascii = c;
					if(c_ascii>32){
						
						key_ascii=key[i];
						
						if(c_ascii+key_ascii<127) {
							c_ascii= c_ascii+key_ascii;
						}
						
						else {
							c_ascii = c_ascii+key_ascii-93;
						}
						c = c_ascii;
						i++;
						}
	
						
						if(i==8){
							i = 0;
						}
						
					
					printf("%c", c);
					fputc(c, output);
						
				
						
							
				}	
			}
			
			if(mode==2) {
				
				printf("Digite a chave de descriptografia... \n");
				gets(key);
				
				
				while((c=fgetc(arquivo)) != EOF) {
					
					c_ascii = c;
					if(c_ascii>32){
						key_ascii=key[i];
						
						if(key_ascii+33<=c_ascii) {
							c_ascii = c_ascii-key_ascii;
						}
						
						else {
							c_ascii= c_ascii-key_ascii+93;
						}
							
						i++;
				}
					printf("%c", c_ascii);
					fputc(c_ascii, output);
					
					
					if(i==8) {
						i=0;
					}
						
							
				}	
			}
		}
		
	else {
		printf("Login invalido...");
		return 0;
	}
	fprintf(log,"%s,%s,%d/%d/%d,%d:%d:%d,%s", user_info.id, key, data_hora_atual->tm_mday, data_hora_atual->tm_mon+1, data_hora_atual->tm_year+1900, data_hora_atual->tm_hour, data_hora_atual->tm_min, data_hora_atual->tm_sec, user_info.nome);
	fclose(log);
	fclose(arquivo);
	fclose(database);
	fclose(output);
	return 0;
	}
