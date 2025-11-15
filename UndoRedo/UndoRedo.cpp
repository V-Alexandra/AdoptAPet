#include "UndoRedo.h"
#include <stdexcept>

void UndoRedo::add_undo(const Service& service) {
    undo_list.push_back(service);  // Deep copy
    redo_list.clear();             // Invalidate redo history
}

Service UndoRedo::make_undo() {
    if (undo_list.size() <= 1) {
        throw std::out_of_range("No more undos available");
    }

    Service last = undo_list.back();
    undo_list.pop_back();
    redo_list.push_back(last);

    return undo_list.back();  // Return previous state
}

Service UndoRedo::make_redo() {
    if (redo_list.empty()) {
        throw std::out_of_range("No more redos available");
    }

    Service redo = redo_list.back();
    redo_list.pop_back();
    undo_list.push_back(redo);

    return redo;
}
