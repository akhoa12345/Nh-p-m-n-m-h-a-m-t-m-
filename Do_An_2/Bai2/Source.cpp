#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

// Function to calculate (base^exp) % mod
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to perform Diffie-Hellman key exchange
long long diffieHellman(long long base, long long prime, long long private_key) {
    return modPow(base, private_key, prime);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input_file output_file" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1]);
    std::ofstream output_file(argv[2]);

    if (!input_file.is_open() || !output_file.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return 1;
    }

    // Read input values from the file
    long long p, g, a, b;
    input_file >> std::hex >> p >> g >> a >> b;

    // Calculate public keys and shared secret
    long long A = diffieHellman(g, p, a);
    long long B = diffieHellman(g, p, b);
    long long K = diffieHellman(A, p, b);

    // Write output to the file
    output_file << std::hex << std::uppercase << A << std::endl;
    output_file << std::hex << std::uppercase << B << std::endl;
    output_file << std::hex << std::uppercase << K << std::endl;

    // Close files
    input_file.close();
    output_file.close();

    return 0;
}
