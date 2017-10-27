#ifndef __UTIL_ITERATOR_HPP
#define __UTIL_ITERATOR_HPP

#include <lang/Exception.hpp>
#include <memory>

namespace util {

template<class T>
class IteratorBase {
public:
	virtual ~IteratorBase() {}
	virtual bool hasNext() = 0;
	virtual const T& next() = 0;
	virtual void remove() {
		throw lang::UnsupportedOperationException("remove");
	}
};

template<class T>
using Iterator = std::shared_ptr<IteratorBase<T>>;

template<class T, class... Args>
std::shared_ptr<T> makeIterator(Args&&... args) { return std::make_shared<T>(args...); }

} //namespace util

#endif