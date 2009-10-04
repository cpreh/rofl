#include "mergeable.hpp"
#include "merge.hpp"
#include <rofl/graph/simplify.hpp>
#include <rofl/graph/edge_iterator.hpp>
#include <rofl/graph/vertex_descriptor.hpp>
#include <rofl/graph/out_edge_iterator.hpp>
#include <rofl/graph/vertex_iterator.hpp>
#include <rofl/graph/vertices_begin.hpp>
#include <rofl/graph/vertices_end.hpp>
#include <rofl/graph/edge_descriptor.hpp>
#include <rofl/math/barycenter.hpp>
#include <rofl/dereference.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/math/vector/length.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/assert.hpp>
#include <sge/cerr.hpp>
#include "../cyclic_iterator.hpp"
#include "../cyclic_iterator_impl.hpp"
#include <queue>
#include <vector>

namespace
{
typedef std::vector<rofl::graph::vertex_descriptor> deletion_vector;
typedef std::queue<rofl::graph::edge_descriptor> out_queue;

void edit_out_edge(
	deletion_vector &deletes,
	out_queue &out_edges,
	rofl::graph::object &g,
	rofl::graph::vertex_descriptor u,
	rofl::graph::vertex_descriptor v,
	rofl::graph::edge_properties const &ep)
{
	SGE_ASSERT(
		std::find(deletes.begin(),deletes.end(),v) == deletes.end());
	
	rofl::graph::vertex_properties 
		&up = 
			g[u],
		&vp = 
			g[v];
			
	if(
		!rofl::graph::mergeable(
			up.polygon(),
			vp.polygon(),
			ep.adjacent_edge()))
		return;
	
	up.polygon(
		rofl::graph::merge(
			up.polygon(),
			vp.polygon(),
			ep.adjacent_edge()));
	
	up.barycenter(
		rofl::math::barycenter(
			rofl::dereference(
				up.polygon())));
	
	std::pair
	<
		rofl::graph::out_edge_iterator,
		rofl::graph::out_edge_iterator
	> q = 
		boost::out_edges(
			v,
			g);
	
	for (; q.first != q.second; ++q.first)
	{
		SGE_ASSERT(
			boost::source(*q.first,g) == v);
			
		SGE_ASSERT(
			std::find(deletes.begin(),deletes.end(),v) == deletes.end());
			
		rofl::graph::vertex_descriptor w = 
			boost::target(
				*q.first,
				g);
		
		if (u == w)
			continue;
		
		std::pair<rofl::graph::edge_descriptor,bool> n = 
			boost::add_edge(
				u,
				w,
				rofl::graph::edge_properties(
					sge::math::vector::length(
						vp.barycenter()-g[w].barycenter()),
					g[*q.first].adjacent_edge()),
				g);
		
		out_edges.push(
			n.first);
		
		SGE_ASSERT(
			std::find(
				g[u].polygon().begin(),
				g[u].polygon().end(),
				g[*q.first].adjacent_edge().start()) != g[u].polygon().end());
				
		SGE_ASSERT(
			std::find(
				g[u].polygon().begin(),
				g[u].polygon().end(),
				g[*q.first].adjacent_edge().end()) != g[u].polygon().end());
	}
	
	boost::clear_vertex(
		v,
		g);
		
	deletes.push_back(
		v);
}

void edit_vertex(
	deletion_vector &deletes,
	rofl::graph::object &g,
	rofl::graph::vertex_descriptor u)
{
	// Wurde diese Ecke schon gelöscht? Dann nicht bearbeiten (wir müssen lazy
	// löschen, weil sonst alles durcheinanderkommt (wir löschen Vertizes an
	// beliebigen Stellen)
	if (std::find(deletes.begin(),deletes.end(),u) != deletes.end())
		return;
	
	out_queue out_edges;
	for(
		std::pair
		<
			rofl::graph::out_edge_iterator,
			rofl::graph::out_edge_iterator
		>
		p = 
		boost::out_edges(
			u,
			g);
		p.first != p.second; 
		p.first++)
		out_edges.push(
			*p.first);
	
	while (!out_edges.empty())
	{
		rofl::graph::edge_descriptor e = 
			out_edges.front();
		out_edges.pop();
		edit_out_edge(
			deletes,
			out_edges,
			g,
			u,
			boost::target(
				e,
				g),
			g[e]);
	}
}
}

void rofl::graph::simplify(
	object &g)
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

	deletion_vector deletes;
	for (vertex_iterator v = vertices_begin(g),next = v; v != vertices_end(g);v = next)
	{
		++next;
		edit_vertex(
			deletes,
			g,
			*v);
	}

	BOOST_FOREACH(deletion_vector::reference r,deletes)
		boost::remove_vertex(
			r,
			g);
	
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
