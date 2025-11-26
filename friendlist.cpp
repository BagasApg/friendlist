#include <iostream>
// #include <sstream>

struct Node
{
    int id, level, height;
    std::string name, rank;

    Node *left;
    Node *right;
};

Node *createNewNode(int id, int level, std::string name, std::string rank)
{
    Node *newNode = new Node();

    newNode->id = id;
    newNode->level = level;
    newNode->name = name;
    newNode->rank = rank;
    newNode->height = 1;

    newNode->left = newNode->right = nullptr;
    return newNode;
}

Node *findMin(Node *root)
{
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}

int max(int left, int right)
{
    if (left > right)
    {
        return left;
    }
    else
    {
        return right;
    }
}

int height(Node *root)
{
    if (root == nullptr)
    {
        return -1;
    }
    else
    {
        root->height = max(height(root->left), height(root->right)) + 1;
    }
    return root->height;
}

Node *rightRotate(Node *root)
{
    Node *temp = root->left;
    root->left = temp->right;
    temp->right = root;

    root->height = height(root);
    temp->height = height(temp);
    return temp;
}

Node *leftRotate(Node *root)
{
    Node *temp = root->right;
    root->right = temp->left;
    temp->left = root;

    root->height = height(root);
    temp->height = height(temp);
    return temp;
}

int getBalance(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else
    {
        return height(root->left) - height(root->right);
    }
}

Node *rebalance(Node *root)
{
    root->height = height(root);
    if (getBalance(root) == 2)
    {
        if (getBalance(root->right) < 0)
        {
            root->right = rightRotate(root->right);
        }
        return leftRotate(root);
    }
    if (getBalance(root) == -2)
    {
        if (getBalance(root->left) > 0)
        {
            root->left = leftRotate(root->left);
        }
        return rightRotate(root);
    }
    return root;
}

Node *insertNode(Node *root, int id, int level, std::string name, std::string rank)
{
    if (root == nullptr)
    {
        root = createNewNode(id, level, name, rank);
    }
    else if (id < root->id)
    {
        root->left = insertNode(root->left, id, level, name, rank);
    }
    else
    {
        root->right = insertNode(root->right, id, level, name, rank);
    }
    return rebalance(root);
}

Node *search(Node *root, int id)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else if (id == root->id)
    {
        return root;
    }
    else if (id <= root->id)
    {
        return search(root->left, id);
    }
    else
    {
        return search(root->right, id);
    }
}

Node *deleteNode(Node *root, int id)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else if (id == root->id)
    {
        if (root->left == nullptr)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        Node *temp = findMin(root->right);
        root->id = temp->id;
        root->right = deleteNode(root->right, temp->id);
    }
    else if (id < root->id)
    {
        root->left = deleteNode(root->left, id);
    }
    else
    {
        root->right = deleteNode(root->right, id);
    }
    return rebalance(root);
}

void show(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    show(root->left);
    std::cout << root->id << "\t" << root->name << "\t\t" << root->level << "\t" << root->rank << std::endl;
    show(root->right);
}

// std::string rank(std::string r)
// {
//     std::string res = "";
//     std::string buffer;

//     std::istringstream ss(r);

//     std::getline(ss, buffer, '-');
//     if (buffer == "0")
//     {
//         res += "Warrior";
//     }
//     else if (buffer == "1")
//     {
//         res += "Elite";
//     }
//     else if (buffer == "2")
//     {
//         res += "Master";
//     }
//     else if (buffer == "3")
//     {
//         res += "Grandmaster";
//     }
//     else if (buffer == "4")
//     {
//         res += "Epic";
//     }
//     else if (buffer == "5")
//     {
//         res += "Legend";
//     }
//     else if (buffer == "6")
//     {
//         res += "Mythic";
//     }
//     else if (buffer == "7")
//     {
//         res += "Mythical Honor";
//     }
//     else if (buffer == "8")
//     {
//         res += "Mythical Glory";
//     }
//     else
//     {
//         res += "Mythical Immortal";
//     }

//     std::getline(ss, buffer, '-');

//     return res + " " + buffer;
// }

main()
{

    Node *root = nullptr;

    root = insertNode(root, 15, 15, "TanteiBozu", "4-1");
    root = insertNode(root, 20, 15, "Celestia.", "4-2");
    std::cout << "yok";
    root = insertNode(root, 30, 15, "impi", "4-3");
    root = insertNode(root, 5, 15, "Epylepsee", "4-4");

    Node *res = search(root, 5);

    show(root);
    deleteNode(root, 15);
    show(root);

    // std::cout << (res->rank);

    return 0;
}