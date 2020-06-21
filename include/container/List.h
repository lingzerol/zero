#ifndef ZERONET_CONTAINER_LIST_H
#define ZERONET_CONTAINER_LIST_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "common.h"

_ZERONET_BEGIN


class List {
private:
	using _inner_vector_data_pointer_type = std::shared_ptr<void>;
	using  _inner_data_type = std::vector<_inner_vector_data_pointer_type>;
	using _inner_data_pointer_type = std::shared_ptr<_inner_data_type>;
	using _type_vector = std::vector<std::string>;
public:
	List() noexcept:data(new _inner_data_type()),type_name() {
	
	}

private:
	void _const_list_copy(const List& list) {
		data.reset(new _inner_data_type());
		*data = *list.data;
		type_name = list.type_name;
	}
public:
	List(const List& list)noexcept:data(nullptr) {
		_const_list_copy(list);
	}
	List& operator=(const List&list) {
		_const_list_copy(list);
		return *this;
	}

private:
	void _no_const_list_ref(List& list) {
		data = list.data;
	}
public:
	List(List& list)noexcept :data(nullptr) {
		_no_const_list_ref(list);
	}
	List& operator=(List&list) {
		_no_const_list_ref(list);
		return *this;
	}
private:
	void _no_const_list_ref(List&& list) {
		data = list.data;
		list.data = nullptr;
	}
public:
	List(List&& list)noexcept:data(nullptr) {
		_no_const_list_ref(list);
	}
	List& operator=(List&&list) {
		_no_const_list_ref(list);
		return *this;
	}

private:
	void _const_list_copy(const _inner_data_pointer_type& _data)noexcept {
		data.reset(new _inner_data_type());
		*data = *_data;
	}
	List(const _inner_data_pointer_type& data)noexcept :data(nullptr) {
		_const_list_copy(data);
	}

	void _no_const_list_ref(_inner_data_pointer_type& _data)noexcept {
		data = _data;
	}
	List(_inner_data_pointer_type& data)noexcept :data(nullptr) {
		_no_const_list_ref(data);
	}

	void _no_const_list_ref(_inner_data_pointer_type&& _data) noexcept {
		data = _data;
	}
	List(_inner_data_pointer_type&& data)noexcept :data(nullptr) {
		_no_const_list_ref(data);
	}

public:
	List copy() noexcept {
		_inner_data_pointer_type nd(new _inner_data_type());
		*nd = *data;
		return List(nd);
	}
	void copy(List& list) noexcept {
		list = List(data);
	}
	void copy(List&& list) noexcept {
		list = List(data);
	}

private:
	int8 check_index(int8 index) {
		if (index<0 || index > data->size()) {
			return data->size() + index;
		}
		return index;
	}
public:

	_inner_vector_data_pointer_type operator[](int8 index) {
		index = check_index(index);
		return (*data)[index];
	}


	template <typename T>
	void append(const T& val) noexcept {
		_inner_vector_data_pointer_type save_val_pointer(reinterpret_cast<void*>(new T(val)));
		data->push_back(save_val_pointer);
		type_name.push_back(typeid(T).name);
	}//append with copy value


	template <> void append(const std::shared_ptr<void>& val) {
		data->push_back(val);
		type_name.push_back(typeid(std::shared_ptr<void>).name);
	}

	List get(int8 start, int8 end, int8 step=1) {
		List result;
		start = check_index(start);
		end = check_index(end);
		typedef bool (*end_function)(int8, int8);
		if (step == 0) {
			return result;
		}
		if ((start <= end && step < 0) || (start > end&& end > 0)) {
			std::swap(start, end);
		}
		end_function check = [](int8 l, int8 r) {return l < r; };
		if (start > end) {
			check = [](int8 l, int8 r) {return l > r; };
		}
		for (int8 i = start; check(i, end); ++i) {
			result.append((*data)[i]);
		}
	}
	
	template <typename T>
	T& get(int8 index) {
		index = check_index(index);
		return *reinterpret_cast<T*>((*data)[index].get());
	}

	template <typename T>
	const T& get(int8 index) const {
		index = check_index(index);
		return reinterpret_cast<T*>((*data)[index].get());
	}
	
	uint8 size() const {
		return data->size();
	}
	uint8 len() const {
		return data->size();
	}

	~List() {
	}
private:
	_inner_data_pointer_type data;
	_type_vector type_name;
};

_ZERONET_END

#endif