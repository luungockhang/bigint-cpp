// 22880068-BigInt.cpp : This file contains the 'main' function. Program execution begins and ends there.
// TODO: Chuyển đổi int thành BigInt

#include <iostream>
#include <string>
#include <cmath>
#include "bigint.h"
using std::cout;
using std::cin;

int main()
{

	//BigInt num1 = InputDecBase();
	//BigInt num2 = InputDecBase();
	//BigInt result = Divide(num1, num2,1);
	// result = Add2Ints(num1, num2);
	// result = Subtract2Ints(num1, num2);
	
	// Start
	BigInt result = IntToBigInt(2250);
	
	cout << "2250 + 300";
	result = Add(result, IntToBigInt(300));
	Print(result);

	cout << "Ket qua * 2 ty";
	result = Multiply(result, IntToBigInt(2000000000)); // 2 tỷ
	Print(result);

	cout << "Ket qua - 1234";
	result = Subtract(result, IntToBigInt(1234));
	Print(result);

	cout << "Hay nhap so chia tiep theo: ";
	BigInt enter = InputDecBase();
	BigInt modulo = result;
	result = Divide(result, enter, 1);
	cout << "Thuong la: ";
	Print(result);

	cout << "Du: ";
	modulo = Divide(modulo, enter, 2);
	Print(modulo);

	cout << "Doi cua thuong la: ";
	result = Opposite(result);
	Print(result);

	cout << "Tri tuyet doi la: ";
	result = Absolute(result);
	Print(result);

	cout << "Ket qua mu 3 la: ";
	result = Pow(result, 3);
	Print(result);

	cout << "Can bac 3 ket qua la: ";
	result = CubeRoot(result);
	Print(result);

	cout << "Can bac 2 ket qua la: ";
	result = SquareRoot(result);

	// debug
	//BigInt a = IntToBigInt(1);
	//BigInt b = IntToBigInt(99);
	//BigInt result = Add(a, b);

	Print(result);
	//DecInputDecOutput();
	//HexInputDecOutput();
}

// test
//int main() {
//	BigInt result = Multiply(IntToBigInt(3123034), IntToBigInt(3123034));
//	Print(result);
//	result = Multiply(result, result);
//	Print(result);
//}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

