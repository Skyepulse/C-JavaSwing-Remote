---------------------------------QUESTIONS POUR PROJET INF224--------------------------------------------

******TP1******:
4/ On apelle les methodes sans implementations dans la classe de base des methodes virtuelles.
Il ne sera plus possible d'instancier après l'implémentation basique de Video et Photo des objets de la classe de base car cette classe devient virtuelle. 

5/ On peut utiliser le polymorphisme pour instancier des objets derivant de la même classe, et si la methode abstraite existe dans la classe parent alors les classes filles appelleront les classes overrided.
Dans le cas du c++ on doit instancier ainsi: ClassePere *objet = new classeFille1(); si on a un tableau de ClassePere*. Faire attention a bien creer un tableau avec des pointeurs et non les objets car ainsi on peut utiliser tous les avantages du Polymorphisme. Si les objets sont de grande taille, faire une liste d'objets et non de pointeurs peut prendre beaucoup de place...

6/ Pour le tableau d'entiers pour la durée des chapitres, on peut utiliser unsigned int* chapterLengths pour stocker le pointeur vers le tableau. Pour le get, il suffit d'utiliser const unsigned int* getChapterLengths() const pour empecher la modification des données. Pour le set, il faut passer en argument un nouveau pointeur et la taille du tableau, puis detruire l'ancien tableau et en creer un nouveau a partir des valeurs du tableau dont le pointeur est en argument! Ne pas oublier de set le pointeur a nullptr si on initialise sans valeurs.
Voici l'implémentation: 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

public:
    Film():
        chaptersLength(nullptr),numChapters(0){}

    Film(std::string name, std::string path, unsigned int length, unsigned int* chaptersLength, unsigned int numChapters):
        Video{name, path, length}, chaptersLength{chaptersLength}, numChapters{numChapters}{}
    ~Film(){
        std::cout << "Film Destroyed\n";
        delete[] chaptersLength;
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

7/ Il faut faire attention à modifier FILM parceque il faut detruire le tableau des chapitres dans son destructeur.
Si on copie un objet avec des pointeurs comme variable d'instance, on ne copie pas les objets pointés mais les pointeurs ce qui fait que les deux objets vont posseder des variables d'instance qui pointent vers le même objet pointé initialement (le même espace mémoire). Voici une solution: on peut réecrire un constructeur qui a en argument un autre objet de la même classe et pour chaque variable d'instance pointeur initialiser un nouveau pointeur avec des mêmes données mais pour le coup pas le même espace mémoire!

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Constructor for copying the object
    Film(const Film& copie): numChapters(copie.numChapters){
        chaptersLength = new unsigned int[numChapters];
        for(unsigned int i = 0; i < numChapters; i++)
            chaptersLength[i] = copie.chaptersLength[i];
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ici, si on essaye de faire ceci:
    Film *film = new Film("Film1", "D:\\WAMP\\www\\media\\videoRobot2.mp4", 5, chapters, 5);
    Film *film2 = new Film(*film);
    cout << film->getChapterLengths() << " " << film2->getChapterLengths() << endl;
On trouve que les deux adresses sont différentes.

8/La liste Group qui herite de std::list<Multimedia*> est bien une liste de pointeurs car par convention en c++, cela permet d'éviter des memory leak et des tailles de list grandes si les objets sont volumineux.

9/Attention la classe Group dérive donc maintenant de std::list<std::shared_ptr<Multimedia>>.

10/ POur ne pouvoir construire des objets Multimedia et Groupe que a partir de cette nouvelle classe, il suffit de mettre les constructeurs des Multimedia et Objet en protected et mettre en friend class MyClass où MyClass est la seule classe qui a accès aux constructeurs avec les classes enfant bien sûr. Aussi, vu que l'on utilise shared_ptr<> on doit créer une fonction dans chaque classe qui crée l'objet et renvoie un shared_ptr que seulement la classe qui gère toutes les structures peut appeler (en la mettant private par exemple avec la classe qui gère les structures en friend).



