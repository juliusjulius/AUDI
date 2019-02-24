#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {

	Vector::Vector(size_t size) : //rychlejsie cez inicializacny zoznam
		memory_(calloc(size, 1)), // skor calloc ako malloc ... 1 lebo pracujeme s byte ( = 1byte)
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_)
	{
		memcpy(this->memory_, other.memory_, size_); 
	}

	Vector::~Vector()
	{
		free(memory_);
		memory_ = nullptr; //nemusi byt
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
		if (this != &other) {
			this->size_ = other.size_;
			this->memory_ = realloc(this->memory_, this->size_);
			memcpy(this->memory_, other.memory_, size_);
		}
		return *this;
	}

	bool Vector::operator==(const Vector& other) const
	{
		return this->size_ == other.size_ && memcmp(this->memory_, other.memory_, this->size_) == 0;
	}

	byte& Vector::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Index out of range.");
		return *(this->getBytePointer(index));
	}

	byte Vector::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Index out of range.");
		return *(this->getBytePointer(index));
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Index out of range.");
		DSRoutines::rangeCheckExcept(index + count, this->size_, "Index out of range.");

		memmove(&dest, this->getBytePointer(index), count);
		return dest;
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Index out of range.");
		DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_, "Index out of range.");
		DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "Index out of range.");
		DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_, "Index out of range.");

		memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
	}

	byte* Vector::getBytePointer(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Index out of range.");
		return reinterpret_cast<byte*>(this->memory_) + index; // lepsie ako (byte*)
	}

}