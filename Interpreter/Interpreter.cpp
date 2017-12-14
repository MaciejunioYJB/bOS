#include "Interpreter.h"


Interpreter::Interpreter() {
	_PID = 0;
	_RegA = 0;
	_RegB = 0;
	_RegC = 0;
	_IP = 0;
}


Interpreter::~Interpreter()
{
}

void Interpreter::loadRegister() { // Running to wskaznik na PCB
	_PID = running->ProcessID;
	_RegA = running->A;
	_RegB = running->B;
	_RegC = running->C;
	_IP = running->CommandCounter;
}

std::string Interpreter::loadInstruction() {
	// wywolanie pamieci operacyjnej
	// zwraca nam rozkaz jaki ma zostac wykonany
	// return STRING Z ROZKAZEM
}

void Interpreter::saveRegisters() {
	running->SetCommandCounter(_IP);
	running->A = _RegA;
	running->B = _RegB;
	running->C = _RegC;
	running->Timmer++;
}

void Interpreter::showRegisters() {
	std::cout << std::endl << "Stan reejestrow dla procesu: " << _PID << std::endl;
	std::cout << "A: " << _RegA << std::endl;
	std::cout << "B: " << _RegA << std::endl;
	std::cout << "C: " << _RegA << std::endl;
	std::cout << "Licznik rozkazow: " << _IP << std::endl;
}

bool Interpreter::runInstruction() {
	// wczytujemy rozkaz do wykonania
	// instruction = loadInstruction();
	/*
	Prace rozdzielamy sobie na tablice Stringow
	rozkazy b�d� do niej zapisywane, maks rozmiar = 3.
	string s = Ram.getCommands();
	instruction[0] = s.substr(0,2);
	itd.
	*/


	// operation = instruction.substr(0,2);
	std::string operation = instruction[0];


	// operator zamkniecia procesu
	if (operation==("AD")) {
		// killujemy proces
		showRegisters();
		_IP += operation.length();

	}

	/* Operacje logiczne */
	// MV nazwa_rejestru liczba
	if (operation==("MV")) {
		std::string d1 = instruction[1];
		std::string d2 = instruction[2];
		if (d1 == "A") {
			if (d2 == "B") {
				_RegA = _RegB;
			}
			else if (d2 == "C") {
				_RegA = _RegC;
			}
			else if (d2 == "A") {
				_RegA = _RegA;
			}
			else {
				_RegA = std::stoi(d2);
			}
		}
		else if (d1 == "B") {
			if (d2 == "A") {
				_RegB = _RegA;
			}
			else if (d2 == "C") {
				_RegB = _RegC;
			}
			else if (d2 == "B") {
				_RegB = _RegB;
			}
			else {
				_RegB = std::stoi(d2);
			}
		}
		else if (d1 == "C") {
			if (d2 == "A") {
				_RegC = _RegA;
			}
			else if (d2 == "B") {
				_RegC = _RegB;
			}
			else if (d2 == "C") {
				_RegC = _RegC;
			}
			else {
				_RegC = std::stoi(d2);
			}
		}
	}

	// EQ nazwa_rejestru nazwa_rejestru
	else if (operation==("EQ")) {
		std::string d1 = instruction[1];
		std::string d2 = instruction[2];
		if (d1 == d2 || d1 == "A" && d2 == "B" && _RegA == _RegB ||
			d1 == "A" && d2 == "C" && _RegA == _RegC ||
			d1 == "B" && d2 == "A" && _RegB == _RegA ||
			d1 == "B" && d2 == "C" && _RegB == _RegC ||
			d1 == "C" && d2 == "A" && _RegC == _RegA ||
			d1 == "C" && d2 == "B" && _RegC == _RegB) {
			std::cout << "Wartosci sa sobie rowne!" << std::endl;
			_flagEQ = true;
		}
		else {
			_flagEQ = false;
			std::cout << "Wartosci sa rozne!" << std::endl;
		}
	}
	// JP gdzie
	else if (operation==("JP")) {
		std::string d1 = instruction[1];
		_IP = std::stoi(d1);
	}
	// JT gdzie(jesli prawda)
	else if (operation==("JT")) {
		std::string d1 = instruction[1];
		if (_flagEQ == true) _IP = std::stoi(d1);
	}
	// JF gdzie(je�li falsz)
	else if (operation==("JF")) {
		std::string d1 = instruction[1];
		if (_flagEQ == false) _IP = std::stoi(d1);
	}

	/* Operacje arytmetyczne */
	// AD nazwa_rejestru liczba/nazwa_rejestru
	else if (operation==("AD")) {
		std::string d1 = instruction[1];
		std::string d2 = instruction[2];
		if (d1 == "A") {
			if (d2 == "B") {
				_RegA += _RegB;
			}
			else if (d2 == "C") {
				_RegA += _RegC;
			}
			else if (d2 == "A") {
				_RegA += _RegA;
			}
			else {
				_RegA += std::stoi(d2);
			}
		}
		else if (d1 == "B") {
			if (d2 == "A") {
				_RegB += _RegA;
			}
			else if (d2 == "C") {
				_RegB += _RegC;
			}
			else if (d2 == "B") {
				_RegB += _RegB;
			}
			else {
				_RegB += std::stoi(d2);
			}
		}
		else if (d1 == "C") {
			if (d2 == "A") {
				_RegC += _RegA;
			}
			else if (d2 == "B") {
				_RegC += _RegB;
			}
			else if (d2 == "C") {
				_RegC += _RegC;
			}
			else {
				_RegC += std::stoi(d2);
			}
		}
	}

	// ML nazwa_rejestru liczba/nazwa_rejestru
	else if (operation==("ML")) {
		std::string d1 = instruction[1];
		std::string d2 = instruction[2];
		if (d1 == "A") {
			if (d2 == "B") {
				_RegA *= _RegB;
			}
			else if (d2 == "C") {
				_RegA *= _RegC;
			}
			else if (d2 == "A") {
				_RegA *= _RegA;
			}
			else {
				_RegA *= std::stoi(d2);
			}
		}
		else if (d1 == "B") {
			if (d2 == "A") {
				_RegB *= _RegA;
			}
			else if (d2 == "C") {
				_RegB *= _RegC;
			}
			else if (d2 == "B") {
				_RegB *= _RegB;
			}
			else {
				_RegB *= std::stoi(d2);
			}
		}
		else if (d1 == "C") {
			if (d2 == "A") {
				_RegC *= _RegA;
			}
			else if (d2 == "B") {
				_RegC *= _RegB;
			}
			else if (d2 == "C") {
				_RegC *= _RegC;
			}
			else {
				_RegC *= std::stoi(d2);
			}
		}
	}

	// SB nazwa_rejestru liczba/nazwa_rejestru
	else if (operation==("SB")) {
		std::string d1 = instruction[1];
		std::string d2 = instruction[2];
		if (d1 == "A") {
			if (d2 == "B") {
				_RegA -= _RegB;
			}
			else if (d2 == "C") {
				_RegA -= _RegC;
			}
			else if (d2 == "A") {
				_RegA -= _RegA;
			}
			else {
				_RegA -= std::stoi(d2);
			}
		}
		else if (d1 == "B") {
			if (d2 == "A") {
				_RegB -= _RegA;
			}
			else if (d2 == "C") {
				_RegB -= _RegC;
			}
			else if (d2 == "B") {
				_RegB -= _RegB;
			}
			else {
				_RegB -= std::stoi(d2);
			}
		}
		else if (d1 == "C") {
			if (d2 == "A") {
				_RegC -= _RegA;
			}
			else if (d2 == "B") {
				_RegC -= _RegB;
			}
			else if (d2 == "C") {
				_RegC -= _RegC;
			}
			else {
				_RegC -= std::stoi(d2);
			}
		}
	}

	// DV nazwa_rejestru liczba/nazwa_rejestru
	else if (operation==("DV")) {
		std::string d1 = instruction[1];
		std::string d2 = instruction[2];
		if (d1 == "A") {
			if (d2 == "A") {
				_RegA /= _RegA;
			}
			else if (d2 == "B") {
				_RegA /= _RegB;
			}
			else if (d2 == "C") {
				_RegA /= _RegC;
			}
			else {
				_RegA /= std::stoi(d2);
			}
		}
		else if (d1 == "B") {
			if (d2 == "A") {
				_RegB /= _RegA;
			}
			else if (d2 == "B") {
				_RegB /= _RegB;
			}
			else if (d2 == "C") {
				_RegB /= _RegC;
			}
			else {
				_RegB /= std::stoi(d2);
			}
		}
		else if (d1 == "C") {
			if (d2 == "A") {
				_RegC /= _RegA;
			}
			else if (d2 == "B") {
				_RegC /= _RegB;
			}
			else if (d2 == "C") {
				_RegC /= _RegC;
			}
			else {
				if (std::stoi(d2) == 0) {
					std::cout << "ERROR! Nie mozna dzielic przez 0\n";
				}
				else _RegC /= std::stoi(d2);
			}
		}
	}

	// IC nazwa_rejestru
	else if (operation==("IC")) {
		std::string reg = instruction[1];
		if (reg == "A") {
			_RegA++;
		}
		else if (reg == "B") {
			_RegA++;
		}
		else if (reg == "C") {
			_RegA++;
		}
	}
	// DC nazwa_rejestru
	else if (operation==("DC")) {
		std::string reg = instruction[1];
		if (reg == "A") {
			_RegA--;
		}
		else if (reg == "B") {
			_RegA--;
		}
		else if (reg == "C") {
			_RegA--;
		}
	}

	/* Operacje wykonywane na dysku */
	// OF nazwa_pliku
	else if (operation==("OF")) {
		std::string d1 = instruction[1];
		dysk.open_file(d1);
	}
	// ZF nazwa_pliku
	else if (operation==("ZF")) {
		std::string d1 = instruction[1];
		dysk.close_file(d1);
	}
	// CF nazwa_pliku
	else if (operation==("CF")) {
		std::string d1 = instruction[1];
		dysk.create_file(d1);
	}
	// WF nazwa_pliku dane
	else if (operation==("WF")) {
		std::string d1 = instruction[1];
		std::string d2 = instruction[2];
		dysk.write_file(d1, d2);
	}
	// PF nazwa_pliku
	else if (operation==("PF")) {
		std::string d1 = instruction[1];
		dysk.print_file(d1);
	}
	// DF nazwa_pliku
	else if (operation==("DF")) {
		std::string d1 = instruction[1];
		dysk.delete_file(d1);
	}
	// RF nazwa_pliku_stara nazwa_pliku_nowa
	else if (operation==("RF")) {
		std::string d1 = instruction[1];
		std::string d2 = instruction[2];
		dysk.rename_file(d1, d2);
	}
	// AF nazwa_pliku dane
	else if (operation==("AF")) {
		std::string d1 = instruction[1];
		std::string d2 = instruction[2];
		dysk.add_to_file(d1, d2);
	}
	// LF
	else if (operation==("LF")) {
		dysk.print_file_list();
	}
	// PD
	else if (operation==("PD")) {
		dysk.printDisc();
	}




	/* Operacje wykonywane na komunikatach */
	// SC nazwa_procesu nazwa_procesu
	else if (operation==("SC")) {
		
	}
	// RC nazwa_procesu nazwa_procesu
	else if (operation==("RC")) {
		//
	}
	
	/* Operacje wykonywane na procesach */
	// CP nazwa_procesu
	else if (operation==("CP")) {
		//create a new process
	}
	// DP nazwa_procesu
	else if (operation==("DP")) {
		//delete a new process
	}
	// Aktywny proces: AP
	else if (operation==("AP")) {
		scheduler.print_running();
	}
	// Gotowe procesy: RP
	else if (operation==("RP")) {
		scheduler.wyswietl_gotowe();
	}
	/* Operacje wykonywane na pamieci RAM */
	// SR
	else if (operation==("SR")) {
		RAM.show();
	}
	// SF
	else if (operation==("SF")) {
		RAM.showFIFO();
	}
}

/*
ROZKAZY -> deasmbleracja
D1 - pierwsza dana
D2 - druga dana

1. Operacja zamkniecia
	EX => zamyka proces, kill program

2. Operacje logiczne
	MV nazwa_rejestru nazwa_rejestru/liczba => D1 <- D2
	EQ nazwa_rejestru nazwa_rejestru		=> true if d1 == d2, else false
	JP gdzie								=> jump D1
	JT gdzie								=> if true jump D1
	JF gdzie								=> if false jump D1

3. Operacje arytmetyczne 
	AD nazwa_rejestru liczba/nazwa_rejestru => D1 += D2
	ML nazwa_rejestru liczba/nazwa_rejestru => D1 *= D2
	SB nazwa_rejestru liczba/nazwa_rejestru => D1 -= D2
	DV nazwa_rejestru liczba/nazwa_rejestru => D1 /= D2
	IC nazwa_rejestru						=> D1++
	DC nazwa_rejestru						=> D1--

4. Operacje wykonywane na dysku
	OF nazwa_pliku							=> otwarcie pliku
	ZF nazwa_pliku							=> zamkniecie pliku
	CF nazwa_pliku							=> utworzenie pliku
	WF nazwa_pliku dane						=> zapis do pliku
	PF nazwa_pliku							=> Print File
	DF nazwa_pliku							=> Delete File
	RF nazwa_pliku_stara nazwa_pliku_nowa	=> Rename File
	AF nazwa_pliku dane						=> Add to File. Dopisuje do pliku
	LF										=> wy�wietla pliki na dysku
	PD										=> wy�wietla cala zawartosc dysku

5. Operacje wykonywane na komunikatach
	SC nazwa_procesu						=> Send communicate
	RC nazwa_procesu						=> Receive communicate
	

6. Operacje wykonywane na procesach
	CP nazwa_procesu						=> Create a new process
	DP nazwa_procesu						=> Delete a process
	AP										=> Print active process
	RP										=> print ready process

7. Operacje wykonywane na pamieci RAM
	SR										=> Show RAM
	SF										=> Show FIFO
*/