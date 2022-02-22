#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include <map>
#include <string>
using std::string;
using std::map;

// AddressMap provides a thread-safe mapping of addresses for each Kubernetes cluster.
typedef char* Instance;
// typedef string ID;

struct AddressMap{
	// Addresses hold the underlying map. Visible only for testing, for the purposes of simplified construction.
	// Production code should never access this directly.
	//map<ID ,string> Addresses;
	map<string ,string> Addresses;
};

#endif // CLUSTER_HPP