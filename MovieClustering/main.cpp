//#include <iostream>
//using namespace std;
//#include <fstream>
//#include "DataProcess.h"
//#include "DataInitialize.h"
//int main()
//{
//	DataProcess * dataProcess;
//	dataProcess = new DataProcess();
//	while (!dataProcess->getFlag())
//	{
//		dataProcess->userClustering();
//		dataProcess->analyseKCentsers();
//	}
//
//
//	getchar();
//	return 0;
//}
//
//
//
//
//
//

#include <iostream>
using namespace std;
#include <fstream>
#include<string>
int main()
{
	ifstream infile2("user-movie.dat", ios::in);
	ifstream infile1("cluster2.dat",ios::in);
	ofstream ofile("user-movie-cluster.dat");
	if (!infile1)
	{
		cout << "file1 error" << endl;
		return 0;
	}
	if (!infile2)
	{
		cout << "file2 error" << endl;
		return 0;
	}
	int id1=0, id2=0;
	string str="";
	while (infile1>>id1)
	{
		cout << id1 << endl;
		id2 = 0;
		bool flag = false;
		while (infile2>>id2)
		{
			getline(infile2, str);
			if (id1==id2)
			{
				flag = true;
				break;
			}
		}
		if (flag)
		{
			ofile << id1 << "\t" << str << endl;
		}
		id1 = 0;
	}
	infile1.close();
	infile2.close();
	ofile.close();
	cout << "over1" << endl;
	getchar();
	return 0;
}