
#include "utils.h"

Utils::Utils()
{

}

int Utils::getIdByIndex(const QModelIndex *index)
{
    return index->sibling(index->row(), 0).data().toInt();
}

