//--------------------------------------------------------------------------
// File: queens.cpp
//
// Created by: Joel S. McCance
// Creation date: Thu Feb 24 12:54:40 2011
// Last modified: Fri Feb 25 15:24:32 2011
//
//--------------------------------------------------------------------------

#include <iostream>

#include "QState.h"

int main(int argc, char* argv[])
{
    QState bob(8);

    bob.print( );
    std::cout << bob.getScore( ) << std::endl;

    return 0;
}
