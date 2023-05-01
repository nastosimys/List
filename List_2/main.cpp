#include <iostream>
#include <fstream>

using namespace std;

struct Link {
	int val;
	Link* next;
	Link(int _val, Link* _n = nullptr) :val(_val), next(_n) {}
};

class List {
	Link* first;
	Link* end;
public:
	List() {
		Link* p = new Link(0);
		p->next = p;
		first = p;
		end = p;
	}
	void add(int a) {
		Link* tmp = first;
		while (tmp->next != first) {
			if (tmp->next->val > a) {
				Link* b = new Link(a, tmp->next);
				tmp->next = b;
				return;
			}
			tmp = tmp->next;
		}
		Link* c = new Link(a, first);
		tmp->next = c;
		end = c;
	}

	void addLast(int a) {
		Link* p = new Link(a, first);
		end->next = p;
		end = end->next;
	}

	List(const List& l) {
    	first = new Link(0);
    	first->next = first; 
    	end = first;
		Link* tmp = l.first->next;
    	while (tmp != l.first) {
    		addLast(tmp->val);
    		tmp = tmp->next;
    	}
	}
	List& operator=(const List& l) {
		if (this != &l) {
			Link* tmp = l.first->next;
			this->clean();
			while (tmp != l.first) {
				addLast(tmp->val);
				tmp = tmp->next;
			}
		}
		return *this;
	}
	friend ostream& operator << (ostream& out, List& list) {
		Link* tmp = list.first->next;
		while (tmp != list.first) {
			out << tmp->val << " ";
			tmp = tmp->next;
		}
		out << "$ ";
		return out;
	}
	void clean() {
/*		Link* tmp = first;
		while (tmp->next != first) {
			Link* tmp = first->next;
			first->next = tmp->next;
			delete tmp;
		}*/
    	first->next = first;
	}
	friend istream& operator>>(istream& in, List& list) {
		list.clean();
		string tmp;
		in >> tmp;
		string sep = "$";
		while (tmp != sep) {
//			list.addLast(atoi(tmp.c_str()));
			list.add(atoi(tmp.c_str()));
			in >> tmp;
		}
		return in;
	}
	List intersection(List list_1, List list_2) {
		List list_3;
		Link* tmp_1 = list_1.first->next;
		Link* tmp_2 = list_2.first->next;
		while ((tmp_1 != list_1.first) && (tmp_2 != list_2.first)) {
			if (tmp_1->val < tmp_2->val) {
				tmp_1 = tmp_1->next;
			}
			else if (tmp_1->val > tmp_2->val) {
				tmp_2 = tmp_2->next;
			}
			else {
				list_3.addLast(tmp_2->val);
				tmp_1 = tmp_1->next;
				tmp_2 = tmp_2->next;
			}
		}
		return list_3;
	}
	~List() {
		while (first != end) {
			Link* tmp = first->next;
			delete first;
			first = tmp;
		}
	}
};

int main() {
	List list_1, list_2, list_3;

	ifstream file_1("List1.txt");
	file_1 >> list_1;
	cout << "list_1: " << list_1;
	cout << endl;
	ifstream file_2("List2.txt");
	file_2 >> list_2;
	cout << "list_2: " << list_2;
	cout << endl;

	list_3 = list_3.intersection(list_1, list_2);
	cout << "list_3: " << list_3;
	ofstream file3("List3.txt");
	file3 << list_3;
	return 0;
}