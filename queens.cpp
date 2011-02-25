//--------------------------------------------------------------------------
// File: queens.cpp
//
// Created by: Joel S. McCance
// Creation date: Thu Feb 24 12:54:40 2011
// Last modified: Fri Feb 25 18:49:31 2011
//
//--------------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "QState.h"

// Operation prototypes
//--------------------------------------------------------------------------

void hillClimbSearch(QState& startState);

//--------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    const int NUM_TRIALS_WITHOUT_RESTARTS = 100;
    const int NUM_TRIALS_WITH_RESTARTS = 50;

    //... Run a set of trials without restarts and count the failures.
    int failureCount = 0;
    for (int i = 0; i < NUM_TRIALS_WITHOUT_RESTARTS; ++i)
    {
        QState state(8);

        hillClimbSearch(state);

        if (state.getScore( ) > 0)
        {
            ++failureCount;
        }
    }

    std::cout << "Searches that hit plateaux: " << failureCount << std::endl;

    //... Run a set of trials WITH restarts and count the average number
    //    of restarts per search.
    int searchCount = 0;
    for (int i = 0; i < NUM_TRIALS_WITH_RESTARTS; ++i)
    {
        QState state(8);
        int lastScore = -1;

        while (state.getScore( ) > 0)
        {
            hillClimbSearch(state);
            ++searchCount;

            if (state.getScore( ) == lastScore)
            {
                state = QState(8);
                lastScore = -1;
            }
            else
            {
                lastScore = state.getScore( );
            }
        }
    }

    std::cout << "Average restarts per search: " <<
            (float)searchCount/NUM_TRIALS_WITH_RESTARTS << std::endl;

    return 0;
}

//--------------------------------------------------------------------------
// OPERATION DEFINITIONS
//--------------------------------------------------------------------------

void hillClimbSearch(QState& state)
{
    bool atPlateau = false;

    while (state.getScore( ) > 0 and not atPlateau)
    {
        std::vector<QState> successors;

        state.generateSuccessors(successors);

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
