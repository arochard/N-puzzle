#include "main.h"

void initTree(TreeNode &root, short *a)
{
    root.setParent(NULL);
    root.setState(a);
    root.setDepth(0);
}

void setNodeValues(TreeNode &node)
{
    node.setScore(calculateHeurestic(node.getState(), all.size));
    node.setDepth(0);
}

void setChildValues(TreeNode *node, int index, int work)
{
    TreeNode * const *children = node->getChildren();

    if (children[index] != NULL) {
        children[index]->setDepth(node->getDepth() + 1);
        if (work) {
            if (!all.greedy && !all.unicost) {
                children[index]->setScore(calculateHeurestic(node->getState(), all.size) * 2 + node->getDepth() + 1);
            }else if (all.greedy) {
                children[index]->setScore(calculateHeurestic(node->getState(), all.size));
            }else if (all.unicost) {
                children[index]->setScore(node->getDepth() + 1);
            }
        }
        children[index]->setParent(node);
        all.complexity_time++;
    }
}


