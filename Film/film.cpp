#include "film.h"
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#define SIZE 5
#define Max 5
using namespace std;
/*Film::Film()
{
    title="my movie!";
    director="my director!";
    time=1900;
    level=0;
    introduce="no movie!";
}
*/
string Film::set_title(const string & name)
{
    title=name;
    return title;
}
Film::Film()
{
   // Film f[SIZE];
   level=0;
    string name1,director1,introduce1;
    int t=0;
   Level level1;
   int x;
    ifstream infile;
    infile.open("data.txt",ios::in);
    if(!infile)
    {
        cout<<"文件打开错误!"<<endl;
        return;
    }
    if(!infile.eof())
    {
        infile>>name1>>director1>>t>>x>>introduce1;
        switch(x)
        {
            case 0:{level1=zero;break;}
            case 1:{level1=one;break;}
            case 2:{level1=two;break;}
            case 3:{level1=three;break;}
            case 4:{level1=four;break;}
            case 5:{level1=five;break;}
        }
        title=name1;
        director=director1;
         time=t;
         set_level(level1);
         introduce=introduce1;

    }
}
void Film::set_level(const Level x)
{
       switch(x)
       {
       case zero:
      {
       level="☆☆☆☆☆";
            break;
        }
       case one:
        {
            level="★☆☆☆☆";
            break;
        }
       case two:
        {
            level="★★☆☆☆";
            break;
        }
       case three:
        {
            level="★★★☆☆";
            break;
        }
       case four:
        {
            level="★★★★☆";
            break;
        }
       case five:
        {
            level="★★★★★";
            break;
        }
       }
}
const char*Film::set_title(const char*name)
{
    title=name;
    return name;
}
int Film::set_time(const int t )
{
    time=t;
    return t;
}
string Film::set_director(const string name)
{
    director=name;
    return director;
}
void Film::output()const
{
    cout<<"影片名："<<title<<endl;
    cout<<"上映时间："<<time<<"年"<<endl;
    cout<<"导演："<<director<<endl;
    cout<<"电影评价："<<level<<endl;
    cout<<"内容简介:"<<endl;
    cout<<introduce<<endl;
}
 Directorcut::Directorcut():Film()
 {
    // cout<<"请输入变更后的时间"<<endl;
     int t;
     //cin>>t;
     t=1990;
    set_time_update(t);
   // cout<<"请输入变更内容："<<endl;
    string str;
    //cin>>str;
    str="no change";
    set_content_update(str);
 }
int Directorcut::set_time_update(const int t)
{
    time_update=t;
    return time_update;
}
string Directorcut::set_content_update(const string content)
{
    content_update=content;
    return content_update;

}
void Directorcut::output()const
{
    Film::output();
    cout<<endl;

    cout<<"影片变更信息："<<endl;
    cout<<"变更时间："<<time_update<<endl;
    cout<<"变更内容："<<content_update<<endl;
}
string ForeignFilm::set_language(const string&x)
{
    language=x;
    return language;

}
ForeignFilm::ForeignFilm():Film()
{
    //cout<<"请输入语言种类："<<endl;
    string str;
  //  cin>>str;
  str="English";
set_language(str);
}
void ForeignFilm::output()const
{
    Film::output();
    cout<<endl;
    cout<<"影片语言:"<<language<<endl;
}
 void Film::Input(istream &f)
 {
     string name1,director1,introduce1;
    int t=0;
   Level level1;
   int x;
   f>>name1>>director1>>t>>x>>introduce1;
    switch(x)
        {
            case 0:{level1=zero;break;}
            case 1:{level1=one;break;}
            case 2:{level1=two;break;}
            case 3:{level1=three;break;}
            case 4:{level1=four;break;}
            case 5:{level1=five;break;}
        }
     title=name1;
     director=director1;
     time=t;
     set_level(level1);
     introduce=introduce1;
 }
 void Directorcut::Input(istream &f)
 {
     int t;
     string introduce1;
Film::Input(f);
f>>t>>introduce1;
time_update=t;
content_update=introduce1;
 }
 void ForeignFilm::Input(istream&f)
 {
Film::Input(f);
string language1;
f>>language1;
language=language1;
 }
void Film:: read_file()
{
    Film*films[Max];
    int i=0;
    string names;
    ifstream file;
    file.open("mydata.txt",ios::in);
    if(!file)
    {
        cout<<"file open error!"<<endl;
        exit(0);
    }
    while((file>>names)&&i<Max)
    {
        string str1,str2,str3,str4;
        str1="Film";
        str2="Directorcut";
        str3="ForeignFilm";
        str4="SAndD";
        cout<<endl<<endl;
        if(names==str1)films[i]=new Film;
           if(names==str2)films[i]=new Directorcut;
           if(names==str3) films[i]=new ForeignFilm;
        if(names==str4)films[i]=new SAndD;
            films[i]->Input(file);
            films[i]->output();
            i++;
    }


}

void SAndD::set_artist(const string name)
{
    artist=name;

}
 void SAndD::output()const
{
    Film::output();
    cout<<"艺术家："<<artist<<endl;
}
 void SAndD:: Input(istream &file)
{

      Film::Input(file);
         string str;
         file>>str;
       set_artist(str);
}
