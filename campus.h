#ifndef CAMPUS_H
#define CAMPUS_H

#define MAXV 50
#define INF 9999

// 全局变量声明
extern int n;
extern int B[MAXV];
extern char Q[MAXV][MAXV];
extern int adjacency_matrix[MAXV][MAXV];
extern int road_status[MAXV][MAXV];

// 路径查找相关变量
extern int visited[MAXV];
extern int path[MAXV];
extern int path_count;
extern int all_paths[1000][MAXV];
extern int path_lengths[1000];
extern int path_distances[1000];
extern int path_blocked_segments[1000];
extern int total_paths;
extern int dist[MAXV];
extern int prev[MAXV];
extern int found[MAXV];

// 核心功能函数声明
void init_adjacency_matrix();
void menu();

// 四个主要功能的函数声明
void function1();  // 学校地图查看
void function2();  // 地点信息查看
void function3();  // 修改地图信息
void function4();  // 路径查询

// 顶点管理函数
void add_vertex();
void setup_connections_for_new_vertex(int new_index);
void delete_vertex();
void update_vertex();

// 工具函数声明
void place(char Q[MAXV][MAXV], int n);
int input1();
int input2(int n, int B[MAXV]);
int input3();

#endif