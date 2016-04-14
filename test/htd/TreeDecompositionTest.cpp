/*
 * File:   TreeDecompositionTest.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015, Michael Abseher
 *    E-Mail: <abseher@dbai.tuwien.ac.at>
 *
 * This file is part of htd.
 *
 * htd is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * htd is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.

 * You should have received a copy of the GNU General Public License
 * along with htd.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <htd/main.hpp>

#include <vector>

class TreeDecompositionTest : public ::testing::Test
{
    public:
        TreeDecompositionTest(void)
        {

        }

        ~TreeDecompositionTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(TreeDecompositionTest, CheckEmptyTree)
{
    htd::TreeDecomposition decomposition;

    ASSERT_EQ((std::size_t)0, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.edgeCount());

    ASSERT_EQ((std::size_t)0, decomposition.vertices().size());
    ASSERT_EQ((std::size_t)0, decomposition.hyperedges().size());

    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertices().size());

    ASSERT_TRUE(decomposition.isConnected());

    ASSERT_EQ((std::size_t)0, decomposition.leafNodeCount());

    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertexCount());

    try
    {
        decomposition.root();

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }
}

TEST(TreeDecompositionTest, CheckSize1Tree)
{
    htd::TreeDecomposition decomposition;

    ASSERT_EQ((std::size_t)0, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.edgeCount());

    ASSERT_EQ((std::size_t)0, decomposition.vertices().size());
    ASSERT_EQ((std::size_t)0, decomposition.hyperedges().size());

    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertices().size());

    ASSERT_TRUE(decomposition.isConnected());

    ASSERT_EQ((std::size_t)0, decomposition.leafNodeCount());

    try
    {
        decomposition.root();

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    htd::vertex_t root = decomposition.insertRoot();

    ASSERT_TRUE(decomposition.isVertex(root));
    ASSERT_TRUE(decomposition.isRoot(root));
    ASSERT_EQ(root, decomposition.root());

    ASSERT_EQ((std::size_t)1, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.edgeCount());
    ASSERT_EQ((std::size_t)0, decomposition.edgeCount(root));

    ASSERT_EQ((std::size_t)1, decomposition.vertices().size());
    ASSERT_EQ((std::size_t)0, decomposition.hyperedges().size());

    ASSERT_EQ((std::size_t)1, decomposition.isolatedVertexCount());
    ASSERT_EQ((std::size_t)1, decomposition.isolatedVertices().size());

    ASSERT_TRUE(decomposition.isConnected());

    ASSERT_EQ((std::size_t)1, decomposition.leafNodeCount());
    ASSERT_EQ((std::size_t)1, decomposition.leafNodes().size());
    ASSERT_EQ((htd::vertex_t)1, decomposition.leafNodes()[0]);

    ASSERT_EQ((std::size_t)1, decomposition.isolatedVertexCount());
    ASSERT_EQ(root, decomposition.isolatedVertices()[0]);
    ASSERT_EQ(root, decomposition.isolatedVertexAtPosition(0));
    ASSERT_TRUE(decomposition.isIsolatedVertex(root));
}

TEST(TreeDecompositionTest, CheckSize3Tree)
{
    htd::TreeDecomposition decomposition;

    ASSERT_EQ((std::size_t)0, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.edgeCount());

    ASSERT_EQ((std::size_t)0, decomposition.vertices().size());
    ASSERT_EQ((std::size_t)0, decomposition.hyperedges().size());

    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertices().size());

    ASSERT_TRUE(decomposition.isConnected());

    ASSERT_EQ((std::size_t)0, decomposition.leafNodeCount());

    try
    {
        decomposition.root();

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    htd::vertex_t root = decomposition.insertRoot();

    htd::vertex_t child = decomposition.addChild(root);

    ASSERT_NE(root, child);

    ASSERT_TRUE(decomposition.isVertex(root));
    ASSERT_TRUE(decomposition.isVertex(child));
    ASSERT_TRUE(decomposition.isRoot(root));
    ASSERT_EQ(root, decomposition.root());

    ASSERT_EQ((std::size_t)2, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)1, decomposition.edgeCount());
    ASSERT_EQ((std::size_t)1, decomposition.edgeCount(root));
    ASSERT_EQ((std::size_t)1, decomposition.edgeCount(child));

    ASSERT_EQ((std::size_t)2, decomposition.vertices().size());
    ASSERT_EQ((std::size_t)1, decomposition.hyperedges().size());

    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertices().size());

    ASSERT_TRUE(decomposition.isConnected());

    ASSERT_EQ((std::size_t)1, decomposition.leafNodeCount());

    ASSERT_TRUE(decomposition.isChild(root, child));
    ASSERT_FALSE(decomposition.isChild(child, root));

    htd::vertex_t newRoot = decomposition.addParent(root);

    ASSERT_TRUE(decomposition.isVertex(root));
    ASSERT_TRUE(decomposition.isVertex(child));
    ASSERT_TRUE(decomposition.isVertex(newRoot));
    ASSERT_TRUE(decomposition.isRoot(newRoot));
    ASSERT_EQ(newRoot, decomposition.root());

    ASSERT_EQ((std::size_t)3, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)2, decomposition.edgeCount());
    ASSERT_EQ((std::size_t)2, decomposition.edgeCount(root));
    ASSERT_EQ((std::size_t)1, decomposition.edgeCount(child));
    ASSERT_EQ((std::size_t)1, decomposition.edgeCount(newRoot));

    ASSERT_EQ((std::size_t)3, decomposition.vertices().size());
    ASSERT_EQ((std::size_t)2, decomposition.hyperedges().size());

    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertices().size());

    ASSERT_TRUE(decomposition.isConnected());

    ASSERT_EQ((std::size_t)1, decomposition.leafNodeCount());

    ASSERT_TRUE(decomposition.isChild(newRoot, root));
    ASSERT_TRUE(decomposition.isChild(root, child));
    ASSERT_FALSE(decomposition.isChild(newRoot, child));
    ASSERT_TRUE(decomposition.isParent(child, root));
    ASSERT_TRUE(decomposition.isParent(root, newRoot));
    ASSERT_FALSE(decomposition.isParent(child, newRoot));

    ASSERT_EQ(child, decomposition.childAtPosition(root, (htd::index_t)0));
    ASSERT_EQ(root, decomposition.childAtPosition(newRoot, (htd::index_t)0));

    try
    {
        decomposition.childAtPosition(child, (htd::index_t)0);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ(newRoot, decomposition.parent(root));
    ASSERT_EQ(root, decomposition.parent(child));

    try
    {
        decomposition.parent(newRoot);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)1, decomposition.childCount(root));
    ASSERT_EQ((std::size_t)0, decomposition.childCount(child));
    ASSERT_EQ((std::size_t)1, decomposition.childCount(newRoot));

    ASSERT_EQ(root, decomposition.children(newRoot)[0]);
    ASSERT_EQ(child, decomposition.children(root)[0]);

    ASSERT_FALSE(decomposition.isLeafNode(root));
    ASSERT_TRUE(decomposition.isLeafNode(child));
    ASSERT_FALSE(decomposition.isLeafNode(newRoot));

    ASSERT_EQ((std::size_t)2, decomposition.vertexCount(root));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(child));
    ASSERT_EQ((std::size_t)3, decomposition.vertexCount(newRoot));

    ASSERT_EQ((std::size_t)2, decomposition.neighborCount(root));
    ASSERT_EQ((std::size_t)1, decomposition.neighborCount(child));
    ASSERT_EQ((std::size_t)1, decomposition.neighborCount(newRoot));

    ASSERT_EQ((std::size_t)0, decomposition.associatedEdgeIds(newRoot, root).size());
    ASSERT_EQ((std::size_t)1, decomposition.associatedEdgeIds(root, newRoot).size());
    ASSERT_EQ((htd::id_t)2, decomposition.associatedEdgeIds(root, newRoot)[0]);

    ASSERT_TRUE(decomposition.isEdge((htd::id_t)1));
    ASSERT_TRUE(decomposition.isEdge(root, newRoot));
    ASSERT_TRUE(decomposition.isEdge(std::vector<htd::vertex_t> { root, newRoot }));
    ASSERT_FALSE(decomposition.isEdge(std::vector<htd::vertex_t> { root, child, newRoot }));

    std::vector<htd::vertex_t> edgeElements1 { root, child };
    std::vector<htd::vertex_t> edgeElements2 { root, child, newRoot };

    ASSERT_TRUE(decomposition.isEdge(htd::ConstCollection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end())));
    ASSERT_FALSE(decomposition.isEdge(htd::ConstCollection<htd::vertex_t>(edgeElements2.begin(), edgeElements2.end())));

    ASSERT_EQ((std::size_t)1, decomposition.associatedEdgeIds(edgeElements1).size());
    ASSERT_EQ((std::size_t)0, decomposition.associatedEdgeIds(edgeElements2).size());
    ASSERT_EQ((htd::id_t)1, decomposition.associatedEdgeIds(edgeElements1)[0]);

    ASSERT_EQ((std::size_t)1, decomposition.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end())).size());
    ASSERT_EQ((std::size_t)0, decomposition.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(edgeElements2.begin(), edgeElements2.end())).size());
    ASSERT_EQ((htd::id_t)1, decomposition.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end()))[0]);

    ASSERT_EQ((std::size_t)1, decomposition.associatedEdgeIds(htd::Collection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end())).size());
    ASSERT_EQ((std::size_t)0, decomposition.associatedEdgeIds(htd::Collection<htd::vertex_t>(edgeElements2.begin(), edgeElements2.end())).size());
    ASSERT_EQ((htd::id_t)1, decomposition.associatedEdgeIds(htd::Collection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end()))[0]);

    ASSERT_FALSE(decomposition.isNeighbor(root, root));
    ASSERT_TRUE(decomposition.isNeighbor(root, child));
    ASSERT_TRUE(decomposition.isNeighbor(root, newRoot));
    ASSERT_TRUE(decomposition.isNeighbor(child, root));
    ASSERT_FALSE(decomposition.isNeighbor(child, child));
    ASSERT_FALSE(decomposition.isNeighbor(child, newRoot));;
    ASSERT_TRUE(decomposition.isNeighbor(newRoot, root));
    ASSERT_FALSE(decomposition.isNeighbor(newRoot, child));
    ASSERT_FALSE(decomposition.isNeighbor(newRoot, newRoot));

    ASSERT_TRUE(decomposition.isConnected());
    ASSERT_TRUE(decomposition.isConnected(root, root));
    ASSERT_TRUE(decomposition.isConnected(root, child));
    ASSERT_TRUE(decomposition.isConnected(root, newRoot));
    ASSERT_TRUE(decomposition.isConnected(child, root));
    ASSERT_TRUE(decomposition.isConnected(child, child));
    ASSERT_TRUE(decomposition.isConnected(child, newRoot));;
    ASSERT_TRUE(decomposition.isConnected(newRoot, root));
    ASSERT_TRUE(decomposition.isConnected(newRoot, child));
    ASSERT_TRUE(decomposition.isConnected(newRoot, newRoot));

    ASSERT_EQ(root, decomposition.vertexAtPosition((htd::index_t)0));
    ASSERT_EQ(child, decomposition.vertexAtPosition((htd::index_t)1));
    ASSERT_EQ(newRoot, decomposition.vertexAtPosition((htd::index_t)2));

    try
    {
        decomposition.vertexAtPosition((htd::index_t)3);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    const htd::ConstCollection<htd::vertex_t> & rootNeighbors = decomposition.neighbors(root);
    const htd::ConstCollection<htd::vertex_t> & childNeighbors = decomposition.neighbors(child);
    const htd::ConstCollection<htd::vertex_t> & newRootNeighbors = decomposition.neighbors(newRoot);

    try
    {
        decomposition.neighbors((htd::vertex_t)4);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    std::vector<htd::vertex_t> rootNeighbors2;
    std::vector<htd::vertex_t> childNeighbors2;
    std::vector<htd::vertex_t> newRootNeighbors2;

    try
    {
        decomposition.copyNeighborsTo(rootNeighbors2, (htd::vertex_t)4);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)2, rootNeighbors.size());
    ASSERT_EQ((std::size_t)1, childNeighbors.size());
    ASSERT_EQ((std::size_t)1, newRootNeighbors.size());

    ASSERT_EQ((std::size_t)0, rootNeighbors2.size());
    ASSERT_EQ((std::size_t)0, childNeighbors2.size());
    ASSERT_EQ((std::size_t)0, newRootNeighbors2.size());

    decomposition.copyNeighborsTo(rootNeighbors2, root);
    decomposition.copyNeighborsTo(childNeighbors2, child);
    decomposition.copyNeighborsTo(newRootNeighbors2, newRoot);

    ASSERT_EQ((std::size_t)2, rootNeighbors2.size());
    ASSERT_EQ((std::size_t)1, childNeighbors2.size());
    ASSERT_EQ((std::size_t)1, newRootNeighbors2.size());

    ASSERT_EQ(child, rootNeighbors[0]);
    ASSERT_EQ(newRoot, rootNeighbors[1]);
    ASSERT_EQ(root, childNeighbors[0]);
    ASSERT_EQ(root, newRootNeighbors[0]);

    ASSERT_EQ(child, rootNeighbors2[0]);
    ASSERT_EQ(newRoot, rootNeighbors2[1]);
    ASSERT_EQ(root, childNeighbors2[0]);
    ASSERT_EQ(root, newRootNeighbors2[0]);

    ASSERT_EQ(child, decomposition.neighborAtPosition(root, (htd::index_t)0));
    ASSERT_EQ(newRoot, decomposition.neighborAtPosition(root, (htd::index_t)1));
    ASSERT_EQ(root, decomposition.neighborAtPosition(child, (htd::index_t)0));
    ASSERT_EQ(root, decomposition.neighborAtPosition(newRoot, (htd::index_t)0));

    try
    {
        decomposition.neighborAtPosition((htd::vertex_t)4, (htd::index_t)0);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        decomposition.neighborAtPosition(root, (htd::index_t)2);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)2, decomposition.hyperedges(root).size());
    ASSERT_EQ((std::size_t)1, decomposition.hyperedges(child).size());
    ASSERT_EQ((std::size_t)1, decomposition.hyperedges(newRoot).size());

    try
    {
        decomposition.hyperedges((htd::vertex_t)4);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }
}

TEST(TreeDecompositionTest, CheckTreeManipulations)
{
    htd::TreeDecomposition decomposition;

    htd::vertex_t root = decomposition.insertRoot();

    htd::vertex_t node11 = decomposition.addChild(root);
    htd::vertex_t node12 = decomposition.addChild(root);
    htd::vertex_t node13 = decomposition.addChild(root);

    htd::vertex_t node111 = decomposition.addChild(node11);
    htd::vertex_t node121 = decomposition.addChild(node12);
    htd::vertex_t node122 = decomposition.addChild(node12);
    htd::vertex_t node131 = decomposition.addChild(node13);
    htd::vertex_t node132 = decomposition.addChild(node13);
    htd::vertex_t node133 = decomposition.addChild(node13);
    htd::vertex_t node134 = decomposition.addChild(node13);

    htd::vertex_t node1331 = decomposition.addChild(node133);

    ASSERT_EQ((std::size_t)12, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)11, decomposition.edgeCount());

    ASSERT_EQ((std::size_t)3, decomposition.childCount(root));
    ASSERT_EQ((std::size_t)1, decomposition.childCount(node11));
    ASSERT_EQ((std::size_t)2, decomposition.childCount(node12));
    ASSERT_EQ((std::size_t)4, decomposition.childCount(node13));

    ASSERT_EQ((std::size_t)0, decomposition.childCount(node111));
    ASSERT_EQ((std::size_t)0, decomposition.childCount(node121));
    ASSERT_EQ((std::size_t)0, decomposition.childCount(node122));
    ASSERT_EQ((std::size_t)0, decomposition.childCount(node131));
    ASSERT_EQ((std::size_t)0, decomposition.childCount(node132));
    ASSERT_EQ((std::size_t)1, decomposition.childCount(node133));
    ASSERT_EQ((std::size_t)0, decomposition.childCount(node134));

    ASSERT_EQ((std::size_t)0, decomposition.childCount(node1331));

    ASSERT_EQ((std::size_t)7, decomposition.leafNodeCount());

    ASSERT_EQ((std::size_t)12, decomposition.vertexCount(root));
    ASSERT_EQ((std::size_t)2, decomposition.vertexCount(node11));
    ASSERT_EQ((std::size_t)3, decomposition.vertexCount(node12));
    ASSERT_EQ((std::size_t)6, decomposition.vertexCount(node13));

    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node122));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node131));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node132));
    ASSERT_EQ((std::size_t)2, decomposition.vertexCount(node133));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node134));

    decomposition.setParent(node12, node111);

    ASSERT_EQ((std::size_t)12, decomposition.vertexCount(root));
    ASSERT_EQ((std::size_t)5, decomposition.vertexCount(node11));
    ASSERT_EQ((std::size_t)3, decomposition.vertexCount(node12));
    ASSERT_EQ((std::size_t)6, decomposition.vertexCount(node13));

    ASSERT_EQ((std::size_t)4, decomposition.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node122));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node131));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node132));
    ASSERT_EQ((std::size_t)2, decomposition.vertexCount(node133));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node134));

    decomposition.removeChild(node13, node132);

    ASSERT_FALSE(decomposition.isVertex(node132));

    ASSERT_EQ((std::size_t)11, decomposition.vertexCount(root));
    ASSERT_EQ((std::size_t)5, decomposition.vertexCount(node11));
    ASSERT_EQ((std::size_t)3, decomposition.vertexCount(node12));
    ASSERT_EQ((std::size_t)5, decomposition.vertexCount(node13));

    ASSERT_EQ((std::size_t)4, decomposition.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node122));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node131));
    ASSERT_EQ((std::size_t)2, decomposition.vertexCount(node133));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node134));

    decomposition.removeVertex(node12);

    ASSERT_EQ((std::size_t)10, decomposition.vertexCount(root));
    ASSERT_EQ((std::size_t)4, decomposition.vertexCount(node11));
    ASSERT_EQ((std::size_t)5, decomposition.vertexCount(node13));

    ASSERT_EQ((std::size_t)3, decomposition.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node122));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node131));
    ASSERT_EQ((std::size_t)2, decomposition.vertexCount(node133));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node134));

    decomposition.removeSubtree(node13);

    ASSERT_EQ((std::size_t)5, decomposition.vertexCount(root));
    ASSERT_EQ((std::size_t)4, decomposition.vertexCount(node11));

    ASSERT_EQ((std::size_t)3, decomposition.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node122));

    try
    {
        decomposition.removeSubtree(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    decomposition.removeRoot();

    ASSERT_EQ((std::size_t)0, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.edgeCount());
}

TEST(TreeDecompositionTest, CheckCopyConstructors)
{
    htd::Tree tree;

    htd::vertex_t root1 = tree.insertRoot();
    htd::vertex_t treeNode2 = tree.addChild(root1);
    htd::vertex_t treeNode3 = tree.addChild(root1);
    htd::vertex_t treeNode4 = tree.addChild(treeNode2);
    htd::vertex_t treeNode5 = tree.addChild(treeNode3);

    tree.removeVertex(treeNode4);

    htd::LabeledTree labeledTree;

    htd::vertex_t root2 = labeledTree.insertRoot();
    htd::vertex_t labeledTreeNode2 = labeledTree.addChild(root2);
    htd::vertex_t labeledTreeNode3 = labeledTree.addChild(root2);

    labeledTree.removeVertex(labeledTreeNode2);

    htd::TreeDecomposition treeDecomposition;

    htd::vertex_t root3 = treeDecomposition.insertRoot();
    htd::vertex_t treeDecompositionNode2 = treeDecomposition.addChild(root3);

    treeDecomposition.removeVertex(root3);

    treeDecomposition.setBagContent(treeDecompositionNode2, std::vector<htd::vertex_t> { 1, 2, 3 });

    const htd::ITreeDecomposition & treeDecompositionReference = treeDecomposition;

    htd::TreeDecomposition td1(tree);
    htd::TreeDecomposition td2(labeledTree);
    htd::TreeDecomposition td3(treeDecomposition);
    htd::TreeDecomposition td4(treeDecompositionReference);

    ASSERT_EQ((std::size_t)4, td1.vertexCount());
    ASSERT_TRUE(td1.isVertex(root1));
    ASSERT_TRUE(td1.isVertex(treeNode2));
    ASSERT_TRUE(td1.isVertex(treeNode3));
    ASSERT_FALSE(td1.isVertex(treeNode4));
    ASSERT_TRUE(td1.isVertex(treeNode5));

    ASSERT_EQ((std::size_t)2, td2.vertexCount());
    ASSERT_TRUE(td2.isVertex(root2));
    ASSERT_FALSE(td2.isVertex(labeledTreeNode2));
    ASSERT_TRUE(td2.isVertex(labeledTreeNode3));

    ASSERT_EQ((std::size_t)1, td3.vertexCount());
    ASSERT_FALSE(td3.isVertex(root3));
    ASSERT_TRUE(td3.isVertex(treeDecompositionNode2));

    ASSERT_EQ((std::size_t)1, td4.vertexCount());
    ASSERT_FALSE(td4.isVertex(root3));
    ASSERT_TRUE(td4.isVertex(treeDecompositionNode2));

    ASSERT_EQ((std::size_t)0, td1.bagSize(root1));
    ASSERT_EQ((std::size_t)0, td1.bagSize(treeNode2));
    ASSERT_EQ((std::size_t)0, td1.bagSize(treeNode3));

    try
    {
        td1.bagSize(treeNode4);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, td1.bagSize(treeNode5));

    ASSERT_EQ((std::size_t)0, td2.bagSize(root2));

    try
    {
        td2.bagSize(labeledTreeNode2);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, td2.bagSize(labeledTreeNode3));

    ASSERT_EQ((std::size_t)3, td3.bagSize(treeDecompositionNode2));

    ASSERT_EQ((htd::vertex_t)1, td3.bagContent(treeDecompositionNode2)[0]);
    ASSERT_EQ((htd::vertex_t)2, td3.bagContent(treeDecompositionNode2)[1]);
    ASSERT_EQ((htd::vertex_t)3, td3.bagContent(treeDecompositionNode2)[2]);

    ASSERT_EQ((std::size_t)3, td4.bagSize(treeDecompositionNode2));

    ASSERT_EQ((htd::vertex_t)1, td4.bagContent(treeDecompositionNode2)[0]);
    ASSERT_EQ((htd::vertex_t)2, td4.bagContent(treeDecompositionNode2)[1]);
    ASSERT_EQ((htd::vertex_t)3, td4.bagContent(treeDecompositionNode2)[2]);

    td1 = treeDecomposition;
    td2 = tree;
    td3 = labeledTree;

    ASSERT_EQ((std::size_t)4, td2.vertexCount());
    ASSERT_TRUE(td2.isVertex(root1));
    ASSERT_TRUE(td2.isVertex(treeNode2));
    ASSERT_TRUE(td2.isVertex(treeNode3));
    ASSERT_FALSE(td2.isVertex(treeNode4));
    ASSERT_TRUE(td2.isVertex(treeNode5));

    ASSERT_EQ((std::size_t)2, td3.vertexCount());
    ASSERT_TRUE(td3.isVertex(root2));
    ASSERT_FALSE(td3.isVertex(labeledTreeNode2));
    ASSERT_TRUE(td3.isVertex(labeledTreeNode3));

    ASSERT_EQ((std::size_t)1, td1.vertexCount());
    ASSERT_FALSE(td1.isVertex(root3));
    ASSERT_TRUE(td1.isVertex(treeDecompositionNode2));

    ASSERT_EQ((std::size_t)0, td2.bagSize(root1));
    ASSERT_EQ((std::size_t)0, td2.bagSize(treeNode2));
    ASSERT_EQ((std::size_t)0, td2.bagSize(treeNode3));

    try
    {
        td2.bagSize(treeNode4);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, td2.bagSize(treeNode5));

    ASSERT_EQ((std::size_t)0, td3.bagSize(root2));

    try
    {
        td3.bagSize(labeledTreeNode2);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, td3.bagSize(labeledTreeNode3));

    ASSERT_EQ((std::size_t)3, td1.bagSize(treeDecompositionNode2));

    ASSERT_EQ((htd::vertex_t)1, td1.bagContent(treeDecompositionNode2)[0]);
    ASSERT_EQ((htd::vertex_t)2, td1.bagContent(treeDecompositionNode2)[1]);
    ASSERT_EQ((htd::vertex_t)3, td1.bagContent(treeDecompositionNode2)[2]);

    ASSERT_EQ((std::size_t)1, td1.leafNodeCount());
    ASSERT_EQ((std::size_t)2, td2.leafNodeCount());
    ASSERT_EQ((std::size_t)1, td3.leafNodeCount());

    ASSERT_EQ(treeDecompositionNode2, td1.leafNodes()[0]);
    ASSERT_EQ(treeDecompositionNode2, td1.leafNodeAtPosition(0));

    ASSERT_EQ(treeNode2, td2.leafNodes()[0]);
    ASSERT_EQ(treeNode2, td2.leafNodeAtPosition(0));
    ASSERT_EQ(treeNode5, td2.leafNodes()[1]);
    ASSERT_EQ(treeNode5, td2.leafNodeAtPosition(1));

    ASSERT_EQ(labeledTreeNode3, td3.leafNodes()[0]);
    ASSERT_EQ(labeledTreeNode3, td3.leafNodeAtPosition(0));

    ASSERT_EQ((std::size_t)0, td1.joinNodeCount());
    ASSERT_EQ((std::size_t)1, td2.joinNodeCount());
    ASSERT_EQ((std::size_t)0, td3.joinNodeCount());

    ASSERT_EQ(root1, td2.joinNodes()[0]);
    ASSERT_EQ(root1, td2.joinNodeAtPosition(0));

    ASSERT_FALSE(td1.isJoinNode(treeDecompositionNode2));

    ASSERT_TRUE(td2.isJoinNode(root1));
    ASSERT_FALSE(td2.isJoinNode(treeNode2));
    ASSERT_FALSE(td2.isJoinNode(treeNode3));
    ASSERT_FALSE(td2.isJoinNode(treeNode5));

    ASSERT_FALSE(td3.isJoinNode(root2));
    ASSERT_FALSE(td3.isJoinNode(labeledTreeNode3));

    try
    {
        td1.isJoinNode(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, td1.forgetNodeCount());
    ASSERT_EQ((std::size_t)0, td2.forgetNodeCount());
    ASSERT_EQ((std::size_t)0, td3.forgetNodeCount());

    ASSERT_FALSE(td1.isForgetNode(treeDecompositionNode2));

    ASSERT_FALSE(td2.isForgetNode(root1));
    ASSERT_FALSE(td2.isForgetNode(treeNode2));
    ASSERT_FALSE(td2.isForgetNode(treeNode3));
    ASSERT_FALSE(td2.isForgetNode(treeNode5));

    ASSERT_FALSE(td3.isForgetNode(root2));
    ASSERT_FALSE(td3.isForgetNode(labeledTreeNode3));

    try
    {
        td1.isForgetNode(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)1, td1.introduceNodeCount());

    ASSERT_EQ((std::size_t)0, td2.introduceNodeCount());
    ASSERT_EQ((std::size_t)0, td3.introduceNodeCount());

    ASSERT_TRUE(td1.isIntroduceNode(treeDecompositionNode2));

    ASSERT_FALSE(td2.isIntroduceNode(root1));
    ASSERT_FALSE(td2.isIntroduceNode(treeNode2));
    ASSERT_FALSE(td2.isIntroduceNode(treeNode3));
    ASSERT_FALSE(td2.isIntroduceNode(treeNode5));

    ASSERT_FALSE(td3.isIntroduceNode(root2));
    ASSERT_FALSE(td3.isIntroduceNode(labeledTreeNode3));

    try
    {
        td1.isIntroduceNode(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    td2 = treeDecompositionReference;

    ASSERT_EQ((std::size_t)1, td2.vertexCount());

    ASSERT_EQ((std::size_t)3, td2.bagSize(treeDecompositionNode2));

    ASSERT_EQ((htd::vertex_t)1, td2.bagContent(treeDecompositionNode2)[0]);
    ASSERT_EQ((htd::vertex_t)2, td2.bagContent(treeDecompositionNode2)[1]);
    ASSERT_EQ((htd::vertex_t)3, td2.bagContent(treeDecompositionNode2)[2]);

    ASSERT_TRUE(td2.isIntroduceNode(treeDecompositionNode2));
    ASSERT_FALSE(td2.isForgetNode(treeDecompositionNode2));
    ASSERT_FALSE(td2.isJoinNode(treeDecompositionNode2));
    ASSERT_TRUE(td2.isLeafNode(treeDecompositionNode2));
}

TEST(TreeDecompositionTest, CheckBagContentModifications)
{
    htd::TreeDecomposition td1;

    htd::vertex_t root = td1.insertRoot();

    ASSERT_EQ((std::size_t)0, td1.bagSize(root));
    ASSERT_EQ((std::size_t)0, td1.bagContent(root).size());

    try
    {
        td1.bagSize(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td1.bagContent(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    std::vector<htd::vertex_t> bagContent { 3, 2, 1 };

    td1.setBagContent(root, bagContent);

    ASSERT_EQ((std::size_t)3, td1.bagSize(root));
    ASSERT_EQ((std::size_t)3, td1.bagContent(root).size());

    ASSERT_EQ((htd::vertex_t)1, td1.bagContent(root)[0]);
    ASSERT_EQ((htd::vertex_t)2, td1.bagContent(root)[1]);
    ASSERT_EQ((htd::vertex_t)3, td1.bagContent(root)[2]);

    td1.setBagContent(root, std::vector<htd::vertex_t> { 4, 5 });

    ASSERT_EQ((std::size_t)2, td1.bagSize(root));
    ASSERT_EQ((std::size_t)2, td1.bagContent(root).size());

    ASSERT_EQ((htd::vertex_t)4, td1.bagContent(root)[0]);
    ASSERT_EQ((htd::vertex_t)5, td1.bagContent(root)[1]);

    td1.setBagContent(root, htd::ConstCollection<htd::vertex_t>::getInstance(bagContent));

    ASSERT_EQ((std::size_t)3, td1.bagSize(root));
    ASSERT_EQ((std::size_t)3, td1.bagContent(root).size());

    ASSERT_EQ((htd::vertex_t)1, td1.bagContent(root)[0]);
    ASSERT_EQ((htd::vertex_t)2, td1.bagContent(root)[1]);
    ASSERT_EQ((htd::vertex_t)3, td1.bagContent(root)[2]);

    try
    {
        td1.setBagContent(htd::Vertex::UNKNOWN, bagContent);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td1.setBagContent(htd::Vertex::UNKNOWN, std::vector<htd::vertex_t> { });

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td1.setBagContent(htd::Vertex::UNKNOWN, htd::ConstCollection<htd::vertex_t>::getInstance(bagContent));

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)1, td1.vertexCount());
}

TEST(TreeDecompositionTest, CheckNodeTypeDetection)
{
    htd::TreeDecomposition td1;
    htd::TreeDecomposition td2;
    htd::TreeDecomposition td3;

    htd::vertex_t root1 = td1.insertRoot();
    htd::vertex_t root2 = td2.insertRoot();
    htd::vertex_t root3 = td3.insertRoot();

    htd::vertex_t node11 = td1.addChild(root1);
    htd::vertex_t node21 = td2.addChild(root2);
    htd::vertex_t node31 = td3.addChild(root3);
    htd::vertex_t node32 = td3.addChild(root3);

    td2.setBagContent(node21, std::vector<htd::vertex_t> { 1, 2 });

    td3.setBagContent(root3, std::vector<htd::vertex_t> { 1, 2 });
    td3.setBagContent(node31, std::vector<htd::vertex_t> { 1 });
    td3.setBagContent(node32, std::vector<htd::vertex_t> { 2 });

    ASSERT_EQ((std::size_t)1, td1.leafNodeCount());
    ASSERT_EQ((std::size_t)1, td2.leafNodeCount());
    ASSERT_EQ((std::size_t)2, td3.leafNodeCount());

    ASSERT_EQ((std::size_t)1, td1.leafNodes().size());
    ASSERT_EQ((std::size_t)1, td2.leafNodes().size());
    ASSERT_EQ((std::size_t)2, td3.leafNodes().size());

    ASSERT_EQ(node11, td1.leafNodes()[0]);
    ASSERT_EQ(node11, td1.leafNodeAtPosition(0));

    try
    {
        td1.leafNodeAtPosition(1);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ(node21, td2.leafNodes()[0]);
    ASSERT_EQ(node21, td2.leafNodeAtPosition(0));

    try
    {
        td2.leafNodeAtPosition(1);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ(node31, td3.leafNodes()[0]);
    ASSERT_EQ(node31, td3.leafNodeAtPosition(0));
    ASSERT_EQ(node32, td3.leafNodes()[1]);
    ASSERT_EQ(node32, td3.leafNodeAtPosition(1));

    try
    {
        td1.leafNodeAtPosition(2);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, td1.joinNodeCount());
    ASSERT_EQ((std::size_t)0, td2.joinNodeCount());
    ASSERT_EQ((std::size_t)1, td3.joinNodeCount());

    ASSERT_EQ((std::size_t)0, td1.joinNodes().size());
    ASSERT_EQ((std::size_t)0, td2.joinNodes().size());
    ASSERT_EQ((std::size_t)1, td3.joinNodes().size());

    try
    {
        td1.joinNodeAtPosition(0);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td2.joinNodeAtPosition(0);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ(root3, td3.joinNodes()[0]);
    ASSERT_EQ(root3, td3.joinNodeAtPosition(0));

    try
    {
        td3.joinNodeAtPosition(1);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, td1.forgetNodeCount());
    ASSERT_EQ((std::size_t)1, td2.forgetNodeCount());
    ASSERT_EQ((std::size_t)0, td3.forgetNodeCount());

    ASSERT_EQ((std::size_t)0, td1.forgetNodes().size());
    ASSERT_EQ((std::size_t)1, td2.forgetNodes().size());
    ASSERT_EQ((std::size_t)0, td3.forgetNodes().size());

    try
    {
        td1.forgetNodeAtPosition(0);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ(root2, td2.forgetNodes()[0]);
    ASSERT_EQ(root2, td2.forgetNodeAtPosition(0));

    try
    {
        td2.forgetNodeAtPosition(1);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td3.forgetNodeAtPosition(0);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, td1.introduceNodeCount());
    ASSERT_EQ((std::size_t)1, td2.introduceNodeCount());
    ASSERT_EQ((std::size_t)2, td3.introduceNodeCount());

    ASSERT_EQ((std::size_t)0, td1.introduceNodes().size());
    ASSERT_EQ((std::size_t)1, td2.introduceNodes().size());
    ASSERT_EQ((std::size_t)2, td3.introduceNodes().size());

    try
    {
        td1.forgetNodeAtPosition(0);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((htd::vertex_t)1, td2.introducedVertexAtPosition(node21, 0));
    ASSERT_EQ((htd::vertex_t)2, td2.introducedVertexAtPosition(node21, 1));

    try
    {
        td2.introducedVertexAtPosition(node21, 2);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((htd::vertex_t)2, td3.introducedVertexAtPosition(root3, 0, node31));
    ASSERT_EQ((htd::vertex_t)1, td3.introducedVertexAtPosition(root3, 0, node32));

    try
    {
        td2.introduceNodeAtPosition(1);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ(node31, td3.introduceNodes()[0]);
    ASSERT_EQ(node31, td3.introduceNodeAtPosition(0));
    ASSERT_EQ(node32, td3.introduceNodes()[1]);
    ASSERT_EQ(node32, td3.introduceNodeAtPosition(1));

    try
    {
        td3.introduceNodeAtPosition(2);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, td3.introducedVertexCount(root3));
    ASSERT_EQ((std::size_t)1, td3.introducedVertexCount(node31));
    ASSERT_EQ((std::size_t)1, td3.introducedVertexCount(node32));

    ASSERT_EQ((std::size_t)1, td3.introducedVertexCount(root3, node31));
    ASSERT_EQ((std::size_t)1, td3.introducedVertexCount(root3, node32));

    ASSERT_EQ((std::size_t)1, td3.introducedVertices(root3, node31).size());
    ASSERT_EQ((std::size_t)1, td3.introducedVertices(root3, node32).size());

    ASSERT_EQ((htd::vertex_t)2, td3.introducedVertices(root3, node31)[0]);
    ASSERT_EQ((htd::vertex_t)1, td3.introducedVertices(root3, node32)[0]);
    ASSERT_EQ((htd::vertex_t)2, td3.introducedVertexAtPosition(root3, 0, node31));
    ASSERT_EQ((htd::vertex_t)1, td3.introducedVertexAtPosition(root3, 0, node32));

    try
    {
        td3.introducedVertexCount(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td3.introducedVertexCount(htd::Vertex::UNKNOWN, root3);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td3.introducedVertexCount(root3, htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td3.introducedVertices(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td3.introducedVertices(htd::Vertex::UNKNOWN, 0);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td3.introducedVertexAtPosition(root3, 0);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td3.introducedVertexAtPosition(root3, 1, node31);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td3.introducedVertexAtPosition(root3, 1, node32);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, td1.rememberedVertexCount(root1));
    ASSERT_EQ((std::size_t)0, td1.rememberedVertexCount(root1, node11));
    ASSERT_EQ((std::size_t)0, td1.rememberedVertices(root1).size());
    ASSERT_EQ((std::size_t)0, td1.rememberedVertices(root1, node11).size());

    ASSERT_EQ((std::size_t)0, td2.rememberedVertexCount(root2));
    ASSERT_EQ((std::size_t)0, td2.rememberedVertexCount(root2, node21));
    ASSERT_EQ((std::size_t)0, td2.rememberedVertices(root2).size());
    ASSERT_EQ((std::size_t)0, td2.rememberedVertices(root2, node21).size());

    ASSERT_EQ((std::size_t)2, td3.rememberedVertexCount(root3));
    ASSERT_EQ((std::size_t)1, td3.rememberedVertexCount(root3, node31));
    ASSERT_EQ((std::size_t)1, td3.rememberedVertexCount(root3, node32));
    ASSERT_EQ((std::size_t)2, td3.rememberedVertices(root3).size());
    ASSERT_EQ((std::size_t)1, td3.rememberedVertices(root3, node31).size());
    ASSERT_EQ((std::size_t)1, td3.rememberedVertices(root3, node32).size());

    ASSERT_EQ((htd::vertex_t)1, td3.rememberedVertices(root3)[0]);
    ASSERT_EQ((htd::vertex_t)2, td3.rememberedVertices(root3)[1]);
    ASSERT_EQ((htd::vertex_t)1, td3.rememberedVertexAtPosition(root3, 0));
    ASSERT_EQ((htd::vertex_t)2, td3.rememberedVertexAtPosition(root3, 1));

    ASSERT_EQ((htd::vertex_t)1, td3.rememberedVertices(root3, node31)[0]);
    ASSERT_EQ((htd::vertex_t)2, td3.rememberedVertices(root3, node32)[0]);
    ASSERT_EQ((htd::vertex_t)1, td3.rememberedVertexAtPosition(root3, 0, node31));
    ASSERT_EQ((htd::vertex_t)2, td3.rememberedVertexAtPosition(root3, 0, node32));

    try
    {
        td3.rememberedVertexAtPosition(root3, 3);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td3.rememberedVertexAtPosition(root3, 1, node31);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td3.rememberedVertexAtPosition(root3, 1, node32);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }
}

TEST(TreeDecompositionTest, CheckIntroduceNodeDetection)
{
    htd::TreeDecomposition td;

    htd::vertex_t node1 = td.insertRoot();

    htd::vertex_t node11 = td.addChild(node1);
    htd::vertex_t node12 = td.addChild(node1);

    htd::vertex_t node121 = td.addChild(node12);

    td.setBagContent(node1, std::vector<htd::vertex_t> { 1, 2 });
    td.setBagContent(node11, std::vector<htd::vertex_t> { 1 });
    td.setBagContent(node12, std::vector<htd::vertex_t> { 2 });
    td.setBagContent(node121, std::vector<htd::vertex_t> { });

    ASSERT_EQ((std::size_t)2, td.introduceNodeCount());
    ASSERT_EQ(node11, td.introduceNodes()[0]);
    ASSERT_EQ(node11, td.introduceNodeAtPosition(0));
    ASSERT_EQ(node12, td.introduceNodes()[1]);
    ASSERT_EQ(node12, td.introduceNodeAtPosition(1));

    ASSERT_EQ((std::size_t)0, td.introducedVertexCount(node1));
    ASSERT_EQ((std::size_t)1, td.introducedVertexCount(node11));
    ASSERT_EQ((std::size_t)1, td.introducedVertexCount(node12));
    ASSERT_EQ((std::size_t)0, td.introducedVertexCount(node121));

    ASSERT_EQ((std::size_t)1, td.introducedVertexCount(node1, node11));
    ASSERT_EQ((std::size_t)1, td.introducedVertexCount(node1, node12));
    ASSERT_EQ((std::size_t)1, td.introducedVertexCount(node12, node121));

    try
    {
        td.introducedVertexCount(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.introducedVertexCount(node121, htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.introducedVertexCount(htd::Vertex::UNKNOWN, node121);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((htd::vertex_t)1, td.introducedVertices(node11)[0]);
    ASSERT_EQ((htd::vertex_t)1, td.introducedVertexAtPosition(node11, 0));
    ASSERT_EQ((htd::vertex_t)2, td.introducedVertices(node12)[0]);
    ASSERT_EQ((htd::vertex_t)2, td.introducedVertexAtPosition(node12, 0));

    ASSERT_EQ((htd::vertex_t)2, td.introducedVertices(node12, node121)[0]);
    ASSERT_EQ((htd::vertex_t)2, td.introducedVertexAtPosition(node12, 0, node121));

    try
    {
        td.introducedVertexAtPosition(node12, 2);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.introducedVertexAtPosition(node12, 2, node121);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.introducedVertexAtPosition(htd::Vertex::UNKNOWN, 0);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.introducedVertexAtPosition(htd::Vertex::UNKNOWN, 0, node12);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.introducedVertexAtPosition(node12, 0, htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_TRUE(td.isIntroducedVertex(node12, 2));
    ASSERT_TRUE(td.isIntroducedVertex(node12, 2, node121));

    ASSERT_FALSE(td.isRememberedVertex(node12, 2));
    ASSERT_FALSE(td.isRememberedVertex(node12, 2, node121));

    try
    {
        td.introducedVertices(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.introducedVertices(htd::Vertex::UNKNOWN, node121);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    std::vector<htd::vertex_t> introducedVertices;

    td.copyIntroducedVerticesTo(introducedVertices, node12);

    ASSERT_EQ((std::size_t)1, introducedVertices.size());
    ASSERT_EQ((htd::vertex_t)2, introducedVertices[0]);

    introducedVertices.clear();

    try
    {
        td.copyIntroducedVerticesTo(introducedVertices, htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, introducedVertices.size());

    td.copyIntroducedVerticesTo(introducedVertices, node12, node121);

    ASSERT_EQ((std::size_t)1, introducedVertices.size());
    ASSERT_EQ((htd::vertex_t)2, introducedVertices[0]);

    introducedVertices.clear();

    try
    {
        td.copyIntroducedVerticesTo(introducedVertices, htd::Vertex::UNKNOWN, node121);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, introducedVertices.size());

    try
    {
        td.copyIntroducedVerticesTo(introducedVertices, node12, htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, introducedVertices.size());
}

TEST(TreeDecompositionTest, CheckRememberedVertexDetection)
{
    htd::TreeDecomposition td;

    htd::vertex_t node1 = td.insertRoot();

    htd::vertex_t node11 = td.addChild(node1);
    htd::vertex_t node12 = td.addChild(node1);

    htd::vertex_t node121 = td.addChild(node12);

    td.setBagContent(node1, std::vector<htd::vertex_t> { 1, 2 });
    td.setBagContent(node11, std::vector<htd::vertex_t> { 1 });
    td.setBagContent(node12, std::vector<htd::vertex_t> { 2 });
    td.setBagContent(node121, std::vector<htd::vertex_t> { });

    ASSERT_EQ((std::size_t)2, td.rememberedVertexCount(node1));
    ASSERT_EQ((std::size_t)0, td.rememberedVertexCount(node11));
    ASSERT_EQ((std::size_t)0, td.rememberedVertexCount(node12));
    ASSERT_EQ((std::size_t)0, td.rememberedVertexCount(node121));

    ASSERT_EQ((std::size_t)1, td.rememberedVertexCount(node1, node11));
    ASSERT_EQ((std::size_t)1, td.rememberedVertexCount(node1, node12));
    ASSERT_EQ((std::size_t)0, td.rememberedVertexCount(node12, node121));

    try
    {
        td.rememberedVertexCount(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.rememberedVertexCount(node121, htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.rememberedVertexCount(htd::Vertex::UNKNOWN, node121);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((htd::vertex_t)1, td.rememberedVertices(node1)[0]);
    ASSERT_EQ((htd::vertex_t)1, td.rememberedVertexAtPosition(node1, 0));
    ASSERT_EQ((htd::vertex_t)2, td.rememberedVertices(node1)[1]);
    ASSERT_EQ((htd::vertex_t)2, td.rememberedVertexAtPosition(node1, 1));

    try
    {
        td.rememberedVertexAtPosition(node1, 2);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.rememberedVertexAtPosition(node1, 1, node11);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.rememberedVertexAtPosition(htd::Vertex::UNKNOWN, 0);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.rememberedVertexAtPosition(htd::Vertex::UNKNOWN, 0, node12);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.rememberedVertexAtPosition(node12, 0, htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_TRUE(td.isRememberedVertex(node1, 1));
    ASSERT_TRUE(td.isRememberedVertex(node1, 2));
    ASSERT_FALSE(td.isRememberedVertex(node1, 1, node12));

    try
    {
        td.rememberedVertices(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.rememberedVertices(htd::Vertex::UNKNOWN, node12);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    std::vector<htd::vertex_t> rememberedVertices;

    td.copyRememberedVerticesTo(rememberedVertices, node12);

    ASSERT_EQ((std::size_t)0, rememberedVertices.size());

    td.copyRememberedVerticesTo(rememberedVertices, node1);

    ASSERT_EQ((std::size_t)2, rememberedVertices.size());
    ASSERT_EQ((htd::vertex_t)1, rememberedVertices[0]);
    ASSERT_EQ((htd::vertex_t)2, rememberedVertices[1]);

    rememberedVertices.clear();

    try
    {
        td.copyRememberedVerticesTo(rememberedVertices, htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, rememberedVertices.size());

    td.copyRememberedVerticesTo(rememberedVertices, node1, node12);

    ASSERT_EQ((std::size_t)1, rememberedVertices.size());
    ASSERT_EQ((htd::vertex_t)2, rememberedVertices[0]);

    rememberedVertices.clear();

    try
    {
        td.copyRememberedVerticesTo(rememberedVertices, htd::Vertex::UNKNOWN, node121);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, rememberedVertices.size());

    try
    {
        td.copyRememberedVerticesTo(rememberedVertices, node12, htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, rememberedVertices.size());
}

TEST(TreeDecompositionTest, CheckForgetNodeDetection)
{
    htd::TreeDecomposition td;

    htd::vertex_t node1 = td.insertRoot();

    htd::vertex_t node11 = td.addChild(node1);
    htd::vertex_t node12 = td.addChild(node1);

    htd::vertex_t node121 = td.addChild(node12);

    htd::vertex_t root = td.addParent(node1);

    td.setBagContent(root, std::vector<htd::vertex_t> { 1 });
    td.setBagContent(node1, std::vector<htd::vertex_t> { 1, 2 });
    td.setBagContent(node11, std::vector<htd::vertex_t> { 1, 2 });
    td.setBagContent(node12, std::vector<htd::vertex_t> { 1, 2 });
    td.setBagContent(node121, std::vector<htd::vertex_t> { 1, 2, 3, 4 });

    ASSERT_EQ((std::size_t)2, td.forgetNodeCount());
    ASSERT_EQ(node12, td.forgetNodes()[0]);
    ASSERT_EQ(node12, td.forgetNodeAtPosition(0));
    ASSERT_EQ(root, td.forgetNodes()[1]);
    ASSERT_EQ(root, td.forgetNodeAtPosition(1));

    ASSERT_EQ((std::size_t)1, td.forgottenVertexCount(root));
    ASSERT_EQ((std::size_t)0, td.forgottenVertexCount(node1));
    ASSERT_EQ((std::size_t)0, td.forgottenVertexCount(node11));
    ASSERT_EQ((std::size_t)2, td.forgottenVertexCount(node12));
    ASSERT_EQ((std::size_t)0, td.forgottenVertexCount(node121));

    ASSERT_EQ((std::size_t)1, td.forgottenVertexCount(root, node1));
    ASSERT_EQ((std::size_t)0, td.forgottenVertexCount(node1, node11));
    ASSERT_EQ((std::size_t)0, td.forgottenVertexCount(node1, node12));
    ASSERT_EQ((std::size_t)2, td.forgottenVertexCount(node12, node121));

    try
    {
        td.forgottenVertexCount(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.forgottenVertexCount(node121, htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.forgottenVertexCount(htd::Vertex::UNKNOWN, node121);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((htd::vertex_t)3, td.forgottenVertices(node12)[0]);
    ASSERT_EQ((htd::vertex_t)3, td.forgottenVertexAtPosition(node12, 0));
    ASSERT_EQ((htd::vertex_t)4, td.forgottenVertices(node12)[1]);
    ASSERT_EQ((htd::vertex_t)4, td.forgottenVertexAtPosition(node12, 1));

    ASSERT_EQ((htd::vertex_t)3, td.forgottenVertices(node12, node121)[0]);
    ASSERT_EQ((htd::vertex_t)3, td.forgottenVertexAtPosition(node12, 0, node121));
    ASSERT_EQ((htd::vertex_t)4, td.forgottenVertices(node12, node121)[1]);
    ASSERT_EQ((htd::vertex_t)4, td.forgottenVertexAtPosition(node12, 1, node121));

    try
    {
        td.forgottenVertexAtPosition(node12, 2);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.forgottenVertexAtPosition(node12, 2, node121);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.forgottenVertexAtPosition(htd::Vertex::UNKNOWN, 0);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.forgottenVertexAtPosition(htd::Vertex::UNKNOWN, 0, node12);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.forgottenVertexAtPosition(node12, 0, htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_FALSE(td.isForgottenVertex(node12, 1));
    ASSERT_FALSE(td.isForgottenVertex(node12, 2));
    ASSERT_TRUE(td.isForgottenVertex(node12, 3));
    ASSERT_TRUE(td.isForgottenVertex(node12, 4));

    ASSERT_FALSE(td.isForgottenVertex(node12, 1, node121));
    ASSERT_FALSE(td.isForgottenVertex(node12, 2, node121));
    ASSERT_TRUE(td.isForgottenVertex(node12, 3, node121));
    ASSERT_TRUE(td.isForgottenVertex(node12, 4, node121));

    ASSERT_TRUE(td.isRememberedVertex(node12, 1));
    ASSERT_TRUE(td.isRememberedVertex(node12, 2));
    ASSERT_FALSE(td.isRememberedVertex(node12, 3));
    ASSERT_FALSE(td.isRememberedVertex(node12, 4));

    ASSERT_TRUE(td.isRememberedVertex(node12, 1, node121));
    ASSERT_TRUE(td.isRememberedVertex(node12, 2, node121));
    ASSERT_FALSE(td.isRememberedVertex(node12, 3, node121));
    ASSERT_FALSE(td.isRememberedVertex(node12, 4, node121));

    try
    {
        td.forgottenVertices(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.forgottenVertices(htd::Vertex::UNKNOWN, node121);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    std::vector<htd::vertex_t> forgottenVertices;

    td.copyForgottenVerticesTo(forgottenVertices, node12);

    ASSERT_EQ((std::size_t)2, forgottenVertices.size());
    ASSERT_EQ((htd::vertex_t)3, forgottenVertices[0]);
    ASSERT_EQ((htd::vertex_t)4, forgottenVertices[1]);

    forgottenVertices.clear();

    try
    {
        td.copyForgottenVerticesTo(forgottenVertices, htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, forgottenVertices.size());

    td.copyForgottenVerticesTo(forgottenVertices, node12, node121);

    ASSERT_EQ((std::size_t)2, forgottenVertices.size());
    ASSERT_EQ((htd::vertex_t)3, forgottenVertices[0]);
    ASSERT_EQ((htd::vertex_t)4, forgottenVertices[1]);

    forgottenVertices.clear();

    try
    {
        td.copyForgottenVerticesTo(forgottenVertices, htd::Vertex::UNKNOWN, node121);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, forgottenVertices.size());

    try
    {
        td.copyForgottenVerticesTo(forgottenVertices, node12, htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)0, forgottenVertices.size());
}

TEST(TreeDecompositionTest, CheckInducedHyperedges1)
{
    htd::TreeDecomposition td;

    htd::vertex_t node1 = td.insertRoot();

    ASSERT_EQ((std::size_t)0, td.inducedHyperedges(node1).size());

    try
    {
        td.inducedHyperedges(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    htd::Hyperedge h1(1, 1, 2);
    htd::Hyperedge h2(2, 2, 3);
    htd::Hyperedge h3(3, 3, 3);

    std::vector<htd::Hyperedge> inputEdges1 { h1, h2, h3 };

    htd::FilteredHyperedgeCollection hyperedges1(inputEdges1, std::vector<htd::index_t> { 0, 1, 2 });
    htd::FilteredHyperedgeCollection hyperedges2(inputEdges1, std::vector<htd::index_t> { 2, 1, 0 });
    htd::FilteredHyperedgeCollection hyperedges3(inputEdges1, std::vector<htd::index_t> { 0 });

    td.setInducedHyperedges(node1, hyperedges1);

    ASSERT_EQ((std::size_t)3, td.inducedHyperedges(node1).size());

    auto it = td.inducedHyperedges(node1).begin();

    ASSERT_EQ((htd::id_t)1, it->id());
    ++it;
    ASSERT_EQ((htd::id_t)2, it->id());
    ++it;
    ASSERT_EQ((htd::id_t)3, it->id());

    try
    {
        td.setInducedHyperedges(htd::Vertex::UNKNOWN, hyperedges1);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)3, td.inducedHyperedges(node1).size());

    try
    {
        td.setInducedHyperedges(htd::Vertex::UNKNOWN, std::move(hyperedges1));

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)3, td.inducedHyperedges(node1).size());

    it = td.inducedHyperedges(node1).begin();

    ASSERT_EQ((htd::id_t)1, it->id());
    ++it;
    ASSERT_EQ((htd::id_t)2, it->id());
    ++it;
    ASSERT_EQ((htd::id_t)3, it->id());

    td.setInducedHyperedges(node1, std::move(hyperedges2));

    try
    {
        td.inducedHyperedges(htd::Vertex::UNKNOWN);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ((std::size_t)3, td.inducedHyperedges(node1).size());

    it = td.inducedHyperedges(node1).begin();

    ASSERT_EQ((htd::id_t)3, it->id());
    ++it;
    ASSERT_EQ((htd::id_t)2, it->id());
    ++it;
    ASSERT_EQ((htd::id_t)1, it->id());
}

TEST(TreeDecompositionTest, TestVertexLabelModifications)
{
    htd::TreeDecomposition td;

    td.insertRoot();
    td.addChild(1);
    td.addChild(1);
    td.addChild(2);

    td.setVertexLabel("Label", 1, new htd::Label<int>(1));
    td.setVertexLabel("Label", 2, new htd::Label<int>(2));
    td.setVertexLabel("Label", 3, new htd::Label<int>(3));

    ASSERT_EQ((std::size_t)1, td.labelCount());
    ASSERT_EQ((std::size_t)1, td.labelNames().size());
    ASSERT_EQ("Label", td.labelNames()[0]);
    ASSERT_EQ("Label", td.labelNameAtPosition(0));

    try
    {
        td.labelNameAtPosition(1);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_FALSE(td.isLabeledVertex("Label", 0));
    ASSERT_TRUE(td.isLabeledVertex("Label", 1));
    ASSERT_TRUE(td.isLabeledVertex("Label", 2));
    ASSERT_TRUE(td.isLabeledVertex("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(3, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    htd::ILabel * newLabel = new htd::Label<int>(33);

    td.setVertexLabel("Label", 3, newLabel);

    ASSERT_FALSE(td.isLabeledVertex("Label", 0));
    ASSERT_TRUE(td.isLabeledVertex("Label", 1));
    ASSERT_TRUE(td.isLabeledVertex("Label", 2));
    ASSERT_TRUE(td.isLabeledVertex("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    td.setVertexLabel("Label", 3, newLabel);

    ASSERT_FALSE(td.isLabeledVertex("Label", 0));
    ASSERT_TRUE(td.isLabeledVertex("Label", 1));
    ASSERT_TRUE(td.isLabeledVertex("Label", 2));
    ASSERT_TRUE(td.isLabeledVertex("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    try
    {
        td.swapVertexLabels(0, 1);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.swapVertexLabels(1, 0);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    td.swapVertexLabels(1, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    td.swapVertexLabels(1, 3);

    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    td.swapVertexLabels(3, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    htd::ILabel * exportedLabel = td.transferVertexLabel("Label", 1);

    ASSERT_FALSE(td.isLabeledVertex("Label", 0));
    ASSERT_FALSE(td.isLabeledVertex("Label", 1));
    ASSERT_TRUE(td.isLabeledVertex("Label", 2));
    ASSERT_TRUE(td.isLabeledVertex("Label", 3));

    try
    {
        td.transferVertexLabel("Label", 0);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.transferVertexLabel("Label3", 1);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.vertexLabel("Label", 1);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    ASSERT_EQ(1, htd::accessLabel<int>(*exportedLabel));

    td.setVertexLabel("Label2", 2, new htd::Label<int>(1));
    td.setVertexLabel("Label2", 3, new htd::Label<int>(2));

    td.swapVertexLabel("Label", 2, 3);

    try
    {
        td.swapVertexLabel("UnknownLabel", 2, 3);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 3)));
    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label2", 2)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label2", 3)));

    td.removeVertexLabel("Label", 2);
    td.removeVertexLabel("Label", htd::Vertex::UNKNOWN);
    td.removeVertexLabel("Label3", 2);
    td.removeVertexLabel("Label3", htd::Vertex::UNKNOWN);

    try
    {
        td.vertexLabel("Label", 2);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label2", 2)));

    delete exportedLabel;
}

TEST(TreeDecompositionTest, TestEdgeLabelModifications)
{
    htd::TreeDecomposition td;

    td.insertRoot();
    td.addChild(1);
    td.addChild(1);
    td.addChild(2);

    td.setEdgeLabel("Label", 1, new htd::Label<int>(1));
    td.setEdgeLabel("Label", 2, new htd::Label<int>(2));
    td.setEdgeLabel("Label", 3, new htd::Label<int>(3));

    ASSERT_EQ((std::size_t)1, td.labelCount());
    ASSERT_EQ((std::size_t)1, td.labelNames().size());
    ASSERT_EQ("Label", td.labelNames()[0]);
    ASSERT_EQ("Label", td.labelNameAtPosition(0));

    try
    {
        td.labelNameAtPosition(1);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_FALSE(td.isLabeledEdge("Label", 0));
    ASSERT_TRUE(td.isLabeledEdge("Label", 1));
    ASSERT_TRUE(td.isLabeledEdge("Label", 2));
    ASSERT_TRUE(td.isLabeledEdge("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(3, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    htd::ILabel * newLabel = new htd::Label<int>(33);

    td.setEdgeLabel("Label", 3, newLabel);

    ASSERT_FALSE(td.isLabeledEdge("Label", 0));
    ASSERT_TRUE(td.isLabeledEdge("Label", 1));
    ASSERT_TRUE(td.isLabeledEdge("Label", 2));
    ASSERT_TRUE(td.isLabeledEdge("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    td.setEdgeLabel("Label", 3, newLabel);

    ASSERT_TRUE(td.isLabeledEdge("Label", 1));
    ASSERT_TRUE(td.isLabeledEdge("Label", 2));
    ASSERT_TRUE(td.isLabeledEdge("Label", 3));
    ASSERT_FALSE(td.isLabeledEdge("Label", 0));

    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    try
    {
        td.swapEdgeLabels(0, 1);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.swapEdgeLabels(1, 0);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    td.swapEdgeLabels(1, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    td.swapEdgeLabels(1, 3);

    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    td.swapEdgeLabels(3, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    htd::ILabel * exportedLabel = td.transferEdgeLabel("Label", 1);

    ASSERT_FALSE(td.isLabeledEdge("Label", 1));
    ASSERT_TRUE(td.isLabeledEdge("Label", 2));
    ASSERT_TRUE(td.isLabeledEdge("Label", 3));
    ASSERT_FALSE(td.isLabeledEdge("Label", 0));

    try
    {
        td.transferEdgeLabel("Label", 0);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.transferEdgeLabel("Label3", 1);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        td.edgeLabel("Label", 1);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    ASSERT_EQ(1, htd::accessLabel<int>(*exportedLabel));

    td.setEdgeLabel("Label2", 2, new htd::Label<int>(1));
    td.setEdgeLabel("Label2", 3, new htd::Label<int>(2));

    td.swapEdgeLabel("Label", 2, 3);

    try
    {
        td.swapEdgeLabel("UnknownLabel", 2, 3);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 3)));
    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label2", 2)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label2", 3)));

    td.removeEdgeLabel("Label", 2);
    td.removeEdgeLabel("Label", htd::Vertex::UNKNOWN);
    td.removeEdgeLabel("Label3", 2);
    td.removeEdgeLabel("Label3", htd::Vertex::UNKNOWN);

    try
    {
        td.edgeLabel("Label", 2);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label2", 2)));

    delete exportedLabel;
}

int main(int argc, char **argv)
{
    /* GoogleTest may throw. This results in a non-zero exit code and is intended. */
    // coverity[fun_call_w_exception]
    ::testing::InitGoogleTest(&argc, argv);

    /* GoogleTest may throw. This results in a non-zero exit code and is intended. */
    // coverity[fun_call_w_exception]
    return RUN_ALL_TESTS();
}
