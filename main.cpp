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
    char lable = 'B';
    int num = 1;
    int x_row = -1;
    int y_col = -1;
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
                    cout << "0";
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

        cout << "Enter X: ";
        cin >> x;

        cout << "Enter Y: ";
        cin >> y;

        cout << "H(0) / V(1): ";
        cin >> dir;

        grid(length, width, num_rows, coords);
        size = get_size(ship_choice);
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
        printArr(coords);
        grid(length, width, num_rows, coords);
    }
    return 0;
}
