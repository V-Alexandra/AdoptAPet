#include "Service.h"
#include <algorithm>

Service::Service(Repository& tutorial_list) : service_list{tutorial_list} {}

Service::Service(const Service& other) : service_list(other.service_list) {}

Service& Service::operator=(const Service& other) {
    if (this == &other)
        return *this;
    this->service_list = other.service_list;
    return *this;
}

void Service::Add_tutorial(Tutorial t) {
    this->service_list.Add(t);
}

void Service::Remove_tutorial(std::string title) {
    this->service_list.Delete(title);
}

void Service::Update_tutorial(std::string title, Tutorial t) {
    this->service_list.Update(title, t);
}

std::vector<Tutorial> Service::get_tutorials_given_presenter(std::string user_presenter) {
    std::vector<Tutorial> tutorial_list;
    std::vector<Tutorial> repo = this->service_list.getTutorials();

    std::copy_if(repo.begin(), repo.end(), std::back_inserter(tutorial_list),
                 [&](Tutorial& elem) {
                     return user_presenter == elem.getPresenter() || user_presenter.empty();
                 });

    return tutorial_list;
}

void Service::UpdateLikes(std::string title) {
    auto& repo = this->service_list.getTutorials();
    for (auto& elem : repo) {
        if (elem.getTitle() == title) {
            elem.setLikes(elem.getLikes() + 1);
        }
    }
}

Repository& Service::get_list() {
    return this->service_list;
}

void Service::save_repo_file() {
    this->service_list.save_data_to_file();
}

void Service::load_repo_file(std::string filename) {
    this->service_list.readTutorialsFromFile(filename);
}
