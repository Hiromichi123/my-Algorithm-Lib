#include<iostream>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100

class MatrixGraph {
public:
    VertexType vertex[MAXSIZE]; // 顶点表
    EdgeType arc[MAXSIZE][MAXSIZE]; // 邻接矩阵
    int vertex_num, edge_num; // 图的当前顶点数和边数
    int visited[MAXSIZE]; // 访问标记数组
    int front, rear, queue[MAXSIZE]; // 层序遍历队列

    MatrixGraph(int v_num = 0, int e_num = 0) : vertex_num(v_num), edge_num(e_num) {
        // 初始化顶点表
        for(int i = 0; i < v_num; i++) {
            this->vertex[i] = char('A' + i);
        }

        // 初始化邻接矩阵
        for(int i = 0; i < vertex_num; i++) {
            for(int j = 0; j < vertex_num; j++) {
                this->arc[i][j] = 0;
            }
        }

        // 初始化标记数组
        for(int i = 0; i < vertex_num; i++) {
            this->visited[i] = 0;
        }
    }

    // 添加边，具名对象&，临时对象&&
    MatrixGraph& add_edge(const char* edge) & {
        this->arc[edge[0]-'A'][edge[3]-'A'] = 1;
        this->arc[edge[3]-'A'][edge[0]-'A'] = 1; // 无向图对称赋值
        return *this;
    }
    MatrixGraph&& add_edge(const char* edge) && {
        this->arc[edge[0]-'A'][edge[3]-'A'] = 1;
        this->arc[edge[3]-'A'][edge[0]-'A'] = 1; // 无向图对称赋值
        return std::move(*this);
    }

    // 重置访问标记数组
    MatrixGraph& reset_visited() & {
        for(int i = 0; i < this->vertex_num; i++) this->visited[i] = 0;
        std::cout<<std::endl;
        return *this;
    }
    MatrixGraph&& reset_visited() && {
        for(int i = 0; i < this->vertex_num; i++) this->visited[i] = 0;
        std::cout<<std::endl;
        return std::move(*this);
    }

    // 深度优先遍历
    MatrixGraph& DFS(int start) & {
        this->visited[start] = 1; // 标记已访问
        std::cout << this->vertex[start] << " ";
        for(int j = 0; j < this->vertex_num; j++) {
            if(this->arc[start][j] != 0 && !this->visited[j]) { // 有边且未访问
                this->DFS(j); // 向下递归
            }
        }
        return *this;
    }
    MatrixGraph&& DFS(int start) && {
        this->visited[start] = 1;
        std::cout << this->vertex[start] << " ";
        for(int j = 0; j < this->vertex_num; j++) {
            if(this->arc[start][j] != 0 && !this->visited[j]) {
                this->DFS(j);
            }
        }
        return std::move(*this);
    }

    // 广度优先遍历
    MatrixGraph& BFS(int start) & {
        front = rear = 0; // 初始化队列
        visited[start] = 1; // 标记已访问
        std::cout << vertex[start] << " ";
        queue[rear++] = start; // 入队

        while(front != rear) { // 非空
            int i = queue[front++]; // 出队
            for(int j = 0; j < vertex_num; j++) {
                if(arc[i][j] == 1 && visited[j] == 0) { // 有边且未访问
                    visited[j] = 1; // 标记已访问
                    std::cout << vertex[j] << " ";
                    queue[rear++] = j; // 入队
                }
            }
        }
        return *this;
    }
    MatrixGraph&& BFS(int start) && {
        front = rear = 0;
        visited[start] = 1;
        std::cout << vertex[start] << " ";
        queue[rear++] = start;

        while(front != rear) {
            int i = queue[front++];
            for(int j = 0; j < vertex_num; j++) {
                if(arc[i][j] == 1 && visited[j] == 0) {
                    visited[j] = 1;
                    std::cout << vertex[j] << " ";
                    queue[rear++] = j;
                }
            }
        }
        return std::move(*this);
    }    
};

int main() {
    // 具名对象，左值
    MatrixGraph G1(8, 15);
    G1.add_edge("A->B").add_edge("A->F")
        .add_edge("B->C").add_edge("B->G").add_edge("B->I")
        .add_edge("C->D").add_edge("C->I")
        .add_edge("D->E").add_edge("D->G")
        .add_edge("E->F").add_edge("E->H")
        .add_edge("F->G")
        .add_edge("G->H")
        .DFS(0).reset_visited()
        .BFS(0).reset_visited();

    // 临时对象，右值
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    MatrixGraph G2 = MatrixGraph(8, 15)
        .add_edge("A->B").add_edge("A->F")
        .add_edge("B->C").add_edge("B->G").add_edge("B->I")
        .add_edge("C->D").add_edge("C->I")
        .add_edge("D->E").add_edge("D->G")
        .add_edge("E->F").add_edge("E->H")
        .add_edge("F->G")
        .add_edge("G->H")
        .DFS(0).reset_visited()
        .BFS(0).reset_visited();

        return 0;
}
