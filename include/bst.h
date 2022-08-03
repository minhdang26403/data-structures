#ifndef BST_H_
#define BST_H_

namespace ds {
template<typename Type>
struct Node {
  Type value_;
  Node* parent_;
  Node* left_;
  Node* right_;

  Node(const Type& value, Node* parent=nullptr, Node* left=nullptr, Node *right=nullptr)
    : value_(value), parent_(parent), left_(left), right_(right) {}
};

template<typename Type>
class BST {
 public:
  using Pointer = Node<Type>*;
  BST() = default;
  ~BST() {
    DestructTree(root_);
  }

  BST(const BST& other) = delete;
  BST& operator=(const BST& other) = delete;

  /**
   * @return a pointer to the root of the tree
   */
  Pointer GetRoot() {
    return root_;
  }

  /**
   * Searchs the BST for a value
   * @param value the value to search
   * @return the pointer to the tree node containing the value
   */
  Pointer Search(const Type& value) {
    Pointer node = root_;
    while (node != nullptr && node->value_ != value) {
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
  Pointer Minimum(Pointer node) {
    while (node != nullptr && node->left_ != nullptr) {
      node = node->left_;
    }
    return node;
  }

  /**
   * Finds the the maximum value of the subtree rooted at a node
   * @param node the root of that subtree
   * @return the pointer to the tree node containing the maximum value
   */
  Pointer Maximum(Pointer node) {
    while (node != nullptr && node->right_ != nullptr) {
      node = node->right_;
    }
    return node;
  }

  /**
   * Finds the successor (next greater) of a node
   * @param node the node to find its successor
   * @return a pointer to the successor node
   */
  Pointer Successor(Pointer node) {
    if (node->right_ != nullptr) {
      return Minimum(node->right_);
    }
    while (node->parent_ != nullptr && node != node->parent_->right_) {
      node = node->parent_;
    }
    return node->parent_;
  }

  /**
   * Finds the predecessor of a node
   * @param node the node to find its predecessor
   * @return a pointer to the predecessor node
   */
  Pointer Predecessor(Pointer node) {
    if (node->left_ != nullptr) {
      return Maximum(node->left_);
    }
    while (node->parent_ != nullptr && node != node->parent_->left_) {
      node = node->parent_;
    }
    return node->parent_;
  }

  /**
   * Inserts a new element into the binary search tree
   * @param value the value of the element to insert
   */
  void Insert(const Type& value) {
    auto new_node = new Node<Type>(value);
    Pointer parent = nullptr;
    Pointer cur = root_;
    while (cur != nullptr) {
      parent = cur;
      if (value < cur->value_) {
        cur = cur->left_;
      } else {
        cur = cur->right_;
      }
    }
    new_node->parent_ = parent;
    if (parent == nullptr) {
      root_ = new_node;
    } else if (value < parent->value_) {
      parent->left_ = new_node;
    } else {
      parent->right_ = new_node;
    }
  }

  /**
   * Deletes a value from the BST
   * @param value the value to delete
   * @return true if deletion succeeds; otherwise, false
   */
  bool Delete(const Type& value) {
    Pointer node = Search(value);
    if (node == nullptr) {
      return false;
    }
    if (node->left_ == nullptr) {
      Transplant(node, node->right_);
    } else if (node->right_ == nullptr) {
      Transplant(node, node->left_);
    } else {
      Pointer successor = Minimum(node->right_);
      if (successor->parent_ != node) {
        Transplant(successor, successor->right_);
        successor->right_ = node->right_;
        successor->right_->parent_ = successor;
      }
      Transplant(node, successor);
      successor->left_ = node->left_;
      successor->left_->parent_ = successor;
    }
    delete node;
    return true;
  }

 private:
  /**
   * A helper function that replaces one subtree with another subtree
   * @param u subtree to be replaced
   * @param v subtree to replace
   */
  void Transplant(Pointer u, Pointer v) {
    if (u->parent_ == nullptr) {
      root_ = v;
    } else if (u->parent_->left_ == u) {
      u->parent_->left_ = v;
    } else {
      u->parent_->right_ = v;
    }
    if (v != nullptr) {
      v->parent_ = u->parent_;
    }
  }

  /**
   * Recursively destroy the BST
   * @param root the root of the tree
   */
  void DestructTree(Pointer root) {
    if (root == nullptr) {
      return;
    }
    DestructTree(root->left_);
    DestructTree(root->right_);
    delete root;
  }
  // The root of the tree
  Pointer root_{};
};

} // namespace ds

#endif // BST_H_