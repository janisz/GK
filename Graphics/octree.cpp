//#include "octree.h"

//OcTree::OcTree()
//{
//    usedColors = 0;
//    root = new Node(0, -1);
//    CreateTree(root, 0);
//}

//OcTree::~OcTree()
//{
//}

//void OcTree::CreateTree(Node *r, int level)
//{
//    if (level == 7) return;

//    level++;
//    for (int i=0;i<8;i++)
//    {
//        r->next[i] = new Node(r, level);
//        CreateTree(r->Next(i), level);
//    }
//}

//void OcTree::Insert(int color)
//{
//    Node *tmp = root;
//    while (!tmp->isLeaf())
//    {
//        tmp->colorCount++;
//        tmp = tmp->Next(tmp->Branch(color));
//    }
//    tmp->colorCount++;
//    tmp->color = color;
//    tmp->leaf = true;
//}
//void OcTree::SetColors()
//{
//    SetColors(root);
//}

//uint OcTree::getColor(uint color)
//{
//    Node *tmp = root;
//    while (!tmp->isLeaf())
//    {
//        tmp->colorCount++;
//        tmp = tmp->Next(tmp->Branch(color));
//    }
//    return tmp->color;
//}

//uint OcTree::SetColors(Node* r)
//{
//    if (r->isLeaf())
//    {
//        if (r->color)
//        {
//            usedColors++;
//        }
//        return r->color;
//    }
//    for (int i=0;i<8;i++)
//        SetColors(r->Next(i));

//    r->color = r->HeavyNode()->color;

//    return r->color;
//}


//Node* OcTree::FindColorNode(uint color)
//{
//    Node *tmp = root;
//    while (!tmp->isLeaf())
//    {
//        tmp->colorCount++;
//        tmp = tmp->Next(tmp->Branch(color));
//    }
//    return tmp;
//}

