#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

struct Elem
{
	int value = 0;
	Elem* npx = NULL;
};

int count(Elem* head, Elem* tail, Elem* qFront, Elem* qBack, bool& isEmpty);
void garbage_hard(Elem*& head, Elem*& tail, Elem* qFront, Elem* qBack, Elem*& actual, bool& isEmpty);
void garbage_soft(Elem* head, Elem* tail, Elem* qFront, Elem* qBack, bool& isEmpty);
void printQueue(Elem* head, Elem* tail, Elem* qFront, Elem* qBack, bool& isEmpty);
void push(int value, Elem*& qfront, Elem*& qBack, Elem*& head, Elem*& tail, Elem*& actual, bool& isEmpty);
void pop(Elem*& qFront, Elem* qBack, Elem* head, Elem* tail, bool& isEmpty);
void add_beg(int value, Elem*& head, Elem*& tail, Elem*& actual);
void add_end(int value, Elem*& head, Elem*& tail, Elem*& actual);
void add_act(int value, Elem*& head, Elem*& tail, Elem*& actual);
void print_forward(Elem* head);
void print_backwards(Elem* tail);
void print_actual(Elem* actual);
void next(Elem*& actual, Elem* head);
void prev(Elem*& actual, Elem* tail);
void del_beg(Elem*& actual, Elem*& head, Elem*& tail, Elem*& qFront, Elem*& qBack);
void del_end(Elem*& actual, Elem*& head, Elem*& tail, Elem*& qFront, Elem*& qBack);
void del_act(Elem*& actual, Elem*& head, Elem*& tail);
void del_val(Elem*& actual, Elem*& head, Elem*& tail, int value);
int give_listSize(Elem*& head, Elem*& tail);

Elem* XOR(Elem* ad1, Elem* ad2);
Elem* XORForward(Elem*& prev, Elem* current);
Elem* XORBackward(Elem* current, Elem*& next);

int main()
{
	bool isEmpty = true;


	Elem* head = NULL;
	Elem* tail = NULL;
	Elem* actual = NULL;

	Elem* qfront = NULL;
	Elem* qback = NULL;

	char* answ = new char;
	int value = 0;
	while (scanf("%s", answ) != EOF)
	{
		if (strstr(answ, "ACTUAL") != NULL)
		{
			print_actual(actual);
		}
		else if (strstr(answ, "NEXT") != NULL)
		{
			next(actual, head);
		}
		else if (strstr(answ, "PREV") != NULL)
		{
			prev(actual, tail);
		}
		else if (strstr(answ, "ADD_BEG") != NULL)
		{
			scanf("%d", &value);
			add_beg(value, head, tail, actual);
		}
		else if (strstr(answ, "ADD_END") != NULL)
		{
			scanf("%d", &value);
			add_end(value, head, tail, actual);
		}
		else if (strstr(answ, "ADD_ACT") != NULL)
		{
			scanf("%d", &value);
			add_act(value, head, tail, actual);
		}
		else if (strstr(answ, "DEL_BEG") != NULL)
		{
			del_beg(actual, head, tail, qfront, qback);
		}
		else if (strstr(answ, "DEL_END") != NULL)
		{
			del_end(actual, head, tail, qfront, qback);
		}
		else if (strstr(answ, "DEL_VAL") != NULL)
		{
			scanf("%d", &value);
			del_val(actual, head, tail, value);
		}
		else if (strstr(answ, "DEL_ACT") != NULL)
		{
			del_act(actual, head, tail);
		}
		else if (strstr(answ, "PRINT_FORWARD") != NULL)
		{
			print_forward(head);
		}
		else if (strstr(answ, "PRINT_BACKWARD") != NULL)
		{
			print_backwards(tail);
		}
		else if (strstr(answ, "SIZE") != NULL)
		{
			printf("%d\n", give_listSize(head, tail));
		}
		else if (strstr(answ, "PUSH") != NULL)
		{
			scanf("%d", &value);
			push(value, qfront, qback, head, tail, actual, isEmpty);
		}
		else if (strstr(answ, "POP") != NULL)
		{
			pop(qfront, qback, head, tail, isEmpty);
		}
		else if (strstr(answ, "PRINT_QUEUE") != NULL)
		{
			printQueue(head, tail, qfront, qback, isEmpty);
		}
		else if (strstr(answ, "COUNT") != NULL)
		{
			printf("%d\n", count(head, tail, qfront, qback, isEmpty));
		}
		else if (strstr(answ, "GARBAGE_SOFT") != NULL)
		{
			garbage_soft(head, tail, qfront, qback, isEmpty);
		}
		else if (strstr(answ, "GARBAGE_HARD") != NULL)
		{
			garbage_hard(head, tail, qfront, qback, actual, isEmpty);
		}
	}

	delete answ;
	return 0;
}

int count(Elem* head, Elem* tail, Elem* qFront, Elem* qBack, bool& isEmpty)
{
	int number = 0;

	if (isEmpty) return 0;
	else if (qFront == qBack)
	{
		return 1;
	}
	else
	{
		Elem* temp = tail;
		Elem* next = NULL;

		while (temp != qFront)
		{
			temp = XORBackward(temp, next);
		}


		while (temp != qBack)
		{
			if (temp != head)
			{
				temp = XORBackward(temp, next);
			}
			else
			{
				temp = tail;
				next = NULL;
			}
			number++;
		}
		return ++number;
	}

}

void garbage_soft(Elem* head, Elem* tail, Elem* qFront, Elem* qBack, bool& isEmpty)
{
	if (count(head, tail, qFront, qBack, isEmpty) == give_listSize(head, tail)) return;

	Elem* temp = tail;
	Elem* next = NULL;
	if (qBack != NULL)
	{
		while (temp != qBack)
		{
			temp = XORBackward(temp, next);
		}

		while (temp != qFront)
		{
			if (temp != head)
			{
				temp = XORBackward(temp, next);
			}
			else
			{
				temp = tail;
				next = NULL;
			}
			if (temp == qFront) return;
			temp->value = 0;
		}
	}
	else
	{
		while (temp != NULL)
		{
			temp->value = 0;
			temp = XORBackward(temp, next);
		}
	}
}

void garbage_hard(Elem*& head, Elem*& tail, Elem* qFront, Elem* qBack, Elem*& actual, bool& isEmpty)
{
	if (count(head, tail, qFront, qBack, isEmpty) == give_listSize(head, tail)) return;

	Elem* temp = tail;
	Elem* next = NULL;

	if (qBack == NULL)
	{

		while (temp != NULL)
		{
			actual = temp;
			temp = XORBackward(temp, next);
			del_act(actual, head, tail);
		}

	}
	else
	{
		while (temp != qBack)
		{
			temp = XORBackward(temp, next);
		}
		temp = XORBackward(temp, next);

		while (temp != qFront)
		{
			actual = temp;
			if (temp != head)
			{
				Elem* helpPtr = next;
				temp = XORBackward(temp, next);

				del_act(actual, head, tail);
				next = helpPtr;

			}
			else
			{
				temp = tail;
				next = NULL;
			}
			if (temp == qFront) return;
		}
	}
}

void push(int value, Elem*& qfront, Elem*& qBack, Elem*& head, Elem*& tail, Elem*& actual, bool& isEmpty)
{
	Elem* temp = tail;
	Elem* next = NULL;


	if (head == NULL)
	{
		add_beg(value, head, tail, actual);
		qfront = head;
		qBack = head;
		isEmpty = false;
	}
	else
	{
		if (!isEmpty)
		{
			if (head != tail)
			{

				if (qBack != head)
				{
					while (temp != qBack)
					{
						temp = XORBackward(temp, next);
					}
					Elem* test = next;
					if (XORBackward(temp, test) == qfront)
					{
						actual = qBack;
						add_act(value, head, tail, actual);
						qBack = XORBackward(qBack, next);
						return;
					}
					qBack = XOR(next, temp->npx);
				}
				else
				{
					if (qfront != tail)
						qBack = tail;
					else
					{
						add_beg(value, head, tail, actual);
						qBack = head;
					}
				}
				qBack->value = value;
			}
			else
			{
				add_beg(value, head, tail, actual);
				qBack = head;
			}
		}
		else
		{
			if (qBack == NULL)
			{
				qBack = tail;
				qfront = tail;
			}
			isEmpty = false;
			qBack->value = value;
		}
	}
}

void pop(Elem*& qFront, Elem* qBack, Elem* head, Elem* tail, bool& isEmpty)
{
	Elem* temp = tail;
	Elem* next = NULL;

	if (qFront != qBack)
	{
		printf("%d\n", qFront->value);
		if (qFront != head)
		{
			while (temp != qFront)
			{
				temp = XORBackward(temp, next);
			}
			qFront = XOR(temp->npx, next);
		}
		else
		{
			qFront = tail;
		}

	}
	else if (isEmpty)
	{
		printf("NULL\n");
		return;
	}
	else
	{
		isEmpty = true;
		printf("%d\n", qFront->value);
	}
}

void printQueue(Elem* head, Elem* tail, Elem* qFront, Elem* qBack, bool& isEmpty)
{
	if (!isEmpty)
	{
		Elem* temp = tail;
		Elem* next = NULL;

		while (temp != qFront)
		{
			temp = XORBackward(temp, next);
		}

		while (temp != qBack)
		{
			printf("%d ", temp->value);

			if (temp != head)
			{
				temp = XORBackward(temp, next);
			}
			else
			{
				temp = tail;
				next = NULL;
			}
		}
		printf("%d ", temp->value);
		printf("\n");
	}
	else printf("NULL\n");
}

void add_beg(int value, Elem*& head, Elem*& tail, Elem*& actual)
{
	Elem* ptr = new Elem;
	ptr->value = value;
	ptr->npx = head;
	if (head == NULL)
	{
		tail = ptr;
		actual = ptr;
	}
	else
	{
		head->npx = XOR(ptr, head->npx);
	}
	head = ptr;
}

void add_end(int value, Elem*& head, Elem*& tail, Elem*& actual)
{
	Elem* ptr = new Elem;
	ptr->value = value;
	ptr->npx = tail;
	if (tail == NULL)
	{
		head = ptr;
		actual = ptr;
	}
	else
	{
		tail->npx = XOR(ptr, tail->npx);
	}
	tail = ptr;
}

void add_act(int value, Elem*& head, Elem*& tail, Elem*& actual)
{
	Elem* newElem = new Elem;
	newElem->value = value;
	if (actual == head && head != NULL)
	{
		newElem->npx = head;
		head = newElem;
		actual->npx = XOR(newElem, actual->npx);

	}
	else if (actual == NULL)
	{
		add_beg(value, head, tail, actual);
		delete newElem;
	}
	else
	{
		Elem* temp = head;
		Elem* prev = NULL;

		while (temp != actual)
		{
			temp = XORForward(prev, temp);
		}
		Elem* next = XOR(temp->npx, prev);

		newElem->npx = XOR(prev, temp);
		prev->npx = XOR(newElem, XOR(prev->npx, actual));
		actual->npx = XOR(newElem, next);
	}

}

void del_beg(Elem*& actual, Elem*& head, Elem*& tail, Elem*& qFront, Elem*& qBack)
{
	if (head == NULL)
		return;
	else if (head == tail)
	{
		actual = NULL;
		delete head;
		head = NULL;
		tail = NULL;
		qFront = NULL;
		qBack = NULL;
	}
	else
	{

		Elem* temp = head;
		head = head->npx;
		head->npx = XOR(temp, head->npx);
		if (actual == temp)
			actual = head;
		if (qFront == temp)
			qFront = tail;
		if (qBack == temp)
			qBack = head;

		delete temp;
	}
}

void del_end(Elem*& actual, Elem*& head, Elem*& tail, Elem*& qFront, Elem*& qBack)
{
	if (tail == NULL)
		return;
	else if (head == tail)
	{
		actual = NULL;
		delete head;
		head = NULL;
		tail = NULL;
		qBack = NULL;
		qFront = NULL;
	}
	else
	{
		Elem* temp = tail;
		tail = tail->npx;
		tail->npx = XOR(temp, tail->npx);
		if (actual == temp)
			actual = tail;
		if (qBack == temp)
			qBack = head;
		if (qFront == temp)
			qFront = tail;



		delete temp;
	}
}

void del_act(Elem*& actual, Elem*& head, Elem*& tail)
{
	if (actual == NULL)
		return;
	else if (actual == head && actual == tail)
	{
		head = NULL;
		tail = NULL;
		//delete actual;
		actual = NULL;
	}
	else if (actual == head)
	{
		actual = tail;
		Elem* temp = head;
		head = head->npx;
		head->npx = XOR(temp, head->npx);

		delete temp;
	}
	else if (actual == tail)
	{
		Elem* temp = tail;
		actual = actual->npx;
		tail = actual;
		tail->npx = XOR(temp, tail->npx);
		delete temp;
	}
	else
	{

		Elem* temp = tail;
		Elem* next = NULL;

		while (temp != actual)
		{
			temp = XORBackward(temp, next);
		}

		Elem* prev = XOR(temp->npx, next);

		next->npx = XOR(prev, XOR(temp, next->npx));
		prev->npx = XOR(next, XOR(temp, prev->npx));

		actual = XOR(temp->npx, next);

		delete temp;

	}
}

void print_forward(Elem* head)
{
	if (head == NULL)
	{
		printf("NULL\n");
		return;
	}

	Elem* temp = head;
	Elem* prev = NULL;

	while (temp != NULL)
	{
		printf("%d ", temp->value);
		temp = XORForward(prev, temp);
	}
	printf("\n");
}

void print_backwards(Elem* tail)
{
	if (tail == NULL)
	{
		printf("NULL\n");
		return;
	}

	Elem* temp = tail;
	Elem* next = NULL;
	while (temp != NULL)
	{
		printf("%d ", temp->value);
		temp = XORBackward(temp, next);
	}
	printf("\n");
}

void print_actual(Elem* actual)
{
	if (actual != NULL)
		printf("%d ", actual->value);
	else printf("NULL");

	printf("\n");
}

void next(Elem*& actual, Elem* head)
{
	if (actual == NULL)
	{
		printf("NULL\n");
		return;
	}
	Elem* temp = head;
	Elem* prev = NULL;

	while (temp != actual)
	{
		temp = XORForward(prev, temp);
	}
	temp = XORForward(prev, temp);
	if (temp == NULL)
		temp = head;
	actual = temp;
	printf("%d\n", temp->value);
}

void prev(Elem*& actual, Elem* tail)
{
	if (actual == NULL)
	{
		printf("NULL\n");
		return;
	}
	Elem* temp = tail;
	Elem* next = NULL;
	while (temp != actual)
	{
		temp = XORBackward(temp, next);
	}
	temp = XORBackward(temp, next);
	if (temp == NULL)
		temp = tail;
	actual = temp;
	printf("%d\n", temp->value);
}

void del_val(Elem*& actual, Elem*& head, Elem*& tail, int value)
{
	Elem* temp = head;
	Elem* prev = NULL;


	if (head == NULL) return;

	while (temp->value != value)
	{
		temp = XORForward(prev, temp);
		if (temp == NULL) return;

	}

	Elem* next = XOR(temp->npx, prev);


	if (temp == head && temp == tail)
	{
		head = NULL;
		tail = NULL;

	}
	else if (temp == head)
	{
		head = head->npx;
		head->npx = XOR(temp, head->npx);
	}
	else if (temp == tail)
	{
		tail = tail->npx;
		tail->npx = XOR(temp, tail->npx);

	}
	else
	{
		next->npx = XOR(prev, XOR(temp, next->npx));
		prev->npx = XOR(next, XOR(temp, prev->npx));
	}
	if (temp == actual)
	{
		if (actual == head)
		{
			actual = tail;
		}
		else if (actual == head && actual == tail)
		{
			actual = NULL;
			head = NULL;
			tail = NULL;
		}
		else actual = XOR(temp->npx, next);
	}

	delete temp;

	del_val(actual, head, tail, value);
}

int give_listSize(Elem*& head, Elem*& tail)
{
	int size = 0;
	Elem* temp = head;
	Elem* prev = NULL;
	while (temp != tail)
	{
		temp = XORForward(prev, temp);
		size++;
	}

	return ++size;
}

Elem* XOR(Elem* ad1, Elem* ad2)
{
	return (Elem*)((uintptr_t)ad1 ^ (uintptr_t)ad2);
}

Elem* XORForward(Elem*& prev, Elem* current)
{
	Elem* temp = XOR(prev, current->npx);
	prev = current;
	return temp;
}

Elem* XORBackward(Elem* current, Elem*& next)
{
	Elem* temp = XOR(current->npx, next);
	next = current;
	return temp;
}
