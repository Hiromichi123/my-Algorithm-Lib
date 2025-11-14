# include<iostream>

typedef char ElemType;

typedef struct TreeNode {
    ElemType data;
    TreeNode *lchild;
    TreeNode *rchild;

    TreeNode(ElemType val) : data(val), lchild(nullptr), rchild(nullptr) {};
}TreeNode;

typedef TreeNode* BiTree;

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

    return 0;
}