#pragma once

#include <memory>
#include <vector>

#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/objects/object_base.h"
#include "raytrc/geometry/ray.h"

namespace raytrc {

struct TreeNode {
  std::shared_ptr<TreeNode> left;
  std::shared_ptr<TreeNode> right;
  std::shared_ptr<ObjectBase> obj;
  AABB aabb;

  TreeNode() {
    this->left = nullptr;
    this->right = nullptr;
    this->obj = nullptr;
  };
};

class BVH {
 public:
  std::shared_ptr<TreeNode> root;

  BVH(std::vector<std::shared_ptr<ObjectBase>> objects);

  void processNode(std::shared_ptr<TreeNode> node,
                   std::vector<std::shared_ptr<ObjectBase>> objects);
  bool cast(Ray *ray, Intersection *intersection);
};

}  // namespace raytrc