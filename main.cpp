
#include <QtWidgets/QApplication>
#include "Tutorial.h"
#include "Repository/Repository.h"
#include "Service.h"
#include "Repository/FileRepository.h"
#include "Repository/CSVRepository.h"
#include "Repository/HTMLRepository.h"
#include "GUI.h"
#include "initialwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CSVRepository repo{ "repo.txt" };
    CSVRepository user_repo{"userwatchlist.csv"};
    Service serv{ repo };
    Service user_list{user_repo};
    serv.load_repo_file("repo.txt");
    user_list.load_repo_file("userwatchlist.csv");
    AdminDesigner admin{ serv,user_list };
    userdesigner user{serv, user_list };
    InitialWindow initial_window{admin, user};
    initial_window.show();
    return a.exec();
}

