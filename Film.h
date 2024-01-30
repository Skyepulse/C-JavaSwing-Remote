#ifndef FILM_H
#define FILM_H
#include "Video.h"
#include <iostream>
#include <string>
#include <vector>

class Film: public Video
{
private:
    unsigned int* chaptersLength{};
    unsigned int numChapters{};



protected:
    Film() = default;

    Film(std::string name, std::string path, unsigned int length, const unsigned int* chaptersLength, unsigned int numChapters):
        Video{name, path, length}{
            setChapterLengths(chaptersLength, numChapters);
        }
    friend class DataManager;

public:

    ~Film() override{
        delete[] chaptersLength;
    }

    //Constructor for copying the object
    Film(const Film& copie): Video(copie){
        setChapterLengths(copie.chaptersLength, copie.numChapters);
    }

    std::string getClassName() const override{
        return "Film";
    }

    /*!
     * \brief write writes the object in a file
     * \param file ostream object
     */
    std::ostream& operator<<(std::ostream& file) override{
        Video::operator<<(file);
        file << numChapters << "\n";
        for(unsigned int i = 0; i < numChapters; i++)
            file << chaptersLength[i] << "\n";
        return file;
    }

    /*!
     * \brief read reads the object from a file
     * \param file istream object
     */
    std::istream& operator>>(std::istream& file) override{
        Video::operator>>(file);
        std::string line;
        std::getline(file, line);
        unsigned int numC= std::stoi(line);
        unsigned int* durations = new unsigned int[numC];
        for(unsigned int i = 0; i < numChapters; i++){
            std::getline(file, line);
            durations[i] = std::stoi(line);
        }
        setChapterLengths(durations, numC);
        delete[] durations;
        return file;
    }

    void setChapterLengths(const unsigned int* durations, unsigned int numC){
        if(chaptersLength == durations)
            return;
        delete[] chaptersLength;

        if(durations == nullptr || numC == 0){
            chaptersLength = nullptr;
            numChapters = 0;
            return;
        }
        chaptersLength = new unsigned int[numC];
        numChapters = numC;
        for(unsigned int i = 0; i < numC; i++)
            this->chaptersLength[i] = durations[i];
    }


    const unsigned int* getChapterLengths() const {
        return chaptersLength;
    }

    unsigned int getNumChapters() const {
        return numChapters;
    }

    /*!
     * \brief displayChapterDurations displays the duration of each chapter
     */
    void displayChapterDurations() const{
        for(unsigned int i = 0; i < numChapters; i++)
            std::cout << "Chapter " << (i+1) << ": " << chaptersLength[i] << " minutes. ";
        std::cout << std::endl;
    }

    /*!
     * \brief showAttributes stores in a string the object's specific attributes
        \return the string where the information is stored
     */
    std::string showAttributes() const override{
        std::string out = "Film name: " + this->getName() + ". Number of chapters: " + std::to_string(getNumChapters()) + ".";
        for(unsigned int i = 0; i < numChapters; i++)
            out += "Chapter " + std::to_string(i+1) + ": " + std::to_string(chaptersLength[i]) + " minutes. ";
        return out;
    }
};


#endif // FILM_H
