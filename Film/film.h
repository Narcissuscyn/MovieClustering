#ifndef FILM_H
#define FILM_H
#include<fstream>
#include<iostream>
using namespace std;
enum Level{zero,one,two,three,four,five};
class Film
{
private:
    string title;
    string director;
    int time;
    char*level;
    string introduce;
public:
 Film ();
    void set_level(const Level x=zero);
    ~Film(){delete level;}
    string set_title(const string& name);
   const char*set_title(const char*name);
    int set_time(const int t );
    void filmintroduce();
    string set_director(const string name);
     virtual void output()const;
     virtual void Input(istream &file);
    void read_file();
};
class Directorcut:public Film
{
private:
    int time_update;
    string content_update;
public:

    int set_time_update(const int time);
   string set_content_update(const string content);
    void output()const;
    Directorcut();
    void Input(istream &file);
};
class ForeignFilm:public Film
{
private:
    string language;
public:
    ForeignFilm();
    string set_language(const string&x);
    void output()const;
    void Input(istream &file);
};
class SAndD:public Film
{
private:
    string artist;
public:
    SAndD()
    {
    string name;
    name="my artist!";
    set_artist(name );
    }
    void set_artist(const string name);
     virtual void output()const;
     virtual void Input(istream &file);

};
#endif // FILM_H
