#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream infile("movies.dat",ios::in);

    ofstream ofile("movie_info.dat");
    int movieid=0,no_movieid=0;
    string desc="";

while( infile>>movieid)
   {
    getline(infile,desc);
    bool flag=false;
    ifstream infile1("no_movieid.dat",ios::in);
    while(infile1>>no_movieid)
    {
    if(movieid==no_movieid)
    {
        flag=true;
        break;
    }

    }
    if(!flag)
    {
        ofile<<movieid<<"\t"<<"电影名："+desc+"(电影类型)"<<endl;
    }
    movieid=0;
    infile1.close();
}
infile.close();
    cout << "Hello world!" << endl;
    return 0;
}
