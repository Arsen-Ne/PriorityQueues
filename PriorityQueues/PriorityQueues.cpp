#include <iostream>
#include <string>
#include "Qp3.h"
using namespace std;

void swap(Qp3& q1, Qp3& q2) {
	Qp3 tmp(std::move(q1));
	q1 = std::move(q2);
	q2 = std::move(tmp);
}

int main()
{
	setlocale(LC_ALL, "russian");
	Qp3* q = new Qp3();
	//q->push(0, Priority::high);
	//q->push(1, Priority::low);
	//q->push(2, Priority::medium);
	//q->push(3, Priority::low);
	//q->push(4, Priority::low);	
	//q->push(6, Priority::high);	
	
	//Qp3 q2(*q); // вызов копирующего конструктора	
	//Qp3 q2(move(*q)); // вызов перемещающего конструктора

	Qp3* q3 = new Qp3(); 
	q3->push(10, Priority::low);		
	swap(q, q3); //проверка семантики перемещения	

	//q2.remove_front_element();	
	//cout << "q: " << q->get_front_element_info() << endl;
	//cout << "q2: " << q2.get_front_element_info() << endl;

	
	cout << "Use" << endl;
	cout << "0 - to exit" << endl;
	cout << "1 - определение числа элементов в очереди, имеющих конкретный приоритет, и общего количества элементов" << endl;
	cout << "2 - проверку на пустоту очереди" << endl;
	cout << "3 - вставку элемента со значением и приоритетом;" << endl;
	cout << "4 - удаление элемента из очереди;" << endl;
	cout << "5 - получение информации о приоритете и значении элемента, стоящего в голове очереди." << endl;

	while (true) {
		cout << endl << "Enter option key: ";
		int s;
		cin >> s;
		switch (s) {
		case 0:
			return 0;
		case 1:
			cout << endl << "low: " << (q->get_size_with_priority(Priority::low)) << endl;
			cout << "medium: " << (q->get_size_with_priority(Priority::medium)) << endl;
			cout << "high: " << (q->get_size_with_priority(Priority::high)) << endl;
			cout << "total: " << (q->get_size()) << endl;
			break;
		case 2:
			if (q->is_empty()) {
				cout << "очередь пустая" << endl;
				break;
			}
			cout << "очередь не пустая" << endl;
			break;
		case 3:
			int n, m;
			cout << "введите значение элемента" << endl;
			cin >> n;
			cout << "выберите приоритет элемента" << endl;
			cout << "1 - high" << endl;
			cout << "2 - medium" << endl;
			cout << "3 - low" << endl;
			cin >> m;	
			if (m > 0 and m < 4) {
				q->push(n, (Priority)m);
				cout << "элемент добавлен в очередь" << endl;
				break;
			}
			cout << "неправильная опция, элемент не добавлен" << endl;
			break;		
		case 4:
			if (q->remove_front_element()) {
				cout << "первый элемент удален из очереди" << endl;
				break;
			}
			cout << "нечего удалять, очередь пустая" << endl;
			break;
		case 5:
			cout << q->get_front_element_info() << endl;
			break;
		default:
			cout << "Wrong option";
			break;
		}
	} 	
}