#include <rofl/dereference.hpp>
#include <rofl/aux/graph/mergeable.hpp>
#include <rofl/aux/graph/merge.hpp>
#include <rofl/graph/edge_descriptor.hpp>
#include <rofl/graph/edge_properties.hpp>
#include <rofl/graph/object.hpp>
#include <rofl/graph/out_edge_iterator.hpp>
#include <rofl/graph/simplify.hpp>
#include <rofl/graph/vertex_descriptor.hpp>
#include <rofl/graph/vertex_iterator.hpp>
#include <rofl/graph/vertex_properties.hpp>
#include <rofl/graph/vertices_begin.hpp>
#include <rofl/graph/vertices_end.hpp>
#include <rofl/math/barycenter.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/config/external_begin.hpp>
#include <exception>
#include <functional>
#include <set>
#include <queue>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{
// This is a giant hack and it goes as follows: We want to remove
// vertices from the graph and at the same time use a vector to
// store those vertices (because then astar will be faster).
// While iterating through the vertices, deletion is not advisable, so
// we store the vertices in a container. This could be a vector or a list.
// At the end of the algorithm, we delete all of the vertices in this
// container _but_ one deletion invalidates all other vertex_descriptors
// because we use a vector. To tackle this problem we use a set which is sorted
// with std::greater. This only works because we know vertex_descriptor is
// the index into the vector where the vertices are stored. And it works very well
// because the larger indices are deleted first.
using deletion_set = std::set<rofl::graph::vertex_descriptor, std::greater<>>;

using out_queue = std::queue<rofl::graph::edge_descriptor>;

void edit_out_edge(
    fcppt::reference<deletion_set> const deletes,
    fcppt::reference<out_queue> const out_edges,
    fcppt::reference<rofl::graph::object> const _graph,
    rofl::graph::vertex_descriptor u,
    rofl::graph::vertex_descriptor v,
    rofl::graph::edge_properties const &ep)
{
  if (deletes.get().find(v) != deletes.get().end())
  {
    return;
  }

  rofl::graph::vertex_properties &up = _graph.get()[u];
  rofl::graph::vertex_properties const &vp = _graph.get()[v];

  if (!rofl::aux::graph::mergeable(up.polygon(), vp.polygon(), ep.adjacent_edge()))
  {
    return;
  }

  up.polygon(rofl::aux::graph::merge(up.polygon(), vp.polygon(), ep.adjacent_edge()));

  up.barycenter(rofl::math::barycenter(rofl::dereference(up.polygon())));

  std::pair<rofl::graph::out_edge_iterator, rofl::graph::out_edge_iterator> q{
      boost::out_edges(v, _graph.get())};

  for (; q.first != q.second; ++q.first)
  {
    if (boost::source(*q.first, _graph.get()) != v)
    {
      std::terminate();
    }

    if (deletes.get().find(v) != deletes.get().end())
    {
      std::terminate();
    }

    rofl::graph::vertex_descriptor const w = boost::target(*q.first, _graph.get());

    if (u == w)
    {
      continue;
    }

    std::pair<rofl::graph::edge_descriptor, bool> const n = boost::add_edge(
        u,
        w,
        rofl::graph::edge_properties(
            fcppt::math::vector::length(vp.barycenter() - _graph.get()[w].barycenter()),
            _graph.get()[*q.first].adjacent_edge()),
        _graph.get());

    out_edges.get().push(n.first);

    /* very pedantic asserts
		FCPPT_ASSERT(
			std::find(
				g[u].polygon().begin(),
				g[u].polygon().end(),
				g[*q.first].adjacent_edge().start()) != g[u].polygon().end());

		FCPPT_ASSERT(
			std::find(
				g[u].polygon().begin(),
				g[u].polygon().end(),
				g[*q.first].adjacent_edge().end()) != g[u].polygon().end());*/
  }

  boost::clear_vertex(v, _graph.get());

  deletes.get().insert(v);
}

void edit_vertex(
    fcppt::reference<deletion_set> const deletes,
    fcppt::reference<rofl::graph::object> const _graph,
    rofl::graph::vertex_descriptor u)
{
  // Wurde diese Ecke schon gelöscht? Dann nicht bearbeiten (wir müssen lazy
  // löschen, weil sonst alles durcheinanderkommt (wir löschen Vertizes an
  // beliebigen Stellen))
  if (deletes.get().find(u) != deletes.get().end())
  {
    return;
  }

  out_queue out_edges{};

  for (std::pair<rofl::graph::out_edge_iterator, rofl::graph::out_edge_iterator> p =
           boost::out_edges(u, _graph.get());
       p.first != p.second;
       p.first++)
  {
    out_edges.push(*p.first);
  }

  while (!out_edges.empty())
  {
    rofl::graph::edge_descriptor const e = out_edges.front();

    out_edges.pop();

    edit_out_edge(
        deletes,
        fcppt::make_ref(out_edges),
        _graph,
        u,
        boost::target(e, _graph.get()),
        _graph.get()[e]);
  }
}

}

void rofl::graph::simplify(fcppt::reference<rofl::graph::object> const _graph)
{
#if 0
	for (std::pair<edge_iterator,edge_iterator> i = boost::edges(g); i.first != i.second; ++i.first)
	{
		bool const m =
			mergeable(
				g[boost::source(*i.first,g)].polygon(),
				g[boost::target(*i.first,g)].polygon(),
				g[*i.first].adjacent_edge()) ;

		sge::cerr
			<< "polygons "
			<< dereference(g[boost::source(*i.first,g)].polygon())
			<< " and "
			<< dereference(g[boost::target(*i.first,g)].polygon())
			<< " can be merged: "
			<< m
			<< "\n";

		if (!m)
			continue;

		sge::cerr
			<< "merging results in " <<
		dereference(merge(
			g[boost::source(*i.first,g)].polygon(),
			g[boost::target(*i.first,g)].polygon(),
			g[*i.first].adjacent_edge())) << "\n";
	}
#endif

  deletion_set deletes{};

  for (vertex_iterator it(rofl::graph::vertices_begin(_graph.get()));
       it != rofl::graph::vertices_end(_graph.get());
       ++it)
  {
    edit_vertex(fcppt::make_ref(deletes), _graph, *it);
  }

  for (auto const &to_remove : deletes)
  {
    boost::remove_vertex(to_remove, _graph.get());
  }

  /* PSEUDOCODE
	foreach (vertex v : g)
	{
		ecken = ecken(v,u) in edges;
		while (!ecken.empty())
		{
			(v,u,kante) = ecken.pop(); // u = neue Ecke

			if (!verschmelzbar(v,u,kante)) // guckt, ob kante unnötig ist
				continue;

			v.polygon() =
				verschmelze(
					u.polygon(),
					v.polygon(),
					kante);

			barycenter anpassen

			// Nachbarn übernehmen und später durchgehen
			foreach (w in ecken(u,w,anderekante)) // w = neue (transitive) Ecke
			{
				if (w == u) // keine Selbstverschmelzung
					continue;
				add_edge(
					v,w,anderekante);
				ecken.insert(
					(v,w,anderekante));
			}

			// alle Kanten, die u betreffen
			delete (u,*,*);
			// u selber
			delete u;
		}
	}
	*/
}
