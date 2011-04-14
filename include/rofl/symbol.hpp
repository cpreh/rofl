#ifndef ROFL_SYMBOL_HPP_INCLUDED
#define ROFL_SYMBOL_HPP_INCLUDED

#ifdef rofl_EXPORTS
#include <fcppt/export_symbol.hpp>
#	define ROFL_SYMBOL FCPPT_EXPORT_SYMBOL
#else
#include <fcppt/import_symbol.hpp>
#	define ROFL_SYMBOL FCPPT_IMPORT_SYMBOL
#endif

#endif
