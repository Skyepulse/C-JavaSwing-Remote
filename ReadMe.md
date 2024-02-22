# C++/JavaSwing socket communication Media remote

> This project is an implementation of a C++ media database and javaSwing remote communicating with the database in a client/server socket based communication. 

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Current Version](https://img.shields.io/badge/version-1.0.1-green.svg)](https://github.com/yourusername/projectname)

## About this project

The project was done in the context of the INF224 C++ and Java coding paradigms course at Télécom Paris. It aims at creating an effective and well structure media database using all the best convention for OOP in C++ and a simple user interface with javaSwing. It also aims at better understanding TCP socket client/server communication and building in parallel two applications with separate makefiles.

## How to build it

In order to build this project and test it, try the following steps:
1- Clone this repository on a Linux machine that can compile C++ and has Java installed.
2- Go to the c++ repository and type the command "make run".
3- Go to the swing repository and type "make run".

To clean everything, please type the "make clean-all" command in both repositories. It will clean the executables and the .class / .o files of the project.

WARNING: a rogue depend-myprog file may stop the build process with an error. If this happens please delete the file and it should work as usual. 
