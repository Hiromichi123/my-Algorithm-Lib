// 单链表应用
/*[2019] 设线性表L=(a1, a2, a3, ⋯,an−2, an−1, an)采用带头节点的单链表保存，
请设计一个空间复杂度为O(1)
且时间上尽可能高效的算法，重新排列L中的各节点，得到线性表
L′=(a1, a2, a3, ⋯,an−2, an−1, an)
*/

// 题干强制定义
typedef struct node {
    int data;
    struct node* next;
    node(int d, node* n) : data(d), next(n) {} // 构造函数：初始化数据和指针
}NODE;

/*---------------------------------------------------------------*/

#include<iostream>
class list{
public:
    NODE* head; // 头节点

    // 由数组构造链表，0表示结束
    list(int* array0) {
        head = new NODE(0, nullptr);
        NODE* current = head;

        for(; *array0 != 0; array0++) {
            NODE* node = new NODE(*array0, nullptr);
            current->next = node;
            current = node;
        }
        current->next = nullptr; // 末尾
    }

    // 直接又传入头节点的构造
    list(NODE* first) {
        head = new NODE(0, first);
    }

    void print() {
        NODE* current = head->next;
        for(; current; current = current->next)
            std::cout<<current->data<<" ";
        std::cout<<std::endl;
    }

    ~list() {
        for(NODE* current = head; current;) {
            NODE* temp = current;
            current = current->next;
            delete temp;
        }
    }

    NODE* get_middle();
    NODE* flip(NODE* start);
    void reorder();
};

// 获取中间元素(偶数取上中位)
NODE* list::get_middle() {
    if(!head || !head->next) return nullptr;
    NODE *fast = head->next, *slow = head->next;
    for(; fast->next && fast->next->next; fast = fast->next->next, slow = slow->next);
    return slow;
}

// 翻转元素
NODE* list::flip(NODE* start) {
    if(!start) return nullptr;
    NODE *front = nullptr, *cur = start, *pre; // pre本质上是一个temp
    for(; cur != nullptr; front = cur,
                        cur = pre) {
                            pre = cur->next;
                            cur->next = front;
                        }
    start->next = nullptr; // 翻转后的尾节点指向空
    return front;
}

// 重对齐
void list::reorder() {
    if (!head || !head->next) return;
    NODE* mid = get_middle();
    NODE* flipped = flip(mid->next); // 翻转后半部分
    mid->next = nullptr; // 切断前后部分

    NODE *first = head->next, *second = flipped, *temp1, *temp2;
    for(; second; first = temp1,
                second = temp2) { // 交叉合并
        temp1 = first->next;
        temp2 = second->next;

        first->next = second;
        second->next = temp1;
    }
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0};
    list l(array);

    //重对齐
    l.reorder();
    l.print();
    
    return 0;
}