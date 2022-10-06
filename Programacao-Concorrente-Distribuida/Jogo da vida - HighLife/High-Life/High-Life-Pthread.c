
/*
 *   UNIFESP SJC
 *
 *   PROGRAMAÇÃO CONCORRENTE E DISTRIBUÍDA
 *   HIGH LIFE - Pthread
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> 

#define MATRIX_LENGTH 2048
#define NUM_GENERATIONS 2000

/* NÚMERO DE THREADS: */
#define NUM_THREADS 4

pthread_barrier_t barrier;
int flag = 0;

typedef struct {
	
	int thread_id;
	int **grid, **newGrid;
	
} thread_data;

int **buildMatrix() {
	
    int **matrix = (int**)malloc(sizeof(int*) * MATRIX_LENGTH);
    
    int i;
    for (i = 0; i < MATRIX_LENGTH; i++) {
    	matrix[i] = (int*)calloc(MATRIX_LENGTH, sizeof(int));
	}
    return matrix;
}

void initGrid(int **grid)
{
	/* GLIDER */
    int lin = 1, col = 1;
    
    grid[lin][col + 1] = 1;
    grid[lin + 1][col + 2] = 1;
    grid[lin + 2][col] = 1;
    grid[lin + 2][col + 1] = 1;
    grid[lin + 2][col + 2] = 1;

	/* R-pentomino */
    lin = 10; col = 30;
    
    grid[lin][col+ 1 ] = 1;
    grid[lin][col + 2] = 1;
    grid[lin + 1][col] = 1;
    grid[lin + 1][col + 1] = 1;
    grid[lin + 2][col + 1] = 1;
}

int getNeighbors(int **grid, int i, int j) {
	
	int limit = MATRIX_LENGTH - 1;
	
	int up = i - 1;
	int down = i + 1;
	int left = j - 1;
	int right = j + 1;
	
	if (up < 0) up = limit;
	if (down > limit) down = 0;
	if (left < 0) left = limit;
	if (right > limit) right = 0;		
		
	/*				   
	 *
	 *	   grid[up][left]	  grid[up][j]	  grid[up][right]	 grid[i][left]
	 *				
	 *	   | x | - | - |	 | - | x | - |	   | - | - | x |	 | - | - | - |
	 *	   -------------     -------------	   -------------     -------------
	 *	   | - | O | - |	 | - | O | - |	   | - | O | - |	 | x | O | - |
	 *	   -------------	 -------------	   -------------	 -------------
	 *	   | - | - | - |	 | - | - | - |	   | - | - | - |	 | - | - | - |
	 *
	 *
	 *	   grid[i][right]   grid[down][left]   grid[down][j]   grid[down][right]
	 *				
	 *	   | - | - | - |	 | - | - | - |	   | - | - | - |	 | - | - | - |
	 *	   -------------     -------------	   -------------     -------------
	 *	   | - | O | x |	 | - | O | - |	   | - | O | - |	 | - | O | - |
	 *	   -------------	 -------------	   -------------	 -------------
	 *	   | - | - | - |	 | x | - | - |	   | - | x | - |	 | - | - | x |
	 *
	 *
	 *	   x = Posição do vizinho
	 *	   O = Posição da célula 
	 */
		
	int row[] = {up, up, up, i, i, down, down, down};
	int col[] = {left, j, right, left, right, left, j, right};
	
	int k, num_neighbors = 0;
	for (k = 0; k < 8; k++) {
		if (grid[row[k]][col[k]] == 1) num_neighbors++; 
	}		
	return num_neighbors;
}

int cellAlive(int **grid) {
	
	int num_cells = 0;
	int i, j;
	
	for (i = 0; i < MATRIX_LENGTH; i++) {
			
		for (j = 0; j < MATRIX_LENGTH; j++) {
			if (grid[i][j] == 1) num_cells++;
		}
	}
	return num_cells;
}

void printSubMatrix(int **grid) {
	
	int i, j;
	for (i = 0; i < 50; i++) {
		
		for (j = 0; j < 50; j++) {
			printf("%d ", grid[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void *nextGeneration(void *arg) {
		
	thread_data *local_th_data = (thread_data*) arg;
	
	int chuck = MATRIX_LENGTH / NUM_THREADS;
	int local_start = local_th_data->thread_id * chuck;
	int local_end = (local_th_data->thread_id + 1) * chuck;
	
	int i, j, k;
	for (k = 0; k < NUM_GENERATIONS; k++) {
		
		for (i = local_start; i < local_end; i++) {
    
		    for (j = 0; j < MATRIX_LENGTH; j++) {
		    	
		        int num_neighbors = getNeighbors(local_th_data->grid, i, j);
				
				if (local_th_data->grid[i][j] == 1 && num_neighbors < 2) local_th_data->newGrid[i][j] = 0;
				else if (local_th_data->grid[i][j] == 1 && (num_neighbors == 2 || num_neighbors == 3))	local_th_data->newGrid[i][j] = 1;	
				else if (local_th_data->grid[i][j] == 1 && num_neighbors > 3) local_th_data->newGrid[i][j] = 0;
				else if (local_th_data->grid[i][j] == 0 && (num_neighbors == 3 || num_neighbors == 6)) local_th_data->newGrid[i][j] = 1;
				else local_th_data->newGrid[i][j] = local_th_data->grid[i][j];	
			}
		}
		
		/* Atualizando grid e newGrid */
		pthread_barrier_wait(&barrier);
		
			int **temp = local_th_data->grid;
			local_th_data->grid = local_th_data->newGrid;
			local_th_data->newGrid = temp;
			
			if (local_th_data->thread_id == 0 && k < 4 && flag) {
				printf("Geracao %d: %d\n", k + 1, cellAlive(local_th_data->grid));
				printSubMatrix(local_th_data->grid);
			}
			
		pthread_barrier_wait(&barrier);	
	}
	pthread_barrier_destroy(&barrier);
}
	
void startGameOfLife(int **grid, int **newGrid, pthread_t *th, thread_data *th_data) {
	
	printf("Condicao inicial: %d\n", cellAlive(grid));
	
	int i;
	for (i = 0; i < NUM_THREADS; i++) {
			
		int *id = malloc(sizeof(int));
		*id = i;
			
		th_data[i].grid = grid;
		th_data[i].newGrid = newGrid;
		th_data[i].thread_id = i;
			
		pthread_create(&th[i], NULL, &nextGeneration, (void *) &th_data[i]);
		free(id);
	}
		
	for (i = 0; i < NUM_THREADS; i++) {
		pthread_join(th[i], NULL);
	}
	printf("Ultima geracao (%d iteracoes): %d celulas vivas.\n", NUM_GENERATIONS, cellAlive(grid));
}

void demoHighLife(int **grid, int **newGrid, pthread_t *th, thread_data *th_data) {
	
	printf("Condicao inicial: %d\n", cellAlive(grid));
	
	flag = 1;
		
	int i;
	for (i = 0; i < NUM_THREADS; i++) {
			
		int *id = malloc(sizeof(int));
		*id = i;
			
		th_data[i].grid = grid;
		th_data[i].newGrid = newGrid;
		th_data[i].thread_id = i;
			
		pthread_create(&th[i], NULL, &nextGeneration, (void *) &th_data[i]);
		free(id);
	}
	
	for (i = 0; i < NUM_THREADS; i++) {
		pthread_join(th[i], NULL);
	}
}

int main() {

	int **grid = buildMatrix();
	int **newGrid = buildMatrix();
	
	initGrid(grid);
	initGrid(newGrid);
	
	pthread_barrier_init(&barrier, NULL, NUM_THREADS);
	
	pthread_t th[NUM_THREADS];
	thread_data th_data[NUM_THREADS];
	
	//demoHighLife(grid, newGrid, th, th_data);
	
	time_t t1, t2;
	
    time(&t1);
	startGameOfLife(grid, newGrid, th, th_data);
	time(&t2);
	
	printf("Tempo: %.2f segundos.\n", difftime(t2, t1));	
	return 0;
}