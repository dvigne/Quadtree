#pragma once
#include <cstdint>
#include <vector>
#include <utility>
#include <memory>

/////////////////////////////////////////////////
/// Out of Bounds Derived Structure
/// Throws `const char * "Supplied point is out of tree bounds"` if the requested operation cannot be completed given the point
/// @author Derick Vigne
/// @copyright MIT License
/////////////////////////////////////////////////

struct OutOfBoundsException : public std::exception {
  /// @brief Returns `const char *` for pretty printing
  const char * what() const throw() {
    return "Supplied point out of tree bounds";
  }
};

/////////////////////////////////////////////////
/// @struct point
/// @brief Simple datastructure to hold x and y
/// coordinates
///
/// @fn point::point(float x, float y)
/// @brief point struct constructor
/// @param x X coordinate to assign
/// @param y Y coordinate to assign
///
/// @fn bool point::operator==(const point& otherPoint)
/// @brief Overloaded `==` operator for equivalency testing
/// @param otherPoint Second point to test
/// @returns `bool` True or false depending on equivalency
/////////////////////////////////////////////////

struct point {
  float x; ///< X coordinate of the point
  float y; ///< Y coordinate of the point
  point(float x, float y) : x(x), y(y){};
  bool operator==(const point& otherPoint) { return (x == otherPoint.x) && (y == otherPoint.y); };
};

class Node {
private:
  point position;
  int8_t occupiedConfidence;
  bool nodeVisited = false;

public:
  /////////////////////////////////////////////////
  /// @fn Node::Node(point* position, int occupiedConfidence, bool visited = false)
  /// @brief Node constructor
  /// @param position point position of node
  /// @param occupiedConfidence Percent confidence that a node is occupied by an obstacle.
  /// Helps with optimizing the search algorithm.
  /// ranges from `0-100` and `-1` if unknown
  /// @param visited Optional setting to mark this node as visited
  /////////////////////////////////////////////////
  Node(point position, int occupiedConfidence, bool visited = false) : position(position), occupiedConfidence(occupiedConfidence), nodeVisited(visited){};
  point getPosition();
  int getOccupiedConfidence();
  bool visited();
};

class Point {
public:
  float x; ///< X Coordinate
  float y; ///< Y Coordinate
};

class Box {
private:
  point topLeft;
  point bottomRight;

public:
  /////////////////////////////////////////////////
  /// @fn Box::Box(point center, float halfDimension)
  /// @brief Axis-aligned bounding box constructor
  /// @param topLeft top-most left point of the bounding box
  /// @param bottomRight bottom-most right point of the bounding box
  /////////////////////////////////////////////////
  Box(point topLeft, point bottomRight) : topLeft(topLeft), bottomRight(bottomRight){};
  bool contains(point pt);
  bool contains(Node node);
  bool intersectsBox(Box box);
  std::pair<point, point> getBounds();
};

/////////////////////////////////////////////////
/// Quadtree class containing supporting quadtree functions
/// @author Derick Vigne
/////////////////////////////////////////////////
class Quadtree {
private:
  const uint8_t nodeCapacity = 4;
  Box boundingBox;

  std::vector<Node> nodes;

  std::unique_ptr<Quadtree> topLeft;
  std::unique_ptr<Quadtree> topRight;
  std::unique_ptr<Quadtree> bottomLeft;
  std::unique_ptr<Quadtree> bottomRight;

  void subdivide(); ///< Split the node into four equal quadrants about the center

public:
  /////////////////////////////////////////////////
  /// @fn Quadtree::Quadtree(Box boundingBox)
  /// @brief Quadtree Constructor
  /// @param boundingBox Set the bounding box for this quadrant of the quadtree
  ///
  /// @fn Quadtree::Quadtree(point topLeftPoint, point bottomRightPoint)
  /// @brief Same as the Quadtree(Box boundingBox) constructor, except it will
  /// build a bounding box out of the provided points
  /// @param topLeftPoint The topmost left point of the bounding box
  /// @param bottomRightPoint top bottom-most right point of the bounding box
  /////////////////////////////////////////////////
  Quadtree(Box boundingBox) : boundingBox(boundingBox){};
  Quadtree(point topLeftPoint, point bottomRightPoint) : boundingBox(topLeftPoint, bottomRightPoint){};
  bool insert(Node node);
  Node search(point position);
  Box getBoundingBox();
  // std::vector<Node*> search(Box* range); // Only traversing by point for the moment....this will require some thought
};
