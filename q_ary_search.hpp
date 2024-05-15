
#ifndef ML__ALGORITHM__Q_ARY_SEARCH_HPP
#define ML__ALGORITHM__Q_ARY_SEARCH_HPP

#include <functional>
#include <cassert>

namespace ml {
namespace algorithm {


/// How length of array (subarray) is represented.
typedef unsigned int length_t;


/// Parameters used by '_2_ary_search' functions.
struct _2_ary_search_parameters_t {
	// Minimal length of the search range, below which we switch 
	// to linear search.
	length_t _to_linear_threshold = 2*2;
} _2_ary_search_parameters;


/// Q-ary search with partitioning into 2 fragments, on each step.
/// At the end, linear search is being performed.
/// Generally, this is almost the same as the binary search, 
/// with the difference that at the end linear search is performed.
/// Returns the first position 'it' in the range [begin, end), 
/// on which 'pred(*it, q)' is not satisfied.
template< typename RanIt, typename ValueT, typename PredT >
inline RanIt _2_ary_search( 
		RanIt begin, RanIt end, 
		const ValueT& q, 
		PredT pred )
{
	// Q-ary search
	RanIt begin_1;
	length_t fragment_length;
	// Work with {begin, length}, not with [begin, end)
	length_t length = (length_t)(end - begin);
	while ( length >= _2_ary_search_parameters._to_linear_threshold ) {
		fragment_length = length / 2;
		begin_1 = begin + fragment_length;
		if ( pred( *begin_1, q ) ) {
			begin = begin_1;
			length -= fragment_length;  // The last fragment
			continue;
		}
		length = fragment_length;  // Dive into 1/2-nd
	}
	// Linear search
	end = begin + length;
	while ( begin != end && pred( *begin, q ) )
		++begin;
	return begin;
}

template< typename RanIt, typename ValueT >
inline RanIt _2_ary_lower_bound(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ return _2_ary_search( begin, end, q, std::less< ValueT >() ); }

template< typename RanIt, typename ValueT >
inline RanIt _2_ary_upper_bound(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ return _2_ary_search( begin, end, q, std::less_equal< ValueT >() ); }

template< typename RanIt, typename ValueT >
inline bool _2_ary_search(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ RanIt result = _2_ary_search( begin, end, q, std::less< ValueT >() );
	  return result != end && ! (q < *result); }


/// Parameters used by '_3_ary_search' functions.
struct _3_ary_search_parameters_t {
	// Minimal length of the search range, below which we switch 
	// to linear search.
	length_t _to_linear_threshold = 3*2;
} _3_ary_search_parameters;

/// Q-ary search with partitioning into 3 fragments, on each step.
/// At the end, linear search is being performed.
/// Returns the first position 'it' in the range [begin, end), 
/// on which 'pred(*it, q)' is not satisfied.
template< typename RanIt, typename ValueT, typename PredT >
inline RanIt _3_ary_search(
		RanIt begin, RanIt end,
		const ValueT& q, 
		PredT pred )
{
	// Q-ary search
	RanIt begin_1, begin_2;
	length_t fragment_length;
	// Work with {begin, length}, not with [begin, end)
	length_t length = (length_t)(end - begin);
	while ( length >= _3_ary_search_parameters._to_linear_threshold ) {
		fragment_length = length / 3;
		begin_1 = begin + fragment_length;
		if ( pred( *begin_1, q ) ) {
			begin_2 = begin_1 + fragment_length;
			if ( pred( *begin_2, q ) ) {
				begin = begin_2;
				length -= 2 * fragment_length;  // The last fragment
				continue;
			}
			else
				begin = begin_1;
		}
		length = fragment_length;  // Dive into 1/3-rd
	}
	// Linear search
	end = begin + length;
	while ( begin != end && pred( *begin, q ) )
		++begin;
	return begin;
}

template< typename RanIt, typename ValueT >
inline RanIt _3_ary_lower_bound(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ return _3_ary_search( begin, end, q, std::less< ValueT >() ); }

template< typename RanIt, typename ValueT >
inline RanIt _3_ary_upper_bound(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ return _3_ary_search( begin, end, q, std::less_equal< ValueT >() ); }

template< typename RanIt, typename ValueT >
inline bool _3_ary_search(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ RanIt result = _3_ary_search( begin, end, q, std::less< ValueT >() );
	  return result != end && ! (q < *result); }


/// Parameters used by '_4_ary_search' functions.
struct _4_ary_search_parameters_t {
	// Minimal length of the search range, below which we switch 
	// to linear search.
	length_t _to_linear_threshold = 4*2;
} _4_ary_search_parameters;

/// Q-ary search with partitioning into 4 fragments, on each step.
/// At the end, linear search is being performed.
/// Returns the first position 'it' in the range [begin, end), 
/// on which 'pred(*it, q)' is not satisfied.
template< typename RanIt, typename ValueT, typename PredT >
inline RanIt _4_ary_search(
		RanIt begin, RanIt end,
		const ValueT& q, 
		PredT pred )
{
	// Q-ary search
	RanIt begin_1, begin_2, begin_3;
	length_t fragment_length;
	// Work with {begin, length}, not with [begin, end)
	length_t length = (length_t)(end - begin);
	while ( length >= _4_ary_search_parameters._to_linear_threshold ) {
		fragment_length = length / 4;
		begin_1 = begin + fragment_length;
		if ( pred( *begin_1, q ) ) {
			begin_2 = begin_1 + fragment_length;
			if ( pred( *begin_2, q ) ) {
				begin_3 = begin_2 + fragment_length;
				if ( pred( *begin_3, q ) ) {
					begin = begin_3;
					length -= 3 * fragment_length;  // The last fragment
					continue;
				}
				else
					begin = begin_2;
			}
			else
				begin = begin_1;
		}
		length = fragment_length;  // Dive into 1/4-rd
	}
	// Linear search
	end = begin + length;
	while ( begin != end && pred( *begin, q ) )
		++begin;
	return begin;
}

template< typename RanIt, typename ValueT >
inline RanIt _4_ary_lower_bound(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ return _4_ary_search( begin, end, q, std::less< ValueT >() ); }

template< typename RanIt, typename ValueT >
inline RanIt _4_ary_upper_bound(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ return _4_ary_search( begin, end, q, std::less_equal< ValueT >() ); }

template< typename RanIt, typename ValueT >
inline bool _4_ary_search(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ RanIt result = _4_ary_search( begin, end, q, std::less< ValueT >() );
	  return result != end && ! (q < *result); }


/// Parameters used by '_5_ary_search' functions.
struct _5_ary_search_parameters_t {
	// Minimal length of the search range, below which we switch 
	// to linear search.
	length_t _to_linear_threshold = 5*2;
} _5_ary_search_parameters;

/// Q-ary search with partitioning into 5 fragments, on each step.
/// At the end, linear search is being performed.
/// Returns the first position 'it' in the range [begin, end), 
/// on which 'pred(*it, q)' is not satisfied.
template< typename RanIt, typename ValueT, typename PredT >
inline RanIt _5_ary_search( 
		RanIt begin, RanIt end, 
		const ValueT& q, 
		PredT pred )
{
	// Q-ary search
	RanIt begin_1, begin_2, begin_3, begin_4;
	length_t fragment_length;
	// Work with {begin, length}, not with [begin, end)
	length_t length = (length_t)(end - begin);
	while ( length >= _5_ary_search_parameters._to_linear_threshold ) {  
		fragment_length = length / 5;
		begin_1 = begin + fragment_length;
		if ( pred( *begin_1, q ) ) {
			begin_2 = begin_1 + fragment_length;
			if ( pred( *begin_2, q ) ) {
				begin_3 = begin_2 + fragment_length;
				if ( pred( *begin_3, q ) ) {
					begin_4 = begin_3 + fragment_length;
					if ( pred( *begin_4, q ) ) {
						begin = begin_4;
						length -= 4 * fragment_length;  // The last fragment
						continue;
					}
					else
						begin = begin_3;
				}
				else
					begin = begin_2;
			}
			else
				begin = begin_1;
		}
		length = fragment_length;  // Dive into 1/5-th
	}
	// Linear search
	end = begin + length;
	while ( begin != end && pred( *begin, q ) )
		++begin;
	return begin;
}

template< typename RanIt, typename ValueT >
inline RanIt _5_ary_lower_bound(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ return _5_ary_search( begin, end, q, std::less< ValueT >() ); }

template< typename RanIt, typename ValueT >
inline RanIt _5_ary_upper_bound(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ return _5_ary_search( begin, end, q, std::less_equal< ValueT >() ); }

template< typename RanIt, typename ValueT >
inline bool _5_ary_search(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ RanIt result = _5_ary_search( begin, end, q, std::less< ValueT >() );
	  return result != end && ! (q < *result); }


/// Parameters used by '_6_ary_search' functions.
struct _6_ary_search_parameters_t {
	// Minimal length of the search range, below which we switch 
	// to linear search.
	length_t _to_linear_threshold = 6*2;
} _6_ary_search_parameters;

/// Q-ary search with partitioning into 6 fragments, on each step.
/// At the end, linear search is being performed.
/// Returns the first position 'it' in the range [begin, end), 
/// on which 'pred(*it, q)' is not satisfied.
template< typename RanIt, typename ValueT, typename PredT >
inline RanIt _6_ary_search( 
		RanIt begin, RanIt end, 
		const ValueT& q, 
		PredT pred )
{
	// Q-ary search
	RanIt begin_1, begin_2, begin_3, begin_4, begin_5;
	length_t fragment_length;
	// Work with {begin, length}, not with [begin, end)
	length_t length = (length_t)(end - begin);
	while ( length >= _6_ary_search_parameters._to_linear_threshold ) {
		fragment_length = length / 6;
		begin_1 = begin + fragment_length;
		if ( pred( *begin_1, q ) ) {
			begin_2 = begin_1 + fragment_length;
			if ( pred( *begin_2, q ) ) {
				begin_3 = begin_2 + fragment_length;
				if ( pred( *begin_3, q ) ) {
					begin_4 = begin_3 + fragment_length;
					if ( pred( *begin_4, q ) ) {
						begin_5 = begin_4 + fragment_length;
						if ( pred( *begin_5, q ) ) {
							begin = begin_5;
							length -= 5 * fragment_length;  // The last fragment
							continue;
						}
						else
							begin = begin_4;
					}
					else
						begin = begin_3;
				}
				else
					begin = begin_2;
			}
			else
				begin = begin_1;
		}
		length = fragment_length;  // Dive into 1/6-th
	}
	// Linear search
	end = begin + length;
	while ( begin != end && pred( *begin, q ) )
		++begin;
	return begin;
}

template< typename RanIt, typename ValueT >
inline RanIt _6_ary_lower_bound(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ return _6_ary_search( begin, end, q, std::less< ValueT >() ); }

template< typename RanIt, typename ValueT >
inline RanIt _6_ary_upper_bound(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ return _6_ary_search( begin, end, q, std::less_equal< ValueT >() ); }

template< typename RanIt, typename ValueT >
inline bool _6_ary_search(
		RanIt begin, RanIt end,
		const ValueT& q )
	{ RanIt result = _6_ary_search( begin, end, q, std::less< ValueT >() );
	  return result != end && ! (q < *result); }


} // namespace algorithm
} // namespace ml

#endif // ML__ALGORITHM__Q_ARY_SEARCH_HPP
