#include "DataInitialize.h"
#include <fstream>
#include <ctime>
#include "stdlib.h"
#include <iostream>
using namespace std;
Data::Data()
{
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < MOVIE_NUMBER;j++)
		{
			KCenters[i][j] = 0;
		}
	}
}

void Data::initKCenters()
{
	ofstream ofile("Kcenter1.dat");
	srand((int)time(NULL));
	for (int i = 0; i < K; i++)
	{

		for (int j = 0; j < MOVIE_NUMBER; j++)
		{
			KCenters[i][j] = rand() % 5 + 1;
			ofile << KCenters[i][j] << "\t";
		}
		ofile << endl;
	}
	ofile.close();
	/*ifstream infile("Kcenter1.dat",ios::in);
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < MOVIE_NUMBER; j++)
		{
			infile>>KCenters[i][j];
		}
	}
	infile.close();*/
}

void Data::initUsers()
{
	ifstream infile("rating1.dat", ios::in);
	int atr = 0;
	int j = 0;
	while ((infile >> users[atr].UserID) && (atr<USER_NUMBER))
	{
	//	cout << movies[atr].MovieID << " ";
		j = 0;
		while (j<MOVIE_NUMBER)
		{
			infile >> users[atr].Coordinate[j];
		//	cout << movies[atr].Coordinate[j] << " ";
			j++;
			
		}
		atr++;
	//	cout << endl;
	}
	cout << atr << "+" << j << endl;
	infile.close();
	//getchar();
}