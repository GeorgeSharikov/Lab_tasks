using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>  
#include <Windows.h>
#include <cctype>

void open_file(string& text, string& prev_name) {
    string file_name;
    cout << "Введите название файла: ";
    cin >> file_name;
    if (file_name.substr(file_name.find_last_of(".") + 1) != "txt") {
        cout << "Неверное расширение\n";
        return;
    }

    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл\n";
        return;
    }
    if (file_name == prev_name) {
        cout << text;
        return;
    }
    prev_name = file_name;
    text = "";
    string line;
    while (getline(file, line)) {
        text += line;
        text += "\n";
    }
    cout << "Файл " << file_name << ":\n" << text << "\n";
    file.close();
}

void save_file(const string text, const string prev_name) {
    ofstream file(prev_name);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл" << endl;
        return;
    }
    file << text;
    cout << "Файл сохранен" << endl;
    file.close();
}

void copy_strings(string text, string prev_name) {
    if (prev_name.empty()) {
        cout << "Никакой файл не открыт";
    }
    const char* output = text.c_str();
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    cout << "Скопировано" << endl;
    //HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, text.length() + 1);
    //memcpy(GlobalLock(hMem), &text, text.length() + 1);
    //GlobalUnlock(hMem);
    //cout << &hMem;
    //OpenClipboard(0);
    //EmptyClipboard();
    //SetClipboardData(CF_TEXT, hMem);
    //CloseClipboard();
}

void upper_case(string& text, string prev_name) {
    string newText="";
    for (int i = 0; i < text.length(); i++) {
        if ((i == 0 && text[i] != ' ') || (text[i] != ' ' && (text[i - 1] == ' ' || text[i - 1] == '\n'))) {
            newText+=toupper(text[i]);
        }else newText += text[i];
    }
    text = newText;
    cout << text;
}

void insert_from_file(string& text) {
    string file_name;
    cout << "Введите название файла: ";
    cin >> file_name;
    if (file_name.substr(file_name.find_last_of(".") + 1) != "txt") {
        cout << "Неверное расширение\n";
        return;
    }

    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл\n";
        return;
    }
    
    string line;
    while (getline(file, line)) {
        text += line;
        text += "\n";
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    int command;
    cout << "1: Открыть файл\n";
    cout << "2: Сохранить файл\n";
    cout << "3: Выйти\n";
    cout << "4: Копирование строк.\n";
    cout << "5: Замена всех первых строчных букв слов прописными\n";
    cout << "6: Вставка текста из файла.\n";

    string text, prev_file_name;
    bool is_open = false;
    while (true) {
        if (!is_open) {
            open_file(text, prev_file_name);
            is_open = true;
        }
        cout << "Введите команду: ";
        cin >> command;
        while (cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            cout << "Неверная команда ";
            cin >> command;
        }

        switch (command)
        {
        case 1:
            open_file(text, prev_file_name);
            break;
        case 2:
            save_file(text, prev_file_name);
            break;
        case 3:
            cout << "Выход";
            return 0;
        case 4:
            copy_strings(text, prev_file_name);
            break;
        case 5:
            upper_case(text, prev_file_name);
            break;
        case 6:
            insert_from_file(text);
            break;
        default:
            cout << "Неверная Команда\n";
            break;
        }
        
    }
	return 0;
}
