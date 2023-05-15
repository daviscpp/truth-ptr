#include <stdexcept>

#ifndef TRUTH_PTR_H
#define TRUTH_PTR_H

template<typename T>
class truth_ptr
{
public:
	truth_ptr() = default;
	truth_ptr(const T& ptr) : data(new T (ptr)) {};
	truth_ptr(const truth_ptr& truth) : data(new T(*(truth.data))) {}
	truth_ptr(truth_ptr<T>&& truth);
	~truth_ptr() { delete this->data; }
	truth_ptr<T>& operator=(truth_ptr<T>&& truth);
	truth_ptr<T>& operator=(const truth_ptr<T>& truth);
	T& operator*();
	T* operator->();
private:
	T* data{ nullptr };
};

template<typename T>
T& truth_ptr<T>::operator*()
{
	if (!this->data)
	{
		throw std::runtime_error("attempted to dereference null pointer, is this information legit?");
	}

	return *this->data;
}

template<typename T>
T* truth_ptr<T>::operator->()
{
	if (!this->data)
	{
		throw std::runtime_error("attempted to dereference null pointer, is this information legit?");
	}

	return this->data;
}

template<typename T>
inline truth_ptr<T>::truth_ptr(truth_ptr<T>&& truth)
	: data(truth.data)
{
	truth.data = nullptr;
}

template<typename T>
inline truth_ptr<T>& truth_ptr<T>::operator=(truth_ptr<T>&& truth)
{
	delete this->data;
	this->data = truth.data;
	truth.data = nullptr;

	return *this;
}

template<typename T>
truth_ptr<T>& truth_ptr<T>::operator=(const truth_ptr<T>& truth)
{
	//ensure we don't shoot ourselves in the foot
	if (this != &truth)
	{
		T* temp = new T(*(truth.data));
		delete this->data;
		this->data = temp;
	}

	return *this;
}

#endif