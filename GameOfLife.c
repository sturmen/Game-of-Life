#include <stdio.h>
#include <time.h>
#define ROWS 20
#define COLS 79

int generation = 0;
int population = 0;
int populationMax = 0;
int populationMin = 0;
int tempGrid[ROWS][COLS];

int getUserInput();
void initGrid(int, int, int[ROWS][COLS]);
void processGeneration(int, int, int[ROWS][COLS]);
int countNeighbors(int, int, int[ROWS][COLS], int, int);
void printGrid(int, int, int[ROWS][COLS]);
void sleep(unsigned int);


    //main function
int main()
{
    srand((unsigned int) time(NULL));
    int grid[ROWS][COLS];
    initGrid(ROWS, COLS, grid);
    printGrid(ROWS, COLS, grid);
    
    int i, g;
    g = getUserInput();
    for (i = 0; i < g; i++)
    {
        generation++;
        processGeneration(ROWS, COLS, grid);
        printGrid(ROWS, COLS, grid);
        sleep(1000);
    }
    
    
	return 0;
}

    //functions
int getUserInput()
{
	int g;
	printf("Welcome to the Game of Life.\n");
	printf("How many generations do you want to watch?");
	scanf("%d", &g);
	return g;
}

void initGrid(int rows, int cols, int g[rows][cols])
{
	int i, j, k;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
                //array is bounded by [-1]'s
			if (i == 0 || j == 0 || i == (rows - 1) || j == (cols - 1))
			{
				g[i][j] = -1;
			}
			else
			{
                    //initial random grid
				k = rand() % 3;
                if (k == 0)
                {
                    g[i][j] = 1;
                    population++;
                }
                else
                {
                    g[i][j] = 0;
                }
			}
		}
	}
    processGeneration(rows, cols, g);
}

void processGeneration(int rows, int cols, int g[rows][cols])
{
    int i, j, neighbors;
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
                //ignore borders
            if (g[i][j] == -1) continue;
                //get number of neighbors
            neighbors = countNeighbors(rows, cols, g, i, j);
                //death conditions
            if(g[i][j] == 1 && (neighbors < 2 || neighbors > 3))
            {
                tempGrid[i][j] = 0;
            }
                //birth conditions
            else if (g[i][j] == 0 && neighbors == 3)
            {
                tempGrid[i][j] = 1;
            }
        }
    }
        //clean slate for population counting
    population = 0;
        //population counting
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            if(g[i][j] == -1) continue;
            if(tempGrid[i][j] == 1) population++;
            g[i][j] = tempGrid[i][j];
        }
    }
    if (population > populationMax) 
    {
        populationMax = population;
    }
    if (population < populationMin || populationMin == 0)
    {
        populationMin = population;
    }
}

int countNeighbors(int rows, int cols, int g[rows][cols], int x, int y)
{
    int n = 0, i, j;
    
    for (j = y - 1; j < y + 2; j++)
    {
        for (int i = x - 1; i < x + 2; i++)
        {
            if (i == x && j == y)
            {
                continue;
            }
            if (g[i][j] != -1)
            {
                n += g[i][j];
            }
        }
    }
    return n;
}

void printGrid(int rows, int cols, int g[rows][cols])
{
    system("clear");
    printf("Welcome to the Game of Life! Generation %d\n", generation);
    printf("Population: %d [MAX %d] [ MIN %d]\n", population, populationMax, populationMin);
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            switch (g[i][j])
            {
                case -1: putchar('#'); break;
                case  0: putchar(' '); break;
                case  1: putchar('0'); break;
                default: break;
            }
        }
        putchar('\n');
    }
}


void sleep(unsigned int mill)
{
    clock_t start = clock();
    while (clock() - start < mill) { }
}



    //end of the code