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

    int visited[MAXSIZE]; // 访问标记数组
    int dist[MAXSIZE]; // 起点到各点的最短距离
    int path[MAXSIZE]; // 路径

    MatrixGraph(int v_num = 0, int e_num = 0) : vertex_num(v_num), edge_num(e_num) {
        // 初始化顶点表
        for(int i = 0; i < v_num; i++) {
            this->vertex[i] = char('A' + i);
        }

        // 初始化邻接矩阵
        for(int i = 0; i < vertex_num; i++) {
            for(int j = 0; j < vertex_num; j++) {
                if(i == j)
                    this->arc[i][j] = 0; // 对角线置0
                else
                    this->arc[i][j] = MAX; // 无边
            }
        }

        // 初始化辅助数组
        for(int i = 0; i < vertex_num; i++) {
            this->visited[i] = 0;
            this->path[i] = -1;
            this->dist[i] = MAX;
        }
    }

    // 添加带权边
    MatrixGraph&& add_edge(const char* edge, int weight) && {
        this->arc[edge[0]-'A'][edge[3]-'A'] = weight;
        this->arc[edge[3]-'A'][edge[0]-'A'] = weight; // 无向图对称赋值
        return std::move(*this);
    }

    // 重置访问标记数组
    MatrixGraph&& reset_visited() && {
        for(int i = 0; i < this->vertex_num; i++) this->visited[i] = 0;
        std::cout<<std::endl;
        return std::move(*this);
    }

    //Dijkstra最短路径 
    MatrixGraph&& Dijkstra(int start) && {
        for(int i = 0; i < vertex_num; i++) dist[i] = arc[start][i]; // 填入起点相邻边权值

        visited[start] = 1; // 起点已访问
        // 主循环，寻找剩余顶点的最短路径
        for(int i = 1; i < vertex_num; i++) {
            int min = MAX;
            int u = -1;

            // 未访问顶点中dist最小的顶点，存入u
            for(int j = 0; j < vertex_num; j++) {
                if(visited[j] == 0 && dist[j] < min) {
                    min = dist[j];
                    u = j;
                }
            }
            if(u == -1) break; // 所有可达顶点已访问
            
            visited[u] = 1; // 标记u已访问

            // 更新dist和path
            for(int j = 0; j < vertex_num; j++) {
                if(visited[j] == 0 && arc[u][j] < MAX) {
                    if(dist[u] + arc[u][j] < dist[j]) {
                        dist[j] = dist[u] + arc[u][j];
                        path[j] = u;
                    }
                }
            }
        }

        // 输出结果
        for(int i = 0; i < vertex_num; i++) {
            std::cout << vertex[start] << " -> " << vertex[i] << " = " << dist[i] << std::endl;
            int j = i;
            std::cout << vertex[i]; // 先打印终点
            while(path[j] != -1) {
                std::cout << " <- " << vertex[path[j]];
                j = path[j];
            }
            // 补打印起点
            if(j != start && dist[i] != 0) {
                std::cout << " <- " << vertex[start];
            }
            std::cout << std::endl;
        }

        return std::move(*this);
    }

    //Floyd最短路径
    MatrixGraph&& Floyd() && {
        int dist[MAXSIZE][MAXSIZE];
        int path[MAXSIZE][MAXSIZE];

        // 初始化dist和path矩阵
        for(int i = 0; i < vertex_num; i++) {
            for(int j = 0; j < vertex_num; j++) {
                dist[i][j] = arc[i][j];
                if(i != j && arc[i][j] < MAX)
                    path[i][j] = i;
                else
                    path[i][j] = -1;
            }
        }

        // i中转顶点，j起始顶点，k终止顶点
        for(int i = 0; i < vertex_num; i++) {
            for(int j = 0; j < vertex_num; j++) {
                for(int k = 0; k < vertex_num; k++) {
                    if(dist[j][i] + dist[i][k] < dist[j][k]) {
                        dist[j][k] = dist[j][i] + dist[i][k];
                        path[j][k] = path[i][k];
                    }
                }
            }
        }

        // 输出结果
        for(int i = 0; i < vertex_num; i++) {
            for(int j = 0; j < vertex_num; j++) {
                if(i != j) {
                    std::cout << vertex[i] << " -> " << vertex[j] << " = " << dist[i][j] << std::endl;
                    int curr = j;
                    std::cout << vertex[j];
                    while(path[i][curr] != -1) {
                        std::cout << " <- " << vertex[path[i][curr]];
                        curr = path[i][curr];
                    }
                    if(curr != i && dist[i][j] != 0) {
                        std::cout << " <- " << vertex[i];
                    }
                    std::cout << std::endl;
                }
            }
        }
        return std::move(*this);
    }
};

int main() {
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    MatrixGraph G = MatrixGraph(9, 15)
        .add_edge("A->B", 10).add_edge("A->F", 11)
        .add_edge("B->C", 18).add_edge("B->G", 16).add_edge("B->I", 12)
        .add_edge("C->D", 22).add_edge("C->I", 8)
        .add_edge("D->E", 20).add_edge("D->G", 24).add_edge("D->H", 16).add_edge("D->I", 21)
        .add_edge("E->F", 26).add_edge("E->H", 7)
        .add_edge("F->G", 17)
        .add_edge("G->H", 19)
        .Dijkstra(0).reset_visited()
        .Floyd().reset_visited();

        return 0;
}
