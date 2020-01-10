// A Debugging Exercise by Marc Chee (marcc@aie.edu.au)
// 18/12/2016

// Marines are trying to "de-bug" an area (haha . . . haha)
// However something's up with this code . . . figure out what's going wrong
// When you're finished, there should be no compiler errors or warnings
// The encounter should also run and finish correctly as per the rules in the comments

// In many cases there are differences between what's in otherwise identical sections
// for Marines and Zerglings. It's good to be able to tell what the differences are
// and why they might be important.

// What's efficient and inefficient? Why?
// What uses more memory and what doesn't? Why?

// Last modified by Terry Nguyen (terryn@aie.edu.au)
// 10/09/2019

#include <iostream>
#include "Marine.h"
#include "Zergling.h"

using std::cout;
using std::endl;


//Are a group of entities alive?
int alive(Entity * arr, size_t arrSize)
{
	int check = 0;
	for (int a = 0; a < arrSize; a++)
	{
		if (arr[a].isAlive()) check++;
	}
	return check;
}

int main()
{
	size_t squadSize = 10;
	Marine * squad = new Marine[squadSize];
	size_t swarmSize = 20;
	Zergling * swarm = new Zergling[swarmSize];
	int zergTarget = 0;
	int marineTarget = 0;
	bool turn = false;

	cout << "A squad of marines approaches a swarm of Zerglings and opens fire! The Zerglings charge!" << endl;
	// Attack each other until only one team is left alive
	while (alive(squad, squadSize) && alive(swarm, swarmSize)) // If anyone is left alive to fight . . .
	{
		if (alive(squad, squadSize) && !turn) // if there's at least one marine alive
		{
			for (size_t i = 0; i < squadSize; i++) // go through the squad
			{
				// each marine will attack the first zergling in the swarm
				cout << "A marine fires for " << squad[i].attack() << " damage. " << endl;
				int damage = squad[i].attack();
				swarm[zergTarget].takeDamage(damage);
				if (!swarm[zergTarget].isAlive()) // if the zergling dies, it is marked as such
				{
					cout << "The zergling target dies." << endl;
					cout << "There are " << alive(swarm, swarmSize) << " zerglings left." << endl;
					if (zergTarget < (swarmSize - 1)) {
						zergTarget++;
						turn = !turn;
					}
				}
				break;
			}
		}
		if (alive(swarm, swarmSize) && turn) // if there's at least one zergling alive
		{
			for (size_t i = 0; i < swarmSize; i++) // loop through zerglings
			{
				cout << "A zergling attacks for " << swarm[i].attack() << " damage." << endl;
				squad[marineTarget].takeDamage(swarm[i].attack());
				if (!squad[marineTarget].isAlive())
				{
					cout << "The marine succumbs to his wounds." << endl;
					cout << "There are " << alive(squad, squadSize) << " marines left." << endl;
					if (marineTarget < (squadSize - 1)) {
						marineTarget++;
						turn = !turn;
					}
				}
				break;
			}
		}
	}
	// Once one team is completely eliminated, the fight ends and one team wins
	cout << "The fight is over. ";
	if (alive(squad, squadSize))
	{
		cout << "The Marines win." << endl;
	}
	else
	{
		cout << "The Zerg win." << endl;
	}
	std::cin;
	return 0;
}