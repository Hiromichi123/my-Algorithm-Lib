# include <iostream>
# include <queue>
# include <vector>
# include <algorithm>
# include <unordered_set>
# include <unordered_map>

#define MAXSIZE 20

class Node {
public:
    int pos_x, pos_y; // 节点位置
    int state; // 节点状态：0表示空，1表示墙，2表示物品
    Node *top, *bottom, *left, *right; // 四方连接

    Node(int x, int y) : pos_x(x), pos_y(y), state(0),
                        top(nullptr), bottom(nullptr),
                        left(nullptr), right(nullptr){}
};

class GridMap {
private:
    Node* grid[MAXSIZE][MAXSIZE];

public:
    GridMap() {
        for (int i = 0; i < MAXSIZE; i++) {
            for (int j = 0; j < MAXSIZE; j++) {
                grid[i][j] = new Node(i, j);
            }
        }

        // 建立连接
        for (int i = 0; i < MAXSIZE; i++) {
            for (int j = 0; j < MAXSIZE; j++) {
                if (i > 0) grid[i][j]->left = grid[i-1][j];
                if (i < MAXSIZE - 1) grid[i][j]->right = grid[i+1][j];
                if (j > 0) grid[i][j]->bottom = grid[i][j-1];
                if (j < MAXSIZE - 1) grid[i][j]->top = grid[i][j+1];
            }
        }
    }

    ~GridMap() {
        for (int i = 0; i < MAXSIZE; i++) {
            for (int j = 0; j < MAXSIZE; j++) {
                delete grid[i][j];
            }
        }
    }

    Node* getNode(int x, int y) {
        if (x < 0 || x >= MAXSIZE || y < 0 || y >= MAXSIZE) {
            return nullptr;
        }
        return grid[x][y];
    }

    void print() {
        for (int j = MAXSIZE - 1; j >= 0; j--) {
            for (int i = 0; i < MAXSIZE; i++) {
                std::cout << grid[i][j]->state << " ";
            }
            std::cout << std::endl;
        }
    }

    void bfs_explore(Node* start, Node* goal);
    void bfs_explore_bidirectional(Node* start, Node* goal);
};

// 单相BFS
void GridMap::bfs_explore(Node* start, Node* goal) {
    if (!start || !goal) return;

    std::unordered_map<Node*, Node*> parent; // 记录路径
    std::unordered_set<Node*> visited; // 已访问节点
    std::queue<Node*> q; // BFS队列

    q.push(start); // 起点入队
    visited.insert(start); // 起点已访问
    parent[start] = nullptr; // 起点无父节点

    while (!q.empty()) {
        Node* current_node = q.front(); // 当前队首节点
        q.pop(); // 弹出队首元素

        // 检查是否已到达目标
        if (current_node == goal) {
            // 回溯路径
            std::vector<Node*> path;
            Node* node = goal;
            while (node) {
                path.push_back(node);
                node = parent[node];
            }
            std::reverse(path.begin(), path.end()); // 反转路径顺序，从起点到终点
            std::cout << "找到路径！路径长度: " << path.size() << std::endl;
            std::cout << "路径: ";
            for (Node* node : path) {
                std::cout << "(" << node->pos_x << "," << node->pos_y << ") ";
            }
            std::cout << std::endl;
            return;
        }

        // 四方相邻节点，范围循环        
        for (auto neighbor : {current_node->top, current_node->bottom, 
                               current_node->left, current_node->right}) {
            // 检查是否：有效、未访问过、非墙
            if (neighbor && visited.find(neighbor) == visited.end() 
                && neighbor->state != 1) {
                
                visited.insert(neighbor); // 标记为已访问
                parent[neighbor] = current_node; // 记录父节点
                q.push(neighbor); // 入队
            }
        }
    }

    std::cout << "未找到从起点到终点的路径！" << std::endl;
}

// 双向BFS
void GridMap::bfs_explore_bidirectional(Node* start, Node* goal) {
    if (!start || !goal) return;

    std::unordered_map<Node*, Node*> parent_start; // 起点方向父节点
    std::unordered_map<Node*, Node*> parent_goal;  // 目标方向父节点
    std::unordered_set<Node*> visited_start; // 起点方向已访问节点
    std::unordered_set<Node*> visited_goal;  // 目标方向已访问节点
    std::queue<Node*> q_start; // 起点方向队列
    std::queue<Node*> q_goal;  // 目标方向队列

    q_start.push(start);
    visited_start.insert(start);
    parent_start[start] = nullptr;

    q_goal.push(goal);
    visited_goal.insert(goal);
    parent_goal[goal] = nullptr;

    // 路径回溯
    auto remount = [&](Node* meet_node) {
        std::vector<Node*> path;

        // 起点到交汇点
        Node* node = meet_node;
        while (node) {
            path.push_back(node);
            auto it = parent_start.find(node);
            if (it == parent_start.end()) break;
            node = it->second;
        }
        std::reverse(path.begin(), path.end());

        // 交汇点到目标
        auto it = parent_goal.find(meet_node);
        node = (it != parent_goal.end()) ? it->second : nullptr;
        while (node) {
            path.push_back(node);
            auto it2 = parent_goal.find(node);
            if (it2 == parent_goal.end()) break;
            node = it2->second;
        }

        std::cout << "双向BFS找到路径！路径长度: " << path.size() << std::endl;
        std::cout << "路径: ";
        for (Node* n : path) {
            std::cout << "(" << n->pos_x << "," << n->pos_y << ") ";
        }
        std::cout << std::endl;
    };

    while (!q_start.empty() && !q_goal.empty()) {
        // 从起点方向扩展
        Node* current_start = q_start.front();
        q_start.pop();

        for (auto neighbor : {current_start->top, current_start->bottom, 
                               current_start->left, current_start->right}) {
            if (neighbor && neighbor->state != 1
                    && visited_start.find(neighbor) == visited_start.end()) {
                
                visited_start.insert(neighbor);
                parent_start[neighbor] = current_start;
                q_start.push(neighbor);

                // 检查是否被反向访问
                if (visited_goal.find(neighbor) != visited_goal.end()) {
                    remount(neighbor); // 路径回溯
                    return;
                }
            }
        }

        // 从目标方向对称扩展
        Node* current_goal = q_goal.front();
        q_goal.pop();

        for (auto neighbor : {current_goal->top, current_goal->bottom, 
                               current_goal->left, current_goal->right}) {
            if (neighbor && neighbor->state != 1
                    && visited_goal.find(neighbor) == visited_goal.end()) {

                visited_goal.insert(neighbor);
                parent_goal[neighbor] = current_goal;
                q_goal.push(neighbor);

                // 检查是否被起点方向访问
                if (visited_start.find(neighbor) != visited_start.end()) {
                    remount(neighbor); // 路径回溯
                    return;
                }
            }
        } 
    }
}

int main() {
    GridMap map;
    
    // 示例设置状态
    map.getNode(5, 5)->state = 1;
    map.getNode(10, 10)->state = 2;
    
    map.print();

    std::cout << "\n开始BFS搜索..." << std:: endl;
    Node* start = map.getNode(5, 5);
    Node* goal = map.getNode(10, 10);
    map.bfs_explore(start, goal);
    map.bfs_explore_bidirectional(start, goal);
    
    return 0;
}
