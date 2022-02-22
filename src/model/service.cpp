#include "model/service.hpp"

string Service::getName() {
    return Attributes.Name;
}

Service::Service() {}

Service::Service(ServiceAttributes attr, Port* p, string account, string add){
  Attributes = attr;
  Ports = p;
  ServiceAccounts = account;
  Address = add;
}

void Service::setService(ServiceAttributes attr, Port* p, string account, string add) {
  Attributes = attr;
  Ports = p;
  ServiceAccounts = account;
  Address = add;
}