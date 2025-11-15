//
// Created by Alexandra on 6/5/2025.
//

#include "Tutorial.h"

Tutorial::Tutorial()
{
    this->title = "";
    this->presenter = "";
    this->duration = 0;
    this->likes = 0;
    this->link = "";
}

string Tutorial::getTitle()
{
    return this->title;
}

string Tutorial::getPresenter()
{
    return this->presenter;
}

string Tutorial::getLink()
{
    return this->link;
}

int Tutorial::getDuration()
{
    return this->duration;
}

int Tutorial::getLikes()
{
    return this->likes;
}

void Tutorial::setLikes(int nr_likes)
{
    this->likes = nr_likes;
}
