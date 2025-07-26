#include "KDTree.h"
#include <Arduino.h>

KDTree::KDTree() {
  global_root = nullptr;
}

struct KDTreeNode* KDTree::newKDTreeNode(float point[], int value[]) {
  struct KDTreeNode* temp = new KDTreeNode;

  temp->point[0] = point[0];
  temp->point[1] = point[1];
  temp->value[0] = value[0];
  temp->value[1] = value[1];

  temp->left = temp->right = nullptr;
  return temp;

}

KDTreeNode *KDTree::insertRec(KDTreeNode *root, float point[], int value[], unsigned depth) {
  // If tree is empty
  if (root == nullptr) {
    return newKDTreeNode(point, value);
  }

  // Find current dimension (i.e. x or y)
  unsigned cd = depth % 2;

  // Compare points
  if (point[cd] < (root->point[cd])) {
    root->left = insertRec(root->left, point, value, depth + 1);
  } else {
    root->right = insertRec(root->right, point, value, depth + 1);
  }

  return root;
}

KDTreeNode* KDTree::insert(float point[], int value[]) {
  global_root = insertRec(global_root, point, value, 0);
  return global_root;
}

bool KDTree::areEqual(float point1[], float point2[]) {
  if (point1[0] != point2[0] || point1[1] != point2[1]) {
    return false;
  }
  return true;
}

KDTreeNode* KDTree::closest(KDTreeNode *n0, KDTreeNode *n1, float target[]) {
  if (n0 == nullptr) {
    return n1;
  }
  if (n1 == nullptr) {
    return n0;
  }
  // calculate squared distance to n0
  double d0 = distSquared(target, n0->point);
  // calculate squared distance to n1
  double d1 = distSquared(target, n1->point);

  // return node with shorter distance (default to n1 if equal)
  if (d0 < d1) {
    return n0;
  }
  return n1;
}

double KDTree::distSquared(float p1[], float p2[]) {
  double x_diff = abs( p2[0] - p1[0] );
  double y_diff = abs( p2[1] - p1[1] );
  return x_diff * x_diff + y_diff * y_diff;
}

KDTreeNode* KDTree::nearestNeighborRec(KDTreeNode *root, float target[], unsigned depth) {
  if (root == nullptr) {
    return nullptr;
  }

  KDTreeNode *nextBranch;
  KDTreeNode *otherBranch;

  if (target[depth % 2] < root->point[depth % 2]) {
    nextBranch = root->left;
    otherBranch = root->right;
  } else {
    nextBranch = root->right;
    otherBranch = root->left;
  }

  KDTreeNode* temp = nearestNeighborRec(nextBranch, target, depth + 1);
  KDTreeNode* best = closest(temp, root, target);

  double radiusSquared = distSquared(target, best->point);

  double dist = target[depth % 2] - root->point[depth % 2];

  if (radiusSquared >= dist * dist) {
    temp = nearestNeighborRec(otherBranch, target, depth + 1);
    best = closest(temp, best, target);
  }

  return best;

}

KDTreeNode* KDTree::nearestNeighbor(float target[]) {
  return nearestNeighborRec(global_root, target, 0);
}



bool KDTree::searchRec(KDTreeNode *root, float point[], unsigned depth) {
  // Base cases
  if (root == nullptr) {
    return false;
  }
  if (areEqual(root->point, point)) {
    return true;
  }

  // Current dimension
  unsigned cd = depth % 2;

  // Compare point with root with respect to current dimension
  if (point[cd] < root->point[cd]) {
    return searchRec(root->left, point, depth + 1);
  }

  return searchRec(root->right, point, depth + 1);
}

bool KDTree::search(float point[]) {
  return searchRec(global_root, point, 0);
}
