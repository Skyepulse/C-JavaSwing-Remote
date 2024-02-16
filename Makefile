##########################################
#
#  Exemple de Makefile
#  Eric Lecolinet - Reda Dehak - Telecom ParisTech 2015
#  INF224 - TP C++ et Java Swing - http://www.telecom-paristech.fr/~elc/inf224
#
##########################################

#
# Nom du programme C++
#
PROG_CPP = myprog

#
# Nom du programme Java
#
PROG_JAVA = MediaRemote

#
# Fichiers sources C++ (NE PAS METTRE les .h ni les .o seulement les .cpp)
#
SOURCES_CPP = DataManager.cpp Multimedia.cpp Video.cpp Photo.cpp Film.cpp Group.cpp tcpserver.cpp ccsocket.cpp main.cpp

#
# Fichiers sources Java
#
SOURCES_JAVA = MediaRemote.java

#
# Fichiers objets C++ (ne pas modifier sauf si l'extension n'est pas .cpp)
#
OBJETS = ${SOURCES_CPP:%.cpp=%.o}

#
# Compilateur C++ et Java
#
CXX = c++
JAVAC = javac

#
# Options du compilateur C++
#   -g pour debugger, -O optimise, -Wall affiche les erreurs, -I pour les headers
#   -std=c++11 pour C++11
#
CXXFLAGS = -std=c++11 -Wall -g

#
# Options de l'editeur de liens C++
#
LDFLAGS = 

#
# Librairies a utiliser avec C++
#
LDLIBS = -lpthread

#
# Options du compilateur Java
#
JAVAFLAGS =

##########################################
#
# Regles de construction/destruction des executables
# depend-${PROG_CPP} sera un fichier contenant les dependances C++
#

all: cpp java

cpp: ${PROG_CPP}

java: $(SOURCES_JAVA)
	$(JAVAC) $(JAVAFLAGS) $(SOURCES_JAVA)

cppRun: ${PROG_CPP}
	./${PROG_CPP}

javaRun: java
	java ${PROG_JAVA}

${PROG_CPP}: depend-${PROG_CPP} ${OBJETS}
	${CXX} -o $@ ${CXXFLAGS} ${LDFLAGS} ${OBJETS} ${LDLIBS}

clean:
	-@$(RM) *.o *.class depend-${PROG_CPP} core 1>/dev/null 2>&1

clean-all: clean
	-@$(RM) ${PROG_CPP} ${PROG_JAVA}.class 1>/dev/null 2>&1

tar:
	tar cvf ${PROG_CPP}.tar.gz ${SOURCES_CPP}
	tar cvf ${PROG_JAVA}.tar.gz ${SOURCES_JAVA}

# Gestion des dependances C++ : creation automatique des dependances en utilisant 
# l'option -MM de g++ (attention tous les compilateurs n'ont pas cette option)
#
depend-${PROG_CPP}:
	${CXX} ${CXXFLAGS} -MM ${SOURCES_CPP} > depend-${PROG_CPP}

###########################################
#
# Regles implicites
#

.SUFFIXES: .cpp .cxx .c .java

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

#############################################
#
# Inclusion du fichier des dependances C++
#
-include depend-${PROG_CPP}