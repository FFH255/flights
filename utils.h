
#ifndef UTILS_H
#define UTILS_H

#include "qabstractitemmodel.h"
class Utils
{

public:
    Utils();
    static int getIdByIndex(const QModelIndex *index);
};

#endif // UTILS_H
