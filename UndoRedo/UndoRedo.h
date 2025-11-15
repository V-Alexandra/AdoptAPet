#pragma once
#include <vector>
#include "Service.h"

class UndoRedo {
private:
    std::vector<Service> undo_list;
    std::vector<Service> redo_list;

public:
    void add_undo(const Service& service);
    Service make_undo();
    Service make_redo();
};
