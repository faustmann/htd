/* 
 * File:   Hyperedge.cpp
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

#ifndef HTD_HTD_HYPEREDGE_CPP
#define	HTD_HTD_HYPEREDGE_CPP

#include <htd/Hyperedge.hpp>

#include <tuple>

htd::Hyperedge::Hyperedge(htd::id_t id) : id_(id), elements_()
{

}

htd::Hyperedge::Hyperedge(htd::id_t id, htd::vertex_t vertex1, htd::vertex_t vertex2) : id_(id), elements_()
{
    elements_.push_back(vertex1);
    elements_.push_back(vertex2);
}

htd::Hyperedge::Hyperedge(htd::id_t id, const htd::ConstCollection<htd::vertex_t> & elements) : id_(id), elements_(elements.begin(), elements.end())
{

}

htd::Hyperedge::~Hyperedge()
{

}

htd::id_t htd::Hyperedge::id() const
{
    return id_;
}

htd::Collection<htd::vertex_t> htd::Hyperedge::elements()
{
    return htd::Collection<htd::vertex_t>::getInstance(elements_);
}

htd::ConstCollection<htd::vertex_t> htd::Hyperedge::elements() const
{
    return htd::ConstCollection<htd::vertex_t>::getInstance(elements_);
}

bool htd::Hyperedge::empty() const
{
    return elements_.empty();
}

bool htd::Hyperedge::containsVertex(htd::vertex_t vertex) const
{
    return std::find(elements_.begin(), elements_.end(), vertex) != elements_.end();
}

void htd::Hyperedge::push_back(htd::vertex_t vertex)
{
    elements_.push_back(vertex);
}

void htd::Hyperedge::erase(htd::vertex_t vertex)
{
    elements_.erase(std::remove(elements_.begin(), elements_.end(), vertex), elements_.end());
}

std::size_t htd::Hyperedge::size() const
{
    return elements_.size();
}

htd::Iterator<htd::vertex_t> htd::Hyperedge::begin(void)
{
    return htd::Iterator<htd::vertex_t>(elements_.begin());
}

const htd::ConstIterator<htd::vertex_t> htd::Hyperedge::begin(void) const
{
    return htd::ConstIterator<htd::vertex_t>(elements_.begin());
}

htd::Iterator<htd::vertex_t> htd::Hyperedge::end(void)
{
    return htd::Iterator<htd::vertex_t>(elements_.end());
}

const htd::ConstIterator<htd::vertex_t> htd::Hyperedge::end(void) const
{
    return htd::ConstIterator<htd::vertex_t>(elements_.end());
}

const htd::vertex_t & htd::Hyperedge::operator[](htd::index_t index) const
{
    htd::ConstIterator<htd::vertex_t> position = begin();

    std::advance(position, index);

    return *position;
}

htd::Hyperedge & htd::Hyperedge::operator=(const htd::Hyperedge & other)
{
    id_ = other.id_;

    elements_ = other.elements_;

    return *this;
}

bool htd::Hyperedge::operator<(const htd::Hyperedge & other) const
{
    return std::tie(elements_, id_) < std::tie(other.elements_, other.id_);
}

bool htd::Hyperedge::operator>(const htd::Hyperedge & other) const
{
    return std::tie(elements_, id_) > std::tie(other.elements_, other.id_);
}

bool htd::Hyperedge::operator==(const htd::Hyperedge & other) const
{
    return other.id_ == id_ && other.elements_ == elements_;
}

bool htd::Hyperedge::operator!=(const htd::Hyperedge & other) const
{
    return other.id_ != id_ || other.elements_ != elements_;
}

#endif /* HTD_HTD_HYPEREDGE_CPP */