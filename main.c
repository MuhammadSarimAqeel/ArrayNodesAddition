#include <stdio.h>
#include <stdlib.h>

// A Linked List Node
struct Node
{
	int data;
	struct Node* next;
};

// Helper function to create a new node with the given data
struct Node* newNode(int data)
{
	// create a new linked list node from the heap
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->data = data;
	node->next = NULL;

	return node;
}

// Helper function to create a new node with the given data and
// pushes it onto the list's front
void push(struct Node**headRef, int data)
{
	// create a new linked list node from the heap
	struct Node* node = newNode(data);
	node->next = *headRef;
	*headRef = node;
}

// Helper function to print a given linked list
void printList(struct Node* head)
{
	struct Node* ptr = head;
	while (ptr)
	{
		printf("%d  ", ptr->data);
		ptr = ptr->next;
	}

//	printf("null\n");
}

// Iterate through the list and move/insert each node
// in front of the out list like `push()` of the node
void reverse(struct Node** headRef)
{
	struct Node* out = NULL;
	struct Node* current = *headRef;

	// traverse the list
	while (current)
	{
		// tricky: note the next node
		struct Node* next = current->next;

		// move the current node onto the out
		current->next = out;
		out = current;

		// process next node
		current = next;
	}

	// fix head pointer
	*headRef = out;
}

// Function to add two lists, `X` and `Y`
void add(struct Node* X, struct Node* Y, struct Node **head)
{
	// stores the last seen node
	struct Node* prevNode = NULL;

	// initialize carry with 0
	int carry = 0;

	// run till both lists are empty
	while (X || Y)
	{
		// sum is X's data + Y's data + carry (if any)
		int sum = 0;
		if (X) {
			sum += X->data;
		}
		if (Y) {
			sum += Y->data;
		}
		sum += carry;

		// if the sum of a 2–digit number, reduce it and update carry
		carry = sum / 10;
		sum = sum % 10;

		// create a new node with the calculated sum
		struct Node* node = newNode(sum);

		// if the output list is empty
		if (*head == NULL)
		{
			// update `prev` and `head` pointers to point to the new node
			prevNode = node;
			*head = node;
		}
		else {
			// add the new node to the output list
			prevNode->next = node;

			// update the previous node to point to the new node
			prevNode = node;
		}

		// advance `X` and `Y` for the next iteration of the loop
		if (X) {
			X = X->next;
		}

		if (Y) {
			Y = Y->next;
		}
	}

	if (carry != 0) {
		push(&(prevNode->next), carry);
	}
}

// Function to add two lists, `X` and `Y`
struct Node* addLists(struct Node* X, struct Node* Y)
{
	struct Node* out = NULL;

	// reverse `X` and `Y` to access elements from the end
	reverse(&X);
	reverse(&Y);

	add(X, Y, &out);
	reverse(&out);

	// optional: call reverse again on `X` and `Y`

	return out;
}

int main(void)
{
    int num ,num2;

    printf("Enter 1st Number : ");
    scanf("%d", &num);


	printf("Enter 2nd Number : ");
    scanf("%d", &num2);


	// construct list `X` (5 —> 7 —> 3 —> 4) from number `x`
	struct Node* X = NULL;
	while (num)
	{
		push(&X, num % 10);
		num = num/10;
	}

	// construct list `Y` (9 —> 4 —> 6) from number `y`
	struct Node* Y = NULL;
	while (num2)
	{
		push(&Y, num2 % 10);
		num2 = num2/10;
	}
printf("The Addition of the nodes of 1st and 2nd number`s linked list is ");
	printList(addLists(X, Y));

	return 0;
}
