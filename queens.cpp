//--------------------------------------------------------------------------
// File: queens.cpp
//
// Created by: Joel S. McCance
// Creation date: Thu Feb 24 12:54:40 2011
// Last modified: Mon Feb 28 19:04:13 2011
//
//--------------------------------------------------------------------------

#include <iostream>
#include <vector>

#include <unistd.h>

#include "QState.h"

//--------------------------------------------------------------------------
// Operation prototypes
//--------------------------------------------------------------------------

void hillClimbSearch(QState& startState);
/*
    Takes a QState and performs a basic hill-climbing search on it until
    either a goal-state is reached or a plateau is reached.
*/

void printUsage( );
/*
    Prints usage instructions to std::cout
*/

//--------------------------------------------------------------------------
// Program Main
//--------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    //... Option flags
    bool useRestarts = false;
    bool quietMode = false;

    //... Program parameters
    QState state;
    unsigned int boardDimension = 8;
    int restartCount = 0;

    //... Process command-line options
    bool doneGettingOptions = false;
    while (not doneGettingOptions)
    {
        char optCh = getopt(argc, argv, "qrd:?");
        if (optCh == -1)
        {
            doneGettingOptions = true;
        }
        else
        {
            switch (optCh)
            {
                case 'q':
                    quietMode = true;
                    break;

                case 'r':
                    useRestarts = true;
                    break;

                case 'd':
                    boardDimension = atoi(optarg);
                    if (boardDimension == 2 or boardDimension == 3)
                    {
                    std::cerr <<
                        "The 2- and 3-queens problems have zero solutions."
                        << std::endl;
                    exit(1);
                    }
                    break;
                case '?':
                default:
                    printUsage( );
                    exit(1);
            }
        }
    }

    //... Run the hill-climbing search
    do
    {
        state = QState(boardDimension);
        hillClimbSearch(state);
        ++restartCount;
    }
    while (state.getScore( ) > 0 and useRestarts);

    //... Report results

    if (not quietMode)
    {
        state.printBoard( );
    }
    
    if (useRestarts)
    {
        std::cout << "Restarts required: " << restartCount << std::endl;
    }
    else
    {
        std::cout << "Attacking pairs: " << state.getScore( ) << std::endl;
    }

    return 0;
}

//--------------------------------------------------------------------------
// Operation Definitions
//--------------------------------------------------------------------------

void hillClimbSearch(QState& state)
{
    bool atPlateau = false;

    while (state.getScore( ) > 0 and not atPlateau)
    {
        std::vector<QState> successors;

        state.generateSuccessors(successors);

        //... Determine the smallest successor
        QState smallest = *successors.begin( );
        for (std::vector<QState>::iterator it = successors.begin( );
                it != successors.end( );
                ++it)
        {
            if (it->getScore( ) < smallest.getScore( ))
            {
                smallest = *it;
            }
        }

        //... Check for plateaux.
        // If we're not at one, set state to the smallest successor.
        if (smallest.getScore( ) >= state.getScore( ))
        {
            atPlateau = true;
        }
        else
        {
            state = smallest;
        }
    }
}

//--------------------------------------------------------------------------

void printUsage( )
{
    std::cout << "Usage: queens [-rcq?] [-d N]" << std::endl;
    std::cout << "\t-r\tUse random restarts to find solution" << std::endl;
    std::cout << "\t-q\tSuppress printing the board and number of" << std::endl;
    std::cout << "\t  \tattacking queens" << std::endl;
    std::cout << "\t-d N\tSets the board dimension and number of" << std::endl;
    std::cout << "\t  \tqueens to N (Default = 8)" << std::endl;
    std::cout << "\t-?\tPrint this usage message" << std::endl;
}
