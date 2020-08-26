#include "Quadtree.h"

/////////////////////////////////////////////////
/// @fn Box Quadtree::getBoundingBox()
/// @brief returns the requested nodes bounding box
/// @returns `Box` The bounding box of the node
/////////////////////////////////////////////////

Box Quadtree::getBoundingBox() {
  return boundingBox;
}

void Quadtree::subdivide() {
  point topLeftPoint = boundingBox.getBounds().first;
  point bottomRightPoint = boundingBox.getBounds().second;

  topLeft = std::unique_ptr<Quadtree>(new Quadtree(
    topLeftPoint, point(topLeftPoint.x / 2, topLeftPoint.y / 2)
  ));

  bottomLeft = std::unique_ptr<Quadtree>(new Quadtree(
    point(topLeftPoint.x, topLeftPoint.y),
     point(topLeftPoint.x / 2, bottomRightPoint.y)
  ));

  topRight = std::unique_ptr<Quadtree>(new Quadtree(
    point(topLeftPoint.x / 2, topLeftPoint.y),
    point(bottomRightPoint.x, topLeftPoint.y /2)
  ));

  bottomRight = std::unique_ptr<Quadtree>(new Quadtree(
    point(topLeftPoint.x / 2, topLeftPoint.y / 2), bottomRightPoint
  ));
}

/////////////////////////////////////////////////
/// @fn bool Quadtree::insert(Node)
/// @brief Insert a node containing a Point into the quadtree
/// @param node Node to be inserted
/////////////////////////////////////////////////

bool Quadtree::insert(Node node) {
  if(!boundingBox.contains(node)) {
    return false;
  }

  if(nodes.size() < nodeCapacity && !topLeft) {
    nodes.push_back(node);
    return true;
  }

  if(!topLeft) {
    subdivide();
  }

  if(topLeft->insert(node)) return true;
  if(topRight->insert(node)) return true;
  if(bottomLeft->insert(node)) return true;
  if(bottomRight->insert(node)) return true;

  return false;
}

/////////////////////////////////////////////////
/// @fn Node Quadtree::search(point position)
/// @brief Search for a given point and return the node
/// @param position Point to search for
/// @return `Node` Returns requested Node
/// @throws OutOfBoundsException
/// Will be thrown if requested point does not exist in the tree
/////////////////////////////////////////////////

Node Quadtree::search(point position) {
  if(!boundingBox.contains(position)) {
    throw OutOfBoundsException();
  }

  for (Node node : nodes) {
    if(node.getPosition() == position) {
      return node;
    }
  }

  if(topLeft->getBoundingBox().contains(position)) {
    return topLeft->search(position);
  }

  if(topRight->getBoundingBox().contains(position)) {
    return topRight->search(position);
  }

  if(bottomLeft->getBoundingBox().contains(position)) {
    return bottomLeft->search(position);
  }

  else {
    return bottomRight->search(position);
  }
}
