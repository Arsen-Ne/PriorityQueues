#include "Qp3.h"
#include <string>
#include <iostream>
//using namespace std;

string priorityToStr(Priority priority) {
	switch (priority) {
	case Priority::high: return "high";
	case Priority::medium: return "medium";
	case Priority::low: return "low";
	};
}

void Qp3::insert_after(Node*& rear, Node*& p) {
	p->next = rear->next;
	rear->next = p;
	rear = p;
}

void Qp3::set_front(Node*& p) {
	p->next = front;
	front = p;
}

void Qp3::clone(const Qp3& q) {
	Node* tmp = q.front;
	for (unsigned i = 0; i < q.size; i++) {
		push(tmp->val, tmp->priority);
		tmp = tmp->next;
	}
}

void Qp3::move(Node*& a, Node*& b)
{
	a = b;
	b = nullptr;
}

void Qp3::move(Qp3&& q)
{
	move(front, q.front);
	move(rear_high, q.rear_high);
	move(rear_medium, q.rear_medium);
	move(rear_low, q.rear_low);

	size = q.size;
	size_high = q.size_high;
	size_medium = q.size_medium;
	size_low = q.size_low;	
	q.size = 0;
	q.size_high = 0;
	q.size_medium = 0;
	q.size_low = 0;
}

void Qp3::erase() {
	while (remove_front_element());
}

Qp3::~Qp3() {
	erase();
}

Qp3::Qp3(const Qp3& q) {
	clone(q);
}

Qp3& Qp3::operator = (const Qp3& q) {
	if (this != &q) {
		erase();
		clone(q);
	}
	return *this;
}

// move constructor
Qp3::Qp3(Qp3&& q) noexcept : front(nullptr), rear_high(nullptr), rear_medium(nullptr), rear_low(nullptr) {
	*this = std::move(q); // calls move assignment operator
}

// move assignment operator
Qp3& Qp3::operator = (Qp3&& q) noexcept {
	if (&q == this)
		return *this; // проверка на самоприсваивание 
	erase();
	this->move(std::move(q));
	return *this;
}

bool Qp3::is_empty() const {
	return front == nullptr;
}

int Qp3::get_size() const {	
	return size;
}

int Qp3::get_size_with_priority(Priority _priority) const {
	switch (_priority) {
	case Priority::high: return	size_high;
	case Priority::medium: return size_medium;
	case Priority::low: return size_low;
	}
}

void Qp3::push(int _val, Priority _priority) {
	Node* p = new Node(_val, _priority);
	size++;
	switch (_priority) {
	case Priority::high:
		size_high++;
		if (rear_high == nullptr) {
			set_front(p);
			rear_high = p;
			return;
		}
		insert_after(rear_high, p);
		break;
	case Priority::medium:
		size_medium++;
		if (rear_medium == nullptr) {
			if (rear_high == nullptr) {
				set_front(p);
				rear_medium = p;
				return;
			}
			rear_medium = rear_high;
		}
		insert_after(rear_medium, p);
		break;
	case Priority::low:
		size_low++;
		if (rear_low == nullptr) {
			if (is_empty()) {
				set_front(p);
				rear_low = p;
				return;
			}
			else {
				rear_low = (rear_medium == nullptr) ? rear_high : rear_medium;
			}
		}
		insert_after(rear_low, p);
		break;
	}
}

bool Qp3::remove_front_element() {
	if (!is_empty()) {
		Node* p = front;
		front = p->next;
		size--;
		switch (p->priority) {
		case Priority::high:
			size_high--;
			if (size_high == 0) {
				rear_high = nullptr;
			}
			break;
		case Priority::medium:
			size_medium--;
			if (size_medium == 0) {
				rear_medium = nullptr;
			}
			break;
		case Priority::low:
			size_low--;
			if (size_low == 0) {
				rear_low = nullptr;
			}
			break;
		}
		delete p;
		return true;
	}
	return false;
}

string Qp3::get_front_element_info() const {
	if (!is_empty()) {
		return "value: " + to_string(front->val) + ", priority: " + priorityToStr(front->priority);
	}
	return "очередь пустая, нет первого элемента";
}
