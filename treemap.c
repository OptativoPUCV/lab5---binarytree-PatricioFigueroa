#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap * tree = (TreeMap *)malloc(sizeof(TreeMap));
  tree->lower_than = lower_than;
  tree->root = NULL;
  return tree;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  tree->current = tree->root;
  while(is_equal(tree,tree->current->pair->key,key) != 1)
    {
      if(tree->current->right == NULL && tree->current->left == NULL) 
      {
        if(tree->lower_than(tree->current->pair->key,key))
        {
          tree->current->right = createTreeNode(key, value) ;
          tree->current->right->parent = tree->current;
          tree->current = tree->current->right;
        }
        else
        {
          tree->current->left = createTreeNode(key, value) ;
          tree->current->left->parent = tree->current;
          tree->current = tree->current->left;
        }
        return;
      }
      if(tree->lower_than(tree->current->pair->key,key))
        tree->current = tree->current->right;
      else tree->current = tree->current->left;
      
    }
  
}

TreeNode * minimum(TreeNode * x){
    while(x->left != NULL)
        x = x->left;
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(node->left == NULL)
  {
    if(node->right == NULL)
    {
      if(node->parent->right == node)
        node->parent->right = NULL;
      else node->parent->left = NULL;
      return;
    }
    if(node->pair->key > node->parent->pair->key)
    {
      node->right->parent = node->parent;
      node->parent->right = node->right;
      return;
    }
    else
    {
      node->right->parent = node->parent;
      node->parent->left = node->right;
      return;
    }
  }
  if(node->right == NULL)
  {
    if(node->pair->key > node->parent->pair->key)
    {
      node->left->parent = node->parent;
      node->parent->right = node->left;
      return;
    }
    else
    {
      node->left->parent = node->parent;
      node->parent->left = node->left;
      return;
    }
  }
  TreeNode *auxiliar = minimum(node->right);
  node->pair->key = auxiliar->pair->key;
  node->pair->value = auxiliar->pair->value;
  removeNode(tree, auxiliar);
  }

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return ;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);
}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  tree->current = tree->root;
  while(is_equal(tree,tree->current->pair->key,key) != 1)
    {
      if(tree->current->right == NULL && tree->current->left == NULL) 
      {
        return NULL;
      }
      if(tree->lower_than(tree->current->pair->key,key))
        tree->current = tree->current->right;
      else tree->current = tree->current->left;
    }
    return tree->current->pair;
}


Pair * upperBound(TreeMap * tree, void* key) {
   tree->current = tree->root;
   TreeNode *aux = tree->root;
  while(is_equal(tree,tree->current->pair->key,key) != 1)
    {
      if(tree->current->right == NULL && tree->current->left == NULL) 
        break;
      if(tree->lower_than(tree->current->pair->key,key))
      {
        aux= tree->current;
        tree->current = tree->current->right;
      }
      else tree->current = tree->current->left; 
  }
  if(is_equal(tree,tree->current->pair->key,key) != 1)
    return aux->pair;
  return tree->current->pair;
}

Pair * firstTreeMap(TreeMap * tree) {
  return minimum(tree->root)->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    TreeNode *auxiliar = tree->current;
  if (auxiliar->right != NULL) {
    tree->current = minimum(auxiliar->right);
    return tree->current->pair;
  }
  while (auxiliar->parent != NULL && auxiliar == auxiliar->parent->right) {
    auxiliar = auxiliar->parent;
  }
  auxiliar = auxiliar->parent;
  if (auxiliar == NULL) {
    tree->current = NULL;
    return NULL;
  } else {
    tree->current = auxiliar;
    return auxiliar->pair;
  }
}


