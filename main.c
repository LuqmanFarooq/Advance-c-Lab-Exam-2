#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node {
	int employeeId;
	char firstName[20];
	char secondName[20];
	char department[30];
	float monthlySalary;

	struct node* NEXT;
};
void AddEmployeeAtStart(struct node** top);
void AddEmployeeAtEnd(struct node* top);
void SavingToFile(struct node* top);
void DisplayList(struct node* top, char dept[30]);
void MonthlyPaySlip(struct node* top, int id);
void main()
{
	struct node* headPtr = NULL;
	int choice;
	int chkId;
	char dept[30];
	//file variavble
	FILE* out;

	// menu choices
	printf("Please enter 1 to add a employee at the end of the list\n2 to display the employees and monthly wages bill for a department\n3 to generate a payslip for a given employee");
	scanf("%d", &choice);

	while (choice != -1)
	{
		if (choice == 1)
		{
			if (headPtr == NULL)
				AddEmployeeAtStart(&headPtr);
			else
			{
				AddEmployeeAtEnd(headPtr);
			}//else
		}
		else if (choice == 2)
		{
			printf("Please enter the department you wish to search for\n");
			scanf("%s", &dept);
			DisplayList(headPtr,dept);
		}
		else if (choice == 3)
		{
			printf("Please enter the employee id the payslip is for\n");
				scanf("%d", &chkId);
				MonthlyPaySlip(headPtr, chkId);
		}
		printf("Please enter 1 to add a employee at the end of the list\n2 to display the employees and monthly wages bill for a department\n3 to generate a payslip for a given employee");
		scanf("%d", &choice);
		}// while choice
	SavingToFile(headPtr);
	

	


}// main function
// adding employee at start 
	void AddEmployeeAtStart(struct node** top)
	{
		struct node* newNode;
		int id;

		printf("Please enter the ID of the new employee\n");
		scanf("%d", &id);

		if (searchList(*top, id) == 1)
		{
			printf("Sorry the ID already exists\n");
			return;
		}

		newNode = (struct node*)malloc(sizeof(struct node));

		printf("Please enter employee name\n");
		scanf("%s", newNode->firstName);
		printf("Please enter employee surname\n");
		scanf("%s", newNode->secondName);
		newNode->employeeId= id;
		printf("Please enter employee department\n");
		scanf("%s", newNode->department);
		printf("Please enter employee monthly wage\n");
		scanf("%f", &newNode->monthlySalary);

		newNode->NEXT = *top;
		*top = newNode;
	}// add at start

	int searchList(struct node* top, int searchID)
	{
		int found = 0;
		struct node* temp = top;

		while (temp != NULL)
		{
			if (temp->employeeId == searchID)
			{
				found = 1;
				return found;
			}

			temp = temp->NEXT;
		}

		return found;
	}// search list
	// adding employee at end
	void AddEmployeeAtEnd(struct node* top)
	{
		struct node* temp = top;
		struct node* newNode;
		int id;

		printf("Please enter the ID of the new employee\n");
		scanf("%d", &id);

		if (searchList(top, id) == 1)
		{
			printf("Sorry the ID already exists\n");
			return;
		}

		while (temp->NEXT != NULL)
		{
			temp = temp->NEXT;
		}

		newNode = (struct node*)malloc(sizeof(struct node));

		printf("Please enter employee name\n");
		scanf("%s", newNode->firstName);
		printf("Please enter employee surname\n");
		scanf("%s", newNode->secondName);
		newNode->employeeId = id;
		printf("Please enter employee department\n");
		scanf("%s", newNode->department);
		printf("Please enter employee monthly wage\n");
		scanf("%f", &newNode->monthlySalary);

		newNode->NEXT = NULL;
		temp->NEXT = newNode;
	}// adding employee at end

	// saving to file
	void SavingToFile(struct node* top)
	{
		FILE* out;
		// opening file in append mode
		out = fopen("Employee.txt", "a");
		struct node* temp = top;
		while (temp != NULL)
		{
			fprintf(out,"%d %s %s %s %.0f\n", temp->employeeId, temp->firstName, temp->secondName, temp->department, temp->monthlySalary);
			temp = temp->NEXT;
		}
		if (out != NULL)
		{
			fclose(out);
		}
	}
	// display employee details matching the department entered by user
	void DisplayList(struct node* top,char dept[30])
	{
		struct node* temp = top;
		float total=0;
		while (temp != NULL)
		{
			if (strcmp(temp->department, dept) == 0)
			{
				printf("%d %s %s %s %.0f\n", temp->employeeId, temp->firstName, temp->secondName, temp->department, temp->monthlySalary);
				//calculation department total
				total = temp->monthlySalary + total;
			}
			temp = temp->NEXT;
		}
		printf("The total spend for sales is:%.0f\n", total);
	}
	// monthly pay slip calculations
	void MonthlyPaySlip(struct node* top, int id)
	{
		struct node* temp = top;
		float paye;
		float usc;
		float netPay;
		while (temp != NULL)
		{
			if (temp->employeeId == id)
			{
				printf("Employee %d %s %s\n",temp->employeeId,temp->firstName,temp->secondName);
				printf("Gross Pay: %f\n", temp->monthlySalary);
				if (temp->monthlySalary <= 1000)
				{
					paye = 0;
				}
				// calculation paye by multiplying 0.2 converted from 20%
				else if (temp->monthlySalary > 1000 && temp->monthlySalary <= 2000)
				{
					
					paye = temp->monthlySalary*0.2;
				}
				// calculation paye by multiplying 0.4 converted from 40%
				else if(temp->monthlySalary>2000)
				{
					paye = temp->monthlySalary*0.4;
				}
				printf("Paye:%f\n", paye);
				// prsi calculation @5%
				usc = temp->monthlySalary*0.05;
				// usc cannot excede 200
				if (usc > 200)
				{
					usc = 200;
				}
				printf("PRSI:%f\n", usc);
				// calculating nett pay
				netPay = ((temp->monthlySalary) - paye - usc);
				printf("Nett Pay:%f\n", netPay);
			}
			temp = temp->NEXT;
		}
	}