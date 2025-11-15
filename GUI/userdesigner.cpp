//
// Created by Alexandra on 6/5/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_userdesigner.h" resolved

#include "userdesigner.h"
#include "ui_userdesigner.h"
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
userdesigner::userdesigner(Service service, Service serv,QWidget *parent) : service{service}, user_list{serv},
    QWidget(parent), ui(new Ui::userdesigner) {
    ui->setupUi(this);
    current_tutorial_index = -1;
    QObject::connect(ui->filterButton, &QPushButton::clicked, this, &userdesigner::filterButtonHandler);
    QObject::connect(ui->userWatchListButton, &QPushButton::clicked, this, &userdesigner::displayUserWLButtonHandler);
    QObject::connect(ui->nextButton, &QPushButton::clicked, this, &userdesigner::onNextButtonClicked);
    populateList();
}
void userdesigner::populateList()
{
    this->ui->userWidgetList->clear();

    std::vector<Tutorial> tutorials = this->service.get_list().getTutorials();
    for ( Tutorial &t: tutorials) {
        QString itemText = QString::fromStdString(t.getTitle() + " - " + t.getPresenter() + " duration: " + std::to_string(t.getDuration()) + " likes: " +std::to_string(t.getLikes()) + " " + t.getLink());
        this->ui->userWidgetList->addItem(itemText);
    }
}
userdesigner::~userdesigner() {
    delete ui;
}

void userdesigner::filterButtonHandler()
{
    QString presenter = this->ui->presenterLineEdit->text();
    filtered_tutorial_list = this->service.get_tutorials_given_presenter(presenter.toStdString());
    current_tutorial_index = 0;
    iterationStopped = false;

    if (!filtered_tutorial_list.empty()) {
        showNextTutorial();
    } else {
        QMessageBox::warning(this, "Warning", "No tutorials found.");
    }
}

void userdesigner::displayUserWLButtonHandler()
{
    this->ui->userWidgetList->clear();

    std::vector<Tutorial> tutorials = this->user_list.get_list().getTutorials();
    for ( Tutorial &t: tutorials) {
        QString itemText = QString::fromStdString(t.getTitle() + " - " + t.getPresenter() + " duration: " + std::to_string(t.getDuration()) + " likes: " +std::to_string(t.getLikes()) + " " + t.getLink());
        this->ui->userWidgetList->addItem(itemText);
    }
}

void userdesigner::onNextButtonClicked()
{
    if (current_tutorial_index < filtered_tutorial_list.size()) {
        current_tutorial_index= (current_tutorial_index + 1) % filtered_tutorial_list.size();
        showNextTutorial();
    }
}

void userdesigner::showNextTutorial()
{
    if (!iterationStopped && current_tutorial_index < filtered_tutorial_list.size()) {
        this->ui->userWidgetList->clear();
        auto& tutorial = filtered_tutorial_list[current_tutorial_index];
        QString itemText = QString::fromStdString(tutorial.getTitle() + " - " + tutorial.getPresenter() + " duration: " + std::to_string(tutorial.getDuration()) + " likes: " + std::to_string(tutorial.getLikes()) + " " + tutorial.getLink());
        this->ui->userWidgetList->addItem(itemText);
    } else if (iterationStopped && current_tutorial_index != -1) {
        QMessageBox::warning(this, "Warning", "You have stopped the iteration.");
        current_tutorial_index = -1;
    }
}

void userdesigner::update()
{
    this->displayUserWLButtonHandler();
}

void userdesigner::SetTitle()
{
    this->setWindowTitle("User");
}

