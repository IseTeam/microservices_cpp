#ifndef MYSQL_MANAGER_HPP
#define MYSQL_MANAGER_HPP

#include "mysql/mysql.h"

struct ConnectionInfo {
    const char* host;            // 主机地址
    const char* user;            // 用户名
    const char* password;        // 密码
    const char*    database;        // 数据库名
    unsigned int port;            // 端口号
    const char*    unix_socket;    // unix连接标识
    unsigned long clientflag;    // 客户端连接标志

    // 构造函数，设置一些默认值
    ConnectionInfo() :
        host("127.0.0.1"),
        user("root"),
        password("12345678"),
        database("istio"),
        port(3306),
        unix_socket(NULL),
        clientflag(0) {}
};

class MySQLManager {
public:
  bool Init(ConnectionInfo& info);

  bool FreeConnect();

  bool ExecuteSql(const char* sql);

  MYSQL_RES* QueryData(const char* sql);

  void PrintQueryRes();
    
  MYSQL_RES* getRES();

private:
  MYSQL m_mysql;
  MYSQL_RES* m_res;
};

#endif // MYSQL_MANAGER_HPP