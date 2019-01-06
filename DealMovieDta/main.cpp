#include <iostream>
#include <fstream>
using namespace std;
#define movie_number 3883
#define user_number 6040
//int movie[movie_number][user_number];
int main()
{
    //找出没有被评价的电影.
   ifstream infile("o_movie.txt",ios::in);
    ofstream ofile("n_movie.txt");
    int movieID1,movieID2;
if((!infile))
    {
        cout<<"file error!"<<endl;
        return 0;
    }
    while(infile>>movieID1)
    {
        bool flag=false;
        ifstream infile1("rating_movie.dat");
     //   cout<<movieID1<<endl;
       while(infile1>>movieID2)
       {
           if(movieID1==movieID2)
           {

               flag=true;
               break;
           }
       }
       if(!flag)
    {
        ofile<<movieID1<<endl;
    }
     infile1.close();
    }
    infile.close();
    ofile.close();
    return 0;
}
