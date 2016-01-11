/*
 * File:   InducedSubgraphLabelingOperation.cpp
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

#ifndef HTD_HTD_INDUCEDSUBGRAPHLABELINGOPERATION_CPP
#define	HTD_HTD_INDUCEDSUBGRAPHLABELINGOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/InducedSubgraphLabelingOperation.hpp>
#include <htd/PostOrderTreeTraversal.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <unordered_set>

htd::InducedSubgraphLabelingOperation::InducedSubgraphLabelingOperation(const htd::IHypergraph & graph) : graph_(graph)
{

}

htd::InducedSubgraphLabelingOperation::~InducedSubgraphLabelingOperation()
{

}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(labelingFunctions);

    std::vector<std::pair<htd::Hyperedge, htd::Hyperedge>> relevantHyperedges;

    for (const htd::Hyperedge & hyperedge : graph_.hyperedges())
    {
        htd::vertex_container elements(hyperedge.begin(), hyperedge.end());

        std::sort(elements.begin(), elements.end());

        elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

        relevantHyperedges.push_back(std::make_pair(htd::Hyperedge(hyperedge.id(), elements), hyperedge));
    }

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubtreeRoot)

        htd::VectorAdapter<htd::Hyperedge> label;

        std::vector<htd::Hyperedge> & labelContent = label.container();

        std::unordered_set<htd::vertex_t> childHyperedgeSelection;

        for (htd::vertex_t child : decomposition.children(vertex))
        {
            const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = decomposition.forgottenVertices(vertex);

            for (const htd::Hyperedge & hyperedge : dynamic_cast<const htd::Label<htd::ConstCollection<htd::Hyperedge>> *>(&(decomposition.vertexLabel(htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER, child)))->value())
            {
                if (childHyperedgeSelection.count(hyperedge.id()) == 0)
                {
                    bool ok = true;

                    for (auto it = forgottenVertexCollection.begin(); ok && it != forgottenVertexCollection.end(); ++it)
                    {
                        ok = std::find(hyperedge.begin(), hyperedge.end(), *it) == hyperedge.end();
                    }

                    if (ok)
                    {
                        childHyperedgeSelection.insert(hyperedge.id());

                        labelContent.push_back(hyperedge);
                    }
                }
            }

            const htd::ConstCollection<htd::vertex_t> & bag = decomposition.bagContent(vertex);

            for (const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge : relevantHyperedges)
            {
                if (childHyperedgeSelection.count(hyperedge.first.id()) == 0 && std::includes(bag.begin(), bag.end(), hyperedge.first.begin(), hyperedge.first.end()))
                {
                    labelContent.push_back(hyperedge.second);
                }
            }
        }

        if (!decomposition.isRoot(vertex))
        {
            std::unordered_set<htd::vertex_t> irrelevantHyperedges;

            const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = decomposition.forgottenVertices(decomposition.parent(vertex), vertex);

            for (const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge : relevantHyperedges)
            {
                if (htd::has_non_empty_set_intersection(hyperedge.first.begin(), hyperedge.first.end(), forgottenVertexCollection.begin(), forgottenVertexCollection.end()))
                {
                    irrelevantHyperedges.insert(hyperedge.first.id());
                }
            }

            relevantHyperedges.erase(std::remove_if(relevantHyperedges.begin(), relevantHyperedges.end(), [&](const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge)
            {
                return irrelevantHyperedges.count(hyperedge.first.id()) > 0;
            }), relevantHyperedges.end());
        }

        decomposition.setVertexLabel(htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::Hyperedge>>(htd::ConstCollection<htd::Hyperedge>::getInstance(label)));
    });
}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(labelingFunctions);

    std::vector<std::pair<htd::Hyperedge, htd::Hyperedge>> relevantHyperedges;

    for (const htd::Hyperedge & hyperedge : graph_.hyperedges())
    {
        htd::vertex_container elements(hyperedge.begin(), hyperedge.end());

        std::sort(elements.begin(), elements.end());

        elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

        relevantHyperedges.push_back(std::make_pair(htd::Hyperedge(hyperedge.id(), elements), hyperedge));
    }

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubtreeRoot)

        htd::VectorAdapter<htd::Hyperedge> label;

        std::vector<htd::Hyperedge> & labelContent = label.container();

        std::unordered_set<htd::vertex_t> childHyperedgeSelection;

        for (htd::vertex_t child : decomposition.children(vertex))
        {
            const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = decomposition.forgottenVertices(vertex);

            for (const htd::Hyperedge & hyperedge : dynamic_cast<const htd::Label<htd::ConstCollection<htd::Hyperedge>> *>(&(decomposition.vertexLabel(htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER, child)))->value())
            {
                if (childHyperedgeSelection.count(hyperedge.id()) == 0)
                {
                    bool ok = true;

                    for (auto it = forgottenVertexCollection.begin(); ok && it != forgottenVertexCollection.end(); ++it)
                    {
                        ok = std::find(hyperedge.begin(), hyperedge.end(), *it) == hyperedge.end();
                    }

                    if (ok)
                    {
                        childHyperedgeSelection.insert(hyperedge.id());

                        labelContent.push_back(hyperedge);
                    }
                }
            }

            const htd::ConstCollection<htd::vertex_t> & bag = decomposition.bagContent(vertex);

            for (const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge : relevantHyperedges)
            {
                if (childHyperedgeSelection.count(hyperedge.first.id()) == 0 && std::includes(bag.begin(), bag.end(), hyperedge.first.begin(), hyperedge.first.end()))
                {
                    labelContent.push_back(hyperedge.second);
                }
            }
        }

        if (!decomposition.isRoot(vertex))
        {
            std::unordered_set<htd::vertex_t> irrelevantHyperedges;

            const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = decomposition.forgottenVertices(decomposition.parent(vertex), vertex);

            for (const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge : relevantHyperedges)
            {
                if (htd::has_non_empty_set_intersection(hyperedge.first.begin(), hyperedge.first.end(), forgottenVertexCollection.begin(), forgottenVertexCollection.end()))
                {
                    irrelevantHyperedges.insert(hyperedge.first.id());
                }
            }

            relevantHyperedges.erase(std::remove_if(relevantHyperedges.begin(), relevantHyperedges.end(), [&](const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge)
            {
                return irrelevantHyperedges.count(hyperedge.first.id()) > 0;
            }), relevantHyperedges.end());
        }

        decomposition.setVertexLabel(htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::Hyperedge>>(htd::ConstCollection<htd::Hyperedge>::getInstance(label)));
    });
}

htd::InducedSubgraphLabelingOperation * htd::InducedSubgraphLabelingOperation::clone(void) const
{
    return new htd::InducedSubgraphLabelingOperation(graph_);
}

#endif /* HTD_HTD_INDUCEDSUBGRAPHLABELINGOPERATION_CPP */