#include "Quadtree.h"

/////////////////////////////////////////////////
/// @fn point Node::getPosition()
/// @brief Returns the Position of the Node object
/// @returns `point` The Position of the Node Object
/////////////////////////////////////////////////

point Node::getPosition() {
  return position;
}

/////////////////////////////////////////////////
/// @fn int Node::getOccupiedConfidence()
/// @brief Returns the percent occupied confidency score that an
/// obstacle exists at this node.
/// @returns `int` percent occupancy score. Ranges from `0-100`
/// or `-1` if unknown
/////////////////////////////////////////////////

int Node::getOccupiedConfidence() {
  return occupiedConfidence;
}

/////////////////////////////////////////////////
/// @fn bool Node::visited()
/// @brief Check if we have visited this node before. This helps with
/// optimizing the search algorithm for completeness.
/// @returns `bool` true or false regarding whether we have
/// visited this node or not.
/////////////////////////////////////////////////

bool Node::visited() {
  return nodeVisited;
}
