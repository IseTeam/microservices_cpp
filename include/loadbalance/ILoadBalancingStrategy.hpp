#ifndef ILOADBALANCINGSTRATEGY_HPP
#define ILOADBALANCINGSTRATEGY_HPP

#include <memory>
#include <vector>

template<class T>
class ILoadBalancingStrategy {
public:
  virtual std::shared_ptr<T> next(const std::vector<std::shared_ptr<T>>& clients) = 0;
};

#endif // ILOADBALANCINGSTRATEGY_HPP
