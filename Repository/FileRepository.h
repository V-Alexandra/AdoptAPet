
#pragma once

#include "Repository.h"

class FileRepository: public Repository{
protected:
    std::string filename;

    void readTutorialsFromFile(std::string filename);
    void save_data_to_file();
public:
    FileRepository(std::string filename);
    void Add(Tutorial t) override;
    void Delete(std::string title) override;
    void Update(std::string title, Tutorial x) override;
    std::string getFilename();
};


