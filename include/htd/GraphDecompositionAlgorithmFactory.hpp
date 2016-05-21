/*
 * File:   GraphDecompositionAlgorithmFactory.hpp
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

#ifndef HTD_HTD_GRAPHDECOMPOSITIONALGORITHMFACTORY_HPP
#define HTD_HTD_GRAPHDECOMPOSITIONALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IGraphDecompositionAlgorithm.hpp>
#include <htd/IDecompositionManipulationOperation.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/IGraphDecompositionManipulationOperation.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IGraphDecompositionAlgorithm interface.
     */
    class GraphDecompositionAlgorithmFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~GraphDecompositionAlgorithmFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static GraphDecompositionAlgorithmFactory & instance(void);

            /**
             *  Create a new IGraphDecompositionAlgorithm object.
             *
             *  @return A new IGraphDecompositionAlgorithm object.
             */
            htd::IGraphDecompositionAlgorithm * getGraphDecompositionAlgorithm(void);

            /**
             *  Set the default implementation of the IGraphDecompositionAlgorithm interface.
             *
             *  @param[in] original The new default implementation of the IGraphDecompositionAlgorithm interface.
             */
            void setConstructionTemplate(htd::IGraphDecompositionAlgorithm * original);

            /**
             *  Set the manipulations which are applied globally to each decomposition generated by the algorithm. The manipulation operations are applied in the given order.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm factory. Deleting a manipulation operation provided to this method outside the decomposition
             *  algorithm factory or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

            /**
             *  Add a new manipulation operation which shall be applied globally to each decomposition generated by the algorithm. The manipulation operations are applied in the given order.
             *
             *  @note When calling this method the control over the memory region of the manipulation operation is transferred to the
             *  decomposition algorithm factory. Deleting the manipulation operation provided to this method outside the decomposition
             *  algorithm factory or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperation    The manipulation operation which shall be applied globally to each decomposition generated by the algorithm.
             */
            void addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation);

            /**
             *  Add additional manipulation operations which shall be applied globally to each decomposition generated by the algorithm. The manipulation operations are applied in the given order.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm factory. Deleting a manipulation operation provided to this method outside the decomposition
             *  algorithm factoryor assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            void addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IGraphDecompositionAlgorithm * constructionTemplate_;

            std::vector<htd::ILabelingFunction *> labelingFunctions_;

            std::vector<htd::IGraphDecompositionManipulationOperation *> postProcessingOperations_;

            GraphDecompositionAlgorithmFactory(void);

            GraphDecompositionAlgorithmFactory(const GraphDecompositionAlgorithmFactory & original);

            GraphDecompositionAlgorithmFactory & operator=(const GraphDecompositionAlgorithmFactory & original);
    };
}

#endif /* HTD_HTD_GRAPHDECOMPOSITIONALGORITHMFACTORY_HPP */
