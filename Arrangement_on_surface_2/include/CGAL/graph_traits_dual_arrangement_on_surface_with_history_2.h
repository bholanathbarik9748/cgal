// Copyright (c) 2018 Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
// You can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Author(s) : Ron Wein         <wein@post.tau.ac.il>
//             Ophir Setter     <ophirset@post.tau.ac.il>
//             Sebastien Loriot <sebastien.loriot@cgal.org>
//             Efi Fogel        <efifogel@gmail.com>

#ifndef CGAL_GRAPH_TRAITS_DUAL_ARRANGEMENT_ON_SURFACE_WITH_HISTORY_2_H
#define CGAL_GRAPH_TRAITS_DUAL_ARRANGEMENT_ON_SURFACE_WITH_HISTORY_2_H

#include <CGAL/license/Arrangement_on_surface_2.h>

/*! \file
 * Definition of:
 * 1. the specialized Dual<Arrangement_on_surface_with_history_2> class,
 * 2. the specialized
 *      boost::graph_traits<Dual<Arrangement_on_surface_with_history_2> >class,
 * 3. The free functions required by the various graph concepts.
 */

// include this to avoid a VC15 warning
#include <CGAL/boost/graph/Named_function_parameters.h>

#include <CGAL/Arrangement_on_surface_with_history_2.h>
#include <CGAL/Arrangement_2/graph_traits_dual.h>
#include <CGAL/disable_warnings.h>

namespace CGAL {

// The specialized Dual<Arrangement_on_surface_with_history_2... class template.
template <typename GeomTraits_2, typename TopolTraits>
class Dual<Arrangement_on_surface_with_history_2<GeomTraits_2, TopolTraits> > :
    public Dual_arrangement_on_surface<Arrangement_on_surface_with_history_2
                                       <GeomTraits_2, TopolTraits> >
{
public:
  typedef Arrangement_on_surface_with_history_2<GeomTraits_2, TopolTraits>                Arrangement;
  typedef typename Arrangement::Geometry_traits_2         Geometry_traits_2;
  typedef typename Arrangement::Topology_traits           Topology_traits;

private:
  typedef Dual_arrangement_on_surface<Arrangement>        Base;

public:
  /*! Default constructor. */
  Dual() : Base() {}

  /*! Constructor from an arrangement. */
  Dual(const Arrangement& arr) : Base(arr) {}
};

}

namespace boost {

// The specialized
// graph_traits<CGAL::Dual<CGAL::Arrangement_on_surface_with_history_2... class
// template.
template <typename GeomTraits_2, typename TopolTraits>
class graph_traits<CGAL::Dual<CGAL::Arrangement_on_surface_with_history_2
                              <GeomTraits_2, TopolTraits> > > :
    public CGAL::Graph_traits_dual_arr_on_surface_impl
             <CGAL::Arrangement_on_surface_with_history_2<GeomTraits_2,
                                                          TopolTraits> >
{};

}

namespace CGAL {

// Templates of free functions that handle
//   graph_traits<Dual<Arrangement_on_surface_with_history_2...
// class template.
CGAL_DUAL_ARRANGEMENT_2_OUT_DEGREE(Arrangement_on_surface_with_history_2)
CGAL_DUAL_ARRANGEMENT_2_OUT_EDGES(Arrangement_on_surface_with_history_2)
CGAL_DUAL_ARRANGEMENT_2_SOURCE(Arrangement_on_surface_with_history_2)
CGAL_DUAL_ARRANGEMENT_2_TARGET(Arrangement_on_surface_with_history_2)
CGAL_DUAL_ARRANGEMENT_2_IN_DEGREE(Arrangement_on_surface_with_history_2)
CGAL_DUAL_ARRANGEMENT_2_IN_EDGES(Arrangement_on_surface_with_history_2)
CGAL_DUAL_ARRANGEMENT_2_DEGREE(Arrangement_on_surface_with_history_2)
CGAL_DUAL_ARRANGEMENT_2_NUM_VERTICES(Arrangement_on_surface_with_history_2)
CGAL_DUAL_ARRANGEMENT_2_VERTICES(Arrangement_on_surface_with_history_2)
CGAL_DUAL_ARRANGEMENT_2_NUM_EDGES(Arrangement_on_surface_with_history_2)
CGAL_DUAL_ARRANGEMENT_2_EDGES(Arrangement_on_surface_with_history_2)

}

#endif
