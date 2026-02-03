#include <iostream>
#include <algorithm>
#include <typeinfo>
using namespace std;

void line(const int length)
{
    cout << "   ";
    for (int i = 0; i < length; i++) 
    {
    cout << "*";
    }
    cout << endl;
}

bool contains(int arr[], int value, int arr_length)
{
    for (int i = 0; i < arr_length; i++)
    {
        if (*(arr + i) == value)
        {
            return true;
        }
    }
    return false;
}

void grid(int length, int width, int num_rows, int x[], int y[], int arr_length) 
{
    int space_between = length / num_rows;
    char lable = 'B';
    int num = 1;

    int row = 1;
    int col = 0;

    int space_count = 0;


    cout << "     A"; // Formatting 

    for (int i = 0; i < num_rows - 1; i++)
    {
        cout << "   ";
        cout << lable;
        lable += 1;
    }

    cout << endl;
    line(length);

    for (int j = 0; j < width; j++)
    {
        if (num >= 10)
        {
            cout << num << " ";
        } 
        else
        {
            cout << num << "  ";
        }
        num += 1;
        for (int i = 0; i < length; i++)
        {
            if (i % space_between == 0)
            {
                cout << "|";
                col += 1;
                space_count = 0;
            }
            else if (space_count == 1) {
                if (contains(x, col, arr_length) && contains(y, row, arr_length))
                {
                    cout << "*";
                }
            }
            else
            {
                cout << " ";
                space_count += 1;
            }
            row += 1;
        }
        cout << endl;
        line(length);
    }
    cout << endl;
}

void print_ships_options()
{
    cout << "Choose Ship Type:" << endl;
    cout << "1. BattleShip (5x1)" << endl;
    cout << "2. Destroyer  (4x1)" << endl;
    cout << "3. Tanker     (3x1)" << endl;
    cout << "4. Jet        (2x1)" << endl;
}

bool valid_ship_num(const int input)
{
    return input == 1 || input == 2 || input == 3 || input == 4;
}

bool valid_ship_chosen(const int input, bool ship_available[])
{
    if (input > 4 || input < 1)
    {
        return false;
    }
    return !*(ship_available + input - 1);
}

void place_ships(bool player_ships[], int *x, int *y)
{
    int input = -1;

    print_ships_options();
    cout << "Enter: " << endl;
    cin >> input;
 
    while (!valid_ship_num(input) || !valid_ship_chosen(
        input, &player_ships[0]))
    {
        cout << "Error, try again" << endl;
        cout << "Enter: ";
        cin >> input;
    }
    *(player_ships + (input - 1)) = false;
    
    cout << "Enter x Coord: ";
    cin >> *x;

    cout << endl;
    cout << "Enter y Coord: ";
    cin >> *y;
}

void fill_arr(int arr[], int value, int arr_length)
{
    for (int i = 0; i < arr_length; i++)
    {
        *(arr + i) = value;
    }
}

int main()
{
    // Screen const
    const int length = 49; 
    const int width = length / 4;
    const int num_rows = 12;

    // Game loop
    bool player_1_ships[4] = {false, false, false, false};
    int num_ships = 4;

    bool placing = true;

    bool running = true;
    bool player_1 = true; // If true player_1 turn, 
                          // otherwise player_2 turn


    int player_1_x[num_ships];
    int player_1_y[num_ships];
    int player_2_x[num_ships];
    int player_2_y[num_ships];
 
    fill_arr(&player_1_x[0], -1, num_ships);
    fill_arr(&player_1_y[0], -1, num_ships);
    fill_arr(&player_2_x[0], -1, num_ships);
    fill_arr(&player_2_y[0], -1, num_ships);

    // Game states
    grid(length, width, num_rows, player_1_x, player_1_y, num_ships);

    for (int i = 0; i < num_ships; i++)
    {
        int x = -1; 
        int y = -1;
        place_ships(player_1_ships, &x, &y);
        *(player_1_x + i) = x;
        *(player_1_y + i) = y;
        grid(length, width, num_rows, player_1_x, player_1_y, num_ships);
    }
    return 0;
}
