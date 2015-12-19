#ifndef LMS_INTERNAL_DAG_H
#define LMS_INTERNAL_DAG_H

#include <map>
#include <set>

namespace lms {
namespace internal {

/**
 * @brief Templated directed acyclic graph.
 *
 * https://en.wikipedia.org/wiki/Directed_acyclic_graph
 *
 * This implementation is not thread-safe.
 */
template<typename T>
class DAG {
private:
    typedef std::map<T, std::set<T>> GraphType;
    GraphType m_data;
public:
    /**
     * @brief Add an edge from dependency to node.
     *
     * The nodes will be created if not yet existent.
     *
     * @param node target node
     * @param dependency source node
     */
    void edge(T const& from, T const& to) {
        m_data[to].insert(from);
        m_data[from];
    }

    /**
     * @brief Create a node.
     *
     * Does nothing if node was already there.
     *
     * @param node node to be created
     */
    void node(T const& node) {
        m_data[node];
    }

    /**
     * @brief Check if the graph contains an edge.
     * @param node
     * @param dependency
     * @return
     */
    bool hasEdge(T const& from, T const& to) const {
        typename GraphType::const_iterator it = m_data.find(to);
        return it != m_data.end() && 1 == it->second.count(from);
    }

    /**
     * @brief Remove an edge.
     *
     * Does nothing if edge was not existent.
     *
     * @param from source node
     * @param to target node
     */
    void removeEdge(T const& from, T const& to) {
        typename GraphType::iterator it = m_data.find(to);
        if(it != m_data.end()) {
            it->second.erase(from);
        }
    }

    /**
     * @brief Check if the graph contains any free node.
     * @return true if a free node was found, false otherwise
     */
    bool hasFree() const {
        for(typename GraphType::const_iterator it = m_data.begin(); it != m_data.end(); it++) {
            if(it->second.empty()) {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Search for a node having no incoming edges.
     * @param result The node value will be assigned to this parameter
     * @return true if a free node was found and result was assigned, false
     * otherwise
     */
    bool getFree(T& result) const {
        for(typename GraphType::const_iterator it = m_data.begin(); it != m_data.end(); it++) {
            if(it->second.empty()) {
                result = it->first;
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Search for a node having no incoming edges and remove it.
     * @param result The node value will be assigned to this parameter
     * @return true if a free node was found and result was assigned, false
     * otherwise
     */
    bool getAndRemoveFree(T& result) {
        for(typename GraphType::iterator it = m_data.begin(); it != m_data.end(); it++) {
            if(it->second.empty()) {
                result = it->first;
                m_data.erase(it);
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Delete all edges coming from a certain node.
     * @param node source node
     */
    void removeEdgesFrom(T const& from) {
        for(auto & pair : m_data) {
            pair.second.erase(from);
        }
    }

    /**
     * @brief Check if the graph contains no nodes or dependencies
     * @return true if graph is empty, false otherwise
     */
    bool empty() const {
        return m_data.empty();
    }

    /**
     * @brief Check if the dependency graph has any circles or may come
     * into state where there are no free nodes.
     * @return true if the graph may get deadlocked, false otherwise
     */
    bool hasCycle() const {
        DAG copy(*this);

        T node;
        while(copy.getAndRemoveFree(node)) {
            copy.removeEdgesFrom(node);
        }

        return !copy.empty();
    }

    /**
     * @brief Delete all nodes and edges.
     */
    void clear() {
        m_data.clear();
    }

    /**
     * @brief Perform a topological sort on the graph.
     *
     * https://en.wikipedia.org/wiki/Topological_sorting
     *
     * The result parameter must a list type that supports push_back. Therefore
     * the template parameter should be std::vector, std::list or std::deque.
     *
     * @param result The sorted node list will push_back'ed to this parameter
     * @return true if sorting was successful, false if the graph contains
     * cycles
     */
    template<typename ListType>
    bool topoSort(ListType & result) {
        DAG copy(*this);

        T node;
        while(copy.getAndRemoveFree(node)) {
            copy.removeEdgesFrom(node);
            result.push_back(node);
        }

        return copy.empty();
    }

    /**
     * @brief Iterator to the internal data structure.
     * @return read-only begin iterator
     */
    typename GraphType::iterator begin() const {
        return m_data.begin();
    }

    /**
     * @brief Iterator to the internal data structure.
     * @return  read-only end iterator
     */
    typename GraphType::iterator end() const {
        return m_data.end();
    }
};

}  // namespace internal
}  // namespace lms

#endif // LMS_INTERNAL_DAG_H
