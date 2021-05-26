#include <iostream>
#include<string>
#include<fstream>
using namespace std;

class People {
	char* m_fio;
	int* m_homePhone;
	int* m_mobPhone;
	int* m_workPhone;
	char* m_info;
public:
	People();
	People(const char* fio, int homePhoone, int mobPhone, int workPhone, const char* info);
	~People();
	People& setFio();
	People& setHomePhone();
	People& setMobPhone();
	People& setWorkPhone();
	People& setInfo();
	friend ostream& operator<<(ostream& out, const People& people);
	People& operator=(const People& people);
	char* getFIO() { return m_fio; };
};
ostream& operator<<(ostream& out, const People& people) {
	out << "ФИО: " << people.m_fio << endl
		<< "Домашний телефон: " << *people.m_homePhone << endl
		<< "Мобльый телефон: " << *people.m_mobPhone << endl
		<< "Рабочий телефон: " << *people.m_workPhone << endl
		<< "Инфо: " << people.m_info << endl;
	return out;
}
People& People::operator=(const People& people) {
	if (m_fio)delete[] m_fio;
	else delete m_fio;
	m_fio = new char[strlen(people.m_fio) + 1];
	strcpy_s(m_fio, strlen(people.m_fio) + 1, people.m_fio);
	*m_homePhone = *people.m_homePhone;
	*m_mobPhone = *people.m_mobPhone;
	*m_workPhone = *people.m_workPhone;
	if (m_info)delete[] m_info;
	else delete m_info;
	m_info = new char[strlen(people.m_info) + 1];
	strcpy_s(m_info, strlen(people.m_info) + 1, people.m_info);
	return *this;
}
People::People():People("Default", 1234567, 1234567890, 1234567, "Dop info") {}
People::People(const char* fio, int homePhone, int mobPhone, int workPhone, const char* info)
{
	if (fio) {
		m_fio = new char[strlen(fio) + 1];
		strcpy_s(m_fio, strlen(fio) + 1, fio);
	}
	else {
		m_fio = new char[8]{ "Default" };
	}
	m_homePhone = new int{ homePhone };
	m_mobPhone = new int{ mobPhone };
	m_workPhone = new int{ workPhone };
	if (m_info) {
		m_info = new char[strlen(info) + 1];
		strcpy_s(m_info, strlen(info) + 1, info);
	}
	else {
		m_info = new char[8]{ "Default" };
	}
}
People::~People() {
	if (m_fio) delete[] m_fio;
	else delete m_fio;
	delete m_homePhone;
	delete m_mobPhone;
	delete m_workPhone;
	if (m_info) delete[] m_info;
	else delete m_info;
	cout << "Destroy\n";
}
People& People::setFio() {
	char buf[255];
	cout << "Введите ФИО: ";
	gets_s(buf);
	int sizebuf = strlen(buf) + 1;
	delete[]m_fio;
	m_fio = new char[sizebuf];
	for (int i{ 0 }; i < sizebuf; ++i) {
		if (i == sizebuf - 1)
			m_fio[i] = '\0';
		else
		m_fio[i] = buf[i];
	}
	return *this;
}
People& People::setHomePhone() {
	int buf;
	cout << "Введите домашний телефон: ";
	cin >> buf;
	*m_homePhone = buf;
	cin.ignore(32567, '\n');
	return *this;
}
People& People::setMobPhone() {
	int buf;
	cout << "Введите мобильный телефон: ";
	cin >> buf;
	*m_mobPhone = buf;
	cin.ignore(32567, '\n');
	return *this;
}
People& People::setWorkPhone() {
	int buf;
	cout << "Введите рабочий телефон: ";
	cin >> buf;
	*m_workPhone = buf;
	cin.ignore(32567, '\n');
	return *this;
}
People& People::setInfo() {
	char buf[255];
	cout << "Введите инфо: ";
	gets_s(buf);
	int sizebuf = strlen(buf) + 1;
	delete[]m_info;
	m_info = new char[sizebuf];
	for (int i{ 0 }; i < sizebuf; ++i) {
		if (i == sizebuf - 1)
			m_info[i] = '\0';
		else
			m_info[i] = buf[i];
	}
	return *this;
}
template<class T>
class PhoneBook {
	T* m_people;
	int m_size;
public:
	PhoneBook();
	PhoneBook(int size);
	~PhoneBook();
	T& operator[](int index);
	//friend ostream& operator<<(ostream& out, const PhoneBook& phonebook);
	PhoneBook& addPeople();
	PhoneBook& delPeople();
	int getSize() { return m_size; };
	PhoneBook& saveFile();
	PhoneBook& loadFile();
	PhoneBook& searchPeople();
};
template<class T>
T& PhoneBook<T>::operator[](int index) {
	if(index >= 0 && index < m_size)
	return m_people[index];
}
//template<class T>
//ostream& operator<<(ostream& out, const PhoneBook<T>& phonebook) {
//	for (int i{ 0 }; i < phonebook.m_size; ++i) {
//		out << phonebook[i];
//	}
//	return out;
//}
template<class T>
PhoneBook<T>::PhoneBook() :PhoneBook(0) {}
template<class T>
PhoneBook<T>::PhoneBook(int size)
	: m_size{size}
{
	if (m_size > 0)
		m_people = new People[m_size];
	else {
		m_people = nullptr;
		m_size = 0;
	}
}

template<class T>
PhoneBook<T>::~PhoneBook() { 
	if (m_people)
		delete[]m_people;
	else delete m_people;
}
template<class T>
PhoneBook<T>& PhoneBook<T>::addPeople() {
	++m_size;
	if (m_people == nullptr) {
		PhoneBook<People>* m_people = new PhoneBook<People>(m_size);
		return *this;
	}
	else {
		PhoneBook<People>* tmp = new PhoneBook<People>(m_size);
		for (int i{ 0 }; i < m_size - 1; ++i) {
			tmp->m_people[i] = m_people[i];
		}
		delete[]m_people;
		*this = *tmp;
		return *this;
	}
}
template<class T>
PhoneBook<T>& PhoneBook<T>::delPeople() {
	if(m_size > 0)--m_size;
	if (m_size > 0) {
		PhoneBook<People>* tmp = new PhoneBook<People>(m_size);
		for (int i{ 0 }; i < m_size - 1; ++i) {
			tmp->m_people[i] = m_people[i];

		}
		delete[]m_people;
		*this = *tmp;
		return *this;
	}
	else m_people = nullptr;
}
template<class T>
PhoneBook<T>& PhoneBook<T>::searchPeople() {
	int temp; bool flag = true;

	cout << "Введите фио для поиска: ";
	char value[255];
	gets_s(value);
	for (int i = 0, j = 1; i < m_size; ++i) {
		temp = strcmp(m_people[i].getFIO(), value);
		if (temp == 0) {
			cout << "\nНайдена запись!\n";
			cout << "№" << i + 1 << " " << m_people[i];
			flag = false;
		}
	}
	if (flag) cout << "Человека с такой фамилией не найдено!\n";
	return *this;
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Сохранение в файл посредством метода не получилось реализовать
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
template<class T>
PhoneBook<T>& PhoneBook<T>::saveFile() {
	fstream File;
	/*char way[255];
	cout << "Введите путь сохранения файла: ";
	gets_s(way);*/
	File.open("Test.txt", fstream::out | fstream::in | fstream::app);
	if (!File.is_open()) {
		cout << "Ошибка открытия файла.";
	}
	else {
		for (int i{ 0 }; i < m_size; ++i) {
			File.write((char*) & (*this)[i], sizeof(People));
		}
		cout << "\t\nДанные сохранены." << endl;
	File.close();
	}
	return *this;
}
template<class T>
PhoneBook<T>& PhoneBook<T>::loadFile() {
	fstream File;
	/*char way[255];
	cout << "Введите путь сохранения файла: ";
	gets_s(way);*/
	int i{ 0 };
	File.open("Test.txt", fstream::out | fstream::in);
	if (!File.is_open()) {
		cout << "Ошибка открытия файла.";
	}
	else {
		cout << "\t\nФайл успешно открыт." << endl;
		PhoneBook<People> tmp[sizeof(File) / sizeof(People)];
		for (int i{ 0 }; i < sizeof(File) / sizeof(People); ++i) {
			File.read((char*)& tmp[i], sizeof(People));
			cout << " File:  " << sizeof(File) << "  People:  " << sizeof(People) << "  i: " << i;
		}
		cout << "\t\nДанные загружены." << endl;
		File.close();
		//delete[]m_people;
		*this = *tmp;
		return *this;
	}
}


int main()
{
	system("chcp 1251");
	system("cls");
	PhoneBook<People> phonebook(2);
	//phonebook[0].setFio().setHomePhone();
	//phonebook.saveFile();
	phonebook.loadFile();

	/*for (int i{ 0 }; i < phonebook.getSize(); ++i)
		cout << phonebook[i];
	cout << "================================\n";
	cout << "Добавляем двух человек: " << endl;
	phonebook.addPeople();
	phonebook.addPeople();
	for (int i{ 0 }; i < phonebook.getSize(); ++i)
		cout << phonebook[i];
	cout << "================================\n";
	cout << "Удаляем человека: " << endl;
	phonebook.delPeople();
	for (int i{ 0 }; i < phonebook.getSize(); ++i)
		cout << phonebook[i];
	cout << "================================\n";
	cout << "Ищем человека по ФИО: \n";
	phonebook.searchPeople();*/
}
