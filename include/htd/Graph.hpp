/* 
 * File:   Graph.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2016, Michael Abseher
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

#ifndef HTD_HTD_GRAPH_HPP
#define	HTD_HTD_GRAPH_HPP

#include <htd/IMutableGraph.hpp>
#include <htd/IMutableHypergraph.hpp>

namespace htd
{
    /**
     *  Default implementation of the IMutableGraph interface.
     */
    class HTD_API Graph : public virtual htd::IMutableGraph
    {
        public:
            /**
             *  Constructor for a graph.
             *
             *  @param[in] manager   The management instance to which the new graph belongs.
             */
            Graph(const htd::LibraryInstance * const manager);

            /**
             *  Constructor for a graph.
             *
             *  @param[in] manager       The management instance to which the new graph belongs.
             *  @param[in] initialSize  The initial size of the created graph.
             */
            Graph(const htd::LibraryInstance * const manager, std::size_t initialSize);

            /**
             *  Copy constructor for a graph.
             *
             *  @param[in] original  The original graph.
             */
            Graph(const Graph & original);

            /**
             *  Copy constructor for a graph.
             *
             *  @param[in] original  The original graph.
             */
            Graph(const htd::IGraph & original);

            virtual ~Graph();
            
            std::size_t vertexCount(void) const HTD_OVERRIDE;

            std::size_t edgeCount(void) const HTD_OVERRIDE;

            std::size_t edgeCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isEdge(htd::id_t edgeId) const HTD_OVERRIDE;

            bool isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            bool isEdge(const std::vector<htd::vertex_t> & elements) const HTD_OVERRIDE;

            bool isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::ConstCollection<htd::id_t> associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            htd::ConstCollection<htd::id_t> associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::ConstCollection<htd::id_t> associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::vertex_t vertexAtPosition(htd::index_t index) const HTD_OVERRIDE;
            
            bool isConnected(void) const HTD_OVERRIDE;
            
            bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const HTD_OVERRIDE;
            
            std::size_t neighborCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const HTD_OVERRIDE;

            void copyNeighborsTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> vertices(void) const HTD_OVERRIDE;

            std::size_t isolatedVertexCount(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> isolatedVertices(void) const HTD_OVERRIDE;

            htd::vertex_t isolatedVertexAtPosition(htd::index_t index) const HTD_OVERRIDE;

            bool isIsolatedVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::Hyperedge> hyperedges(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::Hyperedge> hyperedges(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedge(htd::id_t edgeId) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::FilteredHyperedgeCollection hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const HTD_OVERRIDE;

            htd::FilteredHyperedgeCollection hyperedgesAtPositions(std::vector<htd::index_t> && indices) const HTD_OVERRIDE;

            htd::vertex_t nextVertex(void) const HTD_OVERRIDE;

            htd::id_t nextEdgeId(void) const HTD_OVERRIDE;

            htd::vertex_t addVertex(void) HTD_OVERRIDE;

            htd::vertex_t addVertices(std::size_t count) HTD_OVERRIDE;

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            htd::id_t addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            void removeEdge(htd::id_t edgeId) HTD_OVERRIDE;

            void removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            Graph * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current mutable graph.
             *
             *  @return A new Graph object identical to the current mutable graph.
             */
            Graph * clone(void) const;

            htd::IGraph * cloneGraph(void) const HTD_OVERRIDE;

            htd::IMultiGraph * cloneMultiGraph(void) const HTD_OVERRIDE;

            htd::IHypergraph * cloneHypergraph(void) const HTD_OVERRIDE;

            htd::IMultiHypergraph * cloneMultiHypergraph(void) const HTD_OVERRIDE;

            htd::IMutableGraph * cloneMutableGraph(void) const HTD_OVERRIDE;
#endif

            /**
             *  Copy assignment operator for a mutable graph.
             *
             *  @param[in] original  The original graph.
             */
            Graph & operator=(const Graph & original);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            Graph & operator=(const htd::IGraph & original) HTD_OVERRIDE;

            Graph & operator=(const htd::IMultiGraph & original) HTD_OVERRIDE;
#else
            Graph & operator=(const htd::IGraph & original);

            Graph & operator=(const htd::IMultiGraph & original);

            void assign(const htd::IGraph & original) HTD_OVERRIDE;

            void assign(const htd::IMultiGraph & original) HTD_OVERRIDE;
#endif

        private:
            htd::IMutableHypergraph * base_;
    };
}

#endif /* HTD_HTD_GRAPH_HPP */
