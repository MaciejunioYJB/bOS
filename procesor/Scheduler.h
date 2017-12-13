#pragma once
#include "Process.h"
#include <vector>
#include <iostream>
#include <queue>
#include <memory>
using namespace std;
shared_ptr<PCB> running = nullptr;
struct komparator
{
	bool operator() (shared_ptr<PCB> p1, shared_ptr<PCB> p2)
	{
		return p1->Tau > p2->Tau;
	}
};
class Scheduler
{
	int time;
	float alpha = 0.5;
	vector<shared_ptr<PCB>> procesy_gotowe;
	priority_queue<shared_ptr<PCB>, vector<shared_ptr<PCB>>, komparator> procesy_gotowe_queue;
public:
	Scheduler()
	{
		time = 0;
		running = FirstProcess(0);
	}
	void Schedule()
	{
		if (running != nullptr && running->GetState() == State::ZAKONCZONY)
		{
			time = running->Timmer;

		}
		if (running != nullptr && running->GetState() != State::AKTYWNY)
		{
			if (procesy_otrzymane.size() > 0)
			{
				bool x = false;
				for (auto proces : procesy_otrzymane)
				{
					if (proces->GetState() == State::NOWY) proces->SetState(State::GOTOWY);
					if (proces->GetState() == State::GOTOWY)
					{
						if (time == 0)
						{
							procesy_gotowe.push_back(proces);
						}
						else
						{
							if (x == false)
							{
								proces->SetTau(time*alpha + (1 - alpha)*running->GetTau());
								procesy_gotowe.push_back(proces);
								x = true;
							}
							else
							{
								proces->SetTau(time*alpha + (1 - alpha)*procesy_gotowe.back()->GetTau());
								procesy_gotowe.push_back(proces);
							}
						}
					}
				}
				for (auto proces : procesy_gotowe)
				{
					cout << proces->ProcessName << " - Tau: " << proces->GetTau() << endl;
					procesy_gotowe_queue.push(proces);
				}
				procesy_otrzymane.clear();
				procesy_gotowe.clear();
				if (procesy_gotowe_queue.size() > 0)
				{
					running = procesy_gotowe_queue.top();
					procesy_gotowe_queue.pop();
					running->SetState(State::AKTYWNY);
					cout << "Aktywny: " << running->ProcessName << " with Tau - " << running->GetTau() << endl;

				}
			}
			else
			{
				if (procesy_gotowe_queue.size() <= 0)
				{
					cout << "Brak gotowych procesow!" << endl;
					running = FirstProcess(0);
				}
				else
				{
					for (int i = 0; i <= procesy_gotowe_queue.size(); i++)
					{
						procesy_otrzymane.push_back(procesy_gotowe_queue.top());
						procesy_gotowe_queue.pop();
					}
					bool x = false;
					for (int i = 0; i < procesy_otrzymane.size(); i++)
					{
						if (x == false)
						{
							procesy_otrzymane[i]->SetTau(time*alpha + (1 - alpha)*running->GetTau());
							procesy_gotowe_queue.push(procesy_otrzymane[i]);
							x = true;
						}
						else
						{
								procesy_otrzymane[i]->SetTau(time*alpha + (1 - alpha)*procesy_otrzymane[i-1]->GetTau());
								procesy_gotowe_queue.push(procesy_otrzymane[i]);
							
						}
					}
					procesy_otrzymane.clear();
					running = procesy_gotowe_queue.top();
					procesy_gotowe_queue.pop();
					running->SetState(State::AKTYWNY);
					cout << "Aktywny: " << running->ProcessName << " with Tau - " << running->GetTau() << endl;
				}

			}
		}
	}
	void print_running()
	{
		cout << "Akutalnie wykonywany jest proces o nazwie: " << running->ProcessName << endl;
	}
	void wyswietl_gotowe()
	{
		priority_queue<shared_ptr<PCB>, vector<shared_ptr<PCB>>, komparator> procesy_gotowe_queue2 = procesy_gotowe_queue;
		if (procesy_gotowe_queue2.size() > 0 && procesy_otrzymane.size() > 0)
		{
			cout << "Procesy gotowe:" << endl;
			for (int i = 0; i <= procesy_gotowe_queue2.size(); i++)
			{
				cout << "Nazwa: " << procesy_gotowe_queue2.top()->ProcessName << endl;
				procesy_gotowe_queue2.pop();
			}
			for (auto proces : procesy_otrzymane)
			{
				cout << "Nazwa: " << proces->ProcessName << endl;
			}
		}
		else if (procesy_gotowe_queue2.size() > 0)
		{
			cout << "Procesy gotowe:" << endl;
			for (int i = 0; i <= procesy_gotowe_queue2.size(); i++)
			{
				cout << "Nazwa: " << procesy_gotowe_queue2.top()->ProcessName << endl;
				procesy_gotowe_queue2.pop();
			}
		}
		else if (procesy_otrzymane.size() > 0)
		{
			cout << "Procesy gotowe: " << endl;
			for (auto proces : procesy_otrzymane)
			{
				cout << "Nazwa: " << proces->ProcessName << endl;
			}
		}
		else
		{
			cout << "Brak procesow gotowych!" << endl;
		}
	}
	void dodaj_do_procesow_gotowych(shared_ptr<PCB> proces)
	{
		procesy_otrzymane.push_back(proces);
	}


};

