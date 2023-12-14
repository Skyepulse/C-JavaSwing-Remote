#ifndef FILM_H
#define FILM_H
#include "Video.h"
#include <iostream>
#include <string>
#include <vector>

class Film: public Video
{
private:
    unsigned int* chaptersLength;
    unsigned int numChapters;



protected:
    Film():
        chaptersLength(nullptr),numChapters(0){}

    Film(std::string name, std::string path, unsigned int length, unsigned int* chaptersLength, unsigned int numChapters):
        Video{name, path, length}, chaptersLength{chaptersLength}, numChapters{numChapters}{}
    friend class DataManager;

public:

    ~Film(){
        std::cout << "Film Destroyed\n";
        delete[] chaptersLength;
    }

    //Constructor for copying the object
    Film(const Film& copie): numChapters(copie.numChapters){
        chaptersLength = new unsigned int[numChapters];
        for(unsigned int i = 0; i < numChapters; i++)
            chaptersLength[i] = copie.chaptersLength[i];
    }

    void setChapterLengths(unsigned int* durations, unsigned int numC){
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
};


#endif // FILM_H
