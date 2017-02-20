#include "main.h"

void    astar3(t_astar &var, int index)
{
    if (var.opened_end.find(var.children[index]->getStringedState()) == var.opened_end.end() &&
        var.closed_end.find(var.children[index]->getStringedState()) == var.closed_end.end()) {
        setChildValues(var.e, index, 0);
        var.pq_end.push((var.children[index]));
        var.opened_end.insert({var.children[index]->getStringedState(), (var.children[index])});
    }
    else
        delete var.children[index];
}
int    astar2(t_astar &var, int index)
{
    if (var.opened_end.find(var.children[index]->getStringedState()) != var.opened_end.end()
        || var.closed_end.find(var.children[index]->getStringedState()) != var.closed_end.end())
    {
        if (var.opened_end.find(var.children[index]->getStringedState()) != var.opened_end.end())
        {
            var.e2 = var.opened_end[var.children[index]->getStringedState()];
        }
        else
        {
            var.e2 = var.closed_end[var.children[index]->getStringedState()];
        }
        var.success = true;
        var.e->printree();
        var.e2->printree_end();
        std::cout<<"complexity_time / "<<all.complexity_time<<std::endl;
        std::cout<<"complexity_size / "<<var.closed.size() + var.closed_end.size()<<std::endl;
        std::cout <<"nb_moves : " << all.nb_moves + 1<<std::endl;
        return 1;
    }
    if (var.closed.find(var.children[index]->getStringedState()) == var.closed.end()
        && var.opened.find(var.children[index]->getStringedState()) == var.opened.end()) {
        setChildValues(var.e, index, 1);
        var.pq.push((var.children[index]));
        var.opened.insert({var.children[index]->getStringedState(), (var.children[index])});
    }
    else {
        delete var.children[index];
        var.e->setChildren(NULL, index);
    }
    return 0;
}

void    astar(TreeNode &root)
{
    t_astar var;

    var.children = NULL;
    var.success = false;
    var.success2 = false;
    normalized2(*root.getState());
    TreeNode end(all.finalsnail);
    end.StateToStr();

    setNodeValues(end);
    end.setParent(NULL);
    root.StateToStr();
    var.pq_end.push(&end);
    var.opened_end.insert({end.getStringedState(), &end});
    while (!var.success2)
    {
        var.e = var.pq_end.top();
        var.e->StateToStr();
        if (var.e->getDepth() > 11 || var.e->getStringedState() == root.getStringedState()) {
            var.success2 = true;
        }
        else {
            var.pq_end.pop();
            var.e->setChildren(var.e->up(), 0);
            var.e->setChildren(var.e->down(), 1);
            var.e->setChildren(var.e->right(), 2);
            var.e->setChildren(var.e->left(), 3);
            var.closed_end.insert({var.e->getStringedState(), var.e});

            var.children = (TreeNode **) var.e->getChildren();
            if (var.children[0] != NULL) {
                astar3(var, 0);
            }
            if (var.children[1] != NULL) {
                astar3(var, 1);
            }
            if (var.children[2] != NULL){
                astar3(var, 2);
            }
            if (var.children[3] != NULL) {
                astar3(var, 3);
            }
        }
    }
    setNodeValues(root);
    var.pq.push(&root);
    var.opened.insert({root.getStringedState(), (&root)});
    while (!var.success && !var.pq.empty())
    {
        var.e = var.pq.top();

        var.e->StateToStr();
        if (var.e->getStringedState() == end.getStringedState()) {
            var.e->printree();
            std::cout<<"complexity_time / "<<all.complexity_time<<std::endl;
            std::cout<<"complexity_size / "<<var.closed.size() + var.closed_end.size()<<std::endl;
            std::cout<<all.nb_moves<<"nb_moves"<<std::endl;
            var.success = true;
            continue;
        }
        else {
            var.pq.pop();
            var.closed.insert({var.e->getStringedState(), var.e});
            var.e->setChildren(var.e->up(), 0);
            var.e->setChildren(var.e->down(), 1);
            var.e->setChildren(var.e->right(), 2);
            var.e->setChildren(var.e->left(), 3);

            var.children = (TreeNode **) var.e->getChildren();
            if (var.children[0] != NULL) {
                if (astar2(var, 0))
                    continue ;
            }
            if (var.children[1] != NULL) {
                if (astar2(var, 1))
                    continue ;
            }
            if (var.children[2] != NULL){
                if (astar2(var, 2))
                    continue ;
            }
            if (var.children[3] != NULL) {
                if (astar2(var, 3))
                    continue ;
            }
        }
    }
    if (var.pq.empty() && !var.success)
        std::cout<<"Solution not found!"<<std::endl;
}


