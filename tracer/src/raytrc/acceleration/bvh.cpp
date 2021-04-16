/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "bvh.h"

#include <memory>
#include <stack>
#include <vector>

#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/objects/object_base.h"
#include "raytrc/geometry/ray.h"

using namespace raytrc;

/*!
 * The constructor generates a (balanced) tree for all objects, by object median
 * splitting and recursively processing sub nodes.
 */
BVH::BVH(std::vector<std::shared_ptr<ObjectBase>> objects) {
  this->root = std::make_shared<TreeNode>();
  processNode(this->root, objects);
};

/*!
 * Recursive function to generate the acceleration structure tree.
 * Generates a leave (1 object in list) or sub nodes (>1 objects in list), sorts
 * the list and calculates the AABB of all objects in each tree if necessary.
 * This is a top-down implementation.
 */
void BVH::processNode(std::shared_ptr<TreeNode> node,
                      std::vector<std::shared_ptr<ObjectBase>> objects) {
  if (objects.size() == 1) {  // generating a leave node, need no aabb
    node->obj = objects[0];
  } else {  // generating two sub nodes, each containing half of the objects
    AABB aabb = objects[0]->getAABB();
    for (std::shared_ptr<ObjectBase> obj : objects)
      aabb = aabb.combine(obj->getAABB());

    uint8_t maxDim = aabb.getMaxDimension();
    std::sort(
        std::begin(objects), std::end(objects),
        [maxDim](std::shared_ptr<ObjectBase> a, std::shared_ptr<ObjectBase> b) {
          return a->position[maxDim] < a->position[maxDim];
        });

    size_t half = objects.size() / 2;
    std::vector<std::shared_ptr<ObjectBase>> leftObjs(objects.begin(),
                                                      objects.begin() + half);
    std::vector<std::shared_ptr<ObjectBase>> rightObjs(objects.begin() + half,
                                                       objects.end());

    node->left = std::make_shared<TreeNode>();
    node->right = std::make_shared<TreeNode>();
    node->aabb = aabb;

    processNode(node->left, leftObjs);
    processNode(node->right, rightObjs);
  }
};

/*!
 * Cheaper intersection tests through testing against the AABB first, then if
 * necessary against the objects in the subnodes.
 * Implementation uses a stack to keep track of nodes that still need to be
 * searched, additional optimizations for future work: don't search if AABB
 * intersection farther than previously found intersection.
 */
bool BVH::cast(Ray *ray, Intersection *intersection) {
  std::stack<std::shared_ptr<TreeNode>> stk;
  stk.push(this->root);

  float t_ = FLT_MAX;
  std::shared_ptr<ObjectBase> o_;

  while (stk.size()) {
    auto node = stk.top();
    stk.pop();

    if (node->obj == nullptr) {
      // node is internal node -> check if we hit its aabb, if so add subnodes
      // add subnodes
      if (node->aabb.intersect(ray)) {
        stk.push(node->left);
        stk.push(node->right);
      }
    } else {
      // node is leaf -> check if we intersect object
      Intersection tmp;
      if (node->obj->intersect(ray, &tmp) && ray->t > 0 && ray->t < t_) {
        t_ = ray->t;
        o_ = node->obj;
      }
    }
  }

  if (t_ == FLT_MAX) return false;

  o_->intersect(ray, intersection);
  return true;
};