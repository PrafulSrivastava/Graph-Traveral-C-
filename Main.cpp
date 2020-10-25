#include <iostream>
#include <set>
#include <vector>
#include <string>
using namespace std;

//list of notes available
//total amount
//Aim: Pay amount in least number of notes

void least_num_of_notes() {
	int amt = 0;
	int note_count;
	set<int> notes;
	set<int>::reverse_iterator rit;

	cout << "Enter total amount: ";
	cin >> amt;
	cout << "Enter count of notes : ";
	cin >> note_count;
	cout << "Enter note amounts\n";
	int i = 0;
	while (i < note_count) {
		int temp;
		cin >> temp;
		notes.insert(temp);
		i++;
	}
	int count = 0;
	for (rit = notes.rbegin(); rit != notes.rend() && amt >= 0; rit++) {
		while (amt >= *rit) {
			amt -= *rit;
			count++;
		}
	}
	if (!amt) {
		cout << "Notes used : " << count;
	}
	else {
		cout << "Not Possible !" << endl;
	}
}

int factors(int n) {
	bool flag = false;
	if (n <= 0) {
		cout << "Enter number : ";
		cin >> n;
		flag = true;
	}
	
	int count = 0;
	vector<int> factors;
	factors.push_back(n);
	for (int i = n / 2; i > 0; i--) {
		if (n % i == 0) {
			factors.push_back(i);
		}
	}
	if (flag) {
		cout << "Factors are : " << endl;
		for (auto x : factors) {
			cout << x << " ";
		}
	}
	return factors.size();
}
void calculate_nxt_prime(int& np) {
	int i = np+1;
	while (factors(i) > 2) {
		i++;
	}
	np = i;
}
void prime_factors() {
	int n;
	cout << "Enter number : ";
	cin >> n;
	int count = 0;
	vector<int> factors;
	int prime = 2;
	while(n > 1) {
		if (n % prime == 0) {
			factors.push_back(prime);
			n /= prime;
		}
		else {
			calculate_nxt_prime(prime);
		}
	}
	cout << "Factors are : " << endl;
	for (auto x : factors) {
		cout << x << " ";
	}
}



int main2() {
	
	prime_factors();
	return 0;
}