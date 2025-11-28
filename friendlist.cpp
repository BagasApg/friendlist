#include <iostream>
#include <sstream>

struct Node
{
    int id, level;
    std::string username, rank;

    int height;
    Node *left;
    Node *right;
};

Node *createNewNode(int id, int level, std::string name, std::string rank)
{
    Node *newNode = new Node();

    newNode->id = id;
    newNode->level = level;
    newNode->username = name;
    newNode->rank = rank;
    newNode->height = 1;

    newNode->left = newNode->right = nullptr;
    return newNode;
}

int height(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

Node *findMin(Node *node) {
    if (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

int max(int left, int right)
{
    if (left > right)
    {
        return left;
    }
    return right;
}

Node *leftRotate(Node *node)
{
    Node *y = node->right;
    Node *t2 = y->left;

    y->left = node;
    node->right = t2;

    node->height = 1 + max(height(node->left), height(node->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

Node *rightRotate(Node *node)
{
    Node *y = node->left;
    Node *t2 = y->right;

    y->right = node;
    node->left = t2;

    node->height = 1 + max(height(node->left), height(node->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

Node *reBalance(Node *root,int id) {
    root->height = 1 + max(height(root->left), height(root->right));

    int bf = height(root->left) - height(root->right);
    std::cout << bf << std::endl;
    std::cout << root->height << "-" << root->username << std::endl;

    if (bf < -1 )
    {
        if (id < root->right->id) {
            root->right = rightRotate(root->right);
        }
        return leftRotate(root);
    }
    else if (bf > 1 )
    {
        if (id > root->right->id) {
            root->left = leftRotate(root->left);
        }
        return rightRotate(root);
    }

    return root;
}

Node *insertNode(Node *root, int id, int level, std::string username, std::string rank)
{
    if (root == nullptr)
    {
        root = createNewNode(id, level, username, rank);
    }

    else if (id < root->id)
    {
        root->left = insertNode(root->left, id, level, username, rank);
    }
    else
    {
        root->right = insertNode(root->right, id, level, username, rank);
    }
    return reBalance(root, id);
}

Node *deleteNode(Node *root, int id) {
    if (root == nullptr) {
        return nullptr;
    } else if (id < root->id) {
        root->left = deleteNode(root->left, id);
    } else if (id > root->id) {
        root->right = deleteNode(root->right, id);
    } else {
        if (root->left == nullptr) {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == nullptr) {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        Node *temp = findMin(root->right);
        root->id = temp->id;
        root->right = deleteNode(root->right, temp->id);
    }
    return reBalance(root, id);
}

std::string rank(std::string r)
{
    std::string res = "";
    std::string buffer;

    std::istringstream ss(r);

    std::getline(ss, buffer, '-');
    if (buffer == "0")
    {
        res += "Warrior";
    }
    else if (buffer == "1")
    {
        res += "Elite";
    }
    else if (buffer == "2")
    {
        res += "Master";
    }
    else if (buffer == "3")
    {
        res += "Grandmaster";
    }
    else if (buffer == "4")
    {
        res += "Epic";
    }
    else if (buffer == "5")
    {
        res += "Legend";
    }
    else if (buffer == "6")
    {
        res += "Mythic";
    }
    else if (buffer == "7")
    {
        res += "Mythical Honor";
    }
    else if (buffer == "8")
    {
        res += "Mythical Glory";
    }
    else
    {
        res += "Mythical Immortal";
    }

    std::getline(ss, buffer, '-');

    return res + " " + buffer;
}

void show(Node *root, int step = 0)
{
    if (root == nullptr)
    {
        if (step == 0)
        {
            std::cout << "You have no friend :(";
        }
        return;
    }

    show(root->left, ++step);

    std::cout << height(root->left) - height(root->right) << " = ";
    std::cout << root->height << "\t";
    std::cout << root->id << "\t";
    std::cout << root->level << "\t";
    std::cout << root->username << "\t\t";
    std::cout << rank(root->rank) << "\n";

    show(root->right, step++);
}

main()
{

    Node *root = nullptr;

    root = insertNode(root, 3, 33, "Vretz", "5-1");
    root = insertNode(root, 8, 33, "Bunnyhop", "5-1");
    root = insertNode(root, 5, 33, "Bunnyhop senpai", "5-1");
    root = insertNode(root, 10, 33, "suichan", "5-1");
    root = insertNode(root, 1, 33, "newbie", "5-1");
    show(root);
    std::cout << std::endl;
    deleteNode(root, 8);
    show(root);

    std::cout << "Done!";

    return 0;
}