#include "ARN.h"
#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>

ARN::ARN() : root(nullptr) {}

Node* ARN::getRoot() {
    return root;
}

void ARN::fixinsertion(Node*& root, Node* newNode) {
    while (newNode->parent != nullptr && newNode->parent->color == Color::RED) {
        Node* grandparent = newNode->parent->parent;
        if (grandparent != nullptr && newNode->parent == grandparent->left) {
            Node* uncle = grandparent->right;
            if (uncle != nullptr && uncle->color == Color::RED) {
                newNode->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                newNode = grandparent;
            }
            else {
                if (newNode == newNode->parent->right) {
                    newNode = newNode->parent;
                    rotateLeft(root, newNode);
                }

                newNode->parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateRight(root, grandparent);
            }
        }
        else {
            Node* uncle = grandparent->left;
            if (uncle != nullptr && uncle->color == Color::RED) {
                newNode->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                newNode = grandparent;
            }
            else {
                if (newNode == newNode->parent->left) {
                    newNode = newNode->parent;
                    rotateRight(root, newNode);
                }
                newNode->parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateLeft(root, grandparent);
            }
        }
    }

    root->color = Color::BLACK;  
}

void ARN::rotateLeft(Node*& root, Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = rightChild;
    }
    else if (node == node->parent->left) {
        node->parent->left = rightChild;
    }
    else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

void ARN::rotateRight(Node*& root, Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = leftChild;
    }
    else if (node == node->parent->left) {
        node->parent->left = leftChild;
    }
    else {
        node->parent->right = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

Node* ARN::insertNode(Node* root, int key) {
    Node* newNode = new Node(key);
    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        }
        else if (key > current->key) {
            current = current->right;
        }
        else {
            delete newNode;
            return root;
        }
    }

    newNode->parent = parent;
    if (parent == nullptr) {
        newNode->color = Color::BLACK;
        return newNode;
    }
    else if (key < parent->key) 
        parent->left = newNode;
    
    else 
        parent->right = newNode;
    
    fixinsertion(root, newNode);
    return root;
}


void ARN::insert(int key) {
    root = insertNode(root, key);
}
void ARN::construct(std::vector<int> constrVect)
{
    for (int i = 0; i < constrVect.size(); i++)
        insert(constrVect[i]);
}
Node* ARN::findNode(Node* node, int key) {
    if (node == nullptr || node->key == key) {
        return node;
    }

    if (key < node->key) {
        return findNode(node->left, key);
    }
    else {
        return findNode(node->right, key);
    }
}

Node* ARN::find(int key) {
    return findNode(root, key);
}

Node* ARN::minimum(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}

void ARN::erase(Node* x) {
    if (x == nullptr)
        return;

    erase(x->left);
    erase(x->right);
    delete x;
}

void ARN::clear() {
    erase(root);
    root = nullptr;
}

bool ARN::empty() {
    return root == nullptr;
}

void ARN::preorder(Node* node) {
    if (node == nullptr) {
        return;
    }

    std::cout << node->key << " ";
    if (node->color == Color::RED)
        std::cout << "(RED) ";
    else std::cout << "(BLACK) ";
    preorder(node->left);
    preorder(node->right);
}

void ARN::inorder(Node* node) {
    if (node == nullptr) {
        return;
    }

    inorder(node->left);
    std::cout << node->key << " ";
    if (node->color == Color::RED)
        std::cout << "(RED) ";
    else std::cout << "(BLACK) ";
    inorder(node->right);
}

void ARN::postorder(Node* node) {
    if (node == nullptr) {
        return;
    }

    postorder(node->left);
    postorder(node->right);
    std::cout << node->key << " ";
    if (node->color == Color::RED)
        std::cout << "(RED) ";
    else std::cout << "(BLACK) ";
}

void ARN::niveluri() {
    if (root == nullptr) {
        return;
    }

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        std::cout << current->key << " ";
        if (current->color == Color::RED)
            std::cout << "(RED) ";
        else std::cout << "(BLACK) ";

        if (current->left != nullptr) {
            q.push(current->left);
        }

        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}

void ARN::printTree(int option) {
    switch (option) {
    case 1:
        preorder(root);
        break;
    case 2:
        inorder(root);
        break;
    case 3:
        postorder(root);
        break;
    case 4:
        niveluri();
        break;
    default:
        std::cout << "Invalid option\n";
        break;
    }

    std::cout << std::endl;
}
Node* ARN::findSuccessor(Node* node) {
    Node* current = node->right;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

void ARN::del(int key) {

    root = deleteNode(root, key);
}

Node* ARN::deleteNode(Node* root, int key) {
    Node* node = find(key);
    if (node == nullptr) {
        return root;
    }

    Node* replacement = nullptr;
    if (node->left == nullptr || node->right == nullptr) {
        replacement = node;
    }
    else {
        Node* successor = findSuccessor(node);
        replacement = successor;
    }

    Node* child = (replacement->left != nullptr) ? replacement->left : replacement->right;


    if (child != nullptr) {
        child->parent = replacement->parent;
    }

    if (replacement->parent == nullptr) {
        root = child;
    }
    else if (replacement == replacement->parent->left) {
        replacement->parent->left = child;
    }
    else {
        replacement->parent->right = child;
    }

    if (replacement != node) {
        node->key = replacement->key;
    }

    if (replacement->color == Color::BLACK) {
        fixDeletion(root, child, replacement->parent);
    }

    delete replacement;
    return root;
}

void ARN::fixDeletion(Node*& root, Node* node, Node* parent) {
    while (node != root && (node == nullptr || node->color == Color::BLACK)) {
        if (node == parent->left) {
            Node* sibling = parent->right;
            if (sibling->color == Color::RED) {
                sibling->color = Color::BLACK;
                parent->color = Color::RED;
                rotateLeft(root, parent);
                sibling = parent->right;
            }
            if ((sibling->left == nullptr || sibling->left->color == Color::BLACK) &&
                (sibling->right == nullptr || sibling->right->color == Color::BLACK)) {
                sibling->color = Color::RED;
                node = parent;
                parent = node->parent;
            }
            else {
                if (sibling->right == nullptr || sibling->right->color == Color::BLACK) {
                    sibling->left->color = Color::BLACK;
                    sibling->color = Color::RED;
                    rotateRight(root, sibling);
                    sibling = parent->right;
                }
                sibling->color = parent->color;
                parent->color = Color::BLACK;
                sibling->right->color = Color::BLACK;
                rotateLeft(root, parent);
                node = root;
                break;
            }
        }
        else {
            Node* sibling = parent->left;
            if (sibling->color == Color::RED) {
                sibling->color = Color::BLACK;
                parent->color = Color::RED;
                rotateRight(root, parent);
                sibling = parent->left;
            }
            if ((sibling->left == nullptr || sibling->left->color == Color::BLACK) &&
                (sibling->right == nullptr || sibling->right->color == Color::BLACK)) {
                sibling->color = Color::RED;
                node = parent;
                parent = node->parent;
            }
            else {
                if (sibling->left == nullptr || sibling->left->color == Color::BLACK) {
                    sibling->right->color = Color::BLACK;
                    sibling->color = Color::RED;
                    rotateLeft(root, sibling);
                    sibling = parent->left;
                }
                sibling->color = parent->color;
                parent->color = Color::BLACK;
                sibling->left->color = Color::BLACK;
                rotateRight(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node != nullptr) {
        node->color = Color::BLACK;
    }
}