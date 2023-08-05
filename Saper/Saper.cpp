#include <iostream>
#include <random>
#include <string>
using namespace std;

struct ret
{
    int get;
    bool rep;
};

class Table
{
public:
    Table(int SIZE_X, int SIZE_Y)
    {
        this->SIZE_X = SIZE_X;
        this->SIZE_Y = SIZE_Y;

        arr = new int*[SIZE_Y];
        arr_g = new char*[SIZE_Y];

        for (size_t i = 0; i < SIZE_Y; i++)
        {
            arr[i] = new int[SIZE_X];
            arr_g[i] = new char[SIZE_X];
        }

        for (size_t i = 0; i < SIZE_Y; i++)
        {
            for (size_t j = 0; j < SIZE_X; j++)
            {
                arr_g[i][j] = 'X';
            }
        }
    }
    ~Table()
    {
        for (size_t i = 0; i < SIZE_Y; i++)
        {
            delete[] arr[i];
            delete[] arr_g[i];
        }
        delete[] arr;
        delete[] arr_g;
    }

    bool randomized() 
    {
        int x;
        int y;
        int bomb = 10;
        int count = 0;
        srand(time(NULL));

        for (size_t i = 0; i < SIZE_Y; i++)
        {
            for (size_t j = 0; j < SIZE_X; j++)
            {
                arr_g[i][j] = 'X';
            }
        }

        for (size_t i = 0; i < SIZE_Y; i++)
        {
            for (size_t j = 0; j < SIZE_X; j++)
            {
                arr[i][j] = 0;
            }
        }

        for (size_t i = 0; i < bomb;)
        {
            x = 1 + rand() % 7;
            y = 1 + rand() % 7;

            if (arr[y][x] != 9)
            {
                arr[y][x] = 9;
                i++;
            }
        }
        
        for (size_t i = 0; i < SIZE_Y; i++)
        {
            count = 0;
            for (size_t j = 0; j < SIZE_X; j++)
            {
                if (arr[i][j] == 9)
                {
                    continue;
                }

                if (j - 1 != -1 and arr[i][j - 1] == 9)
                {
                    count++;
                }
                if (j + 1 != 8 and arr[i][j + 1] == 9)
                {
                    count++;
                }
                if (i - 1 != -1 and arr[i - 1][j] == 9)
                {
                    count++;
                }
                if (i + 1 != 8 and arr[i + 1][j] == 9)
                {
                    count++;
                }

                if (i - 1 != -1)
                {
                    if (j - 1 != -1 and arr[i - 1][j - 1] == 9)
                    {
                        count++;
                    }
                    if (j + 1 != 8 and arr[i - 1][j + 1] == 9)
                    {
                        count++;
                    }
                }
                
                if (i + 1 != 8)
                {
                    if (j - 1 != -1 and arr[i + 1][j - 1] == 9)
                    {
                        count++;
                    }
                    if (j + 1 != 8 and arr[i + 1][j + 1] == 9)
                    {
                        count++;
                    }
                }

                arr[i][j] = count;
                count = 0;
            }
        }

        return true;
    }

    void print_tech() 
    {
        for (size_t i = 0; i < 9; i++)
        {
            if (i == 0)
            {
                cout << "# | ";
                continue;
            }
            cout << i << " ";
        }
        cout << endl;
        for (size_t i = 0; i < 9; i++)
        {
            cout << "--";
        }
        cout << endl;
        for (size_t i = 0; i < SIZE_Y; i++)
        {
            cout << i + 1 << " | ";
            
            for (size_t j = 0; j < SIZE_X; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }

    void print()
    {
        for (size_t i = 0; i < 9; i++)
        {
            if (i == 0)
            {
                cout << "# | ";
                continue;
            }
            cout << i << " ";
        }
        cout << endl;
        for (size_t i = 0; i < 9; i++)
        {
            cout << "--";
        }
        cout << endl;
        for (size_t i = 0; i < SIZE_Y; i++)
        {
            cout << i + 1 << " | ";

            for (size_t j = 0; j < SIZE_X; j++)
            {
                cout << arr_g[i][j] << " ";
            }
            cout << endl;
        }
    }

    ret input_coor(int x, int y)
    {
        if (arr_g[y - 1][x - 1] == 'X')
        {
            value.rep = false;
        }
        else
        {
            value.rep = true;
        }
        string a = to_string(arr[y - 1][x - 1]);
        arr_g[y - 1][x - 1] = a[0];
        value.get = arr[y - 1][x - 1];
        return value;
    }

private:
    int SIZE_X;
    int SIZE_Y;
    int** arr;
    char** arr_g;
    ret value;
};

int main()
{
    setlocale(LC_ALL, "ru");
    bool game = true;
    bool win = false;
    int x;
    int y;
    int element = 0;
    Table a(8, 8);
    ret value;
    
    //system("cls");

    while (true)
    {
        cout << "Õî÷åòå íà÷àòü íîâó ãðó?(1 - Òàê, 0 - Í³)" << endl;
        cin >> game;

        if (!game)
        {
            return 0;
        }
        system("cls");
        a.randomized();

        while (true)
        {
            a.print();
            cout << "Ââåä³òü êîîðäèíàòè X:";
            cin >> x;
            cout << "Ââåä³òü êîîðäèíàòè Y:";
            cin >> y;
            system("cls");
            value = a.input_coor(x, y);
            if (value.get == 9)
            {
                bool win = false;
                break;
            }
            else 
            {
                if (!value.rep)
                {
                    element++;
                }
                if (element == 54)
                {
                    bool win = true;
                    break;
                }
            }
        }

        if (win)
        {
            cout << "Âè ïåðåìîãëè!" << endl;
            continue;
        }

        cout << "Âè ïðîãðàëè!" << endl;
    }
    return 0;
}
