




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
  while(is_equal(tree,tree->current->pair->key,key) != 1)
    {
      if(tree->current->right == NULL && tree->current->left == NULL) 
      {
        
        break;
      }
      if(tree->lower_than(tree->current->pair->key,key))
        tree->current = tree->current->right;
      else tree->current = tree->current->left; 
  }
  if(is_equal(tree,tree->current->pair->key,key) != 1)
    return nextTreeMap(tree);
  return tree->current->pair;
      
}

Pair * firstTreeMap(TreeMap * tree) {
  return minimum(tree->root)->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  TreeNode *auxiliar = malloc(sizeof(TreeNode));
  memcpy(auxiliar, tree->current, sizeof(TreeNode));
  if(tree->current->right != NULL)
  {
    tree->current = minimum(tree->current->right);
    return tree->current->pair;
  }
  while(tree->current->parent != NULL && tree->current->parent->pair->key <= auxiliar->pair->key)
    tree->current = tree->current->parent;
  if(tree->current->parent == NULL)
    return NULL;
  else
    return tree->current->pair;
}
