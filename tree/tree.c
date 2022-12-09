#include "tree.h"

#include <stddef.h>
#include <stdio.h>

static inline uint32_t max(uint32_t h1, uint32_t h2) {
	return (h1 > h2) ? h1 : h2;
}

static inline uint32_t get_height(jem_tree_t tree) {
	return (tree) ? tree->h : 0;
}

static inline uint32_t get_id(jem_tree_t tree) {
	return (tree) ? tree->id : 0;
}

static void update_height_bal(jem_tree_t tree) {
	if (tree) {
		uint32_t lh = get_height(tree->left);
		uint32_t rh = get_height(tree->right);
		tree->bal = rh - lh;
		tree->h = max(rh, lh) + 1;
	}
}

static jem_tree_t jem_tree_balance(jem_tree_t tree) {
	if (tree->bal < -1) {
		jem_tree_t tmp = tree->left->right;
		jem_tree_t ret = tree->left;
		ret->right = tree;
		tree->left = tmp;
		ret->h = 1;
		update_height_bal(tree);
		update_height_bal(ret);
		return ret;
	} else if (tree->bal > 1) {
		jem_tree_t tmp = tree->right->left;
		jem_tree_t ret = tree->right;
		ret->left = tree;
		tree->right = tmp;
		ret->h = 1;
		update_height_bal(tree);
		update_height_bal(ret);
		return ret;
	} else {
		return tree;
	}
}

static jem_tree_t internal_get(jem_tree_t tree, uint32_t id) {
	if (tree == NULL)
		return NULL;
	if (tree->id > id)
		return internal_get(tree->left, id);
	else if (tree->id < id)
		return internal_get(tree->right, id);
	else
		return tree;
}

void *jem_tree_get(jem_tree_t tree, uint32_t id, size_t offset) {
	return (void*)((size_t)internal_get(tree, id) - (size_t)offset);
}

jem_tree_t jem_tree_insert(jem_tree_t tree, struct jem_tree_header *node) {
	if (tree == NULL) {
		tree = node;
		tree->h = 1;
		tree->bal = 0;
		tree->right = 0;
		tree->left = 0;
		return tree;
	}

	if (node->id > tree->id) {
		tree->right = jem_tree_insert(tree->right, node);
		update_height_bal(tree);
	} else if (node->id < tree->id) {
		tree->left = jem_tree_insert(tree->left, node);
		update_height_bal(tree);
	} else {
		printf("huh, inserting existing node\n");
		goto done;
	}
	if (tree->bal > 1 || tree->bal < -1)
		tree = jem_tree_balance(tree);

done:
	return tree;
}


jem_tree_t jem_tree_remove(jem_tree_t tree, uint32_t id) {

	if (tree == NULL || id == 0)
		return tree;

	if (id > tree->id) {
		tree->right = jem_tree_remove(tree->right, id);
		update_height_bal(tree);
	} else if (id < tree->id) {
		tree->left = jem_tree_remove(tree->left, id);
		update_height_bal(tree);
	} else {
		jem_tree_t new_root, new_child;
		if (tree->bal < 0) {
			new_root = tree->left;
			new_child = jem_tree_remove(tree->left, get_id(tree->left));
			if (new_root) {
				new_root->right = tree->right;
				new_root->left = new_child;
			}
		} else {
			new_root = tree->right;
			new_child = jem_tree_remove(tree->right, get_id(tree->right));
			if (new_root) {
				new_root->left = tree->left;
				new_root->right = new_child;
			}
		}
		tree = new_root;
		update_height_bal(tree);
	}

	if (tree && (tree->bal > 1 || tree->bal < -1)) {
		tree = jem_tree_balance(tree);
	}

	return tree;
}

static void print_internal(jem_tree_t tree, int offset) {
	if (tree == NULL) {
		printf("\n");
		return;
	}
	print_internal(tree->right, offset+1);
	int space_count = offset << 2;
	for (int i = 0; i < space_count; i++)
		printf(" ");
	printf("%4u\n", tree->id);
	print_internal(tree->left, offset+1);
}

void jem_tree_print_debug(jem_tree_t tree) {
	printf("-x-\n");
	print_internal(tree, 0);
	printf("-x-\n");
}
