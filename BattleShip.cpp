#include <iostream>
#include <cstdlib>

using namespace std;

#define EMP (-1)
#define HIT 0
#define OCC 1 // Occupied
#define MIS 1
#define GRID_DIM 12
#define UP 'u'
#define DOWN 'd'
#define LEFT 'l'
#define RIGHT 'r'
#define NUM_SHIPS 5
#define CLEAR_SCREEN "cls"
#define HIT_SYMBOL "x"
#define SHIP_SYMBOL "o"

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

void print_screen(int grid[GRID_DIM][GRID_DIM], int num_ships)
{
    // Prints numbers
    cout << "   ";
    constexpr int offset = 1;
    for (int i = 1; i < GRID_DIM + offset; i++)
    {
        cout << " " << i << " ";
        if (i < 10)
            cout << " ";
    }
    cout << endl;
    print_line(GRID_DIM);

    for (int i = 0; i < GRID_DIM; i++)
    {
        char letter_index = 'A';
        letter_index = static_cast<char>(letter_index + i);

        cout << letter_index << " | ";
        for (int j = 0; j < GRID_DIM; j++)
        {
            if (grid[i][j] == OCC)
            {
                cout << "o";
            }
            else if (grid[i][j] == HIT)
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
        print_line(GRID_DIM);
    }
}

bool valid_dir(const char dir, const int len, const int x, const int y)
{
    constexpr int upper_bound = 12;
    constexpr int lower_bound = 0;

    if (dir != RIGHT && dir != LEFT && dir != DOWN && dir != UP)
        return false;
    if (dir == RIGHT && x + len > upper_bound)
        return false;
    if (dir == LEFT && x - len < lower_bound)
        return false;
    if (dir == UP && y - len < lower_bound)
        return false;
    if (dir == DOWN && y + len > upper_bound)
        return false;
    return true;
}

void check_coord(int grid[GRID_DIM][GRID_DIM], int *x, int *y)
{
    constexpr int upper_bound = 11;
    constexpr int lower_bound = 0;

    while (*x > upper_bound || *x < lower_bound ||  *y > upper_bound || *y < lower_bound || grid[*x][*y] == OCC)
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
        constexpr int offset = 1;
        cout << "Invalid Direction" << endl;
        cout << "Enter X coord: ";
        cin >> *y;
        cout << "Enter Y coord: ";
        cin >> *x;
        cout << "Enter Dir: ";
        cin >> *dir;

        check_coord(grid, x, y);
        *x -= offset;
        *y -= offset;
    }

    for (int i = 0; i < len; i++)
    {
        switch (*dir)
        {
        case UP:
            if (grid[*x - i][*y] == OCC)
            {
                reask_coord(x, y, dir);
                check_coord(grid, x, y);
                i = 0;
            }
            break;
        case DOWN:
            if (grid[*x + i][*y] == OCC)
            {
                reask_coord(x, y, dir);
                check_coord(grid, x, y);
                i = 0;
            }
            break;
        case RIGHT:
            if (grid[*x][*y + i] == OCC)
            {
                reask_coord(x, y, dir);
                check_coord(grid, x, y);
                i = 0;
            }
            break;
        case LEFT:
            if (grid[*x][*y - i] == OCC)
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

void place_ships(int grid[GRID_DIM][GRID_DIM], battleship *ships[], const int num_ships)
{
    for (int i = 0; i < num_ships; i++)
    {
        constexpr int offset = 1;
        cout << "Enter X coord: ";
        cin >> ships[i]->y;
        ships[i]->y -= offset;
        cout << "Enter Y coord: ";
        cin >> ships[i]->x;
        ships[i]->x -= offset;

        check_coord(grid, &ships[i]->x, &ships[i]->y);

        cout << "Enter Dir: ";
        cin >> ships[i]->dir;

        check_dir(grid, &ships[i]->x, &ships[i]->y, &ships[i]->dir, ships[i]->len);

        // At this point coordinates should be valid...
        for (int j = 0; j < ships[i]->len; j++)
        {
            switch (ships[i]->dir)
            {
            case UP:
                grid[ships[i]->x - j][ships[i]->y] = OCC;
                break;
            case DOWN:
                grid[ships[i]->x + j][ships[i]->y] = OCC;
                break;
            case LEFT:
                grid[ships[i]->x][ships[i]->y - j] = OCC;
                break;
            case RIGHT:
                grid[ships[i]->x][ships[i]->y + j] = OCC;
                break;
            default:
                break;
            }
        }
        print_screen(grid, num_ships);
    }
}

void set_grid(int grid[GRID_DIM][GRID_DIM])
{
    for (int i = 0; i < GRID_DIM; i++)
        for (int j = 0; j < GRID_DIM; j++)
            grid[i][j] = EMP;

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

bool game_over(int grid[GRID_DIM][GRID_DIM])
{
    for (int i = 0; i < GRID_DIM; i++)
    {
        for (int j = 0; j < GRID_DIM; j++)
        {
            if (grid[i][j] == OCC)
                return false;
        }
    }
    return true;
}

void attack(int grid[GRID_DIM][GRID_DIM], int atk[GRID_DIM][GRID_DIM])
{
    int x = -1;
    int y = -1;
    constexpr int offset = 1;
    cout << "Entering attack mode..." << endl;
    cout << "Enter X Coord: ";
    cin >> y;
    cout << "Enter Y Coord: ";
    cin >> x;

    y -= offset;
    x -= offset;
    check_coord(atk, &x, &y);

    // 0 is a successful attack, 1 is an unsuccessful attack
    while (atk[x][y] == HIT || atk[x][y] == OCC)
    {
        cout << "Already attacked here" << endl;
        cout << "Enter X Coord: ";
        cin >> y;
        cout << "Enter Y Coord: ";
        cin >> x;

        y -= offset;
        x -= offset;

        check_coord(atk, &x, &y);
    }
    if (grid[x][y] == OCC)
    {
        cout << "Attack Landed!";
        grid[x][y] = HIT;
        atk[x][y] = HIT;
    }
    else
    {
        cout << "Missed Attack!";
        atk[x][y] = MIS;
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
    int p1_grid[GRID_DIM][GRID_DIM];
    int p2_grid[GRID_DIM][GRID_DIM];
    int p1_atk_grid[GRID_DIM][GRID_DIM];
    int p2_atk_grid[GRID_DIM][GRID_DIM];

    set_grid(p1_grid);
    set_grid(p2_grid);
    set_grid(p1_atk_grid);
    set_grid(p2_atk_grid);

    string ans;

    battleship *p1_ships[NUM_SHIPS];
    battleship *p2_ships[NUM_SHIPS];

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
        int sizes[5];
        for (int i = 0; i < NUM_SHIPS; i++)
        {
            cout << "Enter size for ship " << i + 1;
            cin >> sizes[i];
        }
        gen_ships(p1_ships, NUM_SHIPS, sizes);
        gen_ships(p2_ships, NUM_SHIPS, sizes);
    }
    else
    {
        // Default ship sizes
        int sizes[5] = {5, 4, 3, 3, 2};
        gen_ships(p1_ships, NUM_SHIPS, sizes);
        gen_ships(p2_ships, NUM_SHIPS, sizes);
    }
    char temp;
    cout << "**********player 1 turn**********" << endl;
    place_ships(p1_grid, p1_ships, NUM_SHIPS); // gets the x and y
    print_screen(p1_grid, NUM_SHIPS);           // prints the grid

    stall();
    system(CLEAR_SCREEN);

    cout << "**********player 2 turn**********" << endl;
    place_ships(p2_grid, p2_ships, NUM_SHIPS); // gets the x and y
    print_screen(p2_grid, NUM_SHIPS);          // prints the grid

    stall();
    system(CLEAR_SCREEN);

    while (!game_over(p1_grid) && !game_over(p2_grid))
    {
        cout << "**********player 1 turn**********" << endl;
        attack(p2_grid, p1_atk_grid);

        system(CLEAR_SCREEN);

        cout << "**********player 2 turn**********" << endl;
        attack(p1_grid, p2_atk_grid);
        system(CLEAR_SCREEN);
    }

    cout << "Game is over!";
    clear_ships(p1_ships, NUM_SHIPS);
    clear_ships(p2_ships, NUM_SHIPS);

    return 0;
}