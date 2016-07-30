/*
 * File:   TreeDecompositionAlgorithmFactory.cpp
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

#ifndef HTD_HTD_TREEDECOMPOSITIONALGORITHMFACTORY_CPP
#define HTD_HTD_TREEDECOMPOSITIONALGORITHMFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TreeDecompositionAlgorithmFactory.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>
#include <htd/BucketEliminationTreeDecompositionAlgorithm.hpp>

#include <memory>
#include <stdexcept>

htd::TreeDecompositionAlgorithmFactory::TreeDecompositionAlgorithmFactory(const htd::LibraryInstance * const manager) : constructionTemplate_(new htd::BucketEliminationTreeDecompositionAlgorithm(manager)), labelingFunctions_(), postProcessingOperations_()
{

}

htd::TreeDecompositionAlgorithmFactory::TreeDecompositionAlgorithmFactory(const htd::TreeDecompositionAlgorithmFactory & original)
{
    constructionTemplate_ = original.constructionTemplate_->clone();

    for (htd::ILabelingFunction * labelingFunction : original.labelingFunctions_)
    {
    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        labelingFunctions_.emplace_back(labelingFunction->clone());
    #else
        labelingFunctions_.emplace_back(labelingFunction->cloneLabelingFunction());
    #endif
    }

    for (htd::ITreeDecompositionManipulationOperation * postProcessingOperation : original.postProcessingOperations_)
    {
    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        postProcessingOperations_.emplace_back(postProcessingOperation->clone());
    #else
        postProcessingOperations_.emplace_back(postProcessingOperation->cloneTreeDecompositionManipulationOperation());
    #endif
    }
}

htd::TreeDecompositionAlgorithmFactory & htd::TreeDecompositionAlgorithmFactory::operator=(const htd::TreeDecompositionAlgorithmFactory & original)
{
    if (this != &original)
    {
        delete constructionTemplate_;

        constructionTemplate_ = original.constructionTemplate_->clone();

        for (htd::ILabelingFunction * labelingFunction : labelingFunctions_)
        {
            delete labelingFunction;
        }

        labelingFunctions_.clear();

        for (htd::ITreeDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
        {
            delete postProcessingOperation;
        }

        postProcessingOperations_.clear();

        for (htd::ILabelingFunction * labelingFunction : original.labelingFunctions_)
        {
        #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            labelingFunctions_.emplace_back(labelingFunction->clone());
        #else
            labelingFunctions_.emplace_back(labelingFunction->cloneLabelingFunction());
        #endif
        }

        for (htd::ITreeDecompositionManipulationOperation * postProcessingOperation : original.postProcessingOperations_)
        {
        #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            postProcessingOperations_.emplace_back(postProcessingOperation->clone());
        #else
            postProcessingOperations_.emplace_back(postProcessingOperation->cloneTreeDecompositionManipulationOperation());
        #endif
        }
    }

    return *this;
}

htd::TreeDecompositionAlgorithmFactory::~TreeDecompositionAlgorithmFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    for (htd::ILabelingFunction * labelingFunction : labelingFunctions_)
    {
        delete labelingFunction;
    }

    labelingFunctions_.clear();

    for (htd::ITreeDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
    {
        delete postProcessingOperation;
    }

    postProcessingOperations_.clear();
}

htd::ITreeDecompositionAlgorithm * htd::TreeDecompositionAlgorithmFactory::getTreeDecompositionAlgorithm(void) const
{
    htd::ITreeDecompositionAlgorithm * ret = constructionTemplate_->clone();

    for (htd::ILabelingFunction * labelingFunction : labelingFunctions_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        ret->addManipulationOperation(labelingFunction->clone());
#else
        ret->addManipulationOperation(labelingFunction->cloneLabelingFunction());
#endif
    }

    for (htd::ITreeDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        ret->addManipulationOperation(postProcessingOperation->clone());
#else
        ret->addManipulationOperation(postProcessingOperation->cloneTreeDecompositionManipulationOperation());
#endif
    }

    return ret;
}

htd::ITreeDecompositionAlgorithm * htd::TreeDecompositionAlgorithmFactory::getTreeDecompositionAlgorithm(const htd::LibraryInstance * const manager) const
{
    htd::ITreeDecompositionAlgorithm * ret = constructionTemplate_->clone();

    ret->setManagementInstance(manager);

    for (htd::ILabelingFunction * labelingFunction : labelingFunctions_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        htd::ILabelingFunction * clone = labelingFunction->clone();
#else
        htd::ILabelingFunction * clone = labelingFunction->cloneLabelingFunction();
#endif

        clone->setManagementInstance(manager);

        ret->addManipulationOperation(clone);
    }

    for (htd::ITreeDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        htd::ITreeDecompositionManipulationOperation * clone = postProcessingOperation->clone();
#else
        htd::ITreeDecompositionManipulationOperation * clone = postProcessingOperation->cloneTreeDecompositionManipulationOperation();
#endif

        clone->setManagementInstance(manager);

        ret->addManipulationOperation(clone);
    }

    return ret;
}

void htd::TreeDecompositionAlgorithmFactory::setConstructionTemplate(htd::ITreeDecompositionAlgorithm * original)
{
    HTD_ASSERT(original != nullptr)

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

void htd::TreeDecompositionAlgorithmFactory::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    labelingFunctions_.clear();

    postProcessingOperations_.clear();

    addManipulationOperations(manipulationOperations);
}

void htd::TreeDecompositionAlgorithmFactory::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
{
    htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(manipulationOperation);

    if (labelingFunction != nullptr)
    {
        labelingFunctions_.push_back(labelingFunction);
    }

    htd::ITreeDecompositionManipulationOperation * newManipulationOperation = dynamic_cast<htd::ITreeDecompositionManipulationOperation *>(manipulationOperation);

    if (newManipulationOperation != nullptr)
    {
        postProcessingOperations_.push_back(newManipulationOperation);
    }
}

void htd::TreeDecompositionAlgorithmFactory::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(operation);

        if (labelingFunction != nullptr)
        {
            labelingFunctions_.push_back(labelingFunction);
        }

        htd::ITreeDecompositionManipulationOperation * manipulationOperation = dynamic_cast<htd::ITreeDecompositionManipulationOperation *>(operation);

        if (manipulationOperation != nullptr)
        {
            postProcessingOperations_.push_back(manipulationOperation);
        }
    }
}

#endif /* HTD_HTD_TREEDECOMPOSITIONALGORITHMFACTORY_CPP */
