#include<iostream>
#include<graphics.h>
#include<cmath>
#include<cstdlib>
#include<easyx.h>
#include<vector>
using namespace std;

//随机生成的点的数目
#define POINT_NUM 8000
//窗口的大小
#define WIDTH 600
#define HEIGHT 600

struct point
{
  double x;          //该点的X坐标
  double y;        //该点的Y坐标
  int cluster;     //该店所属聚类的索引
};
/**
  绘制每个聚类所用的颜色
**/
COLORREF color[15]=
{
  WHITE,YELLOW,RED,BLUE,GREEN,
  BROWN,LIGHTCYAN,MAGENTA,LIGHTRED,
  CYAN,LIGHTBLUE,LIGHTGREEN, DARKGRAY,
  LIGHTMAGENTA,LIGHTGRAY,
};

//初始化聚类点
void initCluster(vector<struct point*>& pointList,int num);

//随机生成聚类中心
void generateCenter(vector<struct point*>& center,int Num);

//画出所有的点
void drawCluster(vector<struct point*>& pointList);

//获得一个聚类的中心
struct point* getCenter(vector<struct point*>& cluster);

//获得两点之间的欧式距离
double getDistance(struct point* pt1,struct point* pt2);

//获得该点所属的聚类的索引
int getNearestCluster(vector<struct point*>& center,struct point* tempPoint);
//进行迭代
void iteration(vector<struct point*>& pointList,vector<struct point*>& center,int iterNum,int Knum);
//更新聚类中心
void updateCenter(vector<struct point*>& pointList,vector<struct point*>& center,int num);
//单独画出每个聚类的中心
void drawCenter(vector<struct point*>& center);

int main()
{
  //用来存放这些点的坐标
  vector<struct point*> pointList;

  //用于存储聚类的中心
  vector<struct point*> center;

  //聚类的数目
  int Knum;
  int iteratorNum;        //迭代次数
  cout<<"Please input the K number"<<endl;
  cin>>Knum;
  cout<<"Please input the iteratorNum number"<<endl;
  cin>>iteratorNum;
  initgraph(WIDTH,HEIGHT,SHOWCONSOLE);
  setbkcolor(BLACK);
  cleardevice();

  //初始化种群
  initCluster(pointList,POINT_NUM);
  //随机生成聚类中心
  generateCenter(center,Knum);

  //迭代处理
  iteration(pointList,center,iteratorNum,Knum);

  //画出所有的点
  drawCluster(pointList);
  drawCenter(center);
  system("pause");
  closegraph();
  return 0;
}

/**
  随机生成种子点
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
这个是最终的绘图函数
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
  初始化聚类中心
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
* 使用均值求得一个点群的中心
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
*得到一个点所属的聚类的索引
**/
int getNearestCluster(vector<struct point*>& center,struct point* tempPoint)
{
  //第一个点和中心的一个点之间的坐标
  vector<struct point*>::iterator it=center.begin();
  double  min =getDistance(tempPoint,*it);
  int index=0;
  double dist;
  for(int i=0;it!=center.end();it++,i++)
  {
    dist=getDistance(tempPoint,*it);
    if(dist<min)
    {
      //只有出现更近的点时才会出现
      min=dist;
      index=i;
    }
  }
  return index;
}
/**
  返回两个坐标点之间的欧式距离
**/
double getDistance(struct point* pt1,struct point* pt2)
{
  double deltaX=pt1->x - pt2->x;
  double deltaY=pt1->y - pt2->y;
  return sqrt(deltaX*deltaX+deltaY*deltaY);
}

/**
* 迭代处理
**/
void iteration(vector<struct point*>& pointList,vector<struct point*>& center,int itNum,int Knum)
{
  int iterNum=0;
  //迭代的次数
  while(iterNum++<itNum)
  {
    cout<<"第    "<<iterNum-1<<"    次迭代"<<endl;
    //找到每个聚类的中心
    for(vector<struct point*>::iterator it=pointList.begin();it!=pointList.end();it++)
    {
      int index=getNearestCluster(center,*it);
      (*it)->cluster = index;
    }
    //更新聚类的中心
    updateCenter(pointList,center,Knum);
  }
}


/**
*然后得到]每个聚类的中心
**/
void updateCenter(vector<struct point*>& pointList,vector<struct point*>& center,int num)
{
  //清空以前的中心
  center.clear();
  double x;
  double y;
  int pointNumber;
  int count=0;
  //得到每个聚类的中心
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
  在窗口上绘制聚类的中心
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
