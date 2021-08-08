#include <stdio.h>
#pragma warning(disable : 4996)

#define MAX_ELEMENT 20

typedef struct {
	int key;
	int number;
} element;

element heap[MAX_ELEMENT];

int n = 0;
int waiting_number = 9;

void push(element item);
element pop(int size);

int main()
{
	int type;
	int people_number;
	int table_size;

	element temp;

	printf("Start of Program\n");
	printf("기능:\n");
	printf("0.종료 1.대기접수 2.식탁배정\n");
	printf("식탁 대기수: %d\n", n);

	while (1)
	{
		printf("-------------\n");

		printf("기능 선택?: ");
		scanf("%d", &type);
		getchar();

		if (type == 0)
			break;

		else if (type == 1)
		{
			printf("대기번호: %d\n", waiting_number);

			printf("인원수?: ");
			scanf("%d", &people_number);
			getchar();

			temp.key = waiting_number;
			waiting_number = waiting_number - 1;

			temp.number = people_number;

			push(temp);
		}

		else if (type == 2)
		{
			printf("식탁 크기?: ");
			scanf("%d", &table_size);
			getchar();

			temp = pop(table_size);

			if (temp.key == 0)
			{
				printf("배정불가::\n");
			}

			else
			{
				printf("배정:: 대기번호: %d 인원수: %d\n", temp.key, temp.number);
			}
		}

		printf("식탁 대기 수: %d\n", n);
	}

	printf("End of Program\n");

	return 0;
}

void push(element item) 
{
	int i = ++n;

	while ((i != 1) && (item.key > heap[i / 2].key))
	{
		heap[i] = heap[i / 2];
		i = i / 2;
	}

	heap[i] = item;
}

element pop(int size) 
{
	int parent, child;

	element item, temp;
	element queue[MAX_ELEMENT];

	int i = 1;
	int front = 1;
	int rear = 1;

	if (n == 0) 
	{
		item.key = 0;

		return item;
	}

	while (1) 
	{
		if (i > n) 
		{
			item.key = 0;

			return item;
		}

		if (heap[i].number <= size) 
		{
			item = heap[i];

			break;
		}

		else 
		{
			queue[rear++] = heap[i];

			i = i + 1;
		}
	}

	temp = heap[n--];

	parent = 1;
	child = 2;

	while (child < n) 
	{
		if (heap[child].key < heap[child + 1].key) 
			child++;

		if (temp.key >= heap[child].key) 
			break;

		heap[parent] = heap[child];
		child = child * 2;
	}

	heap[parent] = temp;

	while (front != rear) 
	{
		push(queue[front++]);

		n = n - 1;
	}

	return item;
}

