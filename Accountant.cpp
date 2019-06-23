#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#include <vector>
using namespace std;

class CalendarType
{
private:
	int date, month, year, months[12];
public:
	CalendarType()
	{
		date = 1;
		month = 1;
		year = 1900;
		months[0] = months[2] = months[4] = months[6] = months[7] = months[9] = months[11] = 31;
		months[3] = months[5] = months[8] = months[10] = 30;
		months[1] = 28;
	}

	CalendarType(CalendarType &c)
	{
		months[0] = months[2] = months[4] = months[6] = months[7] = months[9] = months[11] = 31;
		months[3] = months[5] = months[8] = months[10] = 30;
		months[1] = 28;
		date = c.date;
		month = c.month;
		year = c.year;
	}

	int endOfMonth(int i)
	{
		if (0 < i || i < 13)
			return months[i - 1];
		else return 0;
	}

	int getDate()
	{
		return date;
	}

	int getMonth()
	{
		return month;
	}

	int getYear()
	{
		return year;
	}

	bool isLeapYear(int y)
	{
		if (y % 4 == 0)
		{
			if (y % 100 == 0)
			{
				if (y % 400 == 0)
					return true;
				else
					return false;
			}
			else
				return true;
		}
		else
			return false;
	}

	bool verify(int x, int y, int z)
	{
		if (z < 1900)
			return false;

		if (y > 12 || y < 1)
			return false;

		if (x < 1 || x > 31)
			return false;

		if (!isLeapYear(z) && x > months[y - 1])
			return false;

		if (isLeapYear(z))
		{
			if (y == 2 && x > 29)
				return false;
			if (y != 2 && x > months[y - 1])
				return false;
		}

		date = x;
		month = y;
		year = z;

		return true;
	}

	void print()
	{
		cout << date << ' ';
		if (month == 1)
			cout << "January";
		else if (month == 2)
			cout << "February";
		else if (month == 3)
			cout << "March";
		else if (month == 4)
			cout << "April";
		else if (month == 5)
			cout << "May";
		else if (month == 6)
			cout << "June";
		else if (month == 7)
			cout << "July";
		else if (month == 8)
			cout << "August";
		else if (month == 9)
			cout << "September";
		else if (month == 10)
			cout << "October";
		else if (month == 11)
			cout << "November";
		else if (month == 12)
			cout << "December";
		cout << ", " << year;
	}
};

struct statement
{
	string account;
	int amount;
	bool visited = false;
};

struct node
{
	CalendarType *cal;
	statement debit;
	statement credit;
	string description;
	node *next;
};

struct node1
{
	string name;
	int amount;
	bool type;
	int discount;
	node1 *next;
};

struct node2
{
	int date = 0, month = 0, year = 0, amount = 0;
	string account = "";
	string from = "";
	void insert(int a, int b, int c, int d, string e, string f)
	{
		date = a;
		month = b;
		year = c;
		amount = d;
		account = e;
		from = f;
	}
};

class NodeList
{
private:
	node1 *head;
	node1 *temp;
public:
	NodeList()
	{
		head = temp = NULL;
	}

	bool insert(string x, bool y, int z, int d)
	{
		if (head == NULL)
		{
			head = new node1;
			head->next = NULL;
			temp = head;
		}
		else
		{
			if (head->name == x)
				return false;
			temp = head;
			while (temp->next != NULL)
			{
				if (temp->name == x)
					return false;
				temp = temp->next;
				if (temp->name == x)
					return false;
			}
			temp->next = new node1;
			temp = temp->next;
		}
		temp->name = x;
		temp->type = y;
		temp->amount = z;
		temp->discount = d;
		temp->next = NULL;
		return true;
	}

	node1* findAndReturn(string x)
	{
		temp = head;
		if (head == NULL)
			return NULL;
		if (head->name == x)
			return head;
		while (temp != NULL)
		{
			if (temp->name == x)
				return temp;
			temp = temp->next;
		}
		return NULL;
	}

	bool remove(string x, node1 *temp)
	{
		if (temp == NULL)
			temp = head;
		if (head->name == x)
		{
			head = head->next;
			temp->next = NULL;
			delete temp;
			return true;
		}
		else
		{
			while (temp != NULL)
			{
				if (temp->next->name == x)
				{
					node1 *temp1 = temp->next;
					temp->next = temp1->next;
					delete temp1;
					return true;
				}
				else
					temp = temp->next;

				if (temp->next == NULL)
					break;
			}
		}
		return false;
	}

	bool update(string x, bool y, int z, int d)
	{
		if (head == NULL)
			return false;
		temp = head;
		while (temp != NULL)
		{
			if (temp->name == x)
			{
				temp->amount += z;
				temp->discount += d;
				if (temp->amount - temp->discount == 0)
					remove(x,head);
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	void print()
	{
		temp = head;
		while (temp != NULL)
		{
			cout << temp->name << '\t';
			temp = temp->next;
		}
		cout << endl;
	}

	bool isEmpty()
	{
		if (head == NULL)
			return true;
		else
			return false;
	}

	void saveClients(ofstream &of)
	{
		if (head == NULL)
			return;
		temp = head;
		while (temp != NULL)
		{
			if (temp == head)
				of << temp->name;
			else
				of << '\n' << temp->name;
			if (temp->amount != 0)
				of << '\n' << temp->type << '\n' << temp->amount << '\n' << temp->discount;
			temp = temp->next;
		}
	}

	~NodeList()
	{
		while (head != NULL)
		{
			temp = head;
			head = head->next;
			temp->next = NULL;
			delete temp;
		}
		delete head;
	}
};

class hashing
{
private:
	NodeList a[26];
public:
	bool h(string x, bool y = false, int z = 0, int d = 0)
	{
		char i;
		if (x[0] >= 65 && x[0] <= 96)
			i = 'A';
		else if (x[0] >= 97 && x[0] <= 122)
			i = 'a';
		else
			return false;

		return a[x[0] - i].insert(x, y, z, d);

	}

	bool update(string x, bool y = false, int z = 0, int d = 0)
	{
		char i;
		if (x[0] >= 65 && x[0] <= 96)
			i = 'A';
		else if (x[0] >= 97 && x[0] <= 122)
			i = 'a';
		else
			return false;
		return a[x[0] - i].update(x, y, z, d);
	}

	node1* findAndReturn(string x)
	{
		char i;
		if (x[0] >= 65 && x[0] <= 96)
			i = 'A';
		else if (x[0] >= 97 && x[0] <= 122)
			i = 'a';
		return a[x[0] - i].findAndReturn(x);
	}

	bool isEmpty(string x)
	{
		char i;
		if (x[0] >= 65 && x[0] <= 96)
			i = 'A';
		else if (x[0] >= 97 && x[0] <= 122)
			i = 'a';
		if (a[x[0] - i].isEmpty())
				return true;
		return false;
	}

	bool allEmpty()
	{
		for (int i = 0; i < 26; i++)
		{
			if (!a[i].isEmpty())
				return false;
		}
		return true;
	}

	void remove(string x)
	{
		char i;
		if (x[0] >= 65 && x[0] <= 96)
			i = 'A';
		else if (x[0] >= 97 && x[0] <= 122)
			i = 'a';
		else
			return;

		if (!a[x[0] - i].isEmpty())
			a[x[0] - i].remove(x, NULL);
	}

	void print()
	{
		for (int i = 0; i < 26; i++)
		{
			if (!a[i].isEmpty())
			{
				a[i].print();
				cout << endl;
			}
		}
	}

	void saveClient(ofstream &onf)
	{
	
		for (int i = 0; i < 26; i++)
		{
			if (!a[i].isEmpty())
				a[i].saveClients(onf);
		}
	}
};

class linkList
{
private:
	node *head;
	node *temp;
public:
	linkList()
	{
		head = NULL;
		temp = NULL;
	}


	void insert(CalendarType _cal, string debitAccount, string creditAccount, int debitAmount, int creditAmount, string Description)
	{
		node *temp2 = NULL;
		if (head == NULL)
		{
			head = new node;
			head->next = NULL;
			temp = head;
			temp2 = NULL;
		}
		else
		{
			temp = head;
			while (true)
			{
				if (temp->next == NULL)
					break;
				if (temp->next->cal->getDate() > _cal.getDate())
					break;
				temp = temp->next;
			}
			if (head->cal->getDate() > _cal.getDate())
			{
				temp = new node;
				temp->next = head;
				temp2 = head;
				head = temp;
			}
			else
			{
				temp2 = temp->next;
				temp->next = new node;
				temp = temp->next;
			}
		}

		temp->cal = new CalendarType(_cal);
		temp->debit.account = debitAccount;
		temp->debit.amount = debitAmount;
		temp->credit.account = creditAccount;
		temp->credit.amount = creditAmount;
		temp->description = Description;
		temp->next = temp2;
	}

	bool remove(CalendarType _cal, string debitAccount, string creditAccount, int debitAmount, int creditAmount, string Description)
	{
		if (head == NULL)
			return false;
		if (head->cal->getDate() == _cal.getDate() && head->cal->getMonth() == _cal.getMonth() && head->cal->getYear() == _cal.getYear() && debitAccount == head->debit.account && creditAccount == head->credit.account && debitAmount == head->debit.amount && creditAmount == head->credit.amount && Description == head->description)
		{
			temp = head;
			head = head->next;
			delete temp;
			return true;
		}
		temp = head;
		while (temp->next != NULL)
		{
			if (temp->next == NULL)
				break;
			if (temp->next->cal->getDate() == _cal.getDate() && temp->next->cal->getMonth() == _cal.getMonth() && temp->next->cal->getYear() == _cal.getYear() && debitAccount == temp->next->debit.account && creditAccount == temp->next->credit.account && debitAmount == temp->next->debit.amount && creditAmount == temp->next->credit.amount && Description == temp->next->description)
			{
				node *temp2 = temp->next;
				temp->next = temp2->next;
				delete temp2;
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	void print()
	{
		if (head == NULL)
		{
			cout << "Empty Ledger\n";
			return;
		}

		temp = head;

		while (temp != NULL)
		{
			cout << "\nDate: ";
			temp->cal->print();
			cout << "\nDebit Account: " << temp->debit.account << " A/C\nDebit Amount: " << temp->debit.amount;
			cout << "\nCredit Account: To " << temp->credit.account << " A/C\nCredit Amount: " << temp->credit.amount;
			cout << "\nDescription: " << temp->description << endl << endl;
			temp = temp->next;
		}
	}

	void finish(ofstream &clientData, ofstream &html, string owner)
	{

		html << "<html><head><style>header,footer{padding: 1em;color:white;background-color:#4aa6e8;clear:left;text-align:center;}div.journal{width:100%;border: 1px solid gray;}table#journal{width: 100%;}table#journal tr:nth-child(even){background-color: #eee;}table#journal tr:nth-child(odd){background-color: #fff;} th{background-color: #ccccff;color: black;padding: 40px;}</style><title>AccountDev</title></head><header><h1>" << owner << "</h1></header><body><div><table id=\"journal\" align=\"center\"><tr><th>Date</th><th>Description</th><th>AmountDebit</th><th>AmountCredit</th></tr>";
		if (head != NULL)
		{
			int sum = 0;
			temp = head;
			while (temp->next != NULL)
			{
				clientData << temp->cal->getDate() << endl << temp->cal->getMonth() << endl << temp->cal->getYear() << endl << temp->debit.account << endl << temp->debit.amount << endl << temp->credit.account << endl << temp->credit.amount << endl << temp->description << endl;
				html << "<tr><td>" << temp->cal->getDate() << '-' << temp->cal->getMonth() << '-' << temp->cal->getYear() << "</td><td>" << temp->debit.account << "</br>    To: " << temp->credit.account << "</br>" << temp->description << "</td><td>" << temp->debit.amount << "</td><td>" << temp->credit.amount << "</td></tr>";
				sum += temp->debit.amount;
				temp = temp->next;
			}
			clientData << temp->cal->getDate() << endl << temp->cal->getMonth() << endl << temp->cal->getYear() << endl << temp->debit.account << endl << temp->debit.amount << endl << temp->credit.account << endl << temp->credit.amount << endl << temp->description;
			html << "<tr><td>" << temp->cal->getDate() << '-' << temp->cal->getMonth() << '-' << temp->cal->getYear() << "</td><td>" << temp->debit.account << "</br>    To: " << temp->credit.account << "</br>(" << temp->description << ")</td><td>" << temp->debit.amount << "</td><td>" << temp->credit.amount << "</td></tr>";
			sum += temp->debit.amount;
			html << "<tr><td>" << temp->cal->endOfMonth(temp->cal->getMonth()) << '-' << temp->cal->getMonth() << '-' << temp->cal->getYear() << "</td><td>Total</td><td>" << sum << "</td><td>" << sum << "</td></tr></td></tr></table></div></body><footer>Made by Ahmad Awan,Ammad ul Islam and Ukasha Tahir</footer></html>";
		}
	}

	bool isEmpty()
	{
		return head == NULL;
	}

	void printJernel()
	{
		temp = head;
		if (head == NULL)
			return;
		string y;
		cout << "+----------+--------------------------------------------------+----------+----------+\n|--Date----|------Description---------------------------------|-Debit--Rs|Credit--Rs+\n";
		while (temp != NULL)
		{
			cout << "+----------+--------------------------------------------------+----------+----------+\n|";
			y = to_string(temp->cal->getDate()) + '-' + to_string(temp->cal->getMonth()) + '-' + to_string(temp->cal->getYear());
			cout << y;
			for (string::size_type i = 0; i < 10 - y.length(); i++)
				cout << ' ';
			cout << '|' << temp->debit.account;
			for (string::size_type i = 0; i < 50 - temp->debit.account.length(); i++)
				cout << ' ';
			cout << "|" << to_string(temp->debit.amount);
			for (string::size_type i = 0; i < 10 - to_string(temp->debit.amount).length(); i++)
				cout << ' ';
			cout << "|          |\n|          |    To: " << temp->credit.account;
			for (string::size_type i = 0; i < 50 - 8 - to_string(temp->debit.amount).length(); i++)
				cout << ' ';
			cout << "|          |" << temp->credit.amount;
			for (string::size_type i = 0; i < 10 - to_string(temp->credit.amount).length(); i++)
				cout << ' ';
			cout << "|\n|          |(" << temp->description << ')';
			for (string::size_type i = 0; i < 48 - temp->description.length(); i++)
				cout << ' ';
			cout << "|          |          |\n";
			temp = temp->next;
		}
		cout << "+----------+--------------------------------------------------+----------+----------+\n";
		int dr = 0;
		int cr = 0;
		temp = head;
		if (head != NULL)
		{
			while (temp->next != NULL)
			{
				dr += temp->debit.amount;
				cr += temp->credit.amount;
				temp = temp->next;
			}
			dr += temp->debit.amount;
			cr += temp->credit.amount;
			CalendarType end_c(*temp->cal);

			y = to_string(end_c.endOfMonth(end_c.getMonth())) + '-' + to_string(end_c.getMonth()) + '-' + to_string(end_c.getYear());
			cout << "|" << y;
			for (string::size_type i = 0; i < 10 - y.length(); i++)
				cout << ' ';
			cout << "|    Sum                                           |" << dr;
			for (string::size_type i = 0; i < 10 - to_string(dr).length(); i++)
				cout << ' ';
			cout << "|" << cr;
			for (string::size_type i = 0; i < 10 - to_string(cr).length(); i++)
				cout << ' ';
			cout << "|\n+----------+--------------------------------------------------+----------+----------+\n";
		}
	}

	void printLedgers(ofstream &out1, ofstream &out)
	{
		temp = head;
		if (head == NULL)
			return;
		while (temp != NULL)
		{
			temp->debit.visited = false;
			temp->credit.visited = false;
			temp = temp->next;
		}
		temp = head;
		node *temp2 = head;
		string account;
		int dr = -1;
		int cr = -1;
		node2 n1;
		node2 n2;
		vector <string> w;
		vector <node2> v[2];
		vector <int> x;
		vector <int> y;
		while (temp != NULL)
		{
			if (temp->debit.visited == true && temp->credit.visited == true)
			{
				temp = temp->next;
				continue;
			}
			for (int k = 0; k < 2; k++)
			{
				if (k == 0 && temp->debit.visited == false)
					account = temp->debit.account;
				else if (k == 1 && temp->credit.visited == false)
					account = temp->credit.account;
			
				temp2 = head;
				while (temp2 != NULL)
				{
					if (temp2->debit.account == account && temp2->debit.visited == false)
					{
						temp2->debit.visited = true;
						bool found = false;
						for (int i = 0; i < w.size(); i++)
						{
							if (w[i] == account)
								found = true;
						}
						if (found != true)
							w.push_back(account);
						n1.insert(temp2->cal->getDate(), temp2->cal->getMonth(), temp2->cal->getYear(), temp2->credit.amount, temp2->credit.account,temp2->debit.account);
						dr++;
						
						v[0].push_back(n1);
						node2 m;
						v[1].push_back(m);

					}
					else if (temp2->credit.account == account && temp2->credit.visited == false)
					{
						temp2->credit.visited = true;
						bool found = false;
						for (int i = 0; i < w.size(); i++)
						{
							if (w[i] == account)
								found = true;
						}
						if (found != true)
							w.push_back(account);
						n2.insert(temp2->cal->getDate(), temp2->cal->getMonth(), temp2->cal->getYear(), temp2->debit.amount, temp2->debit.account,temp2->credit.account);
						cr++;
						
						v[1].push_back(n2);
						node2 m;
						v[0].push_back(m);
					}
					temp2 = temp2->next;
				}
			}
			temp = temp->next;
		}

		for (int k = 0; k < w.size(); k++)
		{
			int sum[3] = { 0, 0, 0 };
			cout << "\tLedger: " << w[k] << endl << "+----------+--------------------+----------+----------+--------------------+----------+\n|   Date   | Particular         |  Amount  |   Date   | Particular         |  Amount  |\n|----------|--------------------|----------|----------|--------------------|----------|\n";
			out1 << "\tLedger: " << w[k] << endl << "+----------+--------------------+----------+----------+--------------------+----------+\n|   Date   | Particular         |  Amount  |   Date   | Particular         |  Amount  |\n|----------|--------------------|----------|----------|--------------------|----------|\n";
			for (int i = 0; i < v[1].size(); i++)
			{
				if (v[0].at(i).from != w[k])
				{
					if (v[1].at(i).from != w[k])
						continue;
				}
				if (!v[0].empty() && v[0][i].date != 0 && v[0][i].from == w[k])
				{
					string y = to_string(v[0][i].date) + '-' + to_string(v[0][i].month) + '-' + to_string(v[0][i].year);
					cout << '|' << y;
					out1 << '|' << y;
					for (string::size_type l = 0; l < 10 - y.length(); l++)
					{
						cout << ' ';
						out1 << ' ';
					}
					cout << '|' << v[0][i].account;
					out1 << '|' << v[0][i].account;
					for (string::size_type l = 0; l < 20 - v[0][i].account.length(); l++)
					{
						cout << ' ';
						out1 << ' ';
					}
					cout << '|' << v[0][i].amount;
					out1 << '|' << v[0][i].amount;
					for (string::size_type l = 0; l < 10 - to_string(v[0][i].amount).length(); l++)
					{
						cout << ' ';
						out1 << ' ';
					}
					sum[0] += v[0][i].amount;
				}
				else
				{
					cout << "|          |                    |          ";
					out1 << "|          |                    |          ";
				}

				if (!v[1].empty() && v[1][i].date != 0 && v[1][i].from == w[k])
				{
					string y = to_string(v[1][i].date) + '-' + to_string(v[1][i].month) + '-' + to_string(v[1][i].year);
					cout << '|' << y;
					out1 << '|' << y;
					for (string::size_type l = 0; l < 10 - y.length(); l++)
					{
						cout << ' ';
						out1 << ' ';
					}
					cout << '|' << v[1][i].account;
					out1 << '|' << v[1][i].account;
					for (string::size_type l = 0; l < 20 - v[1][i].account.length(); l++)
					{
						cout << ' ';
						out1 << ' ';
					}
					cout << '|' << v[1][i].amount;
					out1 << '|' << v[1][i].amount;
					for (string::size_type l = 0; l < 10 - to_string(v[1][i].amount).length(); l++)
					{
						cout << ' ';
						out1 << ' ';
					}
					cout << "|\n";
					out1 << "|\n";
					sum[1] += v[1][i].amount;
				}
				else
				{
					cout << "|          |                    |          |\n|----------|--------------------|----------|----------|--------------------|----------|\n";
					out1 << "|          |                    |          |\n|----------|--------------------|----------|----------|--------------------|----------|\n";
				}
			}
			if (sum[0] > sum[1])
			{
				sum[2] = sum[0] - sum[1];
				cout << "|          |                    |          |          |     c/d down       | " << sum[2] << "   |\n|----------|--------------------|----------|----------|--------------------|----------|\n";
				out1 << "|          |                    |          |          |     c/d down       | " << sum[2] << "   |\n|----------|--------------------|----------|----------|--------------------|----------|\n";
				y.push_back(-1);
			}
			else if (sum[0] < sum[1])
			{
				sum[2] = sum[1] - sum[0];
				cout << "|          |     c/d down       | " << sum[2] << "   |          |                    |          |\n|----------|--------------------|----------|----------|--------------------|----------|\n";
				out1 << "|          |     c/d down       | " << sum[2] << "   |          |                    |          |\n|----------|--------------------|----------|----------|--------------------|----------|\n";
				y.push_back(1);
			}
			else
			{
				sum[2] = sum[0];
				y.push_back(0);
			}

			int high;

			if (sum[0] > sum[1])
				high = sum[0];
			else
				high = sum[1];
			cout << "|          |     Total          | " << high << "   |          |     Total          | " << high << "   |\n+----------+--------------------+----------+----------+--------------------+----------+\n";
			out1 << "|          |     Total          | " << high << "   |          |     Total          | " << high << "   |\n+----------+--------------------+----------+----------+--------------------+----------+\n";

			x.push_back(sum[2]);
			cout << endl << endl;
		}

		cout << "Trial Balance\n";
		out << "Trial Balance\n";

		cout << "+--------------------+----------+----------+\n|  Ledger Account    | Debit Rs | Credit Rs|\n|--------------------|----------|----------|\n";
		out << "+--------------------+----------+----------+\n|  Ledger Account    | Debit Rs | Credit Rs|\n|--------------------|----------|----------|\n";

		int sum[2] = { 0, 0 };

		for (int i = 0; i < w.size(); i++)
		{
			cout << "|" << w[i];
			out << "|" << w[i];
			for (string::size_type l = 0; l < 20 - w[i].length(); l++)
			{
				cout << ' ';
				out << ' ';
			}
			if (y[i] == 0)
			{
				cout << '|' << x[i];
				out << '|' << x[i];
				for (string::size_type l = 0; l < 10 - to_string(x[i]).length(); l++)
				{
					cout << ' ';
					out << ' ';
				}
				cout << '|' << x[i];
				out << '|' << x[i];
				for (string::size_type l = 0; l < 10 - to_string(x[i]).length(); l++)
				{
					cout << ' ';
					out << ' ';
				}
				sum[0] += x[i];
				sum[1] += x[i];
			}
			else
			{
				if (y[i] == -1)
				{
					cout << '|' << x[i];
					out << '|' << x[i];
					for (string::size_type l = 0; l < 10 - to_string(x[i]).length(); l++)
					{
						cout << ' ';
						out << ' ';
					}
					sum[0] += x[i];
				}
				else
				{
					cout << "|          ";
					out << "|          ";
				}
				if (y[i] == 1)
				{
					cout << '|' << x[i];
					out << '|' << x[i];
					for (string::size_type l = 0; l < 10 - to_string(x[i]).length(); l++)
					{
						cout << ' ';
						out << ' ';
					}
					sum[1] += x[i];
				}
				else
				{
					cout << "|          ";
					out << "|          ";
				}
			}
			cout << "|\n|--------------------|----------|----------|\n";
			out << "|\n|--------------------|----------|----------|\n";
		}
		cout << "|     Total          |" << sum[0];
		out << "|     Total          |" << sum[0];
		for (string::size_type l = 0; l < 10 - to_string(sum[0]).length(); l++)
		{
			cout << ' ';
			out << ' ';
		}
		cout << "|" << sum[0];
		out << "|" << sum[0];
		for (string::size_type l = 0; l < 10 - to_string(sum[0]).length(); l++)
		{
			cout << ' ';
			out << ' ';
		}
		cout << "|\n+--------------------+----------+----------+\n\n";
		out << "|\n+--------------------+----------+----------+\n\n";
	}

	~linkList()
	{
		while (head != NULL)
		{
			temp = head;
			head = head->next;
			temp->next = NULL;
			if (temp != NULL)
				delete temp;
		}
		if (head != NULL)
			delete head;
	}
};



class account
{
private:
	string Owner;
	string command;
	string action;
	string acc;
	int commandCount;
	int type[6];
	int pos[16];
	int APR;
	linkList *journal;
	CalendarType *cal;
	hashing *clients;
	hashing *owners;
public:
	account()
	{
		journal = new linkList;
		cal = new CalendarType;
		clients = new hashing;
		owners = new hashing;
		Owner = command = acc = action = "";
		for (int i = 0; i < 16; i++)
		{
			pos[i] = 0;
			if (i < 6)
				type[i] = 0;
		}
	}

	void printJournal()
	{
		journal->print();
		clients->print();
	}

	void saveClientData()
	{
		ofstream clientData(Owner + "\\client.txt");
		if (!clientData.fail())
			clients->saveClient(clientData);
		clientData.close();
	}

	void saveOwnerData()
	{
		ofstream ownerData("owners.txt");
		if (!ownerData.fail())
			owners->saveClient(ownerData);
		ownerData.close();
	}

	void saveJournalData()
	{
		CalendarType c;
		journal->remove(c, "", "", 0, 0, "");
		ofstream journalData(Owner + "\\" + to_string(cal->getMonth()) + '-' + to_string(cal->getYear()) + '-' + "journal.txt");
		ofstream html(Owner + "\\" + to_string(cal->getMonth()) + '-' + to_string(cal->getYear()) + '-' + "journal.html");
		journal->finish(journalData,html, Owner);
		journalData.close();
		html.close();
	}

	void loadOwnersData()
	{
		ifstream ownerData("owners.txt");
		string y;
		if (!ownerData.fail())
		{
			while (std::getline(ownerData, y))
				owners->h(y);
		}
		ownerData.close();
	}

	void loadClientData()
	{
		ifstream clientData(Owner + "\\client.txt");
		if (!clientData.fail())
		{
			int w[3];
			string y[4];
			while (!clientData.eof())
			{
				for (int i = 0; i < 4; i++)
					std::getline(clientData, y[i]);
				for (int i = 0; i < 3; i++)
				{
					int sum = 0;
					for (int j = 0; j < y[i + 1].length() && y[i + 1][0] >= 48 && y[i + 1][0] <= 57; j++)
					{
						sum *= 10;
						sum += y[i + 1][j] - 48;
					}
					w[i] = sum;
				}
				clients->h(y[0], w[0], w[1], w[2]);
			}
		}
		clientData.close();
	}

	void loadJournalData()
	{
		if (!journal->isEmpty())
		{
			CalendarType c;
			journal->remove(c, "", "", 0, 0, "");
		}
		ifstream journalData(Owner + "\\" + to_string(cal->getMonth()) + '-' + to_string(cal->getYear()) + '-' + "journal.txt");
		if (!journalData.fail())
		{
			string y[3];
			string x[5];
			int z[5];
			while (!journalData.eof())
			{
				std::getline(journalData, x[0]);
				std::getline(journalData, x[1]);
				std::getline(journalData, x[2]);
				std::getline(journalData, y[0]);
				std::getline(journalData, x[3]);
				std::getline(journalData, y[1]);
				std::getline(journalData, x[4]);
				std::getline(journalData, y[2]);
				for (int i = 0; i < 5; i++)
				{
					int sum = 0;
					for (int j = 0; j < x[i].length() && x[i][0] >= 48 && x[i][0] <= 57; j++)
					{
						sum *= 10;
						sum += x[i][j] - 48;
					}
					z[i] = sum;
				}
				CalendarType *_cal = new CalendarType;
				_cal->verify(z[0], z[1], z[2]);
				journal->insert(*_cal, y[0], y[1], z[3], z[4], y[2]);
			}
		}
		journalData.close();
	}

	void setOwner(string x)
	{
		Owner = x;
	}

	void reset()
	{
		command = acc = action = "";
		commandCount = 0;
		for (int i = 0; i < 16; i++)
		{
			pos[i] = 0;
			if (i < 6)
				type[i] = 0;
		}
		delete journal;
		delete cal;
		delete clients;
		journal = new linkList;
		cal = new CalendarType;
		clients = new hashing;
		commandCount = 0;
	}

	int enterCommand()
	{
		command = acc = action =  "";
		int p = 0;

		for (int i = 0; i < 12; i++)
		{
			pos[i] = 0;
			if (i < 6)
				type[i] = 0;
		}

		cout << "\nEnter command: ";
		getline(cin, command);

		lowerCase();

		if (command == "exit" || command == "e")
		{
			if (commandCount > 0)
				saveJournalData();
			saveClientData();
			saveOwnerData();
			return 0;
		}

		int z = 0;
		int commasCount = 0;
		for (string::size_type i = 0; i < command.length() && z < 6; i++)
		{
			if (command[i] == '\"')
				commasCount++;
			if (isInt(i))
			{
				if (commasCount % 2 != 0)
				{
					cout << "\nNumbers cannot be in commas\n";
					return -1;
				}
				pos[p] = i;
				p++;
				type[z] = returnInt(i);
				pos[p] = i - 1;
				p++;
				z++;
				if (command[i] == '\"')
					commasCount++;
			}
		}

		if (command[pos[8]+1] == '%')
			type[4] = int((type[4] / 100.0) * type[3]);

		lowerCase();

		int act = 0;
		if ((act = command.find("started", 0)) != string::npos)
			action = "started";
		else if ((act = command.find("broughtin", 0)) != string::npos)
			action = "broughtin";
		else if ((act = command.find("bought", 0)) != string::npos)
			action = "bought";
		else if ((act = command.find("sold", 0)) != string::npos)
			action = "sold";
		else if ((act = command.find("paid", 0)) != string::npos)
			action = "paid";
		else if ((act = command.find("received", 0)) != string::npos)
			action = "received";
		else if ((act = command.find("gaveaway", 0)) != string::npos)
			action = "gaveaway";
		else if ((act = command.find("lost", 0)) != string::npos)
			action = "lost";
		else if ((act = command.find("set", 0)) != string::npos)
			action = "set";
		else if ((act = command.find("return", 0)) != string::npos)
			action = "return";
		else if ((act = command.find("print", 0)) != string::npos)
			action = "print";
		else
		{
			cout << "\nUnknown Action\n";
			return -1;
		}

		pos[p] = act;
		p++;
		pos[p] = act + action.length() - 1;
		p++;

		if ((act = command.find("business", act + 1 + acc.length())) != string::npos)
			acc = "business";
		else if ((act = command.find("building", act + 1 + acc.length())) != string::npos)
			acc = "building";
		else if ((act = command.find("land", act + 1 + acc.length())) != string::npos)
			acc = "land";
		else if ((act = command.find("furniture", act + 1 + acc.length())) != string::npos)
			acc = "furniture";
		else if ((act = command.find("merchendise", act + 1 + acc.length())) != string::npos)
			acc = "merchendise";
		else if ((act = command.find("purchases", act + 1 + acc.length())) != string::npos)
			acc = "purchases";
		else if ((act = command.find("a/p", act + 1 + acc.length())) != string::npos)
			acc = "a/p";
		else if ((act = command.find("a/r", act + 1 + acc.length())) != string::npos)
			acc = "a/r";
		else if ((act = command.find("rent", act + 1 + acc.length())) != string::npos)
			acc = "rent";
		else if ((act = command.find("bill", act + 1 + acc.length())) != string::npos)
			acc = "bill";
		else if ((act = command.find("transportation", act + 1 + acc.length())) != string::npos)
			acc = "transportation";
		else if ((act = act = command.find("utilities", act + 1 + acc.length())) != string::npos)
			acc = "utilities";
		else if ((act = command.find("cash", act + 1 + acc.length())) != string::npos)
			acc = "cash";
		else if ((act = command.find("money", act + 1 + acc.length())) != string::npos)
			acc = "money";
		else if ((act = command.find("owner", act + 1 + acc.length())) != string::npos)
			acc = "owner";
		else if ((act = command.find("date", act + 1 + acc.length())) != string::npos)
			acc = "date";
		else if ((act = command.find("journal", act + 1 + acc.length())) != string::npos)
			acc = "journal";
		else if ((act = command.find("ledger", act + 1 + acc.length())) != string::npos)
			acc = "ledger";
		else
		{
			cout << "\nUnknown Account\n";
			return -1;
		}

		if (action == "print" && acc == "journal" && Owner != "")
		{
			journal->printJernel();
			return 1;
		}

		if (action == "print" && acc == "ledger")
		{
			ofstream ledgerData(Owner + "\\" + to_string(cal->getMonth()) + '-' + to_string(cal->getYear()) + '-' + "ledger.txt");
			ofstream trialData(Owner + "\\" + to_string(cal->getMonth()) + '-' + to_string(cal->getYear()) + '-' + "trialBalance.txt");
			journal->printLedgers(ledgerData,trialData);
			ledgerData.close();
			trialData.close();
			return 1;
		}

		pos[p] = act;
		p++;
		pos[p] = act + acc.length() - 1;
		p++;


		int commas = count(command.begin(), command.end(), '\"');

		if (commas % 2 != 0)
		{
			cout << "\nOdd number of commas\n";
			return -1;
		}

		if (commas != 2 && action == "lost")
		{
			cout << "\nNo description of lost items\n";
			return -1;
		}

		string pay_rec = "";
		
		if (commas % 2 == 0)
		{
			string::size_type i = 0;
			while (i < command.length())
			{
				if (command[i] == '\"')
				{
					int temp = i;
					i++;
					while (command[i] != '\"')
					{
						pay_rec = pay_rec + command[i];
						i++;
					}
					int temp2 = i;
					for (int j = 0; j < 16; j += 2)
					{
						if (temp < pos[j] && pos[j + 1] < temp2)
						{
							cout << "\nWrong position of commas\n";
							return -1;
						}
					}
				}
				i++;
			}
		}
		else
		{
			cout << "\nOdd number of Inverted Commas \"\"\n";
			return -1;
		}

		if (action == "set" && acc == "date")
		{
			if (cal->getMonth() == type[1] && cal->getYear() == type[2])
			{
				cout << "\nAlready in same accounting period\n";
				return -1;
			}
			if (!cal->verify(type[0], type[1], type[2]))
			{
				cout << "\nWrong date set\n";
				return -1;
			}
			else
			{
				if (commandCount > 0)
					saveJournalData();
				loadJournalData();
				loadClientData();
				return 1;
			}
		}

		if ((type[1] != cal->getMonth() || type[2] != cal->getYear()) && commandCount != 0 && action != "set")
		{
			cout << "\nWrong period\n";
			return -1;
		}

		if (!cal->verify(type[0], type[1], type[2]) && commandCount > 0 && action != "set" && acc != "owner" )
		{
			cout << "\nUnknown Date\n";
			return -1;
		}

		node1 *n;
		
		if (action == "set" && acc == "owner")
		{
			if (pay_rec == "")
			{
				cout << "\nUnknown owner\n";
				return -1;
			}
			else if (owners->h(pay_rec))
			{
				setOwner(pay_rec);
				char tab2[256];
				strcpy_s(tab2, Owner.c_str());

				_mkdir(tab2);
			}
			else
			{
				if (!clients->allEmpty() && commandCount > 0)
					saveClientData();
				if (commandCount > 0)
					saveJournalData();
				setOwner(pay_rec);
			}
			reset();
			loadClientData();
			loadJournalData();
			return 1;
		}

		if (Owner == "" && commandCount == 0)
		{
			cout << "\nNo owner found\n";
			return -1;
		}

		else if (action == "started" && acc == "business")
		{
			if (command.find("remove", 0) != string::npos)
				journal->remove(*cal, "cash", "capital", type[3], type[3], "Started business");
			else
				journal->insert(*cal, "cash", "capital", type[3], type[3], "Started business");
		}
		else if (action == "broughtin" && (acc != "business" || acc != "a/r" || acc != "a/p" || acc != "utilities"))
		{
			if (command.find("remove", 0) != string::npos)
				journal->remove(*cal, acc, "capital", type[3], type[3], "Brought in " + acc);
			else
				journal->insert(*cal, acc, "capital", type[3], type[3], "Brought in " + acc);
		}
		else if (action == "bought" && (acc != "business" || acc != "a/r" || acc != "a/p" || acc != "utilities" || acc != "merchendise") && pay_rec == "")
		{
			if (command.find("remove", 0) != string::npos)
				journal->remove(*cal, acc, "cash", type[3], type[3], "Bought " + acc);
			else
				journal->insert(*cal, acc, "cash", type[3], type[3], "Bought " + acc);
		}
		else if (action == "bought" && acc == "merchendise" && pay_rec != "")
		{
			if (command.find("remove", 0) != string::npos)
			{
				journal->remove(*cal, "purchases", "A/P(" + pay_rec + ")", type[3], type[3], "Bought " + acc);
				clients->update(pay_rec, true, -1 * type[3]);
			}
			else
			{
				journal->insert(*cal, "purchases", "A/P(" + pay_rec + ")", type[3], type[3], "Bought " + acc);
				clients->h(pay_rec, true, type[3]);
			}
		}
		else if (action == "bought" && acc == "merchendise")
		{
			if (command.find("remove", 0) != string::npos)
				journal->remove(*cal, "purchases", "cash", type[3], type[3], "Bought " + acc);
			else
				journal->insert(*cal, "purchases", "cash", type[3], type[3], "Bought " + acc);
		}
		else if (action == "sold" && acc == "merchendise" && pay_rec != "")
		{
			if (command.find("remove", 0) != string::npos)
			{
				journal->remove(*cal, "A/R(" + pay_rec + ")", "cash", type[3], type[3], "Sold " + acc);
				clients->update(pay_rec, false, -1 * type[3]);
			}
			else
			{
				clients->h(pay_rec, false, type[3]);
				journal->insert(*cal, "A/R(" + pay_rec + ")", "cash", type[3], type[3], "Sold " + acc);
			}
			//false for A/Receivable
			//true for A/Payable
		}
		else if (action == "sold" && acc == "merchendise")
		{
			if (command.find("remove", 0) != string::npos)
				journal->remove(*cal, "cash", "sales", type[3], type[3], "Sold " + acc);
			else
				journal->insert(*cal, "cash", "sales", type[3], type[3], "Sold " + acc);
		}
		else if (action == "paid" && (acc == "rent" || acc == "transportation" || acc == "utilities" || acc == "bill"))
		{
			if (command.find("remove", 0) != string::npos)
				journal->remove(*cal, acc, "cash", type[3], type[3], "Paid " + acc);
			else
				journal->insert(*cal, acc, "cash", type[3], type[3], "Paid " + acc);
		}
		else if (action == "paid" && acc == "a/p" && pay_rec != "")
		{
			n = clients->findAndReturn(pay_rec);
			if (&n == NULL || n->type == false)
			{
				cout << "\nEither client does not exist or is A/Receivable\n";
				return -1;
			}
			if ((n->amount - n->discount) < type[3] - type[4])
			{
				cout << "\nCannot pay this amount\n";
				return -1;
			}
			if (command.find("remove", 0) != string::npos)
			{
				if (!clients->update(pay_rec, false, (type[3] - type[4]), -1 * type[4]))
					clients->h(pay_rec, false, -1 * (type[3] - type[4]), type[4]);
				journal->remove(*cal, "A/P(" + pay_rec + ")", "cash", type[3] - type[4], type[3] - type[4], "Paid " + acc);
				if (type[4] > 0)
					journal->remove(*cal, "A/P(" + pay_rec + ")", "discount", type[4], type[4], "Discount received");
			}
			else
			{
				clients->update(pay_rec, false, -1 * (type[3] - type[4]), type[4]);
				journal->insert(*cal, "A/P(" + pay_rec + ")", "cash", type[3] - type[4], type[3] - type[4], "Paid " + acc);
				if (type[4] > 0)
					journal->insert(*cal, "A/P(" + pay_rec + ")", "discount", type[4], type[4], "Discount received");
			}
		}
		else if (action == "gaveaway" && acc == "merchendise")
		{
			if (command.find("remove", 0) != string::npos)
				journal->remove(*cal, "charity", "purchases", type[3], type[3], "Gaveaway " + acc);
			else
				journal->insert(*cal, "charity", "purchases", type[3], type[3], "Gaveaway " + acc);
		}
		else if (action == "gaveaway" && (acc == "cash" || acc == "money"))
		{
			if (command.find("remove", 0) != string::npos)
				journal->remove(*cal, "charity", "cash", type[3], type[3], "Gaveaway cash");
			else
				journal->insert(*cal, "charity", "cash", type[3], type[3], "Gaveaway cash");
		}
		else if (action == "lost" && (acc != "bill" || acc != "utilities" || acc != "rent" || acc != "transportation" || acc != "a/r" || acc != "a/p" || acc != "business"))
		{
			if (command.find("remove", 0) != string::npos)
				journal->remove(*cal, "lost", acc, type[3], type[3], "lost " + pay_rec);
			else
				journal->insert(*cal, "lost", acc, type[3], type[3], "lost " + pay_rec);
		}
		else if (action == "received" && acc == "a/r" && pay_rec != "")
		{
			n = clients->findAndReturn(pay_rec);
			if (&n == NULL || n->type == true)
			{
				cout << "\nEither client does not exist or is A/Payable\n";
				return -1;
			}
			if ((n->amount - n->discount) < type[3] - type[4])
			{
				cout << "\nCannot receive this amount\n";
				return -1;
			}
			if (command.find("remove", 0) != string::npos)
			{
				if (!clients->update(pay_rec, true, (type[3] - type[4]), -1 * type[4]))
					clients->h(pay_rec, true, -1 * (type[3] - type[4]), type[4]);
				journal->remove(*cal, "cash", "A/R(" + pay_rec + ")", type[3] - type[4], type[3] - type[4], "Received cash from " + acc);
				if (type[4] > 0)
					journal->remove(*cal, "discount", "A/R(" + pay_rec + ")", type[4], type[4], "Discount allowed");
			}
			else
			{
				clients->update(pay_rec, true, -1 * (type[3] - type[4]), type[4]);

				journal->insert(*cal, "cash", "A/R(" + pay_rec + ")", type[3] - type[4], type[3] - type[4], "Received cash from " + acc);
				if (type[4] > 0)
					journal->insert(*cal, "discount", "A/R(" + pay_rec + ")", type[4], type[4], "Discount allowed");
			}
		}
		else if (action == "return" && acc == "merchendise" && pay_rec != "")
		{
			if ((n = clients->findAndReturn(pay_rec)) == NULL)
			{
				cout << "\nNo Clients found\n";
				return -1;
			}
			if ((n->amount - n->discount) < type[3])
			{
				cout << "\nCannot return this amount\n";
				return -1;
			}
			if (command.find("remove", 0) != string::npos)
			{
				if (n->type == true)
				{
					if (!clients->update(pay_rec, true, -1 * type[3], 0))
						clients->h(pay_rec, true, type[3], 0);
					journal->remove(*cal, "purchases return", "A/R(" + pay_rec + ")", type[3], type[3], "purchases were returned");
				}
				else
				{
					if (!clients->update(pay_rec, true, -1 * type[3], 0))
						clients->h(pay_rec, true, type[3], 0);
					journal->remove(*cal, "A/P(" + pay_rec + ")", "purchases return", type[3], type[3], "purchases returned");
				}
			}
			else
			{
				clients->update(pay_rec, true, -1 * type[3], 0);
				journal->insert(*cal, "purchases return", "A/R(" + pay_rec + ")", type[3], type[3], "purchases were returned");
			}
		}
		else
		{
			cout << "\nUnknown statement\n";
			return -1;
		}
		//journal.insert(cal, "", "", type[3], type[3], action+"|"+acc);

		commandCount++;

		return 1;
	}

	void lowerCase()
	{
		for (string::size_type i = 0; i < command.length(); i++)
		{
			if (command[i] >= 65 && command[i] <= 90)
				command[i] = command[i] + 32;
		}
	};

	bool isInt(string::size_type &i)
	{
		if (command[i] >= 48 && command[i] <= 57)
			return true;
		else
			return false;
	}

	int returnInt(string::size_type &i)
	{
		int sum = 0;
		for (i; i < command.length() && command[i] >= 48 && command[i] <= 57; i++)
		{
			sum *= 10;
			sum += command[i] - 48;
		}

		return sum;
	};
};

void main()
{

	account accountant;

	int x;

	accountant.loadOwnersData();

	do
	{
		x = accountant.enterCommand();
	} while (x != 0);
	
	cout << endl << endl;

	system("pause");

}