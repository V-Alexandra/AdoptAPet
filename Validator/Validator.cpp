
#include "Validator.h"

ValidatorException::ValidatorException(std::string message) {
    this->message = message;
}

std::string ValidatorException::getMessage() {
    return this->message;
}

void TutorialValidator::validate(Tutorial &tutorial) {
    std::string errors = "";
    if(tutorial.getDuration() > 100)
        errors += "This duration is too long!\n";
    if(tutorial.getLikes() < 0)
        errors += "A tutorial cannot have negative likes\n";
    if(tutorial.getTitle().empty())
        errors += "Tutorial title cannot be empty\n";


    if(tutorial.getPresenter().size() < 2)
        errors += "Tutorial presenter cannot be less than 3\n";


    if(tutorial.getLink().empty())
        errors += "Tutorial link cannot be empty\n";

    if(tutorial.getLink().substr(0, 5) != "www")
        errors += "Tutorial link must start with 'www'\n";


    if(errors.size() > 0)
        throw ValidatorException(errors);
}
