#ifndef VIDEO_H
#define VIDEO_H

#include "Multimedia.h"
#include <string>
#include <iostream>
#include <cstdlib>

class Video: public Multimedia
{
private:
    unsigned int length{};

protected:
    Video() = default;
    Video(std::string name, std::string path, unsigned int length):
        Multimedia{name,path},length{length}{}
    friend class DataManager;

public:
    ~Video(){std::cout << "Video Destroyed\n";}

    void setLength(int length){this->length=length;}
    int getLength() const {return length;}

    /*!
     * \brief showNames shows the name and path of the object plus the length
     * \param os ostream object
     */
    void showNames(std::ostream& os) const override {
        os << "Name: " << getName() << " Path: " << getPath() << ". Length: " << getLength() << "." << std::endl;
    }

    /*!
     * \brief streamObject streams the object (play the video)
     */
    void streamObject() const override {
        std::string command = "mpv " + getPath() + " &";
        system(command.data());
    }

    /*!
     * \brief showAttributes stores in a string the object's specific attributes
        \return the string where the information is stored
     */
    std::string showAttributes() const override{
        std::string out = "Video name: " + this->getName() + ". Length: " + std::to_string(getLength()) + " minutes.";
        return out;
    }
};

#endif // VIDEO_H
