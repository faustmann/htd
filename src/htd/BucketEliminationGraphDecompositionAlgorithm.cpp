/*
 * File:   BucketEliminationGraphDecompositionAlgorithm.cpp
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

#ifndef HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_CPP
#define	HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/BucketEliminationGraphDecompositionAlgorithm.hpp>
#include <htd/BidirectionalGraphNaming.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/OrderingAlgorithmFactory.hpp>
#include <htd/GraphDecompositionFactory.hpp>

#include <algorithm>
#include <array>
#include <cstdarg>
#include <functional>
#include <memory>
#include <stack>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

htd::BucketEliminationGraphDecompositionAlgorithm::BucketEliminationGraphDecompositionAlgorithm(void) : labelingFunctions_(), postProcessingOperations_()
{

}

htd::BucketEliminationGraphDecompositionAlgorithm::BucketEliminationGraphDecompositionAlgorithm(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) : labelingFunctions_(), postProcessingOperations_()
{
    setManipulationOperations(manipulationOperations);
}

htd::BucketEliminationGraphDecompositionAlgorithm::~BucketEliminationGraphDecompositionAlgorithm()
{
    for (auto & labelingFunction : labelingFunctions_)
    {
        delete labelingFunction;
    }

    for (auto & postProcessingOperation : postProcessingOperations_)
    {
        delete postProcessingOperation;
    }
}

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>());
}

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    htd::IMutableGraphDecomposition * ret = computeMutableDecomposition(graph);

    std::vector<htd::ILabelingFunction *> labelingFunctions;

    std::vector<htd::IGraphDecompositionManipulationOperation *> postProcessingOperations;

    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(operation);

        if (labelingFunction != nullptr)
        {
            labelingFunctions.push_back(labelingFunction);
        }

        htd::IGraphDecompositionManipulationOperation * manipulationOperation = dynamic_cast<htd::IGraphDecompositionManipulationOperation *>(operation);

        if (manipulationOperation != nullptr)
        {
            postProcessingOperations.push_back(manipulationOperation);
        }
    }

    if (ret != nullptr)
    {
        for (const auto & operation : postProcessingOperations_)
        {
            operation->apply(*ret);
        }

        for (const auto & operation : postProcessingOperations)
        {
            operation->apply(*ret);
        }

        for (const auto & labelingFunction : labelingFunctions_)
        {
            for (htd::vertex_t vertex : ret->vertices())
            {
                htd::ILabelCollection * labelCollection = ret->labelings().exportVertexLabelCollection(vertex);

                htd::ILabel * newLabel = labelingFunction->computeLabel(ret->bagContentVector(vertex), *labelCollection);

                delete labelCollection;

                ret->setVertexLabel(labelingFunction->name(), vertex, newLabel);
            }
        }

        for (const auto & labelingFunction : labelingFunctions)
        {
            for (htd::vertex_t vertex : ret->vertices())
            {
                htd::ILabelCollection * labelCollection = ret->labelings().exportVertexLabelCollection(vertex);

                htd::ILabel * newLabel = labelingFunction->computeLabel(ret->bagContentVector(vertex), *labelCollection);

                delete labelCollection;

                ret->setVertexLabel(labelingFunction->name(), vertex, newLabel);
            }
        }
    }

    return ret;
}

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const
{
    va_list arguments;

    va_start(arguments, manipulationOperationCount);

    std::vector<htd::IDecompositionManipulationOperation *> manipulationOperations;

    for (int manipulationOperationIndex = 0; manipulationOperationIndex < manipulationOperationCount; manipulationOperationIndex++)
    {
        manipulationOperations.push_back(va_arg(arguments, htd::IDecompositionManipulationOperation *));
    }

    return computeDecomposition(graph, manipulationOperations);
}

void htd::BucketEliminationGraphDecompositionAlgorithm::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    labelingFunctions_.clear();

    postProcessingOperations_.clear();

    addManipulationOperations(manipulationOperations);
}

void htd::BucketEliminationGraphDecompositionAlgorithm::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
{
    htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(manipulationOperation);

    if (labelingFunction != nullptr)
    {
        labelingFunctions_.push_back(labelingFunction);
    }

    htd::IGraphDecompositionManipulationOperation * newManipulationOperation = dynamic_cast<htd::IGraphDecompositionManipulationOperation *>(manipulationOperation);

    if (newManipulationOperation != nullptr)
    {
        postProcessingOperations_.push_back(newManipulationOperation);
    }
}

void htd::BucketEliminationGraphDecompositionAlgorithm::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(operation);

        if (labelingFunction != nullptr)
        {
            labelingFunctions_.push_back(labelingFunction);
        }

        htd::IGraphDecompositionManipulationOperation * manipulationOperation = dynamic_cast<htd::IGraphDecompositionManipulationOperation *>(operation);

        if (manipulationOperation != nullptr)
        {
            postProcessingOperations_.push_back(manipulationOperation);
        }
    }
}

htd::BucketEliminationGraphDecompositionAlgorithm * htd::BucketEliminationGraphDecompositionAlgorithm::clone(void) const
{
    std::vector<htd::IDecompositionManipulationOperation *> manipulationOperations;

    for (const auto & labelingFunction : labelingFunctions_)
    {
        manipulationOperations.push_back(labelingFunction->clone());
    }

    for (const auto & postProcessingOperation : postProcessingOperations_)
    {
        manipulationOperations.push_back(postProcessingOperation->clone());
    }

    return new htd::BucketEliminationGraphDecompositionAlgorithm(manipulationOperations);
}

htd::IMutableGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeMutableDecomposition(const htd::IMultiHypergraph & graph) const
{
    htd::IMutableGraphDecomposition * ret = htd::GraphDecompositionFactory::instance().getGraphDecomposition();

    std::size_t size = graph.vertexCount();

    if (size > 0)
    {
        htd::IOrderingAlgorithm * algorithm = htd::OrderingAlgorithmFactory::instance().getOrderingAlgorithm();

        if (algorithm == nullptr)
        {
            throw std::logic_error("htd::IMutableGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeMutableDecomposition(const htd::IHypergraph &) const");
        }

        std::vector<htd::vertex_t> ordering;

        algorithm->writeOrderingTo(graph, ordering);

        delete algorithm;

        std::unordered_map<htd::vertex_t, htd::index_t> indices(size);

        std::unordered_map<htd::vertex_t, htd::vertex_container> buckets(size);

        std::unordered_map<htd::vertex_t, htd::vertex_t> superset(size);

        std::unordered_map<htd::vertex_t, htd::vertex_container> neighbors(size);

        std::vector<htd::vertex_t> edgeTarget(graph.edgeCount());

        DEBUGGING_CODE(std::cout << "Ordering:" << std::endl;
        for (htd::vertex_t vertex : ordering)
        {
            std::cout << vertex << std::endl;
        })

        std::size_t index = 0;

        for (htd::vertex_t vertex : ordering)
        {
            indices[vertex] = index++;

            superset[vertex] = vertex;

            buckets[vertex].push_back(vertex);
        }

        std::size_t edgeCount = graph.edgeCount();

        htd::vertex_container elements;

        const htd::ConstCollection<htd::Hyperedge> & hyperedges = graph.hyperedges();

        auto it = hyperedges.begin();

        for (htd::index_t index = 0; index < edgeCount; ++index)
        {
            const htd::Hyperedge & edge = *it;

            /*
            std::cout << "EDGE " << index << ": ";
            htd::print(edge, std::cout);
            std::cout << std::endl;
            */

            switch (edge.size())
            {
                case 1:
                {
                    edgeTarget[index] = edge[0];

                    break;
                }
                case 2:
                {
                    htd::vertex_t vertex1 = edge[0];
                    htd::vertex_t vertex2 = edge[1];

                    if (vertex1 != vertex2)
                    {
                        if (indices.at(vertex1) < indices.at(vertex2))
                        {
                            auto & selectedBucket = buckets[vertex1];

                            auto position = std::lower_bound(selectedBucket.begin(), selectedBucket.end(), vertex2);

                            if (position == selectedBucket.end() || *position != vertex2)
                            {
                                selectedBucket.insert(position, vertex2);
                            }

                            edgeTarget[index] = vertex1;
                        }
                        else
                        {
                            auto & selectedBucket = buckets[vertex2];

                            auto position = std::lower_bound(selectedBucket.begin(), selectedBucket.end(), vertex1);

                            if (position == selectedBucket.end() || *position != vertex1)
                            {
                                selectedBucket.insert(position, vertex1);
                            }

                            edgeTarget[index] = vertex2;
                        }
                    }

                    break;
                }
                default:
                {
                    edge.copyTo(elements);

                    std::sort(elements.begin(), elements.end());

                    elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

                    htd::vertex_t minimumVertex = getMinimumVertex(elements, indices);

                    auto & selectedBucket = buckets[minimumVertex];

                    std::vector<htd::vertex_t> newBucketContent;
                    newBucketContent.reserve(selectedBucket.size());

                    std::set_union(selectedBucket.begin(), selectedBucket.end(), elements.begin(), elements.end(), std::back_inserter(newBucketContent));

                    std::swap(selectedBucket, newBucketContent);

                    edgeTarget[index] = minimumVertex;

                    elements.clear();

                    break;
                }
            }

            ++it;
        }

        DEBUGGING_CODE(std::cout << std::endl << "Buckets:" << std::endl;
        for (std::size_t index = 0; index < size; index++)
        {
            std::cout << "   Bucket " << index + htd::Vertex::FIRST << ": ";
            htd::print(buckets[index], false);
            std::cout << std::endl;
        }

        std::cout << std::endl << "Relevant Buckets:" << std::endl;
        for (htd::id_t bucket : relevantBuckets)
        {
            std::cout << "   Bucket " << bucket << ": ";
            htd::print(buckets[bucket], false);
            std::cout << std::endl;
        }

        std::cout << std::endl << "Connections:" << std::endl;
        )

        /*
        std::size_t maxSize = 0;
        std::cout << "Buckets:" << std::endl;
        for (htd::vertex_t vertex : graph.vertices())
        {
            std::cout << "   Bucket " << vertex << ": ";
            htd::print(buckets[vertex], std::cout, false);
            std::cout << std::endl;

            if (buckets[vertex].size() > maxSize)
            {
                maxSize = buckets[vertex].size();
            }
        }
        std::cout << std::endl << "MAX SIZE: " << maxSize << std::endl << std::endl;
        */

        for (htd::vertex_t selection : ordering)
        {
            DEBUGGING_CODE(std::cout << std::endl << "   Processing bucket " << selection << " ..." << std::endl;)

            const htd::vertex_container & bucket = buckets[selection];

            //std::cout << std::endl << std::endl << std::endl << "SELECTION: " << selection << std::endl << std::endl;

            if (bucket.size() > 1)
            {
                DEBUGGING_CODE(
                    std::cout << "      Bucket " << selection << ": ";
                    htd::print(bucket, false);
                    std::cout << std::endl;
                )

                htd::vertex_t minimumVertex = getMinimumVertex(bucket, indices, selection);

                DEBUGGING_CODE(
                    std::cout << "      Minimum Vertex: " << minimumVertex << std::endl;

                    if (minimumVertex < selection)
                    {
                        std::cout << "      Connection: " << minimumVertex << " - " << selection << std::endl;
                    }
                    else
                    {
                        std::cout << "      Connection: " << selection << " - " << minimumVertex << std::endl;
                    }
                )

                auto & selectedBucket = buckets[minimumVertex];

                std::vector<htd::vertex_t> newBucketContent;
                newBucketContent.reserve(selectedBucket.size() + bucket.size());

                htd::set_union(selectedBucket, bucket, selection, newBucketContent);

                std::swap(selectedBucket, newBucketContent);

                neighbors[selection].push_back(minimumVertex);
                neighbors[minimumVertex].push_back(selection);

                if (selectedBucket.size() + 1 > bucket.size())
                {
                    superset[minimumVertex] = minimumVertex;
                }
                else
                {
                    superset[minimumVertex] = superset[selection];
                }
            }
        }

        /*
        std::cout << "Buckets:" << std::endl;
        for (htd::vertex_t vertex : graph.vertices())
        {
            std::cout << "   Bucket " << vertex << ": ";
            htd::print(buckets[vertex], std::cout, false);
            std::cout << std::endl;
            std::cout << "      SUPERSET: " << superset[vertex] << std::endl;
            std::cout << "      NEIGHBORS: ";
            htd::print(neighbors[vertex], std::cout, false);
            std::cout << std::endl << std::endl;
        }
        std::cout << std::endl << std::endl << std::endl;

        index = 0;

        std::cout << "Hyperedges:" << std::endl;
        for (const htd::Hyperedge & hyperedge : graph.hyperedges())
        {
            htd::print(hyperedge, std::cout);
            std::cout << std::endl;
            std::cout << "   BAG: " << edgeTarget[index] << std::endl << std::endl;
            if (superset[edgeTarget[index]] != edgeTarget[index])
            {
                std::cout << "XXX" << std::endl;
            }

            ++index;
        }
        std::cout << std::endl << std::endl << std::endl;
        */

        htd::BidirectionalGraphNaming<htd::vertex_t, htd::id_t> graphNaming;

        std::function<htd::vertex_t(void)> vertexCreationFunction(std::bind(&htd::IMutableGraphDecomposition::addVertex, ret));

        for (htd::vertex_t vertex : ordering)
        {
            auto & currentNeighborhood = neighbors[vertex];

            if (superset[vertex] != vertex)
            {
                /*
                std::cout << "REMOVING " << vertex << " ..." << std::endl;
                std::cout << "   Bucket " << vertex << ": ";
                htd::print(buckets[vertex], std::cout, false);
                std::cout << std::endl;
                std::cout << "      SUPERSET: " << superset[vertex] << std::endl;
                std::cout << "      NEIGHBORS: ";
                htd::print(neighbors[vertex], std::cout, false);
                std::cout << std::endl << std::endl;
                */

                switch (currentNeighborhood.size())
                {
                    case 0:
                    {
                        break;
                    }
                    case 1:
                    {
                        auto & twoHopNeighborhood = neighbors[currentNeighborhood[0]];

                        twoHopNeighborhood.erase(std::find(twoHopNeighborhood.begin(), twoHopNeighborhood.end(), vertex));

                        break;
                    }
                    case 2:
                    {
                        htd::vertex_t neighbor1 = currentNeighborhood[0];
                        htd::vertex_t neighbor2 = currentNeighborhood[1];

                        auto & twoHopNeighborhood1 = neighbors[neighbor1];
                        auto & twoHopNeighborhood2 = neighbors[neighbor2];

                        *(std::find(twoHopNeighborhood1.begin(), twoHopNeighborhood1.end(), vertex)) = neighbor2;
                        *(std::find(twoHopNeighborhood2.begin(), twoHopNeighborhood2.end(), vertex)) = neighbor1;

                        if (superset[neighbor1] == neighbor1 && superset[neighbor2] == neighbor2)
                        {
                            ret->addEdge(graphNaming.insertVertex(neighbor1, vertexCreationFunction).first,
                                         graphNaming.insertVertex(neighbor2, vertexCreationFunction).first);
                        }

                        break;
                    }
                    default:
                    {
                        htd::vertex_t replacement = htd::Vertex::UNKNOWN;

                        for (auto it = currentNeighborhood.begin(); replacement == htd::Vertex::UNKNOWN && it != currentNeighborhood.end(); ++it)
                        {
                            if (std::includes(buckets[*it].begin(), buckets[*it].end(), buckets[vertex].begin(), buckets[vertex].end()))
                            {
                                replacement = *it;
                            }
                        }

                        //std::cout << "REPLACEMENT: " << replacement << std::endl;

                        auto & replacementNeighborhood = neighbors[replacement];

                        replacementNeighborhood.erase(std::find(replacementNeighborhood.begin(), replacementNeighborhood.end(), vertex));

                        std::copy_if(currentNeighborhood.begin(), currentNeighborhood.end(), std::back_inserter(replacementNeighborhood), [&](htd::vertex_t neighbor) { return neighbor != replacement; });

                        for (htd::vertex_t neighbor : currentNeighborhood)
                        {
                            if (neighbor != replacement)
                            {
                                auto & currentNeighborhood2 = neighbors[neighbor];

                                *(std::find(currentNeighborhood2.begin(), currentNeighborhood2.end(), vertex)) = replacement;

                                if (superset[replacement] == replacement && superset[neighbor] == neighbor)
                                {
                                    ret->addEdge(graphNaming.insertVertex(replacement, vertexCreationFunction).first,
                                                 graphNaming.insertVertex(neighbor, vertexCreationFunction).first);

                                    /*
                                    if (replacement < neighbor)
                                    {
                                        std::cout << "EDGE: " << replacement << " - " << neighbor << std::endl;
                                    }
                                    else
                                    {
                                        std::cout << "EDGE: " << neighbor << " - " << replacement << std::endl;
                                    }
                                    */
                                }
                            }
                        }

                        break;
                    }
                }

                neighbors.erase(vertex);
            }
            else
            {
                bool connected = false;

                for (htd::vertex_t neighbor : currentNeighborhood)
                {
                    if (superset[neighbor] == neighbor)
                    {
                        ret->addEdge(graphNaming.insertVertex(vertex, vertexCreationFunction).first,
                                     graphNaming.insertVertex(neighbor, vertexCreationFunction).first);

                        connected = true;
                    }
                }

                if (!connected)
                {
                    graphNaming.insertVertex(vertex, vertexCreationFunction);
                }
            }

            /*
            std::cout << "Buckets:" << std::endl;
            for (htd::vertex_t vertex : graph.vertices())
            {
                if (superset[vertex] == vertex)
                {
                    std::cout << "   Bucket " << vertex << ": ";
                    htd::print(buckets[vertex], std::cout, false);
                    std::cout << std::endl;
                    std::cout << "      SUPERSET: " << superset[vertex] << std::endl;
                    std::cout << "      NEIGHBORS: ";
                    htd::print(neighbors[vertex], std::cout, false);
                    std::cout << std::endl << std::endl;
                }
            }
            std::cout << std::endl << std::endl << std::endl;
            */
        }

        std::unordered_map<htd::vertex_t, std::vector<htd::index_t>> inducedEdges(ret->vertexCount());

        it = hyperedges.begin();

        for (index = 0; index < edgeCount; ++index)
        {
            it->copyTo(elements);

            std::sort(elements.begin(), elements.end());

            elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

            distributeEdge(index, elements, superset[edgeTarget[index]], buckets, neighbors, inducedEdges);

            elements.clear();

            ++it;
        }

        /*
        std::cout << std::endl << std::endl << std::endl << "Buckets:" << std::endl;
        for (htd::vertex_t vertex : graph.vertices())
        {
            if (superset[vertex] == vertex)
            {
                std::cout << "   Bucket " << vertex << ": ";
                htd::print(buckets[vertex], std::cout, false);
                std::cout << std::endl;
                std::cout << "      Induced Hyperedges:" << std::endl;
                for (htd::index_t edgeIndex : inducedEdges[vertex])
                {
                    htd::print(graph.hyperedges()[edgeIndex], std::cout);
                    std::cout << std::endl;
                }
                std::cout << std::endl;
                std::cout << "      INDUCED EDGES: " << inducedEdges[vertex].size() << std::endl;
            }
        }
        std::cout << std::endl << std::endl << std::endl;
        */

        for (htd::vertex_t vertex : ret->vertices())
        {
            /*
            std::cout << "SET BAG CONTENT " << vertex << " (" << result.lookupVertex(vertex) << "): ";
            htd::print(buckets[vertex], std::cout, false);
            std::cout << std::endl;
            */

            htd::vertex_t vertexName = graphNaming.vertexName(vertex);

            ret->setBagContent(vertex, std::move(buckets[vertexName]));

            ret->setInducedHyperedges(vertex, graph.hyperedgesAtPositions(inducedEdges[vertexName]));
        }
    }

    return ret;
}

htd::vertex_t htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::unordered_map<htd::vertex_t, htd::index_t> & vertexIndices) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    switch (vertices.size())
    {
        case 0:
        {
            throw std::out_of_range("htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const htd::Collection<htd::vertex_t> &, const std::unordered_map<htd::vertex_t, htd::index_t> &) const");
        }
        case 1:
        {
            ret = vertices[0];

            break;
        }
        case 2:
        {
            if (vertexIndices.at(vertices[0]) <= vertexIndices.at(vertices[1]))
            {
                ret = vertices[0];
            }
            else
            {
                ret = vertices[1];
            }

            break;
        }
        default:
        {
            std::size_t minimum = (std::size_t)-1;

            std::size_t currentIndex = (std::size_t)-1;

            for (htd::vertex_t vertex : vertices)
            {
                currentIndex = vertexIndices.at(vertex);

                if (currentIndex < minimum)
                {
                    ret = vertex;

                    minimum = currentIndex;
                }
            }

            break;
        }
    }

    return ret;
}

htd::vertex_t htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::unordered_map<htd::vertex_t, htd::index_t> & vertexIndices, htd::vertex_t excludedVertex) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    switch (vertices.size())
    {
        case 0:
        {
            throw std::out_of_range("htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const htd::Collection<htd::vertex_t> &, const std::unordered_map<htd::vertex_t, htd::index_t> &, htd::vertex_t) const");
        }
        case 1:
        {
            if (vertices[0] == excludedVertex)
            {
                throw std::out_of_range("htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const htd::Collection<htd::vertex_t> &, const std::unordered_map<htd::vertex_t, htd::index_t> &, htd::vertex_t) const");
            }

            ret = vertices[0];

            break;
        }
        case 2:
        {
            if (vertices[0] == excludedVertex)
            {
                ret = vertices[1];
            }
            else if (vertices[1] == excludedVertex)
            {
                ret = vertices[0];
            }
            else if (vertexIndices.at(vertices[0]) <= vertexIndices.at(vertices[1]))
            {
                ret = vertices[0];
            }
            else
            {
                ret = vertices[1];
            }

            break;
        }
        default:
        {
            std::size_t minimum = (std::size_t)-1;

            std::size_t currentIndex = (std::size_t)-1;

            for (htd::vertex_t vertex : vertices)
            {
                if (vertex != excludedVertex)
                {
                    currentIndex = vertexIndices.at(vertex);

                    if (currentIndex < minimum)
                    {
                        ret = vertex;

                        minimum = currentIndex;
                    }
                }
            }

            break;
        }
    }

    return ret;
}

void htd::BucketEliminationGraphDecompositionAlgorithm::distributeEdge(htd::index_t edgeIndex, const std::vector<htd::vertex_t> & edge, htd::vertex_t startBucket, const std::unordered_map<htd::vertex_t, htd::vertex_container> & buckets, const std::unordered_map<htd::vertex_t, htd::vertex_container> & neighbors, std::unordered_map<htd::vertex_t, std::vector<htd::index_t>> & inducedEdges) const
{
    std::stack<std::pair<htd::vertex_t, htd::vertex_t>> originStack;

    std::unordered_set<htd::vertex_t> visitedVertices;

    htd::vertex_t currentBucket = startBucket;

    originStack.push(std::make_pair(currentBucket, htd::Vertex::UNKNOWN));

    while (!originStack.empty())
    {
        currentBucket = originStack.top().first;

        if (visitedVertices.count(currentBucket) == 0)
        {
            htd::vertex_t predecessorBucket = originStack.top().second;

            if (predecessorBucket == htd::Vertex::UNKNOWN)
            {
                inducedEdges[currentBucket].push_back(edgeIndex);

                originStack.pop();

                for (htd::vertex_t neighbor : neighbors.at(currentBucket))
                {
                    if (visitedVertices.count(neighbor) == 0)
                    {
                        originStack.push(std::make_pair(neighbor, currentBucket));
                    }
                }
            }
            else
            {
                const htd::vertex_container & currentBucketContent = buckets.at(currentBucket);

                originStack.pop();

                if (std::includes(std::lower_bound(currentBucketContent.begin(), currentBucketContent.end(), edge[0]), currentBucketContent.end(), edge.begin(), edge.end()))
                {
                    inducedEdges[currentBucket].push_back(edgeIndex);

                    for (htd::vertex_t neighbor : neighbors.at(currentBucket))
                    {
                        if (visitedVertices.count(neighbor) == 0)
                        {
                            originStack.push(std::make_pair(neighbor, currentBucket));
                        }
                    }
                }
            }

            visitedVertices.insert(currentBucket);
        }
        else
        {
            originStack.pop();
        }
    }
}

#endif /* HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_CPP */
