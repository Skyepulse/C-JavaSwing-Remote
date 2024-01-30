#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include "Multimedia.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Group.h"
#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <sstream>

class DataManager
{
private:
    std::map<std::string, std::shared_ptr<Multimedia>> data;
    std::map<std::string, std::shared_ptr<Group>> groups;

public:
    DataManager() = default;
    ~DataManager() = default;

    void createPhoto(std::string name, std::string path, double latitude, double longitude);
    void createVideo(std::string name, std::string path, unsigned int length);
    void createFilm(std::string name, std::string path, unsigned int length, unsigned int* chaptersLength, unsigned int numChapters);
    void createGroup(std::string name);

    void writeMedias(std::ostream& o) const;
    void writeGroups(std::ostream& o) const;
    void readFactory(std::istream& i);
    
    /*!
     * \brief addMediaToGroup adds a media object to a group
     * \param mediaName the name of the media
     * \param groupName the name of the group
     */
    void addMediaToGroup(std::string mediaName, std::string groupName);

    /*!
     * \brief removeMediaFromGroup removes a media object from a group
     * \param mediaName the name of the media
     * \param groupName the name of the group
     */
    void removeMediaFromGroup(std::string mediaName, std::string groupName);
    
    /*!
     * \brief showMediaInfo shows the info of the media object with the correct name
     * \param name the name of the media
     * \param o the ostream object
     */
    void showMediaInfo(std::string name, std::ostream& o) const;

    /*!
     * \brief playMedia plays the media object with the correct name
     * \param name the name of the media
     * \returns 1 if successful, -1 if not
     */
    int playMedia(std::string name) const;

    /*!
     * \brief showGroupInfo shows the info of the group with the correct name
     * \param name the name of the group
     * \param o the ostream object
     */
    void showGroupInfo(std::string name, std::ostream& o) const;

    /*!
     * \brief destroyMedia will destroy a Media object with the correct name
     * \param name the name of the media
     */
    int destroyMedia(std::string name);

    /*!
     * \brief destroyGroup will destroy a Group object with the correct name
     * \param name the name of the group
     */
    int destroyGroup(std::string name);

    /*!
     * \brief Returns the attributes of searched media
     * \param name the name of the group
     * \returns a string with the information inside it
     */
    std::string showMediaAttributes(std::string name) const; 

    /*!
     * \brief Returns the names of media with this substring in their name
     * \param substring the substring
     * \returns a string with the information inside it
     */
    std::string searchMediaWithSubstring(std::string substring) const;
};

#endif // DATAMANAGER_H
