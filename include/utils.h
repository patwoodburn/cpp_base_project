#include <array>
#include <functional>
#include <algorithm>

template<class Iterator>
inline void BubbleSort(Iterator begin, Iterator end) {
   for (Iterator i = begin; i  != end; ++i)
      for (Iterator j = begin; j < i; ++j)
         if (*i < *j)
            std::iter_swap(i, j);
}

template<class Iterator>
inline void CopySort(Iterator begin, Iterator end, Iterator out, void func (Iterator, Iterator)){
   std::copy(begin, end, out);
   func(out, out + (end - begin));
}