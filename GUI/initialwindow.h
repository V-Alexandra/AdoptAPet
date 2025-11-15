//
// Created by Alexandra on 6/5/2025.
//

#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H

#include <QMainWindow>
#include "admindesigner.h"
#include "userdesigner.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InitialWindow; }
QT_END_NAMESPACE

class InitialWindow : public QMainWindow {
Q_OBJECT

public:
    explicit InitialWindow(AdminDesigner &admin_designer, userdesigner&user_designer ,QWidget *parent = nullptr);
    ~InitialWindow() override;
    void connect_signals_and_slots();

private:
    Ui::InitialWindow *ui;
    AdminDesigner& admin_designer;
    userdesigner& user_designer;
};


#endif //INITIALWINDOW_H
