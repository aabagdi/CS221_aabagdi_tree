#define CATCH_CONFIG_MAIN

#include "tree.hh"
#include "tree++.hh"
#include "catch_amalgamated.hpp"
#include <iostream>

tree_ptr_t tree1() {                                             // this is the example tree given in tree.hh
    tree_ptr_t root = create_tree(126, 126);                                  
    tree_ptr_t L = create_tree(-5, -5);
    tree_ptr_t LL = create_tree(12, 12);
    tree_ptr_t LR = create_tree(6, 6);
    tree_ptr_t LRL = create_tree(9, 9);
    tree_ptr_t R = create_tree(12, 12);
    tree_ptr_t RL = create_tree(3,3);

    LR->left_ = LRL;

    L->left_ = LL;
    L->right_ = LR;

    R->left_ = RL;

    root->left_ = L;
    root->right_= R;   

    return root;

}                                                           

tree_ptr_t tree2() {                                             // this is an unbalanced tree with one of the duplicate elements in the root node
    tree_ptr_t root = create_tree(2, 2);
    tree_ptr_t L = create_tree(7, 7);
    tree_ptr_t R = create_tree(2, 2);
    tree_ptr_t LL = create_tree(1, 1);
    tree_ptr_t LR = create_tree(15, 15);
    tree_ptr_t RL = create_tree(1, 1);
    tree_ptr_t RR = create_tree(12, 12);
    tree_ptr_t RRR = create_tree(9, 9);

    L->left_ = LL;
    L->right_ = LR;

    RR->right_ = RRR;

    R->left_ = RL;
    R->right_ = RR;

    root->left_ = L;
    root->right_ = R;   

    return root;                               
}                                                         

tree_ptr_t tree3() {                                             // this is a linked list where every key except the last is 1
    tree_ptr_t LLLL = create_tree(5, 1);
    tree_ptr_t LLL = create_tree(1, 1, LLLL);
    tree_ptr_t LL = create_tree(1, 1, LLL);
    tree_ptr_t L = create_tree(1, 1, LL);
    tree_ptr_t root = create_tree(1, 1, L);

    return root;                                                  
}

tree_ptr_t tree4() {                                             // this is a full and balanced binary search tree
    tree_ptr_t RR = create_tree(120, 120);
    tree_ptr_t RL = create_tree(95, 95);
    tree_ptr_t R = create_tree(100, 100, RL, RR);

    tree_ptr_t LL = create_tree(60, 60);
    tree_ptr_t LR = create_tree(85, 85);
    tree_ptr_t L = create_tree(80, 80, LL, LR);

    tree_ptr_t root = create_tree(90, 90, L, R);
    
    return root;
}

tree_ptr_t tree5() {
    tree_ptr_t root = create_tree(666, 666);                     // this is just a single node containing the key 666

    return root;
}


TEST_CASE("path_to test") {                                      // this is a test case for the path_to function in Catch2. It makes the five trees, tests whether path_to
    tree_ptr_t t1 = tree1();                                     // returns the proper values given the inputs in each tree, and then deletes the five trees off the heap
    tree_ptr_t t2 = tree2();                                     
    tree_ptr_t t3 = tree3();
    tree_ptr_t t4 = tree4();
    tree_ptr_t t5 = tree5();

    REQUIRE(path_to(t1, 12) == "LL");
    REQUIRE(path_to(t1, 10) == "-");
    REQUIRE(path_to(t1, 126) == "");  

    REQUIRE(path_to(t2, 2) == "");
    REQUIRE(path_to(t2, 13) == "-");
    REQUIRE(path_to(t2, 12) == "RR");

    REQUIRE(path_to(t3, 2) == "-");
    REQUIRE(path_to(t3, 1) == "");
    REQUIRE(path_to(t3, 5) == "LLLL");

    REQUIRE(path_to(t4, 85) == "LR");
    REQUIRE(path_to(t4, 90) == "");
    REQUIRE(path_to(t4, 1337) == "-");

    REQUIRE(path_to(t5, 666) == "");
    REQUIRE(path_to(t4, 123) == "-");

    destroy_tree(t1);
    destroy_tree(t2);
    destroy_tree(t3);
    destroy_tree(t4);
    destroy_tree(t5);
}

TEST_CASE("node_at test") {                                     // this is a test case for the path_to function in Catch2. It makes the five trees, tests whether node_at
    tree_ptr_t t1 = tree1();                                    // returns the proper values given the inputs in each tree, and then deletes the five trees off the heap
    tree_ptr_t t2 = tree2();                                    
    tree_ptr_t t3 = tree3();
    tree_ptr_t t4 = tree4();
    tree_ptr_t t5 = tree5();

    REQUIRE(node_at(t1, "LRL")->key_ == 9);
    REQUIRE(node_at(t1, "LLLL") == nullptr);
    REQUIRE(node_at(t1, "")->key_ == 126);

    REQUIRE(node_at(t2, "RRL") == nullptr);
    REQUIRE(node_at(t2, "LR")->key_ == 15);
    REQUIRE(node_at(t2, "")->key_ == 2);

    REQUIRE(node_at(t3, "LLLL")->key_ == 5);
    REQUIRE(node_at(t3, "")->key_ == 1);
    REQUIRE(node_at(t3, "R") == nullptr);

    REQUIRE(node_at(t4, "RL")->key_ == 95);
    REQUIRE(node_at(t4, "")->key_ == 90);
    REQUIRE(node_at(t4, "LLR") == nullptr);

    REQUIRE(node_at(t5, "")->key_ == 666);
    REQUIRE(node_at(t5, "L") == nullptr);
    REQUIRE(node_at(t5, "R") == nullptr);


    destroy_tree(t1);
    destroy_tree(t2);
    destroy_tree(t3);
    destroy_tree(t4);
    destroy_tree(t5);
}