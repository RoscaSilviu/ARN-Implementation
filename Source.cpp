#include <iostream>
#include "ARN.h"

int main() {
    ARN arnTree;
    int option;

    do {
        std::cout << "-------------------------------------\n";
        std::cout << "Menu:\n";
        std::cout << "1. Insert\n";
        std::cout << "2. Construct\n";
        std::cout << "3. Search\n";
        std::cout << "4. Delete\n";
        std::cout << "5. Minimum\n";
        std::cout << "6. Maximum\n";
        std::cout << "7. Print Tree (Preorder)\n";
        std::cout << "8. Print Tree (Inorder)\n";
        std::cout << "9. Print Tree (Postorder)\n";
        std::cout << "10. Print Tree (Level Order)\n";
        std::cout << "11. Clear\n";
        std::cout << "0. Exit\n";
        std::cout << "-------------------------------------\n";
        std::cout << "Enter your choice: ";
        std::cin >> option;

        switch (option) {
        case 1: {
            int key;
            std::cout << "Enter the key to insert: ";
            std::cin >> key;
            arnTree.insert(key);
            break;
        }
        case 2: {
            std::vector<int> constructVect;
            int n;
            std::cout << "Enter the number of elements to construct: ";
            std::cin >> n;
            std::cout << "Enter the elements: ";
            for (int i = 0; i < n; i++) {
                int key;
                std::cin >> key;
                constructVect.push_back(key);
            }
            arnTree.construct(constructVect);
            std::cout << "Tree constructed successfully.\n";
            break;
        }
        case 3: {
            int key;
            std::cout << "Enter the key to search: ";
            std::cin >> key;
            Node* result = arnTree.find(key);
            if (result != nullptr) {
                std::cout << "Key found in the tree.\n";
            }
            else {
                std::cout << "Key not found in the tree.\n";
            }
            break;
        }
        case 4: {
            int key;
            std::cout << "Enter the key to delete: ";
            std::cin >> key;
            arnTree.del(key);
            std::cout << "Key deleted successfully.\n";
            break;
        }
       case 5: {
            Node* minNode = arnTree.minimum(arnTree.getRoot());
            if (minNode != nullptr) {
                std::cout << "Minimum key in the tree: " << minNode->key << "\n";
            }
            else {
                std::cout << "The tree is empty.\n";
            }
            break;
        }
        case 7: {
            std::cout << "Preorder traversal: ";
            arnTree.printTree(1);
            break;
        }
        case 8: {
            std::cout << "Inorder traversal: ";
            arnTree.printTree(2);
            break;
        }
        case 9: {
            std::cout << "Postorder traversal: ";
            arnTree.printTree(3);
            break;
        }
        case 10: {
            std::cout << "Level order traversal: ";
            arnTree.printTree(4);
            break;
        }
        case 11: {
            arnTree.clear();
            std::cout << "Tree cleared successfully.\n";
            break;
        }
        case 0: {
            std::cout << "Exiting...\n";
            break;
        }
        default: {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
        } while (option != 0);

    }