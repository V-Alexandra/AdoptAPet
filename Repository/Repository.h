#pragma once
#include <vector>
#include "Tutorial.h"

class Repository {
private:
    std::vector<Tutorial> tutorials;

public:
    Repository() = default;

    // Deep copy constructor
    Repository(const Repository& other) {
        this->tutorials = other.tutorials;
    }

    // Deep copy assignment operator
    Repository& operator=(const Repository& other) {
        if (this == &other)
            return *this;
        this->tutorials = other.tutorials;
        return *this;
    }

    virtual void Add(Tutorial t);
    virtual void Delete(std::string title);
    virtual    void Update(std::string title, Tutorial t);

    virtual std::vector<Tutorial>& getTutorials();
    virtual Tutorial getElement(int position);
    virtual int getRepositoryLength();
    virtual void setElement(int position, Tutorial t);

   virtual void save_data_to_file();
    virtual    void readTutorialsFromFile(std::string filename);
};
