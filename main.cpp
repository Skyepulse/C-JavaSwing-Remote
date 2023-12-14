#include <iostream>
#include <vector>
#include <string>
#include <memory>

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

    DataManager *manager = new DataManager();
    //Creation of a Photo and Video list
    MultimediaPointer first = manager->createPhoto("Photo1","D:\\WAMP\\www\\media\\pipe.png", 3, 4);
    MultimediaPointer second = manager->createVideo("Video1", "D:\\WAMP\\www\\media\\videoRobot2.mp4", 5);
    MultimediaPointer third = manager->createPhoto("Photo2", "D:\\WAMP\\www\\media\\3275.jpg ", 3, 4);

    //Creation of a FILM:
    unsigned int* chapters = new unsigned int[5]{1, 2, 3, 4, 5};
    manager->createFilm("Film1", "D:\\WAMP\\www\\media\\videoRobot2.mp4", 5, chapters, 5);

    //Creation of a Group
    GroupPointer group1 = manager->createGroup("Group1");
    GroupPointer group2 = manager->createGroup("Group2");
    group1->push_back(first);
    group1->push_back(second);
    group2->push_back(third);
    manager->showGroupInfo("Group2", cout);

    manager->destroyMedia("Photo2");

    manager->showGroupInfo("Group2", cout);



    return 0;
}
