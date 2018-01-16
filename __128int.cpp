/*
__uint128_t can hold upto +340282366920938463463374607431768211455 = ((1<<128)-1)
*/

typedef __int128_t int128; // or __int128
typedef __uint128_t uint128; // or unsigned __int128

std::ostream& operator<<(std::ostream &outputstream, __int128_t &t) {
	bool sign = false;
	if(t < 0) sign = true;
	__uint128_t num = sign ? -t : t;
	string str = num == 0 ? "0" : "";
	while(num) {
		int ld = num % 10;
	  	str += char(ld + '0');
		num /= 10;
	} reverse(str.begin(), str.end());
	if(sign) str = "-" + str; outputstream << str;
	return outputstream;
}
std::ostream& operator<<(std::ostream &outputstream, __uint128_t &t) {
	__uint128_t num = t;
	string str = num == 0 ? "0" : "";
	while(num) {
		int ld = num % 10;
	  	str += char(ld + '0');
		num /= 10;
	} reverse(str.begin(), str.end());
	outputstream << str;
	return outputstream;
}
std::istream& operator>> (std::istream &inputstream, __int128_t &t)
{
	long long intputnumber; // or long long int
	inputstream >> intputnumber;
	t = intputnumber;
	return inputstream;
}
std::istream& operator>> (std::istream &inputstream, __uint128_t &t)
{
	unsigned long long intputnumber; // or unsigned long long int
	inputstream >> intputnumber;
	t = intputnumber;
	return inputstream;
}
