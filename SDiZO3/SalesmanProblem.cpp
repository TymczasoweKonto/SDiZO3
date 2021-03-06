#include "stdafx.h"
#include "SalesmanProblem.h"


SalesmanProblem::SalesmanProblem()
{
}


SalesmanProblem::~SalesmanProblem()	//Uwa�a� tutaj
{
	for (int i = 0; i < amountOfCities; i++)
	{
		delete[] distanceMatrix[i];
	}
	delete[] distanceMatrix;
}

bool SalesmanProblem::loadFromFile(std::string fileName)
{
	fstream file;
	file.open(fileName, ios::in);

	if (file.is_open())
	{
		if (file.fail())
		{
			return false;
		}
		file >> amountOfCities;
		distanceMatrix = new int*[amountOfCities];
		for (int i = 0; i < amountOfCities; i++)
		{
			distanceMatrix[i] = new int[amountOfCities];
		}

		for (int i = 0; i < amountOfCities; i++)
		{
			for (int j = 0; j < amountOfCities; j++)
			{
				file >> distanceMatrix[i][j];
			}
		}

	}
	else
	{
		return false;
	}

	file.close();
	return true;
}

void SalesmanProblem::greedyAlgorithm()
{
	int *visited = new int[amountOfCities]; //visited, 1 oznacza odwiedzono, 0 - miasto nie by�o odwiedzone
	vector<int> bestRoute;
	int totalCost = 0;
	for (int i = 0; i < amountOfCities; i++)
	{
		visited[i] = 0;
	}

	int start = 0; //Przyjmuj� pierwsze miasto jako punkt startowy i ko�cowy podr�y
	pair <int, int> tempClosestCity; // Tymczasowe najbli�sze miasto, <odleg�o��, indeks>
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > tempRouteQueue; //Kolejka dr�g, wybiera najkr�tsz� <Koszt, Miasto docelowe>
	int currentCity = start; //Aktualnie odwiedzane miasto
	bestRoute.push_back(start); //Umieszczam punkt startowy w �cie�ce
	visited[start] = 1; 
	
	for (int i = 0; i < amountOfCities-1; i++)
	{
		for (int j = 0; j < amountOfCities; j++)
		{
			if (visited[j] == 0 && distanceMatrix[currentCity][j] != 0)
			tempRouteQueue.push(make_pair(distanceMatrix[currentCity][j], j));
			
		}
		tempClosestCity = tempRouteQueue.top(); //Wyci�gam z kolejki miasto o najmniejszym koszcie dotarcia
		bestRoute.push_back(tempClosestCity.second);
		visited[tempClosestCity.second] = 1;
		currentCity = tempClosestCity.second; //"Id�" do miasta o najmniejszym koszcie

		while (tempRouteQueue.size() >= 1)
		{
			tempRouteQueue.pop();
		}
		
	}
	bestRoute.push_back(start); // Dodaj� numer pierwszego wierzcho�ka

	for (int i = 0; i < bestRoute.size()-1; i++)
	{
		totalCost += distanceMatrix[bestRoute[i]][bestRoute[i + 1]];
	}

	//Wy�wietlanie

	cout << "Koszt podrozy: " << totalCost << endl;
	cout << "Droga: " << endl;
	for (int z = 0; z < amountOfCities; z++)
	{
		cout << bestRoute[z] << " --> ";
	}
	cout << bestRoute[amountOfCities];
	cout << endl;

	delete[] visited;
}

void SalesmanProblem::bruteforce() //Permutacje wszystkich �cie�ek
{
	int *cities = new int[amountOfCities-1]; //Tablica miast
	int tempCost = 0;
	int bestCost = 0;
	int *bestRoute = new int[amountOfCities];
	for (int i =0; i < amountOfCities-1; i++)
	{
		cities[i] = i+1;
		
	}
	
	//sort(cities, cities+amountOfCities);

	do
	{
		tempCost = 0;
		tempCost += distanceMatrix[0][cities[0]];
		for (int i = 0; i < amountOfCities - 2; i++)
		{
			tempCost += distanceMatrix[cities[i]][cities[i + 1]];
		}
		
		tempCost += distanceMatrix[cities[amountOfCities-2]][0];
		

		if (tempCost < bestCost || bestCost == 0)
		{
			bestCost = tempCost;
			bestRoute[0] = 0;
			for (int i = 0; i < amountOfCities; i++)
			{
				bestRoute[i+1] = cities[i];
			}
		}

	} while (next_permutation(cities, cities + amountOfCities-1));
	

	//Wy�wietlanie


	cout << "Koszt: " << bestCost << endl << "Najlepsza droga: " << endl;
	for (int i = 0; i < amountOfCities; i++)
	{
		cout << bestRoute[i] << " --> ";
	}
	cout << "0" << endl;

	delete[] cities;
	delete[] bestRoute;
}

void SalesmanProblem::print()
{
	cout << "Ilosc miast: " << amountOfCities << endl;

	cout << setw(4) << "  ";
	for (int i = 0; i < amountOfCities; i++)
	{
		cout << setw(3) << " | " << setw(3) << i;
	}
	cout << setw(3) << " | " << endl;
	for (int i = 0; i < amountOfCities; i++)
	{
		cout << i << setw(3) << "|";
		for (int j = 0; j < amountOfCities; j++)
		{
			
				cout << setw(3) << " : " << setw(3) << distanceMatrix[i][j];
			
			
		}
		cout << setw(3) << " : " << endl;
	}
}
