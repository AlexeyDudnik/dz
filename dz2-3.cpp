#include <iostream>
#include <initializer_list>
using namespace std;
struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Node(int value) : data(value), left(nullptr), right(nullptr), parent(nullptr) {}
};
class BSTree {
private:
    Node* root;
    Node* find(int value, Node* node);
    Node* findMin(Node* node);
    Node* remove(int value, Node* node);
    void clear(Node* node);
    void print(Node* node);
public:
    BSTree() : root(nullptr) {}
    BSTree(initializer_list<int> list);
    ~BSTree();
    bool add_element(int value);
    bool delete_element(int value);
    bool find_element(int value);
    void print();
};
BSTree::BSTree(initializer_list<int> list) {
    for (int value : list) {
        add_element(value);
    }
}
BSTree::~BSTree() {
    clear(root);
}
bool BSTree::add_element(int value) {
    if (root == nullptr) {
        root = new Node(value);
        return true;
    }
    Node* current = root;
    while (true) {
        if (value < current->data) {
            if (current->left == nullptr) {
                current->left = new Node(value);
                current->left->parent = current;
                return true;
            }
            current = current->left;
        }
        else if (value > current->data) {
            if (current->right == nullptr) {
                current->right = new Node(value);
                current->right->parent = current;
                return true;
            }
            current = current->right;
        }
        else {
            return false;
        }
    }
}
bool BSTree::delete_element(int value) {
    root = remove(value, root);
    return root != nullptr;
}
bool BSTree::find_element(int value) {
    return find(value, root) != nullptr;
}
void BSTree::print() {
    print(root);
    cout << endl;
}
Node* BSTree::find(int value, Node* node) {
    if (node == nullptr || node->data == value) {
        return node;
    }
    if (value < node->data) {
        return find(value, node->left);
    }
    else {
        return find(value, node->right);
    }
}
Node* BSTree::findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
Node* BSTree::remove(int value, Node* node) {
    if (node == nullptr) return nullptr;
    if (value < node->data) {
        node->left = remove(value, node->left);
    }
    else if (value > node->data) {
        node->right = remove(value, node->right);
    }
    else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->right = remove(temp->data, node->right);
    }
    return node;
}
void BSTree::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}
void BSTree::print(Node* node) {
    if (node != nullptr) {
        print(node->left);
        cout << node->data << " ";
        print(node->right);
    }
}
int main() {
    BSTree tree = { 10, 5, 15, 3, 7, 12, 17 };
    tree.print();
    int searchValue = 7;
    if (tree.find_element(searchValue)) {
        cout << searchValue << " found" << endl;
    }
    else {
        cout << searchValue << " not found" << endl;
    }
    int deleteValue = 15;
    if (tree.delete_element(deleteValue)) {
        cout << deleteValue << " deleted" << endl;
    }
    else {
        cout << deleteValue << " not found" << endl;
    }
    tree.print();
    return 0;
}
