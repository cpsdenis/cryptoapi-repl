#include <windows.h>
#include <wincrypt.h>
#include <WinCryptEx.h>
#include <iostream>
#include <vector>
#include <iomanip>

// Helper to print bytes as a hex string
void printHex(const std::vector<BYTE>& data) {
    for (BYTE b : data) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    }
    std::cout << std::dec << std::endl;
}

int main() {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    
    std::string message = "Hello, CryptoPro SDK!";
    std::vector<BYTE> hashResult;
    DWORD hashLen = 0;

    // 1. Acquire a cryptographic provider context for GOST R 34.10-2012 (256-bit)
    // PROV_GOST_2012_256 is declared inside WinCryptEx.h
    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_GOST_2012_256, CRYPT_VERIFYCONTEXT)) {
        DWORD err = GetLastError();
        std::cerr << "CryptAcquireContext failed. Error: 0x" << std::hex << err << std::endl;
        return 1;
    }

    // 2. Create a hash object
    // CALG_GR3411_2012_256 is declared inside WinCryptEx.h
    if (!CryptCreateHash(hProv, CALG_GR3411_2012_256, 0, 0, &hHash)) {
        std::cerr << "CryptCreateHash failed. Error: " << GetLastError() << std::endl;
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    // 3. Hash the data
    if (!CryptHashData(hHash, reinterpret_cast<const BYTE*>(message.c_str()), static_cast<DWORD>(message.length()), 0)) {
        std::cerr << "CryptHashData failed. Error: " << GetLastError() << std::endl;
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    // 4. Retrieve the hash size
    DWORD dwSize = sizeof(DWORD);
    if (!CryptGetHashParam(hHash, HP_HASHSIZE, reinterpret_cast<BYTE*>(&hashLen), &dwSize, 0)) {
        std::cerr << "CryptGetHashParam (size) failed. Error: " << GetLastError() << std::endl;
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    // 5. Get the hash value
    hashResult.resize(hashLen);
    if (!CryptGetHashParam(hHash, HP_HASHVAL, hashResult.data(), &hashLen, 0)) {
        std::cerr << "CryptGetHashParam (value) failed. Error: " << GetLastError() << std::endl;
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    // Output the result (in Little-Endian format, as returned by CryptoAPI)
    std::cout << "Data: " << message << std::endl;
    std::cout << "GOST R 34.11-2012 (256): ";
    printHex(hashResult);

    // 6. Clean up resources
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return 0;
}
