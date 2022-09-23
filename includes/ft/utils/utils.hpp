#ifndef CONTAINERS_UTILS_HPP
# define CONTAINERS_UTILS_HPP

#include "ft/utils/iterator_traits.hpp"

namespace ft {

  /* 
   * enable_if  
   *
   * STL says :
   * Define a member typedef type only if a boolean constant is true.
   * 
   * And this 35 minute video explains its usage :
   * https://www.youtube.com/watch?v=Vkck4EU2lOU
   * 
   * My explanation:
   * if you have a function that need a return type TYPE, but there's 
   * two different possible implementations based on a condition,
   * instead of implementing an overload for the function we
   * can "S I M P L Y" define the return type as :
   *  
   * enable_if<condition, TYPE>::type func( ... ).
   * 
   * This will only "activate" the function if the condition is true.
   * 
   */
  template < bool, typename T >
  struct enable_if
  {};

  template <typename T>
  struct enable_if<true, T>
  { typedef T type; };

  /*
   * is_integral 
   *
   * See:
   * https://en.cppreference.com/w/cpp/types/is_integral
   * 
   * This is to be combined with enable_if to make cool
   * template SFINAE's.
   */
  template <typename T>
  struct is_integral
  { static bool const value = false; };

  template <>
  struct is_integral<bool> { static bool const value = true; };

  template <>
  struct is_integral<char> { static bool const value = true; };

  template <>
  struct is_integral<unsigned char> { static bool const value = true; };

  template <>
  struct is_integral<wchar_t> { static bool const value = true; };

  template <>
  struct is_integral<short> { static bool const value = true; };

  template <>
  struct is_integral<unsigned short> { static bool const value = true; };

  template <>
  struct is_integral<int> { static bool const value = true; };

  template <>
  struct is_integral<unsigned int> { static bool const value = true; };

  template <>
  struct is_integral<long> { static bool const value = true; };

  template <>
  struct is_integral<unsigned long> { static bool const value = true; };

  /* lexicographical_compare
   * https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
   *
   * checks wether the first range [ first1, last1 ] is 
   * lexicographically less than the second range [ first2, last2].
   * 
   * InputIt refers, quite cleverly, to Input Iterator.
   * This means the class to be used has to at least
   * have operators ->, *, !=,  ++, and the typedefs
   * reference and value_type.
   * Rules :
   *  + Two ranges are compared element by element.
   *  + The first mismatching element defines which range is
   *    lexicographically less or greater than the other.
   *  + If one range is a prefix of another, the shorter range
   *    is lexicographically less than the other.
   *  + If two ranges have equivalent elements and are of the same
   *    length, then the ranges are lexicographically equal.
   *  + An empty range is lexicographically less than any non-empty range.
   *  + Two empty ranges are lexicographically equal.
   *
   */
  template< class InputIt1, class InputIt2 >
  bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2 )
  {
    while (first1 != last1) {
      if (first2 == last2 || *first1 < *first2 ) {
        break ;
      } else if (*first1 > *first2) {
        return true;
      }
      ++first1;
      ++first2;
    }
    return (first1 == last1) && (first2 != last2);
  }

  /* Cpp reference says :
   * comp	-	comparison function object (i.e. an object that
   * satisfies the requirements of Compare) which returns
   * ​true if the first argument is less than the second.
   */
  template< class InputIt1, class InputIt2, class Compare >
  bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2,
                                Compare comp )
  {
    while (first1 != last1) {
      if (first2 == last2 || comp(*first1, *first2)) {
        break ;
      } else if (comp(*first2, *first1)) {
        return true;
      }
      ++first1;
      ++first2;
    }
    return (first1 == last1) && (first2 != last2);
  }

  /*
   * equal
   * 
   * returns true if range [ first1, last1 ] is equal
   * to [ first2, first2 - first1 + last1 ]. This function
   * is more interesting than it seems :
   * 
   * f1, f2, l1 represent iterator positions. But this iterators
   * point to a type. Assume it is char (int is confusing because
   * theres no concept of distance here, just equivalence).
   * If I go from it1 to last1, is the data the same as if I go from
   * it2 to last1 + it1 ? (rememver iterators are ALWAYS pointers so
   * they can be summed up).
   * 
   * Case where it is :
   * 
   *         it1       it2                    last1
   *         |          |                       |
   * data = abcabcabcabcabcabcabcabcabcabcabcabcabcabcabc...
   *       [abcabcabcabcabcabcabcabcabcabcabcabc]
   *       <------------ [it1, last1] --------->
   *                   [abcabcabcabcabcabcabcabcabcabcabc]
   *                   <--- [it2, it2 + last1 - it1] -->
   * 
   * NOTICE how if it2 was moved 1 iterator position to the
   * right or left, then the segments would NOT be the equal.
   * 
   * Case where it is not:
   * 
   *         it1       it2          last1
   *         |          |            |
   * data = abcdefghijklmnopqrstuvwxyz
   *        
   * So this function is, in a sense, trying to check wether
   * these two segments of data are equivalent. There's also
   * a very cool example of use to check wether a word is or 
   * not a palyndrome using reverse iterators:
   * https://en.cppreference.com/w/cpp/algorithm/equal
   */
  template< class InputIt1, class InputIt2 >
  bool equal( InputIt1 first1, InputIt1 last1,
              InputIt2 first2 )
  {
    while (first1 != last1) {
      if (*first1 != *first2) {
        return false;
      }
      ++first1;
      ++first2;
    }
    return true;
  }

  /* From
   * https://stackoverflow.com/questions/13675203/implementation-safe-nullptr
   */
  const class nullptr_t {
      public:

          /* Return 0 for any class pointer */
          template<typename T>
          operator T*() const {
              return 0;
          }

          /* Return 0 for any member pointer */
          template<typename T, typename U>
          operator T U::*() const {
              return 0;
          }

      private:

          /* Not allowed to get the address */
          void operator&() const;

  } nullptr_t = {};

  /* distance implementation
   * Abstracion of what normal distance (when speaking about
   * numbers) is.
   */
  template<class It>
  typename ft::iterator_traits<It>::difference_type
      distance(It first, It last,
                typename enable_if<!is_integral<It>::value, It>::type* = 0)
  {
      typename ft::iterator_traits<It>::difference_type result = 0;
      while (first != last) {
          ++first;
          ++result;
      }
      return result;
  }

} /* namespace ft */

#endif /* CONTAINERS_UTILS_HPP */