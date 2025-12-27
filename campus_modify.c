#include <stdio.h>
#include <string.h>
#include "campus.h"

// 增加地标节点
void add_vertex() {
    int b;
    printf("输入需要添加的地标节点的编号: ");
    scanf("%d", &b);
    
    // 检查是否已存在
    int exists = 0;
    for(int i = 0; i < n; i++) {
        if(B[i] == b) {
            exists = 1;
            break;
        }
    }
    
    if(exists) {
        printf("该地标节点已存在！\n");
    } else {
        B[n] = b;
        printf("输入地标节点的名称(【编号】名称): ");
        scanf("%s", Q[n]);
        
        // 初始化新节点的邻接矩阵
        for(int i = 0; i < MAXV; i++) {
            if(i == n) {
                adjacency_matrix[n][i] = 0;
                road_status[n][i] = 1;
            } else {
                adjacency_matrix[n][i] = INF;
                adjacency_matrix[i][n] = INF;
                road_status[n][i] = 1;
                road_status[i][n] = 1;
            }
        }
        
        n++;
        printf("添加成功！当前共有 %d 个地标节点。\n", n);

        // 为新节点设置道路连接
        printf("为新节点设置道路连接 ");
        setup_connections_for_new_vertex(n-1);
    }
}

// 为新节点设置道路连接
void setup_connections_for_new_vertex(int new_index) {
    printf("\n════════════ 为 %s 设置道路连接 ════════════\n", Q[new_index]);
    printf("输入要连接的节点编号和距离（输入666结束）\n");
    
    int target_node, distance;
    int connection_count = 0;
    
    while(1) {
        printf("\n连接节点编号 (1-%d, 666结束): ", n-1);
        scanf("%d", &target_node);
        
        if(target_node == 666) break;
        
        // 验证节点编号
        if(target_node < 1 || target_node > n-1) {
            printf("错误：节点编号无效！\n");
            continue;
        }
        
        // 查找目标节点索引
        int target_index = -1;
        for(int i = 0; i < n-1; i++) {
            if(B[i] == target_node) {
                target_index = i;
                break;
            }
        }
        
        if(target_index == -1) {
            printf("错误：找不到该节点！\n");
            continue;
        }
        
        if(target_index == new_index) {
            printf("错误：不能连接自己！\n");
            continue;
        }
        
        // 输入距离
        printf("到 %s 的距离(米): ", Q[target_index]);
        scanf("%d", &distance);
        
        if(distance <= 0) {
            printf("错误：距离必须大于0！\n");
            continue;
        }
        
        // 设置连接
        adjacency_matrix[new_index][target_index] = distance;
        adjacency_matrix[target_index][new_index] = distance;
        road_status[new_index][target_index] = 1;
        road_status[target_index][new_index] = 1;
        
        connection_count++;
        printf("✅ 已连接：%s ↔ %s (%d米)\n", 
               Q[new_index], Q[target_index], distance);
    }
    
    printf("\n完成！%s 连接了 %d 个节点\n", Q[new_index], connection_count);
    printf("═══════════════════════════════════════════\n");
}

// 删除地标节点
void delete_vertex() {
    int b;
    printf("请输入需要删除的地标节点编号: ");
    b = input2(n, B);
    if(b == 666) return;
    
    int index = -1;
    for(int i = 0; i < n; i++) {
        if(B[i] == b) {
            index = i;
            break;
        }
    }
    
    if(index == -1) {
        printf("未找到该地标节点！\n");
        return;
    }
    
    printf("确认删除 %s (编号: %d) 吗？(y/n): ", Q[index], B[index]);
    char confirm;
    scanf(" %c", &confirm);
    
    if(confirm == 'y' || confirm == 'Y') {
        // 删除节点（覆盖）
        for(int i = index; i < n - 1; i++) {
            B[i] = B[i + 1];
            strcpy(Q[i], Q[i + 1]);
            
            // 移动邻接矩阵的行和列
            for(int j = 0; j < n; j++) {
                adjacency_matrix[i][j] = adjacency_matrix[i + 1][j];
                road_status[i][j] = road_status[i + 1][j];
            }
        }
        
        // 移动邻接矩阵的列
        for(int i = 0; i < n - 1; i++) {
            for(int j = index; j < n - 1; j++) {
                adjacency_matrix[i][j] = adjacency_matrix[i][j + 1];
                road_status[i][j] = road_status[i][j + 1];
            }
        }
        
        n--;
        printf("删除成功！当前共有 %d 个地标节点。\n", n);
    } else {
        printf("取消删除操作。\n");
    }
}

// 更新地标节点信息
void update_vertex() {
    int b;
    printf("请输入需要更新的地标节点编号: ");
    b = input2(n, B);
    if(b == 666) return;
    
    for(int i = 0; i < n; i++) {
        if(B[i] == b) {
            printf("当前节点名称: %s\n", Q[i]);
            printf("请输入新的节点名称(【编号】名称): ");
            scanf("%s", Q[i]);
            printf("更新成功！\n");
            return;
        }
    }
    printf("未找到该地标节点！\n");
}

// 修改道路状态
void modify_road_status() {
    int from, to, status;
    
    printf("\n════════════════════ 修改道路状态 ════════════════════\n");
    place(Q, n);
    
    printf("请输入起点编号(1-%d): ", n);
    scanf("%d", &from);
    printf("请输入终点编号(1-%d): ", n);
    scanf("%d", &to);
    
    if(from < 1 || from > n || to < 1 || to > n) {
        printf("错误：输入的地点编号无效！\n");
        return;
    }
    
    if(from == to) {
        printf("错误：起点和终点不能相同！\n");
        return;
    }
    
    int from_index = from - 1;
    int to_index = to - 1;
    
    if(adjacency_matrix[from_index][to_index] == INF) {
        printf("错误：%s 到 %s 之间没有道路！\n", Q[from_index], Q[to_index]);
        return;
    }
    
    printf("当前道路状态: ");
    if(road_status[from_index][to_index] == 1) {
        printf("✅ 正常通行\n");
    } else {
        printf("⚠️  临时禁行\n");
    }
    
    printf("请选择新的道路状态:\n");
    printf("1. ✅ 正常通行\n");
    printf("2. ⚠️  临时禁行\n");
    printf("请选择(1-2): ");
    scanf("%d", &status);
    
    if(status == 1) {
        road_status[from_index][to_index] = 1;
        road_status[to_index][from_index] = 1;
        printf("✅ 已设置 %s ↔ %s 为正常通行\n", Q[from_index], Q[to_index]);
    } else if(status == 2) {
        road_status[from_index][to_index] = 0;
        road_status[to_index][from_index] = 0;
        printf("⚠️  已设置 %s ↔ %s 为临时禁行\n", Q[from_index], Q[to_index]);
    } else {
        printf("错误：输入无效！\n");
    }
    
    printf("═══════════════════════════════════════════════════\n");
}

// 修改菜单
void modify(int n, char Q[MAXV][MAXV], int B[MAXV]) {
    int a; 
    printf("\n");
    place(Q, n);
    printf("\n\t**************修改菜单***************");
    printf("\n\t**       (1)增加地标节点           **");
    printf("\n\t**       (2)删除地标节点           **");
    printf("\n\t**       (3)更新地标节点信息       **");
    printf("\n\t**       (4)修改路径信息           **");
    printf("\n\t*************************************\n");
    printf("请选择: ");
    a = input3();
    
    switch(a) {
        case 1:
            add_vertex();
            break;
            
        case 2:
            delete_vertex();
            break;
            
        case 3:
            update_vertex();
            break;
            
        case 4:
            modify_road_status();
            break;
    }
}

void function3() {
    modify(n, Q, B);
}