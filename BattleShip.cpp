#include <iostream>
#include <cstdlib>
#include "testing"
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

void print_screen(int grid[12][12], int num_ships)
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
            else if (grid[i][j] == 0)
            {
                cout << "x";
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

bool valid_dir(const char dir, const int len, const int x, const int y)
{
    if (dir != 'r' && dir != 'l' && dir != 'd' && dir != 'u')
        return false;
    if (dir == 'r' && x + len > 12)
        return false;
    if (dir == 'l' && x - len < 0)
        return false;
    if (dir == 'u' && y - len < 0)
        return false;
    if (dir == 'd' && y + len > 12)
        return false;
    return true;
}

void check_coord(int grid[12][12], int *x, int *y)
{
    while (*x > 11 || *x < 0 ||  *y > 11 || *y < 0 || grid[*x][*y] == 1)
    {
        cout << "Made in here " << *x << " " << *y << endl;
        cout << "Invalid coordinate pressed" << endl;
        cout << "Enter X coord";
        cin >> *y;
        cout << "Enter Y coord";
        cin >> *x;
    }
}

void reask_coord(int *x,  int *y, char *dir)
{
    cout << "Invalid Coord, please try again" << endl;
    cout << "Enters X coord: ";
    cin >> *y;
    cout << "Enter Y coord: ";
    cin >> *x;
    cout << "Enter Dir: ";
    cin >> *dir;
}

void check_dir(int grid[12][12], int *x, int *y, char *dir, const int len)
{
    check_coord(grid, x, y);
    while (!valid_dir(*dir, len, *x, *y))
    {
        cout << "Invalid Direction" << endl;
        cout << "Enter X coord: ";
        cin >> *y;
        cout << "Enter Y coord: ";
        cin >> *x;
        cout << "Enter Dir: ";
        cin >> *dir;

        check_coord(grid, x, y);
        *x -= 1;
        *y -= 1;
    }

    for (int i = 0; i < len; i++)
    {
        switch (*dir)
        {
        case 'u':
            if (grid[*x - i][*y] == 1)
            {
                reask_coord(x, y, dir);
                check_coord(grid, x, y);
                i = 0;
            }
            break;
        case 'd':
            if (grid[*x + i][*y] == 1)
            {
                reask_coord(x, y, dir);
                check_coord(grid, x, y);
                i = 0;
            }
            break;
        case 'r':
            if (grid[*x][*y + i] == 1)
            {
                reask_coord(x, y, dir);
                check_coord(grid, x, y);
                i = 0;
            }
            break;
        case 'l':
            if (grid[*x][*y - i] == 1)
            {
                reask_coord(x, y, dir);
                check_coord(grid, x, y);
                i = 0;
            }
            break;
        default:
            reask_coord(x, y, dir);
            check_coord(grid, x, y);
            i = 0;
        }
    }
}

void place_ships(battleship *ships[], const int num_ships, int grid[12][12])
{
    for (int i = 0; i < num_ships; i++)
    {
        cout << "Enter X coord: ";
        cin >> ships[i]->y;
        ships[i]->y -= 1;
        cout << "Enter Y coord: ";
        cin >> ships[i]->x;
        ships[i]->x -= 1;

        check_coord(grid, &ships[i]->x, &ships[i]->y);

        cout << "Enter Dir: ";
        cin >> ships[i]->dir;

        check_dir(grid, &ships[i]->x, &ships[i]->y, &ships[i]->dir, ships[i]->len);

        // At this point coordinates should be valid...
        for (int j = 0; j < ships[i]->len; j++)
        {
            switch (ships[i]->dir)
            {
            case 'u':
                grid[ships[i]->x - j][ships[i]->y] = 1;
                break;
            case 'd':
                grid[ships[i]->x + j][ships[i]->y] = 1;
                break;
            case 'l':
                grid[ships[i]->x][ships[i]->y - j] = 1;
                break;
            case 'r':
                grid[ships[i]->x][ships[i]->y + j] = 1;
                break;
            default:
                break;
            }
        }
        print_screen(grid, num_ships);
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
    print_screen(grid, num_ships);
    return 0;
}

bool game_over(int grid[12][12])
/*
 * TODO: this function
 */
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (grid[i][j] == 1)
                return false;
        }
    }
    return true;
}

void attack(int grid[12][12], int atk[12][12])
{
    int x = -1;
    int y = -1;

    cout << "Entering attack mode..." << endl;
    cout << "Enter X Coord: ";
    cin >> y;
    cout << "Enter Y Coord: ";
    cin >> x;
    y -= 1;
    x -= 1;
    check_coord(atk, &x, &y);

    // 0 is a successful attack, 1 is an insuccessful attack
    while (atk[x][y] == 0 || atk[x][y] == 1)
    {
        cout << "Already attacked here" << endl;
        cout << "Enter X Coord: ";
        cin >> y;
        cout << "Enter Y Coord: ";
        cin >> x;
        y -= 1;
        x -= 1;
        check_coord(atk, &x, &y);
    }
    if (grid[x][y] == 1)
    {
        cout << "Attack Landed!";
        grid[x][y] = 0;
        atk[x][y] = 0;
    }
    else
    {
        cout << "Missed Attack!";
        atk[x][y] = 1;
    }
}

void stall()
{
    char temp;
    cout << "Enter Any Key to Continue: ";
    cin >> temp;
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
    int p1_atk_grid[12][12];
    int p2_atk_grid[12][12];

    set_grid(p1_grid);
    set_grid(p2_grid);
    set_grid(p1_atk_grid);
    set_grid(p2_atk_grid);

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
        // TODO: logic for choosing ships
    }
    else
    {
        // Default ship sizes
        int sizes[5] = {5, 4, 3, 3, 2};

        gen_ships(p1_ships, num_ships, sizes);
        gen_ships(p2_ships, num_ships, sizes);
    }
    char temp;
    cout << "**********player 1 turn**********" << endl;
    place_ships(p1_ships, num_ships, p1_grid); // gets the x and y
    print_screen(p1_grid, num_ships);           // prints the grid

    stall();
    system("cls");

    cout << "**********player 2 turn**********" << endl;
    place_ships(p2_ships, num_ships, p2_grid); // gets the x and y
    print_screen(p2_grid, num_ships);          // prints the grid

    stall();
    system("cls");

    // TODO: Attacking Phase
    while (!game_over(p1_grid) && !game_over(p2_grid))
    {
        cout << "**********player 1 turn**********" << endl;
        attack(p2_grid, p1_atk_grid);

        system("cls");

        cout << "**********player 2 turn**********" << endl;
        attack(p1_grid, p2_atk_grid);
        system("cls");
    }

    cout << "Game is over!";
    clear_ships(p1_ships, num_ships);
    clear_ships(p2_ships, num_ships);

    return 0;
}