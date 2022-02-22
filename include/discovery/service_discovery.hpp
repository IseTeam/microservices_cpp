#ifndef SERVICE_DISCOVERY_HPP
#define SERVICE_DISCOVERY_HPP


#include "../model/service.hpp"
#include "../model/service_instance.hpp"
#include "../mysql_manager.hpp"

// ClusterServiceInfo将服务的名称与特定的Kubernetes集群组合在一起。这用于调试关于Kubernetes多集群服务(MCS)状态的信息。
struct ClusterServiceInfo {
	string  Name;    
	string  Namespace;
	string  Cluster;
};

class ServiceDiscovery {
public:
  // 所有服务声明
  Service* Services();

  // 根据主机名检索服务(如果存在的话)
  Service* GetService(string name);

  // 检索给定端口上具有匹配标签的服务实例
  ServiceInstance* InstancesByPort(Service svc, int servicePort, map<string, string> Labels);

  // 返回与给定代理共存的服务实例
  // ServiceInstance[] GetProxyServiceInstances(string Proxy);

  // map<string, string> Labels GetProxyWorkloadLabels(string Proxy);

  // 返回查找的服务帐户列表
	// 指定服务的主机名和端口
  string GetIstioServiceAccounts(Service svc, int ports);

  // ExportedServices返回通过Kubernetes多集群服务(MCS) ServiceExport API导出的服务的信息。仅适用于Kubernetes集群中的服务。
  ClusterServiceInfo* ExportedServices();

  void init();
  Service* getServiceAndPrintQueryRes();
  ServiceInstance* getServiceInstanceAndPrintQueryRes();
  string getAccounts();
  MySQLManager mysql;
};

#endif // SERVICE_DISCOVERY_HPP