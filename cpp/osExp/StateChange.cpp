lude<iostream>
#include<deque>
#include<string>
using namespace std;
deque<string> run;
deque<string> ready;
deque<string> block;

void state_print()
{
	cout << "run: ";
	for (auto a : run)
	{
		cout << a << '\t';
	}
	cout << endl;

	cout << "ready: ";
	for (auto a : ready)
	{
		cout << a << '\t';
	}
	cout << endl;
	cout << "block: ";
	for (auto a : block)
	{
		cout << a << '\t';
	}
	cout << endl;

}

int main()
{
	int n;
	cout << "input the count of process" << endl;
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		ready.push_back("process" +to_string(i));
	}

	cout << "initialize" << endl << endl;
	state_print();
	
	while (true)
	{
		int select;
		cout << "input select" << endl;
		cout << "1ready to run   2run to ready   3run to block    4block to ready" << endl<<endl;
		cin >> select;
		switch (select)
		{
		case 1:
			if (!ready.empty())
			{
				run.push_back(ready.front());
				ready.pop_front();
			}
			state_print();
			break;
		case 2:
			if (!run.empty())
			{
				ready.push_back(run.front());
				run.pop_front();
			}
			state_print();
			break;
		case 3:
			if (!run.empty())
			{
				block.push_back(run.front());
				run.pop_front();
			}
			state_print();
			break;
		case 4:
			if (!block.empty())
			{
				ready.push_back(block.front());
				block.pop_front();
			}
			state_print();
			break;
		default:
			break;
		}

	}

	

	return 0;
}
