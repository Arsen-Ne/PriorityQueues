#pragma once
#include <string>
using namespace std;

enum class Priority { high = 1, medium, low };

class Qp3
{
private:
	struct Node {
		int val;
		Priority priority;
		Node* next;
		Node(int _val, Priority _priority) : val(_val), priority(_priority), next(nullptr) {}
	};
	Node* front;
	Node* rear_high;
	Node* rear_medium;
	Node* rear_low;
	unsigned size = 0;
	unsigned size_high = 0;
	unsigned size_medium = 0;
	unsigned size_low = 0;

	void insert_after(Node*& rear, Node*& p);
	void set_front(Node*& p);
	void clone(const Qp3& q);
	void erase();

public:
	Qp3() : front(nullptr), rear_high(nullptr), rear_medium(nullptr), rear_low(nullptr) {}

	~Qp3();

	Qp3(const Qp3& q);
	Qp3& operator = (const Qp3& q);

	Qp3(Qp3&& q) noexcept;
	Qp3& operator = (Qp3&& q) noexcept;

	bool is_empty();
	int get_size();
	int get_size_with_priority(Priority _priority);
	void push(int _val, Priority _priority);
	bool remove_front_element();
	string get_front_element_info();	
};

