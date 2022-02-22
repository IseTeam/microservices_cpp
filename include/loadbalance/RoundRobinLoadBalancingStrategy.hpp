#ifndef ROUNDROBINLOADBALANCINGSTRATEGY_HPP
#define ROUNDROBINLOADBALANCINGSTRATEGY_HPP

#include "ILoadBalancingStrategy.hpp"

template <class T>
class RoundRobinLoadBalancingStrategy : public ILoadBalancingStrategy<T> {
public:
  RoundRobinLoadBalancingStrategy() : m_current{0} {}

  virtual inline std::shared_ptr<T> next(const std::vector<std::shared_ptr<T>>& clients) override {
    if(clients.empty())
      return nullptr;

    if(m_current >= clients.size()) {
      m_current = 0;
    }

    auto current = m_current;
    ++m_current;

    return clients.at(current);
  }

private:
  uint32_t m_current;
};

#endif // ROUNDROBINLOADBALANCINGSTRATEGY_HPP