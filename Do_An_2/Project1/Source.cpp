#include <iostream>
#include <fstream>
#include <vector>

// Hàm kiểm tra xem g có phải là căn nguyên thủy modulo p không
bool isPrimitiveRoot(unsigned long long g, unsigned long long p, const std::vector<int>& factors) {
    if (g <= 1 || g >= p) {
        return false;
    }

    for (int factor : factors) {
        unsigned long long result = 1;
        for (int i = 0; i < (p - 1) / factor; ++i) {
            result = (result * g) % p;
        }

        if (result == 1) {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input_file output_file" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return 1;
    }

    unsigned long long p, n, g;
    input >> p >> n;

    std::vector<int> factors(n);
    for (int i = 0; i < n; ++i) {
        input >> factors[i];
    }

    input >> g;

    int result = isPrimitiveRoot(g, p, factors) ? 1 : 0;
    output << result << std::endl;

    input.close();
    output.close();

    return 0;
}
