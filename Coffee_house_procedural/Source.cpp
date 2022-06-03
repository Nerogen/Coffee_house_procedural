#include <iostream>
#include <map>
using namespace std;


void coffee_machine(int& number_of_coffee, int how_much_is_needed, int time_of_make, int& current_time) {
	// make coffe from a few coffee beans and update time 
	number_of_coffee -= how_much_is_needed;
	current_time += time_of_make;
}

void cappuccinator(int& number_of_milk, int how_much_is_needed, int time_of_make, int& current_time) {
	// whipping milk and update time 
	number_of_milk -= how_much_is_needed;
	current_time += time_of_make;
}

int random() {
	// get new random number
	srand(time(NULL));
	return rand();
}

int cookingSpeed() {
	// get random number in range(1, 10)
	return random() % 3 + 10;
}

int cappuccino(int& number_of_coffee, int& number_of_milk, int& number_of_syrup, int time_of_make, int& current_time) {
	// check if there are enough ingredients and return 1 if cooked, otherwise 0
	if (number_of_coffee >= 2 && number_of_milk >= 2 && number_of_syrup >= 1) {
		cappuccinator(number_of_milk, 2, time_of_make, current_time);
		coffee_machine(number_of_coffee, 2, time_of_make, current_time);
		number_of_syrup -= 1;
		return 1;
	} else {
		return 0;
	}
}

int late(int& number_of_coffee, int& number_of_milk, int time_of_make, int& current_time) {
	// check if there are enough ingredients and return 1 if cooked, otherwise 0
	if (number_of_coffee >= 1 && number_of_milk >= 1) {
		cappuccinator(number_of_milk, 1, time_of_make, current_time);
		coffee_machine(number_of_coffee, 1, time_of_make, current_time);
		return 1;
	} else {
		return 0;
	}
}

int espresso(int& number_of_coffee, int time_of_make, int& current_time) {
	// check if there are enough ingredients and return 1 if cooked, otherwise 0
	if (number_of_coffee >= 5) {
		coffee_machine(number_of_coffee, 5, time_of_make, current_time);
		return 1;
	} else {
		return 0;
	}
}

int dessert(int& number_of_desserts, int delivery_time, int &current_time) {
	// check if there are enough desserts in stock and return 1 if there is, otherwise 0
	if (number_of_desserts >= 1) {
		number_of_desserts -= 1;
		current_time += delivery_time;
		return 1;
	} else {
		return 0;
	}
}

int order(int& queue, int& count_of_visitors, int& number_of_desserts, int& number_of_coffee, int& number_of_milk_bottles, int& number_of_syrup, int& time_of_make, int& current_time, map<int, int>& statistics) {
	// function for service clients 
	int rating = 0;
	if (queue) {

		int what_need_buy = random() % 3 + 2;

		if (what_need_buy == 1) {
			int made = dessert(number_of_desserts, time_of_make, current_time);
			if (made == 1) {
				rating += 5;
				statistics[what_need_buy] += 1;
			} else {
				rating += 1;
			}
		}

		else if (what_need_buy == 2) {
			int made = cappuccino(number_of_coffee, number_of_milk_bottles, number_of_syrup, time_of_make, current_time);
			if (made == 1) {
				rating += 5;
				statistics[what_need_buy] += 1;
				current_time += time_of_make;
			} else {
				rating += 1;
			}
		}

		else if (what_need_buy == 3) {
			int made = late(number_of_coffee, number_of_milk_bottles, time_of_make, current_time);
			if (made == 1) {
				rating += 5;
				statistics[what_need_buy] += 1;
				current_time += time_of_make;
			} else {
				rating += 1;
			}
		}

		else {
			int made = espresso(number_of_coffee, time_of_make, current_time);
			if (made == 1) {
				rating += 5;
				statistics[what_need_buy] += 1;
				current_time += time_of_make;
			} else {
				rating += 1;
			}
		}

		count_of_visitors += 1;
		queue -= 1;

	}

	return rating;
}

void coffee_house(int number_of_desserts, int number_of_coffee, int number_of_milk, int number_of_syrup, int time_of_work, int time_of_visits, int time_of_make, int time_of_wait) {
	// model action
	int rating = 0;
	int count_of_visitors = 0;
	int current_time = 1;
	int first_queue = 0;
	int second_queue = 0;
	map<int, int> statistics{ {1, 0}, {2, 0}, {3, 0}, {4,0}};

	while (time_of_work >= current_time)
	{
		cout << "Number of visitors in first queue: " << first_queue << endl;
		cout << "Number of visitors in second queue: " << second_queue << endl;
		cout << "Rating: " << rating << endl;

		// adding new arrived visitors to the queue
		for (int i = 0; i < time_of_visits; i++) {
			if ((random() + i) % 2 == 0) {
				first_queue += 1;
			} else {
				second_queue += 1;
			}
		}

		// if the waiting time for the order has passed, the visitors who have not been served leave
		if (time_of_wait % current_time == 0) {
			for (int i = 0; i < time_of_visits; i++) {
				if ((random() + i) % 2 == 0) {
					if (first_queue > 0) {
						first_queue -= 1;
					}
				} else {
					if (second_queue > 0) {
						second_queue -= 1;
					}
				}
			}
		}

		// first extend (speed of worker)
		int speed_of_kooking_for_first_worker = time_of_make / cookingSpeed();
		int speed_of_kooking_second_worker = time_of_make / cookingSpeed();
		// two calls 'cause we have two queues
		rating += order(first_queue, count_of_visitors, number_of_desserts, number_of_coffee, number_of_milk, number_of_syrup, speed_of_kooking_for_first_worker, current_time, statistics);
		rating += order(second_queue, count_of_visitors, number_of_desserts, number_of_coffee, number_of_milk, number_of_syrup, speed_of_kooking_second_worker, current_time, statistics);
		current_time += 1;
	}

	auto avarage_rating = rating / count_of_visitors;

	cout << "Today rating is: " << avarage_rating << endl;
	// last extend (all statistics) 
	cout << "Sales statistics for today: " << endl;
	cout << "Number of visitors: " << count_of_visitors << endl;
	cout << "number of sold desserts: " << statistics[1] << endl;
	cout << "number of sold cappuccino: " << statistics[2] << endl;
	cout << "number of sold late: " << statistics[3] << endl;
	cout << "number of sold espresso: " << statistics[4] << endl;
}



void main() {
	cout << "Start !" << endl;
	// parameters(number_of_desserts, number_of_coffee, number_of_milk, number_of_syrup, time_of_work, time_of_visits, time_of_make, time_of_wait)
	coffee_house(10, 10, 10, 40, 10, 10, 0.5, 3);
	cout << "Finish !" << endl;
}
