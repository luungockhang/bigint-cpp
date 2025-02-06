#include "bigint.h"
#include <string>
#include <iostream>
#include <math.h>
using std::cin;
using std::cout;

// Hàm xử lý mảng --------------------------------------------
// Reinitialize the array by assigning 0 to all slots and '0' to first slot.
BigInt InitArray(BigInt b) {
	for (int i = 0; i < sizeof(b.input); i++) {
		b.input[i] = 0;
	}
	b.input[0] = '0'; // reset số về 0
	return b;
}
// Reverse a Big Endian input into Little Endian and vice versa
BigInt ReverseInput(BigInt result) {
	int i = 0;
	int j = result.LastIndex;
	while (i < j) {
		int temp = result.input[i];
		result.input[i] = result.input[j];
		result.input[j] = temp;
		i++;
		j--;
	}
	return result;
}
// Remove leading zeroes from a Big Endian number
BigInt RemoveLeadingZeroes(BigInt b) {
	while (b.input[0] == '0' && b.input[1] != 0) {
		// replace this number with one forward and pull the whole array back
		// would be faster if it was a linked list
		for (int i = 0; i <= b.LastIndex; i++) {
			if (i + 1 <= b.LastIndex) {
				b.input[i] = b.input[i + 1];
			}
			// last digit
			else {
				b.input[i] = 0;
			}
		}
		b.LastIndex--;
	}
	return b;
}
// Make a BigInt zero immediately
BigInt TurnZero(BigInt b) {
	for (int i = 0; i < b.LastIndex; i++) {
		b.input[i] = '0';
	}
	b = RemoveLeadingZeroes(b);
	return b;
}
// Find last number index of a BigInt
int FindLastIndex(BigInt b) {
	for (int i = sizeof(b.input) - 1; i >= 0; i--) {
		if (b.input[i] != EMPTY_CHAR) {
			return i;
		}
	}
}
// Check if the numerator is out of number
bool CheckOutOfNumber(BigInt b, int position) {
	if (position == sizeof(b.input) - 1 || b.input[position + 1] == 0) {
		return true;
	}
	return false;
}
// Add remaining digits into result 
BigInt AddRemaining(BigInt b, BigInt result, int carry, int bIndex, int resultIndex) {
	// Cộng hêt số còn lại từ BigInt b vào BigInt result (Little Endian)
	while (bIndex >= 0 && resultIndex < sizeof(result.input)) {
		int num = b.input[bIndex] - '0';
		int sum = num + carry;
		if (sum < 0) {
			sum = 10 + sum;
			carry = -1;
			result.input[resultIndex] = sum % 10 + '0';
		}
		else {
			result.input[resultIndex] = sum % 10 + '0';
			if (sum > 9) {
				carry = sum / 10;
			}
			else {
				carry = 0;
			}
		}												// add the previous carry
		bIndex--;
		resultIndex++;
	}

	// last moment hack code
	if (carry > 0 && resultIndex < sizeof(result.input)) {
		result.input[resultIndex] = carry + '0';
	}
	return result;
}
// Unused function
BigInt SubtractRemaining(BigInt b, BigInt result, int carry, int bIndex, int resultIndex) {
	// Cộng hêt số còn lại từ BigInt b vào BigInt result
	while (bIndex >= 0 && resultIndex < sizeof(result.input)) {
		int num = b.input[bIndex] - '0';
		int sum = num + carry;							// add the previous carry
		result.input[resultIndex] = sum % 10 + '0';
		carry = 0;										// no more carry
		bIndex--;
		resultIndex++;
	}
	return result;
}
// Remove negative sign
BigInt RemoveNegSign(BigInt b) {
	int i = 0;
	while (b.input[i] != EMPTY_CHAR) {
		b.input[i] = b.input[i + 1];
		i++;
	}
	return b;
}
// IntStorage Initialization
IntStorage InitArray(IntStorage a) {
	for (int i = 0; i < sizeof(a.HundredMillions); i++) {
		a.HundredMillions[i] = 0;
	}
	return a;
};
// Find where the last number is
IntStorage FindLastNumber(IntStorage a) {
	for (int i = 0; i < sizeof(a.HundredMillions); i++) {
		if (a.HundredMillions[i] == EMPTY_INTEGER) {
			a.EndOfNumber = i;
			return a;
		}
	}
	return a;
}

// Hàm xử lý chuyển đổi -------------------------------------

// Convert Integer to BigInt
BigInt IntToBigInt(int n) {
	BigInt result;
	strcpy_s(result.input, "init");
	result = InitArray(result);

	// Turn int into positive for processing
	if (n < 0) {
		result.isNeg = true;
		n *= -1;
	}

	int index = 0;
	do {
		// Little Endian int slicing
		result.input[index] = n % 10 + '0';
		n /= 10;
		index++;
	} while (n > 0);

	result.LastIndex = FindLastIndex(result);
	result = ReverseInput(result);

	return result;
}
// Convert Decimal string into computer integer
IntStorage DecStringToInt(IntStorage a, BigInt b) {
	a.PowerOfHundredMillions = 0;

	// Lặp qua từng phần tử của chuỗi để nạp vào biến số nguyên
	int i = b.LastIndex; // last input is /0
	int hundredMillionCount = 0;
	a.HundredMillions[hundredMillionCount] = 0;
	int powerOfTens = 0;
	int power = 0;
	while (i >= 0) {
		power = pow(10, powerOfTens);
		int digit = b.input[i] - '0';
		a.HundredMillions[hundredMillionCount] += digit * power;
		if (powerOfTens == 7) {
			powerOfTens = 0;
			hundredMillionCount++;
			a.HundredMillions[hundredMillionCount] = 0;
		}
		else {
			powerOfTens++;
		}
		i--;
	}


	return a;
}
// Hex to Int (unused)
IntStorage HexStringToInt(IntStorage a, BigInt b) {
	a.PowerOfHundredMillions = 0;

	// Lặp qua từng phần tử của chuỗi để nạp vào biến số nguyên
	int i = b.LastIndex; // last input is /0
	int hundredMillionCount = 0;
	a.HundredMillions[hundredMillionCount] = 0;
	//int digitCount = 0;
	int powerOfSixteens = 0;
	int power = 0;
	int carry = 0;
	if (b.isNeg) {
		while (i >= 1) {
			power = pow(16, powerOfSixteens);
			int digit = ConvertHexChar2Dec(b.input[i]);
			a.HundredMillions[hundredMillionCount] += digit * power + carry;
			//cout << b.input[i]*power + "\n";
			if (powerOfSixteens == 7 || a.HundredMillions[hundredMillionCount] >= ONE_HUNDRED_MILLION) {
				// Move the most significant number to next number
				carry = a.HundredMillions[hundredMillionCount] / ONE_HUNDRED_MILLION;
				a.HundredMillions[hundredMillionCount] %= ONE_HUNDRED_MILLION;
				powerOfSixteens = 0;						// reset power
				hundredMillionCount++;						// next in array
				a.HundredMillions[hundredMillionCount] = 0; // array element initialization
			}
			else {
				carry = 0;
				powerOfSixteens++;
			}
			i--;
		}
	}
	else {
		while (i >= 0) {
			power = pow(16, powerOfSixteens);
			int digit = ConvertHexChar2Dec(b.input[i]);
			a.HundredMillions[hundredMillionCount] += digit * power + carry;
			//cout << b.input[i]*power + "\n";
			if (powerOfSixteens == 7 || a.HundredMillions[hundredMillionCount] >= ONE_HUNDRED_MILLION) {
				// Move the most significant number to next number
				carry = a.HundredMillions[hundredMillionCount] / ONE_HUNDRED_MILLION;
				a.HundredMillions[hundredMillionCount] %= ONE_HUNDRED_MILLION;
				powerOfSixteens = 0;						// reset power
				hundredMillionCount++;						// next in array
				a.HundredMillions[hundredMillionCount] = 0; // array element initialization
			}
			else {
				carry = 0;
				powerOfSixteens++;
			}
			i--;
		}
	}


	return a;
}
int ConvertHexChar2Dec(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	}
	else if (c >= 'a' && c <= 'f') {
		return c - 'a' + 10;
	}
	else {
		return 0;
	}
}

// Hàm xử lý so sánh -----------------------------------------

// Compare a to b. // 1 = smaller, 2 = equal, 3 = larger
int Compare(BigInt a, BigInt b) {
	if (a.LastIndex < b.LastIndex) {
		return 1;
	}
	if (a.LastIndex > b.LastIndex) {
		return 3;
	}
	// Compare each number pair
	for (int i = 0; i < a.LastIndex + 1; i++) {
		int num1 = a.input[i] - '0';
		int num2 = b.input[i] - '0';
		if (num1 < num2) {
			return 1;
		}
		if (num1 > num2) {
			return 3;
		}
	}
	// Equal case
	return 2;
}
int CompareNeg(BigInt a, BigInt b) {
	// 1 = smaller, 2 = equal, 3 = larger
	if (a.isNeg && !b.isNeg) {
		return 1;
	}
	if (!a.isNeg && b.isNeg) {
		return 3;
	}

	// Both a and b are negative, 
	// so flip the results of Compare.
	if (a.LastIndex < b.LastIndex) {
		return 3;
	}
	// Compare each number pair
	for (int i = 0; i < a.LastIndex + 1; i++) {
		int num1 = a.input[i] - '0';
		int num2 = b.input[i] - '0';
		if (num1 < num2) {
			return 3;
		}
		if (num1 > num2) {
			return 1;
		}
	}
	// Equal case
	return 2;
}
// Equal, Different, Smaller, Larger, Smaller/Equal, Larger/Equal

// Check whether two BigInts are equal.
bool CheckEqual(BigInt a, BigInt b) {
	if (a.isNeg || b.isNeg) {
		if (CompareNeg(a, b) == 2) {
			return true;
		}
		return false;
	}
	if (Compare(a, b) == 2) {
		return true;
	}
	return false;
}
// Check whether two BigInts are different.
bool CheckDifferent(BigInt a, BigInt b) {
	if (a.isNeg || b.isNeg) {
		if (CompareNeg(a, b) != 2) {
			return true;
		}
		return false;
	}
	if (Compare(a, b) != 2) {
		return true;
	}
	return false;
}
// Check whether two BigInts are smaller.
bool CheckSmaller(BigInt a, BigInt b) {
	if (a.isNeg || b.isNeg) {
		if (CompareNeg(a, b) == 1) {
			return true;
		}
		return false;
	}
	if (Compare(a, b) == 1) {
		return true;
	}
	return false;
}
// Check whether two BigInts are larger.
bool CheckLarger(BigInt a, BigInt b) {
	if (a.isNeg || b.isNeg) {
		if (CompareNeg(a, b) == 3) {
			return true;
		}
		return false;
	}
	if (Compare(a, b) == 3) {
		return true;
	}
	return false;
}
// Check whether two BigInts are smaller or equal.
bool CheckSmallerOrEqual(BigInt a, BigInt b) {
	if (a.isNeg || b.isNeg) {
		if (CompareNeg(a, b) == 3) {
			return true;
		}
		return false;
	}
	if (Compare(a, b) != 3) {
		return true;
	}
	return false;
}
// Check whether two BigInts are larger or equal.
bool CheckLargerOrEqual(BigInt a, BigInt b) {
	if (a.isNeg || b.isNeg) {
		if (CompareNeg(a, b) == 1) {
			return true;
		}
		return false;
	}
	if (Compare(a, b) != 1) {
		return true;
	}
	return false;
}

// Hàm xử lý tính toán ---------------------------------------

// Subtract two ints (a - b)
BigInt Subtract(BigInt a, BigInt b) {
	// init result
	BigInt result;
	strcpy_s(result.input, "123123ABCDEF");
	result = InitArray(result);

	// Dealing with negative numbers...
	if (a.isNeg && !b.isNeg) {  // -a - b
		BigInt temp = a;
		temp.isNeg = false;
		result = Add(temp, b);
		result.isNeg = true;
		return result;
	}
	else if (!a.isNeg && b.isNeg) { // a - -b
		BigInt temp = b;
		temp.isNeg = false;
		result = Add(temp, a);
		return result;
	}
	else if (a.isNeg && b.isNeg) { // -a - -b => -a + b -> b - a (swap)
		BigInt temp = a;
		a = b;
		b = temp;
	}

	// if b has more digits than a then swap them for an easier time :D
	// or if they have same digits and the first number's 1st digit is smaller than second's
	if (CheckSmaller(a, b)) {
		BigInt temp = a;
		a = b;
		b = temp;
		result.isNeg = !result.isNeg;
	}

	int i = a.LastIndex; int j = b.LastIndex;
	int k = 0, carry = 0;

	while (i >= 0 && j >= 0) {
		int num1 = a.input[i] - '0';
		int num2 = b.input[j] - '0';
		int sum = num1 - num2 + carry;
		if (sum < 0) {
			result.input[k] = 10 + sum + '0'; // 2 - 3 = -1, 10 - 1 = 9
			carry = -1;
		}
		else {
			result.input[k] = sum + '0';
			carry = 0;
		}
		i--; j--; k++;
	}
	if (i >= 0) { // a
		result = AddRemaining(a, result, carry, i, k);
	}

	// Filling in other attributes
	result.LastIndex = FindLastIndex(result);
	// Remove first zero
	while (result.input[result.LastIndex] == '0' && result.LastIndex != 0) {
		result.input[result.LastIndex] = 0;
		result.LastIndex--;
	}
	// Reverse input array
	result = ReverseInput(result);
	return result;
}
// Add two ints
BigInt Add(BigInt a, BigInt b) {
	// init result
	BigInt result;
	strcpy_s(result.input, "123123ABCDEF");
	result = InitArray(result);

	if (a.isNeg && !b.isNeg) {  // -a + b
		result = Subtract(b, a);
		return result;
	}
	else if (!a.isNeg && b.isNeg) {
		result = Subtract(b, a);
		return result;
	}
	else if (a.isNeg && b.isNeg) {
		result.isNeg = true;
	}

	// when a has less digits than b / a is smaller than b
	if (CheckSmaller(a, b)) {
		BigInt temp = a;
		a = b;
		b = temp;
	}

	int i = a.LastIndex; // last index
	int j = b.LastIndex;
	int k = 0;			 // k is result index pre-reversed
	int carry = 0;

	while (i >= 0 && j >= 0) {
		int num1 = a.input[i] - '0';
		int num2 = b.input[j] - '0';
		int sum = num1 + num2 + carry;
		if (sum >= 10) {
			result.input[k] = sum % 10 + '0';
			carry = sum / 10;
		}
		else {
			result.input[k] = sum % 10 + '0';
			carry = 0;
		}
		i--;
		j--;
		k++;
	}

	// Add remaining numbers if any 
	if (i >= 0) {
		result = AddRemaining(a, result, carry, i, k);
		carry = 0;
	}

	// Add carry if 
	if (carry > 0) {
		result.input[k] = carry + '0';
	}
	result.LastIndex = FindLastIndex(result);	// Find last index
	result = ReverseInput(result);				// Reverse input array
	return result;
}
// Multiply two ints
BigInt Multiply(BigInt a, BigInt b) {

	BigInt result = a;
	result = InitArray(result);
	// posneg proc

	// smaller number swap
	if (CheckSmaller(a, b)) {
		BigInt temp = a;
		a = b;
		b = temp;
	}

	// multiply proc init
	int i = a.LastIndex, j = b.LastIndex, subProductIndex = 0, powerCount = 0;
	BigInt subProduct = a;
	strcpy_s(subProduct.input, "init");
	subProduct = InitArray(subProduct); // subtotal input = 00000

	int carry = 0;

	while (i >= 0 && j >= 0) {
		int num1 = a.input[i] - '0';
		int num2 = b.input[j] - '0';
		int product = num1 * num2 + carry;
		if (product >= 10) {
			carry = product / 10;
			subProduct.input[subProductIndex] = product % 10 + '0';
			product = 0; // just to be safe
		}
		else {
			carry = 0;
			subProduct.input[subProductIndex] = product % 10 + '0';
			product = 0; // for peace of mind
		}
		i--;
		subProductIndex++;

		if (i < 0 && j >= 0) {
			i = a.LastIndex;
			j--;
			// deal with leftover carry
			if (carry > 0) {
				subProduct.input[subProductIndex] = carry + '0';
				carry = 0;
			}
			subProduct.LastIndex = FindLastIndex(subProduct);
			subProduct = ReverseInput(subProduct);
			// add more zeroes when more power is gained
			for (int iteration = 0; iteration < powerCount; iteration++) {
				subProduct.LastIndex++;
				subProduct.input[subProduct.LastIndex] = '0';
			}

			// add the subproducts into result and reinit subProduct
			subProduct = RemoveLeadingZeroes(subProduct);
			subProduct.LastIndex = FindLastIndex(subProduct);
			result.LastIndex = FindLastIndex(result);
			result = Add(result, subProduct);
			subProduct = InitArray(subProduct);
			subProductIndex = 0;
			powerCount++;
			// Add to result for now.
		}
	}
	if ((a.isNeg && !b.isNeg) || (!a.isNeg && b.isNeg)) {
		result.isNeg = true;
	}

	// Safety. Can remove.
	result = RemoveLeadingZeroes(result);
	result.LastIndex = FindLastIndex(result);

	return result;
}
// Divide two ints - Mode: 1 = quotient (chia nguyên). 2 = modulo (chia dư)
BigInt Divide(BigInt a, BigInt b, int mode) {
	// Khởi tạo biến kết quả
	BigInt result = a;
	strcpy_s(result.input, "init");
	result = InitArray(result);

	// Lỗi chia cho 0
	// Trong mảng input, chỉ có số 0 còn mấy char khác là 0
	if (b.input[0] == '0' && b.input[1] == 0) {
		result.input[0] = 33; // !
		return result;
	}

	// Trích số BigInt subnum từ a, có độ dài bằng b trước
	BigInt subNum = b;
	subNum.isNeg = false;
	BigInt denom = b;
	denom.isNeg = false;
	// Vị trí của số đầu trên a cho subnum
	int resultPosition = 0;
	// Tăng lên bằng denom.LastIndex sau lần đầu nạp số
	int numeratorPosition = 0;

	// Nạp số lần đầu: copy số của a vào subnum
	for (int subNumPos = 0; subNumPos <= b.LastIndex; subNumPos++) {
		subNum.input[subNumPos] = a.input[numeratorPosition + subNumPos];
	}
	numeratorPosition = denom.LastIndex;

	while (numeratorPosition <= a.LastIndex) {
		// So sánh subNum và denom
		subNum.LastIndex = FindLastIndex(subNum);
		denom.LastIndex = FindLastIndex(denom);
		int compareResult = Compare(subNum, denom);
		// Nhỏ hơn thì thêm 1 số từ tử số
		if (compareResult == 1) {
			// Nhỏ hơn thì chia nguyên = 0. Hạ số nếu còn. 
			result.input[resultPosition] = 0 + '0';
			resultPosition++;

			// Check hết số và hạ số
			if (CheckOutOfNumber(a, numeratorPosition)) {
				// Trả số dư là subNum còn lại
				break; // break out of this loop. 
			}
			// Hạ số tiếp theo trên tử số xuống
			numeratorPosition++;
			subNum.LastIndex += 1;
			subNum.input[subNum.LastIndex] = a.input[numeratorPosition];
		}
		else if (compareResult == 2) {
			// subNum = denom thì result = 1
			result.input[resultPosition] = 1 + '0';
			resultPosition++;

			// Trừ tử số con
			subNum = Subtract(subNum, denom); // subNum = 0, LastIndex = 0

			// Check hết số và hạ số
			if (CheckOutOfNumber(a, numeratorPosition)) {
				// Trả số dư là subNum còn lại
				break; // break out of this loop. 
			}
			numeratorPosition++;
			subNum.LastIndex += 1;
			subNum.input[subNum.LastIndex] = a.input[numeratorPosition];
		}
		else {
			// subNum > denom: cộng denom liên tục tới khi 
			// gặp một bước mà subNum < denom thì lùi
			// rồi lưu số lần cộng denom làm kết quả (bắt đầu là 1)
			// tóm lại là phải cộng liên tục denom và giữ 2 kết quả trước sau
			int quotient = 1;
			BigInt temp_before = b; // temporary denom... before adding
			BigInt temp_after = temp_before; // temp after adding lol

			// Bug hunt log
			// Hành vi: 121 / 20 = 066
			// Mô tả:
			// Khi hạ 121 -> ra thương 6 : đúng như mong đợi
			// Trừ xong còn lại 1. -> Ra thương 6: không đúng như mong đợi

			// Phán đoán: Do không reset quotient, và đã đẩy con trỏ thêm 1
			// trước khi thực hiện tiếp phép chia.

			// Sửa: Bỏ dòng cập nhật result trước khi break lúc hết số.

			// Check if subNum or equal is still larger than temp (before)
			while (CheckLargerOrEqual(subNum, temp_before)) {
				// Check one step ahead if subNum is smaller than denom after adding
				temp_after = Add(temp_after, b);
				// True -> Return quotient, subtract subNum by temp_before (assign to result)
				if (CheckSmaller(subNum, temp_after)) {
					result.input[resultPosition] = quotient + '0';
					resultPosition++;
					quotient = 0;
					break;
				}
				// False -> Add again. Update temp before
				temp_before = temp_after;
				quotient++;
			}

			// subNum = kết quả sau khi trừ đi temp_before
			// nhắc lại: temp_before là denom còn đủ nhỏ trước khi lại cộng thêm chính nó
			subNum = Subtract(subNum, temp_before);
			// Check số và hạ số
			if (CheckOutOfNumber(a, numeratorPosition)) {
				// Trả số dư là subNum còn lại
				/*result.input[resultPosition] = quotient + '0';*/
				break; // break out of this loop. 
			}
			numeratorPosition++;
			subNum.LastIndex += 1;
			subNum.input[subNum.LastIndex] = a.input[numeratorPosition];
			subNum = RemoveLeadingZeroes(subNum);
		}
	}
	// Chia lấy dư
	if (mode == 2) {
		return subNum;
	}

	// Xét dấu
	if ((a.isNeg && !b.isNeg) || (!a.isNeg && b.isNeg)) {
		result.isNeg = true;
	}

	// Tìm lại LastIndex, xóa số 0 phía trước
	result.LastIndex = FindLastIndex(result);
	result = RemoveLeadingZeroes(result);

	return result;
}
// Flip BigInt's negativity/positivity :D
BigInt Opposite(BigInt b) {
	b.isNeg = !b.isNeg;
	return b;
}
// Get absolute value
BigInt Absolute(BigInt b) {
	b.isNeg = false;
	return b;
}
// Power
BigInt Pow(BigInt b, int power) {
	BigInt output = b;  // ^1
	power--;			// decrement because of assignment

	for (int i = 0; i < power; i++) {
		output = Multiply(output, b);
	}

	output.LastIndex = FindLastIndex(output);
	return output;
}
// Square Root
BigInt SquareRoot(BigInt b) {
	// Check negative
	if (b.isNeg) {
		b.input[0] = 34;
		return b;
	}
	BigInt temp = IntToBigInt(1);

	// Check zero
	if (CheckSmaller(b, temp)) return b;

	// Check one
	if (CheckSmaller(b, IntToBigInt(4))) return temp;

	// More than one
	BigInt before = temp;
	BigInt compare = temp;
	while (CheckSmaller(compare,b)) {
		before = temp;
		temp = Add(temp, IntToBigInt(1));
		compare = temp; // ^1
		compare = Multiply(compare, temp); // ^2
	}

	return before;
}
// Cube Root
BigInt CubeRoot(BigInt b) {
	BigInt temp = IntToBigInt(1);

	// Check zero
	if (CheckSmaller(b, temp)) return b;

	// Check one
	if (CheckSmaller(b, IntToBigInt(8))) return temp;

	// More than one
	BigInt before = temp;
	BigInt compare = temp; // temp
	while (CheckSmaller(compare, b)) {
		before = temp;
		temp = Add(temp, IntToBigInt(1));
		compare = temp; // temp
		compare = Multiply(compare, temp); // temp ^ 2
		compare = Multiply(compare, temp); // temp ^ 3
	}

	return temp;
}

// Nhập xuất -------------------------------------------------
// Input decimal base number
BigInt InputDecBase() {
	// Khai báo khởi tạo
	BigInt b;
	strcpy_s(b.input, "123456789123456789");
	b = InitArray(b);

	IntStorage a;
	a = InitArray(a);

	// Xử lý nhập
	cout << "Nhap mot so nguyen he thap phan (toi da 100 chu so)\n";
	cin >> b.input;


	// Xử lý chuyển thành số nguyên
	if (b.input[0] == '-') {
		b.isNeg = true;
		b = RemoveNegSign(b);
	}


	b.LastIndex = FindLastIndex(b);

	// Xử lý bỏ số 0 ở đầu
	b = RemoveLeadingZeroes(b);

	a = DecStringToInt(a, b);
	a = FindLastNumber(a);

	// Debug
	//cout << "End of input at index: " << FindLastIndex(b) << "\n";
	//PrintBigInt(b);
	// In
	//PrintResults(a, b);
	return b;
}
// Print BigInt (with IntStorage as param) (unused)
void Print(IntStorage a, BigInt b) {
	if (b.isNeg) {
		cout << "-";
		for (int i = a.EndOfNumber - 1; i >= 0; i--) {
			cout << a.HundredMillions[i];
		}
	}
	else {
		for (int i = a.EndOfNumber - 1; i >= 0; i--) {
			cout << a.HundredMillions[i];
		}
	}
}
// Print BigInt
void Print(BigInt b) {
	// code 33
	if (b.input[0] == 33) {
		cout << "Can't divide by zero";
		return;
	}
	if (b.input[0] == 34) {
		cout << "Square root of negative numbers don't exist";
		return;
	}

	int i = 0;
	cout << "\nKet qua: ";

	if (b.isNeg) {
		cout << "-";
	}
	while (b.input[i] != EMPTY_CHAR) {
		cout << b.input[i];
		i++;
	}
	cout << "\n";
}