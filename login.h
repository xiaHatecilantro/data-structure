#ifndef LOGIN_H
#define LOGIN_H

#define MAX_USERS 50
#define MAX_ACCOUNT_LEN 50
#define MAX_PASSWORD_LEN 50

struct account {
    char account[MAX_ACCOUNT_LEN];
    char password[MAX_PASSWORD_LEN];
};
typedef struct account ACC;

// 全局变量声明
extern ACC user[MAX_USERS];
extern int usernum;

// 函数声明
void userin();
int login();
void registe();
void loginpage();
void getPassword(char *password);

#endif