#include "main.h"

//TMP
#include <stdlib.h>

int linear_conflict(std::vector<short> *b)
{
    int lines = (*b).size() / all.size;
    int currentline = 0;
    int sumconflict = 0;
    int passline;

    for (;currentline < lines; currentline++)
    {
        passline = currentline * lines;
        for (int i = 0; i < lines; i++)
        {
            for (int j = 1; j < lines; j++)
            {
                if (j >= i + 1 && (*b)[i + passline] > (*b)[j + passline] && (*b)[i + passline] - 1 >= passline
                    && (*b)[i + passline] - 1 < (currentline + 1) * lines && (*b)[j + passline] - 1 >= passline && (*b)[j + passline] - 1 < (currentline + 1) * lines)
                {
                    sumconflict += 4;
                }
                if (i + (passline) < i + (j * lines)  && (*b)[i + (passline)] > (*b)[i + (j * lines)]
                    &&  ((*b)[i + (passline)] % lines - 1 == currentline) && (*b)[i + (j * lines)] % lines - 1 == currentline)
                {
                    sumconflict += 4;
                }
            }

        }
    }
    return sumconflict;
}

static int      calculateOutOfRowCol(short *a, int n)
{
    int         sum = 0;

    for (int i = 0; i < n * n; i++)
    {
        if (a[i] > 0 && all.man_tab[a[i] - 1][i] > 0)
        {
            if ((i / n) != (all.final[a[i] - 1] / n))
                sum += 1;
            if (((i + 1) % n) != (all.final[a[i] - 1] % n))
                sum += 1;
        }
    }

    return sum;
}

static int     calculateManhattam(short *a, int n)
{
    int sum;

    sum = 0;
    for (int i = 0; i < n * n; i++)
    {
        if (a[i] > 0) {
            sum += all.man_tab[a[i] - 1][i];
        }
        else if (a[i] == 0) {
            sum += all.man_tab[8][i];
        }
    }
    return sum;
}

static int     calculateHamming(short *a, int n)
{
    int sum;

    sum = 0;
    for (int i = 0; i < n * n; i++)
    {
        if (a[i] != (i + 1)) {
            sum += 1;
        }
    }
    return sum;
}


int calculateHeurestic(std::vector<short> *a, int n)
{
    std::vector<short> b(*a);

    normalized(b);

    if (all.heuristic == 1) {
        return calculateManhattam(&b[0], n) + linear_conflict(&b) ;
    }
    else if (all.heuristic == 2) {
        return calculateHamming(&b[0], n) + linear_conflict(&b);
    }
    else if (all.heuristic == 3) {
        return calculateOutOfRowCol(&b[0], n) + linear_conflict(&b);
    }
    return -1;
}
