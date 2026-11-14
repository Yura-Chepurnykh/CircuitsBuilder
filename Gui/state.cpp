#include "state.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& stream, State state)
{
    switch(state)
    {
    case State::LOGICAL_0:
        return stream << "logical 0 state" << '\n';
    case State::LOGICAL_1:
        return stream << "logical 0 state" << '\n';
    case State::LOGICAL_X:
        return stream << "logical x state" << '\n';
    case State::LOGICAL_Z:
        return stream << "logical z state" << '\n';
    default:
        return stream << "unknown state" << '\n';
    }
}
