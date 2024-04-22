#include <iostream>
#include <filesystem>

using namespace std;

bool check_extension(const string &target_extension, int argc, char *argv[]) {
    for (int i = 2; i < argc; ++i) {
        if (target_extension == argv[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    // 获取到当前可执行文件的路径
    filesystem::path currentPath = filesystem::current_path();
    if (currentPath != "C:\\Users\\ASUS\\Desktop\\temps") {
        cout << "Please run this program in the directory of 'temps'." << endl;
        return 0;
    }
    string curr_filename;
    // 获取当前编译好的可执行文件的文件名
    if (argc > 0) {
        filesystem::path exePath(argv[0]);
        curr_filename = exePath.stem().string() + exePath.extension().string();
    }
    try {
        if (argc == 1) {
            for (const auto &entry : filesystem::directory_iterator(currentPath)) {
                if (entry.path().filename().string() == curr_filename) {
                    continue;
                }
                remove_all(entry.path());
            }
            cout << "Clear Successful." << endl;
        } else {
            if (strcmp(argv[1], "-e") == 0) {
                for (const auto &entry : filesystem::directory_iterator(currentPath)) {
                    if (entry.path().filename().string() == curr_filename ||
                        check_extension(entry.path().extension().string().erase(0, 1), argc, argv)) {
                        continue;
                    }
                    remove_all(entry.path());
                }
                cout << "Cleared All files except for";
                for (int i = 2; i < argc; ++i) {
                    cout << " " << argv[i];
                }
                cout << " format.\n";
            } else if (strcmp(argv[1], "-d") == 0) {
                for (const auto &entry : filesystem::directory_iterator(currentPath)) {
                    if (entry.path().filename().string() == curr_filename) {
                        continue;
                    }
                    for (int i = 2; i < argc; ++i) {
                        if (entry.path().extension().string().erase(0, 1) == argv[i]) {
                            remove_all(entry.path());
                        }
                    }
                }
                cout << "Cleared All files in";
                for (int i = 2; i < argc; ++i) {
                    cout << " " << argv[i];
                }
                cout << " format.\n";
            }
        }
    } catch (filesystem::filesystem_error &e) {
        cout << e.what() << '\n';
    }
    return 0;
}