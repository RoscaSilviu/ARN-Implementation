#pragma once
#include <iostream>
#include <vector>
#include <queue>

enum class Color {
    RED,
    BLACK
};

struct Node {
    int key;
    Color color;
    Node* parent;
    Node* left;
    Node* right;
    Node(int key) : key(key), color(Color::RED), parent(nullptr), left(nullptr), right(nullptr) {}
};

class ARN {
private:
    Node* root;

    Node* balanceInsertion(Node* node);
    void rotateRight(Node * &root, Node * node);
    void rotateLeft(Node*& root, Node* node);
    Node* findNode(Node* node, int key);
    void fixDeletion(Node*& root, Node* node, Node* parent);
    void erase(Node* x);
    void preorder(Node* root);
    void inorder(Node* root);
    void niveluri();
    void postorder(Node* root);
    Node* findSuccessor(Node* node);
    Node* insertNode(Node* node, int key);
    void fixinsertion(Node*& root, Node* newNode);
    Node* deleteNode(Node* root, int key);

public:
    ARN();
    Node* getRoot();
    Node* minimum(Node* node);
    void del(int key);
    void insert(int key);
    Node* find(int key);
    void construct(std::vector<int> constrVect);
    void clear();
    void printTree(int opt);
    bool empty();
};