
#include "GUI.h"
#include "Validator.h"
#include <qlayout.h>
#include <qlabel.h>


GUI::GUI(Service& serv) : serv{ serv }
{
    this->buildGUI();
    //this->populateList();

    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addButtonHandler);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deleteButtonHandler);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateButtonHandler);
    QObject::connect(this->printButton, &QPushButton::clicked, this, &GUI::printButtonHandler);
}


void GUI::buildGUI()
{
    QHBoxLayout* mainLayout = new QHBoxLayout{ this };
    this->tutorialsListWidget = new QListWidget{};
    mainLayout->addWidget(tutorialsListWidget);

    QGridLayout* rightLayout = new QGridLayout{};

    QLabel* titleLabel = new QLabel{ "Title" };
    this->title = new QLineEdit{};
    QLabel* presenterLabel = new QLabel{ "Presenter" };
    this->presenter = new QLineEdit{};
    QLabel* durationLabel = new QLabel{ "Duration" };
    this->duration = new QLineEdit{};
    QLabel* likesLabel = new QLabel{ "Likes" };
    this->likes = new QLineEdit{};
    QLabel* linkLabel = new QLabel{ "Link" };
    this->link = new QLineEdit{};

    rightLayout->addWidget(titleLabel, 0, 0);
    rightLayout->addWidget(this->title, 0, 1);
    rightLayout->addWidget(presenterLabel, 1, 0);
    rightLayout->addWidget(this->presenter, 1, 1);
    rightLayout->addWidget(durationLabel, 2, 0);
    rightLayout->addWidget(this->duration, 2, 1);
    rightLayout->addWidget(likesLabel, 3, 0);
    rightLayout->addWidget(this->likes, 3, 1);
    rightLayout->addWidget(linkLabel, 4, 0);
    rightLayout->addWidget(this->link, 4, 1);

    this->addButton = new QPushButton{ "Add" };
    this->deleteButton = new QPushButton{ "Delete" };
    this->updateButton = new QPushButton{ "Update" };
    this->printButton = new QPushButton{"Display"};

    rightLayout->addWidget(this->addButton, 5, 0);
    rightLayout->addWidget(this->deleteButton, 5, 1);
    rightLayout->addWidget(this->updateButton, 6, 0);
    rightLayout->addWidget(this->printButton, 6, 1);

    mainLayout->addLayout(rightLayout);
}

void GUI::populateList()
{
    this->tutorialsListWidget->clear();

    Repository repo = this->serv.get_list();
    for (auto t : repo.getTutorials())
    {
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(t.getTitle() + " " + t.getPresenter() + " " + std::to_string(t.getDuration()) + " " + std::to_string(t.getLikes()) + " " + t.getLink()) };
        QFont font{ "Arial", 12};
        item->setFont(font);
        this->tutorialsListWidget->addItem(item);

    }
}

void GUI::addButtonHandler()
{
    QString title = this->title->text();
    QString presenter = this->presenter->text();
    int duration = this->duration->text().toInt();
    int likes = this->likes->text().toInt();
    QString link = this->link->text();

    Tutorial newTutorial{ title.toStdString(), presenter.toStdString(), duration, likes, link.toStdString() };

    try {
        TutorialValidator::validate(newTutorial);
        this->serv.Add_tutorial(newTutorial);
        this->populateList();
        this->serv.save_repo_file();

    }
    catch (ValidatorException& e) {

    }
}

void GUI::deleteButtonHandler()
{
    QString title = this->title->text();
    try {
        this->serv.Remove_tutorial(title.toStdString());
        this->populateList();

    }
    catch (const std::runtime_error& e) {

    }
}

void GUI::updateButtonHandler()
{
    QString title = this->title->text();
    QString presenter = this->presenter->text();
    int duration = this->duration->text().toInt();
    int likes = this->likes->text().toInt();
    QString link = this->link->text();

    try {
        this->serv.Update_tutorial(title.toStdString(), Tutorial{title.toStdString(), presenter.toStdString(), duration, likes, link.toStdString()});
        this->populateList();
    }
    catch (const std::runtime_error& e) {

    }
}

void GUI::printButtonHandler() {
    this->populateList();
}
