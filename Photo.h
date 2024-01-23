#ifndef PHOTO_H
#define PHOTO_H

#include "Multimedia.h"
#include <string>
#include <iostream>
#include <cstdlib>

class Photo: public Multimedia
{
private:
    double latitude{};
    double longitude{};



protected:
    Photo()=default;
    Photo(std::string name, std::string path, double latitude, double longitude):
        Multimedia{name, path}, latitude{latitude}, longitude{longitude}{}
    friend class DataManager;
public:

    ~Photo(){std::cout<<"Photo Destroyed\n";}

    void setLatitude(double latitude){this->latitude=latitude;}
    void setLongitude(double longitude){this->longitude=longitude;}
    double getLatitude() const {return latitude;}
    double getLongitude() const {return longitude;}

    std::string getClassName() const override{
        return "Photo";
    }

    /*!
     * \brief write writes the object in a file
     * \param file ostream object
     */
    void write(std::ostream& file) override{
        Multimedia::write(file);
        file << latitude << "\n";
        file << longitude << "\n";
    }

    /*!
     * \brief read reads the object from a file
     * \param file istream object
     */
    void read(std::istream& file) override{
        Multimedia::read(file);
        file >> latitude;
        file >> longitude;
    }
    
    /*!
     * \brief showNames shows the name and path of the object plus the longitude and latitude
     * \param os ostream object
     */
    void showNames(std::ostream& os) const override {
        os << "Name: " << getName() << " Path: " << getPath() << ". Longitude: " << getLongitude() << " Latitude: " << getLatitude() << "." << std::endl;
    }

    /*!
     * \brief streamObject streams the object (shows the picture)
     */
    void streamObject() const override {
        std::string command = "imagej " + getPath() + " &";
        system(command.data());
    }

    /*!
     * \brief showAttributes stores in a string the object's specific attributes
        \return the string where the information is stored
     */
    std::string showAttributes() const override{
        std::string out = "Photo name: " + this->getName() + ". Latitude: " + std::to_string(getLatitude()) + ", Longitude: " + std::to_string(getLongitude()) + ".";
        return out;
    }
};

#endif // PHOTO_H
