#ifndef VISIBILITY_HPP
#define VISIBILITY_HPP

// ID defines underlying platform supporting service registry
typedef char* Instance;

// Private implies namespace local config
const Instance Private = ".";
// Public implies config is visible to all
const Instance Public= "*";
// None implies service is visible to no one. Used for services only
const Instance None = "~";

#endif // VISIBILITY_HPP