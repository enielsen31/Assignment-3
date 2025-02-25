/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Ejner Nielsen
 * Email: nielseej@oregonstate.edu
 */


#include <stdlib.h>


#include "bst.h"


/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};




/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};


/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  struct bst* new_bst = malloc(sizeof(struct bst));
  if (new_bst == NULL) {
        return NULL;  // If malloc fails, return NULL
    }
  new_bst->root = NULL;
  return new_bst;
  /*
   * FIXME:
   */
}


void free_node(struct bst_node* node){
  if(node != NULL){
    free_node(node->right);
    free_node(node->left);
    free(node);
  }
}


/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  if(bst != NULL){
    free_node(bst->root);
    free(bst);


  }
  /*
   * FIXME:
   */
  return;
}




int bst_size_node(struct bst_node* node){
  if(node == NULL){
    return 0;
  }
 return 1 + bst_size_node(node->left) + bst_size_node(node->right);
}
/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
  if(bst == NULL){
    return 0;
  }


return bst_size_node(bst->root);
}


/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
  /*
   * FIXME:
   */
   struct bst_node* new_node = malloc(sizeof(struct bst_node));
    new_node->key = key;
    new_node->value = value;
    new_node->left = new_node->right = NULL;


    if (bst->root == NULL) {
        bst->root = new_node; // Insert as root if the tree is empty
        return;
    }


    struct bst_node* current = bst->root;
    struct bst_node* parent = NULL;


    while (current != NULL) {
        parent = current;
        if (key < current->key) {
            current = current->left; // Move left if the key is smaller
//        } else {
//            current = current->right; // Move right if the key is greater
//        }
//    }
      } else if (key > current->key) {
            current = current->right;  // Move right if the key is greater
        } else {
            // If the key is equal, we don’t insert duplicate keys.
            free(new_node);
            return;
        }
    }


    if (key < parent->key) {
        parent->left = new_node; // Insert to the left of parent
    } else {
        parent->right = new_node; // Insert to the right of parent
    }


  return;
}


/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  /*
   * FIXME:
   */
         struct bst_node* current = bst->root;
    struct bst_node* parent = NULL;
    struct bst_node* successor = NULL;

    // Find the node to remove
    while (current != NULL && current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

if (current == NULL) return; // Node to remove not found

    // Case 1: Node has no children (leaf node)
    if (current->left == NULL && current->right == NULL) {
        if (parent == NULL) {
            bst->root = NULL; // Tree is now empty
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    }
    // Case 2: Node has one child
    else if (current->left == NULL || current->right == NULL) {
        struct bst_node* child = (current->left != NULL) ? current->left : current->right;

        if (parent == NULL) {
            bst->root = child; // Replace root with the child
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(current);
    }
    // Case 3: Node has two children
    else {
        // Find the in-order successor (smallest in the right subtree)
        successor = current->right;
        struct bst_node* successor_parent = current; // To keep track of successor's parent

        while (successor->left != NULL) {
            successor_parent = successor;
            successor = successor->left;
        }

        // Copy successor's data to current node
        current->key = successor->key;
        current->value = successor->value;

        // Remove the successor node
        // If successor has no right child, simply adjust its parent's link
        if (successor_parent->left == successor) {
            successor_parent->left = successor->right;
        } else {
            successor_parent->right = successor->right;
        }
        free(successor);
    }
    return;
}


/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  /*
   * FIXME:
   */
   struct bst_node* current = bst->root;
    while (current != NULL) {
        if (key == current->key) {
            return current->value; // Found the key, return its value
        } else if (key < current->key) {
            current = current->left; // Move left
        } else {
            current = current->right; // Move right
        }
    }
    return NULL; // Key not found
}


/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/


/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
 int bst_height(struct bst* bst) {
  /*
   * FIXME:
   *
   */
 if(bst->root == NULL){
         return -1;
 };
int height  = 0;
struct bst_node* current = bst->root;
while(current != NULL){
        if(current->left != NULL){
                height++;
                current = current->left;
        }else if (current->right != NULL){
                height++;
                current = current->right;
        }else{
                break;
        }
}
return height;
}
/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_path_sum(struct bst* bst, int sum) {
  /*
   * FIXME:
   */
  // Helper function to recursively check the sum along the path
   int path_sum_helper(struct bst_node* node, int current_sum) {
    if (node == NULL) return 0;
    current_sum += node->key;
    if (node->left == NULL && node->right == NULL) {
        return current_sum == sum; // If it's a leaf node, check if the sum matches
    }
    return path_sum_helper(node->left, current_sum) || path_sum_helper(node->right, current_sum);
}


return path_sum_helper(bst->root, 0);
}



/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {

   // FIXME:
   int range_sum_helper(struct bst_node* node) {
    if (node == NULL) return 0;
    int sum = 0;
    if (node->key >= lower && node->key <= upper) {
        sum += node->key;
    }
    if (node->key > lower) sum += range_sum_helper(node->left); // traverse through the left subtree if node's key is larger than lower
    if (node->key < upper) sum += range_sum_helper(node->right); // traverse through the right subtree if node's key is smaller than upper
    return sum;
}


return range_sum_helper(bst->root);

}
