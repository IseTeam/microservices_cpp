#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

// Instance defines network protocols for ports
typedef char* Instance;

class Protocol {
public:
  // GRPC declares that the port carries gRPC traffic.
	Instance GRPC = "GRPC";
	// GRPCWeb declares that the port carries gRPC traffic.
	Instance GRPCWeb= "GRPC-Web";
	// HTTP declares that the port carries HTTP/1.1 traffic.
	// Note that HTTP/1.0 or earlier may not be supported by the proxy.
	Instance HTTP = "HTTP";
  // HTTP_PROXY declares that the port is a generic outbound proxy port.
	// Note that this is currently applicable only for defining sidecar egress listeners.
	// nolint
  Instance HTTP_PROXY = "HTTP_PROXY";
  // HTTP2 declares that the port carries HTTP/2 traffic.
  Instance HTTP2 = "HTTP2";
  // HTTPS declares that the port carries HTTPS traffic.
  Instance HTTPS = "HTTPS";
  // TCP declares the the port uses TCP.
	// This is the default protocol for a service port.
  Instance TCP = "TCP";
  // UDP declares that the port uses UDP.
	// Note that UDP protocol is not currently supported by the proxy.
  Instance UDP = "UDP";
  // MySQL declares that the port carries MySQL traffic.
  Instance MySQL = "MySQL";
  // Unsupported - value to signify that the protocol is unsupported.
  Instance Unsupported = "UnsupportedProtocol";

  // Parse from string ignoring case
  Instance Parse(char* s);
  int toUnicode(char* str);
  constexpr inline int U(const char* str);
};

#endif // PROTOCOL_HPP