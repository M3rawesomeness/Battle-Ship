#include <iostream>

using namespace std;

typedef struct BattleShip
{
    int x;
    int y;
    int len;
} battleship;

battleship *create_ship(int len)
{
    battleship *p = new battleship;
    if (p == NULL)
        return NULL;

    p->x = -1;
    p->y = -1;
    p->len = len;
    return p;
}

void clear_ships(battleship *ships[], int num_ships)
{
    for (int i = 0; i < num_ships; i++)
        delete ships[i];
}

void print_ships(int grid[12][12], int num_ships)
{
    cout << "printing ships";
    return;
}

void place_ships(battleship *ships[], int num_ships, int grid[12][12])
{
    for (int i = 0; i < num_ships; i++)
    {
        print_ships(grid, num_ships);
        cout << "Enter X for " << ships[i]->len << "x" << ships[i]->len;
        cin >> ships[i]->x;
        cout << "Enter Y: ";
        cin >> ships[i]->y;

        grid[ships[i]->x][ships[i]->y] = 1;
    }
}

void set_grid(int grid[12][12])
{
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
            grid[i][j] = -1;
}

void gen_ships(battleship *ships[], int num_ships, int sizes[])
{
    for (int i = 0; i < num_ships; i++)
    {
        ships[i] = create_ship(sizes[i]);
    }
}

int main()
{
    int arr_length = 49;
    int width = arr_length / 4;
    int num_rows = 12;
    int num_cols = num_rows;
    int num_ships = 5;

    int p1_grid[12][12];
    int p2_grid[12][12];

    set_grid(p1_grid);
    set_grid(p2_grid);
    string ans;

    battleship *p1_ships[num_ships];
    battleship *p2_ships[num_ships];

    cout << "Hello! Welcome To BattleShip!" << endl;
    cout << "Would you like custom ships? (y/n)";
    cin >> ans;

    while (ans != "y" && ans != "n")
    {
        cout << "Invalid choice, try again: ";
        cin >> ans;
    }

    if (ans == "y")
    {
        // logic for choosing ships
    }
    else
    {
        int sizes[5] = {5, 4, 3, 3, 2};

        gen_ships(p1_ships, num_ships, sizes);
        gen_ships(p2_ships, num_ships, sizes);
    }
    cout << "**********Player 1 Turn**********" << endl;

    place_ships(p1_ships, num_ships, p1_grid); // Gets the X and Y
    print_ships(p1_grid, num_ships);           // Prints the grid

    clear_ships(p1_ships, num_ships);
    return 0;
}
