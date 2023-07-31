#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_BINARY_TREE_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_BINARY_TREE_H_

#include <iostream>
#include <limits>

namespace s21 {
template <class K, class Compare = std::less<K>>
class BinaryTree {
 public:
  using key_type = K;
  using value_type = K;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

 public:
  class Iterator {
   public:
    using tree_node = typename BinaryTree<K>::BTNode;

    Iterator() : ptr(new BTNode()) {}
    Iterator(tree_node *btNode) : ptr(btNode) {}
    Iterator(const Iterator &other) : ptr(other.ptr) {}
    ~Iterator() {
      if (ptr) ptr = nullptr;
    }

    tree_node *get() { return ptr; }

    value_type operator*() const { return ptr->val; }

    Iterator &operator++() {
      IteratorIncremented();
      return *this;
    }

    Iterator &operator--() {
      IteratorDecremented();
      return *this;
    }

    Iterator operator++(int) const {
      Iterator *prev = *this;
      IteratorIncremented();
      return *prev;
    }

    Iterator operator--(int) const {
      Iterator *prev = *this;
      IteratorDecremented();
      return *prev;
    }

    bool operator==(const Iterator &other) { return ptr == other.ptr; }

    bool operator!=(const Iterator &other) {
      return (ptr->is_fake != other.ptr->is_fake || ptr->val != other.ptr->val);
    }

   protected:
    tree_node *ptr;

    void IteratorIncremented() {
      if (ptr->right) {
        ptr = ptr->right;
        while (!ptr->is_fake && ptr->left) {
          ptr = ptr->left;
        }
      } else {
        BTNode *buff = ptr;
        ptr = ptr->parent;
        while (buff == ptr->right && !ptr->is_fake) {
          buff = ptr;
          ptr = ptr->parent;
        }
      }
    }
    void IteratorDecremented() {
      if (ptr->left) {
        ptr = ptr->left;
        while (ptr->right) {
          ptr = ptr->right;
        }
      } else {
        BTNode *buff = ptr;
        ptr = ptr->parent;
        while (buff == ptr->left) {
          buff = ptr;
          ptr = ptr->parent;
        }
      }
    }
    friend class BinaryTree;
  };

  class ConstIterator : public Iterator {
   public:
    using tree_node = typename BinaryTree<K>::BTNode;

    ConstIterator() : Iterator() {}
    explicit ConstIterator(const tree_node *btNode) : Iterator(btNode) {}
    ~ConstIterator() = default;
  };

 public:
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  iterator begin() { return iterator(MinNode(root)); }

  iterator end() { return iterator(fake_node); }

  size_type size() { return bt_size; }

  struct BTNode {
    value_type val;
    struct BTNode *left;
    struct BTNode *right;
    struct BTNode *parent;
    bool is_fake = false;

    BTNode() : left(nullptr), right(nullptr), parent(nullptr) {}

    explicit BTNode(value_type x)
        : val(x), left(nullptr), right(nullptr), parent(nullptr) {}

    BTNode(BTNode &btNode)
        : val(btNode.val),
          left(btNode.left),
          right(btNode.right),
          parent(btNode.parent) {}
  };

  BinaryTree() : root(nullptr), fake_node(new BTNode()), bt_size(0) {
    MakeRootFake();
  }

  BinaryTree(std::initializer_list<value_type> const &items) : BinaryTree() {
    for (auto i = items.begin(); i != items.end(); i++) {
      insert(*i);
    }
  }

  BinaryTree(const BinaryTree &other) : BinaryTree() {
    root = CopyTree(other.root);
    bt_size = other.bt_size;
  }

  BinaryTree(BinaryTree &&binaryTree) noexcept : BinaryTree() {
    swap(binaryTree);
  }

  ~BinaryTree() {
    if (!root->is_fake) RemoveNode(root);
    delete fake_node;
    root = nullptr;
    fake_node = nullptr;
    bt_size = 0;
  }

  BinaryTree &operator=(BinaryTree &&binaryTree) noexcept {
    swap(binaryTree);
    return *this;
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    int insertion_successful = false;
    if (FindNode(value) != nullptr) {
      return std::make_pair(end(), insertion_successful);
    }

    auto *newNode = new BTNode(value);
    if (root->is_fake) {
      root = newNode;
      insertion_successful = true;
    } else {
      BTNode *tmp = root;
      BTNode *result = tmp;
      while (!insertion_successful && tmp) {
        if (value < tmp->val) {
          if (tmp->left) {
            tmp = tmp->left;
          } else {
            tmp->left = newNode;
            newNode->parent = tmp;
            insertion_successful = true;
          }
        } else if (tmp->val < value) {
          if (tmp->right && !tmp->right->is_fake) {
            tmp = tmp->right;
          } else {
            tmp->right = newNode;
            newNode->parent = tmp;
            insertion_successful = true;
          }
        }
      }
      root = result;
    }
    if (insertion_successful) {
      bt_size++;
      InsertFakeNode(root);
    }
    return std::make_pair(iterator(newNode), true);
  }

  BTNode *FindNode(value_type value) {
    BTNode *tmp = root;
    while (tmp && !tmp->is_fake) {
      if (value < tmp->val) {
        tmp = tmp->left;
      } else if (tmp->val < value) {
        tmp = tmp->right;
      } else
        return tmp;
    }
    return nullptr;
  }

  void swap(BinaryTree &other) {
    std::swap(root, other.root);
    std::swap(fake_node, other.fake_node);
    std::swap(bt_size, other.bt_size);
  }

  void PrintTreeMain() { PrintTreeSupportive(root, "root", 0); }

  void PrintTreeSupportive(BTNode *btNode, const char *dir, int level) {
    if (btNode && !btNode->is_fake) {
      printf("lvl %d %s = %d\n", level, dir, btNode->val);
      PrintTreeSupportive(btNode->left, "left", level + 1);
      PrintTreeSupportive(btNode->right, "right", level + 1);
    }
  }

  bool empty() { return root->is_fake; }

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(BTNode) / 2;
  }

  void clear() {
    if (!empty()) {
      RemoveNode(root);
      MakeRootFake();
      bt_size = 0;
    }
  }

  void merge(BinaryTree &other) {
    BinaryTree<K, Compare> mergedTree;

    for (const auto &value : *this) {
      mergedTree.insert(value);
    }

    for (const auto &value : other) {
      mergedTree.insert(value);
    }

    *this = std::move(mergedTree);
    other.clear();
  }

  iterator find(const value_type &value) {
    BTNode *tmp = FindNode(value);
    return iterator(tmp);
  }

  bool contains(const value_type &value) { return FindNode(value) != nullptr; }

  void erase(iterator pos) {
    if (pos == end()) {
      return;
    }

    BTNode *node = pos.ptr;
    BTNode *parent = node->parent;

    if (node->left == nullptr && node->right == nullptr) {
      if (parent->left == node) {
        parent->left = nullptr;
      } else {
        parent->right = nullptr;
      }
    } else if (node->left == nullptr) {
      if (parent == nullptr) {
        root = node->right;
        root->parent = nullptr;
      } else if (parent->left == node) {
        parent->left = node->right;
        node->right->parent = parent;
      } else {
        parent->right = node->right;
        node->right->parent = parent;
      }
    } else if (node->right == nullptr) {
      if (parent == nullptr) {
        root = node->left;
        root->parent = nullptr;
      } else if (parent->left == node) {
        parent->left = node->left;
        node->left->parent = parent;
      } else {
        parent->right = node->left;
        node->left->parent = parent;
      }
    } else {
      BTNode *successor = MinNode(node->right);

      if (successor->parent != node) {
        BTNode *successorParent = successor->parent;
        successorParent->left = successor->right;

        if (successor->right != nullptr) {
          successor->right->parent = successorParent;
        }

        successor->right = node->right;
        successor->right->parent = successor;
      }

      if (parent == nullptr) {
        root = successor;
        root->parent = nullptr;
      } else if (parent->left == node) {
        parent->left = successor;
        successor->parent = parent;
      } else {
        parent->right = successor;
        successor->parent = parent;
      }

      successor->left = node->left;
      successor->left->parent = successor;
    }

    delete node;
    --bt_size;
  }

 private:
  BTNode *root;
  BTNode *fake_node;
  size_type bt_size{};

  BTNode *CopyTree(const BTNode *btNode) {
    if (btNode == nullptr) return nullptr;
    auto *newNode = new BTNode(btNode->val);
    newNode->parent = btNode->parent;  // !!!
    if (btNode->left) newNode->left = CopyTree(btNode->left);
    if (btNode->right && !btNode->right->is_fake) {
      newNode->right = CopyTree(btNode->right);
    } else if (btNode->right && btNode->right->is_fake)
      InsertFakeNode(newNode);
    return newNode;
  }

  void MakeRootFake() {
    fake_node->is_fake = true;

    fake_node->parent = fake_node;
    fake_node->left = fake_node;
    fake_node->right = fake_node;
    root = fake_node;
  }

  void InsertFakeNode(BTNode *btNode) {
    BTNode *tmp = MaxNode(btNode);
    tmp->right = fake_node;
    fake_node->parent = tmp;
  }

  void RemoveNode(BTNode *btNode) {
    if (btNode->left && !btNode->left->is_fake) {
      RemoveNode(btNode->left);
      btNode->left = nullptr;
    }
    if (btNode->right && !btNode->right->is_fake) {
      RemoveNode(btNode->right);
      btNode->right = nullptr;
    }
    delete btNode;
    btNode = nullptr;
  }

  BTNode *MinNode(BTNode *btNode) {
    while (!btNode->is_fake && btNode->left) {
      btNode = btNode->left;
    }
    return btNode;
  }

  BTNode *MaxNode(BTNode *btNode) {
    while (btNode->right && !btNode->right->is_fake) {
      btNode = btNode->right;
    }
    return btNode;
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_BINARY_TREE_H_
