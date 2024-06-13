#include <stdio.h>
#include <time.h>

int columnNumber, rowNumber;
int gameArea[30][30], gamePoint[30][30], block[3][3], gameAreaColumnValue[30][30], blockAreaColumnValue[30][30];
int score = 0;
int r, c, a, b;

int L[3][3] = { {1, 0, 0}, {1, 0, 0}, {1, 1, 0} };
int Z[3][3] = { {0, 1, 1}, {1, 1, 0}, {0, 0, 0} };
int T[3][3] = { {1, 1, 1}, {0, 1, 0}, {0, 0, 0} };
int O[3][3] = { {1, 1, 0}, {1, 1, 0}, {0, 0, 0} };
int I[3][3] = { {1, 0, 0}, {0, 0, 0}, {0, 0, 0} };
int II[3][3] = { {1, 0, 0}, {1, 0, 0}, {0, 0, 0} };
int III[3][3] = { {1, 0, 0}, {1, 0, 0}, {1, 0, 0} };
int IA[3][3] = { {1, 1, 0}, {0, 0, 0}, {0, 0, 0} };
int IB[3][3] = { {1, 1, 1}, {0, 0, 0}, {0, 0, 0} };

void PrintGameArea(int numberOfRow, int numberOfColumn)
{
    for(a = 0; a < numberOfRow; a++)
    {
        for(b = 0; b < numberOfColumn; b++)
        {
            int gamePoint = gameArea[a][b];
            if(gamePoint == 0)
            {
                printf("-");
            }
            else
            {
                printf("*");
            }
            
        }
        printf("\n");
    }
    printf("\n");
}

int BlockCanFit(int block[3][3], int rowNumber, int columnNumber, int numberOfRow, int numberOfColumn)
{
    int endColumnIndex = -1;
    int endRowIndex = -1;
    for(r = 0; r < 3; r++)
    {
        for(c = 0; c < 3; c++)
        {
            if(block[r][c] > 0 && endColumnIndex < c)
            {
                endColumnIndex = c;
            }
        }
    }
    for(r = 0; r < 3; r++)
    {
        for(c = 0; c < 3; c++)
        {
            if(block[r][c] > 0 && endRowIndex < r)
            {
                endRowIndex = r;
            }
        }
    }
    if(endColumnIndex + columnNumber >= numberOfColumn)
    {

        return 0;
    } 
    if(endRowIndex + rowNumber >= numberOfRow)
    {

        return 0;
    }
    for(r = rowNumber; r < rowNumber + 3; r++)
    {
        for(c = columnNumber; c < columnNumber + 3; c++)
        {
            int gameAreaColumnValue = gameArea[r][c];
            int blockAreaColumnValue = block[r-rowNumber][c - columnNumber];

            if(gameAreaColumnValue > 0 && blockAreaColumnValue > 0)
            {
                return 0;
            }
        }
    }

    return 1;
}


int BlockCanBePlaced(int block[3][3], int rowNumber, int columnNumber, int numberOfRow, int numberOfColumn)
{
    int maxRowIndex = 0;
    for(r = 0; r < 3; r++)
    {
        for(c = 0; c < 3; c++)
        {
            if(block[r][c] > 0 && maxRowIndex < r)
            {
                maxRowIndex = r;
            }
        }
    }
    if(rowNumber + maxRowIndex >= numberOfRow)
    {

        return -1;
    }
    for(r = rowNumber; r < rowNumber + 3; r++)
    {
        for(c = columnNumber; c < columnNumber + 3; c++)
        {
            int gameAreaColumnValue = gameArea[r][c];
            int blockAreaColumnValue = block[r-rowNumber][c - columnNumber];

            if(gameAreaColumnValue > 0 && blockAreaColumnValue > 0)
            {
                return -1;
            }
        }
    }

    return 1;
}



int PlaceBlock(int block[3][3], int rowNumber, int columnNumber, int numberOfRow, int numberOfColumn)
{
    while(BlockCanBePlaced(block, rowNumber, columnNumber, numberOfRow, numberOfColumn) == 1)
    {
        rowNumber++;
    }
    rowNumber--;
    if(rowNumber <= 0)
    {

        return -1;
    }

    for(r = rowNumber; r < rowNumber + 3; r++)
    {
        for(c = columnNumber; c < columnNumber + 3; c++)
        {
            int blockAreaColumnValue = block[r-rowNumber][c - columnNumber];
            if(blockAreaColumnValue > 0)
            {
                gameArea[r][c] = blockAreaColumnValue;   
            }
        }
    }

    return 1;
}

void EraseBlock(int numberOfRow, int numberOfColumn)
{
    int toRow, fromRow, c2;
    int erasedRowCount = 0;
    for(r = numberOfRow-1; r >= 0; r--)
    {
        int isRowSelectedToErase = 1;
        for(c = 0; c < numberOfColumn; c++)
        {
            if(gameArea[r][c] == 0)
            {  	
                isRowSelectedToErase = 0;
            }
        }
        if(isRowSelectedToErase == 1)
        {
            if(erasedRowCount == 0)
            {
                PrintGameArea(numberOfRow, numberOfColumn);
            }
            erasedRowCount++;
            for(toRow = r; toRow > 0; toRow--)
            {
                for(c2 = 0; c2 < numberOfColumn; c2++)
                {
                    gameArea[toRow][c2] = gameArea[toRow -1][c2];
                }
            }
            for(c2 = 0; c2 < numberOfColumn; c2++)
            {
                gameArea[0][c2] = 0;
            }
        }
    }
    score = score + 100 * erasedRowCount * erasedRowCount;
}

int main() 
{
	int numberOfRow, numberOfColumn;
	int coordinatex = 1;
    int coordinatey = 1;
	printf("Please enter row and column number\n");
	scanf("%d %d",&numberOfRow,&numberOfColumn);
	
	printf("\n"); 
	
    for(r = 0; r < numberOfRow; r++)
    {
        for(c = 0; c < numberOfColumn; c++)
        {
            gameArea[r][c] = 0;
        }
    }
    printf("To exit game, enter (0,0)\n");
    do
    {
        PrintGameArea(numberOfRow, numberOfColumn);
        printf("\n");
        
        srand(time(NULL));
        int randomBlockNumber = rand() % 9;
        int selectedBlock[3][3];

        if(randomBlockNumber == 0)
        {
            for(r = 0; r < 3; r++)
            {
                for(c = 0; c < 3; c++)
                {
                    selectedBlock[r][c] = L[r][c];
                }
            }
        }
        else if(randomBlockNumber == 1)
        {
            for(r = 0; r < 3; r++)
            {
                for(c = 0; c < 3; c++)
                {
                    selectedBlock[r][c] = Z[r][c];
                }
            }
        }
        else if(randomBlockNumber == 2)
        {
            for(r = 0; r < 3; r++)
            {
                for(c = 0; c < 3; c++)
                {
                    selectedBlock[r][c] = T[r][c];
                }
            }
        }
        else if(randomBlockNumber == 3)
        {
            for(r = 0; r < 3; r++)
            {
                for(c = 0; c < 3; c++)
                {
                    selectedBlock[r][c] = O[r][c];
                }
            }
        }
        else if(randomBlockNumber == 4)
        {
            for(r = 0; r < 3; r++)
            {
                for(c = 0; c < 3; c++)
                {
                    selectedBlock[r][c] = I[r][c];
                }
            }
        }
        else if(randomBlockNumber == 5)
        {
            for(r = 0; r < 3; r++)
            {
                for(c = 0; c < 3; c++)
                {
                    selectedBlock[r][c] = II[r][c];
                }
            }
        }
        else if(randomBlockNumber == 6)
        {
            for(r = 0; r < 3; r++)
            {
                for(c = 0; c < 3; c++)
                {
                    selectedBlock[r][c] = III[r][c];
                }
            }
        }
        else if(randomBlockNumber == 7)
        {
            for(r = 0; r < 3; r++)
            {
                for(c = 0; c < 3; c++)
                {
                    selectedBlock[r][c] = IA[r][c];
                }
            }
        }
        else if(randomBlockNumber == 8)
        {
            for(r = 0; r < 3; r++)
            {
                for(c = 0; c < 3; c++)
                {
                    selectedBlock[r][c] = IB[r][c];
                }
            }
        }

        printf("Next shape:\n");
        for(r = 0; r < 3; r++)
        {
            for(c = 0; c < 3; c++)
            {
                int blockValue = selectedBlock[r][c];
                if(blockValue > 0)
                {
                    printf("*");
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("Your score: %d\n", score);
        printf("Please enter coordinates (x,y):\n ");

        scanf("%d %d", &coordinatex, &coordinatey);
        if(coordinatex < 0 || coordinatex > numberOfRow)
        {
            printf("Invalid location please try again\n");
            continue;
        }
        if(coordinatey < 0 || coordinatey > numberOfColumn)
        {
            printf("Invalid location please try again\n");
            continue;
        }

        coordinatey--;
        coordinatex--;
        int blockCanFit = BlockCanFit(selectedBlock, coordinatex, coordinatey,numberOfRow, numberOfColumn);
        if(blockCanFit == 0)
        {
            printf("Block can not be placed, please try again\n");
            continue;
        }
        if(PlaceBlock(selectedBlock, coordinatex, coordinatey,numberOfRow, numberOfColumn) == -1)
        {
            printf("Game over\nYour score:%d", score);
            coordinatex = -1;
			coordinatey = -1;
        }
        EraseBlock(numberOfRow, numberOfColumn);
    }while(coordinatex != -1 && coordinatey != -1);

    return 0;
}
