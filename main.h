#pragma once
#include <boost/spirit/include/qi.hpp>
#include <boost/tokenizer.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <boost/program_options.hpp>
#include <unordered_map>
#include <fstream>
#include <queue>
#include <algorithm>
#include <boost/functional/hash.hpp>
#include "TreeNode.h"

struct Comp{
    bool operator()(const TreeNode *a, const TreeNode *b){
        return a->getScore()>b->getScore();
    }
};

struct CompEnd{
    bool operator()(const TreeNode *a, const TreeNode *b){
        return a->getDepth()>b->getDepth();
    }
};

typedef struct program{
    int size;
    std::vector<std::vector<short>> man_tab;
    std::vector<short > finalsnail;
    std::vector<short > final;
    std::vector<short > swaps;
    int complexity_time; // number of states ever represented in memory at the same time during the search
    int                 heuristic;
    bool                greedy;
    bool                unicost;
//    int pathcost;
    int                 nb_moves;
    int                 blank;
}               g_program;

typedef struct s_astar{
    std::priority_queue< TreeNode*, std::vector<TreeNode*>, Comp> pq;
    std::unordered_map<std::string, TreeNode*> opened; //, container_hash<std::vector<int>>
    std::unordered_map<std::string, TreeNode*> closed;

    std::priority_queue< TreeNode*, std::vector<TreeNode*>, CompEnd> pq_end;
    std::unordered_map<std::string, TreeNode*> opened_end;
    std::unordered_map<std::string, TreeNode*> closed_end;
    TreeNode **children;//NULL
    TreeNode *e;
    TreeNode *e2;

    bool                   success;//false
    bool                   success2;//false
}              t_astar;
extern g_program all;



int get_manhattanvalue(int i, int j, int n);
int linear_conflict(std::vector<short> *b);
void normalized(std::vector<short> &a);
void normalized2(std::vector<short> &a);
int calculateHeurestic(std::vector<short> *a, int n);

void initTree(TreeNode &root, short *a);
void setNodeValues(TreeNode &node);
void setChildValues(TreeNode *node, int index, int work);

void astar(TreeNode &root);

std::vector<short >	snail(int m, int n);
std::vector<short >	final(void);
int solvable(std::vector<short> a, int n);