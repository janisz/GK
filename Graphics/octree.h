#ifndef OCTREE_H
#define OCTREE_H

#include "QDebug"
#include "Graphics/colors.h"
#define MAX_LEVEL 8
typedef unsigned int uint;

/*
  *  |  0   1   2   3   4   5   6   7 |
  *--+--------------------------------+
  * R|  0   1   0   0   1   1   0   1 |
  * G|  0   0   1   0   1   0   1   1 |
  * B|  0   0   0   1   0   1   1   1 |
  *
    0 ->   0
    1 -> 100
    2 ->  10
    3 ->   1
    4 -> 110
    5 -> 101
    6 ->  11
    7 -> 111

  */

struct Node
{
    Node* prev = 0;
    Node* next[8] = {0};
    uint color = 0;
    int colorCount = 0;
    int level;
    int order = 0;
    bool leaf = 0;
    bool valid = 0;

    Node(Node *Prev, int Level) { prev = Prev; level = Level; color = 0; colorCount = 0; leaf = false;}
    Node* Next(int i) { return next[i]; }
    Node* Prev() { return prev; }
    bool isLeaf() { return (level == MAX_LEVEL-1) || leaf; }
    bool isRoot() { return prev == 0; }
    int Branch(uint color)    {
        int r = get_bit(getRed(color),   level);
        int g = get_bit(getGreen(color), level);
        int b = get_bit(getBlue(color),  level);
        int val = r*100 + g * 10 + b;

        if (val ==   0) return 0;
        if (val == 100) return 1;
        if (val ==  10) return 2;
        if (val ==   1) return 3;
        if (val == 110) return 4;
        if (val == 101) return 5;
        if (val ==  11) return 6;
        if (val == 111) return 7;
    }

    Node* HeavyNode()     {
        Node *result = next[0];
        for (int i=1;i<MAX_LEVEL;i++) {
            if (result->colorCount < next[i]->colorCount) {
                result = next[i];
            }
        return result;
        }
    }
};

class OcTree{
public:
    OcTree();
    ~OcTree();
    void Show();
    void Insert(int color);
    Node* getRoot() { return root; }
    void SetColors() { SetColors(root); }
    int usedColors = 0;
private:
    Node* root;

    void CreateTree(Node *r, int level);
    uint SetColors(Node *r);
    void CleanColors();
    void OrderNodes(int order);
    void ReductColors(int maxLeafCount);
friend QDebug operator<< (QDebug d, const OcTree *model);
};

inline QDebug operator<< (QDebug d, OcTree* s) {
    d << "Color count: " << s->getRoot()->colorCount;
    d << "\nColors: " << s->usedColors;
    for (int i=0;i<8;i++)
    {
        d << "\n" << i << ": " << s->getRoot()->Next(i)->color;
    }
    return d;
}

#endif // OCTREE_H
