//--------------------------------------------------------------------------
// File: QState.cpp
//
// Created by: Joel S. McCance
// Creation date: Fri Feb 25 14:52:19 2011
// Last modified: Mon Feb 28 18:15:09 2011
//--------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "QState.h"

//--------------------------------------------------------------------------
// INITIALIZATION
//--------------------------------------------------------------------------

bool QState::_initialized = false;

//--------------------------------------------------------------------------
// CONSTRUCTORS
//--------------------------------------------------------------------------

QState::QState(int size)
{
    if (not _initialized)
    {
        std::ifstream urandom;
        long seed;
        urandom.open("/dev/urandom", std::ios::in | std::ios::binary);
        urandom.read(reinterpret_cast<char*>(&seed), sizeof(seed));
        srand48(seed);
        _initialized = true;
        urandom.close( );
    }

    _size = size;

    for(unsigned int i = 0; i < _size; ++i)
    {
        _state.push_back(lrand48( ) % _size);
    }

    _score = countAttacks( );
}

//--------------------------------------------------------------------------

QState::QState(QState& parent, unsigned int row, unsigned int col)
{
    _size = parent._size;
    _state = parent._state;

    _state[col] = row;

    _score = countAttacks( );
}

//--------------------------------------------------------------------------
// PUBLIC METHODS
//--------------------------------------------------------------------------

int QState::getScore( )
{
    return _score;
}

//--------------------------------------------------------------------------

void QState::generateSuccessors(std::vector<QState>& successors)
{
    for (unsigned int col = 0; col < _size; ++col)
    {
        for (unsigned int row = 0; row < _size; ++row)
        {
            // Only generate successor if it is not identical to the
            // parent.
            if (_state[col] != row)
            {
                QState state(*this, row, col);
                successors.push_back(state);
            }
        }
    }
}

//--------------------------------------------------------------------------

void QState::print( )
{
    for (unsigned int row = 0; row < _size; ++row)
    {
        for (unsigned int col = 0; col < _size; ++col)
        {
            char ch = '-';

            if (_state[col] == row)
            {
                ch = 'Q';
            }

            std::cout << ch << " ";
        }

        std::cout << std::endl;
    }
}


//--------------------------------------------------------------------------
// PRIVATE METHODS
//--------------------------------------------------------------------------

int QState::countAttacks( )
{
    int attackCount = 0;

    for (unsigned int i = 0; i < _size - 1; ++i)
    {
        for (unsigned int j = i + 1; j < _size; ++j)
        {
            // Are the queens in the same row?
            if (_state[i] == _state[j])
            {
                ++attackCount;
            }
            else
            {
                // Are the queens on a shared diagonal?
                int row_diff = i - j;
                int col_diff = _state[i] - _state[j];

                if (row_diff*row_diff == col_diff*col_diff)
                {
                    ++attackCount;
                }
            }
        }
    }

    return attackCount;
}
