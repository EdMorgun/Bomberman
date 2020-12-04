#ifndef STATE_H
#define STATE_H

class Doors;

class State
{
public:
    void virtual close(Doors *) = 0;
    void virtual open(Doors *) = 0;
    virtual ~State() = default;
};

#endif // STATE_H
