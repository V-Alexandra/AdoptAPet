#pragma once
#include<string>
#include <istream>
using namespace std;
class Tutorial
{
private:
    string title, presenter, link;
    int duration, likes;
public:
    Tutorial( const string title,const string presenter,const int duration,const  int likes,const  string link) : title{title}, presenter{presenter}, duration{duration}, likes{likes}, link{link}{}
    Tutorial();
    string getTitle();
    string getPresenter();
    string getLink();
    int getDuration();
    int getLikes();
    void setLikes(int nr_likes);
    friend std::ostream& operator<<(std::ostream& os, const Tutorial& tutorial) {
        os << tutorial.title << "," << tutorial.presenter << "," << tutorial.duration << "," << tutorial.likes << ","<< tutorial.link;
        return os;
    }


    friend std::istream& operator>>(std::istream& is, Tutorial& tutorial) {
        std::getline(is >> std::ws, tutorial.title, ',');
        std::getline(is >> std::ws, tutorial.presenter, ',');
        is >> tutorial.duration;
        is.ignore(); // ignore the comma
        is >> tutorial.likes;
        is.ignore();
        std::getline(is >> std::ws, tutorial.link);
        return is;
    }
};