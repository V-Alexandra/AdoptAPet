//
// Created by Alexandra on 6/5/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_InitialWindow.h" resolved

#include "initialwindow.h"
#include "ui_InitialWindow.h"
#include <QPushButton>

InitialWindow::InitialWindow(AdminDesigner&admin_designer, userdesigner& userdesigner, QWidget *parent) : admin_designer{admin_designer}, user_designer{userdesigner},
    QMainWindow(parent), ui(new Ui::InitialWindow) {
    ui->setupUi(this);
    connect_signals_and_slots();
}

InitialWindow::~InitialWindow() {
    delete ui;
}

void InitialWindow::connect_signals_and_slots()
{
    QObject::connect(ui->adminButton, &QPushButton::clicked, [&]()
        {
            //connect to the GUI
            this->admin_designer.show();

        });
    QObject::connect(ui->userButton, &QPushButton::clicked, [&]()
        {
            this->user_designer.show();
        });
}
