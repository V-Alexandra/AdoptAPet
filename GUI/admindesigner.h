//
// Created by Alexandra on 6/5/2025.
//

#ifndef ADMINDESIGNER_H
#define ADMINDESIGNER_H
#include "Service.h"
#include <QWidget>
#include "UndoRedo.h"
#include "Observer.h"
QT_BEGIN_NAMESPACE
namespace Ui { class AdminDesigner; }
QT_END_NAMESPACE

class AdminDesigner : public QWidget, public Observer {
Q_OBJECT

public:
    explicit AdminDesigner(Service &serv, Service &user_list,QWidget *parent = nullptr);
    ~AdminDesigner() override;
    void populateList();
    void addButtonHandler();
    void deleteButtonHandler();
    void updateButtonHandler();
    void displayButtonHandler();
    int getSelectedIndex();
    void setTitle();
    void undoButtonHandler();
    void redoButtonHandler();
    void update() override;

private:
    Ui::AdminDesigner *ui;
    Service serv;
    Service user_list;
    UndoRedo undo_redo;
};


#endif //ADMINDESIGNER_H
