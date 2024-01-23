#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unistd.h>
#include <sstream>
#include <limits.h>

#include "Multimedia.h"
#include "DataManager.h"
#include "Video.h"
#include "Photo.h"
#include "Film.h"
#include "Group.h"
#include "tcpserver.h"

using namespace std;
using MultimediaPointer = std::shared_ptr<Multimedia>;
using GroupPointer = std::shared_ptr<Group>;

const int PORT = 3332;

int main()
{

    char currentPathCStr[PATH_MAX];
    std::string currentPathVar;

    if(getcwd(currentPathCStr, sizeof(currentPathCStr)) != NULL){
        //cout << currentPathCStr << endl;
        std::string currentPath(currentPathCStr);
        currentPathVar = currentPath;
    } else
        cerr << "Failed to retrieve current working directory path" << endl;

    DataManager *manager = new DataManager();
    //Creation of a Photo and Video list
    MultimediaPointer first = manager->createPhoto("Photo1",currentPathVar + "/testMedia/sample1.png", 3, 4);
    MultimediaPointer second = manager->createVideo("Video1", currentPathVar +"/testMedia/sample-5s.mp4", 5);
    MultimediaPointer third = manager->createPhoto("Photo2", currentPathVar +"/testMedia/sample2.jpeg ", 3, 4);

    //Creation of a FILM:
    unsigned int* chapters = new unsigned int[5]{1, 2, 3, 4, 5};
    manager->createFilm("Film1", currentPathVar +"/testMedia/sample-5s.mp4", 5, chapters, 5);

    //Creation of a Group
    GroupPointer group1 = manager->createGroup("Group1");
    GroupPointer group2 = manager->createGroup("Group2");
    group1->push_back(first);
    group1->push_back(second);
    group2->push_back(third);
    

   //Créer le tcpserver
   auto* serveur = new TCPServer([&](std::string const& request, std::string& response){
        if(request.find("find") == 0){
            size_t findSubstring = request.find("find ");
            std::string media = request.substr(findSubstring + 5);

            response = manager->showMediaAttributes(media);

        } else if(request.find("play") == 0){
            size_t playSubstring = request.find("play ");
            std::string media = request.substr(playSubstring + 5);
            int success = manager->playMedia(media);
            if(success < 0)
                response = "Error, the media given does not exist";
            else
                response = "Played media successfully";
        } else if(request.find("search") == 0){
            size_t searchSubstring = request.find("search ");
            std::string name = request.substr(searchSubstring + 7);
            response = manager->searchMediaWithSubstring(name);
        }else {
            response = "The command you tried to execute does not exist in the current context of this Multimedia Server. To find a media and display its attributes write find ..., or play ... if you want to play it. To search all multimedia existing names write search, or search ... to find a multimedia containing a particulatr substring!";
            cout << "The command received is not recognized." << endl;
        }

        return true;
   });

   cout << "Attention, starting server on port " << PORT << endl;
   int status = serveur->run(PORT);

   if(status < 0){
    cerr << "Error when trying to initialize the server" << endl;
    return 1;
   }

    return 0;
}
