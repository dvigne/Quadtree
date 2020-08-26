#include "Quadtree.h"
#include <utility>

/////////////////////////////////////////////////
/// @fn bool Box::contains(point pt)
/// @brief Check if a point is contained within
/// the bounding box
/// @param pt point to check.
/// @returns `bool` point in box.
/////////////////////////////////////////////////

bool Box::contains(point pt) {
  return
    (pt.x >= topLeft.x)  &&
    (pt.x <= bottomRight.x) &&
    (pt.y >= topLeft.y)  &&
    (pt.y <= bottomRight.y);
}

/////////////////////////////////////////////////
/// @fn bool Box::contains(Node node)
/// @brief Checks if a node is contained within a bounding box
/// @param node Node to check
/// @returns `bool` True if node is in bounding box
/////////////////////////////////////////////////

bool Box::contains(Node node) {
  return contains(node.getPosition());
}

/////////////////////////////////////////////////
/// @fn bool Box::intersectsBox(Box* box)
/// @brief Checks if a bounding box exists within another
/// bounding box
/// @param box Box to check
/// @returns `bool` returns true if supplied box
/// intersects with this box
/////////////////////////////////////////////////

bool Box::intersectsBox(Box box) {
  std::pair<point, point> bounds = box.getBounds();
  return contains(bounds.first) &&
         contains(bounds.second);
}

/////////////////////////////////////////////////
/// @fn std::pair<point, point> Box::getBounds()
/// @brief Returns the top left and bottom right points of
/// the bounding box
/// @returns `std::pair<point, point>` Returns a standard pair containing
/// top-left and bottom right
/////////////////////////////////////////////////

std::pair<point, point> Box::getBounds() {
  return std::make_pair(topLeft, bottomRight);
}
