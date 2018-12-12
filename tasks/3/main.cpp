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

// очень грустно что нет constexpr тернарного оператора, либо частичной специализации для шаблонной функции
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

template<typename T1, typename T2>
static void readOneValue(istream &input, vector<byte> &data, void (*decompressFunction)(T1 &)) {
	constexpr bool hasT2 = !is_same_v<T2, NoneType>;
	using TypeInFile = conditional_t<hasT2, T2, T1>;

	TypeInFile valueFromFile;
	input >> valueFromFile;
	if (!input) throw runtime_error(string("Error while reading type: ") + getTypeName<TypeInFile>());

	T1 valueAfterStage1 = decompressStage1<T1, T2, TypeInFile>(valueFromFile);
	if (decompressFunction != nullptr) {
		decompressFunction(valueAfterStage1);
	}

	data.resize(data.size() + sizeof(T1));
	memcpy(&data[data.size() - sizeof(T1)], &valueAfterStage1, sizeof(T1));
}

template<size_t i, typename TypeList1, typename TypeList2>
struct ReaderForOneType;

template<size_t i, typename ...Types1, typename ...Types2>
struct ReaderForOneType<i, TypeList<Types1...>, TypeList<Types2...>> {
	static void read(istream &input, vector<byte> &data, const vector<void *> &decompressFunctionPointers) {
		// https://stackoverflow.com/a/15953673/5812238
		using T1 = tuple_element_t<i, tuple<Types1...>>;
		using T2 = tuple_element_t<i, tuple<Types2...>>;
		void (*decompressFunction)(T1 &) = (void (*)(T1 &)) decompressFunctionPointers[i];
		readOneValue<T1, T2>(input, data, decompressFunction);
	}
};

template<typename TypeList1, typename TypeList2, size_t ...I>
void readNextLineImpl(istream &input, vector<byte> &data, const vector<void *> &decompressFunctionPointers, index_sequence<I...>) {
	(ReaderForOneType<I, TypeList1, TypeList2>::read(input, data, decompressFunctionPointers), ...);
}

template<typename TypeList1, typename ... FunctionsExceptFirst>
void addFunctionPointersToVector(vector<void *> &decompressFunctionPointers, void (*function)(typename TypeList1::head &), FunctionsExceptFirst... functionsExceptFirst) {
	decompressFunctionPointers.push_back((void *) function);
	if constexpr (sizeof...(FunctionsExceptFirst) > 0) {
		addFunctionPointersToVector<typename TypeList1::tail>(decompressFunctionPointers, functionsExceptFirst...);
	}
}

template<typename TypeList1, typename TypeList2>
class Reader {
private:
	ifstream input{"input.txt"};

	// список указателей на функции
	vector<void *> decompressFunctionPointers;

public:
	template<typename ... Functions>
	Reader(Functions... functions) {
		static_assert(Length<TypeList1>::value == Length<TypeList2>::value, "Lengths of TypeList1 and TypeList2 must match");
		static_assert(sizeof...(functions) == Length<TypeList1>::value, "number of Reader constructor arguments should match length of TypeList1");
		addFunctionPointersToVector<TypeList1>(decompressFunctionPointers, functions...);
	}

	void *readNextLine() {
		string line;
		getline(input, line);
		if (!input) throw runtime_error("End of file or IO error");

		vector<byte> data;
		istringstream input_stream(line);
		readNextLineImpl<TypeList1, TypeList2>(input_stream, data, decompressFunctionPointers, make_index_sequence<Length<TypeList1>::value>());

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

void T1Decompress(T1 &value) {
	value.x += 16;
	value.y += 16;
}

int main() {
	Reader<
			TypeList<int,/*     */ char,/*    */ T1,/*      */ T1,/*      */ T1,/* */ T1>,
			TypeList<NoneType,/**/ NoneType,/**/ NoneType,/**/ NoneType,/**/ T2,/* */ T2>
	> reader(/*    */nullptr,/* */ nullptr,/* */ nullptr,/* */ T1Decompress, nullptr, T1Decompress);

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