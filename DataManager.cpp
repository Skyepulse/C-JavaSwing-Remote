#include "DataManager.h"

void DataManager::createPhoto(std::string name, std::string path, double latitude, double longitude){
    if(data.find(name) != data.end()){
        std::cerr << "The name already exists\n";
        return;
    }
    std::shared_ptr<Photo> photo = std::shared_ptr<Photo>(new Photo(name, path, latitude, longitude));
    data[name] = photo;
}

void DataManager::createVideo(std::string name, std::string path, unsigned int length){
    if(data.find(name) != data.end()){
        std::cerr << "The name already exists\n";
        return;
    }
    std::shared_ptr<Video> video = std::shared_ptr<Video>(new Video(name, path, length));
    data[name] = video;
}

void DataManager::createFilm(std::string name, std::string path, unsigned int length, unsigned int* chaptersLength, unsigned int numChapters){
    if(data.find(name) != data.end()){
        std::cerr << "The name already exists\n";
        return;
    }
    std::shared_ptr<Film> film = std::shared_ptr<Film>(new Film(name, path, length, chaptersLength, numChapters));
    data[name] = film;
}

void DataManager::createGroup(std::string name){
    if(groups.find(name) != groups.end()){
        std::cerr << "The group name already exists\n";
        return;
    }
    std::shared_ptr<Group> group = std::shared_ptr<Group>(new Group(name));
    groups[name] = group;
}

void DataManager::addMediaToGroup(std::string mediaName, std::string groupName){
    if(data.find(mediaName) == data.end()){
        std::cerr << "The media name doesn't exist\n";
        return;
    }
    if(groups.find(groupName) == groups.end()){
        std::cerr << "The group name doesn't exist\n";
        return;
    }
    //Also we check the media is not already in the group
    for(auto i = groups[groupName]->begin(); i != groups[groupName]->end(); i++){
        if((*i)->getName() == mediaName){
            std::cerr << "The media is already in the group\n";
            return;
        }
    }
    groups[groupName]->push_back(data[mediaName]);
}

void DataManager::removeMediaFromGroup(std::string mediaName, std::string groupName){
    if(data.find(mediaName) == data.end()){
        std::cerr << "The media name doesn't exist\n";
        return;
    }
    if(groups.find(groupName) == groups.end()){
        std::cerr << "The group name doesn't exist\n";
        return;
    }
    //We check if the media is in the Group that is a std::list<std::shared_ptr<MultiMedia>>
    for(auto i = groups[groupName]->begin(); i != groups[groupName]->end(); i++){
        if((*i)->getName() == mediaName){
            groups[groupName]->erase(i);
            return;
        }
    }
    std::cerr << "The media exists but is not in the group mentioned. No deletion done.\n";
}

void DataManager::showMediaInfo(std::string name, std::ostream& o) const{
    if(data.find(name) == data.end()){
        std::cerr << "The name doesn't exist\n";
        return;
    }
    data.at(name)->showNames(o);
}

std::string DataManager::searchMediaWithSubstring(std::string substring) const{
    std::stringstream resultStringStream;
    resultStringStream << "Existing and accessible multimedia in the database so far: ";
    bool firstFound = false;
    for(const auto& pair: data){
        const std::string& key = pair.first;
        if (key.find(substring) != std::string::npos) {
            if (firstFound) {
                resultStringStream << ", ";
            }
            resultStringStream << key;
            firstFound = true;
        }
    }
    if(firstFound){
        return resultStringStream.str();
    }
    return "No multimedia found with this substring!";
}

void DataManager::showGroupInfo(std::string name, std::ostream &o) const{
    if(groups.find(name) == groups.end()){
        std::cerr << "The group name doesn't exist\n";
        return;
    }
    groups.at(name)->showGroupInfo(o);
}

int DataManager::playMedia(std::string name) const{
    if(data.find(name) == data.end()){
        std::cerr << "The name doesn't exist\n";
        return -1;
    }
    data.at(name)->streamObject();
    return 1;
}

int DataManager::destroyMedia(std::string name){
    if(data.find(name) == data.end()){
        std::cerr << "The name doesn't exist no nee to destroy it\n";
        return -1;
    }
    std::shared_ptr<Multimedia> mediaToDelete = data.at(name);
    //We first need to take the media out of all the groups he is in. We iterate through each group and delete the media if it is in it
    for(auto i = groups.begin(); i != groups.end(); i++){
        //We check if the media is in the Group that is a std::list<std::shared_ptr<MultiMedia>>
        for(auto j = i->second->begin(); j != i->second->end(); j++){
            if((*j)->getName() == name){
                i->second->erase(j);
                break;
            }
        }
    }
    data.erase(name);
    mediaToDelete.reset(); //Destroys the object
    return 1;
}

int DataManager::destroyGroup(std::string name){
    if(groups.find(name) == groups.end()){
        std::cerr << "The group name doesn't exist no need to destroy it\n";
        return -1;
    }
    std::shared_ptr<Group> groupToDelete = groups.at(name);
    groups.erase(name);
    groupToDelete.reset(); //Destroys the object
    return 1;
}

std::string DataManager::showMediaAttributes(std::string name) const {
    if(data.find(name) == data.end()){
        std::string responseError = "Error, the media requested has not been found.";
        return responseError;
    }

    return data.at(name)->showAttributes();
}

void DataManager::writeMedias(std::ostream& o) const{
    for(auto i = data.begin(); i != data.end(); i++){
        o << i->second->getClassName() << "\n";
        i->second->write(o);
    }
}

void DataManager::writeGroups(std::ostream& o) const{
    for(auto i = groups.begin(); i != groups.end(); i++){
        o << i->second->getClassName() << "\n";
        i->second->write(o);
    }
}