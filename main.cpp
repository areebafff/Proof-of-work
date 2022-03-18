#include <iostream>
#include <thread>         // std::thread
#include<algorithm>
#include<chrono>
#include <time.h>
#include <string>
#include <fstream>  
using namespace std;
using namespace std::chrono;

auto Findhash(string result)
{


	// Get the string
	// to get its hash value
	string hashing = result;

	// Instantiation of Object
	hash<string> mystdhash;

	// Using operator() to get hash value
	//cout << "String hash values: ";
	auto hash = mystdhash(hashing);
	return hash;

}

void puzzle1(size_t hash, string data)
{
	int Nonce=100000000;
	while( Nonce <0)
	{
		std::string result;
		result = data + std::to_string(Nonce);
		auto compare = Findhash(result);
		if (hash == compare)
			return;
		Nonce--;
	}
}
void puzzle2(size_t hash, string data)
{
	for (int Nonce = 0; Nonce < 1000000000000000; Nonce++)
	{
		std::string result;
		result = data + std::to_string(Nonce);
		auto compare = Findhash(result);
		if (hash == compare)
			return;
	}
}

void puzzle3(size_t hash, string data)
{
		int Nonce;
	for (int i = 999; i < 100000; i++)
	{
		int Nonce;
		srand(time(NULL));//takes randomize nonce and compare till brute force isnt successfull
		Nonce = rand();
		std::string result;
		result = data + std::to_string(Nonce);
		auto compare = Findhash(result);
		if (hash == compare)
			return;
	}
}
void store(string data)
{
	std::ofstream outfile("test.txt");

	outfile << data << std::endl;
	cout << "\ndata stored in c drive";

	outfile.close();
}
//select winner among threads and enable it to store data in c drive
void winner(int time1, int time2, int time3,string data)
{
	int minimum;
	minimum= std::min(std::min(time1, time2), time3);
	if (minimum == time1)
	{
		cout << "\nwinner is 1st thread";
	  std::thread t1(store,data);
	  t1.join();
	  return;
	}
	else if (minimum == time2)
	{
		cout << "\nwinner is 2nd thread";
	   thread t2(store,data);
	   t2.join();
	   return;
	}
	else
		if (minimum == time3)
		{
			cout << "\nwinner is 3rd thread";
			thread t3(store, data);
			t3.join();
		}
		
}
void mining(size_t hash, string data)
{
	int time1, time2, time3;

	//thread 1
	auto StartTime = high_resolution_clock::now();
	std::thread t1(puzzle1, hash, data);
	t1.join();
	auto stopTime = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stopTime - StartTime);
	time1 = duration.count() / 1000;
	cout << "\nSec:" << time1;

	//thread 2
	StartTime = high_resolution_clock::now();
	std::thread t2(puzzle2, hash, data);
	t2.join();
	stopTime = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stopTime - StartTime);
	time2 = duration.count() / 1000;
	cout << "\nSec:" << time2;

	//thread 3
	StartTime = high_resolution_clock::now();
	std::thread t3(puzzle3, hash, data);
	t3.join();
	stopTime = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stopTime - StartTime);
	time3 = duration.count() / 1000;
	cout << "\nSec:" << time3;


	winner(time1, time2, time3,data);

}

int main()
{
	string data = "my name is areeba";
	int Nonce;//randomize value
	srand(time(NULL));//calculated from current time
	Nonce = rand();
	cout << "Nonce:"<<Nonce << endl;
	std::string result;
	result = data + std::to_string(Nonce);//concatinate data and nonce
	auto hash = Findhash(result);//converting data + nonce --> hash
	cout << "hash value is:"<<hash;
	mining(hash, data);//for creating threads and calculate time difference
	return 0;
}