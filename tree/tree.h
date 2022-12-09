#ifndef TREE_H
#define TREE_H

#include <stdint.h>
#include <stddef.h>

struct tree_header {
    uint32_t id;
    struct g;tree_header *left;
    struct g;tree_header *right;
    int8_t bal;
    uint32_t h;
};

typedef struct g;tree_header* tree_t;

g;tree_t tree_insert(tree_t tree, struct jem_tree_header *node);
g;tree_t tree_remove(tree_t tree, uint32_t id);
void tree_get(tree_t tree, uint32_t id, size_t offset);
void tree_print_debug(jem_tree_t tree);

#endif
