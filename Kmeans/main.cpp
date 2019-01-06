#include<iostream>
#include<graphics.h>
#include<cmath>
#include<cstdlib>
#include<easyx.h>
#include<vector>
using namespace std;

//������ɵĵ����Ŀ
#define POINT_NUM 8000
//���ڵĴ�С
#define WIDTH 600
#define HEIGHT 600

struct point
{
  double x;          //�õ��X����
  double y;        //�õ��Y����
  int cluster;     //�õ��������������
};
/**
  ����ÿ���������õ���ɫ
**/
COLORREF color[15]=
{
  WHITE,YELLOW,RED,BLUE,GREEN,
  BROWN,LIGHTCYAN,MAGENTA,LIGHTRED,
  CYAN,LIGHTBLUE,LIGHTGREEN, DARKGRAY,
  LIGHTMAGENTA,LIGHTGRAY,
};

//��ʼ�������
void initCluster(vector<struct point*>& pointList,int num);

//������ɾ�������
void generateCenter(vector<struct point*>& center,int Num);

//�������еĵ�
void drawCluster(vector<struct point*>& pointList);

//���һ�����������
struct point* getCenter(vector<struct point*>& cluster);

//�������֮���ŷʽ����
double getDistance(struct point* pt1,struct point* pt2);

//��øõ������ľ��������
int getNearestCluster(vector<struct point*>& center,struct point* tempPoint);
//���е���
void iteration(vector<struct point*>& pointList,vector<struct point*>& center,int iterNum,int Knum);
//���¾�������
void updateCenter(vector<struct point*>& pointList,vector<struct point*>& center,int num);
//��������ÿ�����������
void drawCenter(vector<struct point*>& center);

int main()
{
  //���������Щ�������
  vector<struct point*> pointList;

  //���ڴ洢���������
  vector<struct point*> center;

  //�������Ŀ
  int Knum;
  int iteratorNum;        //��������
  cout<<"Please input the K number"<<endl;
  cin>>Knum;
  cout<<"Please input the iteratorNum number"<<endl;
  cin>>iteratorNum;
  initgraph(WIDTH,HEIGHT,SHOWCONSOLE);
  setbkcolor(BLACK);
  cleardevice();

  //��ʼ����Ⱥ
  initCluster(pointList,POINT_NUM);
  //������ɾ�������
  generateCenter(center,Knum);

  //��������
  iteration(pointList,center,iteratorNum,Knum);

  //�������еĵ�
  drawCluster(pointList);
  drawCenter(center);
  system("pause");
  closegraph();
  return 0;
}

/**
  ����������ӵ�
**/
void initCluster(vector<struct point*>& pointList,int num)
{
  cout<<"************************************"<<endl;
  cout<<"      init  cluster   "<<endl;
  for(int num=0;num<POINT_NUM;num++)
  {
    struct point* tempPoint = new point;
    tempPoint->x=rand()%WIDTH;
    tempPoint->y=rand()%HEIGHT;
    pointList.push_back(tempPoint);
  }
  cout<<"************************************"<<endl;
}


/**
��������յĻ�ͼ����
**/
void drawCluster(vector<struct point*>& pointList)
{
  cout<<"***********************************"<<endl;
  cout<<"          draw cluster"<<endl;
  for(vector<struct point*>::iterator it=pointList.begin();it!=pointList.end();it++)
  {
    setfillcolor(color[(*it)->cluster]);
    bar((int)(*it)->x,(int)(*it)->y,(int)(*it)->x+2,(int)(*it)->y+2);
  }
  cout<<"***********************************"<<endl;
}
/**
  ��ʼ����������
**/
void generateCenter(vector<struct point*>& center,int Num)
{
  cout<<"************************************"<<endl;
  cout<<"      generate  cluster  center  "<<endl;
  for(int i=0;i<Num;i++)
  {
    struct point* tempCenter= new point;
    tempCenter->x = rand()%WIDTH;
    tempCenter->y = rand()%HEIGHT;
    center.push_back(tempCenter);
  }
  for(vector<struct point*>::iterator it=center.begin();it!=center.end();it++)
  {
    cout<<"x    "<<(*it)->x<<"  y   "<<(*it)->y<<endl;
  }
  cout<<"************************************"<<endl;
}

/**
* ʹ�þ�ֵ���һ����Ⱥ������
**/
struct point* getCenter(vector<struct point*>& cluster)
{
  double x=0;
  double y=0;
  struct point* tempCenter=new point;
  for(vector<struct point*>::iterator it=cluster.begin();it!=cluster.end();it++)
  {
    x+=(*it)->x;
    y+=(*it)->y;
  }
  tempCenter->x = x/cluster.size();
  tempCenter->y = y/cluster.size();
  return tempCenter;
}

/**
*�õ�һ���������ľ��������
**/
int getNearestCluster(vector<struct point*>& center,struct point* tempPoint)
{
  //��һ��������ĵ�һ����֮�������
  vector<struct point*>::iterator it=center.begin();
  double  min =getDistance(tempPoint,*it);
  int index=0;
  double dist;
  for(int i=0;it!=center.end();it++,i++)
  {
    dist=getDistance(tempPoint,*it);
    if(dist<min)
    {
      //ֻ�г��ָ����ĵ�ʱ�Ż����
      min=dist;
      index=i;
    }
  }
  return index;
}
/**
  �������������֮���ŷʽ����
**/
double getDistance(struct point* pt1,struct point* pt2)
{
  double deltaX=pt1->x - pt2->x;
  double deltaY=pt1->y - pt2->y;
  return sqrt(deltaX*deltaX+deltaY*deltaY);
}

/**
* ��������
**/
void iteration(vector<struct point*>& pointList,vector<struct point*>& center,int itNum,int Knum)
{
  int iterNum=0;
  //�����Ĵ���
  while(iterNum++<itNum)
  {
    cout<<"��    "<<iterNum-1<<"    �ε���"<<endl;
    //�ҵ�ÿ�����������
    for(vector<struct point*>::iterator it=pointList.begin();it!=pointList.end();it++)
    {
      int index=getNearestCluster(center,*it);
      (*it)->cluster = index;
    }
    //���¾��������
    updateCenter(pointList,center,Knum);
  }
}


/**
*Ȼ��õ�]ÿ�����������
**/
void updateCenter(vector<struct point*>& pointList,vector<struct point*>& center,int num)
{
  //�����ǰ������
  center.clear();
  double x;
  double y;
  int pointNumber;
  int count=0;
  //�õ�ÿ�����������
  while(count<num)
  {
    x=0;
    y=0;
    pointNumber=0;
    for(vector<struct point*>::iterator it=pointList.begin();it!=pointList.end();it++)
    {
      if((*it)->cluster==count)
      {
        x+=(*it)->x;
        y+=(*it)->y;
        pointNumber++;
      }
    }
    struct point* tempCenter= new point;
    tempCenter->x = x/pointNumber;
    tempCenter->y = y/pointNumber;
    center.push_back(tempCenter);
    count++;
  }
}
/**
  �ڴ����ϻ��ƾ��������
**/
void drawCenter(vector<struct point*>& center)
{
  cout<<"***********************************"<<endl;
  cout<<"          draw center"<<endl;
  for(vector<struct point*>::iterator it=center.begin();it!=center.end();it++)
  {
    setfillcolor(WHITE);
    fillcircle((int)(*it)->x,(int)(*it)->y,3);
  }
  cout<<"***********************************"<<endl;
}
