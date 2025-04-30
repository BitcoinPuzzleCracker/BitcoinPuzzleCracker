#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

class Key {
public:
    static Key from_hex(const std::string &hex) {
        // Aangenomen dat 'Key' een object vertegenwoordigt dat een adres bevat.
        Key key;
        key.address = "1" + hex.substr(0, 34);  // Simulatie van een Bitcoin adres.
        return key;
    }

    std::string address;
};

std::string int_to_hex(uint64_t num) {
    std::stringstream ss;
    ss << std::hex << num;
    return ss.str();
}

bool sequential_search(const std::string &start_hex, const std::string &end_hex, const std::set<std::string> &addresses, int bulk_size = 20) {
    uint64_t current = std::stoull(start_hex, nullptr, 16);
    uint64_t end = std::stoull(end_hex, nullptr, 16);
    uint64_t step_size = 1;
    const int step_change_interval = 20;
    int iteration = 0;

    while (current <= end) {
        std::vector<std::string> keys;
        std::vector<std::string> addr_list;

        for (int i = 0; i < bulk_size; ++i) {
            if (current > end) {
                break;
            }

            std::string magic = int_to_hex(current);
            magic.insert(magic.begin(), 17 - magic.size(), '0'); // Vul aan naar 17 tekens
            Key key = Key::from_hex(magic);
            keys.push_back(magic);
            addr_list.push_back(key.address);

            std::cout << "(H): " << magic << " : " << key.address << std::endl;
            current += step_size;
        }

        iteration++;
        if (iteration % step_change_interval == 0) {
            step_size = rand() % 10000000000000 + 1000000000000;  // Random stapgrootte
            std::cout << "Nieuwe stapgrootte: " << step_size << std::endl;
        }

        // Zoek naar een match in de adressen
        for (size_t i = 0; i < keys.size(); ++i) {
            if (addresses.find(addr_list[i]) != addresses.end()) {
                std::cout << "\n\nGevonden! Winnende details:" << std::endl;
                std::cout << "Private Key (HEX): " << keys[i] << std::endl;
                std::cout << "Bitcoin Address: " << addr_list[i] << std::endl;

                std::ofstream outfile("winner.txt", std::ios::app);
                outfile << "\nPrivate Key (HEX): " << keys[i] << std::endl;
                outfile << "Bitcoin Address: " << addr_list[i] << std::endl;
                outfile.close();

                return true;  // Match gevonden
            }
        }
    }

    return false;  // Geen match gevonden in dit bereik
}

int main() {
    srand(time(0));  // Zet de random zaadwaarde

    // Laad de adressen uit het bestand
    std::set<std::string> add;
    std::ifstream infile("puzzle.txt");
    std::string line;
    while (std::getline(infile, line)) {
        if (!line.empty()) {
            add.insert(line);
        }
    }

    std::cout << "Loaded " << add.size() << " addresses from puzzle.txt." << std::endl;

    // Definieer de HEX-bereiken
    std::vector<std::pair<std::string, std::string>> ranges = {
        {"4a000000000000000", "4ffffffffffffffff"},
        {"5a000000000000000", "5ffffffffffffffff"},
        {"6a000000000000000", "6ffffffffffffffff"},
        {"7a000000000000000", "7ffffffffffffffff"}
    };

    std::cout << "\nZoeken gestart... Veel succes!" << std::endl;

    // Cyclisch zoeken totdat een match wordt gevonden
    while (true) {
        for (const auto &range : ranges) {
            const std::string &start_hex = range.first;
            const std::string &end_hex = range.second;
            std::cout << "\nBezig met bereik: " << start_hex << " - " << end_hex << std::endl;

            // Zoek binnen het huidige bereik
            if (sequential_search(start_hex, end_hex, add)) {
                std::cout << "Match gevonden! Programma wordt afgesloten." << std::endl;
                return 0;
            }
        }
    }

    return 0;
}
