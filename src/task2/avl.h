typedef struct Node {
    char* code;
    int height;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct AVLtree {
    Node* root;
} AVL;

Node* createNode(char* code);
int getHeight(Node* node);
void updateHeight(Node* node);
Node* rotate_left(Node* node);
Node* rotate_right(Node* node);
Node* balance(Node* node);
Node* insertNode(Node* node, char* code);
void avlInsert(AVL* tree, char* code);
