#include<iostream>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAX 0x10000000

class MatrixGraph {
public:
    VertexType vertex[MAXSIZE]; // 顶点表
    EdgeType arc[MAXSIZE][MAXSIZE]; // 邻接矩阵
    int vertex_num, edge_num; // 顶点数和边数

    
};

// 邻接表边结点
class EdgeNode {
public:
    int edge_vex;
    EdgeNode* next; // 指向next边结点
};

// 邻接表顶点
class VertexNode {
public:
    int in; // 入度数
    VertexType data;
    EdgeNode* head; // 指向first边结点
};

// 邻接表图
class AdjGraph {
public:
    VertexNode adj_list[MAXSIZE]; // 顶点表
    int vertex_num, edge_num; // 顶点数和边数

    AdjGraph(int v_num = 0, int e_num = 0) : vertex_num(v_num), edge_num(e_num) {
        // 初始化顶点表
        for(int i = 0; i < v_num; i++) {
            this->adj_list[i].data = char('A' + i);
            this->adj_list[i].in = 0;
            this->adj_list[i].head = nullptr;
        }
    }
};

// 拓扑排序
AdjGraph&& TopologicalSort(AdjGraph& G) {
    int stack[MAXSIZE]; // 辅助栈
    int top = -1; // 栈顶指针
    int count = 0; // 已输出顶点计数
    // 将入度为0的顶点入栈
    for(int i = 0; i < G.vertex_num; i++) {
        if(G.adj_list[i].in == 0) {
            stack[++top] = i;
        }
    }
    while(top != -1) {
        int v = stack[top--]; // 出栈
        std::cout << G.adj_list[v].data << " "; // 输出顶点
        count++;
        // 遍历v的邻接边
        EdgeNode* p = G.adj_list[v].head;
        while(p != nullptr) {
            int w = p->edge_vex;
            G.adj_list[w].in--; // 邻接点入度减1
            if(G.adj_list[w].in == 0) {
                stack[++top] = w; // 入度为0入栈
            }
            p = p->next;
        }
    }
    if(count < G.vertex_num) {
        std::cout << "Graph has a cycle, topological sort not possible." << std::endl;
    }
    return std::move(G);
}

int main() {
    return 0;
}