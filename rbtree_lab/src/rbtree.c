#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  // TODO: initialize struct if needed

  // rbtree라고 이름 붙여진 구조체를 생성한다. 이때 동적 메모리 할당을 통해 메모리를 할당한다.
  rbtree *p = (rbtree *)calloc(1,sizeof(rbtree));

  p->nil = (node_t*)calloc(1,sizeof(node_t));
  p->nil->color = RBTREE_BLACK;
  p->nil->key = 0;
  p->nil->left = p->nil;
  p->nil->right = p->nil;
  p->nil->parent = NULL;
  p->root = p->nil;

  return p;
}

void rotate_left(rbtree *tree, node_t *target){
    // 1) 오른쪽 자식과 그 왼쪽 서브트리 저장
    node_t *newParent = target->right;
    node_t *remainNode  = newParent->left;

    // 2) 남은 서브트리를 target의 오른쪽 자식으로 연결
    target->right = remainNode;
    if(remainNode != tree->nil){
      remainNode->parent = target;
    }

    // 3) newParent를 target의 위치에 끼워 넣기
    newParent->parent = target->parent;
    if (target->parent == tree->nil){
      tree->root = newParent;
    }else if(target == target->parent->left){
      target->parent->left = newParent;
    }else{
      target->parent->right = newParent;
    }

    // target을 newParent의 왼쪽 자식으로 이동
    newParent->left = target;
    target->parent = newParent;
}

void rotate_right(rbtree *tree, node_t *target){
  // 왼쪽 자식과 그 오른쪽 서브트리 저장
  node_t *newParent = target->left;
  node_t *remainNode = newParent->right;

  // 남은 서브트리를 target의 왼쪽 자식으로 연결
  target->left = remainNode;
  if (remainNode != tree->nil){
    remainNode->parent = target;
  }

  // newParent를 target의 위치에 끼워 넣기
  newParent->parent = target->parent;
  if (target->parent == tree->nil){
    tree->root = newParent;
  }else if(target == target->parent->left){
    target->parent->left = newParent;
  }else{
    target->parent->right = newParent;
  }

  // target을 newParent의 오른쪽 자식으로 이동
  newParent->right = target;
  target->parent = newParent;
}

void rbtree_insert_fix_up(rbtree *t, node_t *current){
  while (current->parent->color == RBTREE_RED){
    if (current->parent == current->parent->parent->left){
      node_t *uncle = current->parent->parent->right;

      if (uncle->color == RBTREE_RED){
        current->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        current->parent->parent->color = RBTREE_RED;
        current = current->parent->parent;
      }else{
        if (current == current->parent->right){
          current = current->parent;
          rotate_left(t, current);
        }
        current->parent->color = RBTREE_BLACK;
        current->parent->parent = RBTREE_RED;
        rotate_right(t, current->parent->parent);
      }
    }else{
      node_t *uncle = current->parent->parent->left;

      if (uncle->color == RBTREE_RED){
        current->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        current->parent->parent->color = RBTREE_RED;
        current = current->parent->parent;
      }else{
        if (current == current->parent->left){
          current = current->parent;
          rotate_right(t, current);
        }
        current->parent->color = RBTREE_BLACK;
        current->parent->parent = RBTREE_RED;
        rotate_left(t, current->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

void delete_node(node_t *node, node_t *nil){
  if (node == nil) return;

  delete_node(node->left, nil);
  delete_node(node->right, nil);
  free(node);
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  if (t==NULL) return;

  delete_node(t->root, t->nil);
  free(t->nil);
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *current = t->root;
  node_t *parent = t->nil;
  node_t *newNode = (node_t *) malloc(sizeof(node_t));
  newNode->key = key;

  while (current != t->nil){
    parent = current;
    if (key < current->key){
      current = current->left;
    }else{
      current = current->right;
    }
  }

  newNode->parent = parent;
  if (parent == t->nil){
    t->root = newNode;
  }else if(newNode->key < parent->key){
    parent->left = newNode;
  }else{
    parent->right = newNode;
  }

  newNode->left = t->nil;
  newNode->right = t->nil;
  newNode->color = RBTREE_RED;

  // insert fixUp 함수 구현
  rbtree_insert_fix_up(t, newNode);

  return t->root;
  // return newNode;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}

// void main(){
//   rbtree *t = new_rbtree();
//   node_t *p = rbtree_insert(t, 5);
//   delete_rbtree(t);
// }