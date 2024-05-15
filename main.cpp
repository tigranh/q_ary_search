
#include <iostream>
#include <random>
#include <algorithm>
#include <type_traits>
#include <chrono>
#include <cassert>

#include "q_ary_search.hpp"


/// Runs general tests on provided search function.
template< typename RanIt, typename ValueType >
void test_search_on_sorted_int_array(
		RanIt (*search_f)( RanIt begin, RanIt end, const ValueType& q ) )
{
	// Test on ordinary sequence
	{
		const int a[] = { 2, 4, 6, 7, 12, 13, 16, 19, 23, 24, 27, 32, 36 };
		const int n = sizeof(a) / sizeof(a[0]);
		const int* result;
		//
		result = (*search_f)( a, a+n, 19 );
		assert( result == a + 7 );
		//
		result = (*search_f)( a, a+n, 36 );
		assert( result == a + 12 );
		//
		result = (*search_f)( a, a+n, 6 );
		assert( result == a + 2 );
		//
		result = (*search_f)( a, a+n, 20 );
		assert( result == a + 8 );
		//
		result = (*search_f)( a, a+n, 8 );
		assert( result == a + 4 );
		//
		result = (*search_f)( a, a+n, 1 );
		assert( result == a );
		//
		result = (*search_f)( a, a+n, 42 );
		assert( result == a + n );
	}

	// Test on fragmented sequence
	{
		const int a[] = { 3, 3, 3, 7, 7, 7, 7, 12, 12, 16, 16, 16, 16 };
		const int n = sizeof(a) / sizeof(a[0]);
		const int* result;
		//
		result = (*search_f)( a, a+n, 7 );
		assert( result == a + 3 );
		//
		result = (*search_f)( a, a+n, 8 );
		assert( result == a + 7 );
		//
		result = (*search_f)( a, a+n, 2 );
		assert( result == a );
		//
		result = (*search_f)( a, a+n, 20 );
		assert( result == a + n );
		//
		result = (*search_f)( a, a+n, 15 );
		assert( result == a + 9 );
	}

	// Test on constant sequence
	{
		const int a[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4 };
		const int n = sizeof(a) / sizeof(a[0]);
		const int* result;
		//
		result = (*search_f)( a, a+n, 4 );
		assert( result == a );
		//
		result = (*search_f)( a, a+n, 5 );
		assert( result == a + n );
	}

	// Test on empty sequence
	{
		const int* a = nullptr;
		const int n = 0;
		const int* result;
		//
		result = (*search_f)( a, a+n, 6 );
		assert( result == a );
		//
		result = (*search_f)( a, a+n, 12 );
		assert( result == a );
	}

}


/// The clock-type, used to measure performance.
typedef std::chrono::high_resolution_clock clock_type;

// A global "collector" variable, which will accumulate results of 
// runs of all searches, in order to avoid compiler optimizations.
volatile unsigned long long collector = 0;


/// Prepares a sorted array of integers of length 'N', in memory 
/// location starting from 'begin'.
/// Values of the array are randomly and unformly generated in the range 
/// [min_value, max_value].
template< typename RanIt, typename ValueType, typename Gen >
void prepare_sorted_int_array( RanIt begin, int N, 
		const ValueType& min_value, const ValueType& max_value, 
		Gen& gen )
{
	// Generate values
	std::uniform_int_distribution< ValueType > dist( min_value, max_value );
	for ( int i = 0; i < N; ++i )
		*(begin + i) = dist( gen );
	// Sort them
	std::sort( begin, begin + N );
}


/// Prepares a sorted array of real numbers of length 'N', in memory 
/// location starting from 'begin'.
/// Values of the array are randomly and unformly generated in the range 
/// [min_value, max_value].
template< typename RanIt, typename ValueType, typename Gen >
void prepare_sorted_real_array( RanIt begin, int N, 
		const ValueType& min_value, const ValueType& max_value, 
		Gen& gen )
{
	// Generate values
	std::uniform_real_distribution< ValueType > dist( min_value, max_value );
	for ( int i = 0; i < N; ++i )
		*(begin + i) = dist( gen );
	// Sort them
	std::sort( begin, begin + N );
}


/// Invokes provided search function 'search_f' on sorted range [begin, end),
/// querying all the values in range [start_q, finish_q], stepping inside it 
/// by 'step_q'.
/// Prints and returns the time spent on all those searches.
template< typename RanIt, typename ValueType >
clock_type::duration run_searches( 
		RanIt (*search_f)( RanIt begin, RanIt end, const ValueType& value ), 
		RanIt begin, RanIt end, 
		ValueType start_q, 
		ValueType finish_q, 
		ValueType step_q )
{
	clock_type::time_point start_time = clock_type::now();
	// Search
	for ( ValueType q = start_q; q <= finish_q; q += step_q ) {
		RanIt result = (*search_f)( begin, end, q );
		// Just add the offset to collector.
		collector += (result - begin);
	}
	// Track
	clock_type::duration dur = clock_type::now() - start_time;
	std::cout << std::chrono::duration_cast< std::chrono::milliseconds >( dur ).count()
			<< " msc" << std::endl;
	return dur;
}


int main( int argc, char* argv[] )
{
	std::cout << "Testing search algorithms: " << std::endl;

	std::cout << "\t std::lower_bound< int >() ..." << std::endl;
	test_search_on_sorted_int_array( & std::lower_bound< const int*, int > );
	//
	std::cout << "\t _2_ary_search< int >() ..." << std::endl;
	test_search_on_sorted_int_array( & ml::algorithm::_2_ary_lower_bound< const int*, int > );
	//
	std::cout << "\t _3_ary_search< int >() ..." << std::endl;
	test_search_on_sorted_int_array( & ml::algorithm::_3_ary_lower_bound< const int*, int > );
	//
	std::cout << "\t _4_ary_search< int >() ..." << std::endl;
	test_search_on_sorted_int_array( & ml::algorithm::_4_ary_lower_bound< const int*, int > );
	//
	std::cout << "\t _5_ary_search< int >() ..." << std::endl;
	test_search_on_sorted_int_array( & ml::algorithm::_5_ary_lower_bound< const int*, int > );
	//
	std::cout << "\t _6_ary_search< int >() ..." << std::endl;
	test_search_on_sorted_int_array( & ml::algorithm::_6_ary_lower_bound< const int*, int > );

	//

	std::default_random_engine gen;

	std::cout << "Benchmarking search algorithms: " << std::endl;

	typedef float data_t;  // Type of data, on which Q-ary search will run

	const int N = 10'000;           // Length of the sorted array
	data_t A[ N ];                  // The sorted array
	const data_t start_q = 0;              // Start of the query range
	const data_t finish_q = 10'000'000;    // Finish of the query range
	const data_t step_q = 1;               // The step inside the query range

	std::cout << "\t ... generating sorted array of length N=" << N 
			<< ", with values in [" << start_q << ", " << finish_q << "]," 
			<< std::endl;
	static_assert( 
			std::is_integral_v< data_t > || std::is_floating_point_v< data_t >,
			"Can't generate array of random numbers with given data type." );
	if constexpr ( std::is_integral_v< data_t > )
		prepare_sorted_int_array( 
				A, N, 
				start_q, finish_q, gen );
	else if constexpr ( std::is_floating_point_v< data_t > )
		prepare_sorted_real_array( 
				A, N, 
				start_q, finish_q, gen );

	std::cout << "\t ... running search algorithms for "
			<< (finish_q - start_q) / step_q << " times each," << std::endl;

	std::cout << "\t std::lower_bound<...>() ... ";
	run_searches( & std::lower_bound< data_t*, data_t >,
			A, A+N, 
			start_q, finish_q, step_q );

	std::cout << "\t _2_ary_search<...>() ... ";
	run_searches( & ml::algorithm::_2_ary_lower_bound< data_t*, data_t >,
			A, A+N, 
			start_q, finish_q, step_q );

	std::cout << "\t _3_ary_search<...>() ... ";
	run_searches( & ml::algorithm::_3_ary_lower_bound< data_t*, data_t >,
			A, A+N, 
			start_q, finish_q, step_q );

	std::cout << "\t _4_ary_search<...>() ... ";
	run_searches( & ml::algorithm::_4_ary_lower_bound< data_t*, data_t >,
			A, A+N, 
			start_q, finish_q, step_q );

	std::cout << "\t _5_ary_search<...>() ... ";
	run_searches( & ml::algorithm::_5_ary_lower_bound< data_t*, data_t >,
			A, A+N, 
			start_q, finish_q, step_q );

	std::cout << "\t _6_ary_search<...>() ... ";
	run_searches( & ml::algorithm::_6_ary_lower_bound< data_t*, data_t >,
			A, A+N, 
			start_q, finish_q, step_q );



	// Try move the array data to heap
	//    or to global memory

	// Try playing with array length
	//

	// Try searches on other data types
	//

	// Try on other compilers
	//





	std::cout << "Final value of the 'collector' variable (to prevent compiler optimizations): " 
			<< collector << std::endl;

	return 0;
}

