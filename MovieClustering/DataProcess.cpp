#include "DataProcess.h"
#include "DataInitialize.h"
#include "Movie.h"
#include <iostream>
#include <fstream>
using namespace std;
DataProcess::DataProcess()
{
	overFlag = false;
	//data
	data = new Data();
	for (int i = 0; i < K;i++)
	{
		distance[i] = 0;
		counts[i] = 0;
		userCluster[i] =new User[500];
	}
	data->initKCenters();
	data->initUsers();
	cout << "初始化完成" << endl;
}


DataProcess::~DataProcess()
{
	for (int i = 0; i < K;i++)
	{
		delete userCluster[i];
	}
	delete data;
}

void DataProcess::userDistance(User user)
{
	
	for (int i = 0; i < K;i++)
	{
		int sum = 0;
		for (int j = 0; j < MOVIE_NUMBER;j++)
		{
			if (user.Coordinate[j]!=0)
			{
				sum += pow(data->KCenters[i][j] - user.Coordinate[j], 2);
			}
			
		}
		
		distance[i] = sqrt(sum);
	}

	float min_distance = MAX_DISTANCE;
	int atr = -1;
	for (int i = 0; i < K; i++)
	{
		if (distance[i]<min_distance)
		{
			min_distance = distance[i];
			atr = i;
		}
	}
	if (atr != -1)
	{

		userCluster[atr][counts[atr]] = user;
		counts[atr]++;
	}

}
void DataProcess::tanimotoDistance(User user)
{
	for (int i = 0; i < K;i++)
	{
		int sum1 = 0,sum2=0,sum3=0;
		for (int j = 0; j < MOVIE_NUMBER;j++)
		{
			sum1 += user.Coordinate[j] * data->KCenters[i][j];
			sum2 += pow(user.Coordinate[j], 2);
			sum3 += pow(data->KCenters[i][j], 2);
		}
		distance[i] = 1 - sum1 / (sqrt(sum2) + sqrt(sum3) - sum1);
	}
	float min_distance = MAX_DISTANCE;
	int atr = -1;
	for (int i = 0; i < K; i++)
	{
		if (distance[i] < min_distance)
		{
			min_distance = distance[i];
			atr = i;
		}
	}
	if (atr != -1)
	{

		userCluster[atr][counts[atr]] = user;
		counts[atr]++;
	}
}
void DataProcess::userClustering()
{
	
	//将所有的用户分类
	for (int i = 0; i < USER_NUMBER;i++)
	{
		userDistance(data->users[i]);
	}
	cout << "电影分类已完成,待写入文件!" << endl;
	ofstream ofile("cluster1.dat");
	for (int i = 0; i < K;i++)
	{
		
		ofile << i + 1 << "\t"<<counts[i] << endl;
		cout <<counts[i]<< "部电影， 质心为" << i + 1 << endl;
		for (int j = 0; j < counts[i];j++)
		{
			ofile << userCluster[i][j].UserID << "\t";
		}
		ofile << endl;
	}
	ofile.close();
	cout << "文件写入完成！" << endl;
	//重新计算质心
}
void DataProcess::analyseKCentsers()
{
	int s1 = 0, s2 = 0;
	for (int i = 0; i < K;i++)
	{
		
		for (int s= 0; s< MOVIE_NUMBER;s++)
		{
			s2 += data->KCenters[i][s];
			int sum = 0;
			int number = 0;
			for (int j = 0; j < counts[i]; j++)
			{
				if (userCluster[i][j].Coordinate[s]!=0)
				{

				sum += userCluster[i][j].Coordinate[s];
				number++;
				}
			}
			if (number != 0)
			{

				if (((float)sum / (float)number) >= ((sum / number) + 0.5))
				{
					s1 += fabs((float)(data->KCenters[i][s] -((sum / number) + 1)));
			data->KCenters[i][s] =( sum / number)+1;

				}
				else
				{
					s1 += data->KCenters[i][s] - (sum / number);
					data->KCenters[i][s] = (sum / number);
				}
			}
			else
			{
				s1 += data->KCenters[i][s];
				data->KCenters[i][s] = 0;
			//	cout << counts[i] << "i的值为：" << i << endl;
			}
			
		}

		distance[i] = 0;
		counts[i] = 0;

	}
	ofstream ofile("centers1.dat");
	for (int i = 0; i < K;i++)
	{
	ofile << i + 1 << endl;
	for (int j = 0; j < MOVIE_NUMBER;j++)
	{
	ofile << data->KCenters[i][j] << "\t";
	}
	ofile << endl;
	}
	ofile.close();
	if ((float)s1 / (float)s2 == 0)
	{
		overFlag = true;
	}
	cout << "变化率：" << (float)s1 / (float)s2 << endl;
}
bool DataProcess::getFlag()
{
	return overFlag;
}