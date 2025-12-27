#include <stdio.h>
#include <string.h>
#include "campus.h"

// 显示所有地点信息的函数
void show_all_places() {
    printf("\n════════════════════ 所有地点信息 ════════════════════\n");
    printf("当前共有 %d 个地标节点：\n", n);
    printf("┌──────┬────────────────────┬────────────────────────────┐\n");
    printf("│ 编号 │      地点名称      │          描述信息          │\n");
    printf("├──────┼────────────────────┼────────────────────────────┤\n");
    
    for(int i = 0; i < n; i++) {
        printf("│ %4d │ %-18s │ ", B[i], Q[i]);
        
        switch(B[i]) {
            case 1: 
                printf("学校的正门，放有代表校区门面的大理石");
                break;
            case 2: 
                printf("图书馆，是卷王们奋斗的地方");
                break;
            case 3: 
                printf("体育馆，小的可怜，保持了先到先得的传统");
                break;
            case 4: 
                printf("同学们课余时间锻炼身体的地方");
                break;
            case 5: 
                printf("学生们休息的地方");
                break;
            case 6: 
                printf("平时购买生活物品的地方");
                break;
            case 7: 
                printf("真正的'超市'，接收快递的地方");
                break;
            case 8: 
                printf("同学们的心灵港湾");
                break;
            case 9: 
                printf("平时生小病看病开药的地方");
                break;
            case 10: 
                printf("商学院根据地");
                break;
            case 11: 
                printf("外包食堂，味道尚可");
                break;
            case 12: 
                printf("思政老师的办公地");
                break;
            case 13: 
                printf("教师公寓");
                break;
            case 14: 
                printf("食院根据地，有很多高大上的实验室");
                break;
            case 15: 
                printf("两大通识课主教学楼之一，戏称'生死楼'");
                break;
            case 16: 
                printf("海上风电实验室");
                break;
            case 17: 
                printf("集机院，计院，材院于一体的学院楼");
                break;
            case 18: 
                printf("合成金属实验室");
                break;
            default:
                // 对于新增的自定义节点，显示通用描述
                printf("用户自定义地标节点");
                break;
        }
        printf(" │\n");
    }
    printf("└──────┴────────────────────┴────────────────────────────┘\n");
    printf("═══════════════════════════════════════════════════\n");
}

// 显示单个地点详细信息
void show_single_place(int place_id) {
    printf("\n════════════════════ 地点详细信息 ════════════════════\n");
    
    // 查找地点索引
    int found_index = -1;
    for(int i = 0; i < n; i++) {
        if(B[i] == place_id) {
            found_index = i;
            break;
        }
    }
    
    if(found_index == -1) {
        printf("错误：未找到编号为 %d 的地点！\n", place_id);
        printf("═══════════════════════════════════════════════════\n");
        return;
    }
    
    printf("地点编号: %d\n", B[found_index]);
    printf("地点名称: %s\n", Q[found_index]);
    printf("描述信息: ");
    
    // 根据编号显示对应的详细描述信息
    switch(place_id) {
        case 1: 
            printf("学校门口\n");
            printf("   学校的正门，放有代表校区门面的大理石，是学校的形象展示窗口。\n");
            break;
        case 2: 
            printf("海纳楼\n");
            printf("   图书馆，是卷王们奋斗的地方，藏书丰富，学习氛围浓厚。\n");
            break;
        case 3: 
            printf("海阳馆\n");
            printf("   体育馆，虽然面积不大，但保持了先到先得的传统，是同学们锻炼的好去处。\n");
            break;
        case 4: 
            printf("运动场\n");
            printf("   同学们课余时间锻炼身体的地方，有跑道、足球场等设施。\n");
            break;
        case 5: 
            printf("学生宿舍\n");
            printf("   学生们休息的地方，生活设施齐全，是学生在校的温馨小家。\n");
            break;
        case 6: 
            printf("超市\n");
            printf("   平时购买生活物品的地方，商品种类丰富，方便学生日常生活。\n");
            break;
        case 7: 
            printf("菜鸟驿站\n");
            printf("   真正的'超市'，接收快递的地方，每天都有大量的包裹进出。\n");
            break;
        case 8: 
            printf("心理咨询中心\n");
            printf("   同学们的心灵港湾，提供专业的心理咨询服务。\n");
            break;
        case 9: 
            printf("校医室\n");
            printf("   平时生小病看病开药的地方，有专业的医护人员值班。\n");
            break;
        case 10: 
            printf("济航楼\n");
            printf("   商学院根据地，商科专业的主要教学和办公场所。\n");
            break;
        case 11: 
            printf("桃李食苑\n");
            printf("   外包食堂，味道尚可，提供各种风味的美食。\n");
            break;
        case 12: 
            printf("人文与教育学院\n");
            printf("   思政老师的办公地，人文社科类课程的主要教学场所。\n");
            break;
        case 13: 
            printf("琴苑\n");
            printf("   教师公寓，为在校教师提供舒适的居住环境。\n");
            break;
        case 14: 
            printf("海科楼\n");
            printf("   食院根据地，有很多高大上的实验室，食品科学专业的教学科研中心。\n");
            break;
        case 15: 
            printf("慎思楼\n");
            printf("   两大通识课主教学楼之一，戏称'生死楼'，承载着许多学生的通识课程记忆。\n");
            break;
        case 16: 
            printf("风电实验室\n");
            printf("   海上风电实验室，专注于风电技术的研究与开发。\n");
            break;
        case 17: 
            printf("厚为楼\n");
            printf("   集机院，计院，材院于一体的学院楼，工科专业的重要基地。\n");
            break;
        case 18: 
            printf("合金实验室\n");
            printf("   合成金属实验室，专注于金属材料的研究与开发。\n");
            break;
        default:
            printf("用户自定义地标节点\n");
            printf("   这是一个用户自定义添加的地标节点，可以根据需要设置具体功能。\n");
            break;
    }
    
    // 显示该地点的连接信息
    printf("\n连接道路信息:\n");
    int has_connections = 0;
    for(int i = 0; i < n; i++) {
        if(i != found_index && adjacency_matrix[found_index][i] != INF) {
            has_connections = 1;
            printf("  → %s (%d米) ", Q[i], adjacency_matrix[found_index][i]);
            if(road_status[found_index][i] == 1) {
                printf("✅ 正常通行\n");
            } else {
                printf("⚠️  临时禁行\n");
            }
        }
    }
    
    if(!has_connections) {
        printf("   暂无连接道路\n");
    }
    
    printf("═══════════════════════════════════════════════════\n");
}


void Description(char Q[MAXV][MAXV], int n, int B[MAXV]) {
    int choice;
    
    do {
        printf("\n════════════════════ 地点信息查看 ════════════════════\n");
        printf("1. 查看所有地点信息\n");
        printf("2. 查看单个地点详细信息\n");
        printf("3. 返回上级菜单\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                show_all_places();
                break;
            case 2:
                printf("\n");
                place(Q, n);
                printf("请输入你要查询的地标编号(输入666返回): ");
                int y = input2(n, B);
                if(y == 666) break;
                show_single_place(y);
                break;
            case 3:
                return;
            default:
                printf("输入错误，请重新选择！\n");
        }
    } while(choice != 3);
}

void function2() {
    Description(Q, n, B);
}