#include <cinttypes>
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
    int y_num = 1;
    int x_num = 1;
    int x_row = -1;
    int y_col = -1;
    int space_count = 0;

    cout << "     " << x_num; // Formatting
    x_num++;
    for (int i = 0; i < num_rows - 1; i++)
    {
        if (x_num < 11)
        {
            cout << "   ";
            cout << x_num;
        }
        else
        {
            cout << "  ";
            cout << x_num;
        }
        x_num += 1;
    }

    cout << endl;
    line(length);
    for (int j = 0; j < width; j++)
    {
        if (y_num >= 10)
        {
            cout << y_num << " ";
        }
        else
        {
            cout << y_num << "  ";
        }
        y_num += 1;
        x_row++;
        y_col = -1;
        for (int i = 0; i < length; i++)
        {
            if (i % space_between == 0)
            {
                cout << "|";
                y_col++;
                space_count = 0;
            }
            else if (space_count == 1)
            {
                if (coords[x_row][y_col] == 1)
                {
                    cout << "O";
                }
                else
                {
                    cout << " ";
                }
                space_count = 0;
            }
            else
            {
                cout << " ";
                space_count += 1;
            }
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
    cout << "Enter: ";
}

int get_size(int choice)
{
    switch (choice)
    {
    case 1:
        return 5;
    case 2:
        return 4;
    case 3:
        return 3;
    case 4:
        return 2;
    }
    return -1;
}

void printArr(int coords[12][12])
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            cout << coords[i][j] << " ";
        }
        cout << endl;
    }
}

bool valid_coords(int x, int y, int dir, int size, int coords[12][12])
{
    if (x > 12 || y > 12 || x < 1 || y < 1)
    {
        return false;
    }

    if (coords[x - 1][y - 1] == 1)
    {
        return false;
    }

    if (dir > 1 || dir < 0)
    {
        return false;
    }

    if (dir == 1)
    {
        for (int j = 0; j < size; j++)
        {
            if (coords[x + j - 1][y - 1] == 1)
            {
                return false;
            }
        }
    }
    else if (dir == 0)
    {
        for (int j = 0; j < size; j++)
        {
            if (coords[x - 1][y + j - 1] == 1)
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    // Screen const
    const int length = 49;
    const int width = length / 4;
    const int num_rows = 12;
    const int num_ships = 4;

    bool ships_chosen[] = {false, false, false, false};
    int coords[12][12]; // 0: No ship 1: ship
    int x, y, dir, size = -1;
    // Fills the array 0
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            coords[i][j] = 0;
        }
    }

    cout << "Player 1" << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int i = 0; i < num_ships; i++)
        {
            int ship_choice = -1;
            print_ships_options();
            cin >> ship_choice;

            while (ship_choice < 1 || ship_choice > 4 ||
                   ships_chosen[ship_choice - 1])
            {
                cout << "Ship Chosen Already" << endl;
                print_ships_options();
                cin >> ship_choice;
            }

            cout << "Enter x: ";
            cin >> y;

            cout << "Enter y: ";
            cin >> x;

            cout << "H(0) / V(1): ";
            cin >> dir;

            size = get_size(ship_choice);

            while (!valid_coords(x, y, dir, size, coords))
            {
                cout << "Coordinates chosen are unavailable" << endl;
                cout << "Please try again" << endl;
                cout << "Enter x: ";
                cin >> y;
                cout << "Enter y: ";
                cin >> x;
                cout << "H(0) / V(1): ";
                cin >> dir;
            }

            if (dir == 1)
            {
                for (int j = 0; j < size; j++)
                {
                    coords[x + j - 1][y - 1] = 1;
                }
            }
            else if (dir == 0)
            {
                for (int j = 0; j < size; j++)
                {
                    coords[x - 1][y + j - 1] = 1;
                }
            }
            else
            {
                cout << "Err";
            }

            grid(length, width, num_rows, coords);

            for (int i = 0; i < 20; i++)
            {
                line(50);
            }
            cout << "Player 2" << endl;
        }
    }
    return 0;
}
