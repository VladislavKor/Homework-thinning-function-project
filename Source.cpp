#include <iostream>
#include <vector>

using namespace std;

void print(vector<pair<int, int>>& data);
void thinning(vector<pair<int, int>>& data, int n = 3); // complexity n^2
void thinning2(vector<pair<int, int>>& data, int n = 3); // complexity n (homework)

int main()
{

	vector<pair<int, int>> data;
	data.push_back({ 1, 10 }); //10
	data.push_back({ 2, 11 });
	data.push_back({ 3, 11 });
	data.push_back({ 4, 11 });
	data.push_back({ 5, 11 });
	data.push_back({ 6, 10 }); //10
	data.push_back({ 7, 11 });
	data.push_back({ 8, 11 });
	data.push_back({ 9, 11 });
	data.push_back({ 10, 11 });
	data.push_back({ 11, 10 }); //10

	vector<pair<int, int>> data2 = data;

	cout << "Initial: ";
	print(data);

	try
	{
		thinning(data, 4);
		thinning2(data2, 4);
	}
	catch (int n)
	{
		cerr << "\nExeption: " << n << " < 3" << endl;
	}

	cout << "\n\nResult data: ";
	print(data);
	cout << "\nResult data2: ";
	print(data2);

	return 0;
}

void print(vector<pair<int, int>>& data)
{
	for (auto& currentPair : data)
		cout << "(" << currentPair.first << ", " << currentPair.second << ") ";
}

void thinning(vector<pair<int, int>>& data, int n)
{

	if (n < 3)
	{
		throw n;
		return;
	}

	int s = data.size();
	int start = 0;
	int stop = 0;
	for (size_t i = 1; i < s; i++)
	{

		if (data[i - 1].second != data[i].second)
		{
			stop = i - 1;

			if (stop == start)
			{
				start = stop + 1;
			}

			else if (stop - start == 1)
			{

				start = stop + 1;
			}

			else if (stop - start == 2)
			{

				data.erase(data.begin() + start + 1);
				s--;
				start += 2;
				i--;
			}

			else if (stop - start > 2)
			{
				int offset = 1;
				for (size_t j = 2; j <= stop - start; j++)
				{
					if (j % n != 0)
					{
						data.erase(data.begin() + start + offset);
						s--;
						i--;
					}
					else
						offset++;
				}
				start += offset + 1;
			}
		}
	}
}

void thinning2(vector<pair<int, int>>& data, int n)
{
	if (n < 3)
	{
		throw n;
		return;
	}

	int s = data.size();
	int counter = 0;
	bool flagFirst = true;

	for (size_t i = 1; i < s - 1; i++)
	{
		if (i == 1 && flagFirst)
		{
			if ((data[i].second == data[i - 1].second))
				counter = 2;
			else
				counter = 1;

			flagFirst = false;
		}
		else
		{
			if (data[i].second != data[i - 1].second)
				counter = 1;
		}

		if ((data[i-1].second == data[i].second) && (data[i].second == data[i + 1].second))
		{
			if (counter % n != 0)
			{
				data.erase(data.begin() + i);
				s--;
				i--;
			}
		}
		counter++;
	}
}
