#include <iostream>
class myCalendar
{
// Part 1
private:
	int year;
	int firstDayOfYear;
public:
	// Part 2
	myCalendar(int y, int first)
	{
		year = y;
		firstDayOfYear = first;
	}
	// Part 3
	int findNumberOfDays(int month)
	{
		switch (month)
		{
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 2:
			if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
				return 29;
			else return 28;
		default:
			return 31;

		}
	}
	// Part 4
	int findFirstDayOfMonth(int month)
	{
		int i = firstDayOfYear;
		for (int j = 1; j < month; j++)
			i = (i + findNumberOfDays(j)) % 7;
		return i==0?7:i;
	}
	// Part 5
	void printMonth(int numberOfDays, int firstDay)
	{
		std::cout << "Su Mo Tu We Th Fr Sa" << std::endl;
		int i;
		for (i = 1; i < firstDay; i++)
			std::cout << "   ";
		i = 1;
		while(i <= numberOfDays)
		{
			if (firstDay > 7)
			{
				std::cout << std::endl;
				firstDay = 1;
			}
			std::cout << i << " ";
			if (i < 10)
				std::cout << " ";
			firstDay++;
			i++;
		}
		std::cout << std::endl;
		return;
	}
	// Part 6
	void printYear()
	{
		for (int i = 1; i < 13; i++)
			printMonth(findNumberOfDays(i), findFirstDayOfMonth(i));
		return;
	}
	// Part 7
	int findDay(int month, int day)
	{
		int i = (findFirstDayOfMonth(month) - 1 + day) % 7;
		return i==0?7:i;
	}
};

// Part 8
int main()
{
	int input1;
	int input2;
	std::cout << "Enter a year:" << std::endl; std::cin >> input1;
	std::cout << "Enter a day of the week:" << std::endl; std::cin >> input2;
	myCalendar cal(input1,input2);
	cal.printYear();
	std::cout << "Enter a month:" << std::endl; std::cin >> input1;
	std::cout << "Enter a day of that month:" << std::endl; std::cin >> input2;
	std::cout << cal.findDay(input1,input2) << std::endl;
}