To test my program with Catch2:
g++ -g -Wall -Wextra -pedantic -Werror -std=c++17 -o main tree.cc test_tree.cc tree++.cc catch_amalgamated.cpp

I had to link together all the cc (and one cpp) files together in order to generate a valid program.

To run it:
./main

To run under valgrind:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./main

create_tree:
All that needs to be done here is to create a new tree_ptr_t, assign the given parameters to it, then return it.

destroy_tree:
I figured since we do not know how deep the tree will be or how many elements it will have, it would be better to do this recursively than iteratively. It deletes the root node, then recursively deletes each node in the left and right subtrees. Running it under valgrind seems to show that it works properly, with no leaks being detected.

in_tree:
This is a helper function that I made to offload some of the work path_to does. Like destroy_tree, I decided to make it recursive as the height of the tree is not concrete. All it does is return true or false if a node with the given key is present in the tree. It checks the root first, then recursively checks the elements in the left and right subtrees, and returns true or false based on that. If all else fails and everything goes pear-shaped somehow, return false. For some reason if I implemented it in tree.cc, I would get "not declared in scope" errors. Since we are not allowed to modify tree.hh to add this function, I elected to create a seperate header for all helper functions (with this being the only one.)

path_to:
I decided that like destroy_tree, this would be recursive as the height of the tree is not known by the function. First, using in_tree, it checks if the key is in the tree in the first place. If not, return "-". Otherwise, initialise an empty string path. Next, if the key is in the root node, return the empty string. Then, check if the key is in the left child, and if so, add "L" to the empty string and recursively check the next left child. Do this same procedure for the right child, and then return the final string. If all goes wrong somehow, return "-".

node_to:
Since the length of the input string is constant and known, I decided to implement this function iteratively. First it checks if the string contains any characters that are not 'L' or 'R', if so return nullptr. Then it initialise a string index and iterates through the string looking for 'L' or 'R', and moves down the tree accordingly and increments the string index. If the end of the string is reached, return the current node it's looking at. If all fails, return nullptr.

test_tree:
I used Catch2 to test my code, and it passed all the tests I threw at it, which included the example tree in tree.hh, an unbalanced tree with a duplicate of the root node, a linked list, a full and balanced BST and finally a single node. create_tree made the nodes and linked them together as expected. I tested path_to with parameters like the root node, an existing node, a nonexistent node, and if applicable, duplicate nodes. I tested node_at with parameters like an empty string, an invalid path, and a valid path. Running the test file under valgrind reports no leaks, so destroy_tree is working fine too.