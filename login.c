#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "login.h"

// 全局变量定义
ACC user[MAX_USERS];
int usernum = 0;

// 安全的密码输入函数
void getPassword(char *password) {
    int i = 0;
    char ch;
    
    while (1) {
        ch = getchar();
        if (ch == '\n' || ch == '\r') {
            break;
        } else if (ch == 8 && i > 0) { // 退格键
            i--;
            printf("\b \b");
        } else if (ch >= 32 && ch <= 126 && i < MAX_PASSWORD_LEN - 1) {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}

void userin() {
    usernum = 1;
    strcpy(user[0].account, "summer");
    strcpy(user[0].password, "123456");
}

int login() {
    char ac[MAX_ACCOUNT_LEN], pa[MAX_PASSWORD_LEN];
        
    printf("\n════════════════════ 用户登录 ════════════════════\n");
    printf("📝 账号: ");
    scanf("%s", ac);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // 清空缓冲区
       
    printf("🔒 密码: ");
    getPassword(pa);
    printf("═══════════════════════════════════════════════════\n");
    
    for(int k = 0; k < usernum; k++) {
        if(strcmp(ac, user[k].account) == 0) {
            if(strcmp(pa, user[k].password) == 0) {
                return 1;	
            } else {
                printf("\n❌ 密码错误！请重新输入！\n");
                return 0;
            }
        }	
    } 
    printf("\n❌ 账号不存在！\n");
    return 0;
}

void write_user(char ac[MAX_ACCOUNT_LEN], char pa[MAX_PASSWORD_LEN]) {
    FILE *filePtr = fopen("users.txt", "a");
    if (filePtr == NULL) {
        printf("无法打开文件！\n");
        return;
    }
    
    fprintf(filePtr, "%s\n", ac);
    fprintf(filePtr, "%s\n", pa);
    fclose(filePtr);
} 

void registe() {
    char ac[MAX_ACCOUNT_LEN], pa1[MAX_PASSWORD_LEN], pa2[MAX_PASSWORD_LEN];
    
    printf("\n════════════════════ 用户注册 ════════════════════\n");
    
    // 清空输入缓冲区
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    while(1) {
        int flag = 0; 
        printf("📝 请输入账号: ");
        scanf("%s", ac);
        
        for(int i = 0; i < usernum; i++) {
            if(strcmp(ac, user[i].account) == 0) {
                printf("❌ 该账号已存在，请重新输入！\n");
                flag = 1;
                break;
            }
        }
        if(flag == 0) break;
    }
    
    // 清空输入缓冲区
    while ((c = getchar()) != '\n' && c != EOF);
    
    while(1) {
        printf("🔒 请输入密码: ");
        getPassword(pa1);
        
        printf("🔒 请确认密码: ");
        getPassword(pa2);
        
        if(strcmp(pa1, pa2) == 0) {
            strcpy(user[usernum].account, ac);
            strcpy(user[usernum].password, pa1);			
            usernum++;
            write_user(ac, pa1);
            break;
        } else {
            printf("❌ 两次输入的密码不一样，请重新输入！\n");
        }
    }
    printf("✅ 账号注册成功！\n");
    printf("═══════════════════════════════════════════════════\n");
}

void loginpage() {
    userin();
    int choice;
    int flag = 0;
    
    while(!flag) {
        printf("\n");
        printf("╔══════════════════════════════════════════╗\n");
        printf("║          欢迎使用校园导航系统            ║\n");
        printf("╠══════════════════════════════════════════╣\n");
        printf("║  1. 🔐 登录                              ║\n");
        printf("║  2. 📝 注册                              ║\n");
        printf("║  0. 🚪 退出系统                          ║\n");
        printf("╚══════════════════════════════════════════╝\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: 
                flag = login(); 
                if(flag) {
                    printf("\n🎉 登录成功！即将进入主菜单...\n");
                    sleep(1);  // 延迟1秒显示成功信息
                }
                break;
            case 2: 
                registe(); 
                break;
            case 0: 
                printf("\n👋 感谢使用，再见！\n");
                exit(0);
            default: 
                printf("\n❌ 无效选择，请重新输入！\n");
        }
    }
}