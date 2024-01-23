#ifndef Multimedia_H
#define Multimedia_H

#include <string>
#include <iostream>
#include <memory>

class Multimedia
{
private:
    std::string name;
    std::string path;

protected:
    Multimedia() = default;
    Multimedia(std::string name, std::string path):name{name},path{path}{}

public:

    virtual ~Multimedia(){std::cout << "Multimedia " << getName() << " has been destroyed."<< std::endl;};

    std::string getPath() const {return path;}
    std::string getName() const {return name;}

    void setPath(std::string path){this->path=path;}
    void setName(std::string name){this->name=name;}
    virtual std::string getClassName() const = 0;

    /*!
     * \brief write writes the object in a file
     * \param file ostream object
     */
    virtual void write(std::ostream& file){
        file << name << "\n";
        file << path << "\n";
    };
    /*!
     * \brief read reads the object from a file
     * \param file istream object
     */
    virtual void read(std::istream& file){
        file >> name;
        file >> path;
    };
    /*!
     * \brief showNames shows the name and path of the object
     * \param os ostream object
     */
    virtual void showNames(std::ostream& os) const = 0;

    /*!
     * \brief streamObject streams the object (shows the picture/play the video)
     */
    virtual void streamObject() const = 0;

    /*!
     * \brief showAttributes stores in a string the object's specific attributes
        \return the string where the information is stored
     */
    virtual std::string showAttributes() const = 0;
};

#endif // Multimedia_H
