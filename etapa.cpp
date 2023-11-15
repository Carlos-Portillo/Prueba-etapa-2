#include <iostream>

using namespace std;

struct TreeNode {
    const char* symbol;
    double probability;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(const char* s, double prob)
        : parent(nullptr), left(nullptr), right(nullptr), symbol(s), probability(prob) {}
};

class BST {

private:
    TreeNode* root;
    TreeNode* lastNode;
    TreeNode* getParentForInsertion();
    void swapNodes(TreeNode* a, TreeNode* b);
    void heapifyUp(TreeNode* node);
    void heapifyDown(TreeNode* node);
    TreeNode* getMinChild(TreeNode* node);
    void printTree(TreeNode* node);
    

public:
    void insert(TreeNode* node);
    TreeNode* extractMin();
    void printHeap();
    void printAllNodes();
    BST() : root(nullptr), lastNode(nullptr) {}
    
};



void BST::insert(TreeNode* node) {
    if (!root) {
        root = node;
        lastNode = node;
    } else {
        TreeNode* currentNode = lastNode;
        while (currentNode->parent && node->probability < currentNode->probability) {
            currentNode = currentNode->parent;
        }

        if (!currentNode->parent) {
            // El nuevo nodo será la nueva raíz
            node->left = currentNode;
            currentNode->parent = node;
            root = node;
        } else if (!currentNode->parent->right) {
            // Si el nodo actual no tiene un hijo derecho, el nuevo nodo se convierte en el hijo derecho
            currentNode->parent->right = node;
            node->parent = currentNode->parent;
        } else {
            // Si el nodo actual tiene un hijo derecho, el nuevo nodo se convierte en el hijo izquierdo del
            // nodo más a la izquierda en el nivel siguiente
            currentNode = currentNode->parent->right;
            while (currentNode->left) {
                currentNode = currentNode->left;
            }
            currentNode->left = node;
            node->parent = currentNode;
        }

        lastNode = node;

        // Restaurar el montículo después de la inserción
        heapifyUp(node);
    }

    // Imprimir el nodo recién insertado
    std::cout << "Inserted: Symbol - " << node->symbol << ", Probability - " << node->probability << std::endl;
}

TreeNode* BST::extractMin() {
        if (!root) {
            return nullptr;
        }

        TreeNode* minNode = root;

        if (root == lastNode) {
            root = nullptr;
            lastNode = nullptr;
        } else {
            swapNodes(root, lastNode);

            TreeNode* parent = lastNode->parent;
            if (parent->left == lastNode) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }

            lastNode = parent;

            // Restaurar el montículo después de la extracción
            heapifyDown(root);
        }

        return minNode;
    }

void BST::printHeap()  {
    printTree(root);
}

void BST::printAllNodes()  {
    cout << "All nodes in the tree:\n";
    printTree(root);
}

TreeNode* BST::getParentForInsertion() {
        TreeNode* temp = lastNode;
        while (temp->parent && temp->parent->right == temp) {
            temp = temp->parent;
        }
        if (temp->parent) {
            temp = temp->parent->right;
        }
        while (temp->left) {
            temp = temp->left;
        }
        return temp;
    }

void BST::swapNodes(TreeNode* a, TreeNode* b) {
    std::swap(a->parent, b->parent);
    std::swap(a->left, b->left);
    std::swap(a->right, b->right);

    if (a->parent) {
        if (a->parent->left == b) {
            a->parent->left = a;
        } else {
            a->parent->right = a;
        }
     

        if (b->parent) {
            if (b->parent->left == a) {
                b->parent->left = b;
            }   else {
                b->parent->right = b;
            }
        }
    }
}

void BST::heapifyUp(TreeNode* node) {
        while (node->parent && node->probability < node->parent->probability) {
            swapNodes(node, node->parent);
            node = node->parent;
        }
    }

    void BST::heapifyDown(TreeNode* node) {
        while (true) {
            TreeNode* minChild = getMinChild(node);
            if (!minChild || node->probability <= minChild->probability) {
                break;
            }
            swapNodes(node, minChild);
            node = minChild;
        }
    }

    TreeNode* BST::getMinChild(TreeNode* node)  {
        if (!node->left && !node->right) {
            return nullptr;
        }
        if (!node->left) {
            return node->right;
        }
        if (!node->right) {
            return node->left;
        }
        return (node->left->probability < node->right->probability) ? node->left : node->right;
    }

    void BST::printTree(TreeNode* node)  {
        if (node) {
            printTree(node->left);
            std::cout << "Symbol: " << node->symbol << ", Probability: " << node->probability << std::endl;
            printTree(node->right);
        }
    }

int main() {
    double probabilities[] = {
        0.29, 0.18, 0.50, 0.37, 0.72, 0.51,
        0.23, 0.40, 0.71, 0.66, 0.12, 0.55,
        0.67, 0.37, 0.20, 0.09, 0.35, 0.31,
        0.77, 0.94, 0.19, 0.66, 0.81, 0.34,
        0.22, 0.56, 0.04, 0.38, 0.07, 0.85
    };

    BST minHeap;
    /*for (int i = 0; i < 28; ++i) {
        TreeNode* node = new TreeNode("ﺝ", probabilities[i]);
        minHeap.insert(node);
    }*/
        
        TreeNode* newNode1 = new TreeNode("ﻱ", 0.75);
        TreeNode* newNode2 = new TreeNode("ﺕ", 0.15);
        minHeap.insert(newNode1);
        minHeap.insert(newNode2);
        //minHeap.printAllNodes();

    

    std::cout << "\nExtracted nodes in ascending order of probability:\n";
    while (TreeNode* minNode = minHeap.extractMin()) {
        std::cout << "Symbol: " << minNode->symbol << ", Probability: " << minNode->probability << std::endl;
        delete minNode;
    }

    return 0;
}
