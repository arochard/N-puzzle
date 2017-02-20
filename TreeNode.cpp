//
// Created by Stefan-ciprian CIRCIU on 1/9/17.
//

#include "TreeNode.h"
#include "main.h"

TreeNode::TreeNode(int size) {
    state = std::vector<short>(size * size, 0);
}

TreeNode::TreeNode(TreeNode const &a) {
    *this = a;
}
TreeNode::TreeNode(std::vector<short> prev) {
    state = prev;
}


TreeNode::~TreeNode(void) {
}

int TreeNode::getScore(void) const {
    return score;
}

void TreeNode::setScore(int score) {
    TreeNode::score = score;
}

int TreeNode::getDepth(void) const {
    return depth;
}

void TreeNode::setDepth(int depth) {
    TreeNode::depth = depth;
}

std::vector <short> *TreeNode::getState(void){
    return &state;
}

void TreeNode::setState(short *state) {
    std::memcpy(&this->state[0], state, sizeof(short) * all.size * all.size);
}

TreeNode *const *TreeNode::getChildren(void) const {
    return children;
}

TreeNode *TreeNode::getParent(void) const {
    return parent;
}

void TreeNode::setParent(TreeNode *parent) {
    TreeNode::parent = parent;
}

void TreeNode::setChildren(TreeNode *children, int index) {
    TreeNode::children[index] = children;
}

bool TreeNode::operator==(const TreeNode &rhs) const {
    return std::memcmp(&this->state[0], &rhs.state[0], sizeof(short) * all.size * all.size);
}

void TreeNode::operator=(const TreeNode &rhs) {
    this->state = rhs.state;
    this->stringedState = rhs.getStringedState();
    this->parent = rhs.getParent();
    this->depth = rhs.getDepth();
    this->score = rhs.getScore();
    this->stringedState = rhs.getStringedState();
    this->children[0] = rhs.getChildren()[0];
    this->children[1] = rhs.getChildren()[1];
    this->children[2] = rhs.getChildren()[2];
    this->children[3] = rhs.getChildren()[3];
}

bool TreeNode::operator!=(const TreeNode &rhs) const {
    return !(rhs == *this);
}

std::string TreeNode::getStringedState(void) const {
    return stringedState;
}

void TreeNode::setStringedState(const std::string &stringedState) {
    TreeNode::stringedState = stringedState;
}

void TreeNode::StateToStr(void)
{
    std::string str;
    for (auto a:state)
    {
        str += std::to_string(a) ;
    }
    this->setStringedState(str);
}

TreeNode *TreeNode::up(void)
{
    //blank position is calculated only here due to performance
    all.blank = std::find(state.begin(),state.end(),0) - state.begin();
    if (all.blank > (all.size - 1))
    {
        std::vector<short> a(*this->getState());
        a[all.blank] = a[all.blank - all.size];
        a[all.blank - all.size] = 0;
        TreeNode *up = new TreeNode(a);
        up->StateToStr();
        return up;
    }
    return NULL;
}

TreeNode *TreeNode::down(void)
{
    int max = all.size * all.size;
    if (all.blank <= (max - all.size - 1))
    {
        std::vector<short> a(*this->getState());
        a[all.blank] = a[all.blank + all.size];
        a[all.blank + all.size] = 0;
        TreeNode *down = new TreeNode(a);
        down->StateToStr();
        return down;
    }
    return NULL;
}

TreeNode * TreeNode::right(void)
{
    if ((all.blank + 1) % all.size != 0)
    {
        std::vector<short> a(*this->getState());
        a[all.blank] = a[all.blank + 1];
        a[all.blank + 1] = 0;
        TreeNode *right = new TreeNode(a);
        right->StateToStr();
        return right;
    }
    return NULL;
}

TreeNode * TreeNode::left(void)
{
    if ((all.blank + 1) % all.size != 1)
    {
        std::vector<short> a(*this->getState());
        a[all.blank] = a[all.blank - 1];
        a[all.blank - 1] = 0;
        TreeNode *left = new TreeNode(a);
        left->StateToStr();
        return left;
    }
    return NULL;
}

void TreeNode::printmap(void)
{
    int max = all.size * all.size;
    for (int i = 0; i < max; i++)
    {
        std::cout<<state[i];
        if ((i + 1) % all.size > 0) {
            if (max > 9 && state[i] < 10)
                std::cout << "  ";
            else
                std::cout << " ";
        }
        else
            std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
void TreeNode::printree(void)
{
    if (this->parent != NULL){
        this->parent->printree();
        all.nb_moves++;
        this->printmap();
    }
    else
        this->printmap();
}
void TreeNode::printree_end(void)
{
    this->printmap();
    if (this->parent != NULL){
        this->parent->printree_end();
        all.nb_moves++;
    }

}
