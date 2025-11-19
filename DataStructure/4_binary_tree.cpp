# include<iostream>

typedef char ElemType;

typedef struct TreeNode {
    ElemType data;
    TreeNode *lchild;
    TreeNode *rchild;

    TreeNode(ElemType val) : data(val), lchild(nullptr), rchild(nullptr) {};
}TreeNode;

// 未做实现
typedef struct ThreadNode {
    ElemType data;
    ThreadNode *lchild;
    ThreadNode *rchild;
    int ltag; // 0孩子，1前驱
    int rtag; // 0孩子，1后继

    ThreadNode(ElemType val) : data(val), lchild(nullptr), rchild(nullptr), ltag(0), rtag(0) {};
}ThreadNode;

typedef TreeNode* BiTree;
typedef ThreadNode* ThreadTree;

char str[] = "ABDH#K###E##CFI###G#J##";
int index = 0;
void CreateBiTree(BiTree *T) {
    if (str[index] == '\0') {
        *T = nullptr;
        return;
    }

    char ch = str[index++];
    if (ch == '#') {
        *T = nullptr;
    } else {
        *T = new TreeNode(ch);
        CreateBiTree(&(*T)->lchild); // 创建左子树
        CreateBiTree(&(*T)->rchild); // 创建右子树
    }
}

// 前序遍历
void PreOrder(BiTree T) {
    if (T == nullptr) return;
    std::cout << T->data;
    PreOrder(T->lchild); // 先左
    PreOrder(T->rchild); // 后右
}

// 中序遍历
void InOrder(BiTree T) {
    if (T == nullptr) return;
    InOrder(T->lchild); // 先左
    std::cout << T->data;
    InOrder(T->rchild); // 后右
}

// 后序遍历
void PostOrder(BiTree T) {
    if (T == nullptr) return;
    PostOrder(T->lchild); // 先左
    PostOrder(T->rchild); // 后右
    std::cout << T->data;
}

// 层序遍历：递归法
int maxDepth(BiTree T) {
    if (T == nullptr) return 0;
    int lDepth = maxDepth(T->lchild);
    int rDepth = maxDepth(T->rchild);
    return (lDepth > rDepth ? lDepth : rDepth) + 1; // 左右子树深度最大值+1
}

// 层序遍历：队列法
#include<queue>
int levelOrder(BiTree T) {
    if (T == nullptr) return 0;
    std::queue<BiTree> Q;
    Q.push(T); // 放入根节点

    int depth = 0;
    while(!Q.empty()) {
        int size = Q.size();
        for (int i = 0; i < size; i++) {
            BiTree node = Q.front();
            Q.pop();
            if (node->lchild) Q.push(node->lchild);
            if (node->rchild) Q.push(node->rchild);
        }
        depth++;
    }
    return depth;
}

int main() {
    BiTree T = nullptr; 
    CreateBiTree(&T);

    std::cout << "前序遍历: ";
    PreOrder(T);
    std::cout << std::endl;

    std::cout << "中序遍历: ";
    InOrder(T);
    std::cout << std::endl;

    std::cout << "后序遍历: ";
    PostOrder(T);
    std::cout << std::endl;

    std::cout << "层序遍历递归: " << maxDepth(T) << std::endl;
    std::cout << "层序遍历队列：" << levelOrder(T) << std::endl;
    return 0;
}