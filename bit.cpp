#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <iomanip>
#include <sstream>

// Functie om een uint64_t om te zetten naar een hexadecimale string
std::string uint64_to_hex(uint64_t value) {
    std::stringstream ss;
    ss << std::setw(16) << std::setfill('0') << std::hex << value;
    return ss.str();
}

// Simulatie van een Bitcoin Key class, voor het genereren van een adres
class Key {
public:
    static Key from_hex(const std::string &hex) {
        Key key;
        // Simuleer het Bitcoin-adres: neem de eerste 34 tekens van de hexstring
        key.address = "1" + hex.substr(0, 34);
        return key;
    }

    std::string address;
};

// Sequentiële zoekfunctie door het opgegeven hexadecimale bereik
bool sequential_search(const std::string &start_hex, const std::string &end_hex, const std::set<std::string> &addresses, int bulk_size = 20) {
    uint64_t start = std::stoull(start_hex, nullptr, 16);
    uint64_t end = std::stoull(end_hex, nullptr, 16);
    uint64_t current = start;

    while (current <= end) {
        for (int i = 0; i < bulk_size && current <= end; ++i) {
            std::string magic = uint64_to_hex(current);  // Genereer de hex sleutel
            Key key = Key::from_hex(magic);  // Genereer het Bitcoin adres uit de hex

            std::cout << "(H): " << magic << " : " << key.address << std::endl;

            // Controleer of het gegenereerde adres overeenkomt met een adres in de set
            if (addresses.find(key.address) != addresses.end()) {
                std::cout << "\nGevonden! Winnende details:\n";
                std::cout << "Private Key (HEX): " << magic << "\nBitcoin Address: " << key.address << std::endl;

                // Log de winnende gegevens naar een bestand
                std::ofstream outfile("winner.txt", std::ios::app);
                outfile << "Private Key (HEX): " << magic << "\nBitcoin Address: " << key.address << std::endl;
                outfile.close();

                return true;  // Match gevonden
            }

            current++;  // Verhoog de huidige waarde met 1
        }
    }

    return false;  // Geen match gevonden
}

int main() {
    std::cout << "Bitcoin Adres Zoeken gestart... veel succes!" << std::endl;

    // Laad de adressen uit het bestand
    std::set<std::string> addresses;
    std::ifstream infile("puzzle.txt");
    std::string line;
    while (std::getline(infile, line)) {
        if (!line.empty()) {
            addresses.insert(line);  // Voeg elk adres toe aan de set
        }
    }

    std::cout << "Laad " << addresses.size() << " adressen uit puzzle.txt." << std::endl;

    // Definieer de hexadecimale zoekbereiken
    std::vector<std::pair<std::string, std::string>> ranges = {
        {"4a000000000000000", "4ffffffffffffffff"},
        {"5a000000000000000", "5ffffffffffffffff"},
        {"6a000000000000000", "6ffffffffffffffff"},
        {"7a000000000000000", "7ffffffffffffffff"}
    };

    // Zoek binnen de gedefinieerde bereiken
    while (true) {
        for (const auto &range : ranges) {
            std::cout << "\nBezig met bereik: " << range.first << " - " << range.second << std::endl;

            // Voer de zoekfunctie uit binnen dit bereik
            if (sequential_search(range.first, range.second, addresses)) {
                std::cout << "Match gevonden! Programma wordt afgesloten." << std::endl;
                return 0;  // Stop het programma als we een match vinden
            }
        }
    }

    return 0;
}
