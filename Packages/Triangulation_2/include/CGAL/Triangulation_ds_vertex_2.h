// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       :
// release_date  :
//
// file          : Triangulation/include/CGAL/Triangulation_ds_vertex_2.h
// source        : $RCSfile$
// revision      : $Revision$
// revision_date : $Date$
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec  < Mariette Yvinec@sophia.inria.fr>
//
// ============================================================================

#ifndef CGAL_TRIANGULATION_DS_VERTEX_2_H
#define CGAL_TRIANGULATION_DS_VERTEX_2_H

#include <utility>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_utils_2.h>
#include <CGAL/Triangulation_ds_circulators_2.h>

CGAL_BEGIN_NAMESPACE

template <class Vb, class Fb >
class  Triangulation_ds_vertex_2 
  : public Vb,
    public Triangulation_cw_ccw_2
{
public:
  typedef typename Vb::Point Point;
  typedef Triangulation_ds_vertex_2<Vb,Fb> Vertex;
  typedef Triangulation_ds_face_2<Vb,Fb> Face;
  typedef std::pair< Face*,int> Edge;
  typedef Triangulation_ds_face_circulator_2<Vertex,Face> Face_circulator;
  typedef Triangulation_ds_vertex_circulator_2<Vertex,Face> 
                                                           Vertex_circulator;
  typedef Triangulation_ds_edge_circulator_2<Vertex,Face> Edge_circulator;

  //CREATORS
  Triangulation_ds_vertex_2() : Vb() {}
  Triangulation_ds_vertex_2(const Point & p) :  Vb(p)  {}
  Triangulation_ds_vertex_2(const Point & p, Face * f) : Vb(p, f )  {}

  //SETTING
  void set_face(Face* f)  { Vb::set_face(f);  }

  //ACCESS
  Face* face() const {return ( (Face *) (Vb::face()) );}
  int degree() const ;
  Vertex_circulator incident_vertices() const;
  Vertex_circulator incident_vertices(const Face* f) const;
  Face_circulator incident_faces() const; 
  Face_circulator incident_faces(const Face* f) const; 
  Edge_circulator incident_edges() const;
  Edge_circulator incident_edges(const Face* f) const;
  bool is_valid(bool verbose = false, int level = 0) const;

};

template <class Vb, class Fb >
int
Triangulation_ds_vertex_2 <Vb,Fb> ::
degree() const
{
  int count = 0;
  Vertex_circulator vc = incident_vertices(), done(vc);
  if ( ! vc. is_empty()) {
    do { 
      count += 1;
    } while (++vc != done);
  }
  return count;
}

template <class Vb, class Fb >
inline
Triangulation_ds_vertex_circulator_2<Triangulation_ds_vertex_2<Vb,Fb>,
                                     Triangulation_ds_face_2<Vb,Fb> >
Triangulation_ds_vertex_2<Vb,Fb> ::
incident_vertices() const
{
  return Vertex_circulator(this);
}
    
template <class Vb, class Fb >
inline
Triangulation_ds_vertex_circulator_2<Triangulation_ds_vertex_2<Vb,Fb>,
                                     Triangulation_ds_face_2<Vb,Fb> >
Triangulation_ds_vertex_2<Vb,Fb> ::
incident_vertices(const Face* f) const
{
  return Vertex_circulator(this,f);
}

template <class Vb, class Fb >
inline
Triangulation_ds_face_circulator_2<Triangulation_ds_vertex_2<Vb,Fb>,
                                   Triangulation_ds_face_2<Vb,Fb> >
Triangulation_ds_vertex_2<Vb,Fb> ::
incident_faces() const
{
  return Face_circulator(this);
}
    
template <class Vb, class Fb >
inline
Triangulation_ds_face_circulator_2<Triangulation_ds_vertex_2<Vb,Fb>,
                                   Triangulation_ds_face_2<Vb,Fb> >
Triangulation_ds_vertex_2<Vb,Fb> ::
incident_faces(const Face* f) const
{
  return Face_circulator(this, f);
}
    
template <class Vb, class Fb >
inline
Triangulation_ds_edge_circulator_2<Triangulation_ds_vertex_2<Vb,Fb>,
                                   Triangulation_ds_face_2<Vb,Fb> >
Triangulation_ds_vertex_2<Vb,Fb> ::  
incident_edges() const
{
  return Edge_circulator(this);
}
       
template <class Vb, class Fb >
inline
Triangulation_ds_edge_circulator_2<Triangulation_ds_vertex_2<Vb,Fb>,
                                   Triangulation_ds_face_2<Vb,Fb> >
Triangulation_ds_vertex_2<Vb,Fb> ::  
incident_edges(const Face* f) const
{
  return Edge_circulator(this, f);
}
    
template <class Vb, class Fb >
bool 
Triangulation_ds_vertex_2<Vb,Fb> ::  
is_valid(bool verbose = false, int level = 0) const
{
  bool result = Vb::is_valid(verbose, level);
  CGAL_triangulation_assertion(result);
  if (face() != NULL) { // face==NULL if dim <0
    result = result && face()->has_vertex(this);
  }
  return result;
}

CGAL_END_NAMESPACE

#endif //CGAL_TRIANGULATION_DS_VERTEX_2_H
