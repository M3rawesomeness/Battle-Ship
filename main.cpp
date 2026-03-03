#include <iostream>

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

int contains(int **coords, int row, int col, int arr_length)
{
    for (int i = 0; i < arr_length; i++)
    {
        if (coords[i][0] == col && coords[i][1] == row)
        {
            return true;
        }
    }
    return false;
}

void grid(int length, int width, int num_rows, int coords[12][12])
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
            else if (space_count == 1 && coords[j % 3][i % 3] == 1)
            {
                cout << "O";
                space_count = 0;
            }

            else
            {
                cout << " ";
                space_count += 1;
            }
        }
        col = 0;
        row += 1;
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

int calc_len_ship(int ship)
{
    switch (ship)
    {
    case 1:
        return 5;
        break;
    case 2:
        return 4;
        break;
    case 3:
        return 3;
        break;
    case 4:
        return 2;
        break;
    default:
        return -1;
    }
}
void place_ships(bool player_ships[], int **coords, int index)
{
    int curr_ship = -1; // Default value, if stays, error
    // This donest work : int coords[] = all_coords;
    print_ships_options();
    cout << "Enter: " << endl;
    cin >> curr_ship;

    // Validate Inputs
    while (!valid_ship_num(curr_ship) ||
           !valid_ship_chosen(curr_ship, &player_ships[0]))
    {
        cout << "Error, try again" << endl;
        cout << "Enter: ";
        cin >> curr_ship;
    }
    *(player_ships + (curr_ship - 1)) = false;

    coords[index][3] = calc_len_ship(curr_ship);

    cout << "Enter X Coord: ";
    cin >> coords[index][0];

    cout << endl;
    cout << "Enter Y Coord: ";
    cin >> coords[index][1];

    cout << endl;
    cout << "Enter Direction(0 for H/1 for V): ";
    cin >> coords[index][2];
}

void fill_arr(int **arr, int value, int length1, int length2)
{
    for (int i = 0; i < length1; i++)
    {
        for (int j = 0; j < length2; j++)
        {
            arr[i][j] = value;
        }
    }
}

int main()
{
    // Screen const
    const int length = 49;
    const int width = length / 4;
    const int num_rows = 12;

    int coords[12][12]; // 0: No ship 1: ship
    // Fills the array 0
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            coords[i][j] = 0;
        }
    }

    grid(length, width, num_rows, coords);

    return 0;
}
