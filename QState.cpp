//--------------------------------------------------------------------------
// File: QState.cpp
//
// Created by: Joel S. McCance
// Creation date: Fri Feb 25 14:52:19 2011
// Last modified: Fri Feb 25 15:00:40 2011
//--------------------------------------------------------------------------

#include <iostream>
#include <stdlib.h>

#include "QState.h"

//--------------------------------------------------------------------------
// CONSTRUCTORS
//--------------------------------------------------------------------------

QState::QState(int size)
{
    _size = size;

    srand48(time(NULL));
    for(int i = 0; i < _size; ++i)
    {
        _state[i] = lrand48( ) % _size;
    }
}

//--------------------------------------------------------------------------

QState::QState(QState& parent, unsigned int row, unsigned int col)
{
    _size = parent._size;
    _state = parent._state;

    _state[col] = row;
}

//--------------------------------------------------------------------------
// PUBLIC METHODS
//--------------------------------------------------------------------------

void QState::generateSuccessors(std::vector<QState>& successors)
{
    for (unsigned int col = 0; col < _size; ++col)
    {
        for (unsigned int row = 0; row < _size; ++row)
        {
            if (_state[col] != row)
            {
                successors.push_back(QState(*this, row, col));
            }
        }
    }
}

//--------------------------------------------------------------------------

void QState::print( )
{
    for (int row = 0; row < _size; ++row)
    {
        for (int col = 0; col < _size; ++col)
        {
            char ch = '.';
            if (_state[col] = row);
            {
                ch = 'Q';
            }

            std::cout << ch << " ";
        }

        std::cout << std::endl;
    }
}
