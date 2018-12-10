#include "../../bonuses/base.h"
#include "../../bonuses/1_10102018/type_list.h"
#include "../../bonuses/1_10102018/length.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <cassert>
using namespace std;

struct NoneType {};
struct NoDecompressor {};

// очень грустно что нет constexpr тернарного оператора, либо частичной специализации для шаблона
template<typename T1, typename T2, typename TypeInFile>
T1 decompressStage1(TypeInFile &valueFromFile) {
	if constexpr (is_same_v<T2, NoneType>) {
		static_assert(is_same_v<TypeInFile, T1>);
		return valueFromFile;
	} else {
		static_assert(is_same_v<TypeInFile, T2>);
		return valueFromFile.decompress();
	}
}

template<typename T1, typename T2, typename T3>
static void readOneValue(istream &input, vector<byte> &data) {
	constexpr bool hasT2 = !is_same_v<T2, NoneType>;
	constexpr bool hasFunction = !is_same_v<T3, NoDecompressor>;
	using TypeInFile = conditional_t<hasT2, T2, T1>;

	TypeInFile valueFromFile;
	input >> valueFromFile;
	if (!input) throw runtime_error(string("Error while reading type: ") + getTypeName<TypeInFile>());

	T1 valueAfterStage1 = decompressStage1<T1, T2, TypeInFile>(valueFromFile);
	if constexpr (hasFunction) {
		T3::decompress(valueAfterStage1);
	}

	data.resize(data.size() + sizeof(T1));
	memcpy(&data[data.size() - sizeof(T1)], &valueAfterStage1, sizeof(T1));
}

template<size_t i, typename TypeList1, typename TypeList2, typename ...TypeList3>
struct ReaderForOneType;

template<size_t i, typename ...Types1, typename ...Types2, typename ...Types3>
struct ReaderForOneType<i, TypeList<Types1...>, TypeList<Types2...>, TypeList<Types3...>> {
	static void read(istream &input, vector<byte> &data) {
		// https://stackoverflow.com/a/15953673/5812238
		using T1 = tuple_element_t<i, tuple<Types1...>>;
		using T2 = tuple_element_t<i, tuple<Types2...>>;
		using T3 = tuple_element_t<i, tuple<Types3...>>;
		readOneValue<T1, T2, T3>(input, data);
	}
};

template<typename TypeList1, typename TypeList2, typename TypeList3, size_t ...I>
void readNextLineImpl(istream &input, vector<byte> &data, index_sequence<I...>) {
	(ReaderForOneType<I, TypeList1, TypeList2, TypeList3>::read(input, data), ...);
}

template<typename TypeList1, typename TypeList2, typename TypeList3>
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
		readNextLineImpl<TypeList1, TypeList2, TypeList3>(input_stream, data, make_index_sequence<Length<TypeList1>::value>());

		byte *result = (byte *) operator new(data.size());
		copy(data.begin(), data.end(), result);
		return result;
	}
};

// тип элемента после распаковки
struct T1 {
	int x;
	int y;
};

// сжатый тип T1 (предполагается, что строка s состоит из цифр и всегда имеет длину 2, первая цифра --- x, вторая цифра --- y)
struct T2 {
	string s;

	T1 decompress() {
		assert(s.length() == 2);
		return {s[0] - '0', s[1] - '0'};
	}
};

istream &operator>>(istream &in, T1 &value) {
	return in >> value.x >> value.y;
}

istream &operator>>(istream &in, T2 &value) {
	return in >> value.s;
}

struct T1Decompressor {
	static void decompress(T1 &value) {
		value.x += 16;
		value.y += 16;
	}
};

int main() {
	Reader<
			TypeList<int,/*       */ char,/*      */ T1,/*        */ T1,/*        */ T1,/*        */ T1/*        */>,
			TypeList<NoneType,/*  */ NoneType,/*  */ NoneType,/*  */ NoneType,/*  */ T2,/*        */ T2/*        */>,
			TypeList<NoDecompressor, NoDecompressor, NoDecompressor, T1Decompressor, NoDecompressor, T1Decompressor>
	> reader;

	vector<size_t> sizes = {sizeof(int), sizeof(char), sizeof(T1), sizeof(T1), sizeof(T1), sizeof(T1)};
	for (int line = 0; line < 2; ++line) {
		byte *data = (byte *) reader.readNextLine();
		for (size_t size : sizes) {
			for (int i = 0; i < size; ++i) {
				cout << setw(2) << hex << (int) data[i] << " ";
			}
			data += size;
			cout << "     ";
		}
		cout << endl;
	}
	return 0;
}