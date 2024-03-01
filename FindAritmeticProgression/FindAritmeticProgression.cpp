/*4.1. Прогрессия (6)
Король Камбузии с детства боится несчастливых арифметических прогрессий с разностью 13. Однажды ему представили список расходов на нужды подданных, 
состоящий из N чисел. Король потребовал оставить только такую начальную часть списка, в которой не скрывается несчастливая арифметическая прогрессия. 
Либеральная общественность, считаясь с мнением короля, настаивает, тем не менее, на сохранении как можно большей части списка. 
Найти максимальное значение K такое, что из первых K чисел списка невозможно выделить M чисел, следующих в порядке их нахождения в списке и образующих 
последовательные члены несчастливой арифметической прогрессии. Выдать члены первой обнаруженной несчастливой прогрессии. 
Ввод из файла INPUT.TXT. Первая строка содержит два целых положительных числа N и M, разделенных пробелом: N – количество чисел в списке, 
а M – недопустимое число членов прогрессии. Вторая строка содержит список расходов в виде целых положительных чисел. 
Ограничения: 2 ≤ N, M ≤ 5000, 1 ≤ Xi ≤ 65000, время 1 с.
Вывод в файл OUTPUT.TXT. В первой строке выводится единственное число K- максимальное количество начальных чисел списка, не содержащих в качестве подсписка 
M последовательных членов несчастливой арифметической прогрессии. Во второй строке выводятся через пробел члены первой обнаруженной несчастливой прогрессии. 
Если ее не обнаружено, вывести No.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

const std::string INPUT_FILE_NAME = "Input.txt";
const std::string OUTPUT_FILE_NAME = "Output.txt";
const std::string FILE_IS_MISSING_MSG = "Input file is missing";
const std::string MIN_LIMIT_IS_REACHED_MSG = "Quality of num is too small";
const std::string MAX_LIMIT_IS_REACHED_MSG = "Avalible size of progression is too big";
const int UNLUCK_PROGRESSION_STEP = 13;
const int MIN_NUM_QUAL_LIMIT = 2;
const int NUM_PROG_LIMIT = 5000;
const int MAX_NUM = 65000;

struct ArrRec
{
	int num;
	int order;
};

int CheckProgrAndGetIt(std::vector<ArrRec>& numRow, int maxProgr, int num, std::vector<int>& progression, bool& found)
{
	//bool progrStart = false;
	int numOfProgrMem = 1;
	int order = numRow[num].order;
	progression.push_back(num);
	while (numOfProgrMem < maxProgr)
	{
		num = num - UNLUCK_PROGRESSION_STEP;
		if (num > 0)
		{
			if (numRow[num].num != num)
			{
				progression.clear();
				return 0;
			}
			else
			{
				if (numRow[num].order < order)
				{
					order = numRow[num].order;
					progression.push_back(num);
					numOfProgrMem++;
				}
				else
				{
					progression.clear();
					return 0;
				}
			}
		}
		else
		{
			progression.clear();
			return 0;
		}
	}
	found = true;
}

void GoThroughInputAndFindProg(std::fstream& input, std::fstream& output, int maxProgr)
{
	std::vector<int>unluckProgression;
	const ArrRec startRec = { -1, 0 };
	std::vector<ArrRec> numRow(MAX_NUM, startRec);
	bool found = false;
	int numOrder(0);
	while (!input.eof() && !found)
	{
		int num(0);
		input >> num;
		numOrder++;
		if ((num >= 1) && (num <= MAX_NUM))
		{
			numRow[num].num = num;
			numRow[num].order = numOrder;
			CheckProgrAndGetIt(numRow, maxProgr, num, unluckProgression, found);
		}
		else
		{
			std::cout << "Meet num out of diapazon\n";
		}
	}
	if (found)
	{
		output << numOrder - 1 << "\n";
		for (std::vector<int>::reverse_iterator num = unluckProgression.rbegin(); num != unluckProgression.rend(); ++num)
		{
			output << *num << " ";
		}
		output << std::endl;
	}
	else
	{
		output << "No" << std::endl;
	}
}

int main()
{
	std::fstream inputFile(INPUT_FILE_NAME), outputFile(OUTPUT_FILE_NAME);
	if (inputFile.is_open())
	{
		std::string line;
		int numQual, maxNumOfProg;
		inputFile >> numQual >> maxNumOfProg;
		if (numQual < MIN_NUM_QUAL_LIMIT)
		{
			std::cout << MIN_LIMIT_IS_REACHED_MSG;
			return 0;
		}
		if (maxNumOfProg > NUM_PROG_LIMIT)
		{
			std::cout << MAX_LIMIT_IS_REACHED_MSG;
			return 0;
		}
		GoThroughInputAndFindProg(inputFile, outputFile, maxNumOfProg);
		inputFile.close();
		outputFile.close();
	}
	else
	{
		std::cout << FILE_IS_MISSING_MSG;
	}
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
