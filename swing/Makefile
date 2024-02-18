# Nom du programme Java
#
PROG_JAVA = MediaRemote

# Fichiers sources Java
#
SOURCES_JAVA = MediaRemote.java

# Compilateur Java
#
JAVAC = javac

# Options du compilateur Java
#
JAVAFLAGS =

all: java

java: $(SOURCES_JAVA)
	$(JAVAC) $(JAVAFLAGS) $(SOURCES_JAVA)

run: java
	java ${PROG_JAVA}

clean:
	-@$(RM) *.class 1>/dev/null 2>&1

clean-all: clean
	-@$(RM) ${PROG_JAVA}.class 1>/dev/null 2>&1

tar:
	tar cvf ${PROG_JAVA}.tar.gz ${SOURCES_JAVA}

###########################################
#
# Regles implicites
#

.SUFFIXES: .java