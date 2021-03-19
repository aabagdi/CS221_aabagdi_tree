#include "tree.hh"
#include "tree++.hh"
#include <iostream>

// definition of helper functions in tree++.hh

bool in_tree(tree_ptr_t tree, key_t key) {                                  // returns true or false if given key is in tree, used by path_to
    if (!tree) {    
        return false;                                                       // if there is no tree (nullptr) return false
    }
    else if (tree->key_ == key) {
        return true;                                                        // if the given key is the current node, return true
    }
    else if (in_tree(tree->left_, key) || in_tree(tree->right_, key)) {
        return true;                                                        // call recursively on left and right child, if key is in either subtree, then return true
    }
    return false;                                                           // if all else fails, return false
}
