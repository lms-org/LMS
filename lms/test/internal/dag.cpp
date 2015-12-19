#include "gtest/gtest.h"
#include "lms/internal/dag.h"

TEST(DAG, edge) {
    lms::internal::DAG<int> g;
    g.edge(1, 2);
    g.edge(2, 3);

    EXPECT_TRUE(g.hasEdge(1, 2));
    EXPECT_TRUE(g.hasEdge(2, 3));

    // No transitive edges
    EXPECT_FALSE(g.hasEdge(1, 3));

    // No reverse edges
    EXPECT_FALSE(g.hasEdge(2, 1));
    EXPECT_FALSE(g.hasEdge(3, 2));
}

TEST(DAG, removeEdge) {
    lms::internal::DAG<int> g;
    g.edge(1, 2);
    g.edge(2, 3);
    g.removeEdge(1, 2);

    ASSERT_FALSE(g.hasEdge(1, 2));
    ASSERT_TRUE(g.hasEdge(2, 3));
}

TEST(DAG, getFree) {
    lms::internal::DAG<int> g;
    g.edge(1, 2);
    g.edge(1, 3);

    int result;
    ASSERT_TRUE(g.getFree(result));
    EXPECT_EQ(1, result);
}

TEST(DAG, hasFree) {
    lms::internal::DAG<int> g;

    g.edge(2, 1);
    ASSERT_TRUE(g.hasFree());

    g.edge(1, 2);
    ASSERT_FALSE(g.hasFree());
}

TEST(DAG, removeEdgesFrom) {
    lms::internal::DAG<int> g;
    g.edge(1, 2);
    g.edge(1, 3);
    g.edge(2, 3);

    g.removeEdgesFrom(1);

    ASSERT_FALSE(g.hasEdge(1, 2));
    ASSERT_FALSE(g.hasEdge(1, 3));
    ASSERT_TRUE(g.hasEdge(2, 3));
}

TEST(DAG, hasCycle) {
    lms::internal::DAG<int> g;
    g.edge(1, 2);
    g.edge(2, 3);
    ASSERT_FALSE(g.hasCycle());

    g.edge(3, 1);
    ASSERT_TRUE(g.hasCycle());
}

TEST(DAG, empty) {
    lms::internal::DAG<int> g;
    ASSERT_TRUE(g.empty());

    g.edge(1, 2);
    ASSERT_FALSE(g.empty());
}

TEST(DAG, clear) {
    lms::internal::DAG<int> g;
    g.edge(1, 2);
    g.clear();

    ASSERT_TRUE(g.empty());
}

TEST(DAG, topoSort) {
    lms::internal::DAG<int> g;
    g.edge(1, 2);
    g.edge(2, 3);
    g.edge(3, 0);

    std::vector<int> result;
    ASSERT_TRUE(g.topoSort(result));

    EXPECT_EQ(std::vector<int>({1, 2, 3, 0}), result);

    g.edge(0, 1);
    ASSERT_FALSE(g.topoSort(result));
}
