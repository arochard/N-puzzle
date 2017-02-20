#include "main.h"

std::vector<short >	snail(int m, int n)
{
    std::vector<short >a(all.size * all.size);
    int i, k = 0, l = 0;
    int print = 0;
    while (k < m && l < n)
    {
        for (i = l; i < n; ++i)
        {
            print++;
            a[k * all.size + i] = print;
        }
        k++;

        for (i = k; i < m; ++i)
        {
            print++;
            a[i * all.size + n - 1] =  print;
        }
        n--;

        if ( k < m)
        {
            for (i = n-1; i >= l; --i)
            {
                print++;
                a[(m-1)*all.size + i] =  print;
            }
            m--;
        }

        if (l < n)
        {
            for (i = m-1; i >= k; --i)
            {
                print++;
                a[i * all.size  + l] = print;
            }
            l++;
        }
    }
    i = std::find(a.begin(),a.end(),all.size * all.size) - a.begin();
    a[i] = 0;
    return a;
}

std::vector<short >	final(void)
{
    std::vector<short > a(all.size * all.size);
    int i;

    for (i = 0; i <  all.size * all.size - 1; i++)
    {
        a[i] = i + 1;
    }
    a[ all.size * all.size - 1 ] = 0;
    return a;
}


std::vector<std::vector<short> > generate_manhattam_tab(std::vector<short> a, int n){

    std::vector<std::vector<short> > manhattan(n * n,std::vector<short>(n * n,0));
    std::cout<<std::endl;
    for (int i = 0; i < n * n ; i++){
        for (int j = 0; j < n * n ; j++)
            manhattan[i][j] = get_manhattanvalue(i, j ,n);
    }
    all.finalsnail = snail(all.size, all.size);
    all.final = final();
    return manhattan;
}

int solvable2(std::vector<short> &a, int n){
    int count = 0;
    int row = 0;
    int solv;

    all.man_tab = generate_manhattam_tab(a, n);
    for (int i = 0; i < (n * n); i++){
        if (a[i] == 0){
            row = abs(i / n - all.size);
        }
        for (int j = i + 1; j < (n * n); j++ ){
            if (a[i] > a[j] && a[j] != 0 && a[i] != 0) {
                count = count + 1;
            }
        }
    }
    if (n % 2 == 1)
        solv = count % 2;
    else if (row % 2 == 0)
        solv = count % 2;
    else
        solv = !(count % 2);
    if (all.size >= 6 && (all.size - 6) % 8 >= 0 && (all.size - 6) % 8 <= 3)
        solv = solv ? 0 : 1;
    return solv;
}


int solvable(std::vector<short> a, int n){
    TreeNode root = TreeNode(n);

    if (solvable2(a, n))
    {
        initTree(root, &a[0]);
        astar(root);
        return 1;
    }
    else
    {
        for (int i = 0; i < a.size(); i++)
        {
            std::cout<<a[i]<<" ";
        }
        std::cout<<"solution does not exist in this configuration"<<std::endl;
        return 0;
    }
}


void normalized(std::vector<short> &a)
{
    std::vector<short> indexes;
    for (short i = 0; i < a.size(); i++) {
        if (all.finalsnail[i] != (i + 1)){
            indexes.push_back((short)(std::find(a.begin(),a.end(), all.finalsnail[i]) - a.begin()));
        }
    }
    for (int i = 0; i < all.swaps.size(); i = i + 2) {
        a[indexes[i/2]]  = all.swaps[i + 1];
    }

}

void normalized2(std::vector<short> &a)
{
    std::vector<short> indexes;
    for (short i = 0; i < a.size(); i++) {
        if (all.finalsnail[i] != (i + 1)){
            all.swaps.push_back(all.finalsnail[i]);
            all.swaps.push_back(all.final[i]);
        }
    }
}

int get_manhattanvalue(int i, int j, int n)
{
    int count = -1;

    if (i > j)
    {
        i ^= j;
        j ^= i;
        i ^= j;
    }
    while (i <= j)
    {
        count++;
        j -= n;
    }
    j += n;
    while (j != i)
    {
        j--;
        count++;
    }
    return count;
}

