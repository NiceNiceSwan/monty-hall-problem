#include <iostream>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

long int time_in_miliseconds()
{
    return duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

mt19937_64 random_number_generator(time_in_miliseconds());
uniform_int_distribution<int> one_in_three(0 , 2);

#define RUNS 100'000

bool game();

int main()
{
	unsigned long long int wins = 0;
	for (size_t i = 0; i < RUNS; i++)
	{
		if (game())
		{
			wins++;
		}
	}
	
	cout << "Wins: " << wins << endl;
	cout << "Win ratio: " << (double)wins/RUNS << endl;
}

bool game()
{
	vector<bool> doors(3, 0);
	int door_selected = one_in_three(random_number_generator);
	doors[door_selected] = true;

	door_selected = one_in_three(random_number_generator);
	bool skipped_goat = false;
	for (size_t i = 0; i < 3; i++)
	{
		if (door_selected == i)
		{
			continue;
		}
		if (!doors[i] && !skipped_goat)
		{
			skipped_goat = true;
			continue;
		}
		door_selected = i;
		break;
	}

	return doors[door_selected];
}
