#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct imformation{
	char user_name[30];
	char password[20];
	int status;
}IMFORMATION;
typedef struct node{
	IMFORMATION imfor;
	struct node *next;
}NODE;
typedef struct list{
	NODE *head;
	NODE *tail;
}LIST;
void initialization(LIST *l){
	l->head=l->tail=NULL;
}
NODE * create_node(IMFORMATION imfor){
	NODE* new_node;
	new_node=(NODE*)malloc(sizeof(NODE));
	if(new_node==NULL){
		printf("fail\n");
	}
	else{
		new_node->imfor = imfor;
		new_node->next = NULL;
	}
	return new_node;
}
void add_node_tail(LIST* l, NODE* new_node){
	if(l->head==NULL){
		l->head = l->tail = new_node;
	}
	else{
		l->tail->next = new_node;
		l->tail = new_node;
	}
}
void print_list(LIST l){
	for(NODE* k = l.head; k!=NULL; k=k->next){
		printf("%20s%20s%20d\n", k->imfor.user_name, k->imfor.password, k->imfor.status);
	}
}
void remove_list(LIST* l){
	for(NODE* k = l->head; k!= NULL; k=k->next){
		l->head=l->head->next;
		free(k);
	}
}
float compare(LIST l, char user[], char pass[]){
	float result;
	for(NODE *k = l.head; k!=NULL; k=k->next){
		float m=strcmp(user,k->imfor.user_name);
		float n=strcmp(pass,k->imfor.password);
		if((m==0)&& (n==0)){
			result=0;
			break;
		}
		else if((m==0)&&(n!=0)){
			result =2;
			break;
		}
		else if((m!=0)&&(n==0)){
			result=1;
		}
		else if((m!=0)&&(n!=0)){
			result=3;
		}
	}
	return result;
}
void menu(){
	printf("\nUSER MANAGEMENT PROGRAM\n");
	printf("--------------------------------\n");
	printf("-1.Register                    -\n");
	printf("-2.Activate                    -\n");
	printf("-3.Sign in                     -\n");
	printf("-4.Search                      -\n");
	printf("-5.Change password             -\n");
	printf("-6.Sign out                    -\n");
	printf("--------------------------------\n");
}
int main(){
	LIST l;
	initialization(&l);
	int status_sign = 0;
	FILE *read_file = fopen("nguoidung.txt","r");
	while(!feof(read_file)){
		IMFORMATION imfor;
		if(fscanf(read_file,"%s %s %d\n",imfor.user_name, imfor.password, &imfor.status) != EOF){
			NODE *new_node = create_node(imfor);
			add_node_tail(&l,new_node);
		}
	}
	fclose(read_file);
	int choose;
	char current_user[35];
	do{
		menu();
		printf("Enter your choice:"); scanf("%d", &choose);
		if(choose==1){
			char user[35], pass[30];
			IMFORMATION imfor;
			printf("\nUser name:"); scanf("%s",user);
			printf("Password:"); scanf("%s",pass);
			float z=compare(l,user,pass);
			if(z==2 || z==0)
				printf("Account existed !");
			else if(z == 1 || z==3){
				FILE *write_file;
				write_file = fopen("nguoidung.txt","a");
				strcpy(imfor.user_name,user);
				strcpy(imfor.password,pass);
				imfor.status=2;
				NODE *new_node=create_node(imfor);
				add_node_tail(&l,new_node);
				fprintf(write_file,"%s %s %d\n", imfor.user_name, imfor.password, imfor.status);
				fclose(write_file);
				printf("Successful registration. Activation required.");
			}
			printf("\n");
		}
		else if(choose==2){
			char activation_code[20], user[35], pass[30];
			printf("Activate Account !\n");
			int confirm=0;
			while(confirm==0){
				printf("\nUser name:"); scanf("%s",user);
				printf("Password:"); scanf("%s",pass);
				float x = compare(l,user,pass);
				if(x==1 || x==2 || x==3){
					confirm = 0;
					printf("Enter the wrong account!-Retype-\n");
				}
				else if(x==0){
					int count=0;
					while(count < 5){
						printf("Enter your account activation code:"); scanf("%s",activation_code);
						float y=strcmp(activation_code,"LTM121216");
						if(y==0){
							FILE *write_file;
							write_file = fopen("nguoidung.txt","w");
							for(NODE *k=l.head; k!=NULL; k=k->next){
								if(strcmp(user,k->imfor.user_name)==0){
									k->imfor.status=1;
									break;
								}
							}
							for(NODE *k=l.head; k!=NULL; k=k->next){
								fprintf(write_file,"%s %s %d\n", k->imfor.user_name, k->imfor.password, k->imfor.status);
							}
							fclose(write_file);
							printf("Account is activated");
							count = 5;
						}
						else if(y != 0){
							count++;
							if(count<5){
								printf("Account is not activated");
							}
							if(count==5){
								printf("Activation codeis incorrect.Account is blocked");
								FILE *write_file;
								write_file = fopen("nguoidung.txt","w");
								for(NODE *k=l.head; k!=NULL; k=k->next){
									if(strcmp(user,k->imfor.user_name)==0){
										k->imfor.status=0;
										break;
									}
								}
								for(NODE *k=l.head; k!=NULL; k=k->next){
									fprintf(write_file,"%s %s %d\n", k->imfor.user_name, k->imfor.password, k->imfor.status);
								}
								fclose(write_file);
							}
						}
					}
					confirm = 1;
				}
			}
			printf("\n");
		}
		else if(choose==3){
			char user[35], pass[30];
			int confirm=0;
			printf("Sign in\n");
			while(confirm < 3){
				printf("\nUser name:"); scanf("%s",user);
				printf("Password:"); scanf("%s",pass);
				int x = compare(l,user,pass);
				if(x==0){
					printf("Hello %s",user);
					confirm = 3;
					status_sign = 1;
					strcpy(current_user,user);
				}
				else if(x==1 || x==3){
					printf("Cannot find account");
				}
				else if(x==2){
					printf("Password is incorrect");
					confirm ++;
					if(confirm==3){
						printf("\nPassword is incorrect. Account is blocked");
					}
				}
			}
			printf("\n");
		}
		else if(choose==4){
			if(status_sign==0){
				printf("\nYou are not logged in ! choose 3 to login!");
			}
			else if(status_sign==1){
				char user[35], status_account[30];
				int find, status;
				printf("Enter the name of the account you want to search:"); scanf("%s",user);
				for(NODE *k=l.head; k!=NULL; k=k->next){
					if(strcmp(user,k->imfor.user_name)==0){
						find=1;
						status=k->imfor.status;
						break;
					}
					else{
						find = 0;
					}
				}
				if(find==1){
					printf("\n%35s%30s\n","User","Status");
					if(status==0){
						strcpy(status_account,"Account is blocked");
					}
					else if(status==1){
						strcpy(status_account,"Account is active");
					}
					else if(status==2){
						strcpy(status_account,"Account is not activated");
					}
					status_account[strlen(status_account)]='\0';
					printf("%35s%30s\n",user,status_account);
				}
				else if(find==0){
					printf("\nCannot find account");
				}
			}
			printf("\n");
		}
		else if(choose==5){
			printf("\nChange password\n");
			if(status_sign==0){
				printf("You are not logged in ! choose 3 to login!");
			}
			else if(status_sign==1){
				char user[35], pass[20], new_pass[20];
				int status=0;
				while(status==0){
					printf("\nUser name:"); scanf("%s",user);
					float k1=strcmp(user,current_user);
					if(k1!=0){
						printf("\nCurrent username is incorrect .You cannot change someone else's password\n");
						printf("Please try again\n");
					}
					else if(k1==0){
						printf("Password:"); scanf("%s",pass);
						
						printf("New pass:"); scanf("%s",new_pass);
						int k = compare(l,user,pass);
						if(k==0){
							FILE *write_file;
							write_file = fopen("nguoidung.txt","w");
							for(NODE *k=l.head; k!=NULL; k=k->next){
								if(strcmp(user,k->imfor.user_name)==0){
									strcpy(k->imfor.password,new_pass);
									break;
								}
							}
							for(NODE *k=l.head; k!=NULL; k=k->next){
								fprintf(write_file,"%s %s %d\n", k->imfor.user_name, k->imfor.password, k->imfor.status);
							}
							fclose(write_file);
							status=1;
						}
						else if(k==2){
							printf("\nWrong old password\n");
							printf("Please try again\n");
						}						
					}
				}
			}
			printf("\n");
		}
		else if(choose==6){
			int status=0;
			char user[30];
			if(status_sign==0){
				printf("You are not logged in ! choose 3 to login!");
			}
			else if(status_sign==1){
				while(status==0){
					printf("\nUser name:"); scanf("%s",user);
					float j=strcmp(user,current_user);
					int h;
					for(NODE *k=l.head; k!=NULL; k=k->next){
						if(strcmp(user,k->imfor.user_name)==0){
							h=1;
							break;
						}
						else{
							h=0;
						}
					}
					if(j==0&&h==1){
						printf("\nGoodbye %s",user);
						status=1;
						status_sign=0;
					}
					else if(j!=0){
						printf("\nAccount %s is not sign in. Your current account name is:%s", user, current_user);
					}
					else if(h== 0)
						printf("\nCannot find account");
				}
			}
			printf("\n");
		}
	}while(choose <=6);
	remove_list(&l);
	return 0;
}