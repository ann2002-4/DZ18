#include <iostream>
#include <fstream>

using namespace std;

class User {
    string _name;
    string _login;
    string _pass;

public:
    User() = default;

    User(const string& name, const string& login, const string& pass)
        : _name(name), _login(login), _pass(pass) {}

    void WriteToStream(ostream& stream) const {
        stream << _name << endl;
        stream << _login << endl;
        stream << _pass << endl;
    }

    void ReadFromStream(istream& stream) {
        getline(stream, _name);
        getline(stream, _login);
        getline(stream, _pass);
    }
};

class Message {
    string _text;
    string _sender;
    string _receiver;

public:
    Message() = default;

    Message(const string& text, const string& sender, const string& receiver)
        : _text(text), _sender(sender), _receiver(receiver) {}

    void WriteToStream(ostream& stream) const {
        stream << _text << endl;
        stream << _sender << endl;
        stream << _receiver << endl;
    }

    void ReadFromStream(istream& stream) {
        getline(stream, _text);
        getline(stream, _sender);
        getline(stream, _receiver);
    }
};

template <typename T>
void WriteToFile(const T& object, const string& filename) {
    ofstream file;
    file.open(filename, ios::out | ios::binary);

    if (!file) {
        cerr << "Failed to open file " << filename << endl;
        return;
    }

    object.WriteToStream(file);

    file.close();
}

template <typename T>
void ReadFromFile(T& object, const string& filename) {
    ifstream file;
    file.open(filename, ios::in | ios::binary);

    if (!file) {
        cerr << "Failed to open file " << filename << endl;
        return;
    }

    object.ReadFromStream(file);

    file.close();
}

int main() {
    User user("John Doe", "jdoe", "password123");
    Message message("Hello, world!", "jdoe", "jsmith");

    string userFilename = "user.dat";
    string messageFilename = "message.dat";

    // Записываем состояния объектов в файлы
    WriteToFile(user, userFilename);
    WriteToFile(message, messageFilename);

    User loadedUser;
    Message loadedMessage;

    ReadFromFile(loadedUser, userFilename);
    ReadFromFile(loadedMessage, messageFilename);


    cout << "Loaded User:" << endl;
    cout << "Name: " << loadedUser.GetName() << endl;
    cout << "Login: " << loadedUser.GetLogin() << endl;
    cout << "Password: " << loadedUser.GetPass() << endl;

    cout << endl;

    cout << "Loaded Message:" << endl;
    cout << "Text: " << loadedMessage.GetText() << endl;
    cout << "Sender: " << loadedMessage.GetSender() << endl;
    cout << "Receiver: " << loadedMessage.GetReceiver() << endl;

    return 0;
}
