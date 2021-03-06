#ifndef IP_TABLES_HANDLER_HPP
#define IP_TABLES_HANDLER_HPP

#include <string>

#include "./chainMap.hpp"
#include "./rule.hpp"

namespace iptables {
class IpTablesHandler {
 public:
  /**
   * @brief Construct a new Ip Tables Handler object
   *
   */
  IpTablesHandler() {}

  /**
   * @brief Destroy the Ip Tables Handler object
   *
   */
  ~IpTablesHandler() {}

  /**
   * @brief Initialize the handler
   *
   */
  void initialize();

  /**
   * @brief Append chain to iptables
   *
   * @param chainName
   * @param ruleNum
   */
  void appendRuleToChain(std::string& chainName, Rule& rule);

  /**
   * @brief Delete chain from iptables
   *
   * @param chainName
   */
  void deleteRuleFromChain(std::string& chainName, Rule& rule);

  /**
   * @brief Insert chain in iptables
   *
   * @param chainName
   */
  void insertRuleIntoChain(std::string& chainName, unsigned int ruleNum, Rule& rule);

  /**
   * @brief Replace chain in iptables
   *
   * @param chainName
   */
  void replaceRuleInChain(std::string& chainName, unsigned int ruleNum, Rule& rule);

  /**
   * @brief List all chains in iptables
   *
   */
  void listAllRulesInChain(std::string& chainName);

  /**
   * @brief List chain rule in iptables
   *
   */
  void listRuleInChain(std::string& chainName, Rule& rule);

  /**
   * @brief Shutdown the handler
   *
   */
  void shutdown();

 private:
  /**
   * @brief Write the iptables header to the rules file
   *
   */
  void writeHeaderToRulesFile();

  /**
   * @brief Write iptables footer to the rules file
   *
   */
  void writeFooterToRulesFile();

  /**
   * @brief Format entry for ip tables
   *
   * @param rule            The rule object
   * @return std::string    Formatted string
   */
  std::string formatEntryForIpTables(Rule& rule);

  /**
   * @brief Commit entry to ip tables
   *
   * @param entry   The entry, formatted a string
   */
  void commitEntryToIpTables(std::string& entry);

  /**
   * @brief Restore rules from file
   *
   */
  void restoreRulesFromFile();

  /**
   * @brief Backup rules to Json file
   *
   */
  void backupRulesToJsonFile();

  ChainMap* chainMap;
};
}  // namespace iptables
#endif  // IP_TABLES_HANDLER_HPP