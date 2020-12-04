#include "statedoors.h"

void Close::open(Doors *d)
{
    d->m_close = true;
    d->setCurrent(new Open());
    delete this;
}

void Open::close(Doors *d)
{
    d->m_close = false;
    d->setCurrent(new Close());
    delete this;
}

