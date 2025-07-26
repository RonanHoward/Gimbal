/*
  KDTree.h - Custom Library for a 2-dimensional K-D
  Tree. Used for Concept Propulsion gimbal.
*/
#ifndef KDTree_h
#define KDTree_h

#include <Arduino.h>

struct KDTreeNode {
  float point[2];
  int value[2];
  KDTreeNode *left, *right;
};

class KDTree {

  public:
    KDTree();
    KDTreeNode *global_root;
    struct KDTreeNode* newKDTreeNode(float point[], int value[]);
    KDTreeNode *insertRec(KDTreeNode *root, float point[], int value[], unsigned depth);
    KDTreeNode* insert(float point[], int value[]);
    bool areEqual(float point1[], float point2[]);
    KDTreeNode* closest(KDTreeNode *n0, KDTreeNode *n1, float target[]);
    KDTreeNode* nearestNeighborRec(KDTreeNode *root, float target[], unsigned depth);
    KDTreeNode* nearestNeighbor(float target[]);
    double distSquared(float p1[], float p2[]);


    bool searchRec(KDTreeNode *root, float point[], unsigned depth);
    bool search(float point[]);

};

#endif