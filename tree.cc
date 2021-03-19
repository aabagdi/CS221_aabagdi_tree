#include "tree.hh"
#include "tree++.hh"
#include <string>

tree_ptr_t create_tree(const key_t& key, const value_t& value, tree_ptr_t left, tree_ptr_t right) {

    tree_ptr_t node = new Tree;                                                                             // initialise pointer to tree node

    node->key_ = key;                                                                                       // set node's key to given key
    node->value_ = value;                                                                                   // set node's value to given value
    node->left_= left;                                                                                      // set node's left child to given, default nullptr
    node->right_= right;                                                                                    // set node's right child to given, default nullptr

    return node;                                                                                            // return pointer
}

void destroy_tree(tree_ptr_t tree) {
    if (tree == nullptr) {
        return;                                                                                             // if there is no tree (nullptr), exit function (base case)
    } 
    destroy_tree(tree->left_);                                                                              // recursively delete left subtree
    destroy_tree(tree->right_);                                                                             // recursively delete right subtree
    delete tree;                                                                                            // delete root node
}

std::string path_to(tree_ptr_t tree, key_t key) {
    if (!in_tree(tree, key)) {
        return "-";                                                                                         // if key is not in tree, return "-"
    }
    std::string path = "";                                                                                  // initialise path string
    if (in_tree(tree, key)) {                                                                               // only go through if key is in the tree
        if(tree->key_ == key) {                                                                             
            return path;                                                                                    // if key is in root node, return ""
        }
        if (in_tree(tree->left_, key)) {
            path = "L" + path_to(tree->left_, key);                                                         // if key is in left child add "L" to path and recursively check next left child
        }
        else if (in_tree(tree->right_, key)) {
            path = "R" + path_to(tree->right_, key);                                                        // if key is in right child add "R" to path and recursively check next right child
        }
        return path;                                                                                        // return final path
    }
    return "-";                                                                                             // if all else fails, return "-"
}   

tree_ptr_t node_at(tree_ptr_t tree, std::string path) {
    for(unsigned int i = 0; i < path.length(); i++) {
        if(path[i] != 'L' && path[i] != 'R') {
            return nullptr;                                                                                 // scan string for non-L,R chars, if found return nullptr
        }
    }
    unsigned int path_index = 0;                                                                            // initialise path index

    tree_ptr_t current = tree;                                                                              // initialise tree traversal node

    while (current != nullptr) {                                                                            // loop continuously unless a nullptr (empty subtree) is reached
        if (path_index == path.length()) {                                                                
            return current;                                                                                 // if end of path is reached, return current node
        }
        if (path_index > path.length()) {
            return nullptr;                                                                                 // if path_index somehow exceeds length of path, return nullptr
        }
        if (path[path_index] == 'L') {
            current = current->left_;
            path_index++;                                                                                   // if char at index in path reads 'L', move left and increment index
        }
        if (path[path_index] == 'R') {
            current = current->right_;
            path_index++;                                                                                   // if char at index in path reads 'R', move right and increment index
        }  
    }
    return nullptr;                                                                                         // if all else fails, return nullptr
}