#include "Repository.h"
#include <algorithm>
#include <fstream>
#include <iostream>

void Repository::Add(Tutorial t) {
    auto it = std::find_if(this->tutorials.begin(), this->tutorials.end(), [&t](Tutorial& tutorial) {
        return tutorial.getTitle() == t.getTitle();
    });

    if (it != tutorials.end())
        throw std::runtime_error("This tutorial already exists.");

    this->tutorials.push_back(t);
}

void Repository::Delete(std::string title) {
    auto it = std::find_if(tutorials.begin(), tutorials.end(), [&title](Tutorial& tutorial) {
        return tutorial.getTitle() == title;
    });

    if (it == tutorials.end()) {
        throw std::runtime_error("This tutorial doesn't exist");
    }

    tutorials.erase(it);
}

void Repository::Update(std::string title, Tutorial t) {
    auto it = std::find_if(tutorials.begin(), tutorials.end(), [&title](Tutorial& tutorial) {
        return tutorial.getTitle() == title;
    });

    if (it == tutorials.end()) {
        throw std::runtime_error("This tutorial doesn't exist");
    }

    *it = t;
}

std::vector<Tutorial>& Repository::getTutorials() {
    return this->tutorials;
}

Tutorial Repository::getElement(int position) {
    return this->tutorials.at(position);
}

int Repository::getRepositoryLength() {
    return static_cast<int>(this->tutorials.size());
}

void Repository::setElement(int position, Tutorial t) {
    if (position < 0 || position >= this->tutorials.size())
        throw std::runtime_error("Index out of range");
    this->tutorials[position] = t;
}

void Repository::save_data_to_file() {
    // Implement as needed
}

void Repository::readTutorialsFromFile(std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open the file.\n";
        return;
    }

    Tutorial tutorial;
    while (file >> tutorial) {
        this->tutorials.push_back(tutorial);
    }

    file.close();
}
