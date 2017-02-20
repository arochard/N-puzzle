//
// Created by Stefan-ciprian CIRCIU on 1/9/17.
//

#pragma once
#include <algorithm>
#include <boost/functional/hash.hpp>
#include <fstream>

class TreeNode {
public:
    TreeNode(int size);
    TreeNode(TreeNode const &a);
    TreeNode(std::vector<short> prev);

    virtual ~TreeNode(void);

    int getScore(void) const;
    void setScore(int score);
    void printree(void);
    void printree_end(void);
    int getDepth(void) const;
    void setDepth(int depth);
    std::vector <short> *getState(void);
    void setState(short *state);
    TreeNode *const *getChildren(void) const;
    void setChildren(TreeNode *children, int index);
    TreeNode *getParent(void) const;
    void setParent(TreeNode *parent);

    bool operator==(const TreeNode &rhs) const;

    void operator=(const TreeNode &rhs);
    bool operator!=(const TreeNode &rhs) const;
    std::string getStringedState() const;
    void StateToStr(void);
    void setStringedState(const std::string &stringedState);

    TreeNode *up(void);
    TreeNode *down(void);
    TreeNode *right(void);
    TreeNode *left(void);
    void printmap(void);
    std::vector<short>    state;


private:
    TreeNode(void);
    int score;
    int depth;
    std::string         stringedState;

    TreeNode *children[4];
    TreeNode *parent;


};

