#pragma once
#include "Repository.h"
#include "Observer.h"

class Service : public Subject {
private:
    Repository service_list;

public:
    Service(Repository& tutorial_list);
    Service(const Service& other);
    Service& operator=(const Service& other);

    void Add_tutorial(Tutorial t);
    void Remove_tutorial(std::string title);
    void Update_tutorial(std::string title, Tutorial t);

    std::vector<Tutorial> get_tutorials_given_presenter(std::string presenter);
    void UpdateLikes(std::string title);

    Repository& get_list();
    void save_repo_file();
    void load_repo_file(std::string filename);
};
