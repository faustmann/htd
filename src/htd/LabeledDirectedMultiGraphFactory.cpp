/*
 * File:   LabeledDirectedMultiGraphFactory.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015-2017, Michael Abseher
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

#ifndef HTD_HTD_LABELEDDIRECTEDMULTIGRAPHFACTORY_CPP
#define HTD_HTD_LABELEDDIRECTEDMULTIGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/LabeledDirectedMultiGraphFactory.hpp>
#include <htd/LabeledDirectedMultiGraph.hpp>

htd::LabeledDirectedMultiGraphFactory::LabeledDirectedMultiGraphFactory(const htd::LibraryInstance * const manager) : htd::GraphTypeFactory<htd::ILabeledDirectedMultiGraph, htd::IMutableLabeledDirectedMultiGraph>(new htd::LabeledDirectedMultiGraph(manager))
{

}

htd::LabeledDirectedMultiGraphFactory::~LabeledDirectedMultiGraphFactory()
{

}

htd::IMutableLabeledDirectedMultiGraph * htd::LabeledDirectedMultiGraphFactory::createInstance(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableLabeledDirectedMultiGraph();
#endif
}

htd::IMutableLabeledDirectedMultiGraph * htd::LabeledDirectedMultiGraphFactory::createInstance(std::size_t initialSize) const
{
    htd::IMutableLabeledDirectedMultiGraph * ret = createInstance();

    ret->addVertices(initialSize);

    return ret;
}

#endif /* HTD_HTD_LABELEDDIRECTEDMULTIGRAPHFACTORY_CPP */
