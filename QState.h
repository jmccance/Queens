//--------------------------------------------------------------------------
// File: QState.h
//
// Created by: Joel S. McCance
// Creation date: Fri Feb 25 11:24:34 2011
// Last modified: Tue Mar  1 11:55:27 2011
//--------------------------------------------------------------------------

#ifndef __QState_h__
#define __QState_h__

#include <vector>

class QState {
    public:
        QState( );
        /*
            Generates a board of size zero.
            Used when you want to create a QState but don't need to
            initialize it yet.
        */

        QState(int size);
        /*
            Generates a size x size QState with a random start state.
        */

        QState(QState& parent, unsigned int row, unsigned int col);
        /*
            Generates a new QState with the same state as parent, but
            moving the queen in the designated row to the designated
            column.
        */

        int getScore( );

        void generateSuccessors(std::vector<QState>& successors);
        /*
            Generate a list of successors of self and store it in the
            provide vector.

            NOTE: Would like to accept any container that supports
            push_back( ). Refer to
        */

        void printBoard( );
        /*
            Pretty-prints the state. E.g., this size-4 board
            . Q . .
            Q . . .
            . . Q .
            . . . Q
        */

    private:
        static bool _initialized;

        std::vector<unsigned int> _state;
        unsigned int _size;
        unsigned int _score;

        int countAttacks( );
        /*
            Returns the number of attacking pairs on this board.
        */
};

#endif
