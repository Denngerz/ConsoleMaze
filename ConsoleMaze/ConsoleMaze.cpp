#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

// Maze
std::vector<std::vector<char>> field;
int width = 10;
int height = 12;
int blockFrequency = 28;

// Dog
char dog = '@';
int dogX{0}, dogY{0};
int dx, dy;

// Finish
int finishX{0}, finishY{0};
char finishSymbol = 'F';

bool reachedFinish = false;


void placeDog()
{
    dogX = rand() % width;
    dogY = rand() % height;
}

void generateField()
{
    for (int i = 0; i < height; i++)
    {
        std::vector<char> row (width);
        for (int j = 0; j < width; j++)
        {
            char symbol;
            int random = rand() % 101;
            if(random <= blockFrequency)
            {
                symbol = '#';
            }
            else
            {
                symbol = '.';
            }
            row[j] = symbol;
        }
        field.push_back(row);
    }

    finishX = rand() % width;
    finishY = rand() % height;
    field[finishY][finishX] = finishSymbol;
}

void generate()
{
    generateField();
    placeDog();
}

void draw()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            char symbol;
            if(i == dogY && j == dogX)
            {
                symbol = dog;
            }
            else
            {
                symbol = field[i][j];
            }
            std::cout << symbol;
        }
        std::cout << std::endl;
    }
}

void getInput()
{
    dx = 0;
    dy = 0;
    char input;
    std::cin >> input;
    switch (input)
    {
        case 'w':
            dy = -1;
            break;
        
        case 's':
            dy = 1;
            break;
        
        case 'a':
            dx = -1;
            break;
        
        case 'd':
            dx = 1;
            break;
    }
}

bool isEndGame()
{
    return reachedFinish;
}

bool isWalkable(int newX, int newY)
{
    if (field[newY][newX] == '#')
    {
        return false;
    }
    
    return true;
}

bool canGoTo(int newX, int newY)
{
    if(newX < 0 || newY < 0 || newX >= width || newY >= height)
    {
        return false;
    }

    if(not isWalkable(newX, newY))
    {
        return false;
    }
    
    return true;
}

void goTo(int newX, int newY)
{
    dogX = newX;
    dogY = newY;
}

void tryGoTo(int newX, int newY)
{
    if(canGoTo(newX, newY))
    {
        goTo(newX, newY);
    }
}

void checkFinish()
{
    if(dogX == finishX && dogY == finishY)
    {
        reachedFinish = true;
    }
}

void logic()
{
    tryGoTo(dogX + dx, dogY + dy);

    checkFinish();
}

int main(int argc, char* argv[])
{
    srand (time(0));
    generate();
    draw();

    while(not isEndGame())
    {
        getInput();
        logic();
        draw();
    }

    std::cout << "PEREMOGA!" << std::endl;
    
    return 0;
}
