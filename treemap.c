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

  TreeMap *local=malloc(sizeof(TreeMap));
  local->current=NULL;
  local->root=NULL;
  
  local->lower_than = lower_than;
    return local;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {

   tree->current=tree->root;
  while(tree->current!=NULL){
    int resultado=tree->lower_than(key,tree->current->pair->key);
    if(is_equal(tree,key, tree->current->pair->key)==0){
      if(resultado==1)
      {
        if(tree->current->left==NULL)
        {
          TreeNode *nodo=createTreeNode(key, value);
          nodo->parent=tree->current;
          tree->current->left=nodo;
          tree->current=tree->current->left;
          return;
        }
        tree->current=tree->current->left;
      }
      else if(resultado==0){
        if(tree->current->right==NULL){
          TreeNode *nodo=createTreeNode(key, value);
          nodo->parent=tree->current;
          tree->current->right=nodo;
          tree->current=tree->current->right;
          return;
        }
        tree->current=tree->current->right;
        
      }
  }
    else if(is_equal(tree,key, tree->current->pair->key)==1){
      return ;  
      
    }
    
  }
  return;

}

TreeNode * minimum(TreeNode * x){

if(x->left==NULL){
  return x;
}

  while(1){

    if(x->left==NULL)
    {
      return x;
    }
    x=x->left;
  }
  

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {


  if(node->left==NULL && node->right==NULL){
    TreeNode *aux=node->parent;
    int r=tree->lower_than(node->pair->key,aux->pair->key);
    if(r==1){
      aux->left=NULL;
      return;
    }
    else{
      aux->right=NULL;
      return;
    }
  }
  if(node->left!=NULL || node->right!=NULL){
    TreeNode *aux=node->parent;
    int r=tree->lower_than(node->pair->key,aux->pair->key);
    if(r==1){
      aux->left=NULL;
    }
    else{
      aux->right=NULL;
    }

    if(node->left!=NULL)
    {
      aux->left=node->left;
      return;
    }
    if(node->right!=NULL){
      aux->right=node->right;
        return;
    }
    
  }

  
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {

  tree->current=tree->root;
  while(tree->current!=NULL){
    int resultado=tree->lower_than(key,tree->current->pair->key);
    if(is_equal(tree,key, tree->current->pair->key)==0){
      if(resultado==1)
      {
        tree->current=tree->current->left;
      }
      else if(resultado==0){
        tree->current=tree->current->right;
        
      }
  }
    else if(is_equal(tree,key, tree->current->pair->key)==1){
      return tree->current->pair;  
      
    }
    
  }
  
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
