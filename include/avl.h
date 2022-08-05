#ifndef AVL_H_
#define AVL_H_

#include "bst.h"

#include <algorithm>

namespace ds {
template<typename Type>
class AVL : public BST<Type> {
 public:
  using typename BST<Type>::Node;

  /** Default constructor */
  AVL() : BST<Type>() {}

  /**
   * Construct a new AVL tree from a list of elements
   * @param other the list of elements
   */
  AVL(Vector<Type>& other) {
    for (const auto& ele : other) {
      Insert(ele);
    }
  }

  /**
   * Construct a new AVL tree using an initializer list
   * @param data the list of elements to initialize
   */
  AVL(std::initializer_list<Type> data) {
    for (const auto& ele : data) {
      Insert(ele);
    }
  }

  /** Copy constructor 
   * @param other the source AVL tree to construct from
   */
  AVL(const AVL& other) : BST<Type>(other) {}

  /** Move constructor 
   * @param other the source AVL tree to move from
   */
  AVL(AVL&& other) : BST<Type>(std::move(other)) {}

  /** Destructor */
  ~AVL() = default;

  /** Copy assignment operator 
   * @param other the source AVL tree to assign from
   * @return a reference to the AVL tree assigned
   */
  AVL& operator=(const AVL& other) {
    AVL copy(other);
    copy.Swap(*this);
    return *this;
  }

  /** Move assignment operator 
   * @param the source AVL tree to move from
   * @return a reference to the AVL tree assigned
   */
  AVL& operator=(AVL&& other) noexcept {
    other.Swap(*this);
    return *this;
  }

  /**
   * Inserts a new element into the AVL tree
   * @param value the value of the element to insert
   * @return a pointer to the newly inserted node
   */
  Node* Insert(const Type& value) {
    auto node = BST<Type>::Insert(value);
    Rebalance(node);
    return node;
  }

  /**
   * Deletes a value from the AVL tree
   * @param value the value to delete
   * @return true if deletion succeeds; otherwise, false
   */
  bool Delete(const Type& value) {
    Node* node = BST<Type>::Search(value);
    if (node == nullptr) {
      return false;
    }
    // the parent of the physically deleted node, used for rebalacing
    Node* action_node;
    if (node->left_ == nullptr) {
      action_node = node->parent_;
      BST<Type>::Transplant(node, node->right_);
    } else if (node->right_ == nullptr) {
      action_node = node->parent_;
      BST<Type>::Transplant(node, node->left_);
    } else {
      Node* successor = BST<Type>::Minimum(node->right_);
      action_node = successor->parent_;
      if (successor->parent_ != node) {
        BST<Type>::Transplant(successor, successor->right_);
        successor->right_ = node->right_;
        successor->right_->parent_ = successor;
      }
      BST<Type>::Transplant(node, successor);
      successor->left_ = node->left_;
      successor->left_->parent_ = successor;
    }
    delete node;
    Rebalance(action_node);
    return true;
  }

 private:
 /**
  * @param node the node to get height
  * @return the height of the node
  */
  int Height(Node* node) {
    if (node == nullptr) {
      return -1;
    }
    return node->height_;
  }

  /**
   * Calculates the height of a node
   * @param node the node to calculate the height
   */
  void UpdateHeight(Node* node) {
    node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;
  }

  /**
   * Left-rotates a node `x`
   * @param x the node to perform left rotation
   */
  void LeftRotate(Node* x) {
    Node* y = x->right_;
    y->parent_ = x->parent_;
    if (y->parent_ == nullptr) {
      // resolve name look-up problem
      BST<Type>::root_ = y;
    } else {
      if (y->parent_->left_ == x) {
        y->parent_->left_ = y;
      } else if (y->parent_->right_ == x) {
        y->parent_->right_ = y;
      }
    }
    x->right_ = y->left_;
    if (x->right_ != nullptr) {
      x->right_->parent_ = x;
    }
    y->left_ = x;
    x->parent_ = y;
    UpdateHeight(x);
    UpdateHeight(y);
  }

  /**
   * Right-rotates a node `x`
   * @param x the node to perform right rotation
   */
  void RightRotate(Node* x) {
    Node* y = x->left_;
    Node* p = x->parent_;
    y->parent_ = x->parent_;
    if (p == nullptr) {
      // resolve name look-up problem
      BST<Type>::root_ = y;
    } else {
      if (p->left_ == x) {
        p->left_ = y;
      } else if (p->right_ == x) {
        p->right_ = y;
      }
    }
    x->left_ = y->right_;
    if (x->left_ != nullptr) {
      x->left_->parent_ = x;
    }
    y->right_ = x;
    x->parent_ = y;
    UpdateHeight(x);
    UpdateHeight(y);
  }

  /**
   * Checks the height of a node and rebalances if it violates the AVL tree property
   * @param node the node to perform rebalancing
   */
  void Rebalance(Node* node) {
    while (node != nullptr) {
      UpdateHeight(node);
      if (Height(node->left_) >= 2 + Height(node->right_)) {
        if (Height(node->left_->left_) >= Height(node->left_->right_)) {
          RightRotate(node);
        } else {
          LeftRotate(node->left_);
          RightRotate(node);
        }
      } else if (Height(node->right_) >= 2 + Height(node->left_)) {
        if (Height(node->right_->right_) >= Height(node->right_->left_)) {
          LeftRotate(node);
        } else {
          RightRotate(node->right_);
          LeftRotate(node);
        }
      }
      node = node->parent_;
    }
  }

};

} // namespace ds

#endif //AVL_H_