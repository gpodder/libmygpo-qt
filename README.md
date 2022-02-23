libmygpo-qt [![Build Status](https://github.com/gpodder/libmygpo-qt/workflows/C/C++%20CI/badge.svg)](https://github.com/gpodder/libmygpo-qt/actions)
=======================

### What is libmygpo-qt

libmygpo-qt is a Qt Library that wraps the gpodder.net Web API (http://wiki.gpodder.org/wiki/Web_Services/API_2)

### Copyright & License

Copyright 2010 - 2018 Stefan Derkits (stefan@derkits.at) , Christian Wagner (christian.wagner86@gmx.at) & Felix Winter (ixos01@gmail.com)

See COPYING File for License

### Maintainer

Current Maintainer: Stefan Derkits (HorusHorrendus @ irc.freenode.net)

### Requirements

* Qt 5 or 6
* CMake 3.0 or higher

### Links

* Homepage:                http://wiki.gpodder.org/wiki/Libmygpo-qt
* Git Repo:                https://github.com/gpodder/libmygpo-qt
* Doxygen Documentation:   http://stefan.derkits.at/libmygpo-doc/
* Bugreports:              http://bugs.gpodder.org
* Contact:                 gpodder@freelists.org
* IRC Channel:             #gpodder on FreeNode (irc.freenode.net)

### How to compile and install

    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Debug
    make
    make install (might need root)

To use libmygpo-qt include the Header "ApiRequest.h" into your Code. You can find the cflags & linker flags for libmygpo-qt either via pkg-config (.pc file will be installed to your System)
or via cmake (Mygpo-qtConfig.cmake will be installed to your system).

You can check the Example Application to see how you can use libmygpo-qt in your Application
