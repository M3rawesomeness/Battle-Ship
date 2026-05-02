#include <iostream>

using namespace std;

typedef struct battleship
{
    int x;
    int y;
    char dir;
    int len;
} battleship;

battleship *create_ship(const int len)
{
    battleship *p = new battleship;

    p->x = -1;
    p->y = -1;
    p->dir = ' ';
    p->len = len;
    return p;
}

void print_line(const int len)
{
    cout << "  ";
    for (int i = 0 ; i < len; i++)
        cout << "----";
    cout << "-" << endl;
}

void print_ships(int grid[12][12], int num_ships)
{
    // Prints numbers
    cout << "   ";
    for (int i = 1; i < 13; i++)
    {
        cout << " " << i << " ";
        if (i < 10)
            cout << " ";
    }
    cout << endl;
    print_line(12);

    for (int i = 0; i < 12; i++)
    {
        char letter_index = 'A';
        letter_index = static_cast<char>(letter_index + i);

        cout << letter_index << " | ";
        for (int j = 0; j < 12; j++)
        {
            if (grid[i][j] == 1)
            {
                cout << "o";
            }
            else
            {
                cout << " ";
            }
            cout << " | ";
        }
        cout << endl;
        print_line(12);
    }
}

void place_ships(battleship *ships[], const int num_ships, int grid[12][12])
{
    for (int i = 0; i < num_ships; i++)
    {
        constexpr int char_index_displacement = 60;
        cout << "For " << ships[i]->len << "x" << ships[i]->len << endl;
        cout << "enter X coord: ";
        cin >> ships[i]->x;
        cout << "enter Y coord: ";
        cin >> ships[i]->y;
        cout << "enter Dir (u/d/l/r): ";
        cin >> ships[i]->dir;

        grid[ships[i]->x - 1][ships[i]->y - 1] = 1;
        ships[i]->y -= char_index_displacement;

        for (int j = 0; j < ships[i]->len; j++)
        {
            if (ships[i]->dir == 'r')
            {
                grid[ships[i]->x - 1][ships[i]->y - 1 + j] = 1;
            }
            else if (ships[i]->dir == 'l')
            {
                grid[ships[i]->x - 1][ships[i]->y - 1 - j] = 1;
            }
            else if (ships[i]->dir == 'd')
            {
                grid[ships[i]->x - 1 + j][ships[i]->y - 1] = 1;
            }
            else if (ships[i]->dir == 'u')
            {
                grid[ships[i]->x - 1 - j][ships[i]->y - 1] = 1;
            }
        }
        print_ships(grid, num_ships);
    }
}

void set_grid(int grid[12][12])
{
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
            grid[i][j] = -1;
}

void gen_ships(battleship *ships[], const int num_ships, int sizes[])
{
    for (int i = 0; i < num_ships; i++)
    {
        ships[i] = create_ship(sizes[i]);
    }
}

void clear_ships(battleship *ships[], const int num_ships)
{
    for (int i = 0; i < num_ships; i++)
        delete ships[i];
}

int test_main()
// Main for testing
{
    constexpr int num_ships = 4;
    int grid[12][12];

    set_grid(grid);
    print_ships(grid, num_ships);
    return 0;
}

int main()
{
    constexpr int arr_length = 49;
    int width = arr_length / 4;
    constexpr int num_rows = 12;
    int num_cols = num_rows;
    constexpr int num_ships = 5;

    int p1_grid[12][12];
    int p2_grid[12][12];

    set_grid(p1_grid);
    set_grid(p2_grid);
    string ans;

    battleship *p1_ships[num_ships];
    battleship *p2_ships[num_ships];

    cout << "hello! welcome to battleship!" << endl;
    cout << "would you like custom ships? (y/n): ";
    cin >> ans;

    while (ans != "y" && ans != "n")
    {
        cout << "invalid choice, try again: ";
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
    cout << "**********player 1 turn**********" << endl;

    place_ships(p1_ships, num_ships, p1_grid); // gets the x and y
    print_ships(p1_grid, num_ships);           // prints the grid

    clear_ships(p1_ships, num_ships);
    return 0;
}