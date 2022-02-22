#ifndef SERVICE_INSTANCE_HPP
#define SERVICE_INSTANCE_HPP

#include "provider.hpp"
#include "service.hpp"
#include "visibility.hpp"
#include "protocol.hpp"
#include "cluster.hpp"
#include <map>
#include <string>

using std::map;
using std::string;

// Locality information for an IstioEndpoint
struct Locality{
	// Label for locality on the endpoint. This is a "/" separated string.
	string Label;
	// ClusterID where the endpoint is located
	string ClusterID;
};


// IstioEndpoint defines a network address (IP:port) associated with an instance of the
// service. A service has one or more instances each running in a
// container/VM/pod.
struct IstioEndpoint {
  // Instance is a non empty map of arbitrary strings. Each version of a service can
  // be differentiated by a unique set of labels associated with the version. These
  // labels are assigned to all instances of a particular service version. For
  // example, lets say catalog.mystore.com has 2 versions v1 and v2. v1 instances
  // could have labels gitCommit=aeiou234, region=us-east, while v2 instances could
  // have labels name=kittyCat,region=us-east.
  map<string, string> Labels;

  // Address is the address of the endpoint, using envoy proto.
	string Address;

  // ServicePortName tracks the name of the port, this is used to select the IstioEndpoint by service port.
	string ServicePortName;

  // EnvoyEndpoint is a cached LbEndpoint, converted from the data, to
	// avoid recomputation
	// EnvoyEndpoint *endpoint.LbEndpoint

	// ServiceAccount holds the associated service account.
	string ServiceAccount;

	// Network holds the network where this endpoint is present
	// Network network.ID
  string Network;

	// The locality where the endpoint is present.
	struct Locality Locality;

	// EndpointPort is the port where the workload is listening, can be different
	// from the service port.
	int EndpointPort;

	// The load balancing weight associated with this endpoint.
	int LbWeight;

	// TLSMode endpoint is injected with istio sidecar and ready to configure Istio mTLS
	string TLSMode;

	// Namespace that this endpoint belongs to. This is for telemetry purpose.
	string Namespace;

	// Name of the workload that this endpoint belongs to. This is for telemetry purpose.
	string WorkloadName;

	// Specifies the hostname of the Pod, empty for vm workload.
	string HostName;

	// If specified, the fully qualified Pod hostname will be "<hostname>.<subdomain>.<pod namespace>.svc.<cluster domain>".
	string SubDomain;

	// The ingress tunnel supportability of this endpoint.
	// If this endpoint sidecar proxy does not support h2 tunnel, this endpoint will not show up in the EDS clusters
	// which are generated for h2 tunnel.
	int TunnelAbility;

	// Determines the discoverability of this endpoint throughout the mesh.
	// DiscoverabilityPolicy EndpointDiscoverabilityPolicy `json:"-"`
};


// ServiceInstance represents an individual instance of a specific version
// of a service. It binds a network endpoint (ip:port), the service
// description (which is oblivious to various versions) and a set of labels
// that describe the service version associated with this instance.
// Since a ServiceInstance has a single IstioEndpoint, which has a single port,
// multiple ServiceInstances are required to represent a workload that listens
// on multiple ports.
//
// The labels associated with a service instance are unique per a network endpoint.
// There is one well defined set of labels for each service instance network endpoint.
//
// For example, the set of service instances associated with catalog.mystore.com
// are modeled like this
//      --> IstioEndpoint(172.16.0.1:8888), Service(catalog.myservice.com), Labels(foo=bar)
//      --> IstioEndpoint(172.16.0.2:8888), Service(catalog.myservice.com), Labels(foo=bar)
//      --> IstioEndpoint(172.16.0.3:8888), Service(catalog.myservice.com), Labels(kitty=cat)
//      --> IstioEndpoint(172.16.0.4:8888), Service(catalog.myservice.com), Labels(kitty=cat)
class ServiceInstance {
public:
  Service ser;
  Port* ServicePort;
  IstioEndpoint Endpoint;

	ServiceInstance();
	ServiceInstance(Service svc, Port* p, string account, string add);
	void setServiceInstance(Service svc, Port* p, string account, string add);

};

#endif // SERVICE_INSTANCE_HPP