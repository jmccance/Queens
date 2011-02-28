//--------------------------------------------------------------------------
// File: queens.cpp
//
// Created by: Joel S. McCance
// Creation date: Thu Feb 24 12:54:40 2011
// Last modified: Mon Feb 28 11:19:07 2011
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

//--------------------------------------------------------------------------
// Program Main
//--------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    bool useRestarts = false;
    bool quietMode = false;
    bool printRestartCounts = false;

    unsigned int boardDimension = 8;
    int restartCount = 0;

    bool doneGettingOptions = false;
    while (not doneGettingOptions)
    {
        char optCh = getopt(argc, argv, "cqrd:");
        if (optCh == -1)
        {
            doneGettingOptions = true;
        }
        else
        {
            switch (optCh)
            {
                case 'c':
                    printRestartCounts = true;
                    break;

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
            }
        }
    }

    QState state(boardDimension);

    while (state.getScore( ) > 0 and useRestarts)
    {
        state = QState(boardDimension);
        hillClimbSearch(state);
        ++restartCount;
    }

    if (not quietMode)
    {
        state.print( );

        // Only print attack count if we weren't using restarts
        if (not useRestarts)
        {
            std::cout << "Attacking pairs: " << state.getScore( ) << std::endl;
        }
    }
    
    // Only pay attention to printRestartCounts if we were actually
    // doing restarts.
    if (printRestartCounts and useRestarts)
    {
        std::cout << "Restarts required: " << restartCount << std::endl;
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

        // Determine the smallest successor
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

        // Check for plateaux. If we're not at one, set state to the
        // smallest successor.
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
