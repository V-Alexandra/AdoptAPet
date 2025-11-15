
#include "HTMLRepository.h"
#include  <fstream>
HTMLRepository::HTMLRepository(std::string name) {
    this->filename = name;
}

void HTMLRepository::readTutorialsFromFile(std::string filename) {
    Repository::readTutorialsFromFile(filename);
}

std::string generateHTML(std::vector<Tutorial> tutorials) {
    std::string htmlContent = "<!DOCTYPE html>\n"
                              "<html>\n"
                              "<head>\n"
                              "    <title>Tutorials</title>\n"
                              "</head>\n"
                              "<body>\n"
                              "<table border=\"1\">\n"
                              "    <tr>\n"
                              "        <td>Title</td>\n"
                              "        <td>Presenter</td>\n"
                              "        <td>Duration</td>\n"
                              "        <td>Likes</td>\n"
                              "        <td>Link</td>\n"
                              "    </tr>\n";

    for (auto& tutorial : tutorials) {
        htmlContent += "    <tr>\n";
        htmlContent += "        <td>" + tutorial.getTitle() + "</td>\n";
        htmlContent += "        <td>" + tutorial.getPresenter() + "</td>\n";
        htmlContent += "        <td>" + std::to_string(tutorial.getDuration()) + "</td>\n";
        htmlContent += "        <td>" + std::to_string(tutorial.getLikes()) + "</td>\n";
        htmlContent += "        <td><a href=\"" + tutorial.getLink() + "\">Link</a></td>\n";
        htmlContent += "    </tr>\n";
    }

    htmlContent += "</table>\n"
                   "</body>\n"
                   "</html>";

    return htmlContent;
}

void HTMLRepository::save_data_to_file() {
    std::ofstream fout("../watchList.html");
    fout << generateHTML(this->getTutorials());
    fout.close();
    system("watchList.html");
}
