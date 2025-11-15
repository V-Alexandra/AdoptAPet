#pragma once

#include <exception>
#include <string>
#include "Tutorial.h"

class ValidatorException  {
private:
    std::string message;
public:
    ValidatorException(std::string message);
    std::string getMessage();
};

class TutorialValidator {
public:
    static void validate(Tutorial &tutorial);
};

