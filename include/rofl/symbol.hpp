#ifndef ROFL_SYMBOL_HPP_INCLUDED
#define ROFL_SYMBOL_HPP_INCLUDED

#ifdef rofl_EXPORTS
#include <fcppt/symbol/export.hpp>
#	define ROFL_SYMBOL FCPPT_SYMBOL_EXPORT
#else
#include <fcppt/symbol/import.hpp>
#	define ROFL_SYMBOL FCPPT_SYMBOL_IMPORT
#endif

#endif
