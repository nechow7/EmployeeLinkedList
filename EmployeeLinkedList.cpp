// nc2418_hwk10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// The program reads in the first file: ID, PayRate and Name 
// The program reads in the second file: ID, hoursworked	

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Function to open file in use in main 
void openFile(ifstream& inFile) {
	string file;
	cout << "Please enter file name: \n";
	cin >> file;
	inFile.open(file);
	while (!inFile)
	{
		cout << "File failed to open!\n";
		cout << "Please enter file name: \n";
		cin >> file;
		inFile.clear();
		inFile.open(file);
	}
}

// mergeSort functions used in the end of main 
void merge(double arr[], int lowleft, int highleft, int highright);
void mergeSort(double arr[], int low, int high);

template <class T>
class ListNode;

template <class T>
class List {
private:
	ListNode<T>* head;
	ListNode<T>* recursiveCopy(ListNode<T>* rhs);
public:
	List() : head(nullptr) {}
	List(const List& rhs) : head(nullptr) { *this = rhs; }
	List<T>& operator=(const List<T>& rhs);
	~List() { clear(); }
	void insertAtHead(T newdata);
	T data(ListNode<T>* ptr);
	void swapdata(ListNode<T>* ptr, T newdata);
	ListNode<T>* next(ListNode<T>* ptr);
	void RemoveFromHead();
	ListNode<T>* FindHead();
	void display();
	bool empty() const { return head == nullptr; }
	void clear();
	void insertAtEnd(T newdata);
	int size() const;
};

template <class T>
class ListNode
{
private:
	T data;
	ListNode<T>* next;
public:
	ListNode() {}
	ListNode(T newdata = T(), ListNode<T>* newnext = nullptr) : data(newdata), next(newnext) {}
	friend class List<T>;
};

// Member functions of List
template <class T>
ListNode<T>* List<T>::recursiveCopy(ListNode<T>* rhs) {
	if (rhs == nullptr)
	{
		return nullptr;
	}
	return new ListNode<T>(rhs->data, recursiveCopy(rhs->next));
}

template <class T>
List<T>& List<T>::operator=(const List<T>& rhs) {

}

template <class T>
ListNode<T>* List<T>::FindHead() {
	return head;
}

template <class T>
T List<T>::data(ListNode<T>* ptr) {
	return ptr->data;
}

template <class T>
void List<T>::swapdata(ListNode<T>* ptr,T newdata) {
	ptr->data = newdata;
}

template <class T>
ListNode<T>* List<T>::next(ListNode<T>* ptr) {
	return ptr->next;
}

template <class T>
void List<T>::RemoveFromHead() {
	ListNode<T> * temp;
	temp = head;
	head = head->next;
	delete temp;
}

template <class T>
void List<T>::display() {
	ListNode<T>* temp;
	temp = head;
	while (temp != NULL)
	{
		cout << temp->data << "\t";
		temp = temp->next;
	}
}

template <class T>
void List<T>::insertAtHead(T newdata) {
	ListNode<T>* temp = new ListNode<T>(newdata);
	temp->next = head;
	head = temp;
}

template <class T>
void List<T>::insertAtEnd(T newdata) {
	if (empty())
	{
		insertAtHead(newdata);
		return;
	}
	ListNode<T>* temp = new ListNode<T>(newdata);
	ListNode<T>* end = head;
	while (end->next != nullptr)
	{
		end = end->next;
	}
	end->next = temp;
}

template <class T>
void List<T>::clear() {
	while (head->next != nullptr)
	{
		ListNode<T>* temp;
		temp = head;
		head = head->next;
		delete temp;
	}
	ListNode<T>* temp;
	temp = head;
	head = nullptr;
	delete temp;
}

template <class T>
int List<T>::size() const {
	int count = 0;
	ListNode<T>* temp;
	temp = head;
	while (temp != nullptr)
	{
		count += 1;
		temp = temp->next;
	}
	return count;
}

// Employee Class
class Employee
{
private:
	int ID;
	double PayRate;
	string Name;
	double TotalPay;
public:
	Employee() {}
	Employee(int ID2, double PayRate2, string Name2,double amount);
	void Display();
	friend ostream& operator<<(ostream& outs, Employee& employ);
	int returnID();
	double returnPay();
	string returnName();
	double returnTotalPay();
	void ChangeID(int num);
	void ChangePayRate(double num);
	void ChangeName(string newName);
	void ChangeTPay(double num);
};

Employee::Employee(int ID2, double PayRate2, string Name2,double amount) {
	ID = ID2;
	PayRate = PayRate2;
	Name = Name2;
	TotalPay = amount;
}

// Member functions of Employee
void Employee::Display() {
	cout << ID << " " << PayRate << " " << Name << " " << TotalPay;
}

int Employee::returnID() {
	return ID;
}

double Employee::returnPay() {
	return PayRate;
}

double Employee::returnTotalPay() {
	return TotalPay;
}

string Employee::returnName() {
	return Name;
}

void Employee::ChangeID(int num) {
	ID = num;
}

void Employee::ChangePayRate(double num) {
	PayRate = num;
}

void Employee::ChangeName(string newName) {
	Name = newName;
}

void Employee::ChangeTPay(double num) {
	TotalPay = num;
}

ostream& operator<<(ostream& outs, Employee& employ) {
	outs << employ.ID << " " << employ.PayRate << " " << employ.Name << " " << employ.TotalPay;
	return outs;
}

// struct to hold data in File 2
struct hours {
	int ID;
	int HoursWork;
};

int main()
{
	// Read in first file and inserts data into linkedlist 
	ifstream inFile;
	ofstream outfile;
	openFile(inFile);
	List<Employee> StaffList;
	Employee Staff;
	int ID;
	while (inFile >> ID)
	{
		Staff.ChangeID(ID);
		double PR;
		inFile >> PR;
		Staff.ChangePayRate(PR);
		inFile.ignore(9999, '\t');
		string name2;
		getline(inFile, name2);
		Staff.ChangeName(name2);
		Staff.ChangeTPay(0);
		StaffList.insertAtEnd(Staff);
	}

	// Reads in second file and stores data in vector Pay
	ifstream inFile2;
	openFile(inFile2);
	vector<hours> Pay;
	hours temp;

	while (inFile2 >> temp.ID)
	{
		inFile2 >> temp.HoursWork;
		Pay.push_back(temp);
	}

	// Goes through the LinkedList and the vector to see which ID's match,
	// if there is a match, the total pay in Employee is multiplied by 
	// hours worked in the vector pay by the hour rate in the Employee 
	ListNode<Employee>* ptr;
	ListNode<Employee>* i;
	ptr = StaffList.FindHead();
	
	Employee N;
	int x;
	double sum;
	for (i = ptr; i != nullptr; i = StaffList.next(i))
	{
		N = StaffList.data(i);
		x = 0;
		sum = 0;
		while (x < Pay.size())
		{
			if (Pay[x].ID == N.returnID())
			{
				sum = (Pay[x].HoursWork)*(N.returnPay());
				sum = N.returnTotalPay() + sum;
				N.ChangeTPay(sum);
				StaffList.swapdata(i, N);
			}
			x += 1;
		}
	}
	
	// creates an array, and puts all of the Totalpay values in it
	ptr = StaffList.FindHead();
	int sizeArr = StaffList.size();
	double* arr = new double[sizeArr];
	int y = 0;
	for (i = ptr; i != nullptr; i = StaffList.next(i))
	{
		N = StaffList.data(i);
		arr[y] = N.returnTotalPay();
		y += 1;
	}

	// Sorts the Arr of TotalPay 
	mergeSort(arr, 0, sizeArr-1);
	
	// Goes through the linked list to find the employee that has a matching 
	//TotalPay to the one in the Arr and prints the name and TotalPay
	ptr =StaffList.FindHead();
	x = sizeArr - 1;
	cout << "*******Payroll Information*******" << endl;
	while (x >= 0)
	{
		for (i = ptr; i != nullptr; i = StaffList.next(i))
		{
			N = StaffList.data(i);
			if (arr[x] == N.returnTotalPay())
			{
				cout << "\t"<<N.returnName() << ", $" << N.returnTotalPay() << endl;
			}
		}
		x -= 1;
	}
	cout << "*********End Payroll*************";

	delete arr;
	return 0;
}

void mergeSort(double arr[], int low, int high) {
	int midInd;

	if (low == high)
	{
		return;
	}
	else
	{ 
		midInd = (low + high) / 2;
		mergeSort(arr, low, midInd);
		mergeSort(arr, midInd + 1, high);
		merge(arr, low, midInd, high);
	}
}
	
void merge(double arr[], int lowleft, int highleft, int highright) {
	int lowRight, size;
	double* mergedArr;
	int iRight, iLeft, iRes;

	lowRight = highleft + 1;
	size = highright - lowleft + 1;
	mergedArr = new double[size];

	iLeft = lowleft;
	iRight = lowRight;
	iRes = 0;

	while (iLeft <= highleft && iRight <= highright)
	{
		if (arr[iLeft] < arr[iRight])
		{
			mergedArr[iRes] = arr[iLeft];
			iLeft += 1;
			iRes += 1;
		}
		else
		{
			mergedArr[iRes] = arr[iRight];
			iRight += 1;
			iRes += 1;
		}
	}
	while(iLeft <= highleft)
		{
		mergedArr[iRes] = arr[iLeft];
		iLeft += 1;
		iRes += 1;
		}
	while (iRight <= highright)
	{
		mergedArr[iRes] = arr[iRight];
		iRight += 1;
		iRes += 1;
	}

	int i,iArr;
	for (i = 0, iArr = lowleft; i < size; i++,iArr++)
	{
		arr[iArr] = mergedArr[i];
	}

	delete mergedArr;
}
	