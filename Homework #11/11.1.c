#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct _tree {
    int num;
    int subFreq;
    int objFreq;
    struct _tree *left;
    struct _tree *right;
} tree;

tree *buildTree(int *a, int *f, int *p, int l, int r) {
    if (l < r) {
        tree *node = calloc(1, sizeof(tree));
        if (!node) {
            printf("Couldn't allocate memory\n");
            exit(1);
        }
        int minDif = abs(p[l + 1] - p[r + 1]);
        int minInd = l;
        for (int i = l + 1; i < r; i++) {
            if (abs(p[i] + p[i + 1] - p[r + 1] - p[l]) < minDif) {
                minDif = abs((p[i] + p[i + 1] - p[r + 1] - p[l]));
                minInd = i;
            }
        }
        node->num = a[minInd];
        node->subFreq = f[minInd];
        node->objFreq = p[r + 1] - p[l];
        node->left = buildTree(a, f, p, l, minInd - 1);
        node->right = buildTree(a, f, p, minInd + 1, r);
    }
     else if (l == r) {
        tree *leaf = calloc(1, sizeof(tree));
        if (!leaf) {
            printf("Couldn't allocate memory\n");
            exit(1);
        }
        leaf->num = a[r];
        leaf->subFreq = f[r];
        leaf->objFreq = f[r];
        leaf->left = NULL;
        leaf->right = NULL;
        return leaf;
    }
    else {
        return NULL;
    }
}

void printTree(tree *tree, int isRoot, FILE *output) {
    if (isRoot) {
        fprintf(output, "digraph {\n");
        isRoot = 0;
    }
    if (tree->left) {
        fprintf(output, "\"%d\\n%d\\n%d\" -> \"%d\\n%d\\n%d\";\n",
                tree->num, tree->subFreq, tree->objFreq, 
                tree->left->num, tree->left->subFreq, tree->left->objFreq);
        printTree(tree->left, isRoot, output);
    }
    if (tree->right) {
        fprintf(output, "\"%d\\n%d\\n%d\" -> \"%d\\n%d\\n%d\";\n",
                tree->num, tree->subFreq, tree->objFreq,
                tree->right->num, tree->right->subFreq, tree->right->objFreq);
        printTree(tree->right, isRoot, output);
    }
}

void clearTree(tree *tree) {
  if (tree->left) {
    clearTree(tree->left);
  }
  if (tree->right) {
    clearTree(tree->right);
  }
  free(tree);
}

int main() {
    FILE *inputFile = fopen("tree.txt", "r");
    if (!inputFile) {
        printf("Couldn't open file\n");
        exit(1);
    }
    int n = 0;
    fscanf(inputFile, "%d", &n);
    int a[n];
    int f[n];
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d - %d", &a[i], &f[i]);
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n - j - 1; i++) {
            if (a[i] > a[i + 1]) {
                int temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
                temp = f[i];
                f[i] = f[i + 1];
                f[i + 1] = temp;
            }
        }
    }
    int p[n + 1];
    p[0] = 0;
    for (int i = 1; i < n + 1; i++) {
        p[i] = p[i - 1] + f[i - 1];
    }
    tree *searchTree = buildTree(a, f, p, 0, n - 1);
    FILE *outputFile = fopen("output.dot", "w");
    if (!outputFile) {
        printf("Couldn't open file\n");
        exit(1);
    }
    printTree(searchTree, 1, outputFile);
    fprintf(outputFile, "}");
    clearTree(searchTree);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}