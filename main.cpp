#include <iostream>
#include <fstream>

using namespace std;

struct Node {
	public:
		Node *pNext = nullptr;
		int value;

		Node(int value) {
			this->value = value;
		}
};

class List {
	public:
		List() {};

		void push(char data[0x255]) {
			int number = this->charToInt(data);

			if (this->head == nullptr) {
				this->head = new Node(number);
				this->end = this->head;

			} else {
				Node *current = this->end;

				current->pNext = new Node(number);
				this->end = current->pNext;
			}

			this->size++;
		};

		void clear() {
			Node *current = this->head;
			Node *next;

			while (current != nullptr) {
				next = current->pNext;
				delete current;
				current = next;
			}

			this->head = nullptr;
			this->end = nullptr;

			this->size = 0;
		};

		int getSize() {
			return this->size;
		};

		int getValue(int index) {
			Node *current = this->head;

			int counter = 0;

			while (current != nullptr) {
				if (counter == index) {
					return current->value;
				}

				current = current->pNext;
				counter++;
			}
		};

	private:
		int size = 0;
		Node *head = nullptr;
		Node *end = nullptr;

		int charToInt(const char *s) {
			int sign = 1;

			if (*s == '-') {
				sign = -1;
				s++;
			}

			int num = 0;
			while (*s) {
				num = ((*s) - '0') + num * 10;
				s++;
			}

			return num * sign;
		}
};

const char input[] = "input.txt";
const char output[] = "output.txt";

bool isClearCommand(char *text) {
	return (string) text == "clear";
}

int main () {

	List list;

	cout << "На первой строке необходимо указать начальные элементы (целые числа) списка\n"
		 "Каждая последующая строка это команды над списком:\n\n"
   		 "любое количество элементов, которое пойдет в конец списка\n"
	   	 "clear - очистить весь список\n\n";

	ifstream inputFile(input);

	if (inputFile.is_open()) {
		char line[0x255];

		while (inputFile >> line) {
			if (isClearCommand(line)) {
				list.clear();
			} else {
				list.push(line);
			}
		}

		inputFile.close();
	}

	ofstream outputFile(output);

	for (int i = 0; i < list.getSize(); i++) {
		int a = list.getValue(i);
		outputFile << a << endl;
	}

	return 0;
}
