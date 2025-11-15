//
// Created by Alexandra on 6/5/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AdminDesigner.h" resolved

#include "admindesigner.h"
#include "ui_AdminDesigner.h"
#include <QPushButton>
#include <QMessageBox>
#include "Validator.h"
#include "QStandardItemModel"
#include "QAbstractButton"
#include <QKeySequence>
AdminDesigner::AdminDesigner(Service &serv, Service &user_list,QWidget *parent) : serv{serv}, user_list{user_list},
    QWidget(parent), ui(new Ui::AdminDesigner) {
    ui->setupUi(this);
    populateList();
    this->undo_redo.add_undo(this->serv);
    QObject::connect(ui->addButton, &QPushButton::clicked, this, &AdminDesigner::addButtonHandler);
    QObject::connect(ui->deleteButton, &QPushButton::clicked, this, &AdminDesigner::deleteButtonHandler);
    QObject::connect(ui->updateButton, &QPushButton::clicked, this, &AdminDesigner:: updateButtonHandler);
    QObject::connect(ui->displayButton, &QPushButton::clicked, this, &AdminDesigner::displayButtonHandler);
    QObject::connect(ui->undoButton, &QPushButton::clicked, this, &AdminDesigner::undoButtonHandler);
    QObject::connect(ui->redoButton, &QPushButton::clicked, this, &AdminDesigner::redoButtonHandler);


}

AdminDesigner::~AdminDesigner() {
    delete ui;
}

void AdminDesigner::populateList()
{
    // Clear the existing model from the QTableView
    QStandardItemModel* model = new QStandardItemModel(this);
    QStringList headers = {"Title", "Presenter", "Duration", "Likes", "Link"};
    model->setHorizontalHeaderLabels(headers);

    // Retrieve the list of tutorials
    std::vector<Tutorial> tutorials = this->serv.get_list().getTutorials();

    // Populate the model with the tutorial data
    for ( Tutorial& t : tutorials) {
        QList<QStandardItem*> row;
        row.append(new QStandardItem(QString::fromStdString(t.getTitle())));
        row.append(new QStandardItem(QString::fromStdString(t.getPresenter())));
        row.append(new QStandardItem(QString::number(t.getDuration())));
        row.append(new QStandardItem(QString::number(t.getLikes())));
        row.append(new QStandardItem(QString::fromStdString(t.getLink())));
        model->appendRow(row);
    }

    // Set the model to the QTableView
    this->ui->administratorTable->setModel(model);
}




void AdminDesigner::displayButtonHandler()
{

    // Optional: Clear input fields
    ui->TitleLineEdit->clear();
    ui->PresenterLineEdit->clear();
    ui->DurationLineEdit->clear();
    ui->LikesLineEdit->clear();
    ui->LinkLineEdit->clear();

    // Refresh the table
    this->populateList();
}

int AdminDesigner::getSelectedIndex()
{
    QModelIndexList selectedIndex = this->ui->administratorTable->selectionModel()->selectedIndexes();
    if(selectedIndex.size() == 0) {
        this->ui->TitleLineEdit->clear();
        this->ui->PresenterLineEdit->clear();
        this->ui->DurationLineEdit->clear();
        this->ui->LikesLineEdit->clear();
        this->ui->LinkLineEdit->clear();
        return -1;
    }

    int index = selectedIndex.at(0).row();
    return index;
}
void AdminDesigner::addButtonHandler()
{
    QString title = ui->TitleLineEdit->text();
    QString presenter = ui->PresenterLineEdit->text();
    int duration = ui->DurationLineEdit->text().toInt();
    int likes = ui->LikesLineEdit->text().toInt();
    QString link = ui->LinkLineEdit->text();

    Tutorial newTutorial{ title.toStdString(), presenter.toStdString(), duration, likes, link.toStdString() };

    try {
        TutorialValidator::validate(newTutorial);
        this->undo_redo.add_undo(this->serv); // Save state BEFORE adding
        this->serv.Add_tutorial(newTutorial);
        this->serv.notify();
    }
    catch (ValidatorException& e) {
        QMessageBox::critical(this, "Validation Error", "Error");
    }
}

void AdminDesigner::deleteButtonHandler()
{
    int index = getSelectedIndex();
    if (index < 0) {
        QMessageBox::critical(this, "Error", "No tutorial");
        return;
    }

    this->undo_redo.add_undo(this->serv); // Save state BEFORE deleting

    Tutorial tutorial = this->serv.get_list().getElement(index);
    this->serv.Remove_tutorial(tutorial.getTitle());
    this->serv.notify();
}

void AdminDesigner::updateButtonHandler()
{
    QString title = this->ui->TitleLineEdit->text();
    QString presenter = this->ui->PresenterLineEdit->text();
    int duration = this->ui->DurationLineEdit->text().toInt();
    int likes = this->ui->LikesLineEdit->text().toInt();
    QString link = this->ui->LinkLineEdit->text();

    try {
        this->undo_redo.add_undo(this->serv); // Save state BEFORE updating
        this->serv.Update_tutorial(title.toStdString(),
                                   Tutorial{title.toStdString(), presenter.toStdString(), duration, likes, link.toStdString()});
        this->serv.notify();
    }
    catch (const std::runtime_error& e) {
        QMessageBox::critical(this, "Update Error", e.what());
    }
}

void AdminDesigner::undoButtonHandler() {
    try {
        this->serv = this->undo_redo.make_undo();  // Restore previous state
        this->serv.notify();
        this->populateList();
    } catch (const std::out_of_range& e) {
        QMessageBox::critical(this, "Undo Error", e.what());
    }
}

void AdminDesigner::redoButtonHandler() {
    try {
        this->serv = this->undo_redo.make_redo();  // Restore next state
        this->serv.notify();
        this->populateList();
    } catch (const std::out_of_range& e) {
        QMessageBox::critical(this, "Redo Error", e.what());
    }
}


void AdminDesigner::setTitle() {
    this->setWindowTitle("Administrator");
}

void AdminDesigner::update() {
    this->populateList();
}