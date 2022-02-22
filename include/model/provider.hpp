#ifndef PROVIDER_HPP
#define PROVIDER_HPP

// ID defines underlying platform supporting service registry
typedef char* ID;

class Provider {
public:
  ID Mock = "Mock";   // Mock is a service registry that contains 2 hard-coded test services
  ID Kubernetes = "Kubernetes";    // Kubernetes is a service registry backed by k8s API server
  ID External = "External";   // External is a service registry for externally provided ServiceEntries
};

#endif // PROVIDER_HPP