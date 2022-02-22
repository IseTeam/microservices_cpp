#include <spdlog/spdlog.h>
#include <mysql/mysql.h>
#include <iostream>
#include "model/service.hpp"
#include "model/service_instance.hpp"
#include "discovery/service_discovery.hpp"

int main(int argc, char** argv) {
    ServiceDiscovery servicediscovery;
    servicediscovery.init();
    servicediscovery.Services();

    ServiceAttributes attribute;
    map<string, string> label;
    label["kitty"] = "cat";
    attribute.Name = "test";
    attribute.Labels = label;

    Port p;
    p.Name = "test";
    p.Port = 8888;
    p.Protocol = "HTTP";
    Service service(attribute, &p, "jyx","127.0.0.1");
    servicediscovery.InstancesByPort(service, 8888, label);
    servicediscovery.GetIstioServiceAccounts(service, 8888);
    servicediscovery.GetService("test");
    servicediscovery.mysql.FreeConnect();
    return 0;
}