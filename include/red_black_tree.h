#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

#include "vector.h"

#include <algorithm>
#include <iostream>

namespace ds {
enum class Color {RED, BLACK};

template<typename Type>
class RedBlackTree {
 public:
  /** Node representing an element in the tree */
  struct Node {
    Type value_;
    Color color_;
    Node *left_{};
    Node *right_{};
    Node *parent_{};

    /** Default constructor */
    Node() : Node(Type()) {}

    /**
     * Construct a new Node object
     * @param value the value of the node
     */
    explicit Node(const Type& value) : value_(value) {}

    /**
     * Construct a new Node object
     * @param value the value of the node
     * @param color the color of the node (either red or black)
     * @param left the pointer to the left node
     * @param right the pointer to the right node
     * @param parent the pointer to the parent node
     */
    Node(const Type& value, const Color& color, Node *left=nullptr, Node *right=nullptr, Node *parent=nullptr)
      : value_(value), color_(color), left_(left), right_(right), parent_(parent) {}
  };

  /** ---------- Red-Black Tree ---------- */

  /**
   * Default constructor 
   * At the beginning, `root` points to `nil` since the tree is empty
   */
  RedBlackTree() : nil_(new Node(Type(), Color::BLACK)), root_(nil_) {}

  /**
   * Construct a new Red-Black tree from a list of elements
   * @param data the list of elements
   */
  RedBlackTree(Vector<Type>& data) : RedBlackTree() {
    for (const auto& ele : data) {
      Insert(ele);
    }
  }

  /**
   * Construct a new Red-Black tree using an initializer list
   * @param data the list of elements to initialize
   */
  RedBlackTree(std::initializer_list<Type> data) : RedBlackTree() {
    for (const auto& ele : data) {
      Insert(ele);
    }
  }

  /** Copy constructor 
   * @param other the source Red-Black tree to construct from
   */
  RedBlackTree(const RedBlackTree& other) : RedBlackTree() {
    root_ = BuildTree(other.root_, other.nil_, nil_);
  }

  /**
   * Move constructor
   * @param other the source Red-Black tree to move from
   */
  RedBlackTree(RedBlackTree&& other) noexcept : RedBlackTree() {
    other.Swap(*this);
  }

  /** Destructor */
  ~RedBlackTree() {
    DestructTree(root_);
    delete nil_;
  }

  /** Copy assignment operator 
   * @param other the source Red-Black tree to assign from
   * @return a reference to the Red-Black tree assigned
   */
  RedBlackTree& operator=(const RedBlackTree& other) {
    RedBlackTree copy(other);
    copy.Swap(*this);
    return *this;
  }

  /** Move assignment operator 
   * @param the source Red-Black tree to move from
   * @return a reference to the Red-Black tree assigned
   */
  RedBlackTree& operator=(RedBlackTree&& other) noexcept {
    other.Swap(*this);
    return *this;
  }

  /** @return a pointer to the root of the tree*/
  Node* GetRoot() const { return root_; }

  /** @return a pointer to the sentinel node of the tree */
  Node* GetNIL() const { return nil_; }

  /**
   * Searchs the Red Black tree for a value
   * @param value the value to search
   * @return the pointer to the tree node containing the value
   */
  Node* Search(const Type& value) {
    Node *node = root_;
    while (node != nil_ && node->value_ != value) {
      if (value < node->value_) {
        node = node->left_;
      } else {
        node = node->right_;
      }
    }
    return node;
  }

  /**
   * Finds the the minimum value of the subtree rooted at a node
   * @param node the root of that subtree
   * @return the pointer to the tree node containing the minimum value
   */
  Node* Minimum(Node *node) {
    while (node != nil_ && node->left_ != nil_) {
      node = node->left_;
    }
    return node;
  }

  /**
   * Finds the the maximum value of the subtree rooted at a node
   * @param node the root of that subtree
   * @return the pointer to the tree node containing the maximum value
   */
  Node* Maximum(Node *node) {
    while (node != nil_ && node->right_ != nil_) {
      node = node->right_;
    }
    return node;
  }

  /**
   * Finds the successor (next greater) of a node
   * @param node the node to find its successor
   * @return a pointer to the successor node
   */
  Node* Successor(Node *node) {
    if (node->right_ != nil_) {
      return Minimum(node->right_);
    }
    while (node->parent_ != nil_ && node == node->parent_->right_) {
      node = node->parent_;
    }
    return node->parent_;
  }

  /**
   * Finds the predecessor (next smaller) of a node
   * @param node the node to find its predecessor
   * @return a pointer to the predecessor node
   */
  Node* Predecessor(Node *node) {
    if (node->left_ != nil_) {
      return Maximum(node->left_);
    }
    while (node->parent_ != nil_ && node == node->parent_->left_) {
      node = node->parent_;
    }
    return node->parent_;
  }

  /**
   * Inserts a value into the Red-Black tree
   * @param value the value to insert
   * @return a pointer to the newly inserted node
   */
  Node* Insert(const Type& value) {
    auto new_node = new Node(value, Color::RED, nil_, nil_);
    Node *parent = nil_;
    Node *cur = root_;
    while (cur != nil_) {
      parent = cur;
      if (value < cur->value_) {
        cur = cur->left_;
      } else {
        cur = cur->right_;
      }
    }
    new_node->parent_ = parent;
    if (parent == nil_) {
      root_ = new_node;
    } else if (value < parent->value_) {
      parent->left_ = new_node;
    } else {
      parent->right_ = new_node;
    }
    // newly inserted node can violate RB-tree properties
    RBInsertFixUp(new_node);
    return new_node;
  }

  /**
   * Deletes a node with `value` value from the Red-Black tree
   * @param value the value to delete
   * @return true if deletion succeeds; otherwise, false
   */
  bool Delete(const Type& value) {
    Node *z = Search(value);
    if (z == nil_) {
      return false;
    }
    Node *y = z;
    Node *x;
    Color y_original_color = y->color_;
    if (z->left_ == nil_) {
      x = z->right_;
      RBTransplant(z, z->right_);
    } else if (z->right_ == nil_) {
      x = z->left_;
      RBTransplant(z, z->left_);
    } else {
      // Find successor of subtree rooted at node z
      y = Minimum(z->right_);
      y_original_color = y->color_;
      x = y->right_;
      if (y != z->right_) {
        RBTransplant(y, y->right_);
        y->right_ = z->right_;
        y->right_->parent_ = y;
      } else {
        x->parent_ = y;
      }
      RBTransplant(z, y);
      y->left_ = z->left_;
      y->left_->parent_ = y;
      y->color_ = z->color_;
    }
    delete z;
    if (y_original_color == Color::BLACK) {
      RBDeleteFixUp(x);
    }
    return true;
  }

  /** Get all the values of elements in the Red-Black tree in order 
   * @return a vector of values of elements in the Red-Black tree
   */
  Vector<Type> GetValues() {
    Vector<Type> data;
    InorderTraversal(root_, data);
    return data;
  }

  /** For debugging */
  void Print() {
    ds::Vector<Type> tree_values = GetValues();
    if (tree_values.IsEmpty()) {
      std::cout << "Empty tree\n";
    } else {
      for (const auto& num : tree_values) {
        std::cout << num << ' ';
      }
      std::cout << '\n';
    }
  }

 private:
  /**
   * Recursively builds a new Red-Black tree
   * @param root the root of the current subtree
   * @return a pointer to the root of that subtree
   */
  Node* BuildTree(Node *other_root, Node *other_nil, Node *parent) {
    if (other_root == other_nil) {
      return nil_;
    }
    Node *node = new Node(other_root->value_, other_root->color_);
    node->parent_ = parent;
    node->left_ = BuildTree(other_root->left_, other_nil, node);
    node->right_ = BuildTree(other_root->right_, other_nil, node);
    return node;
  }

  /**
   * Recursively destroy the Red-Black tree
   * @param root the root of the tree
   */
  void DestructTree(Node *root) {
    if (root == nil_) {
      return;
    }
    DestructTree(root->left_);
    DestructTree(root->right_);
    delete root;
  }

  /** Swaps data members of two objects 
   * @param rhs the object to swap with
   */
  void Swap(RedBlackTree& rhs) {
    using std::swap;
    swap(nil_, rhs.nil_);
    swap(root_, rhs.root_);
  }

  /**
   * Left-rotates on node `x`
   * @param x the node to perform left rotation
   */
  void LeftRotate(Node *x) {
    Node *y = x->right_;
    x->right_ = y->left_;
    if (y->left_ != nil_) {
      y->left_->parent_ = x;
    }
    y->parent_ = x->parent_;
    if (x->parent_ == nil_) {
      root_ = y;
    } else if (x == x->parent_->left_) {
      x->parent_->left_ = y;
    } else {
      x->parent_->right_ = y;
    }
    y->left_ = x;
    x->parent_ = y;
  }

  /**
   * Right-rotates on node `x`
   * @param x the node to perform right rotation
   */
  void RightRotate(Node *x) {
    Node *y = x->left_;
    x->left_ = y->right_;
    if (y->right_ != nil_) {
      y->right_->parent_ = x;
    }
    y->parent_ = x->parent_;
    if (x->parent_ == nil_) {
      root_ = y;
    } else if (x == x->parent_->right_) {
      x->parent_->right_ = y;
    } else {
      x->parent_->left_ = y;
    }
    y->right_ = x;
    x->parent_ = y;
  }

  /**
   * Fix the red-black properties after inserting a new node
   * @param z the node to start to fix from
   */
  void RBInsertFixUp(Node *z) {
    while (z->parent_->color_ == Color::RED) {
      Node *grandparent = z->parent_->parent_;
      if (z->parent_ == grandparent->left_) {
        Node *uncle = grandparent->right_;
        if (uncle->color_ == Color::RED) {
          // case 1: z's parent and z's uncle are both red
          z->parent_->color_ = Color::BLACK;
          uncle->color_ = Color::BLACK;
          grandparent->color_ = Color::RED;
          z = grandparent;
        } else {
          // case 2: z's uncle is black
          if (z == z->parent_->right_) {
            z = z->parent_;
            LeftRotate(z);
          }
          // case 3: fall through from case 2 
          // Perform rotations as in AVL tree
          z->parent_->color_ = Color::BLACK;
          grandparent->color_ = Color::RED; // grandparent node is unchanged in any case
          RightRotate(grandparent);
        }
      } else {
        // symmetric
        Node *uncle = grandparent->left_;
        if (uncle->color_ == Color::RED) {
          z->parent_->color_ = Color::BLACK;
          uncle->color_ = Color::BLACK;
          grandparent->color_ = Color::RED;
          z = grandparent;
        } else {
          if (z == z->parent_->left_) {
            z = z->parent_;
            RightRotate(z);
          }
          z->parent_->color_ = Color::BLACK;
          grandparent->color_ = Color::RED;
          LeftRotate(grandparent);
        }
      }
    }
    root_->color_ = Color::BLACK;
  }

  /**
   * A helper function that replaces one subtree with another subtree
   * @param u subtree to be replaced
   * @param v subtree to replace
   */
  void RBTransplant(Node *u, Node *v) {
    if (u->parent_ == nil_) {
      root_ = v;
    } else if (u == u->parent_->left_) {
      u->parent_->left_ = v;
    } else {
      u->parent_->right_ = v;
    }
    v->parent_ = u->parent_;
  }

  /**
   * Fix the red-black properties after deleting a node
   * @param x the node to start to fix from
   */
  void RBDeleteFixUp(Node *x) {
    while (x != root_ && x->color_ == Color::BLACK) {
      if (x == x->parent_->left_) {
        // Sibling of node `x`
        Node *w = x->parent_->right_;
        // Case 1: x's sibling node `w` is red
        if (w->color_ == Color::RED) {
          w->color_ = Color::BLACK;
          x->parent_->color_ = Color::RED;
          LeftRotate(x->parent_);
          w = x->parent_->right_;
        }
        // Case 2: `w` is black and its children are black
        if (w->left_->color_ == Color::BLACK && w->right_->color_ == Color::BLACK) {
          w->color_ = Color::RED;
          x = x->parent_;
        } else {
          // Rotations as two cases in AVL tree
          if (w->right_->color_ == Color::BLACK) {
            w->left_->color_ = Color::BLACK;
            w->color_ = Color::RED;
            RightRotate(w);
            w = x->parent_->right_;
          }
          w->color_ = x->parent_->color_;
          x->parent_->color_ = Color::BLACK;
          w->right_->color_ = Color::BLACK;
          LeftRotate(x->parent_);
          x = root_; // Terminate the loop
        }
      } else {
        Node *w = x->parent_->left_;
        if (w->color_ == Color::RED) {
          w->color_ = Color::BLACK;
          x->parent_->color_ = Color::RED;
          RightRotate(x->parent_);
          w = x->parent_->left_;
        }
        if (w->right_->color_ == Color::BLACK && w->left_->color_ == Color::BLACK) {
          w->color_ = Color::RED;
          x = x->parent_;
        } else {
          if (w->left_->color_ == Color::BLACK) {
            w->right_->color_ = Color::BLACK;
            w->color_ = Color::RED;
            LeftRotate(w);
            w = x->parent_->left_;
          }
          w->color_ = x->parent_->color_;
          x->parent_->color_ = Color::BLACK;
          w->left_->color_ = Color::BLACK;
          RightRotate(x->parent_);
          x = root_; // Terminate the loop
        }
      }
    }
    x->color_ = Color::BLACK;
  }

  /**
   * Inorder traverses the Red-Black tree
   * @param root the root of the current subtree
   * @param data the list of values we've gone through
   */
  void InorderTraversal(Node *root, Vector<Type> &data) {
    if (root != nil_) {
      InorderTraversal(root->left_, data);
      data.PushBack(root->value_);
      InorderTraversal(root->right_, data);
    }
  }

  // A sentinel node for handling edge cases
  Node *nil_{};
  // The root of the tree
  Node *root_{};
};

} // namespace ds

#endif // RED_BLACK_TREE_H_