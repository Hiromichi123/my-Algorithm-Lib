#include<iostream>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAX 0x7fffffff

class MatrixGraph {
public:
    VertexType vertex[MAXSIZE]; // 顶点表
    EdgeType arc[MAXSIZE][MAXSIZE]; // 邻接矩阵
    int vertex_num, edge_num; // 图的当前顶点数和边数
    int visited[MAXSIZE]; // 访问标记数组

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

        // 初始化标记数组
        for(int i = 0; i < vertex_num; i++) {
            this->visited[i] = 0;
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

    // 普里姆算法，最小生成树
    MatrixGraph&& Prim() && {
        int i, j, k, min;
        int weight[MAXSIZE]; // 保存候选边
        int vex_index[MAXSIZE]; // 值代表出，下标代表入

        weight[0] = 0; // 从A开始
        vex_index[0] = 0;
        for(i = 1; i < vertex_num; i++) {
            weight[i] = arc[0][i]; // 填入与A相连的边权
            vex_index[i] = 0;
        }

        for(i = 1; i < vertex_num; i++) {
            min = MAX;
            j = 0;
            k = 0;

            // 寻找与生成树距离最小的顶点
            for(; j < vertex_num; j++) {
                if(weight[j] != 0 && weight[j] < min) {
                    min = weight[j];
                    k = j;
                }
            }

            // 将顶点加入生成树
            std::cout << vertex[vex_index[k]] << "->" << vertex[k] << std::endl;
            weight[k] = 0; // 标记为已加入

            // 更新各候选边，为下一轮寻找最小的边
            for(j = 0; j < vertex_num; j++) {
                if(weight[j] != 0 && arc[k][j] < weight[j]) {
                    weight[j] = arc[k][j];
                    vex_index[j] = k;
                }
            }
        }
        return std::move(*this);
    }

    // 克鲁斯卡尔算法，最小生成树
    MatrixGraph&& Kruskal() && {
        struct Edge {
            int start;
            int end;
            int weight;
        } edges[MAXSIZE * MAXSIZE];

        // 提取所有边（只收集 i<j 的无向边），并统计实际边数
        int m = 0; // 实际边数
        for(int i = 0; i < vertex_num; i++) {
            for(int j = i + 1; j < vertex_num; j++) {
                if(arc[i][j] != MAX) {
                    edges[m].start = i;
                    edges[m].end = j;
                    edges[m].weight = arc[i][j];
                    m++;
                }
            }
        }

        // 按权值排序边（使用简单冒泡排序，范围为 m）
        for(int i = 0; i < m - 1; i++) {
            for(int j = 0; j < m - i - 1; j++) {
                if(edges[j].weight > edges[j + 1].weight) {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }

        // 初始化parent数组，用于查找根节点（并查集，初始为自身）
        int parent[MAXSIZE];
        for(int i = 0; i < vertex_num; i++) parent[i] = i;

        int edge_count = 0; // 已加入生成树的边数
        for(int i = 0; i < m && edge_count < vertex_num - 1; i++) {
            int start_parent = edges[i].start;
            int end_parent = edges[i].end;

            // 查找起点的根节点
            while(parent[start_parent] != start_parent) {
                start_parent = parent[start_parent];
            }

            // 查找终点的根节点
            while(parent[end_parent] != end_parent) {
                end_parent = parent[end_parent];
            }

            // 若不构成环路，则加入生成树
            if(start_parent != end_parent) {
                std::cout << vertex[edges[i].start] << "->" << vertex[edges[i].end] << std::endl;
                parent[start_parent] = end_parent; // 合并集合（将 start 的根指向 end 的根）
                edge_count++;
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
        .Prim().reset_visited()
        .Kruskal().reset_visited();

        return 0;
}
