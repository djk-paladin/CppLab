#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <ctime>
#include <limits>
#include <vector>

//  \u001b[31m  \u001b[37m - красный ->белый
//Чёрный	\u001b[30m
// Красный	\u001b[31m
// Зелёный	\u001b[32m
// Жёлтый	\u001b[33m
// Синий	\u001b[34m
// Пурпурный	\u001b[35m
// Голубой	\u001b[36m
// Белый	\u001b[37m
// Сброс цвета	\u001b[0m

//Функция читает количество строк и возвращает ни разу не занятое id
int idCreater(){

    int id = 0;

    std::ifstream idReader("resources/todolist.txt");
    std::string text;
    while(std::getline(idReader, text)){
        id++;
    }

    return id+1;
}

//Класс ToDo, класс задачи
class ToDo
{
    private:

        int id;
        time_t dateStart;
        time_t dateEnd;

    public:

        std::string name;
        std::string list;
        bool done;

    ToDo(time_t stDate, std::string headline, std::string text){
        
        id = idCreater();
        dateStart = stDate;
        name = headline;
        list = text;
        done = false;
        
    }

    ToDo(int ids, time_t stDate, std::string headline, std::string text, bool don){
        
        id = ids;
        dateStart = stDate;
        name = headline;
        list = text;
        done = don;
        
    }

    ToDo(int ids, time_t stDate, time_t endDate, std::string headline, std::string text, bool don){
        
        id = ids;
        dateStart = stDate;
        dateEnd = endDate;
        name = headline;
        list = text;
        done = don;
        
    }

    int getID(){
        return id;
    }

    time_t getDateStart()
    {
        return dateStart;
    }

};

std::vector<ToDo> listMaker(){

    std::string tegsName[6] = {"[id]", "[name]", "[list]", "[startDate]", "[done]", "[endDate]"};

    system("cls");

    std::ifstream File("resources/todolist.txt");
    std::string text;
    std::vector<ToDo> list;


    int id;
    time_t dateStart;
    time_t dateEnd;
    std::string name;
    std::string lister;
    bool done;

    while(std::getline(File, text))
    {

        size_t lastIndexEnd = 0;

        for(std::string teg : tegsName)
        {

            size_t index = lastIndexEnd;

            while((index = text.find(teg, index)) != std::string::npos)
            {
                int paramOfClass;

                if(index > lastIndexEnd)
                {
                
                    paramOfClass = teg == "[id]" ?  1 : teg == "[name]" ? 2 : teg == "[list]" ? 3 : teg == "[startDate]" ? 4 : teg == "[done]" ? 5 : 0;

                    std::string replaced;

                    switch (paramOfClass)
                    {
                        case 1:
                            
                            id = std::stoi(text.substr(lastIndexEnd, index-lastIndexEnd));

                            break;

                        case 2:

                            name = text.substr(lastIndexEnd, index-lastIndexEnd);

                            break;

                        case 3:

                            replaced = text.substr(lastIndexEnd, index-lastIndexEnd);
                            replaceSymbol(replaced, "[newLine]", "\n");

                            lister = replaced;

                            break;

                        case 4:

                            dateStart = std::stoi(text.substr(lastIndexEnd, index-lastIndexEnd));

                            break;

                        case 5:

                            done  = std::stoi(text.substr(lastIndexEnd, index-lastIndexEnd));

                            break;

                        default:

                            break;

                    }

                }

                index += teg.length();
                lastIndexEnd = index;

            }

        }
        
    }

    return list;

}

void replaceSymbol(std::string& text, std::string symbol, std::string newSymbol){
    
    size_t index = 0;

    while((index = text.find(symbol, index)) != std::string::npos)
    {

        text.replace(index, symbol.length(), newSymbol);

        index += newSymbol.length();

    }

}

//Функция которая собирает от пользователь ввод, после чего создает и возвращает класс задачи
ToDo createToDo(){

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Headline of your ToDo?: ";
    std::string headline;
    std::getline(std::cin, headline);
    std::cout << "Write your planes here(enter '.' of the end): ";
    std::string text;
    std::getline(std::cin, text, '.');

    replaceSymbol(text, "\n", "[newLine]");

    time_t timestamp = time(NULL);
    time(&timestamp);

    ToDo plane(timestamp, headline, text);

    return plane;
}

//Функцция для записи самого класса в txt файл, по бокам параметров с текстом добавляются теги для дальнейшей работы функции поиска
void wtriteInFile(){

    ToDo writeList = createToDo();

    std::ofstream FileWrite("resources/todolist.txt", std::ios::app);

    FileWrite << "[id]" << writeList.getID() << "[id][name]" << writeList.name << "[name][list]" << writeList.list << "[list][startDate]" << writeList.getDateStart()  << "[startDate][done]" << writeList.done << "[done]" << std::endl; 

    FileWrite.close();

    system("cls");

    std::cout << "File closed";

    std::this_thread::sleep_for(std::chrono::seconds(3));

}

//Функция проверяющая наличие необходимых директорий и файлов для записи
void chekStartStats(){

    if(!std::filesystem::exists(std::filesystem::current_path() / "resources"))
    {

        std::cout << "\n\u001b[31mDirectory 'resources' doesn`t exist\u001b[37m\n";

        std::filesystem::create_directories(std::filesystem::current_path() / "resources");

        std::cout << "\u001b[32mDirectory 'resources' has created\u001b[0m\n";

    }
    
    std::cout << "\u001b[32mThe directory 'resources' exists\u001b[0m\n";

    std::ifstream file("resources/todolist.txt");

    if(!file)
    {
        std::cout << "\n\u001b[31mFile 'todolist.txt' doesn`t exist\u001b[37m\n";

        std::ofstream creater("resources/todolist.txt");
        creater.close();

        std::cout << "\u001b[32mFile 'todolist.txt' has created\u001b[0m\n";

    }

    file.close();

    std::cout << "\u001b[32mFile 'todolist.txt' exists\u001b[0m\n";

    std::this_thread::sleep_for(std::chrono::seconds(4));

    

}

//Функция вывода главного меню и дальнейших вызовов подпунктов
void pinMainMenue(){

    std::cout <<"|=============Main menue=============|\n"
                "|    [1]-List ToDo                   |\n"
                "|    [2]-Create ToDo                 |\n"
                "|    [3]-Edit ToDo                   |\n"
                "|    [0]-Exit                        |\n"
                "|====================================|\n\nINPUT: ";
    int input;

    std::cin >> input;

    switch (input)
    {
    case 1:
        listMaker();
        break;
    case 2:
        break;
    case 3:
        wtriteInFile();
        break;
    case 4:
        break;
    default:
        system("cls");
        std::cout << "\u001b[31mThis isn`t correct\nTry more \u001b[37m";
        std::this_thread::sleep_for(std::chrono::seconds(5));
        system("cls");
        pinMainMenue();
        break;
    }

}

//Основная функция, запускающая проверку, а затем меню
int main()
{
    system("cls");

    std::cout << "=============Welcome to ToDo list=============\n\n"
                 "Checking system for starting programm"
                 "Checking files for programm\n\n\n";

    chekStartStats();
    system("cls");

    pinMainMenue();

    return 0;

}