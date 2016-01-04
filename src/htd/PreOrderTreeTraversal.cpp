/*
 * File:   PreOrderTreeTraversal.cpp
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

#ifndef HTD_HTD_PREORDERTREETRAVERSAL_CPP
#define	HTD_HTD_PREORDERTREETRAVERSAL_CPP

#include <htd/Globals.hpp>
#include <htd/PreOrderTreeTraversal.hpp>

#include <stack>
#include <stdexcept>

htd::PreOrderTreeTraversal::PreOrderTreeTraversal(void)
{

}

htd::PreOrderTreeTraversal::~PreOrderTreeTraversal()
{

}

void htd::PreOrderTreeTraversal::traverse(const htd::ITree & tree, std::function<void(htd::vertex_t)> targetFunction) const
{
    if (tree.vertexCount() > 0)
    {
        traverse(tree, targetFunction, tree.root());
    }
}

void htd::PreOrderTreeTraversal::traverse(const htd::ITree & tree, std::function<void(htd::vertex_t)> targetFunction, htd::vertex_t startingNode) const
{
    if (!tree.isVertex(startingNode))
    {
        throw std::logic_error("void htd::PreOrderTreeTraversal::traverse(const htd::ITree &, std::function<void(htd::vertex_t)>, htd::vertex_t) const");
    }

    htd::vertex_t currentNode = startingNode;

    htd::index_t currentIndex = 0;

    std::stack<std::pair<htd::vertex_t, htd::index_t>> parentStack;

    while (parentStack.size() > 0 || currentNode != htd::Vertex::UNKNOWN)
    {
        if (currentNode != htd::Vertex::UNKNOWN)
        {
            if (currentIndex == 0)
            {
                targetFunction(currentNode);
            }

            if (currentIndex < tree.childCount(currentNode))
            {
                parentStack.push(std::make_pair(currentNode, currentIndex + 1));

                currentNode = tree.child(currentNode, currentIndex);

                currentIndex = 0;
            }
            else
            {
                currentNode = htd::Vertex::UNKNOWN;
            }
        }
        else
        {
            currentNode = parentStack.top().first;

            currentIndex = parentStack.top().second;

            parentStack.pop();
        }
    }
}

#endif /* HTD_HTD_PREORDERTREETRAVERSAL_CPP */