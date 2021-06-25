#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
using namespace std;

class AttackInfo
{
	public:
		int damage;
		string description;

		AttackInfo(int damage, string description)
		{
			this->damage = damage;
			this->description = description;
		}

};



class BaseCharacter
{
	protected:
		string name;
		int strength;
		int agility;
		int intelligence;
		int maxHp;
		int presentHp;
		int dodgeChance;
		int baseDamage;

	public:
		BaseCharacter(string name,int strength, int agility, int intelligence, int maxHp, int dodgeChance, int baseDamage)
		{
			cout << "BaseClass Constructor" << endl;
			this->name = name;
			this->strength = strength;
			this->agility = agility;
			this->intelligence = intelligence;
			this->maxHp = maxHp;
			presentHp = maxHp;
			this->dodgeChance = dodgeChance;
			this->baseDamage = baseDamage;
	
		}
		
	    virtual AttackInfo* getAttack()
		{
			return primaryAttack();
		}

	    AttackInfo* primaryAttack()
		{
		
			AttackInfo* getPrimaryAttack = new AttackInfo(baseDamage, "strikes at ");
			return getPrimaryAttack;
		}

		AttackInfo* secondaryAttack()
		{
			
		}

		virtual void takeDamage(int amount)
		{
			presentHp -= amount;

			// Health will never be negative
			if (presentHp < 0)
			{
				presentHp = 0;
			}
		}
		
		virtual string toString()
		{	
			stringstream s;
			s << "Name: " << name << "\n";
			s << "Strength: " << strength << "\n";
			s << "Agility: " << agility << "\n";
			s << "Intelligence: " << intelligence << "\n";
			s << "PresentHp: " << presentHp << "\n";
			s << "MaxHp: " << maxHp << "\n";
			s << "Dodge: " << dodgeChance << "\n";
			s << "BaseDamage: " << baseDamage << "\n";
		
				
			return s.str();
		}

		string getName()
		{
			return name;
		}

		int getMaxHp()
		{
			return maxHp;
		}

		int getPresentHp()
		{
			return presentHp;
		}

		int getDodgeChance()
		{
			return dodgeChance;
		}
		
};

class WarriorClass : public BaseCharacter
{
	public:
		int resistance;

	public: 
		WarriorClass(string name, int strength, int agility, int intelligence, int maxHp, int dodgeChance, int baseDamage, int resistance) : BaseCharacter(name, strength, agility, intelligence, maxHp, dodgeChance, baseDamage)
		{
			cout << "Warrior Created" << endl;
			this->resistance = resistance;
		}

		AttackInfo* getAttack()
		{
			int randomNumber = rand() % 100 + 1;

			if (randomNumber < 90)
			{
				return primaryAttack();
			}
			return secondaryAttack();
		}

		AttackInfo* primaryAttack()
		{
			AttackInfo* getPrimaryAttack = new AttackInfo(baseDamage + baseDamage * (strength/20), "Brutally lashes out at ");
			return getPrimaryAttack;
		}

		AttackInfo* secondaryAttack()
		{
			if (dodgeChance < 50)
			{
				dodgeChance += (agility / 2);
			}
			else 
			{
				dodgeChance = 50;
			}
			
			
			AttackInfo* warriorSecondaryAttack = new AttackInfo(2, "Gets more agile and leaps at ");
			return warriorSecondaryAttack;
		}

		void takeDamage(int amount)
		{

			
			//presentHp -= amount - (resistance / 100) * amount;
			
			// hp 100	amount 20	resistance 10


			// Health will never be negative
			if (presentHp < 0)
			{
				presentHp = 0;
			}
		}

		string toString()
		{
			stringstream s;
			s << "Type: Warrior" << endl;
			s << BaseCharacter::toString();
			s << "Resistance: " << resistance << "\n";

			return s.str();
		}
};

class MageClass : public BaseCharacter
{

public:
	MageClass(string name, int strength, int agility, int intelligence, int maxHp, int dodgeChance, int baseDamage) : BaseCharacter(name, strength, agility, intelligence, maxHp, dodgeChance, baseDamage)
	{
		cout << "Mage Created" << endl;
	}

	AttackInfo* getAttack()
	{
		int randomNumber = rand() % 100 + 1;
		
		if (randomNumber < 70)
		{
			return primaryAttack();
		}

		return secondaryAttack();
	}

	

	AttackInfo* secondaryAttack()
	{
		AttackInfo* mageSecondaryAttack = new AttackInfo(baseDamage + baseDamage * (intelligence / 20.0), "throws a fireball at ");
		return mageSecondaryAttack;
	}

	string toString()
	{
		stringstream s;
		s << "Type: Mage" << endl;
		s << BaseCharacter::toString();

		return s.str();
	}
};

class PriestClass : public BaseCharacter
{

public:
	PriestClass(string name, int strength, int agility, int intelligence, int maxHp, int dodgeChance, int baseDamage) : BaseCharacter(name, strength, agility, intelligence, maxHp, dodgeChance, baseDamage)
	{
		cout << "Priest Created" << endl;
	}

	AttackInfo* getAttack()
	{
		int randomNumber = rand() % 100 + 1;

		if (randomNumber < 60)
		{
			return primaryAttack();
		}

		return secondaryAttack();
	}



	AttackInfo* secondaryAttack()
	{
		
		
		//Heals the priest
		presentHp += (5 + intelligence / 20);
	
		// Cant overheal
		if (presentHp > maxHp)
		{
			presentHp = maxHp;
		}

		AttackInfo* priestSA = new AttackInfo(0, "Heals themselves and smiles at ");
		return priestSA;
	}

	string toString()
	{
		stringstream s;
		s << "Type: Priest" << endl;
		s << BaseCharacter::toString();

		return s.str();
	}
};

class ArenaManager
{
private:
	BaseCharacter** contestantList;
	int maxContestants;
	int numContestants;

public:
	ArenaManager(int maxContestants)
	{
		this->maxContestants = maxContestants;
		numContestants = 0;
		contestantList = new BaseCharacter * [maxContestants];
	}

	bool addContestants(char type, string name, int strength, int agility, int intelligence, int maxHp, int dodge, int baseDamage)
	{
		
		if (numContestants < maxContestants)
		{
			if (type == 'm' || type == 'M')
			{
				BaseCharacter* newCharacter = new MageClass(name, strength, agility, intelligence, maxHp, dodge, baseDamage);
				contestantList[numContestants] = newCharacter;
				numContestants++;
			}
			else
			{
				BaseCharacter* newCharacter = new PriestClass(name, strength, agility, intelligence, maxHp, dodge, baseDamage);
				contestantList[numContestants] = newCharacter;
				numContestants++;
			}
			
			
			return true;
			
		}
		cout << "false";
		return false;
	}


	// Warrior creation
	bool addContestants(string name, int strength, int agility, int intelligence, int maxHp, int dodge, int baseDamage, int resistance)
	{
		if (numContestants < maxContestants)
		{
			BaseCharacter* newCharacter = new WarriorClass(name, strength, agility, intelligence, maxHp, dodge, baseDamage, resistance);
			contestantList[numContestants] = newCharacter;
			numContestants++;
	
			return true;

		}
		
		return false;
	}

	string viewContestant(int arrayIndex) 
	{

		stringstream s;

		// Displays choosable contestants
		for (int i = 0; i < numContestants; i++)
		{
			if (contestantList[arrayIndex] == contestantList[i])
			{
				cout << contestantList[arrayIndex]->toString() << endl;
			}
		}
		return s.str();
	}



	string viewAllContestants()
	{
	
		stringstream s;
		// Checks all contestants and prints there toString function
		for (int i = 0; i < numContestants; i++)
		{
			cout << "ID: " << i << endl;
			cout << contestantList[i]->toString() << "\n";
			
		}
		return s.str();
		
	}

	void simulateChallenge(int contestant1, int contestant2)
	{
		bool contestantEntry1 = false;
		bool contestantEntry2 = false;

		// Displays choosable contestants
		for (int i = 0; i < numContestants; i++)
		{
			if (contestantList[contestant1] == contestantList[i])
			{
				contestantEntry1 = true;
			}

			if (contestantList[contestant2] == contestantList[i])
			{
				contestantEntry2 = true;
			}
		}

		// Two valid contestants for the challenge
		if (contestantEntry1 == true && contestantEntry2 == true)
		{
			BaseCharacter* c1 = contestantList[contestant1];
			BaseCharacter* c2 = contestantList[contestant2];
			
			BaseCharacter* turn1;
			BaseCharacter* turn2;

			AttackInfo* attackInfo;
			
			int roundNumber = 0;
			bool turnSwap = false;


			int randomNumber = rand() % 100 + 1;

			// Contestant 1 goes first 
			if (randomNumber > 50)
			{
				turn1 = c1;
				turn2 = c2;
			}
			// Contestant 2 goes first by inverting turns
			else
			{
				turn1 = c2;
				turn2 = c1;
			}

			// Starting Battle
			while (c1->getPresentHp() > 0 && c2->getPresentHp() > 0)
			{
				system("CLS");
				roundNumber++;

				cout << "[Round " << roundNumber << "]" << endl << "\n";

				// First Turn
				if (turn1->getPresentHp() >= 0)
				{
					attackInfo = turn1->getAttack();
					cout << turn1->getName() << " " << attackInfo->description << turn2->getName() << " for " 
					<< attackInfo->damage << " damage" << endl << "\n";

					// Dodge Attempt
					int randomNumber = rand() % 100 + 1;
					
					if (turn2->getDodgeChance() < randomNumber)
					{
						turn2->takeDamage(attackInfo->damage);
					}
					// Cant dodge attacks that arent coming for you (Ex Priest heal)
					else if (attackInfo->damage != 0)
					{
						cout << turn2->getName() << " dodged it!" << endl << "\n";
					}
				}

				// Second turn
				if (turn2->getPresentHp() >= 0)
				{
					attackInfo = turn2->getAttack();
					cout << turn2->getName() << " " << attackInfo->description << turn1->getName() << " for "
					<< attackInfo->damage << " damage"<< endl << "\n";

					// Dodge Attempt
					int randomNumber = rand() % 100 + 1;

					if (turn1->getDodgeChance() < randomNumber)
					{
						turn1->takeDamage(attackInfo->damage);
					}
					
					// Cant dodge attacks that arent damaging (Ex Priest heal)
					else if(attackInfo->damage != 0)
					{
						cout << turn1->getName() << " dodged it!" << endl << "\n";
					}
				}

				// End of round stats
				cout << turn1->getName() << ": " << turn1->getPresentHp() << "/" << turn1->getMaxHp() << endl;
				cout << turn2->getName() << ": " << turn2->getPresentHp() << "/" << turn2->getMaxHp() << endl;
				
				//cout << c1->getName() << ": " << c1->getPresentHp() << "/" << c1->getMaxHp() << endl;
				//cout << c2->getName() << ": " << c2->getPresentHp() << "/" << c2->getMaxHp() << endl;

				system("PAUSE");
			}
		}

		

		// Back to main menu
		else
		{
			cout << "Please select 2 characters" << endl;
			return;
		}


		

	
	}


};


	
	


void userMenu()
{
	// Clears screen everytime gameMenu is called
	system("CLS");
	cout << "1: Add Contestant\n2: View Specific Contestant";
	cout << "\n3: View All Contestants\n4: Run Combat Challenge\n5: Exit" << endl;
}

void addContestant(ArenaManager & am)
{
	BaseCharacter* newCharacter;
	string name;
	int strength; 
	int agility; 
	int intelligence; 
	int maxHp; 
	int dodge; 
	int baseDamage; 
	int resistance;
	char type = 'o';

	system("CLS");
	cout << "     [Character Creation]" << endl << "\n";
	cout << "Pick a class for your character..." << endl;
	cout << "W = Warrior, M = Mage, P = Priest" << endl;

	// Makes sure user picks a class type
	while (type != 'w' && type != 'm' && type != 'p' && type != 'W' && type != 'M' && type != 'P')
	{
		cout << "Select: ";
		cin >> type;
	}
	

	getline(cin, name);
	cout << "Enter the name of your character: ";
	getline(cin, name);
	
	cout << "Enter a value for Strength: ";
	cin >> strength; 
	cout << "Enter a value for Agility: ";
	cin >> agility;
	cout << "Enter a value for Intelligence: ";
	cin >> intelligence;
	cout << "Enter a value for Maximum Hit Points: ";
	cin >> maxHp;
	cout << "Enter a value for dodge chance: ";
	cin >> dodge;
	cout << "Enter a value for Base Damage: ";
	cin >> baseDamage;

	// Only warrior type uses resistances
	
	if (type == 'w' || type == 'W')
	{
		cout << "Enter a value for Resistance: ";
		cin >> resistance;
		cout << endl;
		am.addContestants(name, strength, agility, intelligence, maxHp, dodge, baseDamage, resistance);
	}
	else
	{
		cout << endl;
		am.addContestants(type, name, strength, agility, intelligence, maxHp, dodge, baseDamage);
	}


	
	cout << "You successfully created " << name << endl;
	
	system("Pause");
	


}

void viewAllContestants(ArenaManager& am)
{
	system("CLS");
	cout << "     [All Characters]" << endl << "\n";
	am.viewAllContestants();
	system("Pause");
}

void viewContestant(ArenaManager& am)
{

	int userSelect;
	system("CLS");
	cout << "     [Character Viewer]" << endl << "\n";
	am.viewAllContestants();
	
	cout << "Select an character ID to view: ";
	cin >> userSelect;
	cout << endl;
	system("CLS");
	am.viewContestant(userSelect);
	system("Pause");
}

void runArena(ArenaManager& am)
{
	int contestantSelect1;
	int contestantSelect2;

	system("CLS");
	cout << "     [Battle Arena]" << endl << "\n";
	
	am.viewAllContestants();

	cout << "Select Two Contestants to enter the arena!" << endl << "\n";
	
	cout << "Contestant 1: ";
	cin >> contestantSelect1;

	cout << "Contestant 2: ";
	cin >> contestantSelect2;

	am.simulateChallenge(contestantSelect1, contestantSelect2);
	

}

int main()
{
	srand(time(NULL));
	ArenaManager am = ArenaManager(10);
	

	enum userChoices { addCharacter = 1, viewCharacter = 2, viewAllCharacters = 3, runCombat = 4, Exit = 5 };
	int userInput = 0;
	


	while (userInput != Exit)
	{
		
		
		userMenu();
		cout << endl;
		cout << "userInput: ";
	
		while (userInput < 1 || userInput > 5)
		{
			cin >> userInput;
		}
		

		if (userInput == addCharacter)
		{
			addContestant(am);
		}
		else if (userInput == viewCharacter)
		{
			viewContestant(am);
		}
		else if (userInput == viewAllCharacters)
		{
			viewAllContestants(am);
		}
		else if (userInput == runCombat)
		{
			runArena(am);
		}
		else if (userInput == Exit)
		{
			cout << "Thanks for playing!";
			return 0;
		}
		userInput = 0; 
		
	}
	
}