/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include <memory>
#include <vector>

#include "raytrc/acceleration/acceleration_structure.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/objects/object_base.h"
#include "raytrc/geometry/ray.h"

namespace raytrc {

/*!
 * @brief Each node in the tree structure for this acceleration (BVH) contains a
 * reference to its child nodes and the object pointer. Additionally each node
 * calculates its AABB encompassing all subobjects.
 */
struct TreeNode {
  std::shared_ptr<TreeNode> left;  /*!< left subtree */
  std::shared_ptr<TreeNode> right; /*!< right subtree */
  std::shared_ptr<ObjectBase> obj; /*!< object if leave node, else null */
  AABB aabb;                       /*!< AABB of all subobjects */
};

/*!
 * @brief BVH acceleration structure implemented as tree, see
 * @link{https://en.wikipedia.org/wiki/Bounding_volume_hierarchy}
 */
class BVH : public AccelerationStructure {
 public:
  std::shared_ptr<TreeNode> root; /*!< containing the whole scene */

  /*!
   * @brief Generating the tree based on object list. The splitting criterion is
   * object median splitting, i.e. O(nlog^2(n)) (sorting along each
   * subdimension).
   * @param objects (unsorted) list of objects in the scene
   */
  BVH(std::vector<std::shared_ptr<ObjectBase>> objects);

  /*!
   * @brief Generating one node (sort objects along dimension, generate
   * encompassing AABB, split if necessary)
   * @param node node to be processed
   * @param objects list of objects for this node, if list.size == 1 -> leave
   */
  void processNode(std::shared_ptr<TreeNode> node,
                   std::vector<std::shared_ptr<ObjectBase>> objects);
  /*!
   * @brief Casting a ray through the scene, using the accelerated structure.
   * @param ray ray to be cast
   * @param intersection intersection parameter stub
   * @return whether intersection was found
   */
  bool cast(Ray *ray, Intersection *intersection) override;
};

}  // namespace raytrc