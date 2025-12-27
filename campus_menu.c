#include <stdio.h>
#include <string.h>
#include "campus.h"

// 全局变量定义
//总节点树
int n = 18;
//节点编号和名称
int B[MAXV] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
char Q[MAXV][MAXV] = {
    {"【1】学校门口"}, {"【2】海纳楼"}, {"【3】海阳馆"}, 
    {"【4】运动场"}, {"【5】学生宿舍"}, {"【6】超市"}, 
    {"【7】菜鸟驿站"}, {"【8】心理咨询中心"}, 
    {"【9】校医室"}, {"【10】济航楼"}, {"【11】桃李食苑"}, {"【12】人文与教育学院"}, 
    {"【13】琴苑"}, {"【14】海科楼"}, {"【15】慎思楼"}, {"【16】风电实验室"}, 
    {"【17】厚为楼"}, {"【18】合金实验室"}
};

// 地图邻接矩阵及道路状态矩阵
int adjacency_matrix[MAXV][MAXV];
int road_status[MAXV][MAXV];//1：正常通行，0：临时禁行，INF：无道路

// 路径搜索相关变量
//过程量
int visited[MAXV];                    // 标记节点在DFS过程中是否访问过
int path[MAXV];                       // 临时变量，存储当前查找的路径
int path_count = 0;                   // 当前路径的节点数

//结果量
int all_paths[1000][MAXV];            // 存储所有找到的路径
int path_lengths[1000];               // 每条路径的结点数
int path_distances[1000];             // 每条路径的总距离
int path_blocked_segments[1000];      // 存储每条路径中禁行路段的数量
int total_paths = 0;                  // 总路径数

// Dijkstra算法相关数组
int dist[MAXV];   // 从起点到各节点的最短距离
int prev[MAXV];   // 路径前驱节点
int found[MAXV];  // 标记节点是否已确定最短路径

// 工具函数
// 显示所有地点的坐标指示
void place(char Q[MAXV][MAXV], int n) {
    int i;
    printf("地点坐标指示:\n");
    for(i = 0; i < n; i++) {
        printf("%s   ", Q[i]);
        if(i % 6 == 5) printf("\n");
    }
    printf("\n");
}

int input1() {
    int x;
    scanf("%d", &x);
    while(x > 5 || x < 0) {
        printf("输入错误，请重新输入: ");
        scanf("%d", &x);
    }
    return x;
}

int input2(int n, int B[MAXV]) {
    int x;
    scanf("%d", &x);
    
    while(x != 666) {
        if(x < 1 || x > n) {
            printf("该地标节点不存在请重新输入: ");
            scanf("%d", &x);
            continue;
        }
        
        int found = 0;
        for(int i = 0; i < n; i++) {
            if(B[i] == x) {
                found = 1;
                break;
            }
        }
        
        if(!found) {
            printf("该地标节点不存在请重新输入: ");
            scanf("%d", &x);
        } else {
            break;
        }
    }
    return x;
}

int input3() {
    int x;
    scanf("%d", &x);
    while(x > 4 || x < 1) {
        printf("输入错误，请重新输入: ");
        scanf("%d", &x);
    }
    return x;
}

// 初始化邻接矩阵
void init_adjacency_matrix() {
    int i, j;
    
    for(i = 0; i < MAXV; i++) {
        for(j = 0; j < MAXV; j++) {
            if(i == j) {
                adjacency_matrix[i][j] = 0;
                road_status[i][j] = 1;
            } else {
                adjacency_matrix[i][j] = INF;
                road_status[i][j] = 1;
            }
        }
    }

    adjacency_matrix[0][1] = 18;   road_status[0][1] = 1;
    adjacency_matrix[0][2] = 32;   road_status[0][2] = 1;
    adjacency_matrix[0][17] = 30;  road_status[0][17] = 1;
    adjacency_matrix[0][15] = 36;  road_status[0][15] = 1;
    adjacency_matrix[1][11] = 50;  road_status[1][11] = 1;
    adjacency_matrix[2][3] = 42;   road_status[2][3] = 1;
    adjacency_matrix[3][5] = 60;   road_status[3][5] = 1;
    adjacency_matrix[3][6] = 62;   road_status[3][6] = 1;
    adjacency_matrix[4][6] = 20;   road_status[4][6] = 1;
    adjacency_matrix[4][5] = 26;   road_status[4][5] = 1;
    adjacency_matrix[4][7] = 16;   road_status[4][7] = 1;
    adjacency_matrix[5][7] = 15;   road_status[5][7] = 1;
    adjacency_matrix[4][8] = 56;   road_status[4][8] = 1;
    adjacency_matrix[4][10] = 80;  road_status[4][10] = 1;
    adjacency_matrix[7][9] = 36;   road_status[7][9] = 1;
    adjacency_matrix[9][10] = 50;  road_status[9][10] = 1;
    adjacency_matrix[10][11] = 48; road_status[10][11] = 1;
    adjacency_matrix[11][12] = 48; road_status[11][12] = 1;
    adjacency_matrix[10][12] = 56; road_status[10][12] = 1;
    adjacency_matrix[12][13] = 42; road_status[12][13] = 1;
    adjacency_matrix[13][14] = 80; road_status[13][14] = 1;
    adjacency_matrix[14][15] = 45; road_status[14][15] = 1;
    adjacency_matrix[14][16] = 60; road_status[14][16] = 1;
    adjacency_matrix[15][16] = 26; road_status[15][16] = 1;
    adjacency_matrix[15][17] = 20; road_status[15][17] = 1;
    adjacency_matrix[16][17] = 26; road_status[16][17] = 1;
    
    for(i = 0; i < MAXV; i++) {
        for(j = i + 1; j < MAXV; j++) {
            if(adjacency_matrix[i][j] != INF) {
                adjacency_matrix[j][i] = adjacency_matrix[i][j];
                road_status[j][i] = road_status[i][j];
            }
        }
    }
}

// 主菜单
void menu() {
    int choice;
    
    init_adjacency_matrix();

    do {
        printf("\n");
        printf("╔══════════════════════════════════════════╗\n");
        printf("║    🏫 广东海洋大学阳江校区导航系统     ║\n");
        printf("╠══════════════════════════════════════════╣\n");
        printf("║  1. 🗺️  学校地图查看                    ║\n");
        printf("║  2. 📍 地点信息查看                    ║\n");
        printf("║  3. 🛠️  修改地图信息                    ║\n");
        printf("║  4. 🚶 路径查询                        ║\n");
        printf("║  0. 🚪 退出系统                        ║\n");
        printf("╚══════════════════════════════════════════╝\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: 
                printf("\n📊 正在加载地图...\n");
                function1(); 
                break;
            case 2: 
                printf("\n📋 正在加载地点信息...\n");
                function2(); 
                break;
            case 3: 
                printf("\n⚙️  进入地图管理...\n");
                function3(); 
                break;
            case 4:
                printf("\n🗺️  正在准备路径查询...\n");
                function4();
                break;
            case 0: 
                printf("\n👋 感谢使用校园导航系统，再见！\n");
                break;
            default: 
                printf("\n❌ 无效选择，请重新输入！\n");
        }
    } while(choice != 0);
}