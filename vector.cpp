#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {

	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)),
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_)
	{
		memcpy(memory_, other.memory_, other.size_);
	}

	Vector::~Vector()
	{
		free(memory_);
		memory_ = nullptr;
		size_ = 0;
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure & Vector::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		this->size_ = other.size_;
		if (this->size_ != other.size_) {
			realloc(memory_, other.size_);
		}
		memcpy(this->memory_, other.memory_, this->size_);
		return *this;

	}

	bool Vector::operator==(const Vector& other) const
	{
		return this->size_ == other.size_ && memcmp(this->memory_, other.memory_, this->size_);
	}

	byte& Vector::operator[](const int index)
	{
		if(index >= size_)
			throw std::exception("std::out_of_range");
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte Vector::operator[](const int index) const
	{
		if (index >= size_)
			throw std::exception("std::out_of_range");
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		if (index + count >= size_)
			throw std::exception("std::out_of_range");

		memcpy(&dest, getBytePointer(index), count);
		return dest;
		
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		if (length == 0)
			return;
		if(length + srcStartIndex > src.size_ || length + destStartIndex > dest.size_)
			throw std::exception("std::out_of_range");
		if (&src == &dest && (srcStartIndex + length <= destStartIndex || destStartIndex + length <= srcStartIndex))
			memmove(src.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		else
			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		
	}

	byte* Vector::getBytePointer(const int index) const
	{
		return (reinterpret_cast<byte*>(memory_) + index);
	}

}