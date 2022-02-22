#include "mysql_manager.hpp"
#include "discovery/service_discovery.hpp"

#include <map>
#include <string>
#include <mysql/mysql.h>
#include <cstring>
#include <iostream>
using namespace std;

void ServiceDiscovery::init(){
  ConnectionInfo info;
  info.user = "root";
  info.password = "12345678";
  info.host = "localhost";
  info.port = 3306;
  info.database = "istio";
  info.unix_socket = NULL;
  info.clientflag = 0;
  mysql.Init(info);
}

Service* ServiceDiscovery::getServiceAndPrintQueryRes() {
  if (nullptr == mysql.getRES() || NULL == mysql.getRES()){
    return NULL;
  }

  MYSQL_FIELD* field = nullptr;
  //存字段名二维数组
  char fieldName[64][32];  

  // 获取字段名
  for (int i = 0; field = mysql_fetch_field(mysql.getRES()); ++i){
    strcpy(fieldName[i], field->name);
  }
  int columns = mysql_num_fields(mysql.getRES());
  for (int i = 0; i < columns; ++i) {
    printf("%10s\t", fieldName[i]);
  }
  printf("\n");

  MYSQL_ROW row;

  Service* ret = new Service[64];
  int cnt = 0;
    
  while (row = mysql_fetch_row(mysql.getRES())) {
    ServiceAttributes attribute;
    attribute.Name = row[0];
    Port p;
    p.Name = row[0];
    p.Port = atoi(row[1]);
    p.Protocol = row[2];

    map<string, string> label;
    label[row[3]] = row[4];
    ret[cnt].setService(attribute, &p, row[5], row[6]);
    cnt = cnt + 1;
        
    for (int i = 0; i < columns; ++i) {
      printf("%10s\t", row[i]);
    }
            
    printf("\n");
  }
  return ret;
}

ServiceInstance* ServiceDiscovery::getServiceInstanceAndPrintQueryRes() {
  if (nullptr == mysql.getRES() || NULL == mysql.getRES()) {
    return NULL;
  }

  MYSQL_FIELD* field = nullptr;

  char fieldName[64][32];  

  for (int i = 0; field = mysql_fetch_field(mysql.getRES()); ++i) {
    strcpy(fieldName[i], field->name);
  }

  int columns = mysql_num_fields(mysql.getRES());
  for (int i = 0; i < columns; ++i) {
    printf("%10s\t", fieldName[i]);
  }
  printf("\n");

  MYSQL_ROW row = mysql_fetch_row(mysql.getRES());

  ServiceAttributes attribute;
  attribute.Name = row[0];
  Port p;
  p.Name = row[0];
  p.Port = atoi(row[1]);
  p.Protocol = row[2];

  map<string, string> label;
  label[row[3]] = row[4];
  Service ser(attribute, &p, row[5], row[6]);
  ServiceInstance ret(ser, &p, row[5], row[6]);
        
  for (int i = 0; i < columns; ++i) {
    printf("%10s\t", row[i]);
  }     
  printf("\n");

  return &ret;
}

string ServiceDiscovery::getAccounts() {
  if (nullptr == mysql.getRES() || NULL == mysql.getRES()) {
    return NULL;
  }
  MYSQL_FIELD* field = nullptr;
  char fieldName[64][32];  

  for (int i = 0; field = mysql_fetch_field(mysql.getRES()); ++i) {
    strcpy(fieldName[i], field->name);
  }

  int columns = mysql_num_fields(mysql.getRES());
  for (int i = 0; i < columns; ++i) {
    printf("%10s\t", fieldName[i]);
  }
  printf("\n");

  MYSQL_ROW row;
  string ret;
    
  while (row = mysql_fetch_row(mysql.getRES())) {
    ret = ret + row[0] + "  ";
        
    for (int i = 0; i < columns; ++i) {
      printf("%10s\t", row[i]);
    }
            
    printf("\n");
  }
  return ret;
}

// 所有服务声明
Service* ServiceDiscovery::Services(){
    const char* sql = "SELECT DISTINCT serviceattributes.Name,portlists.Port,portlists.Protocol,keyName as Label_Key, valueName as Label_Value, ServiceAccounts, Address FROM service \
      join serviceattributes on serviceattributes.ServiceAttributes = service.ServiceAttributes\
      join portlists on portlists.PortLists = service.PortList\
      join service_labels on service_labels.Labels = serviceattributes.Labels;";
    mysql.QueryData(sql);
    // mysql.PrintQueryRes();
    Service* ret = getServiceAndPrintQueryRes();
    cout<<"Services() success"<<endl;
    return ret;
}


// 根据主机名检索服务(如果存在的话)
//,keyName as Label_Key, valueName as Label_Value,LabelSelectors, ResourceVersion 
Service* ServiceDiscovery::GetService(string name){
    std::string sqlstr = "SELECT DISTINCT serviceattributes.Name,portlists.Port,portlists.Protocol,keyName as Label_Key, valueName as Label_Value, ServiceAccounts, Address FROM service \
      join serviceattributes on serviceattributes.ServiceAttributes = service.ServiceAttributes\
      join portlists on portlists.PortLists = service.PortList\
      join service_labels on service_labels.Labels = serviceattributes.Labels\
      where serviceattributes.Name = '"+ name +"'";
    const char* sql = sqlstr.c_str();
    mysql.QueryData(sql);
    Service* ret = getServiceAndPrintQueryRes();
    cout<<"GetService() success"<<endl;
    return ret;
}

// 检索给定端口上具有匹配标签的服务实例
ServiceInstance* ServiceDiscovery::InstancesByPort(Service svc, int servicePort, map<string, string> Labels){
    string name = svc.getName();
    map<string, string>::iterator iter = Labels.begin();
    string sqlstr = "select serviceattributes.Name,Port,keyName as Label_Key, valueName as Label_Value,Address,ServiceAccount from serviceinstance \
      join istioendpoint on serviceinstance.Endpoint = istioendpoint.Endpoint\
      join serviceattributes on serviceattributes.ServiceAttributes = serviceinstance.ServiceAttributes\
      join service_labels on istioendpoint.Labels = service_labels.Labels\
      where serviceattributes.Name = '"+ name +"' and serviceinstance.Port = "+ std::to_string(servicePort) +" and keyName = '"+iter->first+"' and valueName = '"+iter->second +"'";
    // string sqlstr= "select * from serviceinstance join istioendpoint on serviceinstance.Endpoint = istioendpoint.Endpoint \
    // where ServiceAttributes = (\
    //   select ServiceAttributes from serviceattributes where Name = '"+ name +"')\
    //   and Port = "+ std::to_string(servicePort) +"\
    //   and istioendpoint.Labels = (select Labels from service_labels where keyName = '"+iter->first+"' and valueName = '"+iter->second +"');";
    const char* sql = sqlstr.c_str();
    mysql.QueryData(sql);
    ServiceInstance* ret = getServiceInstanceAndPrintQueryRes();
    cout<<"InstancesByPort() success"<<endl;
    return ret;
}

// 返回与给定代理共存的服务实例
// ServiceInstance[] GetProxyServiceInstances(string Proxy);

// map<string, string> Labels GetProxyWorkloadLabels(string Proxy);

// 返回查找的服务帐户列表
// 指定服务的主机名和端口
string ServiceDiscovery::GetIstioServiceAccounts(Service svc, int ports){
    string name = svc.getName();
    string sqlstr = "select ServiceAccounts,Name from service join serviceattributes on service.ServiceAttributes = serviceattributes.ServiceAttributes \
        where name = '" + name +"' and \
        PortList = (select PortLists from portlists where Port = " + std::to_string(ports) +")";
    const char* sql = sqlstr.c_str();
    mysql.QueryData(sql);
    string ret = getAccounts();
    // mysql.PrintQueryRes();
    cout<<"GetIstioServiceAccounts() success"<<endl;
    cout<<ret<<endl;
    return ret;
}

// ExportedServices返回通过Kubernetes多集群服务(MCS) ServiceExport API导出的服务的信息。仅适用于Kubernetes集群中的服务。
// ClusterServiceInfo* ServiceDiscovery::ExportedServices(){

// }
