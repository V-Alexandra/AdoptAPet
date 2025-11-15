
#pragma once

#include "Repository.h"
#include "FileRepository.h"

class CSVRepository: public Repository {
private:
    std::string filename;
public:
    CSVRepository(std::string s) {
        this->filename = s;
    }
    void readTutorialsFromFile(std::string filename) override;
    void save_data_to_file() override;
};


