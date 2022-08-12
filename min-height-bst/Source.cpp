#include <iostream>
#include <vector>

using namespace std;

class BST {
public:
  int value;
  BST *left;
  BST *right;

  BST(int value) {
    this->value = value;
    left = nullptr;
    right = nullptr;
  }

  void insert(int value) {
    if (value < this->value) {
      if (left == nullptr) {
        left = new BST(value);
      } else {
        left->insert(value);
      }
    } else {
      if (right == nullptr) {
        right = new BST(value);
      } else {
        right->insert(value);
      }
    }
  }
};

struct Trunk
{
    Trunk* prev;
    string str;

    Trunk(Trunk* prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

BST *constructMinHeightBst(vector<int> array, int startIdx, int endIdx );

BST *minHeightBst(vector<int> array) {
  // Write your code here.
  return constructMinHeightBst(array, 0, array.size() -1 );;
}

BST *constructMinHeightBst(vector<int> array, int startIdx, int endIdx )
{
  if(endIdx < startIdx)return nullptr;

  int midIdx = (startIdx + endIdx) / 2;
  BST *bst = new BST(array[midIdx]);

  bst->left = constructMinHeightBst(array, startIdx, midIdx - 1 );
  bst->right = constructMinHeightBst(array, midIdx + 1 , endIdx );
  return bst;
}
void showTrunks(Trunk* p);
void printTree(BST* root, Trunk* prev, bool isLeft);

int main()
{
    vector<int> array{ 1, 2, 5, 7, 10, 13, 14, 15, 22 };
    printTree(minHeightBst(array), nullptr, false);
    return 0;
}

void showTrunks(Trunk* p)
{
    if (p == nullptr) {
        return;
    }

    showTrunks(p->prev);
    cout << p->str;
}

void printTree(BST* root, Trunk* prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }

    string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev) {
        trunk->str = "---";
    }
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << " " << root->value << endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}