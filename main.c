#include "./malloc.h" 
#include <stdio.h>

struct User {
	struct {
		char* nome;
		char* cpf;
	} Pessoa;
	int id;
};

int main(){
	struct User *user = malloc(sizeof(struct User));
	user->id = 19042007;
	user->Pessoa.nome = "Théo Minarini";
	user->Pessoa.cpf = "791847293847";
	printf("id = %d \nPessoa.nome = %s\nPessoa.cpf = %s", user->id, user->Pessoa.nome, user->Pessoa.cpf);
	return 0;
}
