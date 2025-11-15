//
// Created by Alexandra on 6/5/2025.
//

#ifndef USERDESIGNER_H
#define USERDESIGNER_H

#include <QWidget>
#include "Observer.h"
#include "Service.h"
QT_BEGIN_NAMESPACE
namespace Ui { class userdesigner; }
QT_END_NAMESPACE

class userdesigner : public QWidget, public Observer{
Q_OBJECT

public:
    explicit userdesigner(Service service, Service serv, QWidget *parent = nullptr);
void populateList();
~userdesigner() override;

private:
    Ui::userdesigner *ui;
    Service service, user_list;
    std::vector<Tutorial> filtered_tutorial_list;
    int current_tutorial_index;
    bool iterationStopped;
    void filterButtonHandler();
    void displayUserWLButtonHandler();
    void onNextButtonClicked();
    void showNextTutorial();
    void update() override;
    void SetTitle();

};


#endif //USERDESIGNER_H
