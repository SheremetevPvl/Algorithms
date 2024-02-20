/*1.7. Шашки (5)
На шахматном поле расположены N черных и одна белая шашка. Требуется написать программу, которая по заданному расположению шашек определяет, 
какое максимальное количество шашек может взять белая шашка за один ход. Черная шашка сразу после взятия снимается с доски.
Ввод из файла INPUT.TXT. Задается 8 строк, каждая содержит 8 символов. Символом ‘0’ обозначается пустая клетка, символом ‘1’ положение черной шашки и символом ‘2’ - положение белой шашки.
Вывод в файл OUTPUT.TXT. Вывести единственное число – максимальное количество черных шашек, которых можно взять за один ход.
Пример
Ввод
00010101
00000000
01010100
00000000
01010100
00000000
01010100
20000000
Вывод 
9
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>

const char START_CHECKER_POS_CH = '2';
const char PRESENCE_OF_CHECKER_CH = '1';
const char FREE_SPACE_CH = '0';
const int FIELD_SIZE = 8;
const std::string INPUT = "INPUT.txt";
const std::string OUTPUT = "OUTPUT.txt";

std::vector <std::vector<char>>
ReadFieldFromFile(const std::string& fileName)
{
    std::vector<std::vector<char>> fieldByVectors;
    std::ifstream file(fileName);

    if (!file.is_open()) 
    {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return fieldByVectors;
    }

    std::string line;
    while (std::getline(file, line)) 
    {
        std::vector<char> horizStr;
        std::istringstream iss(line);
        char cell;
        while (iss >> cell) 
        {
            horizStr.push_back(cell);
        }
        fieldByVectors.push_back(horizStr);
    }
    file.close();
    return fieldByVectors;
}

void WriteOutputInFile(const std::string& fileName, int output)
{
    std::fstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
    file << output << std::endl;
    file.close();
}

bool IsValidMove(int newColumn, int newRow, std::vector<std::vector<char>>& field)
{
    if (newColumn >= 0 && newColumn < FIELD_SIZE && newRow >= 0 && newRow < FIELD_SIZE)
    {
        if (field[newRow][newColumn] != PRESENCE_OF_CHECKER_CH)
        {
            return true;
        }
    }
    return false;
}

bool ThereIsNeigbCheker(int newColumn, int newRow, std::vector<std::vector<char>> field, int possibleColMove[], int possibleRowMove[], int index)
{
    int rowToCheck(newRow), colToCheck(newColumn);
    if (possibleRowMove[index] < 0)
    {
        rowToCheck++;
    }
    else
    {
        rowToCheck--;
    }
    if (possibleColMove[index] < 0)
    {
        colToCheck++;
    }
    else
    {
        colToCheck--;
    }
    if (field[rowToCheck][colToCheck] == PRESENCE_OF_CHECKER_CH)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void RemoveBattledChecker(int newColumn, int newRow, std::vector<std::vector<char>>& field, int possibleColMove[], int possibleRowMove[], int index)
{
    int columnOfChecker = newColumn, rowOfChecker = newRow;
    if (possibleRowMove[index] < 0)
    {
        rowOfChecker++;
    }
    else
    {
        rowOfChecker--;
    }
    if (possibleColMove[index] < 0)
    {
        columnOfChecker++;
    }
    else
    {
        columnOfChecker--;
    }
    field[rowOfChecker][columnOfChecker] = FREE_SPACE_CH;
}

int FindAllWaysToBitOthersFromCertPos(std::vector<std::vector<char>> field) 
{
    int startRow(0), startColumn(0);
    size_t maxColSize = field.size();
    size_t maxRowSize = field[maxColSize - 1].size();
    for (int row = 0; row < maxRowSize; row++)                         //поиск расположения начальной шашки
    {
        for (int column = 0; column < maxRowSize; column++)
        {
            if (field[row][column] == START_CHECKER_POS_CH)            //для векторов всё начинается с нуля
            {
                startRow = row;
                startColumn = column;
                break;
            }
        }
    }
    int possibleColChange[] = {-2, 2, 2, -2};                          // лево+верх право+верх право+низ лево+низ
    int possibleRowChange[] = {-2, -2, 2, 2};
    std::queue<std::pair<int, int>>runQueue;
    runQueue.push({ startRow,  startColumn });
    int maxWays(0);
    while (!runQueue.empty())                           //BFS обход
    {
        int row = runQueue.front().first;
        int column = runQueue.front().second;
        runQueue.pop();
        for (int i = 0; i < 4; i++)
        {
            int newCol = column + possibleColChange[i];
            int newRow = row + possibleRowChange[i];
            if (IsValidMove(newCol, newRow, field))                  //если мы не можем попасть за шашку, то и нет смысла проверять соседа в этом направлении
            {
                if (ThereIsNeigbCheker(newCol, newRow, field, possibleColChange, possibleRowChange, i))
                {
                    RemoveBattledChecker(newCol, newRow, field, possibleColChange, possibleRowChange, i);
                    maxWays++;                                       //считает при любой добавке в очередь
                    runQueue.push({ newRow, newCol });
                }
            }
        }
    }
    return maxWays;
}

int main()
{
    std::vector<std::vector<char>> field = ReadFieldFromFile(INPUT);
    /*for (const auto& vec : field) 
    {
        for (char num : vec) 
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }*/
    int maxMoves = FindAllWaysToBitOthersFromCertPos(field);
    WriteOutputInFile(OUTPUT, maxMoves);
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
