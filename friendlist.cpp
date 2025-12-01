#include <iostream>
#include <sstream>
#include <fstream>

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

int max(int left, int right)
{
    if (left > right)
    {
        return left;
    }
    return right;
}

Node *getMin(Node *node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
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

int balanceFactor(Node *node)
{
    return height(node->left) - height(node->right);
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
    else if (id > root->id)
    {
        root->right = insertNode(root->right, id, level, username, rank);
    }
    else
    {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int bf = height(root->left) - height(root->right);
    // std::cout << bf << std::endl;
    // std::cout << root->height << "-" << root->username << std::endl;

    if (bf < -1 && id > root->right->id)
    {
        return leftRotate(root);
    }
    else if (bf > 1 && id < root->left->id)
    {
        return rightRotate(root);
    }
    else if (bf < -1 && id < root->right->id)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    else if (bf > 1 && id > root->left->id)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    return root;
}

Node *deleteNode(Node *root, int id, bool announce = false)
{
    if (root == nullptr)
    {
        return root;
    }
    else if (id < root->id)
    {
        root->left = deleteNode(root->left, id, announce);
    }
    else if (id > root->id)
    {
        root->right = deleteNode(root->right, id, announce);
    }
    else
    {
        if (announce)
        {
            std::cout << "\nPlayer with ID : " << id << " has been removed.\n\n";
        }
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
        else
        {
            Node *temp = getMin(root->right);

            root->id = temp->id;
            root->level = temp->level;
            root->username = temp->username;
            root->rank = temp->rank;

            // std::cout << "Player with ID : " << root->id << " has been removed.\n";

            root->right = deleteNode(root->right, temp->id, false);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int bf = height(root->left) - height(root->right);

    if (bf < -1 && balanceFactor(root->right) < 0)
    {
        return leftRotate(root);
    }
    else if (bf > 1 && balanceFactor(root->left) > 0)
    {
        return rightRotate(root);
    }
    else if (bf < -1 && balanceFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    else if (bf > 1 && balanceFactor(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    return root;
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
            std::cout << "You have no friend :(\nStart adding!\n";
        }
        return;
    }

    if (step > -1)
    {
        show(root->left, ++step);
    }

    // DEBUG PURPOSES
    // std::cout << height(root->left) - height(root->right) << " = ";
    // std::cout << root->height << "\t";
    std::cout << root->id << "\t";
    std::cout << root->level << "\t";
    std::cout << root->username << "\t\t\t";
    std::cout << rank(root->rank) << "\n";

    if (step > -1)
    {
        show(root->right, step++);
    }
}

Node *searchById(Node *root, int id)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else if (id < root->id)
    {
        return searchById(root->left, id);
    }
    else if (id > root->id)
    {
        return searchById(root->right, id);
    }
    else
    {
        return root;
    }
}

Node *searchByName(Node *root, std::string u)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    Node *res;

    res = searchByName(root->left, u);
    if (res != nullptr)
    {
        return res;
    }

    if (root->username == u)
    {
        return root;
    }

    res = searchByName(root->right, u);
    if (res != nullptr)
    {
        return res;
    }

    return nullptr;
}

void dataImport(Node *&root, int &n)
{
    std::fstream file("data.txt", std::ios::in);

    if (!file)
    {
        std::cout << "Terjadi error!";
        return;
    }

    std::string buffer;
    while (getline(file, buffer))
    {
        // std::cout << buffer << std::endl;
        std::string username, rank, id, level;

        std::istringstream ss(buffer);

        std::getline(ss, id, ':');
        std::getline(ss, level, ':');
        std::getline(ss, username, ':');
        std::getline(ss, rank, ':');
        root = insertNode(root, std::stoi(id), std::stoi(level), username, rank);
        n = 1 + std::stoi(id);
    }

    file.close();
}

void dataPackager(Node *root, std::string &result)
{

    if (root == nullptr)
    {
        return;
    }

    dataPackager(root->left, result);

    std::string buffer = "";
    buffer += std::to_string(root->id);
    buffer += ":";
    buffer += std::to_string(root->level);
    buffer += ":";
    buffer += root->username;
    buffer += ":";
    buffer += root->rank;
    buffer += "\n";

    result += buffer;

    dataPackager(root->right, result);
}

void dataExport(Node *&root)
{
    std::fstream file("data.txt", std::ios::out | std::ios::trunc);

    if (!file)
    {
        std::cout << "Terjadi error!";
        return;
    }

    std::string buffer = "";

    dataPackager(root, buffer);
    file << buffer;

    file.close();
}

void header()
{
    std::cout << "===========================================================\n";
    std::cout << "                          Friends                          \n";
    std::cout << "===========================================================\n";
    std::cout << "ID\tLevel\tName\t\t\tRank\n";
}

void menu(Node *&root, int id)
{
    bool result = false;
    while (true)
    {
        if (root != nullptr && !result)
        {
            header();
        }

        if (!result)
        {
            show(root);
        }

        int opt;
        std::cout << "\n1. View All\n2. Add Friend\n3. Search by ID\n4. Search by Name (WIP)\n5. Remove Friend\n6. Close\n\nI'm choosing : ";
        std::cin >> opt;

        if (opt == 1)
        {
            result = false;
            system("cls");
        }
        else if (opt == 2)
        {
            int level;
            std::string username, rank;

            std::cout << "Insert the details...\n";

            std::cout << "Level: ";
            std::cin >> level;
            std::cin.ignore();

            std::cout << "Username: ";
            std::getline(std::cin, username);

            std::cout << "Rank: ";
            std::getline(std::cin, rank);

            Node *res = searchById(root, id);

            system("cls");
            if (!res)
            {

                root = insertNode(root, id, level, username, rank);
                std::cout << "Added " << username << " as your friend!\n";
                id++;
            }
            else
            {
                std::cout << "Player is already your friend!\n";
            }
        }
        else if (opt == 3)
        {
            int lf;
            std::cout << "Insert ID : ";
            std::cin >> lf;

            Node *res = searchById(root, lf);

            system("cls");
            if (res == nullptr)
            {
                std::cout << "\nNot found!\n";
            }
            else
            {
                header();
            }

            show(res, -1);
            result = true;
        }
        else if (opt == 4)
        {
            std::cin.ignore();
            std::string lf;
            std::cout << "Insert Name : ";
            std::getline(std::cin, lf);

            system("cls");
            Node *res = searchByName(root, lf);
            if (res == nullptr)
            {
                std::cout << "\nNot found!\n";
            }
            else
            {
                header();
            }
            show(res, -1);
            result = true;
        }
        else if (opt == 5)
        {
            int lf;
            std::cout << "Insert ID : ";
            std::cin >> lf;

            Node *res = searchById(root, lf);

            system("cls");
            if (!res)
            {
                std::cout << "\nFriend with that ID doesn't exist!\n\n";
            }
            root = deleteNode(root, lf, true);
        }
        else if (opt == 6)
        {
            return;
        }
    }
}

int main()
{

    int auto_inc = 1;
    Node *root = nullptr;
    dataImport(root, auto_inc);

    menu(root, auto_inc);

    dataExport(root);
    std::cout << "\nClosing...";

    return 0;
}