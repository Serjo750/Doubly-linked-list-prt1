#pragma warning(disable:4996)
#include "Dllist.h"
#include<string.h>


// initialization of root
 node* initialize(char *data) {
	node* head;

	head = (node*)malloc(sizeof(node));

	head->data = (char*)malloc(strlen(data) * sizeof(char));

	strcpy(head->data, data);
	head->next = NULL;           
	head->prev = NULL;
	

	return head;
}

//Adding new elem

 node* ADD(node* lst, char *number)
{
	node* temp, * p;
	temp = (struct node*)malloc(sizeof(node));

	temp->data = (char*)malloc(strlen(number) * sizeof(char));
	p = lst->next; // ���������� ��������� �� ��������� ����
	lst->next = temp; // ���������� ���� ��������� �� �����������
	strcpy(temp->data, number);// ���������� ���� ������ ������������ ����
	temp->next = p; // ��������� ���� ��������� �� ��������� ����
	temp->prev = lst; // ��������� ���� ��������� �� ���������� ����
	if (p != NULL)
		p->prev = temp;
	return(temp);
}

node* DEL(node* current) {
	node* next, * prev;

	prev = current->prev;
	next = current->next;

	if (prev != NULL)prev->next = current->next;
	if (next != NULL)next->prev = current->prev;

	delete[] current->data;
	free(current);

	return prev;
}

//deleting of the root
node* DELROOT(node* head)
{
	node* next_after_head;

	next_after_head = head->next;
	next_after_head->prev = NULL;

	delete[] head->data;
	free(head);

	return next_after_head;
}

unsigned COUNT_ELEMENT( node* head) 
{
	int COUNTER = 1;

	node* temp = head;

	while (temp!= NULL) {
		if (temp != NULL)
		{
			COUNTER++;
			temp = temp->next;
		}
	}
	return COUNTER;
}

void TRAVERSAL_FORWARD(node* head)  
{
	node* element = head;
	if(element != NULL)
	{
		while (element!= NULL)
		{
			printf(element->data);

			element = element->next;
		}
	}
}
void TRAVERSAL_BACKWARD(node* tail)
{
	node* element = tail;
	if (element != NULL)
	{
		while (element= NULL)
		{
			printf(element->data);

			element = element->prev;
		}
	}
}

node* FIND(char* elem_data, node* head)
{
	node* element = head;
	if (element != NULL)
	{
		while (element != NULL)
		{
			
			if (element->data == elem_data)
				return element;

			element = element->next;
		}
		return NULL;
	}
}

void EXTRACTION(char* del_elem_data,node* head)
{
	if (FIND(del_elem_data, head)->prev == NULL)DELROOT(head);
	else {
		DEL(FIND(del_elem_data, head));
	}
		printf("Deleted %s completly", del_elem_data);
}

void REMOVING_DUPLICATE(node* head)
{
	node* lhv = head;
	
	if (lhv->next != NULL)
	{
		node* rhv = lhv->next;

		while (lhv != NULL)
		{

			while (rhv != NULL)
			{

				if (lhv->data == rhv->data)//������� �������� ���������
				{
					DEL(rhv);
				}
				rhv = rhv->next;

			}

			lhv = lhv->next;
		}
	}

}

//swap with pointers and data

/*void SWAP(node* lhv, node* rhv)
{
	lhv->prev->next = rhv;
	rhv->next->prev = lhv;

	node* temp = rhv;

	rhv = lhv;
	rhv->next = lhv;

	lhv = temp;
	lhv->prev = rhv;
}
*/

void SWAP(node* lhv, node* rhv)
{
	char *tmp = lhv->data;

	lhv->data = rhv->data;

	rhv->data = tmp;
}
  
node* GETTAIL(node* head)
{
	node* temp = head;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return temp;

}

void BUBBLE_SORT(node* head) {

	int counter = COUNT_ELEMENT(head);

	if (counter >= 2)
	{
		node* tmp = head;

		for (size_t i = 0; i < counter; i++)
		{


			for (size_t i = 0; i < counter - 1; i++)
			{
				if (tmp->data > tmp->next->data)
				{
					SWAP(FIND(tmp->data, head), FIND(tmp->next->data, head));
				}
				tmp = tmp->next;
			}
		}
	}
}

node* READING_FROM_FILE(node* head, char* file_name)
{
	FILE* file_r;

	int Is_node_already_exist = 1;

	printf("Is head already exist: 1 - yes, 0 - no \n");

	scanf("%d", &Is_node_already_exist);

	char seps[] = " ,";
	
	char* token = NULL;

	char buffer[1024];

	node* head_in = nullptr;
	
	node* last = nullptr;
	//������� ������� : ����� - ��������� ������ *(������ ��������� �� ����) , ������� ����� ���������� � ������ 
	if (Is_node_already_exist == 1)
	{
		last = GETTAIL(head);
	}

	file_r = fopen( file_name, "r");

	if (file_r != NULL)
	{
		printf("File was opened successfully!");

		char* splited_str = strtok_s(buffer, seps, &token);

		while (fgets(buffer, 1024, file_r) != NULL)
		{
			while (splited_str != NULL)
			{
				if (!Is_node_already_exist)
				{
					head_in = initialize(splited_str);

					last = head_in;
				}
				else {
					last = ADD(last, splited_str);
				}
				if(token != NULL)
					splited_str = strtok_s(NULL, seps, &token);	
			}
		}
		fclose(file_r);
	}
	return head_in;
}

void WRITING_TO_FILE(node* container_head, char* file_name) {

	FILE* F1;

	F1 = fopen(file_name, "w");

	node* tmp = container_head;

	if (F1 != NULL)
	{
		printf("File was opened successfully!");

		while (tmp != NULL)
		{
			fputs(tmp->data, F1);

			tmp = tmp->next;
		}
		fclose(F1);

	}
	else {
		printf("File wasn't opened correctly!");
	}
}
