
/*
 *   UNIFESP SJC
 *
 *   PROGRAMAÇÃO CONCORRENTE E DISTRIBUÍDA
 *   Manna-Pnueli - (Cliente-Servidor)
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1

/* NÚMERO DE THREADS: */
#define NUM_THREADS 4

int request = 0;
int respond = 0;
int sum = 0;

/* FLAG DE CONTROLE DA REGIÃO CRÍTICA */
int synchronization;

typedef struct {
	pthread_t t;
	int id;
} thread_t;

void critical_section(int id) {
	
	int local = sum;
	sleep(rand() % 2);
	sum = local + 1;
	
	printf("Thread Cliente: %d | SOMA: %d\n", id, sum);
}

void *client(void *args) {
	
	int id = *(int *)args;
	while (TRUE) {
		
		/* CONTROLE DA REGIÃO CRÍTICA */
		if (synchronization) while (respond != id) request = id;
			
		/* SECÇÃO CRÍTICA */
		critical_section(id);
			
		respond = 0;
	}
}

void *server(void *args) {
	
	int id = *(int *)args;
	while (TRUE) {
		
		while (request == 0);
		respond = request;
		
		while (respond != 0);
		request = 0;
	}
}

void create_threads(thread_t *th, int N) {
	
	int i;
	for (i = 0; i < N; i++) {
		
		int *id = (int*)malloc(sizeof(int));
		*id = i;
		
		th[i].id = i;
		
		if (i == 0) {
			printf("Thread Servidor: %d\n", th[i].id);
			pthread_create(&th[i].t, NULL, server, &th[i].id);
		}
		else {
			printf("Thread Cliente: %d\n", th[i].id);
			pthread_create(&th[i].t, NULL, client, &th[i].id);
		} 
		free(id);
	}
	printf("\n\n");
}

void join_threads(thread_t *th, int N) {
	
	int i;
    for (i = 0; i < N; i++) {
		pthread_join(th[i].t, NULL);
	}
}

int main() {
	
	printf("* * * * * Manna-Pnueli - (Cliente-Servidor) * * * * *\n");
	printf("(1) - Controle da Regiao Critica | (2) - Sem Controle da Regiao Critica\n");
	printf("Inserir opcao: ");
	
	int op;
	scanf("%d", &op);
	
	if (op == 1) synchronization = 1;
	else if (op == 2) synchronization = 0;
	else {
		printf("\nOpcao invalida.");
		return -1;
	}
	
	printf("\n\n");
	
	int N = NUM_THREADS + 1;
	thread_t th[N];
	
	create_threads(th, N);
	join_threads(th, N);
	
	return 0;
}
