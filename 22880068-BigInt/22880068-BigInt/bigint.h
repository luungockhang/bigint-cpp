#pragma once
#ifndef BIGINT_H
#define BIGINT_H
// Biến cấu trúc

struct BigInt {
	char input[100];	// lưu string 100 chữ số
	int LastIndex = 0;
	bool isNeg = false;
};

struct IntStorage {
	int HundredMillions[12];			// lưu 1 biến int 8 chữ số -> 96 chữ số (100 trieu ^ 12)
	int PowerOfHundredMillions = 0;		// n*9, dùng làm index cho BigInt
	int EndOfNumber;
};

// Định nghĩa cấu trúc
const int EMPTY_CHAR = 0;
const int EMPTY_INTEGER = 0;
const int ONE_HUNDRED_MILLION = 100000000;

// Các hàm cài đặt trong bigint.cpp
// Hàm xử lý mảng char input
BigInt InitArray(BigInt b);
BigInt ReverseInput(BigInt result);
BigInt RemoveLeadingZeroes(BigInt b);
BigInt TurnZero(BigInt b);
int FindLastIndex(BigInt b);
bool CheckOutOfNumber(BigInt b, int position);
BigInt AddRemaining(BigInt b, BigInt result, int carry, int bIndex, int resultIndex);
BigInt SubtractRemaining(BigInt b, BigInt result, int carry, int bIndex, int resultIndex);
BigInt RemoveNegSign(BigInt b);
IntStorage InitArray(IntStorage a);
IntStorage FindLastNumber(IntStorage a);

// Hàm xử lý chuyển đổi
BigInt IntToBigInt(int n);
IntStorage DecStringToInt(IntStorage a, BigInt b);
IntStorage HexStringToInt(IntStorage a, BigInt b);
int ConvertHexChar2Dec(char c);

// Xử lý so sánh
int Compare(BigInt a, BigInt b);
int CompareNeg(BigInt a, BigInt b);
bool CheckEqual(BigInt a, BigInt b);
bool CheckDifferent(BigInt a, BigInt b);
bool CheckSmaller(BigInt a, BigInt b);
bool CheckLarger(BigInt a, BigInt b);
bool CheckSmallerOrEqual(BigInt a, BigInt b);
bool CheckLargerOrEqual(BigInt a, BigInt b);

// Xử lý tính toán
BigInt Subtract(BigInt a, BigInt b);
BigInt Add(BigInt a, BigInt b);
BigInt Multiply(BigInt a, BigInt b);
BigInt Divide(BigInt a, BigInt b, int mode);
BigInt Opposite(BigInt b);
BigInt Absolute(BigInt b);
BigInt Pow(BigInt b, int power);
BigInt SquareRoot(BigInt b);
BigInt CubeRoot(BigInt b);

// Nhập xuất
BigInt InputDecBase();
void Print(IntStorage a, BigInt b);
void Print(BigInt b);
#endif // !BIGINT_H
