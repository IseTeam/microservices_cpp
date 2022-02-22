#include "mysql_manager.hpp"
#include <spdlog/spdlog.h>

#include <stdio.h>

bool MySQLManager::Init(ConnectionInfo& info) {
  mysql_init(&m_mysql);

  if (!(mysql_real_connect(&m_mysql, info.host, info.user, info.password, info.database, info.port, info.unix_socket, info.clientflag))) {
    return false;
  }

  return true;
}

bool MySQLManager::FreeConnect() {
  mysql_free_result(m_res);
  mysql_close(&m_mysql);

  return false;
}


bool MySQLManager::ExecuteSql(const char * sql) {
  if (mysql_query(&m_mysql, sql)) {
    spdlog::error("执行sql语句失败，错误信息为： {}", mysql_error(&m_mysql));
    return false;
  } else {
    spdlog::info("执行sql语句成功！");
  }

  return true;
}

MYSQL_RES* MySQLManager::QueryData(const char* sql) {
  if (mysql_query(&m_mysql, sql)) {
    spdlog::error("查询语句执行失败，错误信息为： {}", mysql_error(&m_mysql));
    return nullptr;
  } else {
    spdlog::info("查询语句执行成功！");
  }

  m_res = mysql_store_result(&m_mysql);
  return m_res;
}

// 遍历结果集
void MySQLManager::PrintQueryRes()
{
  if (nullptr == m_res || NULL == m_res)
    return;

  MYSQL_FIELD* field = nullptr;

  char fieldName[64][32];  

  for (int i = 0; field = mysql_fetch_field(m_res); ++i) {
    strcpy(fieldName[i], field->name);
  }

  int columns = mysql_num_fields(m_res);
  for (int i = 0; i < columns; ++i){
    printf("%10s\t", fieldName[i]);
  }
  printf("\n");

  MYSQL_ROW row;
  while (row = mysql_fetch_row(m_res)) {
    for (int i = 0; i < columns; ++i){
      printf("%10s\t", row[i]);
    }    
    printf("\n");
  }

}

MYSQL_RES* MySQLManager::getRES(){
    return m_res;
}