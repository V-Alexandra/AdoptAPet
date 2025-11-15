
#include <fstream>
#include "CSVRepository.h"
#include <iostream>

void CSVRepository::readTutorialsFromFile(std::string filename) {
    Repository::readTutorialsFromFile(filename);
}

void CSVRepository::save_data_to_file() {
    std::ofstream fout(this->filename);
    if (!fout.is_open()) {
        std::cerr << "Error opening file: " << this->filename << std::endl;
        return;
    }

    for ( auto& tutorial : this->getTutorials()) {
        fout << tutorial << std::endl;
    }

    fout.close();
    std::system(("start notepad " + std::string(this->filename)).c_str());
}

