#include "model/service_instance.hpp"

ServiceInstance::ServiceInstance() {}

ServiceInstance::ServiceInstance(Service svc, Port* p, string account, string add) {
  ser = svc;
  ServicePort = p;
  IstioEndpoint end;
  end.Address = add;
  end.ServiceAccount = account;
}

void ServiceInstance::setServiceInstance(Service svc, Port* p, string account, string add) {
    ser = svc;
    ServicePort = p;
    IstioEndpoint end;
    end.Address = add;
    end.ServiceAccount = account;
}
