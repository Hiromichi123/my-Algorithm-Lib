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

    list(int* array0) {
        head = new NODE(0, nullptr);
        NODE* current = head;

        for(; array0 != nullptr; array0++) {
            NODE* node = new NODE(*array0, nullptr);
            current->next = node;
            current = node;
        }
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
    void flip();
    void reshape();
};

// 获取中间元素
NODE* list::get_middle() {
    if(!head || !head->next) return nullptr;
    NODE *fast = head->next, *slow = head->next;
    for(; fast != nullptr && fast->next != nullptr; fast = fast->next->next, slow = slow->next);
    return slow;
}

// 翻转元素
void list::flip() {

}

// 重对齐
void list::reshape() {

}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    list l(array);
    l.print();
    NODE* mid = l.get_middle(); //获取中间元素
    std::cout<<mid->data<<std::endl;
    //翻折
    //重对齐

    return 0;
}