#include "../../bonuses/base.h"
#include "../../bonuses/1_10102018/type_list.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <iomanip>
using namespace std;

template<typename TypeList>
void read_types_recursive(istream &input, vector<byte> &data) {
	using T = typename TypeList::head;
	T t;
	input >> t;
	if (!input) throw runtime_error(string("Error while reading type: ") + getTypeName<T>());

	data.resize(data.size() + sizeof(T));
	memcpy(&data[data.size() - sizeof(T)], &t, sizeof(T));
	read_types_recursive<typename TypeList::tail>(input, data);
}

template<>
void read_types_recursive<NullType>(istream &in, vector<byte> &data) {}

template<typename TypeList>
class Reader {
private:
	ifstream input{"input.txt"};

public:
	void *readNextLine() {
		string line;
		getline(input, line);
		if (!input) throw runtime_error("End of file or IO error");

		vector<byte> data;
		istringstream input_stream(line);
		read_types_recursive<TypeList>(input_stream, data);

		byte *result = (byte *) operator new(data.size());
		copy(data.begin(), data.end(), result);
		return result;
	}
};

int main() {
	Reader<TypeList<int, char[10]>> reader;

	for (int line = 0; line < 2; ++line) {
		byte *data = (byte *) reader.readNextLine();
		for (int i = 0; i < sizeof(int) + sizeof(char[10]); ++i) {
			cout << setw(2) << hex << (int) data[i] << " ";
		}
		cout << endl;
	}
	return 0;
}