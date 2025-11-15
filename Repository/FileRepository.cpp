
#include "FileRepository.h"
#include <fstream>
#include <iostream>
FileRepository::FileRepository(std::string filename) {
    this->filename = filename;
}


void FileRepository::Add(Tutorial t) {
    Repository::Add(t);
    this->save_data_to_file();
}

void FileRepository::Delete(std::string title) {
    Repository::Delete(title);
    this->save_data_to_file();
}


void FileRepository::Update(std::string title, Tutorial t) {
    Repository::Update(title, t);
    this->save_data_to_file();
}

void FileRepository::readTutorialsFromFile(std::string filename) {
    Repository::readTutorialsFromFile(filename);
}

void FileRepository::save_data_to_file() {
    std::ofstream fout(this->filename);
    if (!fout.is_open()) {
        std::cerr << "Error opening file: " << this->filename << std::endl;
        return;
    }

    for ( auto& tutorial : this->getTutorials()) {
        fout << tutorial << std::endl;
    }

    fout.close();
}

std::string FileRepository::getFilename() {
    return this->filename;
}



