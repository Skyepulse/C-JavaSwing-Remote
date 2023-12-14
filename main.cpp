#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unistd.h>
#include <limits.h>

#include "Multimedia.h"
#include "DataManager.h"
#include "Video.h"
#include "Photo.h"
#include "Film.h"
#include "Group.h"

using namespace std;
using MultimediaPointer = std::shared_ptr<Multimedia>;
using GroupPointer = std::shared_ptr<Group>;

int main()
{
    char currentPathCStr[PATH_MAX];
    std::string currentPathVar;

    if(getcwd(currentPathCStr, sizeof(currentPathCStr)) != NULL){
        cout << currentPathCStr << endl;
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
    manager->playMedia("Film1");
    manager->playMedia("Photo1");
    manager->playMedia("Photo2");

    return 0;
}
