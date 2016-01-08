/*
 * File:   LabeledPathFactory.hpp
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

#ifndef HTD_HTD_LABELEDPATHFACTORY_HPP
#define HTD_HTD_LABELEDPATHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledPath.hpp>

namespace htd
{
    class LabeledPathFactory
    {
    public:
        ~LabeledPathFactory();

        static LabeledPathFactory & instance(void);

        htd::IMutableLabeledPath * getLabeledPath(void);

        htd::IMutableLabeledPath * getLabeledPath(const htd::ILabeledPath & original);

        void setConstructionTemplate(htd::IMutableLabeledPath * original);

        htd::IMutableLabeledPath & accessMutableLabeledPath(htd::ILabeledPath & original);

        const htd::IMutableLabeledPath & accessMutableLabeledPath(const htd::ILabeledPath & original);

    private:
        htd::IMutableLabeledPath * constructionTemplate_;

        LabeledPathFactory(void);

        LabeledPathFactory(const LabeledPathFactory & original);

        LabeledPathFactory & operator=(const LabeledPathFactory & original);
    };
}

#endif /* HTD_HTD_LABELEDPATHFACTORY_HPP */