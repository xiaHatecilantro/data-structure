#include <stdio.h>
#include <string.h>
#include "campus.h"

// 最短路径查询（Dijkstra算法实现）
void dijkstra(int start) {
    int i, j, u;
    int min_dist;
    //判断起点与各节点之间是否有直接路径
    for(i = 0; i < MAXV; i++) {
        if(road_status[start][i] == 0) {
            dist[i] = INF;
        } else {
            dist[i] = adjacency_matrix[start][i];
        }
        found[i] = 0;
        if(dist[i] < INF && i != start) {
            prev[i] = start;
        } else {
            prev[i] = -1;
        }
    }
    //把起点加入最短路径的集合
    found[start] = 1;
    dist[start] = 0;
    prev[start] = -1;
    //找下一个最近的节点
    for(i = 1; i < MAXV; i++) {
        min_dist = INF;
        u = -1;
        for(j = 0; j < MAXV; j++) {
            if(!found[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        
        if(u == -1) {
            break;
        }
        
        found[u] = 1;
        //遍历u的所有邻接节点j，如果通过u到j更短，则更新dist[j]和prev[j]
        for(j = 0; j < MAXV; j++) {
            if(!found[j] && adjacency_matrix[u][j] < INF && road_status[u][j] == 1) {
                if(dist[u] + adjacency_matrix[u][j] < dist[j]) {
                    dist[j] = dist[u] + adjacency_matrix[u][j];
                    prev[j] = u;
                }
            }
        }
    }
}

void print_shortest_path(int start, int target) {
    //用栈存储路径
    int stack[MAXV];
    int top = -1;
    //栈的特性(FILO),从最后一个节点往前推
    int current = target;
    
    if(dist[target] == INF) {
        printf("从 %s 到 %s 没有可达路径！\n", Q[start], Q[target]);
        return;
    }
    
    while(current != -1) {
        stack[++top] = current;
        current = prev[current];
    }
    
    printf("\n════════════════════ 最短路径信息 ════════════════════\n");
    printf("起点: %s\n", Q[start]);
    printf("终点: %s\n", Q[target]);
    printf("总距离: %d米\n", dist[target]);
    printf("最短路径: ");
    
    for(int i = top; i >= 0; i--) {
        printf("%s", Q[stack[i]]);
        if(i > 0) {
            printf(" → ");
        }
    }
    printf("\n");
    
    printf("路径状态: ");
    int has_blocked = 0;
    for(int i = top; i > 0; i--) {
        int from = stack[i];
        int to = stack[i-1];
        if(road_status[from][to] == 0) {
            has_blocked = 1;
            break;
        }
    }
    
    if(has_blocked) {
        printf("⚠️  包含禁行路段\n");
    } else {
        printf("✅ 所有路段正常通行\n");
    }
    
    printf("═══════════════════════════════════════════════════\n");
}

void find_shortest_path(int start_index, int end_index) {
    printf("\n════════════════════ 最短路径查询 ════════════════════\n");
    printf("起点: %s\n", Q[start_index]);
    printf("终点: %s\n", Q[end_index]);
    
    printf("\n正在计算从 %s 到 %s 的最短路径...\n", Q[start_index], Q[end_index]);
    
    memset(found, 0, sizeof(found));
    memset(prev, -1, sizeof(prev));
    
    dijkstra(start_index);
    
    print_shortest_path(start_index, end_index);
}

//查询所有路径(DFS算法实现)
void find_all_paths_dfs(int current, int target, int distance) {
    visited[current] = 1;
    path[path_count] = current;
    path_count++;
    
    if(current == target) {
        for(int i = 0; i < path_count; i++) {
            all_paths[total_paths][i] = path[i];
        }
        path_lengths[total_paths] = path_count;
        path_distances[total_paths] = distance;
        
        int blocked_count = 0;
        for(int i = 0; i < path_count - 1; i++) {
            int from = path[i];
            int to = path[i+1];
            if(road_status[from][to] == 0) {
                blocked_count++;
            }
        }
        path_blocked_segments[total_paths] = blocked_count;
        
        total_paths++;
    } else {
        for(int i = 0; i < MAXV; i++) {
            if(adjacency_matrix[current][i] != INF && !visited[i]) {
                find_all_paths_dfs(i, target, distance + adjacency_matrix[current][i]);
            }
        }
    }
    
    visited[current] = 0;
    path_count--;
}

void show_road_status() {
    printf("\n════════════════════ 道路状态信息 ════════════════════\n");
    printf("道路状态说明: ✅ 正常通行  ⚠️  临时禁行  ❌ 无连接\n\n");
    
    int has_blocked_roads = 0;
    
    for(int i = 0; i < n; i++) {
        printf("%s 的连接状态:\n", Q[i]);
        int has_connections = 0;
        
        for(int j = 0; j < n; j++) {
            if(i != j && adjacency_matrix[i][j] != INF) {
                has_connections = 1;
                printf("  → %s (%d米) ", Q[j], adjacency_matrix[i][j]);
                
                if(road_status[i][j] == 0) {
                    printf("⚠️  临时禁行\n");
                    has_blocked_roads = 1;
                } else {
                    printf("✅ 正常通行\n");
                }
            }
        }
        
        if(!has_connections) {
            printf("  无连接道路\n");
        }
        printf("\n");
    }
    
    if(!has_blocked_roads) {
        printf("✅ 所有道路均正常通行\n");
    }
    
    printf("═══════════════════════════════════════════════════\n");
}

void find_path_through_specified_point() {
    int start, end, through;
    
    printf("\n════════════════════ 经过指定地点的最短路径查询 ════════════════════\n");
    place(Q, n);
    
    printf("请输入起点编号(1-%d): ", n);
    scanf("%d", &start);
    printf("请输入途经点编号(1-%d): ", n);
    scanf("%d", &through);
    printf("请输入终点编号(1-%d): ", n);
    scanf("%d", &end);
    
    if(start < 1 || start > n || through < 1 || through > n || end < 1 || end > n) {
        printf("错误：输入的地点编号无效！\n");
        return;
    }
    
    if(start == through || through == end || start == end) {
        printf("错误：起点、途经点和终点不能相同！\n");
        return;
    }
    
    int start_index = start - 1;
    int through_index = through - 1;
    int end_index = end - 1;
    
    printf("\n正在计算从 %s 经过 %s 到 %s 的最短路径...\n", 
           Q[start_index], Q[through_index], Q[end_index]);
    
    memset(found, 0, sizeof(found));
    memset(prev, -1, sizeof(prev));
    //先计算起点到途经点的最短路径
    dijkstra(start_index);
    
    if(dist[through_index] == INF) {
        printf("错误：从 %s 到 %s 没有可达路径！\n", Q[start_index], Q[through_index]);
        return;
    }
    
    memset(found, 0, sizeof(found));
    memset(prev, -1, sizeof(prev));
    //再计算途经点到终点的最短路径
    dijkstra(through_index);
    
    if(dist[end_index] == INF) {
        printf("错误：从 %s 到 %s 没有可达路径！\n", Q[through_index], Q[end_index]);
        return;
    }
    
    printf("\n════════════════════ 路径结果 ════════════════════\n");
    printf("起点: %s\n", Q[start_index]);
    printf("途经点: %s\n", Q[through_index]);
    printf("终点: %s\n", Q[end_index]);
    printf("总距离: %d米\n", dist[through_index] + dist[end_index]);
    
    printf("\n第一段路径（起点→途经点）:\n");
    find_shortest_path(start_index, through_index);
    
    printf("\n第二段路径（途经点→终点）:\n");
    find_shortest_path(through_index, end_index);
    
    printf("═══════════════════════════════════════════════════\n");
}

void query_path_condition() {
    int start, end;
    
    printf("\n════════════════════ 路径状况查询 ════════════════════\n");
    place(Q, n);
    
    printf("请输入起点编号(1-%d): ", n);
    scanf("%d", &start);
    printf("请输入终点编号(1-%d): ", n);
    scanf("%d", &end);
    
    if(start < 1 || start > n || end < 1 || end > n) {
        printf("错误：输入的地点编号无效！\n");
        return;
    }
    
    if(start == end) {
        printf("错误：起点和终点不能相同！\n");
        return;
    }
    
    int start_index = start - 1;
    int end_index = end - 1;
    
    printf("\n════════════════════ 直接路径状况 ════════════════════\n");
    if(adjacency_matrix[start_index][end_index] != INF) {
        printf("起点: %s\n", Q[start_index]);
        printf("终点: %s\n", Q[end_index]);
        printf("距离: %d米\n", adjacency_matrix[start_index][end_index]);
        printf("状态: ");
        if(road_status[start_index][end_index] == 1) {
            printf("✅ 正常通行\n");
        } else {
            printf("⚠️  临时禁行\n");
        }
    } else {
        printf("%s 到 %s 没有直接连接的道路\n", Q[start_index], Q[end_index]);
    }
    
    printf("\n════════════════════ 所有连接道路状况 ════════════════════\n");
    printf("%s 的所有连接道路:\n", Q[start_index]);
    int has_connections = 0;
    for(int i = 0; i < n; i++) {
        if(i != start_index && adjacency_matrix[start_index][i] != INF) {
            has_connections = 1;
            printf("  → %s (%d米) ", Q[i], adjacency_matrix[start_index][i]);
            if(road_status[start_index][i] == 1) {
                printf("✅ 正常通行\n");
            } else {
                printf("⚠️  临时禁行\n");
            }
        }
    }
    if(!has_connections) {
        printf("  无连接道路\n");
    }
    
    printf("\n%s 的所有连接道路:\n", Q[end_index]);
    has_connections = 0;
    for(int i = 0; i < n; i++) {
        if(i != end_index && adjacency_matrix[end_index][i] != INF) {
            has_connections = 1;
            printf("  → %s (%d米) ", Q[i], adjacency_matrix[end_index][i]);
            if(road_status[end_index][i] == 1) {
                printf("✅ 正常通行\n");
            } else {
                printf("⚠️  临时禁行\n");
            }
        }
    }
    if(!has_connections) {
        printf("  无连接道路\n");
    }
    
    printf("═══════════════════════════════════════════════════\n");
}

void find_paths_between_points() {
    int start, end;
    int query_type;
    
    printf("\n════════════════════ 路径查询 ════════════════════\n");
    place(Q, n);
    printf("请输入起点编号(1-%d): ", n);
    scanf("%d", &start);
    printf("请输入终点编号(1-%d): ", n);
    scanf("%d", &end);
    
    if(start < 1 || start > n || end < 1 || end > n) {
        printf("错误：输入的地点编号无效！\n");
        return;
    }
    
    if(start == end) {
        printf("错误：起点和终点不能相同！\n");
        return;
    }
    
    int start_index = start - 1;
    int end_index = end - 1;
    
    printf("\n请选择查询类型：\n");
    printf("1. 🗺️  查找所有路径\n");
    printf("2. ⚡ 查找最短路径\n");
    printf("3. 📍 查询经过指定地点的最短路径\n");
    printf("4. 📊 查询路径状况\n");
    printf("请选择(1-4): ");
    scanf("%d", &query_type);
    
    // 查询两点间所有连接路径，并输出最短的三条
    if(query_type == 1) {
        printf("\n正在查找从 %s 到 %s 的所有路径...\n", Q[start_index], Q[end_index]);
        
        memset(visited, 0, sizeof(visited));
        path_count = 0;
        total_paths = 0;
        
        find_all_paths_dfs(start_index, end_index, 0);
        
        if(total_paths == 0) {
            printf("\n未找到从 %s 到 %s 的路径！\n", Q[start_index], Q[end_index]);
        } else {
            printf("\n共找到 %d 条路径，显示最短的3条：\n", total_paths);
            printf("═══════════════════════════════════════════════════\n");
            
            // 采用冒泡排序法对路径按距离进行排序
            for(int i = 0; i < total_paths - 1; i++) {
                for(int j = 0; j < total_paths - i - 1; j++) {
                    if(path_distances[j] > path_distances[j + 1]) {
                        int temp_dist = path_distances[j];
                        path_distances[j] = path_distances[j + 1];
                        path_distances[j + 1] = temp_dist;
                        
                        int temp_len = path_lengths[j];
                        path_lengths[j] = path_lengths[j + 1];
                        path_lengths[j + 1] = temp_len;
                        
                        int temp_blocked = path_blocked_segments[j];
                        path_blocked_segments[j] = path_blocked_segments[j + 1];
                        path_blocked_segments[j + 1] = temp_blocked;
                        
                        for(int k = 0; k < MAXV; k++) {
                            int temp = all_paths[j][k];
                            all_paths[j][k] = all_paths[j + 1][k];
                            all_paths[j + 1][k] = temp;
                        }
                    }
                }
            }
            
            int display_count = total_paths < 3 ? total_paths : 3;
            
            for(int i = 0; i < display_count; i++) {
                printf("\n路径 %d (总距离: %d米):\n", i + 1, path_distances[i]);
                
                if(i == 0) {
                    printf("★ 最短路径");
                }
                if(path_blocked_segments[i] > 0) {
                    printf(" ⚠️  包含%d个禁行路段", path_blocked_segments[i]);
                } else {
                    printf(" ✅ 所有路段正常通行");
                }
                printf("\n");
                
                printf("路线: ");
                for(int j = 0; j < path_lengths[i]; j++) {
                    int place_index = all_paths[i][j];
                    printf("%s", Q[place_index]);
                    if(j < path_lengths[i] - 1) {
                        printf(" → ");
                    }
                }
                printf("\n");
                
                printf("详细路径: \n");
                for(int j = 0; j < path_lengths[i] - 1; j++) {
                    int from = all_paths[i][j];
                    int to = all_paths[i][j + 1];
                    printf("  %s → %s (%d米) ", Q[from], Q[to], adjacency_matrix[from][to]);
                    
                    if(road_status[from][to] == 0) {
                        printf("⚠️  临时禁行\n");
                    } else {
                        printf("✅ 正常通行\n");
                    }
                }
                printf("--------------------------------------------\n");
            }
            
            if(total_paths > 3) {
                printf("\n... 还有 %d 条路径未显示，最短距离为: %d米\n", 
                       total_paths - 3, path_distances[0]);
            }
        }
        
    } else if(query_type == 2) {
        find_shortest_path(start_index, end_index);
        
    } else if(query_type == 3) {
        find_path_through_specified_point();
        
    } else if(query_type == 4) {
        query_path_condition();
        
    } else {
        printf("错误：输入无效！\n");
    }
}

void function4() {
    find_paths_between_points();
}