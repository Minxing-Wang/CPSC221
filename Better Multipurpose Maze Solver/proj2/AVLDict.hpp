//AVLDict.hpp
#ifndef _AVLDICT_HPP
#define _AVLDICT_HPP

#include "PredDict.hpp"

// An implementation of a dictionary ADT as an AVL tree.
//
class AVLDict : public PredDict
  {
  public:
    AVLDict();
    ~AVLDict();
    bool find(MazeState *key, MazeState *&pred);
    void add(MazeState *key, MazeState *pred);

  private:
    struct node {
      MazeState *key;
      MazeState *data;
      int height; // Avoid recomputation of subtree height.
      node *left;
      node *right;
    };

    node *root;

    // The next two variables are just to collect statistics on the
    // number of probes required for each call to find().
    int *depth_stats; // probe_stats[i] should be how often i probes needed
    const static int MAX_STATS = 30; // How big to make the array.
    // And be sure to call this function in your find function (or helper)
    // to record the depth that the find went to:
    void record_stats(int depth);

    void destructor_helper(node * x);
    // These are helper functions just like in your lab...
    inline int height(node *x) { return (x==NULL) ? -1 : x->height; }
    bool update_height(node *x);
    void rotate_left(node *&a);
    void rotate_right(node *&b);
    void doubleRotateLeft(node *&c);
    void doubleRotateRight(node *&d);

    void balance(node *&x);

    void add_helper(node * temp, node* &root);

  };

#endif

