
#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class GUI : public QWidget
{
private:
    Service& serv;

    QListWidget* tutorialsListWidget;
    QLineEdit* title;
    QLineEdit* presenter;
    QLineEdit* duration;
    QLineEdit* likes;
    QLineEdit* link;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    QPushButton* printButton;
public:
    GUI(Service& serv);

private:
    void buildGUI();
    void populateList();

    void addButtonHandler();
    void deleteButtonHandler();
    void updateButtonHandler();
    void printButtonHandler();
};

