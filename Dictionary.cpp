#include <iostream>
using namespace std;

template <typename PairTKey, typename PairTValue>
class KeyValuePair {
public:
	PairTKey key;
	PairTValue value;

	KeyValuePair() :key(), value() {}
	KeyValuePair(const PairTKey key, const PairTValue value)
		:key(key), value(value) {}



	PairTValue& operator[](PairTKey key) { return value; }

	template <typename PairTKey, typename PairTValue>
	friend ostream& operator<<(ostream& print, KeyValuePair<typename PairTKey, typename PairTValue>& kyv);

};

template <typename PairTKey, typename PairTValue>
ostream& operator<<(ostream& print, KeyValuePair<typename PairTKey, typename PairTValue>& kyv) {

	print << kyv.key << " --> " << kyv.value << endl;
	return print;
}





template <typename TKey, typename TValue>
class Dictionary {
private:
	KeyValuePair<TKey, TValue>* _pairs = nullptr;
	size_t _count = 0;
	size_t _capacity = 5;
public:
	Dictionary()
	{
		_pairs = new KeyValuePair<TKey, TValue>[_capacity];
	}
	Dictionary(KeyValuePair<TKey, TValue>* items, size_t count)
	{
		while (count >= _capacity)
			_capacity *= 2;

		_pairs = new KeyValuePair<TKey, TValue>[count] {};

		_count = count;
		for (size_t i = 0; i < _count; i++)
		{
			_pairs[i] = items[i];
		}
	}


	TValue& item(const TKey key) {

		for (size_t i = 0; i < _count; i++)
		{
			if (key == _pairs[i].key)
				return _pairs[i][key];

		}
	}

	TValue& operator[](const TKey key)
	{
		for (size_t i = 0; i < _count; i++)
		{
			if (_pairs[i].key == key) return _pairs[i].value;
		}





	}




	void add(const KeyValuePair<TKey, TValue> pair)
	{
		_count++;
		while (_count >= _capacity)
			_capacity *= 2;

		KeyValuePair<TKey, TValue>* _pairs_cpy = new KeyValuePair<TKey, TValue>[_capacity] {};

		for (size_t i = 0; i < _count - 1; i++)
		{
			_pairs_cpy[i] = _pairs[i];
		}
		_pairs_cpy[_count - 1] = pair;

		delete[] _pairs;
		_pairs = _pairs_cpy;
		cout << "Element added succesfully." << endl;
	}
	void add(const TKey key, const TValue value) {


		_count++;
		while (_count >= _capacity)
			_capacity *= 2;

		KeyValuePair<TKey, TValue>* _pairs_cpy = new KeyValuePair<TKey, TValue>[_capacity] {};

		for (size_t i = 0; i < _count - 1; i++)
			_pairs_cpy[i] = _pairs[i];
		

		KeyValuePair< TKey,  TValue> new_kv(key,value);
		_pairs_cpy[_count - 1] = new_kv;

		delete[] _pairs;
		_pairs = _pairs_cpy;
		cout << "Element added succesfully." << endl;

	}


	size_t count() const {
		return _count;
	}
	size_t capacity() const {
		return _capacity;
	}
	TKey* keys() {
		TKey* keys = new TKey[_count]{};
		for (size_t i = 0; i < _count; i++)
		{
			keys[i] = _pairs[i].key;
		}
		for (size_t i = 0; i < _count; i++)
		{
			cout << keys[i];
		}
		return keys;



	}

	TValue* values() {
		TValue* values = new TValue[_count]{};
		for (size_t i = 0; i < _count; i++)
		{
			values[i] = _pairs[i].value;
		}for (size_t i = 0; i < _count; i++)
		{
			cout << values[i];
		}
		return values;

	}

	KeyValuePair<TKey, TValue>* items() {
		if (_pairs != nullptr)
			return _pairs;
	}



	void clear() {
		if (_pairs != nullptr)
		{
			for (size_t i = 0; i < _count; i++)
			{
				delete[] _pairs[i];
			}
			delete[] _pairs;
		}
	}
	bool containsKey(const TKey key) const {
		for (size_t i = 0; i < _count; i++)
		{
			if (key == _pairs[i].key)return true;
		}
		return false;




	}

	bool containsValue(const TValue value) const {
		for (size_t i = 0; i < _count; i++)
		{
			if (value == _pairs[i].value)return true;
		}
		return false;



	}



	bool remove(const TKey key) {
		int index = 0;
		for (size_t i = 0; i < _count; i++)
		{
			if (key == _pairs[i].key)	break;

			index++;
			if (index == _count)return false;
		}
		KeyValuePair<TKey, TValue>* new_pairs = new KeyValuePair<TKey, TValue>[_count - 1] {};

		for (size_t i = 0; i < index; i++)
			new_pairs[i] = _pairs[i];

		for (size_t i = index + 1; i < _count; i++)
			new_pairs[i - 1] = _pairs[i + index];

		delete[] _pairs;
		_pairs = new_pairs;
		_count--;
		return true;


	}


	template <typename TKey, typename TValue>
	friend ostream& operator<<(ostream& print, Dictionary<typename TKey, typename TValue>& dct);

};
template <typename TKey, typename TValue>
ostream& operator<<(ostream& print, Dictionary<typename TKey, typename TValue>& dct) {

	for (size_t i = 0; i < dct.count(); i++)
	{
		print << dct.items()[i] << endl;
	}

	return print;

}

int main() {



	KeyValuePair<int, double> kv1(1, 11.1);
	KeyValuePair<int, double> kv2(2, 22.2);
	KeyValuePair<int, double> kv3(3, 33.3);
	KeyValuePair<int, double> kv4(4, 44.4);



	KeyValuePair<int, double> a[3]{ kv1,kv2,kv3 };



	Dictionary<int, double> dct(a, 3);

	//cout << kv1.value;
	//cout<<dct.containsValue(33.3);

	//dct.add(16, 166);
	//cout << kv1;
	//dct.add(kv4);
	//dct.values();
	//cout << dct.items();
	//cout << dct.keys()[3];
	//cout << *(dct.keys());
	//cout << dct;

	//cout << dct.remove(5);
	//dct.remove(1);

	//cout << dct;


	//cout << dct.containsKey(4);
	//cout << dct[3];

	//cout << kv2[1] << endl;
	//cout << kv2.value << endl;


	Dictionary<int, string> dict;
	dict.add(1, "Apple");



	 dict[1] = "Apple";
	cout << dict[1] << endl;
	dict[1] = "Banana";
	cout << dict[1] << endl;
}