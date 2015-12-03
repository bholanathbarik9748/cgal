// Copyright (c) 2015  GeometryFactory (France).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// 
//
// Author(s)     : Andreas Fabri


#ifndef CGAL_PROPERTIES_SEAM_MESH_H
#define CGAL_PROPERTIES_SEAM_MESH_H

#include <CGAL/boost/graph/Seam_mesh.h>

#include <CGAL/boost/graph/properties.h>

namespace CGAL {

template <class TM>
class Seam_mesh;


template<class P>
class Seam_mesh_point_map
  : public boost::put_get_helper<typename boost::property_traits<typename boost::property_map<P,vertex_point_t>::const_type>::value_type, Seam_mesh_point_map<P> >
{
public:
  typedef boost::readable_property_map_tag category;
  typedef typename boost::property_traits<typename boost::property_map<P,vertex_point_t>::const_type>::value_type value_type;
  typedef value_type                    reference;
  typedef typename boost::graph_traits<Seam_mesh<P> >::vertex_descriptor key_type;

private:
  typedef typename boost::property_map<P,vertex_point_t>::const_type Map;

public:

  Seam_mesh_point_map(const Seam_mesh<P>& mesh, Map map)
    : mesh(mesh), map(map) 
  {}

  Seam_mesh_point_map(const Seam_mesh_point_map<P>& other)
    : mesh(other.mesh), map(other.map) 
  {}

  reference operator[](const key_type& vd) const
  {
    typename boost::graph_traits<P>::halfedge_descriptor hd = vd;
    return map[target(hd,mesh.mesh())]; 
  }

private:
  const Seam_mesh<P>& mesh;
  Map map;
};


  template<class P, class Map>
class Seam_mesh_uv_map {
public:
  typedef boost::read_write_property_map_tag category;
  typedef typename boost::property_traits<Map>::value_type value_type;
  typedef typename boost::property_traits<Map>::reference reference;
  typedef typename boost::graph_traits<Seam_mesh<P> >::vertex_descriptor key_type;
  // assert that key_type equals boost::property_traits<Map>::key_type

    typedef Seam_mesh<P> Mesh;
public:

  Seam_mesh_uv_map(const Seam_mesh<P>& mesh, Map map)
    : mesh(mesh), map(map) 
  {}

    Seam_mesh_uv_map(const Seam_mesh_uv_map<P,Map>& other)
    : mesh(other.mesh), map(other.map) 
  {}

    //reference operator[](const key_type& vd) const
    //{
    //  typename boost::graph_traits<P>::halfedge_descriptor hd = vd;
    //  return map[target(hd,mesh.mesh())]; 
    //}

  
    inline friend reference get(const Seam_mesh_uv_map<P,Map>& pm, key_type k)
  {
    return get(pm.map,k);
  }

  inline friend void put(const Seam_mesh_uv_map<P,Map>& pm, key_type k, const value_type& v)
  {
    std::cerr << "put" << std::endl;
    typedef typename boost::graph_traits<typename Seam_mesh_uv_map<P,Map>::Mesh>::halfedge_descriptor halfedge_descriptor;
    BOOST_FOREACH(halfedge_descriptor hd, halfedges_around_target(halfedge(k,pm.mesh),pm.mesh)){
      if(! hd.seam){
        std::cerr << "  forward put" << std::endl;
        put(pm.map,target(hd,pm.mesh),v);
      } else {
        std::cerr << " do not forward put as on seam" << std::endl;
      }
    }
  }


private:
  const Seam_mesh<P>& mesh;
  Map map;
  };


} // namespace CGAL


namespace boost {

template<typename P>
struct property_map<CGAL::Seam_mesh<P>, CGAL::vertex_point_t >
{
  typedef CGAL::Seam_mesh<P> SM; 

  typedef CGAL::Seam_mesh_point_map<P> type;
  
  typedef type const_type;
  
};

template<typename P>
typename property_map<CGAL::Seam_mesh<P>, CGAL::vertex_point_t >::const_type
get(CGAL::vertex_point_t, const CGAL::Seam_mesh<P>& sm) {
  return CGAL::Seam_mesh_point_map<P>(sm, get(CGAL::vertex_point_t(), const_cast<P&>(sm.mesh())));
}


} // namespace boost 

#endif // CGAL_PROPERTIES_SEAM_MESH_H
