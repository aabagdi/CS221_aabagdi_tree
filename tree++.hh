#pragma once

#include "tree.hh"

// extension of tree.hh to include helper functions

bool in_tree(tree_ptr_t tree, key_t key);           // returns true or false if given key is in tree, used by path_to
