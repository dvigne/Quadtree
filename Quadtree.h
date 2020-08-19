#ifndef __QUADTREE_H__
#define __QUADTREE_H__
#include <exception>

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
/// Point datastructure containing floating point XY Coordinates
/// @author Derick Vigne
/////////////////////////////////////////////////

class Point {
public:
  float x; ///< X Coordinate
  float y; ///< Y Coordinate

  /////////////////////////////////////////////////
  /// @fn Point(float x, float y)
	/// @brief Used to create a point located at position XY
	/// @param x X Coordinate of Point
	/// @param y Y Coordinate of Point
  /////////////////////////////////////////////////
  Point(float x, float y) { this->x = x; this->y = y; }; ///< Initialization Constructor
};

/////////////////////////////////////////////////
/// Node datastructure containing positional, occupancy, and search heuristics
/// @author Derick Vigne
/////////////////////////////////////////////////

class Node {
private:
  Point* position; ///< Position of this node
  int occupiedConfidence; ///< Percent confident that this given node is occupied by an obstacle
  bool visited = false; ///< Have we visited this node before. Helps with the irrevocability of the search algorithm.

public:
  /////////////////////////////////////////////////
  /// @fn Node(Point position, int occupancyValue, visited = false)
	/// @brief Constructor for a Node Containing a Point and the Data Associated
	/// @param position Nodes 2D position
	/// @param occupancyValue Percent Confidence an Obstacle Exists at that Point
	/// Value will be in the range `0-100` and unknown is `-1`
	/// @param visited Have we Visited this Point Before.
	/// Used to Assist With Irrevocability of the Path Planning Algorithm
  /////////////////////////////////////////////////
  Node(Point position, int occupancyValue, visited = false) { this->position = position; this->occupiedConfidence = occupiedConfidence; this->visited = visited; };
  Point* getPosition(); ///< Returns the Stored Position of the Node
  int getOccupiedConfidence(); ///< Return the Stored Confidence Score
  bool visited(); ///< Returns if Visited
};

/////////////////////////////////////////////////
/// Quadtree class containing supporting quadtree functions
/// @author Derick Vigne
/////////////////////////////////////////////////
class Quadtree {
private:
  ///< Boundary information for intersection detection
  Point* leftBoundary; ///< Top left boundary
  Point* rightBoundary ///< Bottom Right Boundary

  Node* node; ///< Properties of current node

  ///< Quadrants
  Quad* topLeft;
  Quad* bottomLeft;
  Quad* topRight;
  Quad* bottomRight;

public:
  /////////////////////////////////////////////////
  /// @fn Quadtree::Quadtree(Point topLeft, Point bottomRight
  /// @brief Constructor used to initialize the boundaries of the quadtree
	/// @param topLeft Top Left Boundary Point
	/// @param bottomRight Bottom Left Boundary Point
  /////////////////////////////////////////////////
  Quadtree(Point topLeft, Point bottomRight) { this->leftBoundary = topLeft; this->rightBoundary = bottomRight; };
  void insert(Node* node);
  Node* search(Point* point);
  bool contains(Point* point);
};






#endif /* end of include guard: __QUADTREE_H__ */
