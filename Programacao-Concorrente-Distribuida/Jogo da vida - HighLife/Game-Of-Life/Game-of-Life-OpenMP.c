
/*
 *   UNIFESP SJC
 *
 *   PROGRAMAÇÃO CONCORRENTE E DISTRIBUÍDA
 *   GAME OF LIFE - OpenMP
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h> 

#define MATRIX_LENGTH 2048
#define NUM_GENERATIONS 2000

/* NÚMERO DE THREADS: */
#define NUM_THREADS 4

int **buildMatrix() {
	
    int **matrix = (int**)malloc(sizeof(int*) * MATRIX_LENGTH);
    int i;

    for (i = 0; i < MATRIX_LENGTH; i++){
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
    
    grid[lin][col + 1] = 1;
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
	
	#pragma omp parallel num_threads(NUM_THREADS) private(i, j)
	#pragma omp for
	for (i = 0; i < MATRIX_LENGTH; i++) {
		
		for (j = 0; j < MATRIX_LENGTH; j++) {
			if (grid[i][j] == 1) num_cells++;
		}
	}
	return num_cells;
}

void nextGeneration(int **grid, int **newGrid) {
	
	int i, j;
	
	#pragma omp parallel num_threads(NUM_THREADS) private(i,j)
	{
		#pragma omp for
    	for (i = 0; i < MATRIX_LENGTH; i++) {
    
	        for (j = 0; j < MATRIX_LENGTH; j++) {
	        	
	        	int num_neighbors = getNeighbors(grid, i, j);
				
				if (grid[i][j] == 1 && num_neighbors < 2) newGrid[i][j] = 0;
				else if (grid[i][j] == 1 && (num_neighbors == 2 || num_neighbors == 3))	newGrid[i][j] = 1;
				else if (grid[i][j] == 1 && num_neighbors > 3) newGrid[i][j] = 0;
				else if (grid[i][j] == 0 && num_neighbors == 3) newGrid[i][j] = 1;
				else newGrid[i][j] = grid[i][j];			
			}
		}
	}
}

void startGameOfLife(int **grid, int **newGrid) {
	
	printf("Condicao inicial: %d\n", cellAlive(grid));
	
	int i;
	for (i = 0; i < NUM_GENERATIONS; i++) {
		
		nextGeneration(grid, newGrid);
		
		/* Atualizando grid e newGrid */
		int **temp = grid;
		grid = newGrid;
		newGrid = temp;
		
		if (i < 4) printf("Geracao %d: %d\n", i + 1, cellAlive(grid));
	}
	printf("Ultima geracao (%d iteracoes): %d celulas vivas.\n", NUM_GENERATIONS, cellAlive(grid));
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

void demoGameOfLife(int **grid, int **newGrid) {
	
	printf("Condicao Inicial: %d\n", cellAlive(grid));
	
	int i;
	for (i = 0; i < 4; i++) {
		
        nextGeneration(grid, newGrid);
        
        /* Atualizando grid e newGrid */
		int **temp = grid;
		grid = newGrid;
		newGrid = temp;
		
        printf("Geracao %d: %d\n", i + 1, cellAlive(grid));
        printSubMatrix(grid);
    }
}

void freeMatrix(int **matrix) {
	
	int i;
	for (i = 0; i < MATRIX_LENGTH; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {

	int **grid = buildMatrix();
	int **newGrid = buildMatrix();
	
	initGrid(grid);
	initGrid(newGrid);
	
	//demoGameOfLife(grid, newGrid);
	
	time_t t1, t2;
    
	time(&t1);
	startGameOfLife(grid, newGrid);
	time(&t2);
	
	printf("Tempo: %.2f segundos.\n", difftime(t2, t1));
	
	freeMatrix(grid);
	freeMatrix(newGrid);
	return 0;
}