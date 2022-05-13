#include <iostream>
#include "windows.h"
using namespace std;


void coffee_machine(int& number_of_coffee, int time, int how_much_is_needed) {
	Sleep(time * 1000); //this function counts the time in thousandths of a second
	number_of_coffee -= 1;
}

void cappuccinator(int& number_of_milk, int time, int how_much_is_needed) {
	Sleep(time * 1000); //this function counts the time in thousandths of a second
	number_of_milk -= 1;
}

int random() {
	srand(time(NULL));
	return rand();
}

int cappuccino(int& number_of_coffee, int& number_of_milk, int& number_of_syrup, int time_of_make) {
	//check if there are enough ingredients and return 1 if cooked, otherwise 0
	if (number_of_coffee >= 2 && number_of_milk >= 2 && number_of_syrup >= 1) {
		cappuccinator(number_of_milk, time_of_make, 2);
		coffee_machine(number_of_coffee, time_of_make, 2);
		number_of_syrup -= 1;
		return 1;
	}
	else {
		return 0;
	}
}

int late(int& number_of_coffee, int& number_of_milk, int time_of_make) {
	//check if there are enough ingredients and return 1 if cooked, otherwise 0
	if (number_of_coffee >= 1 && number_of_milk >= 1) {
		cappuccinator(number_of_milk, time_of_make, 1);
		coffee_machine(number_of_coffee, time_of_make, 1);
		return 1;
	}
	else {
		return 0;
	}
}

int espresso(int& number_of_coffee, int time_of_make) {
	//check if there are enough ingredients and return 1 if cooked, otherwise 0
	if (number_of_coffee >= 5) {
		coffee_machine(number_of_coffee, time_of_make, 5);
		return 1;
	}
	else {
		return 0;
	}
}

int dessert(int& number_of_desserts, int time_of_get) {
	//check if there are enough desserts in stock and return 1 if there is, otherwise 0
	if (number_of_desserts >= 1) {
		Sleep(time_of_get * 1000);
		number_of_desserts -= 1;
		return 1;
	}
	else {
		return 0;
	}

}

int order(int& queue, int& count_of_visitors, int& number_of_desserts, int& number_of_coffee_sids, int& number_of_milk_bottles, int& number_of_syrup, int& time_of_make) {
	// function for service clients 
	int rating = 0;
	if (queue) {
		int order = random() % 3 + 2;

		if (order == 1) {
			int value = dessert(number_of_desserts, time_of_make);
			if (value == 1) {
				rating += 5;
			}
			else {
				rating += 1;
			}
		}

		else if (order == 2) {
			int value = cappuccino(number_of_coffee_sids, number_of_milk_bottles, number_of_syrup, time_of_make);
			if (value == 1) {
				rating += 5;
			}
			else {
				rating += 1;
			}
		}

		else if (order == 3) {
			int value = late(number_of_coffee_sids, number_of_milk_bottles, time_of_make);
			if (value == 1) {
				rating += 5;
			}
			else {
				rating += 1;
			}
		}

		else {
			int value = espresso(number_of_coffee_sids, time_of_make);
			if (value == 1) {
				rating += 5;
			}
			else {
				rating += 1;
			}
		}
		count_of_visitors += 1;
		queue -= 1;

	}

	else {
		//cout << "Empty" << endl;
	}

	return rating;
}

void coffee_house(int number_of_desserts, int number_of_coffee_sids, int number_of_milk_bottles, int number_of_syrup, int time_of_work, int time_of_visits, int time_of_make, int time_of_wait) {
	// model action
	int rating = 0;
	int count_of_visitors = 0;
	int time_work = 1;
	int first_queue = 0;
	int second_queue = 0;
	while (time_of_work + 1 != time_work)
	{
		cout << "Number of visitors in first queue: " << first_queue << endl;
		cout << "Number of visitors in second queue: " << second_queue << endl;
		cout << "Rating: " << rating << endl;

		// adding newly arrived visitors to the queue
		for (int i = 0; i < time_of_visits; i++) {
			if ((random() + i) % 2 == 0) {
				first_queue += 1;
			}
			else {
				second_queue += 1;
			}
		}

		//if the waiting time for the order has passed, the visitors who have not been served leave
		if (time_of_wait % time_work == 0) {
			for (int i = 0; i < time_of_visits; i++) {
				if ((random() + i) % 2 == 0) {
					if (first_queue > 0) {
						first_queue -= 1;
					}
				}
				else {
					if (second_queue > 0) {
						second_queue -= 1;
					}
				}
			}
		}


		rating += order(first_queue, count_of_visitors, number_of_desserts, number_of_coffee_sids, number_of_milk_bottles, number_of_syrup, time_of_make);
		rating += order(second_queue, count_of_visitors, number_of_desserts, number_of_coffee_sids, number_of_milk_bottles, number_of_syrup, time_of_make);
		time_work += 1;
	}

	auto avarage_rating = rating / count_of_visitors;
	cout << "Today rating is: " << avarage_rating << endl;
}



void main() {
	cout << "Start !" << endl;
	// parameters(number_of_desserts, number_of_coffee_sids, number_of_milk_bottlesnumber_of_syrup, time_of_work, time_of_visits, time_of_make, time_of_wait)
	coffee_house(10, 10, 10, 10, 10, 10, 0.5, 3);
	cout << "Finish !" << endl;
}