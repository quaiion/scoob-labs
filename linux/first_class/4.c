#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

enum COLORS {
    RED = 'R',
    BLUE = 'B',
    NONE = 'N'
};

struct x_node_t {
    struct x_node_t *high;
    struct x_node_t *low;
    struct y_node_t *subbranch;
    int key;
};

struct y_node_t {
    struct y_node_t *high;
    struct y_node_t *low;
    int key;
    bool col;   /* RED <=> true; BLUE <=> false */
};

struct colbuf_t {
    char *data;
    size_t cap;
    size_t size;
};

struct x_node_t *new_x_node(int x_key);
struct y_node_t *new_y_node(int y_key, bool col);

void free_y_branch(struct y_node_t *node);
void free_branch(struct x_node_t *node);

char find_point(struct x_node_t *root, int x_key, int y_key);
/** separated to prevent stack overflow */
struct y_node_t *find_y_node(struct y_node_t *node, int y_key);
struct x_node_t *find_x_node(struct x_node_t *node, int x_key);

void color_point(struct x_node_t *node, int x_key, int y_key, bool col);
/** same thing */
void upsert_y_node(struct y_node_t *node, int y_key, bool col);
struct x_node_t *upsert_x_node(struct x_node_t *node, int x_key);

struct colbuf_t *colbuf_create(size_t init_cap);
void colbuf_destroy(struct colbuf_t *buf);
void colbuf_push(struct colbuf_t *buf, char col);
void colbuf_resize(struct colbuf_t *buf);
void colbuf_dump(struct colbuf_t *buf);

int main() {
    unsigned n = 0;
    struct colbuf_t *buf = colbuf_create(16);
    struct x_node_t *root = new_x_node(0);
    scanf("%u", &n);
    for (unsigned i = 0; i < n; ++i) {
        int x = 0, y = 0, opcode = 0;
        scanf("%u%d%d", &opcode, &x, &y);
        assert(opcode == 1 || opcode == 2);
        if (opcode == 1) {
            char col_sym = 0;
            scanf(" %c", &col_sym);
            assert(col_sym == RED || col_sym == BLUE);
            if (col_sym == RED) {
                color_point(root, x, y, true);
            } else {
                color_point(root, x, y, false);
            }
        } else {
            colbuf_push(buf, find_point(root, x, y));
        }
    }
    colbuf_dump(buf);
    colbuf_destroy(buf);
    free_branch(root);
    return 0;
}

struct x_node_t *new_x_node(int x_key) {
    struct x_node_t *node = calloc(1, sizeof(struct x_node_t));
    assert(node);
    node->key = x_key;
    return node;
}

struct y_node_t *new_y_node(int y_key, bool col) {
    struct y_node_t *node = calloc(1, sizeof(struct y_node_t));
    assert(node);
    node->key = y_key;
    node->col = col;
    return node;
}

void free_y_branch(struct y_node_t *node) {
    if (node == NULL) {
        return;
    }
    free_y_branch(node->high);
    free_y_branch(node->low);
    free(node);
}

void free_branch(struct x_node_t *node) {
    if (node == NULL) {
        return;
    }
    free_y_branch(node->subbranch);
    free_branch(node->high);
    free_branch(node->low);
    free(node);
}

struct x_node_t *upsert_x_node(struct x_node_t *node, int x_key) {
    assert(node != NULL);
    if (x_key > node->key) {
        if (node->high == NULL) {
            node->high = new_x_node(x_key);
            return node->high;
        }
        return upsert_x_node(node->high, x_key);
    }
    if (x_key < node->key) {
        if (node->low == NULL) {
            node->low = new_x_node(x_key);
            return node->low;
        }
        return upsert_x_node(node->low, x_key);
    }
    return node;
}

void upsert_y_node(struct y_node_t *node, int y_key, bool col) {
    assert(node != NULL);
    if (y_key > node->key) {
        if (node->high == NULL) {
            node->high = new_y_node(y_key, col);
            return;
        }
        upsert_y_node(node->high, y_key, col);
    }
    else if (y_key < node->key) {
        if (node->low == NULL) {
            node->low = new_y_node(y_key, col);
            return;
        }
        upsert_y_node(node->low, y_key, col);
    } else {
        node->col = col;
    }
}

void color_point(struct x_node_t *root, int x_key, int y_key, bool col) {
    struct x_node_t *x_node = upsert_x_node(root, x_key);
    if (x_node->subbranch == NULL) {
        x_node->subbranch = new_y_node(y_key, col);
        return;
    }
    upsert_y_node(x_node->subbranch, y_key, col);
}

struct x_node_t *find_x_node(struct x_node_t *node, int x_key) {
    if (node == NULL) {
        return NULL;
    }
    if (x_key > node->key) {
        return find_x_node(node->high, x_key);
    }
    if (x_key < node->key) {
        return find_x_node(node->low, x_key);
    }
    return node;
}

struct y_node_t *find_y_node(struct y_node_t *node, int y_key) {
    if (node == NULL) {
        return NULL;
    }
    if (y_key > node->key) {
        return find_y_node(node->high, y_key);
    }
    if (y_key < node->key) {
        return find_y_node(node->low, y_key);
    }
    return node;
}

char find_point(struct x_node_t *root, int x_key, int y_key) {
    struct x_node_t *x_node = find_x_node(root, x_key);
    if (x_node == NULL) {
        return NONE;
    }
    struct y_node_t *y_node = find_y_node(x_node->subbranch, y_key);
    if (y_node == NULL) {
        return NONE;
    }
    if (y_node->col == true) {
        return RED;
    }
    return BLUE;
}

struct colbuf_t *colbuf_create(size_t init_cap) {
    struct colbuf_t *buf = malloc(sizeof(*buf));
    assert(buf);
    buf->data = malloc(sizeof(char) * init_cap);
    assert(buf->data);
    buf->cap = init_cap;
    buf->size = 0;
    return buf;
}

void colbuf_destroy(struct colbuf_t *buf) {
    free(buf->data);
    free(buf);
}

void colbuf_push(struct colbuf_t *buf, char col) {
    if (buf->size == buf->cap) {
        colbuf_resize(buf);
    }
    buf->data[buf->size++] = col;
}

void colbuf_resize(struct colbuf_t *buf) {
    buf->cap *= 2;
    char *data = realloc(buf->data, buf->cap);
    assert(buf->data);
    buf->data = data;
}

void colbuf_dump(struct colbuf_t *buf) {
    for (unsigned i = 0; i < buf->size; ++i) {
        printf("%c\n", buf->data[i]);
    }
}
